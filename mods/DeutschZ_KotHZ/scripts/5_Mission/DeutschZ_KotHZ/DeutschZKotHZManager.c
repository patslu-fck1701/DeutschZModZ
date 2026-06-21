/*
DeutschZ ModZ
Eigenstaendige Implementierung fuer DeutschZ.
Autor/Eigentuemer: Patrick Sluzalek / fck1701.
Keine direkte Codeuebernahme aus Drittquellen.
Oeffentliche Quellen werden nur zur Konzept- und API-Verifikation genutzt.
*/

class DeutschZKotHZManager
{
    protected ref DeutschZKotHZConfig m_Config;
    protected ref array<ref DeutschZKotHZLootPool> m_LootPools;
    protected bool m_EventActive;
    protected bool m_EventCompleting;
    protected ref DeutschZKotHZZone m_ActiveZone;
    protected PlayerBase m_CurrentHolder;
    protected int m_CurrentCaptureSeconds;
    protected int m_LastHUDSyncSecond;
    protected int m_LastHUDSyncMs;
    protected ref array<Object> m_SpawnedNPCs;
    protected ref array<Object> m_SpawnedZombies;
    protected ref array<Object> m_RewardCrates;
    protected ref array<Object> m_DeliveryObjects;
    protected ref array<Object> m_StaticDecorations;
    protected ref map<PlayerBase, bool> m_ProgressHUDPlayers;
    protected ref DeutschZKotHZFlagpole m_Flagpole;
    protected Object m_ActiveSmoke;
    protected Particle m_ActiveParticleSmoke;
    protected string m_CurrentSmokeState;
    protected bool m_ZombieWavesStarted;
    protected bool m_DZKZ_Wave25Triggered;
    protected bool m_DZKZ_Wave50Triggered;
    protected bool m_DZKZ_Wave75Triggered;
    protected bool m_DZKZ_BossSpawned;
    protected bool m_DZKZ_BossKilled;
    protected bool m_DZKZ_WaitingBossKillAnnounced;
    protected Object m_DZKZ_BossZombie;
    protected ref map<Object, string> m_DZKZ_EventInfectedRegistry;
    protected ref array<string> m_DZKZ_EventLog;
    protected ref array<Object> m_FogEmitters;
    protected ref array<Object> m_SmokeCannons;
    protected string m_LastAnnounceMessage;
    protected int m_LastAnnounceTimeMs;

    protected string m_DeutschZKotHZMarkerId;

    void DeutschZKotHZManager()
    {
        m_Config = DeutschZKotHZConfigManager.Load();
        m_LootPools = DeutschZKotHZConfigManager.GetLootPools();
        m_EventActive = false;
        m_EventCompleting = false;
        m_CurrentCaptureSeconds = 0;
        m_LastHUDSyncSecond = 0;
        m_LastHUDSyncMs = 0;
        m_SpawnedNPCs = new array<Object>;
        m_SpawnedZombies = new array<Object>;
        m_RewardCrates = new array<Object>;
        m_DeliveryObjects = new array<Object>;
        m_StaticDecorations = new array<Object>;
        m_FogEmitters = new array<Object>;
        m_SmokeCannons = new array<Object>;
        m_LastAnnounceMessage = "";
        m_LastAnnounceTimeMs = 0;
        m_ProgressHUDPlayers = new map<PlayerBase, bool>;
        m_Flagpole = null;
        m_ActiveSmoke = null;
        m_ActiveParticleSmoke = null;
        m_CurrentSmokeState = "";
        m_ZombieWavesStarted = false;
        m_DZKZ_Wave25Triggered = false;
        m_DZKZ_Wave50Triggered = false;
        m_DZKZ_Wave75Triggered = false;
        m_DZKZ_BossSpawned = false;
        m_DZKZ_BossKilled = false;
        m_DZKZ_WaitingBossKillAnnounced = false;
        m_DZKZ_BossZombie = null;
        m_DZKZ_EventInfectedRegistry = new map<Object, string>;
        m_DZKZ_EventLog = new array<string>;
        m_DeutschZKotHZMarkerId = "";
    }

    void StartScheduler()
    {
        Print("[DeutschZ_KotHZ] Owned by Patrick Sluzalek / fck1701 / DeutschZ.");
        if (!m_Config || !m_Config.EnableKOTH)
        {
            Print("[DeutschZ_KotHZ] KOTH disabled.");
            return;
        }

        CleanupPersistedKOTHEventObjects();
        // DeutschZ KotHZ second startup pass after world objects have settled.
        GetGame().GetCallQueue(CALL_CATEGORY_SYSTEM).CallLater(CleanupPersistedKOTHEventObjects, 30000, false);
        ScheduleNextEvent();
    }

    protected void CleanupPersistedKOTHEventObjects()
    {
        if (!m_Config || !m_Config.Zones)
            return;

        Print("[DeutschZ_KotHZ] Startup cleanup pass started.");
        int removedTotal = 0;
        foreach (DeutschZKotHZZone zone : m_Config.Zones)
        {
            removedTotal += CleanupZoneKOTHObjects(zone, "startup");
        }
        Print("[DeutschZ_KotHZ] Startup cleanup pass finished. Removed runtime objects=" + removedTotal.ToString());
    }

    protected int CleanupZoneKOTHObjects(DeutschZKotHZZone zone, string reason)
    {
        if (!zone)
            return 0;

        vector pos = zone.FlagpolePosition;
        if (pos == vector.Zero)
            pos = zone.Position;
        if (pos == vector.Zero)
            return 0;

        pos[1] = GetGame().SurfaceY(pos[0], pos[2]);
        float cleanupRadius = Math.Max(zone.Radius + 75.0, 150.0);

        ref array<Object> objects = new array<Object>;
        ref array<CargoBase> cargos = new array<CargoBase>;
        GetGame().GetObjectsAtPosition(pos, cleanupRadius, objects, cargos);

        int removed = 0;
        foreach (Object obj : objects)
        {
            if (!obj)
                continue;

            string objType = obj.GetType();
            if (IsKOTHCleanupObjectType(objType))
            {
                GetGame().ObjectDelete(obj);
                removed++;
            }
        }

        return removed;
    }

    protected bool IsKOTHCleanupObjectType(string objType)
    {
        if (objType == "DeutschZKotHZ_RuntimeFlagpole")
            return true;
        if (objType == "DeutschZKotHZ_EventFlagpole")
            return true;
        if (objType == "DeutschZKotHZ_LegacyFlagpoleCleanupAlias")
            return true;
        if (objType == "DeutschZKotHZ_RemovedLegacyFlagpole")
            return true;
        if (objType == "DeutschZKotHZ_RemovedLegacyFogEmitter")
            return true;
        if (objType == "DeutschZKotHZ_Flag")
            return true;
        if (objType == "M18SmokeGrenade_Green")
            return true;
        if (objType == "M18SmokeGrenade_Yellow")
            return true;
        if (objType == "M18SmokeGrenade_Red")
            return true;
        if (objType == "DeutschZKotHZ_RuntimeFogEmitter")
            return true;
        if (objType == "FireworksLauncher")
            return true;
        if (m_Config && objType == m_Config.DeliveryHelicopterClassName)
            return true;
        // Do not delete reward crates during startup/pre-start orphan cleanup.
        // Reward crates have their own lifetime/despawn handling.

        return false;
    }

    protected void ScheduleNextEvent()
    {
        int minDelay = Math.Max(1, m_Config.MinStartDelayMinutes);
        int maxDelay = Math.Max(minDelay, m_Config.MaxStartDelayMinutes);
        int delayMinutes = Math.RandomIntInclusive(minDelay, maxDelay);
        int delayMs = delayMinutes * 60 * 1000;

        GetGame().GetCallQueue(CALL_CATEGORY_SYSTEM).Remove(StartEvent);
        Print("[DeutschZ_KotHZ] Next event in " + delayMinutes + " minutes.");
        GetGame().GetCallQueue(CALL_CATEGORY_SYSTEM).CallLater(StartEvent, delayMs, false);
    }

    void StartEvent()
    {
        if (m_EventActive)
            return;

        if (!HasEnoughPlayers())
        {
            Print("[DeutschZ_KotHZ] Not enough players online. Rescheduling.");
            ScheduleNextEvent();
            return;
        }

        if (!m_Config.Zones || m_Config.Zones.Count() == 0)
        {
            Print("[DeutschZ_KotHZ] No zones configured. Rescheduling.");
            ScheduleNextEvent();
            return;
        }

        m_ActiveZone = m_Config.Zones.GetRandomElement();
        ApplyGlobalSpawnSettingsIfNeeded();
        m_EventActive = true;
        m_EventCompleting = false;
        m_CurrentHolder = null;
        m_CurrentCaptureSeconds = 0;
        m_LastHUDSyncSecond = 0;
        m_LastHUDSyncMs = 0;
        m_CurrentSmokeState = "";
        m_ZombieWavesStarted = false;
        ResetInfectedSiegeRuntime();
        CancelZombieWaveSchedule();
        if (m_ProgressHUDPlayers)
            m_ProgressHUDPlayers.Clear();

        // DeutschZ KotHZ pre-start cleanup: remove previous event flags/smoke/fireworks near the selected zone before spawning fresh event objects.
        CleanupZoneKOTHObjects(m_ActiveZone, "pre-start");
        SpawnFlagpole();
        SpawnZoneDecorations();
        CreateAllMapMarkers();
        CleanupSmoke();
        SetStatusSmoke("Green");
        MaybeStartFogHazard("Ready");
        TryPlayEventMusic("Ready");
        Announce("KOTH ready: " + m_ActiveZone.ZoneName + ". Event startet gleich!");
        SendHUDToAll(true, m_ActiveZone.ZoneName, 0, 0, m_ActiveZone.CaptureTimeSeconds, 0, "KOTH ready");
        GetGame().GetCallQueue(CALL_CATEGORY_SYSTEM).CallLater(BeginActiveEvent, 10000, false);
    }

    protected void BeginActiveEvent()
    {
        if (!m_EventActive || !m_ActiveZone || m_EventCompleting)
            return;

        SetStatusSmoke("Green");
        MaybeStartFogHazard("Ready");
        // v1.0.25: zombie/infected waves are started on first player entry, DeutschZ wave-system style.
        TryPlayEventMusic("Start");
        Announce("KOTH gestartet: " + m_ActiveZone.ZoneName + ". Erobere und halte die Zone!");
        SpawnNearFlagTestZombies();
        SendHUDToAll(true, m_ActiveZone.ZoneName, 0, 0, m_ActiveZone.CaptureTimeSeconds, CountPlayersInZone(), "KOTH ready");
        GetGame().GetCallQueue(CALL_CATEGORY_SYSTEM).CallLater(TickEvent, 1000, true);
    }

    protected void ApplyGlobalSpawnSettingsIfNeeded()
    {
        if (!m_Config || !m_ActiveZone || m_ActiveZone.UseZoneSpawnSettings)
            return;

        if (m_Config.NPC)
        {
            m_ActiveZone.EnableOptionalNPC = 0;
            m_ActiveZone.NPCAmount = 0;
            m_ActiveZone.NPCSpawnRadius = m_Config.NPC.NPCSpawnRadius;
            m_ActiveZone.NPCSpawnHeightOffset = m_Config.NPC.NPCSpawnHeightOffset;
            m_ActiveZone.NPCDespawnOnEventEnd = m_Config.NPC.NPCDespawnOnEventEnd;
            m_ActiveZone.ValidateNPCClassBeforeSpawn = m_Config.NPC.ValidateClassBeforeSpawn;
            if (m_ActiveZone.NPCClassNames)
                m_ActiveZone.NPCClassNames.Clear();
            if (m_ActiveZone.NPCLoadoutClassNames)
                m_ActiveZone.NPCLoadoutClassNames.Clear();
        }

        if (m_Config.Zombies)
        {
            m_ActiveZone.EnableZombieSpawns = m_Config.Zombies.EnableZombieSpawns;
            m_ActiveZone.InitialZombieSpawnCount = m_Config.Zombies.InitialZombieSpawnCount;
            m_ActiveZone.ZombieWaveCount = m_Config.Zombies.ZombieWaveCount;
            m_ActiveZone.ZombiesPerWave = m_Config.Zombies.ZombiesPerWave;
            m_ActiveZone.MaxTotalZombies = m_Config.Zombies.MaxTotalZombies;
            m_ActiveZone.SecondsBetweenZombieWaves = m_Config.Zombies.SecondsBetweenZombieWaves;
            m_ActiveZone.ZombieSpawnMinDistance = m_Config.Zombies.ZombieSpawnMinDistance;
            m_ActiveZone.ZombieSpawnMaxDistance = m_Config.Zombies.ZombieSpawnMaxDistance;
            m_ActiveZone.ValidateZombieClassBeforeSpawn = m_Config.Zombies.ValidateClassBeforeSpawn;
            m_ActiveZone.DespawnZombiesOnEventEnd = m_Config.Zombies.DespawnZombiesOnEventEnd;
            m_ActiveZone.ZombieTypes = m_Config.Zombies.ZombieTypes;
        }
    }

