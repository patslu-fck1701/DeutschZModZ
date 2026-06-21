/*
    DeutschZ_CourierZ - JSON config.
    Uses the same DeutschZEventSettings block naming as KotHZ, ConvoyZ and GroundZero.
*/

class CourierZEventCoreSettings
{
    int Enabled;
    int MinOnlinePlayers;
    int MaxSimultaneousEvents;
    int MaxEventsPerRestart;
    int MaxRuntimeSeconds;
    int CleanupDelaySeconds;
    int DebugLogs;

    void CourierZEventCoreSettings()
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
        if (MaxRuntimeSeconds < 60) MaxRuntimeSeconds = 60;
        if (CleanupDelaySeconds < 0) CleanupDelaySeconds = 0;
        if (DebugLogs != 0) DebugLogs = 1;
    }
}

class CourierZEventSchedulingSettings
{
    int AutoStartAfterRestart;
    int StartDelayMinSeconds;
    int StartDelayMaxSeconds;
    int RestartAfterFinish;
    int RestartDelayMinSeconds;
    int RestartDelayMaxSeconds;
    int NoPlayerRetryDelaySeconds;

    void CourierZEventSchedulingSettings()
    {
        AutoStartAfterRestart = 1;
        StartDelayMinSeconds = 1200;
        StartDelayMaxSeconds = 1200;
        RestartAfterFinish = 1;
        RestartDelayMinSeconds = 2100;
        RestartDelayMaxSeconds = 2100;
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
        if (NoPlayerRetryDelaySeconds < 15) NoPlayerRetryDelaySeconds = 15;
    }
}

class CourierZEventMarkerSettings
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

    void CourierZEventMarkerSettings()
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
        MarkerName = "DeutschZ CourierZ";
        MarkerIcon = "Deliver";
        MarkerColorARGB = -65536;
        MarkerPrefix = "CourierZ_";
    }

    void Repair()
    {
        if (Enabled != 0) Enabled = 1;
        if (UseMapMarker != 0) UseMapMarker = 1;
        if (Use3DMarker != 0) Use3DMarker = 1;
        if (UseDynamicPositionUpdates != 0) UseDynamicPositionUpdates = 1;
        if (UpdateIntervalSeconds < 3) UpdateIntervalSeconds = 3;
        if (ShowEventRadius != 0) ShowEventRadius = 1;
        if (ShowCarrierMarker != 0) ShowCarrierMarker = 1;
        if (ShowDroppedItemMarker != 0) ShowDroppedItemMarker = 1;
        if (ShowFinalMarker != 0) ShowFinalMarker = 1;
        if (ShowExtractionMarker != 0) ShowExtractionMarker = 1;
        if (MarkerName == "") MarkerName = "DeutschZ CourierZ";
        if (MarkerIcon == "") MarkerIcon = "Deliver";
        if (MarkerColorARGB == 0) MarkerColorARGB = -65536;
        if (MarkerPrefix == "") MarkerPrefix = "CourierZ_";
    }
}

class CourierZEventNotificationSettings
{
    int Enabled;
    int UseExpansionNotifications;
    int UseVanillaNotifications;
    int UseChatMessages;
    int StatusNotifications;
    int StatusIntervalSeconds;

    void CourierZEventNotificationSettings()
    {
        Enabled = 1;
        UseExpansionNotifications = 1;
        UseVanillaNotifications = 1;
        UseChatMessages = 1;
        StatusNotifications = 1;
        StatusIntervalSeconds = 60;
    }

    void Repair()
    {
        if (Enabled != 0) Enabled = 1;
        if (UseExpansionNotifications != 0) UseExpansionNotifications = 1;
        if (UseVanillaNotifications != 0) UseVanillaNotifications = 1;
        if (UseChatMessages != 0) UseChatMessages = 1;
        if (StatusNotifications != 0) StatusNotifications = 1;
        if (StatusIntervalSeconds < 5) StatusIntervalSeconds = 5;
    }
}

class CourierZEventTestingSettings
{
    int FastTestMode;
    int CaptureHoldSeconds;
    int RequiredKillsToWin;
    int HackDurationSeconds;
    int WaveDelaySeconds;
    int StageAutoCompleteSeconds;
    int FinalDefenseSeconds;
    int ExtractionDurationSeconds;

