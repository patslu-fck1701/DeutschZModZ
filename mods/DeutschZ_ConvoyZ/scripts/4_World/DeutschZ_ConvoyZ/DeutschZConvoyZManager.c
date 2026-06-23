/*
DeutschZ ModZ
Eigenstaendige Implementierung fuer DeutschZ.
Autor/Eigentuemer: Patrick Sluzalek / fck1701.
Projekt: DeutschZ.
Modul: DeutschZ_ConvoyZ.
Zweck der Datei: Serverseitige ConvoyZ-Eventlogik, Ablauf, Status und Sicherheitspruefung.
Quellen-/Konzeptnachweis: Eigene DeutschZ-Implementierung; DayZ/CF/Expansion werden nur als Laufzeit-Abhaengigkeit/API genutzt.
Keine direkte Codeuebernahme aus Drittquellen.
*/

static ref DeutschZConvoyZManager g_DeutschZConvoyZManager;
DeutschZConvoyZManager DeutschZConvoyZ_GetManager()
{
    if (!g_DeutschZConvoyZManager) g_DeutschZConvoyZManager = new DeutschZConvoyZManager();
    return g_DeutschZConvoyZManager;
}

class DeutschZConvoyZManager
{
    ref DeutschZConvoyZConfig Config;
    ref DeutschZConvoyZRuntimeState State;
    ref DeutschZConvoyZSpawnManager Spawn;
    ref DeutschZConvoyZAIManager AI;
    ref DeutschZConvoyZHackManager Hack;
    ref DeutschZConvoyZRewardManager Reward;
    ref DeutschZConvoyZCleanupManager CleanupMgr;
    int EventLock;
    int AutoStartScheduled;
    int EventsStartedThisRestart;
    int NextAutoStartAt;

    void DeutschZConvoyZManager()
    {
        Config = new DeutschZConvoyZConfig();
        Spawn = new DeutschZConvoyZSpawnManager();
        AI = new DeutschZConvoyZAIManager();
        Hack = new DeutschZConvoyZHackManager(this);
        Reward = new DeutschZConvoyZRewardManager();
        CleanupMgr = new DeutschZConvoyZCleanupManager(this);
    }

    void Init()
    {
        if (!GetGame() || !GetGame().IsServer()) return;
        Config.Load();
        Reward.Load();
        if (!DeutschZConvoyZValidator.ValidateConfig(Config)) return;
        if (Config.Settings.AutoStartOnMissionInit == 1 && Config.Settings.EnableConvoyZEvent == 1) ScheduleAutoStart(1, "mission init");
    }

    bool StartEvent()
    {
        if (!GetGame() || !GetGame().IsServer()) return false;
        if (!CanStartNewEvent()) return false;
        EventLock = 1;
        State = new DeutschZConvoyZRuntimeState();
        State.EventId = Config.EventData.EventIdPrefix + "_" + GetGame().GetTime().ToString();
        State.EventProcessing = 1;
        State.EventStartedAt = GetGame().GetTime();
        EventsStartedThisRestart++;
        State.RequiredKills = Config.EventData.RequiredAiKills;
        if (State.RequiredKills <= 0) State.RequiredKills = Config.Settings.RequiredAiKills;
        ChangeState(DeutschZConvoyZConstants.STATE_SPAWNING, "start");
        DeutschZConvoyZLogger.Log("EventStart", State.EventId, "SPAWNING", "", Config.EventData.EventCenter, "OK", Config.EventData.EventName);
        if (!Spawn.SpawnCrashSite(Config, State))
        {
            Fail("critical spawn failed");
            EventLock = 0;
            return false;
        }
        SetSmoke(DeutschZConvoyZConstants.SMOKE_RED);
        DeutschZConvoyZ_ExpansionNotify("DeutschZ ConvoyZ", "Top Secret Crash Convoy gestartet.", GetEventPosition());
        ChangeState(DeutschZConvoyZConstants.STATE_SECURE_AREA, "spawn ok");
        AI.StartWaves(Config, State);
        if (Config.Settings.UseEventMarker == 1) DeutschZConvoyZ_RegisterMarker(State.EventId, GetEventPosition(), Config.EventData.EventName);
        GetGame().GetCallQueue(CALL_CATEGORY_SYSTEM).Remove(this.Tick);
        GetGame().GetCallQueue(CALL_CATEGORY_SYSTEM).CallLater(this.Tick, 1000, true);
        SyncStatusNow();
        EventLock = 0;
        return true;
    }