    protected void TickEvent()
    {
        if (!m_EventActive || m_EventCompleting || !m_ActiveZone)
            return;

        int playersInZone = CountPlayersInZone();
        PlayerBase holder = FindSingleHolderInZone(playersInZone);
        string state = "Neutral";

        if (playersInZone > 0 && !m_ZombieWavesStarted)
            StartZombieWaves();

        if (!holder)
        {
            if (playersInZone > 0)
            {
                // Multiple players / contested presence: KOTH is active, but no single holder can capture.
                state = "KOTH in progress";
                SetStatusSmoke("Yellow");
                MaybeStartFogHazard("Progress");
            }
            else
            {
                state = "KOTH ready";
                m_CurrentHolder = null;
                m_CurrentCaptureSeconds = 0;
                SetStatusSmoke("Green");
            }

            SyncHUD(playersInZone, state);
            return;
        }

        if (holder != m_CurrentHolder)
        {
            m_CurrentHolder = holder;
            m_CurrentCaptureSeconds = 0;
            Announce(GetPlayerName(holder) + " kontrolliert jetzt KOTH: " + m_ActiveZone.ZoneName);
        }

        state = "KOTH in progress";
        SetStatusSmoke("Yellow");
        MaybeStartFogHazard("Progress");
        m_CurrentCaptureSeconds++;
        TriggerInfectedSiegeByCapturePercent();
        SyncHUD(playersInZone, state);

        if (m_Config.DebugMode && (m_CurrentCaptureSeconds % 60 == 0))
        {
            Print("[DeutschZ_KotHZ] Capture progress: " + m_CurrentCaptureSeconds + "/" + m_ActiveZone.CaptureTimeSeconds + " players=" + playersInZone);
        }

        if (m_CurrentCaptureSeconds >= m_ActiveZone.CaptureTimeSeconds)
        {
            if (m_DZKZ_BossSpawned && !m_DZKZ_BossKilled)
            {
                if (!m_DZKZ_WaitingBossKillAnnounced)
                {
                    m_DZKZ_WaitingBossKillAnnounced = true;
                    Announce("KotHZ Infected Siege: Zone gesichert, aber der Mummy-Boss lebt noch!");
                    DZKZ_Log("RewardBlocked", "Boss still alive");
                }
                m_CurrentCaptureSeconds = m_ActiveZone.CaptureTimeSeconds;
                SyncHUD(playersInZone, "Boss lebt");
                return;
            }

            FinishEvent(holder);
        }
    }

    bool ReloadJsonConfigs(PlayerIdentity adminIdentity, out string message)
    {
        string adminName = "server";
        string adminId = "";
        if (adminIdentity)
        {
            adminName = adminIdentity.GetName();
            adminId = adminIdentity.GetPlainId();
        }

        Print("[DeutschZ_KotHZ] JSON reload requested by " + adminName + " (" + adminId + ")");

        ref DeutschZKotHZConfig newConfig = DeutschZKotHZConfigManager.Reload();
        if (!newConfig)
        {
            message = "KOTH JSON reload failed. Check RPT.";
            return false;
        }

        m_Config = newConfig;
        m_LootPools = DeutschZKotHZConfigManager.GetLootPools();

        if (m_EventActive && m_ActiveZone)
        {
            ApplyGlobalSpawnSettingsIfNeeded();
            message = "KOTH JSON reloaded. Active event kept running; zone/loot changes apply from next event.";
            Print("[DeutschZ_KotHZ] JSON reload complete while event is active. Active zone kept: " + m_ActiveZone.ZoneName);
            return true;
        }

        GetGame().GetCallQueue(CALL_CATEGORY_SYSTEM).Remove(StartEvent);
        ScheduleNextEvent();
        message = "KOTH JSON reloaded and next event rescheduled.";
        Print("[DeutschZ_KotHZ] JSON reload complete. Scheduler refreshed.");
        return true;
    }

    string GetAdminStatusMessage()
    {
        if (!m_Config)
            return "KOTH config not loaded.";

        string message = "KOTH status: ";
        if (!m_EventActive)
        {
            message += "inactive";
            message += " / enabled=" + m_Config.EnableKOTH.ToString();
            if (m_Config.Zones)
                message += " / zones=" + m_Config.Zones.Count().ToString();
            return message;
        }

        string zoneName = "unknown";
        int playersInZone = 0;
        int captureSeconds = m_CurrentCaptureSeconds;
        int totalSeconds = 0;
        if (m_ActiveZone)
        {
            zoneName = m_ActiveZone.ZoneName;
            totalSeconds = m_ActiveZone.CaptureTimeSeconds;
            playersInZone = CountPlayersInZone();
        }

        int percent = 0;
        if (totalSeconds > 0)
            percent = Math.Clamp((captureSeconds * 100) / totalSeconds, 0, 100);

        message += "active";
        message += " / zone=" + zoneName;
        message += " / players=" + playersInZone.ToString();
        message += " / progress=" + percent.ToString() + "%";
        message += " / smoke=" + m_CurrentSmokeState;
        return message;
    }

    bool AdminForceStartEvent(PlayerIdentity adminIdentity, out string message)
    {
        if (!m_Config)
        {
            message = "KOTH force start failed: config not loaded.";
            return false;
        }

        if (!m_Config.EnableKOTH)
        {
            message = "KOTH force start failed: KOTH disabled in config.";
            return false;
        }

        if (m_EventActive)
        {
            message = "KOTH force start ignored: event already active.";
            return false;
        }

        int oldMinPlayers = m_Config.MinPlayersToStart;
        m_Config.MinPlayersToStart = 0;
        GetGame().GetCallQueue(CALL_CATEGORY_SYSTEM).Remove(StartEvent);
        StartEvent();
        m_Config.MinPlayersToStart = oldMinPlayers;

        if (m_EventActive)
        {
            string adminName = "server";
            if (adminIdentity)
                adminName = adminIdentity.GetName();
            message = "KOTH force start executed by " + adminName + ".";
            return true;
        }

        message = "KOTH force start requested but no event became active. Check zones/config.";
        return false;
    }

    bool AdminForceStopEvent(PlayerIdentity adminIdentity, out string message)
    {
        if (!m_EventActive && !m_EventCompleting)
        {
            message = "KOTH force stop ignored: no active event.";
            return false;
        }

        string adminName = "server";
        if (adminIdentity)
            adminName = adminIdentity.GetName();

        GetGame().GetCallQueue(CALL_CATEGORY_SYSTEM).Remove(StartEvent);
        GetGame().GetCallQueue(CALL_CATEGORY_SYSTEM).Remove(TickEvent);
        GetGame().GetCallQueue(CALL_CATEGORY_SYSTEM).Remove(BeginActiveEvent);
        GetGame().GetCallQueue(CALL_CATEGORY_SYSTEM).Remove(StopEvent);
        StopEvent();
        message = "KOTH force stop executed by " + adminName + ".";
        return true;
    }

    protected void TryPlayEventMusic(string phase)
    {
        // FIX21 Safe-Boot: KOTH music is intentionally disabled.
        // Keep this as a no-op so config/profile leftovers cannot trigger client sound sync.
        return;
    }

    protected int CountPlayersInZone()
    {
        int count = 0;
        ref array<Man> players = new array<Man>;
        GetGame().GetPlayers(players);

        foreach (Man man : players)
        {
            PlayerBase player = PlayerBase.Cast(man);
            if (!player || !player.IsAlive())
                continue;

            if (vector.Distance(player.GetPosition(), m_ActiveZone.Position) <= m_ActiveZone.Radius)
                count++;
        }

        return count;
    }

    protected PlayerBase FindSingleHolderInZone(int playersInZone)
    {
        if (playersInZone != 1)
            return null;

        ref array<Man> players = new array<Man>;
        GetGame().GetPlayers(players);

        foreach (Man man : players)
        {
            PlayerBase player = PlayerBase.Cast(man);
            if (!player || !player.IsAlive())
                continue;

            if (vector.Distance(player.GetPosition(), m_ActiveZone.Position) <= m_ActiveZone.Radius)
                return player;
        }

        return null;
    }

    protected bool HasEnoughPlayers()
    {
        ref array<Man> players = new array<Man>;
        GetGame().GetPlayers(players);
        return players.Count() >= m_Config.MinPlayersToStart;
    }

    protected void FinishEvent(PlayerBase winner)
    {
        if (!winner || m_EventCompleting)
            return;

        m_EventCompleting = true;
        GetGame().GetCallQueue(CALL_CATEGORY_SYSTEM).Remove(TickEvent);
        GetGame().GetCallQueue(CALL_CATEGORY_SYSTEM).Remove(BeginActiveEvent);
        GiveRewards(winner);
        Announce("KOTH gewonnen von " + GetPlayerName(winner) + " bei " + m_ActiveZone.ZoneName + "!");
        DoWinFireworks();
        // v1.0.30: Keep mast and red captured smoke visible longer after capture.
        // Cleanup happens together with StopEvent after Smoke.CompletedSmokeSeconds.
        SetStatusSmoke("Red");
        MaybeStartFogHazard("Completed");
        TryPlayEventMusic("Captured");
        SendHUDToAll(true, m_ActiveZone.ZoneName, 100, m_ActiveZone.CaptureTimeSeconds, m_ActiveZone.CaptureTimeSeconds, CountPlayersInZone(), "KOTH captured");

        int completedSmokeMs = 180000;
        if (m_Config && m_Config.Smoke)
            completedSmokeMs = (int)(Math.Max(1.0, m_Config.Smoke.CompletedSmokeSeconds) * 1000);

        GetGame().GetCallQueue(CALL_CATEGORY_SYSTEM).CallLater(StopEvent, completedSmokeMs, false);
    }

    protected void StopEvent()
    {
        GetGame().GetCallQueue(CALL_CATEGORY_SYSTEM).Remove(TickEvent);
        GetGame().GetCallQueue(CALL_CATEGORY_SYSTEM).Remove(BeginActiveEvent);
        CancelZombieWaveSchedule();
        SendHUDToAll(false, "", 0, 0, 0, 0, "Beendet");
        CleanupOptionalNPCs();
        CleanupZombies();
        CleanupRewardCrates(true);
        CleanupDeliveryObjects();
        CleanupZoneDecorations();
        CleanupSmoke();
        CleanupFogHazard();
        DeleteAllMapMarkers();
        CleanupFlagpole();
        m_EventActive = false;
        m_EventCompleting = false;
        m_ActiveZone = null;
        m_CurrentHolder = null;
        m_CurrentCaptureSeconds = 0;
        m_ZombieWavesStarted = false;
        ResetInfectedSiegeRuntime();
        if (m_ProgressHUDPlayers)
            m_ProgressHUDPlayers.Clear();
        ScheduleNextEvent();
    }


    protected void SpawnZoneDecorations()
    {
        if (!m_ActiveZone || !m_ActiveZone.EnableCrashedHeliDecoration)
            return;

        string decoClass = m_ActiveZone.CrashedHeliClassName;
        if (decoClass == "")
            decoClass = "Wreck_Mi8";

        if (!GetGame().ConfigIsExisting("CfgVehicles " + decoClass))
        {
            Print("[DeutschZ_KotHZ] Decoration class not found, skipping: " + decoClass);
            return;
        }

        vector basePos = m_ActiveZone.Position;
        vector offset = m_ActiveZone.CrashedHeliOffset;
        vector pos = basePos;
        pos[0] = pos[0] + offset[0];
        pos[2] = pos[2] + offset[2];
        pos[1] = GetGame().SurfaceY(pos[0], pos[2]) + offset[1];

        Object deco = GetGame().CreateObjectEx(decoClass, pos, ECE_PLACE_ON_SURFACE | ECE_CREATEPHYSICS | ECE_SETUP, RF_DEFAULT);
        if (!deco)
            deco = GetGame().CreateObject(decoClass, pos, false, true, true);

        if (!deco)
        {
            Print("[DeutschZ_KotHZ] Decoration spawn failed: " + decoClass + " at " + pos.ToString());
            return;
        }

        deco.SetOrientation(m_ActiveZone.CrashedHeliOrientation);
        EntityAI decoEntity = EntityAI.Cast(deco);
        if (decoEntity)
            decoEntity.PlaceOnSurface();

        if (m_StaticDecorations)
            m_StaticDecorations.Insert(deco);

        Print("[DeutschZ_KotHZ] Static decoration spawned: " + decoClass + " at " + deco.GetPosition().ToString());
    }

