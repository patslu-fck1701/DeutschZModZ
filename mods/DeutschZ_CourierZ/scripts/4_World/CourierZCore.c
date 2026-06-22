/*
    DeutschZ_CourierZ main server-authoritative event manager.
    Safe test flow: autostart, visible case pickup by proximity, delivery by proximity, reward cleanup.
*/

static ref CourierZCore g_CourierZCore;

CourierZCore CourierZ_GetCore()
{
    if (!g_CourierZCore)
        g_CourierZCore = new CourierZCore;
    return g_CourierZCore;
}

class CourierZCore
{
    protected ref CourierZConfig m_Config;
    protected ref CourierZState m_State;
    protected Object m_CaseObject;
    protected Object m_RewardObject;
    protected ref array<Object> m_Enemies;
    protected float m_LastTick;
    protected float m_LastStatus;
    protected int m_DeliveryProgressSeconds;
    protected int m_Initialized;

    void CourierZCore()
    {
        m_Enemies = new array<Object>;
        m_DeliveryProgressSeconds = 0;
    }

    void InitServer()
    {
        if (m_Initialized)
            return;
        if (!GetGame() || !GetGame().IsServer())
            return;

        m_Config = CourierZConfig.Load();
        m_State = CourierZPersistence.LoadState();
        m_Initialized = 1;

        if (m_State.State == CourierZConstants.STATE_WAITING_FOR_CARRIER)
        {
            m_CaseObject = CourierZItems.SpawnObject(m_Config.CaseClassName, m_State.CasePosition);
            CreateStartMarkers();
            CourierZBridge.Notify("recovery", "CourierZ wiederhergestellt", "Aktiver Aktenkoffer wurde nach Restart wiederhergestellt.", m_State.CasePosition);
        }
        else if (m_State.State == CourierZConstants.STATE_IN_TRANSIT)
        {
            CreateTransitMarkers();
            CourierZBridge.Notify("recovery", "CourierZ wiederhergestellt", "Aktiver Kurierauftrag wurde nach Restart wiederhergestellt.", m_State.CarrierLastPosition);
        }
        else if (m_Config.DeutschZEventSettings.Scheduling.AutoStartAfterRestart == 1 && m_State.State == CourierZConstants.STATE_IDLE)
        {
            ScheduleNext(m_Config.DeutschZEventSettings.Scheduling.StartDelayMinSeconds);
        }

        CourierZBridge.Notify("init", "CourierZ bereit", "Operation Aktenkoffer ist geladen. Testevent wird automatisch geplant.", m_Config.ContactPosition);
        DeutschZCore_Log.Info(CourierZConstants.LOG_SCOPE, "initialized state=" + CourierZ_StateName(m_State.State));
    }

    void Tick()
    {
        if (!m_Initialized || !m_Config || !m_State)
            return;
        if (!GetGame() || !GetGame().IsServer())
            return;

        float now = GetGame().GetTime() * 0.001;
        if (now - m_LastTick < 1.0)
            return;
        m_LastTick = now;

        if (m_State.State == CourierZConstants.STATE_SCHEDULED)
        {
            if (now >= m_State.NextAutoStartAt)
                TryStartEvent();
            return;
        }

        if (m_State.State == CourierZConstants.STATE_WAITING_FOR_CARRIER)
        {
            TickWaitingForCarrier(now);
            return;
        }

        if (m_State.State == CourierZConstants.STATE_IN_TRANSIT)
        {
            TickInTransit(now);
            return;
        }

        if (m_State.State == CourierZConstants.STATE_CLEANUP)
        {
            if (now >= m_State.CleanupAt)
                FinishCleanupAndReschedule();
            return;
        }
    }

    protected void ScheduleNext(int delaySeconds)
    {
        if (!m_State)
            return;
        float now = GetGame().GetTime() * 0.001;
        m_State.State = CourierZConstants.STATE_SCHEDULED;
        m_State.NextAutoStartAt = now + delaySeconds;
        CourierZPersistence.SaveState(m_State);
        CourierZBridge.Notify("scheduled", "CourierZ geplant", "Operation Aktenkoffer startet in ca. " + delaySeconds.ToString() + " Sekunden.", m_Config.ContactPosition);
    }