    void Tick()
    {
        if (!GetGame() || !GetGame().IsServer() || !State || !Config) return;
        if (State.CurrentState == DeutschZConvoyZConstants.STATE_CLEANUP || State.CurrentState == DeutschZConvoyZConstants.STATE_FAILED) return;
        CheckEventTimeouts();
        if (!State) return;
        Spawn.RefreshSmoke(Config, State);
        SendStatusNotification();
        AI.Tick(Config, State);
        UpdateCarrierMarker();
        CheckDeliveryProgress();
        if (State.CurrentState == DeutschZConvoyZConstants.STATE_SECURE_AREA && State.CurrentKills >= State.RequiredKills) SetBlackboxReady();
        SyncStatusThrottled();
    }

    void SetBlackboxReady()
    {
        if (!State || State.CurrentState != DeutschZConvoyZConstants.STATE_SECURE_AREA) return;
        ChangeState(DeutschZConvoyZConstants.STATE_BLACKBOX_READY, "required AI killed");
        SetSmoke(DeutschZConvoyZConstants.SMOKE_YELLOW);
        DeutschZConvoyZ_ExpansionNotify("DeutschZ ConvoyZ", "Blackbox ist bereit. Hack starten.", GetBlackboxPosition());
        DeutschZConvoyZLogger.Log("BlackboxReady", State.EventId, "BLACKBOX_READY", "", GetBlackboxPosition(), "OK", "");
        SyncStatusNow();
    }

    bool IsBlackbox(Object obj)
    {
        return State && obj && State.BlackboxEntity == obj;
    }

    bool CanHack(PlayerBase player, Object obj)
    {
        if (!State || !Config) return false;
        if (State.CurrentState != DeutschZConvoyZConstants.STATE_BLACKBOX_READY && State.CurrentState != DeutschZConvoyZConstants.STATE_HACKING) return false;
        if (!IsBlackbox(obj)) return false;
        return DeutschZConvoyZValidator.CanHack(player, obj, Config.Settings.BlackboxMaxHackDistance);
    }

    bool RequestHackStart(PlayerBase player)
    {
        return Hack.StartHack(player);
    }

    bool RequestHackStop(PlayerBase player)
    {
        return Hack.StopHack(player, "action released");
    }

    void OnEntityKilled(Object victim, Object killer)
    {
        if (!State || !victim) return;
        PlayerBase killerPlayer = PlayerBase.Cast(killer);
        AI.OnKilled(State, victim, killerPlayer);
        if (State.CurrentState == DeutschZConvoyZConstants.STATE_SECURE_AREA && State.CurrentKills >= State.RequiredKills) SetBlackboxReady();
    }

    void ChangeState(int newState, string reason)
    {
        if (!State) return;
        int old = State.CurrentState;
        State.CurrentState = newState;
        if (newState == DeutschZConvoyZConstants.STATE_BLACKBOX_READY) State.BlackboxReadyAt = GetGame().GetTime();
        if (newState == DeutschZConvoyZConstants.STATE_REWARD_UNLOCKED) State.RewardUnlockedAt = GetGame().GetTime();
        DeutschZConvoyZLogger.Log("StateChanged", State.EventId, DeutschZConvoyZ_StateName(newState), "", GetEventPosition(), "OK", DeutschZConvoyZ_StateName(old) + " -> " + DeutschZConvoyZ_StateName(newState) + " " + reason);
        SendStatusNotification(true);
    }