    protected void CleanupZoneDecorations()
    {
        if (!m_StaticDecorations)
            return;

        foreach (Object deco : m_StaticDecorations)
        {
            if (deco)
                GetGame().ObjectDelete(deco);
        }

        m_StaticDecorations.Clear();
    }

    protected int GetRemainingZombieSlots()
    {
        int maxTotal = 18;
        if (m_ActiveZone && m_ActiveZone.MaxTotalZombies > 0)
            maxTotal = m_ActiveZone.MaxTotalZombies;

        int current = 0;
        if (m_SpawnedZombies)
            current = m_SpawnedZombies.Count();

        int remaining = maxTotal - current;
        if (remaining < 0)
            remaining = 0;

        return remaining;
    }

    protected void DoWinFireworks()
    {
        if (!m_Config || !m_Config.EnableWinFireworks)
            return;

        string fireworkClass = m_Config.WinFireworkClassName;
        if (fireworkClass == "")
            fireworkClass = "FireworksLauncher";

        if (!GetGame().ConfigIsExisting("CfgVehicles " + fireworkClass))
        {
            Print("[DeutschZ_KotHZ] Firework class not found, skipping fireworks: " + fireworkClass);
            return;
        }

        int count = Math.Max(1, m_Config.WinFireworkCount);
        float radius = Math.Max(0.0, m_Config.WinFireworkRadius);
        vector basePos = GetFlagpoleBasePosition();
        if (basePos == vector.Zero && m_ActiveZone)
            basePos = m_ActiveZone.Position;

        for (int i = 0; i < count; i++)
        {
            vector pos = basePos;
            if (radius > 0.0)
            {
                float angle = Math.RandomFloatInclusive(0.0, 6.283185);
                float dist = Math.RandomFloatInclusive(0.0, radius);
                pos[0] = pos[0] + Math.Cos(angle) * dist;
                pos[2] = pos[2] + Math.Sin(angle) * dist;
            }
            pos[1] = GetGame().SurfaceY(pos[0], pos[2]) + Math.Max(0.0, m_Config.WinFireworkHeightOffset);

            FireworksLauncher firework = FireworksLauncher.Cast(GetGame().CreateObjectEx(fireworkClass, pos, ECE_PLACE_ON_SURFACE | ECE_CREATEPHYSICS, RF_DEFAULT));
            if (!firework)
            {
                Print("[DeutschZ_KotHZ] Firework spawn failed: " + fireworkClass + " at " + pos.ToString());
                continue;
            }

            firework.SetOrientation(Vector(Math.RandomFloatInclusive(0.0, 360.0), 0.0, 0.0));
            EntityAI.Cast(firework).OnIgnitedThis(null);
            firework.SetSynchDirty();
            firework.SetLifetime(120);
            Print("[DeutschZ_KotHZ] Win firework ignited: " + fireworkClass + " at " + pos.ToString());
        }
    }

    protected void GiveRewards(PlayerBase player)
    {
        if (!player || !m_Config)
            return;

        DeutschZKotHZLootPool pool = GetActiveLootPool();
        ref array<ref DeutschZKotHZReward> rewards = GetActiveRewardList();
        if (!rewards)
            rewards = new array<ref DeutschZKotHZReward>;

        if (!pool)
        {
            pool = new DeutschZKotHZLootPool();
            pool.PoolName = "RuntimeDefault";
            pool.RewardMode = 1;
            pool.CrateClassName = "DeutschZKotHZ_RewardCrate";
            pool.CrateSpawnAtFlagpole = 1;
            pool.CrateSpawnDistanceFromFlagpole = 6.0;
            pool.CrateLifetimeSeconds = 1800;
            pool.DeleteCrateOnEventEnd = 0;
            Print("[DeutschZ_KotHZ] No active reward pool found, using runtime DeutschZKotHZ_RewardCrate fallback.");
        }

        // DeutschZ design: reward should be a visible crate, not only direct inventory payout.
        pool.RewardMode = 1;

        if (pool && pool.RewardMode == 1)
        {
            SpawnRewardCrate(player, pool, rewards);
            return;
        }

        GiveRewardsDirect(player, rewards);
    }

    protected void GiveRewardsDirect(PlayerBase player, array<ref DeutschZKotHZReward> rewards)
    {
        if (!player || !rewards)
            return;

        foreach (DeutschZKotHZReward reward : rewards)
        {
            if (!reward || reward.ClassName == "")
                continue;

            if (!IsRewardClassConfigured(reward.ClassName))
            {
                Print("[DeutschZ_KotHZ] Direct reward classname not found in config, skipped: " + reward.ClassName);
                continue;
            }

            int count = 1;
            if (!HasNestedRewardData(reward) && reward.Quantity > 1)
                count = reward.Quantity;
            if (reward.MaxSpawnable > 0 && count > reward.MaxSpawnable)
                count = reward.MaxSpawnable;

            for (int i = 0; i < count; i++)
                player.GetInventory().CreateInInventory(reward.ClassName);
        }
    }

    protected void SpawnRewardCrate(PlayerBase winner, DeutschZKotHZLootPool pool, array<ref DeutschZKotHZReward> rewards)
    {
        if (!winner || !pool || !rewards)
            return;

        string crateClassName = pool.CrateClassName;
        if (crateClassName == "" || crateClassName == "SeaChest" || crateClassName == "WoodenCrate" || crateClassName == "DeutschZKotHZ_DropCrate")
            crateClassName = "DeutschZKotHZ_RewardCrate";

        vector cratePos = GetRewardCratePosition(winner, pool);
        cratePos[1] = GetGame().SurfaceY(cratePos[0], cratePos[2]) + 0.35;

        bool heliDelivery = ShouldUseHelicopterRewardDelivery();
        vector landingPos = cratePos;
        if (heliDelivery)
        {
            SpawnRewardDeliveryHelicopter(landingPos);
            float dropDelay = Math.Max(0.0, m_Config.DeliveryCrateDropDelaySeconds);
            if (dropDelay > 0.0)
                GetGame().GetCallQueue(CALL_CATEGORY_SYSTEM).CallLater(AnnounceRewardDrop, (int)(dropDelay * 1000), false, landingPos);

            cratePos[1] = GetGame().SurfaceY(cratePos[0], cratePos[2]) + Math.Max(1.0, m_Config.DeliveryCrateDropHeight);
        }

        Object crateObj = SpawnRewardCrateObject(crateClassName, cratePos, heliDelivery);
        if (!crateObj && crateClassName != "DeutschZKotHZ_RewardCrate")
        {
            Print("[DeutschZ_KotHZ] Configured reward crate failed, trying DeutschZKotHZ_RewardCrate fallback: " + crateClassName);
            crateClassName = "DeutschZKotHZ_RewardCrate";
            crateObj = SpawnRewardCrateObject(crateClassName, cratePos, heliDelivery);
        }
        if (!crateObj)
        {
            // Ready-to-go reward rule: do not spawn vanilla SeaChest/WoodenCrate as productive KOTH reward containers.
            // This avoids deleting or confusing player-owned vanilla containers during cleanup.
            Print("[DeutschZ_KotHZ] Reward crate object spawn failed. Direct reward fallback only, no vanilla container fallback.");
            GiveRewardsDirect(winner, rewards);
            return;
        }

        EntityAI crate = EntityAI.Cast(crateObj);
        if (!crate)
        {
            Print("[DeutschZ_KotHZ] Reward crate object is not EntityAI: " + crateClassName + ". Falling back to direct player reward.");
            GiveRewardsDirect(winner, rewards);
            return;
        }

        crate.SetPosition(cratePos);
        if (!heliDelivery)
            crate.PlaceOnSurface();

        int confirmMs = 1500;
        if (heliDelivery)
            confirmMs = (int)(Math.Max(3.0, m_Config.DeliveryCrateLandingConfirmSeconds) * 1000);
        GetGame().GetCallQueue(CALL_CATEGORY_SYSTEM).CallLater(ConfirmRewardCrateVisible, confirmMs, false, crate);
        if (m_ActiveZone && m_ActiveZone.RewardCrateOrientation != vector.Zero)
            crate.SetOrientation(m_ActiveZone.RewardCrateOrientation);
        int effectiveCrateLifetime = GetEffectiveRewardCrateLifetimeSeconds(pool);
        crate.SetLifetime(effectiveCrateLifetime);
        Print("[DeutschZ_KotHZ] Reward crate config target capacity: 500 slots / class=" + crateClassName + " / lifetime=" + effectiveCrateLifetime.ToString() + "s");

        if (heliDelivery)
            Print("[DeutschZ_KotHZ] Reward crate helicopter drop spawned at " + crate.GetPosition().ToString() + " landingTarget=" + landingPos.ToString() + " class=" + crateClassName + " rewardCount=" + rewards.Count().ToString());
        else
            Print("[DeutschZ_KotHZ] Reward crate spawned at " + crate.GetPosition().ToString() + " class=" + crateClassName + " rewardCount=" + rewards.Count().ToString());
        m_RewardCrates.Insert(crate);

        int rewardInserted = 0;
        int rewardFailed = 0;
        foreach (DeutschZKotHZReward reward : rewards)
        {
            int spawnedCount = SpawnRewardEntry(crate, crate, reward, false);
            if (spawnedCount > 0)
                rewardInserted = rewardInserted + spawnedCount;
            else if (reward && reward.ClassName != "")
                rewardFailed++;
        }
        Print("[DeutschZ_KotHZ] Reward fill completed: inserted=" + rewardInserted.ToString() + " failed=" + rewardFailed.ToString() + " crate=" + crate.GetType());

        if (heliDelivery)
            Announce("KotH Reward-Crate wird per Heli geliefert: " + m_ActiveZone.ZoneName + ".");
        else
            Announce("KotH Reward-Crate gespawnt: " + crateClassName + " bei " + m_ActiveZone.ZoneName + ".");

        if (effectiveCrateLifetime > 0)
        {
            int warningSeconds = 0;
            if (m_Config && m_Config.EnableRewardCrateDespawnWarning)
                warningSeconds = m_Config.RewardCrateDespawnWarningSeconds;

            if (warningSeconds > 0 && warningSeconds < effectiveCrateLifetime)
            {
                int warningMs = (effectiveCrateLifetime - warningSeconds) * 1000;
                string warningZoneName = "KOTH";
                if (m_ActiveZone)
                    warningZoneName = m_ActiveZone.ZoneName;
                GetGame().GetCallQueue(CALL_CATEGORY_SYSTEM).CallLater(AnnounceRewardCrateDespawnWarning, warningMs, false, crate, warningZoneName, warningSeconds);
            }

            int deleteMs = effectiveCrateLifetime * 1000;
            GetGame().GetCallQueue(CALL_CATEGORY_SYSTEM).CallLater(DeleteRewardCrate, deleteMs, false, crate);
        }
    }

    protected int SpawnRewardEntry(EntityAI parent, EntityAI crate, DeutschZKotHZReward reward, bool asAttachment)
    {
        if (!reward)
            return 0;

        if (!ShouldSpawnRewardEntry(reward))
            return 0;

        int spawnCount = GetRewardEntrySpawnCount(reward);
        int successCount = 0;

        for (int i = 0; i < spawnCount; i++)
        {
            EntityAI item = CreateRewardEntity(parent, crate, reward, asAttachment);
            if (!item)
            {
                Print("[DeutschZ_KotHZ] Reward item could not be inserted into crate, no ground fallback: " + reward.ClassName);
                continue;
            }

            successCount++;
            SpawnRewardChildren(item, crate, reward);
        }

        return successCount;
    }

    protected bool ShouldSpawnRewardEntry(DeutschZKotHZReward reward)
    {
        if (!reward)
            return false;

        float chance = reward.SpawnChance;
        if (chance <= 0.0)
            return false;
        if (chance >= 100.0)
            return true;

        float roll = Math.RandomFloatInclusive(0.0, 100.0);
        return roll <= chance;
    }

    protected int GetRewardEntrySpawnCount(DeutschZKotHZReward reward)
    {
        if (!reward)
            return 0;

        int count = 1;
        if (!HasNestedRewardData(reward) && reward.Quantity > 1)
            count = reward.Quantity;

        if (reward.MaxSpawnable > 0 && count > reward.MaxSpawnable)
            count = reward.MaxSpawnable;

        if (count < 1)
            count = 1;

        return count;
    }

    protected bool HasNestedRewardData(DeutschZKotHZReward reward)
    {
        if (!reward)
            return false;

        if (reward.MagazineClassName != "")
            return true;
        if (reward.AttachmentItems && reward.AttachmentItems.Count() > 0)
            return true;
        if (reward.CargoItems && reward.CargoItems.Count() > 0)
            return true;
        if (reward.ExtraRewardItems && reward.ExtraRewardItems.Count() > 0)
            return true;
        if (reward.AlternativeClassNames && reward.AlternativeClassNames.Count() > 0)
            return true;

        return false;
    }

