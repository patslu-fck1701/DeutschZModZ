/*
DeutschZ ModZ
Eigenstaendige Implementierung fuer DeutschZ.
Autor/Eigentuemer: Patrick Sluzalek / fck1701.
Keine direkte Codeuebernahme aus Drittquellen.
Oeffentliche Quellen werden nur zur Konzept- und API-Verifikation genutzt.
*/


// DeutschZ unified event config standard v1.
// Same JSON block name in every event config: DeutschZEventSettings.
class DeutschZKotHZEventCoreSettings
{
    int Enabled;
    int MinOnlinePlayers;
    int MaxSimultaneousEvents;
    int MaxEventsPerRestart;
    int MaxRuntimeSeconds;
    int CleanupDelaySeconds;
    int DebugLogs;

    void DeutschZKotHZEventCoreSettings()
    {
        Enabled = 1;
        MinOnlinePlayers = 1;
        MaxSimultaneousEvents = 1;
        MaxEventsPerRestart = 999;
        MaxRuntimeSeconds = 1800;
        CleanupDelaySeconds = 60;
        DebugLogs = 1;
    }

    void Repair()
    {
        if (Enabled != 0) Enabled = 1;
        if (MinOnlinePlayers < 0) MinOnlinePlayers = 0;
        if (MaxSimultaneousEvents < 1) MaxSimultaneousEvents = 1;
        if (MaxEventsPerRestart < 0) MaxEventsPerRestart = 0;
        if (MaxRuntimeSeconds < 0) MaxRuntimeSeconds = 0;
        if (CleanupDelaySeconds < 0) CleanupDelaySeconds = 0;
        if (DebugLogs != 0) DebugLogs = 1;
    }
}

class DeutschZKotHZEventSchedulingSettings
{
    int AutoStartAfterRestart;
    int StartDelayMinSeconds;
    int StartDelayMaxSeconds;
    int RestartAfterFinish;
    int RestartDelayMinSeconds;
    int RestartDelayMaxSeconds;
    int NoPlayerRetryDelaySeconds;

    void DeutschZKotHZEventSchedulingSettings()
    {
        AutoStartAfterRestart = 1;
        StartDelayMinSeconds = 300;
        StartDelayMaxSeconds = 300;
        RestartAfterFinish = 1;
        RestartDelayMinSeconds = 1200;
        RestartDelayMaxSeconds = 1200;
        NoPlayerRetryDelaySeconds = 60;
    }

    void Repair()
    {
        if (AutoStartAfterRestart != 0) AutoStartAfterRestart = 1;
        if (StartDelayMinSeconds < 0) StartDelayMinSeconds = 0;
        if (StartDelayMaxSeconds < StartDelayMinSeconds) StartDelayMaxSeconds = StartDelayMinSeconds;
        if (RestartAfterFinish != 0) RestartAfterFinish = 1;
        if (RestartDelayMinSeconds < 0) RestartDelayMinSeconds = 0;
        if (RestartDelayMaxSeconds < RestartDelayMinSeconds) RestartDelayMaxSeconds = RestartDelayMinSeconds;
        if (NoPlayerRetryDelaySeconds < 0) NoPlayerRetryDelaySeconds = 0;
    }
}

class DeutschZKotHZEventMarkerSettings
{
    int Enabled;
    int UseMapMarker;
    int Use3DMarker;
    int UseDynamicPositionUpdates;
    int UpdateIntervalSeconds;
    int ShowEventRadius;
    int ShowCarrierMarker;
    int ShowDroppedItemMarker;
    int ShowFinalMarker;
    int ShowExtractionMarker;
    string MarkerName;
    string MarkerIcon;
    int MarkerColorARGB;
    string MarkerPrefix;

    void DeutschZKotHZEventMarkerSettings()
    {
        Enabled = 1;
        UseMapMarker = 1;
        Use3DMarker = 1;
        UseDynamicPositionUpdates = 1;
        UpdateIntervalSeconds = 10;
        ShowEventRadius = 1;
        ShowCarrierMarker = 1;
        ShowDroppedItemMarker = 1;
        ShowFinalMarker = 1;
        ShowExtractionMarker = 1;
        MarkerName = "DeutschZ KotHZ";
        MarkerIcon = "Territory";
        MarkerColorARGB = -65536;
        MarkerPrefix = "KotHZ_";
    }