    void SetSmoke(string smokeState)
    {
        Spawn.SetSmoke(Config, State, smokeState);
    }

    void UnlockReward()
    {
        Reward.Unlock(Config, State);
    }

    void StartDeliveryStage(PlayerBase player, string hackerId)
    {
        if (!State || !Config || !Config.Settings || !player || !player.GetIdentity()) return;

        State.CarrierPlayerId = hackerId;
        State.DeliveryActive = 1;
        State.DeliveryComplete = 0;
        State.LastCarrierMarkerAt = 0;

        GiveItemToPlayer(player, Config.Settings.CarryItemClassName, GetBlackboxPosition());
        GiveItemToPlayer(player, "DZCV_BlackboxDeliveryNote", GetBlackboxPosition());

        ChangeState(DeutschZConvoyZConstants.STATE_DELIVERY_ACTIVE, "blackbox recovered; delivery active");
        SetSmoke(DeutschZConvoyZConstants.SMOKE_GREEN);
        RegisterDeliveryMarker();
        UpdateCarrierMarker(true);
        SendPlayerMessage(player, "DeutschZ ConvoyZ: Blackbox gesichert. Bring sie zum Kontaktmann. Deine Position pingt unregelmaessig.");
        DeutschZConvoyZ_ExpansionNotify("DeutschZ ConvoyZ", "Blackbox geborgen. Traeger wurde markiert.", player.GetPosition());
        DeutschZConvoyZLogger.Log("DeliveryActive", State.EventId, "DELIVERY_ACTIVE", hackerId, player.GetPosition(), "OK", Config.Settings.DeliveryNpcName);
        SyncStatusNow();
    }

    bool GiveItemToPlayer(PlayerBase player, string className, vector fallbackPos)
    {
        if (!player || className == "") return false;
        if (DeutschZCore_UnsafeClassGuard.IsBlockedClass(className)) return false;
        if (!DeutschZConvoyZValidator.IsConfiguredInventoryClass(className))
        {
            DeutschZConvoyZLogger.Log("GiveItemClassMissing", State.EventId, DeutschZConvoyZ_StateName(State.CurrentState), "", fallbackPos, "SKIPPED", className);
            return false;
        }
        EntityAI created = EntityAI.Cast(player.GetInventory().CreateInInventory(className));
        if (!created)
        {
            vector p = fallbackPos;
            p[1] = GetGame().SurfaceY(p[0], p[2]) + 0.75;
            created = EntityAI.Cast(GetGame().CreateObjectEx(className, p, ECE_PLACE_ON_SURFACE | ECE_SETUP));
        }
        if (created)
        {
            DeutschZConvoyZLogger.Log("GiveItem", State.EventId, DeutschZConvoyZ_StateName(State.CurrentState), "", created.GetPosition(), "OK", className);
            return true;
        }
        DeutschZConvoyZLogger.Log("GiveItemFailed", State.EventId, DeutschZConvoyZ_StateName(State.CurrentState), "", fallbackPos, "FAILED", className);
        return false;
    }

    PlayerBase FindCarrierPlayer()
    {
        if (!State || State.CarrierPlayerId == "") return null;
        array<Man> players = new array<Man>;
        GetGame().GetPlayers(players);
        foreach (Man man: players)
        {
            PlayerBase pb = PlayerBase.Cast(man);
            if (pb && pb.GetIdentity() && pb.GetIdentity().GetPlainId() == State.CarrierPlayerId) return pb;
        }
        return null;
    }

    void RegisterDeliveryMarker()
    {
        if (!State || !Config || !Config.Settings) return;
        vector p = Config.Settings.DeliveryNpcPosition;
        p[1] = GetGame().SurfaceY(p[0], p[2]) + 2.0;
        DeutschZConvoyZCoreBridge.CreateEventMarker(State.EventId + "_delivery", Config.Settings.DeliveryNpcName, p);
        DeutschZConvoyZCoreBridge.CreateEvent3DMarker(State.EventId + "_delivery", Config.Settings.DeliveryNpcName, p);
    }