    protected EntityAI CreateRewardEntity(EntityAI parent, EntityAI crate, DeutschZKotHZReward reward, bool asAttachment)
    {
        if (!reward || !parent || !crate)
            return null;

        string className = ResolveRewardClassName(reward);
        if (className == "")
            return null;

        if (!IsRewardClassConfigured(className))
        {
            Print("[DeutschZ_KotHZ] Reward classname not found in config, skipped: " + className);
            return null;
        }

        EntityAI item = null;

        if (asAttachment)
            item = parent.GetInventory().CreateAttachment(className);

        if (!item)
            item = parent.GetInventory().CreateInInventory(className);

        if (!item && parent != crate)
            item = crate.GetInventory().CreateInInventory(className);

        return item;
    }

    protected bool IsRewardClassConfigured(string className)
    {
        if (className == "")
            return false;

        if (GetGame().ConfigIsExisting("CfgVehicles " + className))
            return true;
        if (GetGame().ConfigIsExisting("CfgWeapons " + className))
            return true;
        if (GetGame().ConfigIsExisting("CfgMagazines " + className))
            return true;

        return false;
    }

    protected string ResolveRewardClassName(DeutschZKotHZReward reward)
    {
        if (!reward)
            return "";

        // FIX16: primary reward first, but fall back safely when optional weapon mods are not loaded.
        if (reward.ClassName != "" && IsRewardClassConfigured(reward.ClassName))
            return reward.ClassName;

        if (reward.ClassName != "")
            Print("[DeutschZ_KotHZ] Primary reward classname missing, checking alternatives: " + reward.ClassName);

        if (reward.AlternativeClassNames && reward.AlternativeClassNames.Count() > 0)
        {
            foreach (string alternativeClassName : reward.AlternativeClassNames)
            {
                if (alternativeClassName != "" && IsRewardClassConfigured(alternativeClassName))
                {
                    Print("[DeutschZ_KotHZ] Reward fallback selected: " + alternativeClassName);
                    return alternativeClassName;
                }
            }
        }

        return "";
    }

    protected void SpawnRewardChildren(EntityAI item, EntityAI crate, DeutschZKotHZReward reward)
    {
        if (!item || !crate || !reward)
            return;

        if (reward.MagazineClassName != "")
        {
            if (!IsRewardClassConfigured(reward.MagazineClassName))
            {
                Print("[DeutschZ_KotHZ] Reward magazine classname not found in config, skipped: " + reward.MagazineClassName);
            }
            else
            {
                EntityAI mag = crate.GetInventory().CreateInInventory(reward.MagazineClassName);
                if (!mag)
                    Print("[DeutschZ_KotHZ] Reward magazine could not be inserted into crate: " + reward.MagazineClassName);
            }
        }

        if (reward.AttachmentItems)
        {
            foreach (DeutschZKotHZReward attachment : reward.AttachmentItems)
            {
                SpawnRewardEntry(item, crate, attachment, true);
            }
        }

        if (reward.CargoItems)
        {
            foreach (DeutschZKotHZReward cargoItem : reward.CargoItems)
            {
                SpawnRewardEntry(item, crate, cargoItem, false);
            }
        }

        if (reward.ExtraRewardItems)
        {
            foreach (DeutschZKotHZReward extraItem : reward.ExtraRewardItems)
            {
                SpawnRewardEntry(crate, crate, extraItem, false);
            }
        }
    }

    protected Object SpawnRewardCrateObject(string crateClassName, vector cratePos, bool airDrop)
    {
        if (crateClassName == "" || crateClassName == "SeaChest" || crateClassName == "WoodenCrate" || crateClassName == "DeutschZKotHZ_DropCrate")
            crateClassName = "DeutschZKotHZ_RewardCrate";

        if (!GetGame().ConfigIsExisting("CfgVehicles " + crateClassName))
        {
            Print("[DeutschZ_KotHZ] Reward crate classname not found in CfgVehicles: " + crateClassName);
            return null;
        }

        Object crateObj;
        if (airDrop)
        {
            crateObj = GetGame().CreateObjectEx(crateClassName, cratePos, ECE_CREATEPHYSICS | ECE_SETUP | ECE_UPDATEPATHGRAPH, RF_DEFAULT);
            if (!crateObj)
                crateObj = GetGame().CreateObjectEx(crateClassName, cratePos, ECE_CREATEPHYSICS | ECE_SETUP);
            if (!crateObj)
                crateObj = GetGame().CreateObject(crateClassName, cratePos, false, true, true);
            return crateObj;
        }

        crateObj = GetGame().CreateObjectEx(crateClassName, cratePos, ECE_PLACE_ON_SURFACE | ECE_CREATEPHYSICS | ECE_SETUP | ECE_UPDATEPATHGRAPH, RF_DEFAULT);
        if (!crateObj)
            crateObj = GetGame().CreateObjectEx(crateClassName, cratePos, ECE_PLACE_ON_SURFACE | ECE_CREATEPHYSICS | ECE_SETUP);
        if (!crateObj)
            crateObj = GetGame().CreateObject(crateClassName, cratePos, false, true, true);

        return crateObj;
    }


    protected bool ShouldUseHelicopterRewardDelivery()
    {
        if (!m_Config)
            return false;

        return m_Config.EnableHelicopterRewardDelivery == 1;
    }

    protected void SpawnRewardDeliveryHelicopter(vector landingPos)
    {
        if (!m_Config)
            return;

        string heliClass = m_Config.DeliveryHelicopterClassName;
        if (heliClass == "" || !GetGame().ConfigIsExisting("CfgVehicles " + heliClass))
        {
            heliClass = FindFallbackHelicopterClass();
        }

        if (heliClass == "")
        {
            Print("[DeutschZ_KotHZ] No configured/fallback helicopter class found. Crate will still drop from configured height.");
            return;
        }

        float offset = Math.Max(20.0, m_Config.DeliveryHelicopterOffsetDistance);
        float height = Math.Max(15.0, m_Config.DeliveryHelicopterHeight);
        vector heliPos = landingPos;
        heliPos[0] = heliPos[0] - offset;
        heliPos[1] = GetGame().SurfaceY(landingPos[0], landingPos[2]) + height;

        Object heli = GetGame().CreateObjectEx(heliClass, heliPos, ECE_SETUP, RF_DEFAULT);
        if (!heli)
        {
            Print("[DeutschZ_KotHZ] Delivery helicopter visual spawn failed: " + heliClass + " at " + heliPos.ToString());
            return;
        }

        heli.SetOrientation(Vector(90.0, 0.0, 0.0));
        if (m_DeliveryObjects)
            m_DeliveryObjects.Insert(heli);

        int cleanupMs = (int)(Math.Max(5.0, m_Config.DeliveryHelicopterCleanupSeconds) * 1000);
        GetGame().GetCallQueue(CALL_CATEGORY_SYSTEM).CallLater(DeleteDeliveryObject, cleanupMs, false, heli);
        Print("[DeutschZ_KotHZ] Delivery helicopter visual spawned: " + heliClass + " at " + heliPos.ToString());
    }

    protected string FindFallbackHelicopterClass()
    {
        // No vanilla helicopter exists. Keep this empty so Expansion never becomes an implicit dependency.
        return "";
    }

    protected void AnnounceRewardDrop(vector landingPos)
    {
        if (!m_EventActive || !m_ActiveZone)
            return;

        Announce("Heli-Drop bei KotH - " + m_ActiveZone.ZoneName + ": Reward-Crate faellt jetzt ab!");
        Print("[DeutschZ_KotHZ] Helicopter reward crate drop announced at target " + landingPos.ToString());
    }

    protected void DeleteDeliveryObject(Object obj)
    {
        if (!obj)
            return;

        if (m_DeliveryObjects)
            m_DeliveryObjects.RemoveItem(obj);

        GetGame().ObjectDelete(obj);
    }

    protected void CleanupDeliveryObjects()
    {
        if (!m_DeliveryObjects)
            return;

        foreach (Object obj : m_DeliveryObjects)
        {
            if (obj)
                GetGame().ObjectDelete(obj);
        }

        m_DeliveryObjects.Clear();
    }

    protected void ConfirmRewardCrateVisible(Object crateObj)
    {
        EntityAI crate = EntityAI.Cast(crateObj);
        if (!crate)
        {
            Print("[DeutschZ_KotHZ] Reward crate confirmation failed: crate missing after spawn.");
            return;
        }

        vector pos = crate.GetPosition();
        pos[1] = GetGame().SurfaceY(pos[0], pos[2]) + 0.35;
        crate.SetPosition(pos);
        crate.PlaceOnSurface();
        crate.SetSynchDirty();
        Print("[DeutschZ_KotHZ] Reward crate confirmed/landed at " + crate.GetPosition().ToString() + " class=" + crate.GetType());
    }

    protected vector GetRewardCratePosition(PlayerBase winner, DeutschZKotHZLootPool pool)
    {
        vector pos;

        // v1.0.30: Reward crate should always spawn slightly offset from the mast.
        // Exact reward positions are ignored so the crate spawns visibly offset from the mast.
        if (pool && pool.CrateSpawnAtFlagpole && m_ActiveZone)
            pos = GetFlagpoleBasePosition();
        else if (m_ActiveZone)
            pos = GetFlagpoleBasePosition();
        else if (winner)
            pos = winner.GetPosition();

        if (pos == vector.Zero && m_ActiveZone)
            pos = m_ActiveZone.Position;

        float dist = 6.0;
        if (pool)
            dist = Math.Max(6.0, pool.CrateSpawnDistanceFromFlagpole);

        // Offset on two axes so the crate is never inside the mast/flag object.
        pos[0] = pos[0] + dist;
        pos[2] = pos[2] + (dist * 0.35);
        pos[1] = GetGame().SurfaceY(pos[0], pos[2]);

        Print("[DeutschZ_KotHZ] Reward crate target offset from mast: " + dist.ToString() + "m -> " + pos.ToString());
        return pos;
    }

    protected int GetEffectiveRewardCrateLifetimeSeconds(DeutschZKotHZLootPool pool)
    {
        int minimumLifetime = 1800;
        if (m_Config && m_Config.RewardCrateMinimumLifetimeSeconds > 0)
            minimumLifetime = Math.Max(300, m_Config.RewardCrateMinimumLifetimeSeconds);

        int configuredLifetime = minimumLifetime;
        if (pool && pool.CrateLifetimeSeconds > 0)
            configuredLifetime = pool.CrateLifetimeSeconds;

        return Math.Max(minimumLifetime, configuredLifetime);
    }

    protected void AnnounceRewardCrateDespawnWarning(Object crate, string zoneName, int warningSeconds)
    {
        if (!crate)
            return;

        if (zoneName == "")
            zoneName = "KOTH";

        int minutes = Math.Max(1, warningSeconds / 60);
        string message = "KotH Reward-Crate despawnt in " + minutes.ToString() + " Minuten: " + zoneName + ".";
        if (m_Config && m_Config.RewardCrateDespawnWarningText != "")
        {
            message = m_Config.RewardCrateDespawnWarningText;
            message.Replace("{ZONE}", zoneName);
            message.Replace("{MINUTES}", minutes.ToString());
            message.Replace("{SECONDS}", warningSeconds.ToString());
        }

        Announce(message);
    }

    protected void DeleteRewardCrate(Object crate)
    {
        if (!crate)
            return;

        if (m_RewardCrates)
            m_RewardCrates.RemoveItem(crate);

        DeleteRewardEntityRecursive(EntityAI.Cast(crate));
    }

    protected void CleanupRewardCrates(bool eventEndOnly)
    {
        if (!m_RewardCrates)
            return;

        DeutschZKotHZLootPool pool = GetActiveLootPool();
        if (eventEndOnly && pool && !pool.DeleteCrateOnEventEnd)
            return;

        foreach (Object crate : m_RewardCrates)
        {
            if (!crate)
                continue;

            DeleteRewardEntityRecursive(EntityAI.Cast(crate));
        }

        m_RewardCrates.Clear();
    }