    void Repair(string fallbackName, string fallbackIcon, string fallbackPrefix)
    {
        if (Enabled != 0) Enabled = 1;
        if (UseMapMarker != 0) UseMapMarker = 1;
        if (Use3DMarker != 0) Use3DMarker = 1;
        if (UseDynamicPositionUpdates != 0) UseDynamicPositionUpdates = 1;
        if (UpdateIntervalSeconds < 1) UpdateIntervalSeconds = 1;
        if (ShowEventRadius != 0) ShowEventRadius = 1;
        if (ShowCarrierMarker != 0) ShowCarrierMarker = 1;
        if (ShowDroppedItemMarker != 0) ShowDroppedItemMarker = 1;
        if (ShowFinalMarker != 0) ShowFinalMarker = 1;
        if (ShowExtractionMarker != 0) ShowExtractionMarker = 1;
        if (MarkerName == "") MarkerName = fallbackName;
        if (MarkerIcon == "") MarkerIcon = fallbackIcon;
        if (MarkerPrefix == "") MarkerPrefix = fallbackPrefix;
        if (MarkerColorARGB == 0) MarkerColorARGB = -65536;
    }
}

class DeutschZKotHZEventNotificationSettings
{
    int Enabled;
    int UseExpansionNotifications;
    int UseVanillaNotifications;
    int UseChatMessages;
    int StatusNotifications;
    int StatusIntervalSeconds;
    int NotifyOnScheduled;
    int NotifyOnStart;
    int NotifyOnStageChange;
    int NotifyOnMarkerUpdate;
    int NotifyOnComplete;
    int NotifyOnFail;

    void DeutschZKotHZEventNotificationSettings()
    {
        Enabled = 1;
        UseExpansionNotifications = 1;
        UseVanillaNotifications = 1;
        UseChatMessages = 1;
        StatusNotifications = 1;
        StatusIntervalSeconds = 60;
        NotifyOnScheduled = 1;
        NotifyOnStart = 1;
        NotifyOnStageChange = 1;
        NotifyOnMarkerUpdate = 0;
        NotifyOnComplete = 1;
        NotifyOnFail = 1;
    }

    void Repair()
    {
        if (Enabled != 0) Enabled = 1;
        if (UseExpansionNotifications != 0) UseExpansionNotifications = 1;
        if (UseVanillaNotifications != 0) UseVanillaNotifications = 1;
        if (UseChatMessages != 0) UseChatMessages = 1;
        if (StatusNotifications != 0) StatusNotifications = 1;
        if (StatusIntervalSeconds < 3) StatusIntervalSeconds = 3;
        if (NotifyOnScheduled != 0) NotifyOnScheduled = 1;
        if (NotifyOnStart != 0) NotifyOnStart = 1;
        if (NotifyOnStageChange != 0) NotifyOnStageChange = 1;
        if (NotifyOnMarkerUpdate != 0) NotifyOnMarkerUpdate = 1;
        if (NotifyOnComplete != 0) NotifyOnComplete = 1;
        if (NotifyOnFail != 0) NotifyOnFail = 1;
    }
}

class DeutschZKotHZEventRewardSettings
{
    int Enabled;
    int RewardLifetimeSeconds;
    int DespawnWarningEnabled;
    int DespawnWarningSeconds;

    void DeutschZKotHZEventRewardSettings()
    {
        Enabled = 1;
        RewardLifetimeSeconds = 1800;
        DespawnWarningEnabled = 1;
        DespawnWarningSeconds = 300;
    }

    void Repair()
    {
        if (Enabled != 0) Enabled = 1;
        if (RewardLifetimeSeconds < 60) RewardLifetimeSeconds = 60;
        if (DespawnWarningEnabled != 0) DespawnWarningEnabled = 1;
        if (DespawnWarningSeconds < 0) DespawnWarningSeconds = 0;
    }
}

class DeutschZKotHZEventTestingSettings
{
    int FastTestMode;
    int CaptureHoldSeconds;
    int RequiredKillsToWin;
    int HackDurationSeconds;
    int WaveDelaySeconds;
    int StageAutoCompleteSeconds;
    int FinalDefenseSeconds;
    int ExtractionDurationSeconds;

    void DeutschZKotHZEventTestingSettings()
    {
        FastTestMode = 1;
        CaptureHoldSeconds = 45;
        RequiredKillsToWin = 3;
        HackDurationSeconds = 30;
        WaveDelaySeconds = 30;
        StageAutoCompleteSeconds = 0;
        FinalDefenseSeconds = 120;
        ExtractionDurationSeconds = 30;
    }