    protected bool HasEnoughPlayers()
    {
        array<Man> players = new array<Man>;
        GetGame().GetPlayers(players);
        return players.Count() >= m_Config.DeutschZEventSettings.Event.MinOnlinePlayers;
    }

    protected void TryStartEvent()
    {
        if (m_Config.DeutschZEventSettings.Event.Enabled == 0)
            return;

        if (!HasEnoughPlayers())
        {
            ScheduleNext(m_Config.DeutschZEventSettings.Scheduling.NoPlayerRetryDelaySeconds);
            return;
        }

        if (m_Config.DeutschZEventSettings.Event.MaxEventsPerRestart > 0 && m_State.EventsStartedThisRestart >= m_Config.DeutschZEventSettings.Event.MaxEventsPerRestart)
        {
            CourierZBridge.Notify("blocked", "CourierZ blockiert", "MaxEventsPerRestart erreicht.", m_Config.ContactPosition);
            m_State.State = CourierZConstants.STATE_IDLE;
            CourierZPersistence.SaveState(m_State);
            return;
        }

        CleanupRuntimeObjects(false);

        m_State.EventId = "CourierZ_" + GetGame().GetTime().ToString();
        m_State.State = CourierZConstants.STATE_WAITING_FOR_CARRIER;
        m_State.CasePosition = Grounded(m_Config.ContactPosition);
        m_State.DeliveryPosition = Grounded(m_Config.DeliveryPosition);
        m_State.CurrentCarrierID = "";
        m_State.CurrentCarrierName = "";
        m_State.StartedAt = GetGame().GetTime() * 0.001;
        m_State.EndsAt = m_State.StartedAt + m_Config.Courier.DeliveryTimeLimitSeconds;
        m_State.RequiredKills = m_Config.DeutschZEventSettings.Testing.RequiredKillsToWin;
        m_State.CurrentKills = 0;
        m_DeliveryProgressSeconds = 0;
        m_State.EventsStartedThisRestart++;

        m_CaseObject = CourierZItems.SpawnObject(m_Config.CaseClassName, m_State.CasePosition);
        SpawnEnemies(m_Config.StartEnemyCount, m_State.CasePosition);
        CreateStartMarkers();
        CourierZBridge.Notify("start", "Operation Aktenkoffer", "Ein versiegelter Aktenkoffer wartet auf Abholung. Naehere dich dem Marker und sichere den Koffer.", m_State.CasePosition);
        CourierZPersistence.SaveState(m_State);
    }

    protected vector Grounded(vector pos)
    {
        vector p = pos;
        p[1] = GetGame().SurfaceY(p[0], p[2]);
        return p;
    }

    protected void CreateStartMarkers()
    {
        if (m_Config.DeutschZEventSettings.Markers.Enabled == 0)
            return;

        string prefix = m_Config.DeutschZEventSettings.Markers.MarkerPrefix;
        if (m_Config.DeutschZEventSettings.Markers.UseMapMarker == 1)
            CourierZBridge.Marker(prefix + "case", "CourierZ Aktenkoffer", m_State.CasePosition, m_Config.DeutschZEventSettings.Markers.MarkerColorARGB);
        if (m_Config.DeutschZEventSettings.Markers.Use3DMarker == 1)
            CourierZBridge.Marker3D(prefix + "3D_case", "CourierZ Aktenkoffer 3D", m_State.CasePosition, m_Config.DeutschZEventSettings.Markers.MarkerColorARGB);
    }