    protected void DeleteRewardEntityRecursive(EntityAI entity)
    {
        if (!entity)
            return;

        ref array<EntityAI> children = new array<EntityAI>;

        int attachmentCount = entity.GetInventory().AttachmentCount();
        for (int attachmentIndex = 0; attachmentIndex < attachmentCount; attachmentIndex++)
        {
            EntityAI attachment = entity.GetInventory().GetAttachmentFromIndex(attachmentIndex);
            if (attachment)
                children.Insert(attachment);
        }

        CargoBase cargo = entity.GetInventory().GetCargo();
        if (cargo)
        {
            for (int cargoIndex = 0; cargoIndex < cargo.GetItemCount(); cargoIndex++)
            {
                EntityAI cargoItem = EntityAI.Cast(cargo.GetItem(cargoIndex));
                if (cargoItem)
                    children.Insert(cargoItem);
            }
        }

        foreach (EntityAI child : children)
        {
            DeleteRewardEntityRecursive(child);
        }

        entity.SetLifetime(0);
        GetGame().ObjectDelete(entity);
    }

    protected DeutschZKotHZLootPool GetActiveLootPool()
    {
        string poolName = "Default";
        if (m_ActiveZone && m_ActiveZone.RewardPoolName != "")
            poolName = m_ActiveZone.RewardPoolName;

        DeutschZKotHZLootPool defaultPool = null;

        if (m_LootPools)
        {
            foreach (DeutschZKotHZLootPool pool : m_LootPools)
            {
                if (!pool)
                    continue;

                if (pool.PoolName == poolName)
                    return pool;

                if (pool.PoolName == "Default")
                    defaultPool = pool;
            }
        }

        if (defaultPool)
        {
            Print("[DeutschZ_KotHZ] RewardPoolName not found: " + poolName + ". Using Default loot pool.");
            return defaultPool;
        }

        return null;
    }

    protected ref array<ref DeutschZKotHZReward> GetActiveRewardList()
    {
        DeutschZKotHZLootPool pool = GetActiveLootPool();
        if (pool && pool.Rewards)
            return pool.Rewards;

        return m_Config.Rewards;
    }

    protected void SyncHUD(int playersInZone, string state)
    {
        if (!m_Config || !m_Config.EnableHUD || !m_ActiveZone)
            return;

        int interval = Math.Max(1, m_Config.HUDUpdateIntervalSeconds);
        int nowMs = GetGame().GetTime();
        if (m_LastHUDSyncMs > 0 && (nowMs - m_LastHUDSyncMs) < (interval * 1000))
            return;

        m_LastHUDSyncMs = nowMs;
        m_LastHUDSyncSecond = m_CurrentCaptureSeconds;
        int percent = 0;
        if (m_ActiveZone.CaptureTimeSeconds > 0)
            percent = Math.Clamp((m_CurrentCaptureSeconds * 100) / m_ActiveZone.CaptureTimeSeconds, 0, 100);

        UpdateFlagVisual(percent);
        SendHUDToAll(true, m_ActiveZone.ZoneName, percent, m_CurrentCaptureSeconds, m_ActiveZone.CaptureTimeSeconds, playersInZone, state);
    }

    protected void SendHUDToAll(bool active, string zoneName, int percent, int seconds, int totalSeconds, int playersInZone, string state)
    {
        ref array<Man> players = new array<Man>;
        GetGame().GetPlayers(players);

        bool useDistanceLimit = false;
        float maxHUDDistance = 0.0;

        if (m_Config && m_Config.EnableHUDDistanceLimit && m_Config.HUDMaxDisplayDistanceMeters > 0)
        {
            useDistanceLimit = true;
            maxHUDDistance = m_Config.HUDMaxDisplayDistanceMeters;
        }

        foreach (Man man : players)
        {
            PlayerBase player = PlayerBase.Cast(man);
            if (!player || !player.GetIdentity())
                continue;

            bool sendActive = active;

            // FIX13: Statusbar only visible near the active zone.
            // Players farther away receive an inactive HUD sync so stale bars are hidden immediately.
            if (active && useDistanceLimit && m_ActiveZone)
            {
                float dist = vector.Distance(player.GetPosition(), m_ActiveZone.Position);
                if (dist > maxHUDDistance)
                    sendActive = false;
            }

            Param8<string, bool, string, int, int, int, int, string> data = new Param8<string, bool, string, int, int, int, int, string>(DeutschZKotHZRPC.TOKEN, sendActive, zoneName, percent, seconds, totalSeconds, playersInZone, state);
            GetGame().RPCSingleParam(player, DeutschZKotHZRPC.SYNC_HUD, data, true, player.GetIdentity());
        }

    }


    protected void UpdateFlagVisual(int percent)
    {
        if (!m_Flagpole)
            return;

        m_Flagpole.SetCaptureVisual(Math.Clamp(percent, 0, 100) / 100.0);
    }

    protected void SpawnFlagpole()
    {
        if (!m_ActiveZone || !m_ActiveZone.EnableFlagpole)
            return;

        CleanupFlagpole();
        m_Flagpole = new DeutschZKotHZFlagpole();
        if (!m_Flagpole.Spawn(m_ActiveZone))
            m_Flagpole = null;
    }

    protected vector GetFlagpoleBasePosition()
    {
        if (m_Flagpole)
            return m_Flagpole.GetBasePosition();

        vector pos = vector.Zero;
        if (m_ActiveZone)
        {
            pos = m_ActiveZone.FlagpolePosition;
            if (pos == vector.Zero)
                pos = m_ActiveZone.Position;

            pos[1] = GetGame().SurfaceY(pos[0], pos[2]);
        }

        return pos;
    }

    protected vector GetFlagpoleTopPosition()
    {
        if (m_Flagpole)
            return m_Flagpole.GetTopPosition();

        vector pos = GetFlagpoleBasePosition();
        if (pos != vector.Zero && m_ActiveZone)
            pos[1] = GetGame().SurfaceY(pos[0], pos[2]) + Math.Max(0.0, m_ActiveZone.FlagVisualHeightOffset);

        return pos;
    }

    protected void CleanupFlagpole()
    {
        if (m_Flagpole)
        {
            m_Flagpole.Cleanup();
            m_Flagpole = null;
        }
    }

    protected void SetStatusSmoke(string smokeState)
    {
        if (smokeState == m_CurrentSmokeState)
            return;

        UpdateAllMapMarkersForSmokeState(smokeState);

        if (!m_Config || !m_Config.Smoke || !m_Config.Smoke.EnableSmoke || !m_ActiveZone)
        {
            m_CurrentSmokeState = smokeState;
            return;
        }

        CleanupSmoke();
        m_CurrentSmokeState = smokeState;

        SetFlagParticleSmoke(smokeState);

        if (smokeState == "")
            return;

        if (m_Config.Smoke.UseParticleSmoke && m_Flagpole)
        {
            // Particle smoke is now attached/synced by the custom flagpole. No world particle needed.
        }

        vector smokePos = GetSmokePosition();

        if (m_Config.Smoke.UseObjectSmoke)
        {
            string className = GetSmokeClassName(smokeState);
            if (className != "")
            {
                m_ActiveSmoke = GetGame().CreateObject(className, smokePos, false, true, true);
                if (m_ActiveSmoke)
                {
                    m_ActiveSmoke.SetPosition(smokePos);
                    ActivateSmokeObject(m_ActiveSmoke);
                }
                else
                {
                    Print("[DeutschZ_KotHZ] Could not spawn smoke object: " + className);
                }
            }
        }

        if (m_Config.Smoke.UseObjectSmoke)
        {
            GetGame().GetCallQueue(CALL_CATEGORY_SYSTEM).Remove(RefreshStatusSmoke);
            int refreshMs = (int)(Math.Max(10.0, m_Config.Smoke.SmokeRefreshSeconds) * 1000);
            GetGame().GetCallQueue(CALL_CATEGORY_SYSTEM).CallLater(RefreshStatusSmoke, refreshMs, false, smokeState);
        }
    }

    protected void ActivateSmokeObject(Object smokeObject)
    {
        if (!smokeObject || !m_Config || !m_Config.Smoke || !m_Config.Smoke.AutoActivateSmokeGrenade)
            return;

        SmokeGrenadeBase smokeGrenade = SmokeGrenadeBase.Cast(smokeObject);
        if (!smokeGrenade)
        {
            Print("[DeutschZ_KotHZ] Smoke object is not SmokeGrenadeBase, skip activation: " + smokeObject.GetType());
            return;
        }

        // Vanilla SmokeGrenadeBase starts smoke by Unpin()->Activate()->OnActivateFinished()->SwitchOn().
        // Fallback ForceSwitchOnSmokeGrenade covers server-spawned grenades that do not finish activation normally.
        smokeGrenade.Unpin();

        if (m_Config.Smoke.ForceSwitchOnSmokeGrenade)
            GetGame().GetCallQueue(CALL_CATEGORY_SYSTEM).CallLater(ForceSmokeSwitchOn, 500, false, smokeGrenade);
    }

    protected void ForceSmokeSwitchOn(Object smokeObject)
    {
        SmokeGrenadeBase smokeGrenade = SmokeGrenadeBase.Cast(smokeObject);
        if (!smokeGrenade)
            return;

        if (smokeGrenade.GetCompEM() && smokeGrenade.GetCompEM().CanWork() && !smokeGrenade.GetCompEM().IsWorking())
            smokeGrenade.GetCompEM().SwitchOn();
    }

    protected vector GetSmokePosition()
    {
        vector smokePos = GetFlagpoleBasePosition();
        if (smokePos == vector.Zero && m_ActiveZone)
            smokePos = m_ActiveZone.Position;

        if (smokePos != vector.Zero)
        {
            float heightOffset = 13.0;
            if (m_Config && m_Config.Smoke)
                heightOffset = Math.Max(1.0, m_Config.Smoke.SmokeHeightAboveFlagpole);

            smokePos[1] = GetGame().SurfaceY(smokePos[0], smokePos[2]) + heightOffset;
        }

        return smokePos;
    }

    protected string GetSmokeClassName(string smokeState)
    {
        if (!m_Config || !m_Config.Smoke)
            return "";

        if (smokeState == "Green" || smokeState == "White" || smokeState == "Black" || smokeState == "Blue")
            return m_Config.Smoke.SmokeObjectClassNameGreen;

        if (smokeState == "Yellow")
            return m_Config.Smoke.SmokeObjectClassNameYellow;

        if (smokeState == "Red")
            return m_Config.Smoke.SmokeObjectClassNameRed;

        return "";
    }

    protected int GetSmokeParticleId(string smokeState)
    {
        if (!m_Config || !m_Config.Smoke)
            return 0;

        if (smokeState == "Green" || smokeState == "White" || smokeState == "Black" || smokeState == "Blue")
            return m_Config.Smoke.ParticleIdGreen;

        if (smokeState == "Yellow")
            return m_Config.Smoke.ParticleIdYellow;

        if (smokeState == "Red")
            return m_Config.Smoke.ParticleIdRed;

        return 0;
    }

    protected void RefreshStatusSmoke(string smokeState)
    {
        if (!m_EventActive || !m_ActiveZone || smokeState != m_CurrentSmokeState || smokeState == "")
            return;

        string oldState = m_CurrentSmokeState;
        m_CurrentSmokeState = "";
        SetStatusSmoke(oldState);
    }

    protected void CleanupSmoke()
    {
        GetGame().GetCallQueue(CALL_CATEGORY_SYSTEM).Remove(RefreshStatusSmoke);

        if (m_ActiveParticleSmoke)
        {
            m_ActiveParticleSmoke.Stop();
            m_ActiveParticleSmoke = null;
        }

        if (m_ActiveSmoke)
        {
            GetGame().ObjectDelete(m_ActiveSmoke);
            m_ActiveSmoke = null;
        }
    }


    protected Object SpawnGuardObject(string className, vector pos)
    {
        if (className == "")
            return null;

        if (!GetGame().ConfigIsExisting("CfgVehicles " + className))
        {
            Print("[DeutschZ_KotHZ] Hostile classname missing in CfgVehicles, spawn skipped: " + className);
            return null;
        }

        bool isInfected = GetGame().IsKindOf(className, "ZombieBase") || GetGame().IsKindOf(className, "DayZInfected");
        if (!isInfected)
        {
            Print("[DeutschZ_KotHZ] Hostile classname is not infected, spawn skipped while optional NPC is parked: " + className);
            return null;
        }

        Object obj = null;
        pos[1] = GetGame().SurfaceY(pos[0], pos[2]) + 0.05;
        obj = GetGame().CreateObjectEx(className, pos, ECE_PLACE_ON_SURFACE | ECE_INITAI);
        if (!obj)
            obj = GetGame().CreateObjectEx(className, pos, ECE_PLACE_ON_SURFACE);

        if (obj)
        {
            obj.SetPosition(pos);
            obj.SetOrientation(Vector(Math.RandomFloatInclusive(0.0, 360.0), 0.0, 0.0));
            Print("[DeutschZ_KotHZ] Infected spawned via wave-safe path: " + className + " at " + pos.ToString());
        }

        return obj;
    }