    void UpdateCarrierMarker(bool force = false)
    {
        if (!State || !Config || !Config.Settings) return;
        if (State.CurrentState != DeutschZConvoyZConstants.STATE_DELIVERY_ACTIVE) return;
        if (State.CarrierPlayerId == "") return;

        int interval = Config.Settings.CarrierMarkerUpdateSeconds;
        if (interval < 10) interval = 10;
        int now = GetGame().GetTime();
        if (!force && State.LastCarrierMarkerAt > 0 && now - State.LastCarrierMarkerAt < interval * 1000) return;

        PlayerBase carrier = FindCarrierPlayer();
        if (!carrier) return;
        State.LastCarrierMarkerAt = now;
        string markerId = State.EventId + "_carrier";
        DeutschZConvoyZCoreBridge.DeleteEventMarker(markerId);
        DeutschZConvoyZCoreBridge.CreateEventMarker(markerId, "ConvoyZ Blackbox-Traeger", carrier.GetPosition());
        DeutschZConvoyZCoreBridge.CreateEvent3DMarker(markerId, "ConvoyZ Blackbox-Traeger", carrier.GetPosition());
        DeutschZConvoyZLogger.Log("CarrierMarkerPing", State.EventId, "DELIVERY_ACTIVE", State.CarrierPlayerId, carrier.GetPosition(), "OK", "short ping");
    }

    void CheckDeliveryProgress()
    {
        if (!State || !Config || !Config.Settings) return;
        if (State.CurrentState != DeutschZConvoyZConstants.STATE_DELIVERY_ACTIVE) return;
        if (State.DeliveryComplete == 1) return;

        PlayerBase carrier = FindCarrierPlayer();
        if (!carrier) return;
        float radius = Config.Settings.DeliveryRadius;
        if (radius < 2.0) radius = 2.0;
        if (vector.Distance(carrier.GetPosition(), Config.Settings.DeliveryNpcPosition) <= radius)
        {
            CompleteDelivery(carrier);
        }
    }

    void CompleteDelivery(PlayerBase player)
    {
        if (!State || !Config || !Config.Settings || !player) return;
        State.DeliveryComplete = 1;
        State.DeliveryActive = 0;
        ChangeState(DeutschZConvoyZConstants.STATE_DELIVERED, "blackbox delivered to npc");

        GiveItemToPlayer(player, Config.Settings.DeliveryRewardItemClassName, Config.Settings.DeliveryNpcPosition);
        GiveItemToPlayer(player, Config.Settings.DeliveryMapFragmentClassName, Config.Settings.DeliveryNpcPosition);
        GiveItemToPlayer(player, Config.Settings.DeliveryNoteItemClassName, Config.Settings.DeliveryNpcPosition);
        GiveItemToPlayer(player, "DZCV_OperationLead", Config.Settings.DeliveryNpcPosition);

        SendPlayerMessage(player, "Kontaktmann: " + Config.Settings.DeliveryHintText);
        DeutschZConvoyZ_ExpansionNotify("DeutschZ ConvoyZ", "Blackbox beim Kontaktmann abgegeben. Operation-Spur freigeschaltet.", player.GetPosition());
        DeutschZConvoyZLogger.Log("DeliveryComplete", State.EventId, "DELIVERED", State.CarrierPlayerId, player.GetPosition(), "OK", Config.Settings.DeliveryRewardItemClassName);

        Reward.Unlock(Config, State);
        ChangeState(DeutschZConvoyZConstants.STATE_REWARD_UNLOCKED, "delivery complete reward unlocked");
        ScheduleCleanup();
        SyncStatusNow();
    }

    void SendPlayerMessage(PlayerBase player, string text)
    {
        if (!player || !player.GetIdentity() || text == "") return;
        Param1<string> data = new Param1<string>(text);
        GetGame().RPCSingleParam(player, ERPCs.RPC_USER_ACTION_MESSAGE, data, true, player.GetIdentity());
    }