    void Repair()
    {
        if (FastTestMode != 0) FastTestMode = 1;
        if (CaptureHoldSeconds < 5) CaptureHoldSeconds = 5;
        if (RequiredKillsToWin < 0) RequiredKillsToWin = 0;
        if (HackDurationSeconds < 5) HackDurationSeconds = 5;
        if (WaveDelaySeconds < 0) WaveDelaySeconds = 0;
        if (StageAutoCompleteSeconds < 0) StageAutoCompleteSeconds = 0;
        if (FinalDefenseSeconds < 30) FinalDefenseSeconds = 30;
        if (ExtractionDurationSeconds < 5) ExtractionDurationSeconds = 5;
    }
}

class DeutschZKotHZEventSettings
{
    int SchemaVersion;
    string PresetName;
    string ConfigMode;
    ref DeutschZKotHZEventCoreSettings Event;
    ref DeutschZKotHZEventSchedulingSettings Scheduling;
    ref DeutschZKotHZEventMarkerSettings Markers;
    ref DeutschZKotHZEventNotificationSettings Notifications;
    ref DeutschZKotHZEventRewardSettings Rewards;
    ref DeutschZKotHZEventTestingSettings Testing;

    void DeutschZKotHZEventSettings()
    {
        SchemaVersion = 1;
        PresetName = "FAST_TEST";
        ConfigMode = "FastRestartTest";
        Event = new DeutschZKotHZEventCoreSettings();
        Scheduling = new DeutschZKotHZEventSchedulingSettings();
        Markers = new DeutschZKotHZEventMarkerSettings();
        Notifications = new DeutschZKotHZEventNotificationSettings();
        Rewards = new DeutschZKotHZEventRewardSettings();
        Testing = new DeutschZKotHZEventTestingSettings();
        Repair("DeutschZ KotHZ", "Territory", "KotHZ_");
    }

    void Repair(string fallbackName, string fallbackIcon, string fallbackPrefix)
    {
        if (SchemaVersion < 1) SchemaVersion = 1;
        if (PresetName == "") PresetName = "FAST_TEST";
        if (ConfigMode == "") ConfigMode = "FastRestartTest";
        if (!Event) Event = new DeutschZKotHZEventCoreSettings();
        if (!Scheduling) Scheduling = new DeutschZKotHZEventSchedulingSettings();
        if (!Markers) Markers = new DeutschZKotHZEventMarkerSettings();
        if (!Notifications) Notifications = new DeutschZKotHZEventNotificationSettings();
        if (!Rewards) Rewards = new DeutschZKotHZEventRewardSettings();
        if (!Testing) Testing = new DeutschZKotHZEventTestingSettings();
        Event.Repair();
        Scheduling.Repair();
        Markers.Repair(fallbackName, fallbackIcon, fallbackPrefix);
        Notifications.Repair();
        Rewards.Repair();
        Testing.Repair();
    }
}

class DeutschZKotHZConfig
{
    ref DeutschZKotHZEventSettings DeutschZEventSettings;
    string ConfigInfo;
    string EditHint;
    string OwnerName;
    string OwnerPlayerName;
    string ServerName;
    string OwnershipNotice;
    string MarkerEditHint;
    int EnableKOTH;
    int MaxSimultaneousEvents;
    int MinStartDelayMinutes;
    int MaxStartDelayMinutes;
    int MinPlayersToStart;
    int AnnounceEvent;
    int DebugMode;
    int EnableHUD;
    int HUDUpdateIntervalSeconds;
    int EnableProgressHUD;
    int EnableHUDDistanceLimit;
    float HUDMaxDisplayDistanceMeters;
    int EnableExpansionNotifications;
    int EnableExpansionMarker;
    int EnableExpansion3DMarker;
    int EnableVanillaNotifications;
    int EnableVanillaChatMessages;
    int EnableMarkerFallbackNotifications;
    string MarkerMode;
    int ExpansionMarkerColorARGB;
    string ExpansionMarkerIcon;
    int RewardCrateMinimumLifetimeSeconds;
    int EnableRewardCrateDespawnWarning;
    int RewardCrateDespawnWarningSeconds;
    string RewardCrateDespawnWarningText;
    int EnableWinFireworks;
    string WinFireworkClassName;
    int WinFireworkCount;
    float WinFireworkRadius;
    float WinFireworkHeightOffset;
    int EnableHelicopterRewardDelivery;
    string DeliveryHelicopterClassName;
    float DeliveryHelicopterHeight;
    float DeliveryHelicopterOffsetDistance;
    float DeliveryCrateDropHeight;
    float DeliveryCrateDropDelaySeconds;
    float DeliveryHelicopterCleanupSeconds;
    float DeliveryCrateLandingConfirmSeconds;
    int EnableEventMusic;
    string EventMusicSoundSetName;
    int EventMusicPlayOnReady;
    int EventMusicPlayOnStart;
    int EventMusicPlayOnCaptured;
    float EventMusicRadius;
    float EventMusicVolume;
    ref array<ref DeutschZKotHZZone> Zones;
    ref array<ref DeutschZKotHZReward> Rewards; // fallback reward list
    ref array<ref DeutschZKotHZWavePool> WavePools;
    ref DeutschZKotHZNPCConfig NPC;
    ref DeutschZKotHZSmokeConfig Smoke;
    ref DeutschZKotHZZombieConfig Zombies;