    protected string ResolveZombieFallbackClass(string preferredFallback)
    {
        if (preferredFallback != "" && GetGame().ConfigIsExisting("CfgVehicles " + preferredFallback))
            return preferredFallback;

        if (m_Config && m_Config.Zombies)
        {
            if (m_Config.Zombies.ZombieFallbackClassName != "" && GetGame().ConfigIsExisting("CfgVehicles " + m_Config.Zombies.ZombieFallbackClassName))
                return m_Config.Zombies.ZombieFallbackClassName;

            if (m_Config.Zombies.ZombieFallbackClassNames)
            {
                foreach (string className : m_Config.Zombies.ZombieFallbackClassNames)
                {
                    if (className != "" && GetGame().ConfigIsExisting("CfgVehicles " + className))
                        return className;
                }
            }
        }

        if (GetGame().ConfigIsExisting("CfgVehicles ZmbM_usSoldier_Officer_Desert"))
            return "ZmbM_usSoldier_Officer_Desert";
        if (GetGame().ConfigIsExisting("CfgVehicles ZmbM_usSoldier_Officer_Desert"))
            return "ZmbM_usSoldier_Officer_Desert";
        if (GetGame().ConfigIsExisting("CfgVehicles ZmbM_usSoldier_Officer_Desert"))
            return "ZmbM_usSoldier_Officer_Desert";

        return "";
    }

    protected Object SpawnFallbackZombie(vector pos, string requestedClassName, string preferredFallback)
    {
        if (!m_Config || !m_Config.Zombies || !m_Config.Zombies.EnableZombieClassFallback)
            return null;

        string fallbackClass = ResolveZombieFallbackClass(preferredFallback);
        if (fallbackClass == "")
        {
            Print("[DeutschZ_KotHZ] Zombie fallback enabled but no fallback class exists in CfgVehicles. Requested=" + requestedClassName);
            return null;
        }

        if (requestedClassName == fallbackClass)
            return null;

        Print("[DeutschZ_KotHZ] Zombie fallback: " + requestedClassName + " -> " + fallbackClass);
        return SpawnGuardObject(fallbackClass, pos);
    }

    protected void SpawnNearFlagTestZombies()
    {
        if (!m_Config || !m_Config.DebugMode || !m_ActiveZone || !m_ActiveZone.EnableZombieSpawns)
            return;

        if (!m_ActiveZone.ZombieTypes || m_ActiveZone.ZombieTypes.Count() == 0)
            return;

        Print("[DeutschZ_KotHZ] Debug visible zombie spawn near flag enabled.");

        for (int i = 0; i < 3; i++)
        {
            string zombieClassName = m_ActiveZone.ZombieTypes.Get(i % m_ActiveZone.ZombieTypes.Count());
            vector pos = GetFlagpoleBasePosition();
            float angle = Math.RandomFloatInclusive(0.0, Math.PI * 2.0);
            float dist = Math.RandomFloatInclusive(12.0, 22.0);
            pos[0] = pos[0] + Math.Cos(angle) * dist;
            pos[2] = pos[2] + Math.Sin(angle) * dist;
            pos[1] = GetGame().SurfaceY(pos[0], pos[2]);

            Object zed = SpawnGuardObject(zombieClassName, pos);

            if (!zed)
            {
                Print("[DeutschZ_KotHZ] DEBUG visible zombie failed: " + zombieClassName);
                continue;
            }

            m_SpawnedZombies.Insert(zed);
            Print("[DeutschZ_KotHZ] DEBUG visible zombie spawned: " + zombieClassName + " at " + pos.ToString());
        }
    }

    protected void StartZombieWaves()
    {
        if (!m_ActiveZone || !m_ActiveZone.EnableZombieSpawns)
            return;

        m_ZombieWavesStarted = true;
        Print("[DeutschZ_KotHZ] Infected Siege armed. Waves trigger by capture percent: 25/50/75. Boss: 90.");
        DZKZ_Log("InfectedSiegeArmed", "percent triggers active");
    }

    protected void CancelZombieWaveSchedule()
    {
        GetGame().GetCallQueue(CALL_CATEGORY_SYSTEM).Remove(SpawnZombieWave);
        GetGame().GetCallQueue(CALL_CATEGORY_SYSTEM).Remove(SpawnConfiguredZombieWave);
    }

    protected DeutschZKotHZWavePool GetActiveWavePool()
    {
        if (!m_Config || !m_Config.WavePools || !m_ActiveZone)
            return null;

        string poolName = m_ActiveZone.WavePoolName;
        if (poolName == "")
            poolName = "KVM1_Test_5x6_Zombies";

        DeutschZKotHZWavePool fallback = null;
        foreach (DeutschZKotHZWavePool pool : m_Config.WavePools)
        {
            if (!pool)
                continue;

            if (pool.PoolName == poolName)
                return pool;

            if (!fallback)
                fallback = pool;
        }

        if (fallback)
            Print("[DeutschZ_KotHZ] WavePoolName not found: " + poolName + ". Using first wave pool: " + fallback.PoolName);

        return fallback;
    }

    protected void SpawnConfiguredZombieWave(DeutschZKotHZWaveEntry wave)
    {
        if (!m_EventActive || !m_ActiveZone || !m_ActiveZone.EnableZombieSpawns || !wave)
            return;

        Print("[DeutschZ_KotHZ] Spawning configured zombie wave: " + wave.WaveName + " count=" + wave.EnemyCount.ToString());
        SpawnZombieBatchFromWave(wave);
    }

    protected void SpawnZombieWave(int waveIndex)
    {
        if (!m_EventActive || !m_ActiveZone || !m_ActiveZone.EnableZombieSpawns)
            return;

        SpawnZombieBatch(m_ActiveZone.ZombiesPerWave);
        Print("[DeutschZ_KotHZ] Spawned zone zombie wave " + waveIndex.ToString() + ". Total tracked zombies: " + m_SpawnedZombies.Count().ToString());
    }

    protected void SpawnZombieBatchFromWave(DeutschZKotHZWaveEntry wave)
    {
        if (!wave || wave.EnemyCount <= 0)
            return;

        if (!wave.EnemyClassNames || wave.EnemyClassNames.Count() == 0)
        {
            if (m_ActiveZone && m_ActiveZone.ZombieTypes)
                wave.EnemyClassNames = m_ActiveZone.ZombieTypes;
        }

        if (!wave.EnemyClassNames || wave.EnemyClassNames.Count() == 0)
        {
            Print("[DeutschZ_KotHZ] Configured wave skipped, no enemy classnames: " + wave.WaveName);
            return;
        }

        int remainingSlots = GetRemainingZombieSlots();
        if (remainingSlots <= 0)
        {
            Print("[DeutschZ_KotHZ] Configured zombie wave skipped, max total reached: " + wave.WaveName);
            return;
        }

        int spawnAmount = wave.EnemyCount;
        if (spawnAmount > remainingSlots)
            spawnAmount = remainingSlots;

        int spawnedThisBatch = 0;
        for (int i = 0; i < spawnAmount; i++)
        {
            string zombieClassName = wave.EnemyClassNames.GetRandomElement();
            if (zombieClassName == "")
                continue;

            vector pos = GetRandomZombiePositionForWave(wave);
            string requestedClassName = zombieClassName;
            if (wave.ValidateClassBeforeSpawn && !IsValidZombieGuardClass(zombieClassName))
                zombieClassName = ResolveZombieFallbackClass(wave.FallbackClassName);

            Object zed = null;
            if (zombieClassName != "")
                zed = SpawnGuardObject(zombieClassName, pos);
            if (!zed)
                zed = SpawnFallbackZombie(pos, requestedClassName, wave.FallbackClassName);
            if (!zed)
            {
                Print("[DeutschZ_KotHZ] Could not spawn configured wave enemy or fallback: " + requestedClassName);
                continue;
            }

            m_SpawnedZombies.Insert(zed);
            RegisterEventInfected(zed, wave.WaveName);
            spawnedThisBatch++;
        }

        Print("[DeutschZ_KotHZ] Configured wave completed: " + wave.WaveName + " spawned=" + spawnedThisBatch.ToString() + " trackedTotal=" + m_SpawnedZombies.Count().ToString());
    }


    protected void ResetInfectedSiegeRuntime()
    {
        m_DZKZ_Wave25Triggered = false;
        m_DZKZ_Wave50Triggered = false;
        m_DZKZ_Wave75Triggered = false;
        m_DZKZ_BossSpawned = false;
        m_DZKZ_BossKilled = false;
        m_DZKZ_WaitingBossKillAnnounced = false;
        m_DZKZ_BossZombie = null;
        if (m_DZKZ_EventInfectedRegistry)
            m_DZKZ_EventInfectedRegistry.Clear();
    }

    protected void TriggerInfectedSiegeByCapturePercent()
    {
        if (!m_EventActive || !m_ActiveZone || !m_ActiveZone.EnableZombieSpawns || m_ActiveZone.CaptureTimeSeconds <= 0)
            return;

        int percent = Math.Clamp((m_CurrentCaptureSeconds * 100) / m_ActiveZone.CaptureTimeSeconds, 0, 100);

        if (percent >= 25 && !m_DZKZ_Wave25Triggered)
        {
            m_DZKZ_Wave25Triggered = true;
            Announce("KotHZ Infected Siege: 25% - zivile Infizierte naehern sich!");
            SpawnInfectedSiegeWave("25 Civilian Infected", GetInfectedSiegeWaveCount(4), GetCivilianInfectedClasses(), 18.0, 42.0);
            DZKZ_Log("WaveTriggered", "25 Civilian");
        }

        if (percent >= 50 && !m_DZKZ_Wave50Triggered)
        {
            m_DZKZ_Wave50Triggered = true;
            Announce("KotHZ Infected Siege: 50% - Hunter-Infizierte greifen an!");
            SpawnInfectedSiegeWave("50 Hunter Infected", GetInfectedSiegeWaveCount(4), GetHunterInfectedClasses(), 20.0, 46.0);
            DZKZ_Log("WaveTriggered", "50 Hunter");
        }

        if (percent >= 75 && !m_DZKZ_Wave75Triggered)
        {
            m_DZKZ_Wave75Triggered = true;
            Announce("KotHZ Infected Siege: 75% - Militaerinfizierte in der Zone!");
            SpawnInfectedSiegeWave("75 Military Infected", GetInfectedSiegeWaveCount(4), GetMilitaryInfectedClasses(), 22.0, 52.0);
            DZKZ_Log("WaveTriggered", "75 Military");
        }

        if (percent >= 90 && !m_DZKZ_BossSpawned)
        {
            m_DZKZ_BossSpawned = true;
            Announce("KotHZ Infected Siege: 90% - Mummy-Boss ist erschienen!");
            SpawnInfectedSiegeBoss();
            DZKZ_Log("BossSpawned", "ZmbM_Mummy");
        }
    }

    protected int GetInfectedSiegeWaveCount(int fallbackCount)
    {
        if (m_ActiveZone && m_ActiveZone.ZombiesPerWave > 0)
            return Math.Clamp(m_ActiveZone.ZombiesPerWave, 1, 12);

        if (fallbackCount <= 0)
            return 4;

        return Math.Clamp(fallbackCount, 1, 12);
    }

    protected ref array<string> GetCivilianInfectedClasses()
    {
        ref array<string> classes = new array<string>;
        classes.Insert("ZmbM_usSoldier_Officer_Desert");
        classes.Insert("ZmbM_CitizenASkinny_Blue");
        classes.Insert("ZmbM_FarmerFat_Brown");
        classes.Insert("ZmbM_VillagerOld_Blue");
        classes.Insert("ZmbF_CitizenANormal_Brown");
        return classes;
    }

    protected ref array<string> GetHunterInfectedClasses()
    {
        ref array<string> classes = new array<string>;
        classes.Insert("ZmbM_usSoldier_Officer_Desert");
        classes.Insert("ZmbM_HunterOld_Summer");
        classes.Insert("ZmbM_HunterOld_Winter");
        classes.Insert("ZmbM_usSoldier_Officer_Desert");
        return classes;
    }

    protected ref array<string> GetMilitaryInfectedClasses()
    {
        ref array<string> classes = new array<string>;
        classes.Insert("ZmbM_usSoldier_Officer_Desert");
        classes.Insert("ZmbM_SoldierNormal_Green");
        classes.Insert("ZmbM_usSoldier_Officer_Desert");
        classes.Insert("ZmbM_NBC_Grey");
        classes.Insert("ZmbM_NBC_Yellow");
        return classes;
    }