    void ScheduleCleanup()
    {
        if (!State) return;
        State.CleanupPending = 1;
        GetGame().GetCallQueue(CALL_CATEGORY_SYSTEM).Remove(this.DelayedCleanup);
        GetGame().GetCallQueue(CALL_CATEGORY_SYSTEM).CallLater(this.DelayedCleanup, Config.Settings.CleanupDelaySeconds * 1000, false);
    }

    void DelayedCleanup()
    {
        Cleanup("delayed");
    }

    void Cleanup(string reason)
    {
        CleanupMgr.Cleanup(reason);
    }

    void Fail(string reason)
    {
        if (!State) return;
        ChangeState(DeutschZConvoyZConstants.STATE_FAILED, reason);
        SetSmoke(DeutschZConvoyZConstants.SMOKE_WHITE);
        DeutschZConvoyZ_ExpansionNotify("DeutschZ ConvoyZ", "Convoy Event fehlgeschlagen.", GetEventPosition());
        DeutschZConvoyZLogger.Log("EventFailed", State.EventId, "FAILED", "", GetEventPosition(), "FAILED", reason);
        ScheduleCleanup();
    }

    bool CanStartNewEvent()
    {
        if (!GetGame()) return false;
        if (!GetGame().IsServer()) return false;

        if (!Config) return false;
        if (!Config.Settings) return false;
        if (Config.Settings.EnableConvoyZEvent == 0) return false;

        if (State)
        {
            if (State.EventProcessing == 1) return false;
        }

        if (Config.Settings.MinOnlinePlayersToStart > 0)
        {
            array<Man> players = new array<Man>;
            GetGame().GetPlayers(players);
            if (players.Count() < Config.Settings.MinOnlinePlayersToStart) return false;
        }

        return true;
    }


    void ScheduleAutoStart(int initial, string reason)
    {
        if (!GetGame() || !GetGame().IsServer()) return;
        if (!Config || !Config.Settings) return;
        if (Config.Settings.EnableConvoyZEvent == 0) return;

        int minDelay = Config.Settings.InitialStartDelayMinSeconds;
        int maxDelay = Config.Settings.InitialStartDelayMaxSeconds;

        if (initial == 0)
        {
            if (Config.Settings.RestartEventAfterCleanup == 0) return;
            minDelay = Config.Settings.RestartDelayMinSeconds;
            maxDelay = Config.Settings.RestartDelayMaxSeconds;
        }

        if (minDelay < 0) minDelay = 0;
        if (maxDelay < minDelay) maxDelay = minDelay;

        int delaySec = minDelay;
        if (maxDelay > minDelay)
        {
            int rollMax = maxDelay + 1;
            delaySec = Math.RandomInt(minDelay, rollMax);
        }

        int delayMs = delaySec * 1000;
        NextAutoStartAt = GetGame().GetTime() + delayMs;
        AutoStartScheduled = 1;

        GetGame().GetCallQueue(CALL_CATEGORY_SYSTEM).Remove(this.TryAutoStart);
        GetGame().GetCallQueue(CALL_CATEGORY_SYSTEM).CallLater(this.TryAutoStart, delayMs, false);

        DeutschZConvoyZLogger.Log("AutoStartScheduled", "", "SCHEDULED", "", GetEventPosition(), "OK", reason + " delay " + delaySec.ToString() + "s");
    }

    void TryAutoStart()
    {
        AutoStartScheduled = 0;

        if (!CanStartNewEvent())
        {
            if (!Config || !Config.Settings) return;
            if (Config.Settings.MaxEventsPerRestart > 0 && EventsStartedThisRestart >= Config.Settings.MaxEventsPerRestart) return;

            int retrySec = Config.Settings.NoPlayerRetryDelaySeconds;
            if (retrySec < 30) retrySec = 30;

            int retryMs = retrySec * 1000;
            AutoStartScheduled = 1;
            NextAutoStartAt = GetGame().GetTime() + retryMs;

            GetGame().GetCallQueue(CALL_CATEGORY_SYSTEM).Remove(this.TryAutoStart);
            GetGame().GetCallQueue(CALL_CATEGORY_SYSTEM).CallLater(this.TryAutoStart, retryMs, false);

            DeutschZConvoyZLogger.Log("AutoStartRetry", "", "SCHEDULED", "", GetEventPosition(), "WAIT", "retry " + retrySec.ToString() + "s");
            return;
        }

        StartEvent();
    }