    protected void CreateTransitMarkers()
    {
        if (m_Config.DeutschZEventSettings.Markers.Enabled == 0)
            return;

        string prefix = m_Config.DeutschZEventSettings.Markers.MarkerPrefix;
        CourierZBridge.DeleteMarkers(prefix);

        if (m_Config.DeutschZEventSettings.Markers.UseMapMarker == 1)
        {
            if (m_Config.DeutschZEventSettings.Markers.ShowCarrierMarker == 1)
                CourierZBridge.Marker(prefix + "carrier", "CourierZ Traeger", m_State.CarrierLastPosition, m_Config.DeutschZEventSettings.Markers.MarkerColorARGB);
            if (m_Config.DeutschZEventSettings.Markers.ShowExtractionMarker == 1)
                CourierZBridge.Marker(prefix + "delivery", "CourierZ Uebergabe", m_State.DeliveryPosition, m_Config.DeutschZEventSettings.Markers.MarkerColorARGB);
        }

        if (m_Config.DeutschZEventSettings.Markers.Use3DMarker == 1)
        {
            CourierZBridge.Marker3D(prefix + "3D_delivery", "CourierZ Uebergabe 3D", m_State.DeliveryPosition, m_Config.DeutschZEventSettings.Markers.MarkerColorARGB);
        }
    }

    protected void TickWaitingForCarrier(float now)
    {
        PlayerBase nearby = FindNearestPlayer(m_State.CasePosition, m_Config.Courier.PickupRadius);
        if (nearby && nearby.GetIdentity())
        {
            m_State.CurrentCarrierID = nearby.GetIdentity().GetPlainId();
            m_State.CurrentCarrierName = nearby.GetIdentity().GetName();
            m_State.CarrierLastPosition = nearby.GetPosition();
            m_State.State = CourierZConstants.STATE_IN_TRANSIT;
            m_DeliveryProgressSeconds = 0;
            SendPlayerMessage(nearby, "Aktenkoffer gesichert. Bringe ihn zur markierten Abgabestelle.");
            if (m_CaseObject)
            {
                GetGame().ObjectDelete(m_CaseObject);
                m_CaseObject = null;
            }
            SpawnEnemies(m_Config.DeliveryEnemyCount, m_State.DeliveryPosition);
            CreateTransitMarkers();
            CourierZBridge.Notify("carrier", "Kurier unterwegs", m_State.CurrentCarrierName + " hat den Aktenkoffer aufgenommen. Lieferung zum Zielpunkt starten.", m_State.CarrierLastPosition);
            CourierZPersistence.SaveState(m_State);
            return;
        }

        SendStatus(now, "Aktenkoffer wartet auf Abholung.", m_State.CasePosition);
        CheckTimeout(now);
    }

    protected void TickInTransit(float now)
    {
        PlayerBase carrier = FindCarrier();
        if (!carrier)
        {
            if (m_Config.Courier.DropCaseOnLogout == 1)
                DropCase(m_State.CarrierLastPosition, "Kurier nicht mehr online. Aktenkoffer wurde am letzten Standort abgeworfen.");
            else
                FailEvent("Kurier nicht mehr online.");
            return;
        }

        m_State.CarrierLastPosition = carrier.GetPosition();

        if (vector.Distance(carrier.GetPosition(), m_State.DeliveryPosition) <= m_Config.Courier.DeliveryRadius)
        {
            m_DeliveryProgressSeconds++;
            int requiredHold = m_Config.DeutschZEventSettings.Testing.ExtractionDurationSeconds;
            if (requiredHold < 5) requiredHold = 5;
            if (m_DeliveryProgressSeconds == 1)
                SendPlayerMessage(carrier, "Abgabestelle erreicht. Uebergabe laeuft - bleib im Radius.");
            SendStatus(now, "Uebergabe laeuft: " + m_DeliveryProgressSeconds.ToString() + "/" + requiredHold.ToString() + " Sekunden.", m_State.DeliveryPosition);
            if (m_DeliveryProgressSeconds >= requiredHold)
                CompleteEvent(carrier);
            return;
        }
        else if (m_DeliveryProgressSeconds > 0)
        {
            m_DeliveryProgressSeconds = 0;
            SendPlayerMessage(carrier, "Abgabestelle verlassen. Uebergabe wurde pausiert.");
        }

        if (m_Config.DeutschZEventSettings.Markers.UseDynamicPositionUpdates == 1)
        {
            string prefix = m_Config.DeutschZEventSettings.Markers.MarkerPrefix;
            DeutschZCore_MarkerProviderAPI markers = DeutschZCore_ServiceLocator.GetMarkerProvider();
            if (markers)
                markers.UpdateMarker(prefix + "carrier", m_State.CarrierLastPosition);
        }

        SendStatus(now, "Kurier ist unterwegs. Zielpunkt sichern und Aktenkoffer abliefern.", m_State.CarrierLastPosition);
        CheckTimeout(now);
    }