    protected void SpawnInfectedSiegeWave(string waveName, int count, array<string> classNames, float minRadius, float maxRadius)
    {
        if (!m_ActiveZone || !classNames || classNames.Count() == 0)
            return;

        DeutschZKotHZWaveEntry wave = new DeutschZKotHZWaveEntry();
        wave.WaveName = waveName;
        wave.EnemyCount = count;
        wave.SpawnRadiusMin = minRadius;
        wave.SpawnRadiusMax = maxRadius;
        wave.SpawnOutdoorOnly = 1;
        wave.ValidateClassBeforeSpawn = 1;
        wave.EnableClassFallback = 1;
        wave.FallbackClassName = "ZmbM_usSoldier_Officer_Desert";
        wave.EnemyClassNames.Clear();
        foreach (string className : classNames)
            wave.EnemyClassNames.Insert(className);

        SpawnZombieBatchFromWave(wave);
    }

    protected void SpawnInfectedSiegeBoss()
    {
        if (!m_ActiveZone)
            return;

        vector pos = GetRandomZombiePosition();
        string bossClass = "ZmbM_Mummy";
        if (!IsValidZombieGuardClass(bossClass))
            bossClass = ResolveZombieFallbackClass("ZmbM_usSoldier_Officer_Desert");

        Object boss = null;
        if (bossClass != "")
            boss = SpawnGuardObject(bossClass, pos);

        if (!boss)
        {
            Print("[DeutschZ_KotHZ] Boss spawn failed, falling back to military infected.");
            boss = SpawnFallbackZombie(pos, "ZmbM_Mummy", "ZmbM_usSoldier_Officer_Desert");
        }

        if (boss)
        {
            m_DZKZ_BossZombie = boss;
            m_SpawnedZombies.Insert(boss);
            RegisterEventInfected(boss, "90 Mummy Boss");
        }
        else
        {
            m_DZKZ_BossKilled = true;
            DZKZ_Log("BossSpawnFailed", "fallback failed, reward block disabled");
        }
    }

    protected void RegisterEventInfected(Object infected, string waveName)
    {
        if (!infected)
            return;

        if (!m_DZKZ_EventInfectedRegistry)
            m_DZKZ_EventInfectedRegistry = new map<Object, string>;

        m_DZKZ_EventInfectedRegistry.Set(infected, waveName);
    }

    bool DZKZ_OnInfectedKilled(Object infected)
    {
        if (!infected || !m_DZKZ_EventInfectedRegistry || !m_DZKZ_EventInfectedRegistry.Contains(infected))
            return false;

        string waveName = m_DZKZ_EventInfectedRegistry.Get(infected);
        m_DZKZ_EventInfectedRegistry.Remove(infected);
        if (m_SpawnedZombies)
            m_SpawnedZombies.RemoveItem(infected);

        if (infected == m_DZKZ_BossZombie)
        {
            m_DZKZ_BossKilled = true;
            m_DZKZ_BossZombie = null;
            Announce("KotHZ Infected Siege: Mummy-Boss eliminiert!");
            DZKZ_Log("BossKilled", waveName);
        }
        else
        {
            DZKZ_Log("ZombieKilled", waveName);
        }

        return true;
    }

    protected void DZKZ_Log(string result, string reason)
    {
        string zone = "";
        if (m_ActiveZone)
            zone = m_ActiveZone.ZoneName;
        string line = "[DeutschZ_KotHZ] " + result + " zone=" + zone + " reason=" + reason;
        Print(line);
        if (m_DZKZ_EventLog)
            m_DZKZ_EventLog.Insert(line);
    }

    protected bool IsValidZombieGuardClass(string zombieClassName)
    {
        if (zombieClassName == "")
            return false;

        if (!GetGame().ConfigIsExisting("CfgVehicles " + zombieClassName))
        {
            Print("[DeutschZ_KotHZ] Zombie classname not found in CfgVehicles: " + zombieClassName);
            return false;
        }

        // DayZ native config inheritance check. Custom infected classes should resolve as ZombieBase or DayZInfected.
        if (GetGame().IsKindOf(zombieClassName, "ZombieBase") || GetGame().IsKindOf(zombieClassName, "DayZInfected"))
            return true;

        Print("[DeutschZ_KotHZ] Zombie classname exists but is not inherited from ZombieBase/DayZInfected: " + zombieClassName);
        return false;
    }

    protected void SpawnZombieBatch(int amount)
    {
        if (!m_ActiveZone || amount <= 0 || !m_ActiveZone.ZombieTypes || m_ActiveZone.ZombieTypes.Count() == 0)
        {
            Print("[DeutschZ_KotHZ] Zombie batch skipped. Zone invalid, amount zero, or ZombieTypes empty.");
            return;
        }

        int remainingSlots = GetRemainingZombieSlots();
        if (remainingSlots <= 0)
        {
            Print("[DeutschZ_KotHZ] Zombie batch skipped, max total reached.");
            return;
        }

        if (amount > remainingSlots)
            amount = remainingSlots;

        Print("[DeutschZ_KotHZ] Spawning zombie batch amount=" + amount + " types=" + m_ActiveZone.ZombieTypes.Count());

        int spawnedThisBatch = 0;
        for (int i = 0; i < amount; i++)
        {
            string zombieClassName = m_ActiveZone.ZombieTypes.GetRandomElement();
            if (zombieClassName == "")
                continue;

            string requestedClassName = zombieClassName;
            if (m_ActiveZone.ValidateZombieClassBeforeSpawn && !IsValidZombieGuardClass(zombieClassName))
                zombieClassName = ResolveZombieFallbackClass("");

            vector pos = GetRandomZombiePosition();
            Object zed = null;
            if (zombieClassName != "")
                zed = SpawnGuardObject(zombieClassName, pos);

            if (!zed)
                zed = SpawnFallbackZombie(pos, requestedClassName, "");

            if (!zed)
            {
                Print("[DeutschZ_KotHZ] Could not spawn zombie classname or fallback: " + requestedClassName);
                continue;
            }

            vector zedOri = "0 0 0";
            zedOri[0] = Math.RandomFloatInclusive(0.0, 360.0);
            zed.SetOrientation(zedOri);
            m_SpawnedZombies.Insert(zed);
            RegisterEventInfected(zed, "LegacyBatch");
            spawnedThisBatch++;
            Print("[DeutschZ_KotHZ] Zombie spawned: " + zombieClassName + " at " + pos.ToString());
        }

        if (spawnedThisBatch == 0)
            Print("[DeutschZ_KotHZ] WARNING: Zombie batch spawned zero objects. Check classnames/mod dependencies and surface positions.");
        else
            Print("[DeutschZ_KotHZ] Zombie batch completed. Spawned=" + spawnedThisBatch.ToString() + " trackedTotal=" + m_SpawnedZombies.Count().ToString());
    }

    protected vector GetRandomZombiePositionForWave(DeutschZKotHZWaveEntry wave)
    {
        if (!wave)
            return GetRandomZombiePosition();

        float minDist = Math.Max(1.0, wave.SpawnRadiusMin);
        float maxDist = Math.Max(minDist, wave.SpawnRadiusMax);
        float angle = Math.RandomFloatInclusive(0.0, Math.PI * 2.0);
        float dist = Math.RandomFloatInclusive(minDist, maxDist);
        vector pos = m_ActiveZone.Position;
        pos[0] = pos[0] + Math.Cos(angle) * dist;
        pos[2] = pos[2] + Math.Sin(angle) * dist;
        pos[1] = GetGame().SurfaceY(pos[0], pos[2]);
        return pos;
    }

    protected vector GetRandomZombiePosition()
    {
        float minDist = Math.Max(1.0, m_ActiveZone.ZombieSpawnMinDistance);
        float maxDist = Math.Max(minDist, m_ActiveZone.ZombieSpawnMaxDistance);
        float angle = Math.RandomFloatInclusive(0.0, Math.PI * 2.0);
        float dist = Math.RandomFloatInclusive(minDist, maxDist);
        vector pos = m_ActiveZone.Position;
        pos[0] = pos[0] + Math.Cos(angle) * dist;
        pos[2] = pos[2] + Math.Sin(angle) * dist;
        pos[1] = GetGame().SurfaceY(pos[0], pos[2]);
        return pos;
    }

    protected void CleanupZombies()
    {
        if (!m_SpawnedZombies)
            return;

        if (m_ActiveZone && !m_ActiveZone.DespawnZombiesOnEventEnd)
        {
            m_SpawnedZombies.Clear();
            if (m_DZKZ_EventInfectedRegistry)
                m_DZKZ_EventInfectedRegistry.Clear();
            m_DZKZ_BossZombie = null;
            return;
        }

        foreach (Object zed : m_SpawnedZombies)
        {
            if (zed)
                GetGame().ObjectDelete(zed);
        }

        m_SpawnedZombies.Clear();
        if (m_DZKZ_EventInfectedRegistry)
            m_DZKZ_EventInfectedRegistry.Clear();
        m_DZKZ_BossZombie = null;
    }

    protected void SpawnOptionalNPCs()
    {
        int optionalAIEnabled = 0;
        if (!optionalAIEnabled)
        {
            Print("[DeutschZ_KotHZ] Optional NPC spawn skipped. NPC settings are parked; zombie waves remain active.");
            return;
        }

        if (!m_ActiveZone || !m_ActiveZone.EnableOptionalNPC)
            return;

        if (m_ActiveZone.NPCAmount <= 0)
        {
            Print("[DeutschZ_KotHZ] NPC enabled for zone, but NPCAmount is zero: " + m_ActiveZone.ZoneName);
            return;
        }

        if (!m_ActiveZone.NPCClassNames || m_ActiveZone.NPCClassNames.Count() == 0)
        {
            Print("[DeutschZ_KotHZ] Optional NPC enabled but no NPCClassNames configured. NPC spawn skipped; zombie waves remain active.");
            return;
        }

        for (int i = 0; i < m_ActiveZone.NPCAmount; i++)
        {
            string aiClassName = GetZoneNPCClassName(i);

            if (aiClassName == "")
            {
                Print("[DeutschZ_KotHZ] Empty NPC classname at index: " + i);
                continue;
            }

            if (m_ActiveZone.ValidateNPCClassBeforeSpawn && !GetGame().ConfigIsExisting("CfgVehicles " + aiClassName))
            {
                Print("[DeutschZ_KotHZ] Optional NPC classname not found in CfgVehicles: " + aiClassName + ". NPC spawn skipped.");
                continue;
            }

            vector pos = GetRandomNPCPosition();
            Object ai = SpawnGuardObject(aiClassName, pos);
            if (!ai)
            {
                Print("[DeutschZ_KotHZ] Could not spawn NPC classname: " + aiClassName);
                continue;
            }

            Print("[DeutschZ_KotHZ] NPC spawned: " + aiClassName + " at " + pos.ToString());
            ApplyZoneNPCLoadout(ai);
            m_SpawnedNPCs.Insert(ai);
        }

        Print("[DeutschZ_KotHZ] Spawned NPC for " + m_ActiveZone.ZoneName + ": " + m_SpawnedNPCs.Count());
        if (m_SpawnedNPCs.Count() == 0)
            Print("[DeutschZ_KotHZ] WARNING: No optional NPC spawned. Zombies remain the visible enemy fallback for this test.");
    }

    protected string GetZoneNPCClassName(int index)
    {
        if (!m_ActiveZone || !m_ActiveZone.NPCClassNames || m_ActiveZone.NPCClassNames.Count() == 0)
            return "";

        int safeIndex = index % m_ActiveZone.NPCClassNames.Count();
        string className = m_ActiveZone.NPCClassNames.Get(safeIndex);

        return className;
    }

    protected vector GetRandomNPCPosition()
    {
        float radius = Math.Max(1.0, m_ActiveZone.NPCSpawnRadius);
        float angle = Math.RandomFloatInclusive(0.0, Math.PI * 2.0);
        float dist = Math.RandomFloatInclusive(5.0, radius);
        vector pos = m_ActiveZone.Position;
        pos[0] = pos[0] + Math.Cos(angle) * dist;
        pos[2] = pos[2] + Math.Sin(angle) * dist;
        pos[1] = GetGame().SurfaceY(pos[0], pos[2]) + m_ActiveZone.NPCSpawnHeightOffset;
        return pos;
    }

    protected void ApplyZoneNPCLoadout(Object ai)
    {
        EntityAI entity = EntityAI.Cast(ai);
        if (!entity || !m_ActiveZone || !m_ActiveZone.NPCLoadoutClassNames)
            return;

        foreach (string itemName : m_ActiveZone.NPCLoadoutClassNames)
        {
            if (itemName != "")
                entity.GetInventory().CreateInInventory(itemName);
        }
    }

    protected void CleanupOptionalNPCs()
    {
        if (!m_SpawnedNPCs)
            return;

        if (m_ActiveZone && !m_ActiveZone.NPCDespawnOnEventEnd)
        {
            m_SpawnedNPCs.Clear();
            return;
        }

        foreach (Object ai : m_SpawnedNPCs)
        {
            if (ai)
                GetGame().ObjectDelete(ai);
        }

        m_SpawnedNPCs.Clear();
    }