    int GetOnlinePlayerCount()
    {
        array<Man> players = new array<Man>;
        GetGame().GetPlayers(players);
        return players.Count();
    }

    void CheckEventTimeouts()
    {
        if (!State || !Config || !Config.Settings) return;
        if (Config.Settings.AutoFailStuckEvent == 0) return;

        int now = GetGame().GetTime();

        if (Config.Settings.MaxEventRuntimeSeconds > 0 && State.EventStartedAt > 0)
        {
            int maxRuntimeMs = Config.Settings.MaxEventRuntimeSeconds * 1000;
            if (now - State.EventStartedAt >= maxRuntimeMs)
            {
                Fail("max event runtime reached");
                return;
            }
        }

        if (Config.Settings.BlackboxReadyTimeoutSeconds > 0 && State.CurrentState == DeutschZConvoyZConstants.STATE_BLACKBOX_READY && State.BlackboxReadyAt > 0)
        {
            int readyTimeoutMs = Config.Settings.BlackboxReadyTimeoutSeconds * 1000;
            if (now - State.BlackboxReadyAt >= readyTimeoutMs)
            {
                Fail("blackbox ready timeout");
                return;
            }
        }
    }

    void OnEventCleanupFinished(string eventId, string reason)
    {
        EventLock = 0;
        GetGame().GetCallQueue(CALL_CATEGORY_SYSTEM).Remove(this.Tick);
        if (!Config || !Config.Settings) return;
        if (Config.Settings.EnableConvoyZEvent == 0) return;
        if (Config.Settings.RestartEventAfterCleanup == 0) return;
        if (Config.Settings.MaxEventsPerRestart > 0 && EventsStartedThisRestart >= Config.Settings.MaxEventsPerRestart) return;
        ScheduleAutoStart(0, "cleanup finished");
    }

    void SendStatusNotification(bool force = false)
    {
        if (!GetGame() || !GetGame().IsServer()) return;
        if (!Config || !Config.Settings || !State) return;
        if (Config.Settings.EnableStatusNotifications == 0) return;

        int now = GetGame().GetTime();
        int interval = Config.Settings.StatusNotifyIntervalSeconds;
        if (interval < 3) interval = 3;

        if (!force && State.LastStatusNotifyAt > 0)
        {
            if (now - State.LastStatusNotifyAt < interval * 1000) return;
        }

        State.LastStatusNotifyAt = now;

        string status = BuildStatusText();
        if (status == "") return;

        SendStatusToNearbyPlayers(status);
        SyncStatusNow();
    }


    string BuildStatusText()
    {
        if (!State) return "";

        if (State.CurrentState == DeutschZConvoyZConstants.STATE_SECURE_AREA)
        {
            return "Convoy sichern: " + State.CurrentKills.ToString() + "/" + State.RequiredKills.ToString() + " AI eliminiert";
        }

        if (State.CurrentState == DeutschZConvoyZConstants.STATE_BLACKBOX_READY)
        {
            return "Blackbox bereit: Hack starten";
        }

        if (State.CurrentState == DeutschZConvoyZConstants.STATE_HACKING)
        {
            return "Blackbox entschluesseln: " + State.HackProgressSeconds.ToString() + "/" + GetHackDuration().ToString() + " Sekunden";
        }

        if (State.CurrentState == DeutschZConvoyZConstants.STATE_DELIVERY_ACTIVE)
        {
            return "Blackbox tragen: bringe sie zum Kontaktmann";
        }

        if (State.CurrentState == DeutschZConvoyZConstants.STATE_DELIVERED)
        {
            return "Blackbox abgegeben: Operation-Spur erhalten";
        }

        if (State.CurrentState == DeutschZConvoyZConstants.STATE_REWARD_UNLOCKED)
        {
            return "Blackbox entschluesselt: Reward freigegeben";
        }

        if (State.CurrentState == DeutschZConvoyZConstants.STATE_FAILED)
        {
            return "Convoy Event fehlgeschlagen";
        }

        return "DeutschZ ConvoyZ aktiv";
    }