    protected void SendStatus(float now, string message, vector pos)
    {
        if (m_Config.DeutschZEventSettings.Notifications.StatusNotifications == 0)
            return;
        if (now - m_LastStatus < m_Config.DeutschZEventSettings.Notifications.StatusIntervalSeconds)
            return;
        m_LastStatus = now;
        CourierZBridge.Notify("status", "CourierZ Status", message, pos);
    }

    protected void CheckTimeout(float now)
    {
        if (m_Config.Courier.FailOnTimeExpired == 1 && now >= m_State.EndsAt)
            FailEvent("Zeitlimit abgelaufen.");
    }

    protected PlayerBase FindNearestPlayer(vector pos, float radius)
    {
        array<Man> players = new array<Man>;
        GetGame().GetPlayers(players);
        PlayerBase best;
        float bestDist = radius + 1.0;
        foreach (Man man: players)
        {
            PlayerBase player = PlayerBase.Cast(man);
            if (!player || !player.GetIdentity() || !player.IsAlive())
                continue;
            float dist = vector.Distance(player.GetPosition(), pos);
            if (dist <= radius && dist < bestDist)
            {
                best = player;
                bestDist = dist;
            }
        }
        return best;
    }

    protected PlayerBase FindCarrier()
    {
        if (m_State.CurrentCarrierID == "")
            return null;

        array<Man> players = new array<Man>;
        GetGame().GetPlayers(players);
        foreach (Man man: players)
        {
            PlayerBase player = PlayerBase.Cast(man);
            if (player && player.GetIdentity() && player.GetIdentity().GetPlainId() == m_State.CurrentCarrierID)
                return player;
        }
        return null;
    }

    void OnPlayerKilled(PlayerBase player)
    {
        if (!m_State || m_State.State != CourierZConstants.STATE_IN_TRANSIT)
            return;
        if (!player || !player.GetIdentity())
            return;
        if (player.GetIdentity().GetPlainId() != m_State.CurrentCarrierID)
            return;

        if (m_Config.Courier.DropCaseOnDeath == 1)
            DropCase(player.GetPosition(), "Kurier gefallen. Aktenkoffer wurde am Todesort abgeworfen.");
        else
            FailEvent("Kurier gefallen.");
    }

    protected void DropCase(vector position, string reason)
    {
        m_State.CurrentCarrierID = "";
        m_State.CurrentCarrierName = "";
        m_State.CasePosition = Grounded(position);
        m_State.State = CourierZConstants.STATE_WAITING_FOR_CARRIER;
        m_DeliveryProgressSeconds = 0;
        m_CaseObject = CourierZItems.SpawnObject(m_Config.CaseClassName, m_State.CasePosition);
        CreateStartMarkers();
        CourierZBridge.Notify("drop", "Aktenkoffer verloren", reason, m_State.CasePosition);
        CourierZPersistence.SaveState(m_State);
    }

    protected void CompleteEvent(PlayerBase carrier)
    {
        m_State.State = CourierZConstants.STATE_DELIVERED;
        SendPlayerMessage(carrier, "CourierZ abgeschlossen. DeutschZ Belohnungskiste wurde freigegeben.");
        CourierZBridge.Notify("complete", "Lieferung abgeschlossen", "Operation Aktenkoffer erfolgreich abgeschlossen. DeutschZ Rewardchest freigegeben.", m_State.DeliveryPosition);
        SpawnReward(m_State.DeliveryPosition);
        StartCleanup();
    }