    protected void SetFlagParticleSmoke(string smokeState)
    {
        if (!m_Flagpole || !m_Config || !m_Config.Smoke)
            return;

        int state = -1;
        if (smokeState == "Green" || smokeState == "White" || smokeState == "Black" || smokeState == "Blue")
            state = 0;
        else if (smokeState == "Yellow")
            state = 1;
        else if (smokeState == "Red")
            state = 2;

        m_Flagpole.SetSmokeVisual(state, Math.Max(1.0, m_Config.Smoke.SmokeHeightAboveFlagpole));
    }

    protected string GetShortKOTHLocationName()
    {
        if (!m_ActiveZone)
            return "Zone";

        string name = m_ActiveZone.ZoneName;
        if (name == "")
            return "Zone";

        if (name == "NWAF KOTH TEST" || name == "NWAF KOTH")
            return "NWAF";
        if (name == "Tisy KOTH" || name == "TISY KOTH")
            return "Tisy";
        if (name == "LOPA KOTH")
            return "LOPA";
        if (name == "YRAP KOTH")
            return "YRAP";
        if (name == "Basebuilding KOTH" || name == "BaseBuilding KOTH")
            return "Basebuilding";

        return name;
    }



    protected bool ShouldRunChance(float chance)
    {
        if (chance <= 0.0)
            return false;
        if (chance >= 1.0)
            return true;
        return Math.RandomFloat01() <= chance;
    }

    protected void MaybeStartFogHazard(string eventState)
    {
        if (!m_Config || !m_Config.Smoke || !m_Config.Smoke.EnableFogHazard || !m_ActiveZone)
            return;

        if (m_FogEmitters && m_FogEmitters.Count() > 0)
            return;

        if (eventState == "Ready" && !m_Config.Smoke.FogStartOnReady)
            return;
        if (eventState == "Progress" && !m_Config.Smoke.FogStartOnProgress)
            return;
        if (eventState == "Completed" && !m_Config.Smoke.FogStartOnCompleted)
            return;

        if (!ShouldRunChance(m_Config.Smoke.FogHazardChance))
        {
            Print("[DeutschZ_KotHZ] Fog hazard chance roll skipped fog for this event.");
            return;
        }

        SpawnFogPulse();
    }

    protected void SpawnFogPulse()
    {
        if (!m_EventActive || !m_ActiveZone || !m_Config || !m_Config.Smoke || !m_Config.Smoke.EnableFogHazard)
            return;

        int count = Math.Max(0, m_Config.Smoke.FogEmitterCount);
        if (count <= 0)
            return;

        string emitterType = m_Config.Smoke.FogEmitterObjectType;
        if (emitterType == "")
            emitterType = "DeutschZKotHZ_RuntimeFogEmitter";

        int spawned = 0;
        for (int i = 0; i < count; i++)
        {
            vector pos = GetRandomFogPosition();
            Object obj = GetGame().CreateObjectEx(emitterType, pos, ECE_PLACE_ON_SURFACE | ECE_CREATEPHYSICS | ECE_SETUP);
            if (!obj)
                obj = GetGame().CreateObject(emitterType, pos, false, true, true);

            if (!obj)
            {
                Print("[DeutschZ_KotHZ] Fog emitter spawn failed: " + emitterType);
                continue;
            }

            obj.SetPosition(pos);
            EntityAI ent = EntityAI.Cast(obj);
            if (ent)
                ent.PlaceOnSurface();

            DeutschZKotHZ_RuntimeFogEmitter emitter = DeutschZKotHZ_RuntimeFogEmitter.Cast(obj);
            if (emitter)
                emitter.DeutschZKotHZ_StartFog(m_Config.Smoke.FogParticleType);

            m_FogEmitters.Insert(obj);
            spawned++;
        }

        Print("[DeutschZ_KotHZ] Fog hazard pulse spawned emitters: " + spawned.ToString() + "/" + count.ToString());

        if (m_Config.Smoke.EnableSmokeCannons)
            SpawnSmokeCannons();

        if (m_Config.Smoke.FogPulseSeconds > 0)
            GetGame().GetCallQueue(CALL_CATEGORY_SYSTEM).CallLater(SpawnFogPulse, m_Config.Smoke.FogPulseSeconds * 1000, false);
    }

    protected vector GetRandomFogPosition()
    {
        float radius = Math.Max(1.0, m_Config.Smoke.FogRadius);
        float angle = Math.RandomFloatInclusive(0.0, Math.PI * 2.0);
        float dist = Math.RandomFloatInclusive(2.0, radius);
        vector pos = m_ActiveZone.Position;
        pos[0] = pos[0] + Math.Cos(angle) * dist;
        pos[2] = pos[2] + Math.Sin(angle) * dist;
        pos[1] = GetGame().SurfaceY(pos[0], pos[2]) + Math.Max(0.0, m_Config.Smoke.FogEmitterHeightOffset);
        return pos;
    }

    protected void SpawnSmokeCannons()
    {
        if (!m_Config || !m_Config.Smoke || !m_Config.Smoke.SmokeCannonClassNames || m_Config.Smoke.SmokeCannonClassNames.Count() == 0)
            return;

        int count = Math.Max(0, m_Config.Smoke.SmokeCannonCount);
        for (int i = 0; i < count; i++)
        {
            string smokeType = m_Config.Smoke.SmokeCannonClassNames.GetRandomElement();
            vector pos = GetRandomSmokeCannonPosition();
            Object smoke = GetGame().CreateObject(smokeType, pos, false, true, true);
            if (!smoke)
            {
                Print("[DeutschZ_KotHZ] Smoke cannon spawn failed: " + smokeType);
                continue;
            }

            smoke.SetPosition(pos);
            ActivateSmokeObject(smoke);
            m_SmokeCannons.Insert(smoke);
        }
    }

    protected vector GetRandomSmokeCannonPosition()
    {
        float radius = Math.Max(1.0, m_Config.Smoke.SmokeCannonRadius);
        float angle = Math.RandomFloatInclusive(0.0, Math.PI * 2.0);
        float dist = Math.RandomFloatInclusive(2.0, radius);
        vector pos = m_ActiveZone.Position;
        pos[0] = pos[0] + Math.Cos(angle) * dist;
        pos[2] = pos[2] + Math.Sin(angle) * dist;
        pos[1] = GetGame().SurfaceY(pos[0], pos[2]);
        return pos;
    }

    protected void CleanupFogHazard()
    {
        GetGame().GetCallQueue(CALL_CATEGORY_SYSTEM).Remove(SpawnFogPulse);

        if (m_FogEmitters)
        {
            foreach (Object fog : m_FogEmitters)
            {
                if (fog)
                    GetGame().ObjectDelete(fog);
            }
            m_FogEmitters.Clear();
        }

        if (m_SmokeCannons)
        {
            foreach (Object smoke : m_SmokeCannons)
            {
                if (smoke)
                    GetGame().ObjectDelete(smoke);
            }
            m_SmokeCannons.Clear();
        }
    }


    protected void CreateAllMapMarkers()
    {
        string backend = GetMarkerMode();

        if (backend == "Off" || backend == "VanillaNotifications")
        {
            Print("[DeutschZ_KotHZ] Marker mode disabled or notifications-only. No external map marker API called.");
            return;
        }

        if (!CreateCoreMarker())
            Print("[DeutschZ_KotHZ] Core marker could not be created. HUD/notifications remain active.");
    }

    protected void UpdateAllMapMarkersForSmokeState(string smokeState)
    {
        if (GetMarkerMode() == "Expansion")
            UpdateCoreMarkerForSmokeState(smokeState);
    }

    protected void DeleteAllMapMarkers()
    {
        DeleteCoreMarker();
    }

    protected string GetMarkerMode()
    {
        if (!m_Config)
            return "VanillaNotifications";

        string backend = m_Config.MarkerMode;

        if (backend == "" || backend == "Auto" || backend == "Multi" || backend == "ExpansionOnly")
            backend = "Expansion";

        if (backend == "NotificationsOnly")
            backend = "VanillaNotifications";

        if (backend != "Off" && backend != "VanillaNotifications" && backend != "Expansion")
            backend = "Expansion";

        return backend;
    }

    protected bool CreateCoreMarker()
    {
        string backend = GetMarkerMode();
        if (!m_Config || !m_Config.EnableExpansionMarker || !m_ActiveZone || backend != "Expansion")
            return false;

        vector markerPos = m_ActiveZone.Position;
        markerPos[1] = GetGame().SurfaceY(markerPos[0], markerPos[2]) + 3.0;
        m_DeutschZKotHZMarkerId = GetShortKOTHLocationName();
        if (DeutschZKotHZCoreBridge.CreateEventMarker(m_DeutschZKotHZMarkerId, "KotH - " + GetShortKOTHLocationName(), markerPos))
        {
            Print("[DeutschZ_KotHZ] Core marker created for " + m_ActiveZone.ZoneName);
            if (m_Config.EnableExpansion3DMarker == 1)
                DeutschZKotHZCoreBridge.CreateEvent3DMarker(m_DeutschZKotHZMarkerId, "KotH - " + GetShortKOTHLocationName(), markerPos);
            return true;
        }

        Print("[DeutschZ_KotHZ] Core marker provider unavailable. HUD/notifications remain active.");
        return false;
    }

    protected void UpdateCoreMarkerForSmokeState(string smokeState)
    {
        if (m_DeutschZKotHZMarkerId == "" || !m_ActiveZone)
            return;

        DeutschZKotHZCoreBridge.CreateEventMarker(m_DeutschZKotHZMarkerId, "KotH - " + GetShortKOTHLocationName(), m_ActiveZone.Position);
        if (m_Config && m_Config.EnableExpansion3DMarker == 1)
            DeutschZKotHZCoreBridge.CreateEvent3DMarker(m_DeutschZKotHZMarkerId, "KotH - " + GetShortKOTHLocationName(), m_ActiveZone.Position);
    }

    protected void DeleteCoreMarker()
    {
        if (m_DeutschZKotHZMarkerId != "")
        {
            DeutschZKotHZCoreBridge.DeleteEventMarker(m_DeutschZKotHZMarkerId);
            Print("[DeutschZ_KotHZ] Core marker removed.");
        }
        m_DeutschZKotHZMarkerId = "";
    }

    protected int GetMarkerColorForSmokeState(string smokeState)
    {
        if (smokeState == "Green")
            return ARGB(255, 0, 255, 0);

        if (smokeState == "Yellow")
            return ARGB(255, 255, 255, 0);

        return ARGB(255, 255, 0, 0);
    }

    protected void Announce(string message)
    {
        Print("[DeutschZ_KotHZ] " + message);

        if (!m_Config || !m_Config.AnnounceEvent)
            return;

        int nowMs = GetGame().GetTime();
        if (message == m_LastAnnounceMessage && (nowMs - m_LastAnnounceTimeMs) < 4000)
        {
            Print("[DeutschZ_KotHZ] Duplicate announce blocked: " + message);
            return;
        }

        m_LastAnnounceMessage = message;
        m_LastAnnounceTimeMs = nowMs;

        bool sendVanillaNotification = true;
        bool sendVanillaChatMessage = true;

        if (m_Config)
        {
            if (m_Config.EnableExpansionNotifications == 1)
            {
                vector notifyPos = "0 0 0";
                if (m_ActiveZone)
                    notifyPos = m_ActiveZone.Position;
                DeutschZKotHZCoreBridge.SendNotification("status", "DeutschZ KotHZ", message, notifyPos);
            }

            sendVanillaNotification = m_Config.EnableVanillaNotifications == 1;
            sendVanillaChatMessage = m_Config.EnableVanillaChatMessages == 1;
        }

        if (!sendVanillaNotification && !sendVanillaChatMessage)
            return;

        ref array<Man> players = new array<Man>;
        GetGame().GetPlayers(players);

        foreach (Man man : players)
        {
            PlayerBase player = PlayerBase.Cast(man);
            if (!player || !player.GetIdentity())
                continue;

            if (sendVanillaNotification)
                NotificationSystem.SendNotificationToPlayerExtended(player, 12.0, "DeutschZ KotHZ", message, "set:dayz_inventory image:tf_flag");

            if (sendVanillaChatMessage)
            {
                Param1<string> data = new Param1<string>(message);
                GetGame().RPCSingleParam(player, ERPCs.RPC_USER_ACTION_MESSAGE, data, true, player.GetIdentity());
            }
        }
    }

    protected string GetPlayerName(PlayerBase player)
    {
        if (player && player.GetIdentity())
            return player.GetIdentity().GetName();

        return "Unbekannt";
    }
}