    void CourierZEventTestingSettings()
    {
        FastTestMode = 1;
        CaptureHoldSeconds = 30;
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
        if (HackDurationSeconds < 0) HackDurationSeconds = 0;
        if (WaveDelaySeconds < 5) WaveDelaySeconds = 5;
        if (StageAutoCompleteSeconds < 0) StageAutoCompleteSeconds = 0;
        if (FinalDefenseSeconds < 30) FinalDefenseSeconds = 30;
        if (ExtractionDurationSeconds < 5) ExtractionDurationSeconds = 5;
    }
}

class CourierZUnifiedEventSettings
{
    ref CourierZEventCoreSettings Event;
    ref CourierZEventSchedulingSettings Scheduling;
    ref CourierZEventMarkerSettings Markers;
    ref CourierZEventNotificationSettings Notifications;
    ref CourierZEventTestingSettings Testing;

    void CourierZUnifiedEventSettings()
    {
        Event = new CourierZEventCoreSettings;
        Scheduling = new CourierZEventSchedulingSettings;
        Markers = new CourierZEventMarkerSettings;
        Notifications = new CourierZEventNotificationSettings;
        Testing = new CourierZEventTestingSettings;
    }

    void Repair()
    {
        if (!Event) Event = new CourierZEventCoreSettings;
        if (!Scheduling) Scheduling = new CourierZEventSchedulingSettings;
        if (!Markers) Markers = new CourierZEventMarkerSettings;
        if (!Notifications) Notifications = new CourierZEventNotificationSettings;
        if (!Testing) Testing = new CourierZEventTestingSettings;
        Event.Repair();
        Scheduling.Repair();
        Markers.Repair();
        Notifications.Repair();
        Testing.Repair();
    }
}

class CourierZSpecificSettings
{
    int RequireQuestItem;
    int RequireContactNPC;
    int EnableCourierPvPMarker;
    int CarrierOnlyKnowsDestination;
    int PublicCarrierMarkerDelaySeconds;
    int DropCaseOnDeath;
    int DropCaseOnLogout;
    int PreventStorageTransfer;
    int DeliveryTimeLimitSeconds;
    int AllowPickupByOtherPlayers;
    int RewardOnDelivery;
    int FailOnTimeExpired;
    int CleanupDroppedCaseAfterSeconds;
    float PickupRadius;
    float DeliveryRadius;
    float EnemySpawnRadius;

    void CourierZSpecificSettings()
    {
        RequireQuestItem = 0;
        RequireContactNPC = 0;
        EnableCourierPvPMarker = 1;
        CarrierOnlyKnowsDestination = 1;
        PublicCarrierMarkerDelaySeconds = 300;
        DropCaseOnDeath = 1;
        DropCaseOnLogout = 1;
        PreventStorageTransfer = 1;
        DeliveryTimeLimitSeconds = 1800;
        AllowPickupByOtherPlayers = 1;
        RewardOnDelivery = 1;
        FailOnTimeExpired = 1;
        CleanupDroppedCaseAfterSeconds = 1800;
        PickupRadius = 5.0;
        DeliveryRadius = 10.0;
        EnemySpawnRadius = 35.0;
    }

    void Repair()
    {
        if (RequireQuestItem != 0) RequireQuestItem = 1;
        if (RequireContactNPC != 0) RequireContactNPC = 1;
        if (EnableCourierPvPMarker != 0) EnableCourierPvPMarker = 1;
        if (CarrierOnlyKnowsDestination != 0) CarrierOnlyKnowsDestination = 1;
        if (PublicCarrierMarkerDelaySeconds < 0) PublicCarrierMarkerDelaySeconds = 0;
        if (DropCaseOnDeath != 0) DropCaseOnDeath = 1;
        if (DropCaseOnLogout != 0) DropCaseOnLogout = 1;
        if (PreventStorageTransfer != 0) PreventStorageTransfer = 1;
        if (DeliveryTimeLimitSeconds < 60) DeliveryTimeLimitSeconds = 60;
        if (AllowPickupByOtherPlayers != 0) AllowPickupByOtherPlayers = 1;
        if (RewardOnDelivery != 0) RewardOnDelivery = 1;
        if (FailOnTimeExpired != 0) FailOnTimeExpired = 1;
        if (CleanupDroppedCaseAfterSeconds < 60) CleanupDroppedCaseAfterSeconds = 60;
        if (PickupRadius < 2.0) PickupRadius = 2.0;
        if (DeliveryRadius < 2.0) DeliveryRadius = 2.0;
        if (EnemySpawnRadius < 5.0) EnemySpawnRadius = 5.0;
    }
}