    void SendStatusToNearbyPlayers(string text)
    {
        vector center = GetEventPosition();
        float radius = Config.Settings.StatusSyncRadius;
        if (radius <= 0) radius = 1000.0;

        array<Man> players = new array<Man>;
        GetGame().GetPlayers(players);

        int sent = 0;
        foreach (Man man: players)
        {
            PlayerBase pb = PlayerBase.Cast(man);
            if (!pb || !pb.GetIdentity()) continue;

            float dist = vector.Distance(pb.GetPosition(), center);
            if (dist > radius) continue;

            Param1<string> data = new Param1<string>(text);
            GetGame().RPCSingleParam(pb, ERPCs.RPC_USER_ACTION_MESSAGE, data, true, pb.GetIdentity());
            sent++;
        }

        Print("[DeutschZ_ConvoyZ] Status sent to " + sent.ToString() + " nearby players: " + text);
    }


    int GetHackDuration()
    {
        if (Config && Config.EventData && Config.EventData.HackDurationSeconds > 0) return Config.EventData.HackDurationSeconds;
        if (Config && Config.Settings) return Config.Settings.HackDurationSeconds;
        return 120;
    }

    vector GetEventPosition()
    {
        if (Config && Config.EventData) return Config.EventData.EventCenter;
        return "0 0 0";
    }

    vector GetBlackboxPosition()
    {
        if (State && State.BlackboxEntity) return State.BlackboxEntity.GetPosition();
        if (Config && Config.EventData && Config.EventData.Blackbox) return Config.EventData.Blackbox.Position;
        return "0 0 0";
    }


    void SyncStatusThrottled()
    {
        if (!State || !Config) return;
        int interval = Config.Settings.StatusBarUpdateIntervalSeconds * 1000;
        if (interval <= 0) interval = 1000;
        if (GetGame().GetTime() - State.LastStatusSyncAt < interval) return;
        SyncStatusNow();
    }

    void SyncStatusNow()
    {
        if (!State || !Config) return;
        State.LastStatusSyncAt = GetGame().GetTime();

        string title = "DeutschZ ConvoyZ";
        string status = BuildStatusText();
        string detail = "";
        int percent = 0;

        if (State.CurrentState == DeutschZConvoyZConstants.STATE_SECURE_AREA)
        {
            int required = State.RequiredKills;
            if (required <= 0) required = 1;
            percent = Math.Clamp((State.CurrentKills * 100) / required, 0, 100);
            detail = "Wachen: " + State.CurrentKills.ToString() + " / " + required.ToString();
        }
        else if (State.CurrentState == DeutschZConvoyZConstants.STATE_BLACKBOX_READY)
        {
            percent = 0;
            detail = "Blackbox am Objekt entschluesseln";
        }
        else if (State.CurrentState == DeutschZConvoyZConstants.STATE_HACKING)
        {
            int duration = GetHackDuration();
            if (duration <= 0) duration = 1;
            percent = Math.Clamp((State.HackProgressSeconds * 100) / duration, 0, 100);
            detail = "Hack: " + State.HackProgressSeconds.ToString() + " / " + duration.ToString() + " Sekunden";
        }
        else if (State.CurrentState == DeutschZConvoyZConstants.STATE_DELIVERY_ACTIVE)
        {
            percent = 80;
            detail = "Zum Kontaktmann bringen: " + Config.Settings.DeliveryNpcName;
        }
        else if (State.CurrentState == DeutschZConvoyZConstants.STATE_DELIVERED)
        {
            percent = 95;
            detail = "OperationDeutschZ-Verbindung vorbereitet";
        }
        else if (State.CurrentState == DeutschZConvoyZConstants.STATE_REWARD_UNLOCKED)
        {
            percent = 100;
            detail = "Reward freigegeben";
        }

        vector center = GetEventPosition();
        float radius = Config.Settings.StatusSyncRadius;
        if (radius <= 0) radius = 1000.0;
        array<Man> players = new array<Man>;
        GetGame().GetPlayers(players);
        foreach (Man man: players)
        {
            PlayerBase pb = PlayerBase.Cast(man);
            if (!pb || !pb.GetIdentity()) continue;
            bool active = true;
            if (vector.Distance(pb.GetPosition(), center) > radius) active = false;
            Param6<string, bool, string, string, int, string> data = new Param6<string, bool, string, string, int, string>(DeutschZConvoyZRPC.TOKEN, active, title, status, percent, detail);
            GetGame().RPCSingleParam(pb, DeutschZConvoyZConstants.RPC_STATUS_SYNC, data, true, pb.GetIdentity());
        }
    }

}