    void EnsureDeutschZEventSettings()
    {
        if (!DeutschZEventSettings)
            DeutschZEventSettings = new DeutschZKotHZEventSettings();
        DeutschZEventSettings.Repair("DeutschZ KotHZ", "Territory", "KotHZ_");
    }

    int DeutschZSecondsToMinutes(int seconds)
    {
        if (seconds <= 0) return 1;
        int minutes = seconds / 60;
        if (minutes < 1) minutes = 1;
        if ((minutes * 60) < seconds) minutes = minutes + 1;
        return minutes;
    }

    void ApplyDeutschZEventSettings()
    {
        EnsureDeutschZEventSettings();
        EnableKOTH = DeutschZEventSettings.Event.Enabled;
        MaxSimultaneousEvents = DeutschZEventSettings.Event.MaxSimultaneousEvents;
        MinPlayersToStart = DeutschZEventSettings.Event.MinOnlinePlayers;
        DebugMode = DeutschZEventSettings.Event.DebugLogs;
        MinStartDelayMinutes = DeutschZSecondsToMinutes(DeutschZEventSettings.Scheduling.StartDelayMinSeconds);
        MaxStartDelayMinutes = DeutschZSecondsToMinutes(DeutschZEventSettings.Scheduling.StartDelayMaxSeconds);
        if (MaxStartDelayMinutes < MinStartDelayMinutes) MaxStartDelayMinutes = MinStartDelayMinutes;

        if (DeutschZEventSettings.Markers.Enabled == 0)
        {
            MarkerMode = "Off";
            EnableExpansionMarker = 0;
            EnableExpansion3DMarker = 0;
        }
        else
        {
            MarkerMode = "Expansion";
            EnableExpansionMarker = DeutschZEventSettings.Markers.UseMapMarker;
            EnableExpansion3DMarker = DeutschZEventSettings.Markers.Use3DMarker;
        }

        EnableExpansionNotifications = DeutschZEventSettings.Notifications.Enabled * DeutschZEventSettings.Notifications.UseExpansionNotifications;
        EnableVanillaNotifications = DeutschZEventSettings.Notifications.Enabled * DeutschZEventSettings.Notifications.UseVanillaNotifications;
        EnableVanillaChatMessages = DeutschZEventSettings.Notifications.Enabled * DeutschZEventSettings.Notifications.UseChatMessages;
        EnableMarkerFallbackNotifications = 0;
        AnnounceEvent = DeutschZEventSettings.Notifications.Enabled;
        RewardCrateMinimumLifetimeSeconds = DeutschZEventSettings.Rewards.RewardLifetimeSeconds;
        EnableRewardCrateDespawnWarning = DeutschZEventSettings.Rewards.DespawnWarningEnabled;
        RewardCrateDespawnWarningSeconds = DeutschZEventSettings.Rewards.DespawnWarningSeconds;

        foreach (DeutschZKotHZZone zone: Zones)
        {
            if (!zone) continue;
            if (DeutschZEventSettings.Testing.FastTestMode == 1)
                zone.CaptureTimeSeconds = DeutschZEventSettings.Testing.CaptureHoldSeconds;
        }
    }