class CourierZConfig
{
    int ConfigVersion;
    string PresetName;
    ref CourierZUnifiedEventSettings DeutschZEventSettings;
    ref CourierZSpecificSettings Courier;

    vector ContactPosition;
    vector DeliveryPosition;
    vector ContactOrientation;
    vector DeliveryOrientation;
    string CaseClassName;
    string RewardChestClassName;
    string EnemyClassName;
    int StartEnemyCount;
    int DeliveryEnemyCount;
    ref array<string> RewardItems;

    void CourierZConfig()
    {
        SetDefaults();
    }

    void SetDefaults()
    {
        ConfigVersion = 1;
        PresetName = "STAGGERED_TEST_FIX25_COURIERZ";
        DeutschZEventSettings = new CourierZUnifiedEventSettings;
        Courier = new CourierZSpecificSettings;
        ContactPosition = "7500 0 7500";
        DeliveryPosition = "7800 0 7800";
        ContactOrientation = "0 0 0";
        DeliveryOrientation = "0 0 0";
        CaseClassName = "DZCR_Aktenkoffer";
        RewardChestClassName = "DZCR_RewardChest";
        EnemyClassName = "ZmbM_usSoldier_Officer_Desert";
        StartEnemyCount = 3;
        DeliveryEnemyCount = 3;
        RewardItems = new array<string>;
        RewardItems.Insert("BandageDressing");
        RewardItems.Insert("TacticalBaconCan");
        RewardItems.Insert("Ammo_556x45");
    }

    void Repair()
    {
        if (!DeutschZEventSettings) DeutschZEventSettings = new CourierZUnifiedEventSettings;
        if (!Courier) Courier = new CourierZSpecificSettings;
        if (!RewardItems) RewardItems = new array<string>;
        DeutschZEventSettings.Repair();
        Courier.Repair();
        if (ConfigVersion < 1) ConfigVersion = 1;
        if (PresetName == "") PresetName = "STAGGERED_TEST_FIX25_COURIERZ";
        if (CaseClassName == "") CaseClassName = "DZCR_Aktenkoffer";
        if (RewardChestClassName == "") RewardChestClassName = "DZCR_RewardChest";
        if (EnemyClassName == "") EnemyClassName = "ZmbM_usSoldier_Officer_Desert";
        if (StartEnemyCount < 0) StartEnemyCount = 0;
        if (DeliveryEnemyCount < 0) DeliveryEnemyCount = 0;
        if (RewardItems.Count() < 1) RewardItems.Insert("BandageDressing");
    }

    static CourierZConfig Load()
    {
        CourierZPersistence.EnsureProfileDirs();
        CourierZConfig cfg = new CourierZConfig;
        if (!FileExist(CourierZConstants.CONFIG_PATH))
        {
            cfg.Save();
            DeutschZCore_Log.Info(CourierZConstants.LOG_SCOPE, "created default CourierZ config");
            return cfg;
        }

        JsonFileLoader<CourierZConfig>.JsonLoadFile(CourierZConstants.CONFIG_PATH, cfg);
        cfg.Repair();
        cfg.Save();
        DeutschZCore_Log.Info(CourierZConstants.LOG_SCOPE, "loaded config preset=" + cfg.PresetName);
        return cfg;
    }

    void Save()
    {
        CourierZPersistence.EnsureProfileDirs();
        JsonFileLoader<CourierZConfig>.JsonSaveFile(CourierZConstants.CONFIG_PATH, this);
    }
}