    protected void FailEvent(string reason)
    {
        m_State.State = CourierZConstants.STATE_FAILED;
        CourierZBridge.Notify("failed", "CourierZ fehlgeschlagen", reason, m_State.CasePosition);
        StartCleanup();
    }

    protected void StartCleanup()
    {
        m_State.State = CourierZConstants.STATE_CLEANUP;
        m_State.CleanupAt = GetGame().GetTime() * 0.001 + m_Config.DeutschZEventSettings.Event.CleanupDelaySeconds;
        CourierZPersistence.SaveState(m_State);
    }

    protected void FinishCleanupAndReschedule()
    {
        CleanupRuntimeObjects(true);
        m_State.Reset();
        CourierZPersistence.SaveState(m_State);

        if (m_Config.DeutschZEventSettings.Scheduling.RestartAfterFinish == 1)
            ScheduleNext(m_Config.DeutschZEventSettings.Scheduling.RestartDelayMinSeconds);
    }

    protected void CleanupRuntimeObjects(bool deleteReward)
    {
        CourierZBridge.DeleteMarkers(m_Config.DeutschZEventSettings.Markers.MarkerPrefix);
        if (m_CaseObject)
        {
            GetGame().ObjectDelete(m_CaseObject);
            m_CaseObject = null;
        }
        if (deleteReward && m_RewardObject)
        {
            GetGame().ObjectDelete(m_RewardObject);
            m_RewardObject = null;
        }
        foreach (Object obj: m_Enemies)
        {
            if (obj)
                GetGame().ObjectDelete(obj);
        }
        m_Enemies.Clear();
        DeutschZCore_AIProviderAPI ai = DeutschZCore_ServiceLocator.GetAIProvider();
        if (ai && m_State.EventId != "")
            ai.CleanupEventAI(m_State.EventId);
    }

    protected void SpawnEnemies(int count, vector center)
    {
        for (int i = 0; i < count; i++)
        {
            vector pos = center + Vector(Math.RandomFloat(-m_Config.Courier.EnemySpawnRadius, m_Config.Courier.EnemySpawnRadius), 0, Math.RandomFloat(-m_Config.Courier.EnemySpawnRadius, m_Config.Courier.EnemySpawnRadius));
            bool ok = CourierZBridge.SpawnEnemy(m_State.EventId, m_Config.EnemyClassName, pos);
            if (!ok)
                DeutschZCore_Log.Warn(CourierZConstants.LOG_SCOPE, "enemy spawn failed");
        }
    }

    protected void SendPlayerMessage(PlayerBase player, string message)
    {
        if (!player || !player.GetIdentity() || message == "")
            return;

        Param1<string> data = new Param1<string>(message);
        GetGame().RPCSingleParam(player, ERPCs.RPC_USER_ACTION_MESSAGE, data, true, player.GetIdentity());
    }

    protected void SpawnReward(vector position)
    {
        if (m_Config.Courier.RewardOnDelivery == 0)
            return;

        if (m_Config.RewardChestClassName == "" || m_Config.RewardChestClassName == "SeaChest" || m_Config.RewardChestClassName == "WoodenCrate" || m_Config.RewardChestClassName == "Barrel_ColorBase")
            m_Config.RewardChestClassName = "DZCR_RewardChest";

        m_RewardObject = CourierZItems.SpawnObject(m_Config.RewardChestClassName, position);
        EntityAI container = EntityAI.Cast(m_RewardObject);
        if (!container)
            return;

        foreach (string itemClass: m_Config.RewardItems)
        {
            if (itemClass != "" && !DeutschZCore_UnsafeClassGuard.IsBlockedClass(itemClass) && GetGame().ConfigIsExisting("CfgVehicles " + itemClass))
                container.GetInventory().CreateInInventory(itemClass);
        }
    }
}