    void DeutschZKotHZConfig()
    {
        DeutschZEventSettings = new DeutschZKotHZEventSettings();
        ConfigInfo = "DeutschZ_KotHZ FIX23 fast-test config. Event music is disabled; marker/3D-marker intent and Bridge popup/chat fallbacks are enabled.";
        EditHint = "TESTVERSION: starts after 1 minute, capture time is reduced, and all zones use DeutschZ_Test_HighValue reward pool for quick loot testing. Do not use these fast timings as final live balance.";
        OwnerName = "Patrick Sluzalek";
        OwnerPlayerName = "fck1701";
        ServerName = "DeutschZ";
        OwnershipNotice = "DeutschZ_KotHZ is the custom KOTH framework owned and maintained by Patrick Sluzalek / fck1701 for the DeutschZ server.";
        EnableKOTH = 1;
        MaxSimultaneousEvents = 1;
        MinStartDelayMinutes = 1;
        MaxStartDelayMinutes = 1;
        MinPlayersToStart = 1;
        AnnounceEvent = 1;
        DebugMode = 1;
        EnableHUD = 1;
        HUDUpdateIntervalSeconds = 1;
        EnableProgressHUD = 1;
        EnableHUDDistanceLimit = 1;
        HUDMaxDisplayDistanceMeters = 500.0;
        EnableExpansionNotifications = 1;
        EnableExpansionMarker = 1;
        EnableExpansion3DMarker = 1;
        EnableVanillaNotifications = 1;
        EnableVanillaChatMessages = 1;
        EnableMarkerFallbackNotifications = 1;
        MarkerMode = "Expansion";
        MarkerEditHint = "DeutschZ KotHZ test default: map marker and 3D marker enabled through DeutschZ_ExpansionBridge; vanilla popup and chat fallback enabled so players always see event messages.";
        ExpansionMarkerColorARGB = ARGB(255, 255, 0, 0);
        ExpansionMarkerIcon = "Territory";
        RewardCrateMinimumLifetimeSeconds = 1800;
        EnableRewardCrateDespawnWarning = 1;
        RewardCrateDespawnWarningSeconds = 300;
        RewardCrateDespawnWarningText = "KotH Reward-Crate despawnt in 5 Minuten: {ZONE}.";
        EnableWinFireworks = 0;
        WinFireworkClassName = "FireworksLauncher";
        WinFireworkCount = 3;
        WinFireworkRadius = 6.0;
        WinFireworkHeightOffset = 0.0;
        EnableHelicopterRewardDelivery = 0;
        DeliveryHelicopterClassName = "";
        DeliveryHelicopterHeight = 35.0;
        DeliveryHelicopterOffsetDistance = 120.0;
        DeliveryCrateDropHeight = 8.0;
        DeliveryCrateDropDelaySeconds = 2.0;
        DeliveryHelicopterCleanupSeconds = 25.0;
        DeliveryCrateLandingConfirmSeconds = 10.0;
        EnableEventMusic = 0;
        EventMusicSoundSetName = "";
        EventMusicPlayOnReady = 0;
        EventMusicPlayOnStart = 0;
        EventMusicPlayOnCaptured = 0;
        EventMusicRadius = 0.0;
        EventMusicVolume = 0.0;

        Zones = new array<ref DeutschZKotHZZone>;
        Rewards = new array<ref DeutschZKotHZReward>;
        WavePools = new array<ref DeutschZKotHZWavePool>;
        NPC = new DeutschZKotHZNPCConfig();
        Smoke = new DeutschZKotHZSmokeConfig();
        Zombies = new DeutschZKotHZZombieConfig();

        DeutschZKotHZZone nwaf = new DeutschZKotHZZone();
        nwaf.EditHint = "NWAF fast-test zone. Marker shows KotH - NWAF. Uses NWAF flag and NWAF_Military_Zombies wave pool.";
        nwaf.ZoneName = "NWAF";
        nwaf.Position = "4308.396484 339.136292 10734.681641";
        nwaf.FlagpolePosition = "4308.396484 339.136292 10734.681641";
        nwaf.FlagpoleOrientation = "-149.268600 0 0";
        nwaf.UseExactRewardCratePosition = 0;
        nwaf.RewardCratePosition = "4314.396484 339.136292 10740.681641";
        nwaf.RewardCrateOrientation = "128.947662 0 0";
        nwaf.Radius = 25.0;
        nwaf.CaptureTimeSeconds = 90;
        nwaf.FlagpoleClassName = "DeutschZKotHZ_RuntimeFlagpole";
        nwaf.FlagClassName = "DeutschZKotHZ_NWAF_Flag";
        nwaf.FlagVisualHeightOffset = 13.0;
        nwaf.EnableOptionalNPC = 0;
        nwaf.EnableZombieSpawns = 1;
        nwaf.InitialZombieSpawnCount = 0;
        nwaf.ZombieWaveCount = 3;
        nwaf.ZombiesPerWave = 4;
        nwaf.MaxTotalZombies = 18;
        nwaf.ZombieSpawnMinDistance = 18.0;
        nwaf.ZombieSpawnMaxDistance = 42.0;
        nwaf.EnableCrashedHeliDecoration = 0;
        nwaf.CrashedHeliClassName = "Wreck_Mi8";
        nwaf.CrashedHeliOffset = "16 0 10";
        nwaf.CrashedHeliOrientation = "35 0 0";
        nwaf.RewardPoolName = "DeutschZ_Test_HighValue";
        nwaf.WavePoolName = "KVM1_Test_5x6_Zombies";
        nwaf.StartWavesOnlyWhenPlayerInside = 1;
        nwaf.SpawnOutdoorOnly = 1;
        nwaf.NPCAmount = 0;
        Zones.Insert(nwaf);

        DeutschZKotHZZone tisy = new DeutschZKotHZZone();
        tisy.EditHint = "Tisy zone from Patrick's imported config. Uses Tisy flag and light military waves.";
        tisy.ZoneName = "Tisy";
        tisy.Position = "1677.211426 451.730042 14353.850586";
        tisy.FlagpolePosition = "1677.211426 451.730042 14353.850586";
        tisy.FlagpoleOrientation = "0 0 0";
        tisy.UseExactRewardCratePosition = 0;
        tisy.RewardCratePosition = "1683.211426 451.730042 14359.850586";
        tisy.RewardCrateOrientation = "0 0 0";
        tisy.Radius = 25.0;
        tisy.CaptureTimeSeconds = 90;
        tisy.RewardPoolName = "DeutschZ_Test_HighValue";
        tisy.FlagpoleClassName = "DeutschZKotHZ_RuntimeFlagpole";
        tisy.FlagClassName = "DeutschZKotHZ_Tisy_Flag";
        tisy.FlagVisualHeightOffset = 13.0;
        tisy.EnableOptionalNPC = 0;
        tisy.EnableZombieSpawns = 1;
        tisy.InitialZombieSpawnCount = 0;
        tisy.ZombieWaveCount = 3;
        tisy.ZombiesPerWave = 4;
        tisy.MaxTotalZombies = 18;
        tisy.ZombieSpawnMinDistance = 18.0;
        tisy.ZombieSpawnMaxDistance = 42.0;
        tisy.EnableCrashedHeliDecoration = 0;
        tisy.CrashedHeliClassName = "Wreck_Mi8";
        tisy.CrashedHeliOffset = "16 0 10";
        tisy.CrashedHeliOrientation = "35 0 0";
        tisy.WavePoolName = "KVM1_Test_5x6_Zombies";
        tisy.StartWavesOnlyWhenPlayerInside = 1;
        tisy.SpawnOutdoorOnly = 1;
        tisy.NPCAmount = 0;
        Zones.Insert(tisy);

        DeutschZKotHZZone lopa = new DeutschZKotHZZone();
        lopa.EditHint = "Lopatino Military zone from Patrick's imported config. Marker shows KotH - LOPA.";
        lopa.ZoneName = "LOPA";
        lopa.Position = "2933.669922 271.157990 9686.360352";
        lopa.FlagpolePosition = "2933.669922 271.157990 9686.360352";
        lopa.FlagpoleOrientation = "153.363007 0 0";
        lopa.UseExactRewardCratePosition = 0;
        lopa.RewardCratePosition = "2939.669922 271.157990 9692.360352";
        lopa.RewardCrateOrientation = "153.363007 0 0";
        lopa.Radius = 25.0;
        lopa.CaptureTimeSeconds = 90;
        lopa.RewardPoolName = "DeutschZ_Test_HighValue";
        lopa.FlagpoleClassName = "DeutschZKotHZ_RuntimeFlagpole";
        lopa.FlagClassName = "DeutschZKotHZ_LOPA_Flag";
        lopa.FlagVisualHeightOffset = 13.0;
        lopa.EnableOptionalNPC = 0;
        lopa.EnableZombieSpawns = 1;
        lopa.InitialZombieSpawnCount = 0;
        lopa.ZombieWaveCount = 3;
        lopa.ZombiesPerWave = 4;
        lopa.MaxTotalZombies = 18;
        lopa.ZombieSpawnMinDistance = 18.0;
        lopa.ZombieSpawnMaxDistance = 42.0;
        lopa.EnableCrashedHeliDecoration = 0;
        lopa.CrashedHeliClassName = "Wreck_Mi8";
        lopa.CrashedHeliOffset = "16 0 10";
        lopa.CrashedHeliOrientation = "35 0 0";
        lopa.WavePoolName = "KVM1_Test_5x6_Zombies";
        lopa.StartWavesOnlyWhenPlayerInside = 1;
        lopa.SpawnOutdoorOnly = 1;
        lopa.NPCAmount = 0;
        Zones.Insert(lopa);

        DeutschZKotHZZone yrap = new DeutschZKotHZZone();
        yrap.EditHint = "YRAP Military Depot zone from Patrick's imported config. Marker shows KotH - YRAP.";
        yrap.ZoneName = "YRAP";
        yrap.Position = "1236.432861 189.384430 5803.604492";
        yrap.FlagpolePosition = "1236.432861 189.384430 5803.604492";
        yrap.FlagpoleOrientation = "0 0 0";
        yrap.UseExactRewardCratePosition = 0;
        yrap.RewardCratePosition = "1242.432861 189.384430 5809.604492";
        yrap.RewardCrateOrientation = "0 0 0";
        yrap.Radius = 25.0;
        yrap.CaptureTimeSeconds = 90;
        yrap.RewardPoolName = "DeutschZ_Test_HighValue";
        yrap.FlagpoleClassName = "DeutschZKotHZ_RuntimeFlagpole";
        yrap.FlagClassName = "DeutschZKotHZ_YRAP_Flag";
        yrap.FlagVisualHeightOffset = 13.0;
        yrap.EnableOptionalNPC = 0;
        yrap.EnableZombieSpawns = 1;
        yrap.InitialZombieSpawnCount = 0;
        yrap.ZombieWaveCount = 3;
        yrap.ZombiesPerWave = 4;
        yrap.MaxTotalZombies = 18;
        yrap.ZombieSpawnMinDistance = 18.0;
        yrap.ZombieSpawnMaxDistance = 42.0;
        yrap.EnableCrashedHeliDecoration = 0;
        yrap.CrashedHeliClassName = "Wreck_Mi8";
        yrap.CrashedHeliOffset = "16 0 10";
        yrap.CrashedHeliOrientation = "35 0 0";
        yrap.WavePoolName = "KVM1_Test_5x6_Zombies";
        yrap.StartWavesOnlyWhenPlayerInside = 1;
        yrap.SpawnOutdoorOnly = 1;
        yrap.NPCAmount = 0;
        Zones.Insert(yrap);

        DeutschZKotHZZone zeleno = new DeutschZKotHZZone();
        zeleno.EditHint = "Zeleno Basebuilding test zone. Uses vanilla test loot and KVM1 5x6 infected waves.";
        zeleno.ZoneName = "Zeleno Bau KotH Bauloot";
        zeleno.Position = "2282.993896 185.358643 5235.256836";
        zeleno.FlagpolePosition = "2282.993896 185.358643 5235.256836";
        zeleno.FlagpoleOrientation = "18.000002 0 0";
        zeleno.UseExactRewardCratePosition = 0;
        zeleno.RewardCratePosition = "2261.855469 186.022064 5231.586426";
        zeleno.RewardCrateOrientation = "18.000002 0 0";
        zeleno.Radius = 25.0;
        zeleno.CaptureTimeSeconds = 90;
        zeleno.RewardPoolName = "DeutschZ_Test_HighValue";
        zeleno.FlagpoleClassName = "DeutschZKotHZ_RuntimeFlagpole";
        zeleno.FlagClassName = "DeutschZKotHZ_Basebuild_Flag";
        zeleno.FlagVisualHeightOffset = 13.0;
        zeleno.EnableOptionalNPC = 0;
        zeleno.EnableZombieSpawns = 1;
        zeleno.InitialZombieSpawnCount = 0;
        zeleno.ZombieWaveCount = 3;
        zeleno.ZombiesPerWave = 4;
        zeleno.MaxTotalZombies = 18;
        zeleno.ZombieSpawnMinDistance = 18.0;
        zeleno.ZombieSpawnMaxDistance = 42.0;
        zeleno.EnableCrashedHeliDecoration = 0;
        zeleno.CrashedHeliClassName = "Wreck_Mi8";
        zeleno.CrashedHeliOffset = "16 0 10";
        zeleno.CrashedHeliOrientation = "35 0 0";
        zeleno.WavePoolName = "KVM1_Test_5x6_Zombies";
        zeleno.StartWavesOnlyWhenPlayerInside = 1;
        zeleno.SpawnOutdoorOnly = 1;
        zeleno.NPCAmount = 0;
        Zones.Insert(zeleno);

        DeutschZKotHZZone topolniki = new DeutschZKotHZZone();
        topolniki.EditHint = "Topolniki Basebuilding test zone. Uses vanilla test loot and KVM1 5x6 infected waves.";
        topolniki.ZoneName = "Topolniki Basebuilding KotH";
        topolniki.Position = "2875.519531 214.763733 12652.452148";
        topolniki.FlagpolePosition = "2875.519531 214.763733 12652.452148";
        topolniki.FlagpoleOrientation = "0 0 0";
        topolniki.UseExactRewardCratePosition = 0;
        topolniki.RewardCratePosition = "2879.519531 214.763733 12656.452148";
        topolniki.RewardCrateOrientation = "0 0 0";
        topolniki.Radius = 25.0;
        topolniki.CaptureTimeSeconds = 90;
        topolniki.RewardPoolName = "DeutschZ_Test_HighValue";
        topolniki.FlagpoleClassName = "DeutschZKotHZ_RuntimeFlagpole";
        topolniki.FlagClassName = "DeutschZKotHZ_Basebuild_Flag";
        topolniki.FlagVisualHeightOffset = 13.0;
        topolniki.EnableOptionalNPC = 0;
        topolniki.EnableZombieSpawns = 1;
        topolniki.InitialZombieSpawnCount = 0;
        topolniki.ZombieWaveCount = 3;
        topolniki.ZombiesPerWave = 4;
        topolniki.MaxTotalZombies = 18;
        topolniki.ZombieSpawnMinDistance = 18.0;
        topolniki.ZombieSpawnMaxDistance = 42.0;
        topolniki.EnableCrashedHeliDecoration = 0;
        topolniki.CrashedHeliClassName = "Wreck_Mi8";
        topolniki.CrashedHeliOffset = "16 0 10";
        topolniki.CrashedHeliOrientation = "35 0 0";
        topolniki.WavePoolName = "KVM1_Test_5x6_Zombies";
        topolniki.StartWavesOnlyWhenPlayerInside = 1;
        topolniki.SpawnOutdoorOnly = 1;
        topolniki.NPCAmount = 0;
        Zones.Insert(topolniki);

        DeutschZKotHZZone berenzinho = new DeutschZKotHZZone();
        berenzinho.EditHint = "Berenzinho Basebuilding test zone. Uses vanilla test loot and KVM1 5x6 infected waves.";
        berenzinho.ZoneName = "Berenzinho Basebuilding KotH";
        berenzinho.Position = "12802.842773 6.008640 9668.188477";
        berenzinho.FlagpolePosition = "12802.842773 6.008640 9668.188477";
        berenzinho.FlagpoleOrientation = "36.000004 0 0";
        berenzinho.UseExactRewardCratePosition = 0;
        berenzinho.RewardCratePosition = "12806.842773 6.008640 9672.188477";
        berenzinho.RewardCrateOrientation = "36.000004 0 0";
        berenzinho.Radius = 25.0;
        berenzinho.CaptureTimeSeconds = 90;
        berenzinho.RewardPoolName = "DeutschZ_Test_HighValue";
        berenzinho.FlagpoleClassName = "DeutschZKotHZ_RuntimeFlagpole";
        berenzinho.FlagClassName = "DeutschZKotHZ_Basebuild_Flag";
        berenzinho.FlagVisualHeightOffset = 13.0;
        berenzinho.EnableOptionalNPC = 0;
        berenzinho.EnableZombieSpawns = 1;
        berenzinho.InitialZombieSpawnCount = 0;
        berenzinho.ZombieWaveCount = 3;
        berenzinho.ZombiesPerWave = 4;
        berenzinho.MaxTotalZombies = 18;
        berenzinho.ZombieSpawnMinDistance = 18.0;
        berenzinho.ZombieSpawnMaxDistance = 42.0;
        berenzinho.EnableCrashedHeliDecoration = 0;
        berenzinho.CrashedHeliClassName = "Wreck_Mi8";
        berenzinho.CrashedHeliOffset = "16 0 10";
        berenzinho.CrashedHeliOrientation = "35 0 0";
        berenzinho.WavePoolName = "KVM1_Test_5x6_Zombies";
        berenzinho.StartWavesOnlyWhenPlayerInside = 1;
        berenzinho.SpawnOutdoorOnly = 1;
        berenzinho.NPCAmount = 0;
        Zones.Insert(berenzinho);

        Rewards.Insert(new DeutschZKotHZReward());

        DeutschZKotHZWavePoolsConfig defaultWavePools = new DeutschZKotHZWavePoolsConfig();
        WavePools = defaultWavePools.WavePools;
    }
}