bool DeutschZConvoyZ_AIProviderSpawnForConvoy(string activeEventId, string convoyId, string zoneId, string profileId)
{
    return false;
}

void DeutschZConvoyZ_AIProviderCleanupForEvent(string activeEventId, string reason)
{
}


void DeutschZConvoyZ_RegisterEventMarker(string eventId, vector pos, string name)
{
    if (!GetGame() || !GetGame().IsServer()) return;
    if (eventId == "") return;

    vector markerPos = pos;
    markerPos[1] = GetGame().SurfaceY(markerPos[0], markerPos[2]) + 2.0;

    string markerName = name;
    DeutschZConvoyZManager mgr = g_DeutschZConvoyZManager;
    if (mgr && mgr.Config && mgr.Config.Settings)
    {
        if (mgr.Config.Settings.EventMarkerName != "") markerName = mgr.Config.Settings.EventMarkerName;
    }

    if (markerName == "") markerName = "DeutschZ ConvoyZ Crash";

    bool wants3D = false;
    if (mgr && mgr.Config && mgr.Config.Settings && mgr.Config.Settings.UseEvent3DMarker == 1)
        wants3D = true;

    bool markerOk;
    if (wants3D)
        markerOk = DeutschZConvoyZCoreBridge.CreateEvent3DMarker(eventId, markerName, markerPos);
    else
        markerOk = DeutschZConvoyZCoreBridge.CreateEventMarker(eventId, markerName, markerPos);

    if (markerOk)
    {
        string markerMode = "2D";
        if (wants3D) markerMode = "3D";
        Print("[DeutschZ_ConvoyZ] Core marker registered id=" + eventId + " mode=" + markerMode + " pos=" + markerPos.ToString());
    }
    else
        Print("[DeutschZ_ConvoyZ] Core marker provider unavailable id=" + eventId);
}

void DeutschZConvoyZ_RemoveEventMarker(string eventId)
{
    if (!GetGame() || !GetGame().IsServer()) return;
    if (eventId == "") return;

    if (DeutschZConvoyZCoreBridge.DeleteEventMarker(eventId))
        Print("[DeutschZ_ConvoyZ] Core marker removed id=" + eventId);
}

void DeutschZConvoyZ_RegisterMarker(string eventId, vector pos, string name)
{
    DeutschZConvoyZ_RegisterEventMarker(eventId, pos, name);
}

void DeutschZConvoyZ_RemoveMarker(string eventId)
{
    DeutschZConvoyZ_RemoveEventMarker(eventId);
}

void DeutschZConvoyZ_ExpansionNotify(string title, string text, vector pos)
{
    if (!GetGame() || !GetGame().IsServer()) return;
    Print("[DeutschZ_ConvoyZ] Notify: " + title + " - " + text + " pos=" + pos.ToString());
}
