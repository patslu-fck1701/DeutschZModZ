/*
DeutschZ ModZ
Eigenstaendige Implementierung fuer DeutschZ.
Autor/Eigentuemer: Patrick Sluzalek / fck1701.
Projekt: DeutschZ.
Modul: DeutschZ_ConvoyZ.
Zweck der Datei: Eigene DeutschZ-Datenmodelle und Runtime-State fuer ConvoyZ.
Quellen-/Konzeptnachweis: Eigene DeutschZ-Implementierung; DayZ/CF/Expansion werden nur als Laufzeit-Abhaengigkeit/API genutzt.
Keine direkte Codeuebernahme aus Drittquellen.
*/

class DeutschZConvoyZSpawnPoint
{
    vector Position;
    vector Orientation;

    void DeutschZConvoyZSpawnPoint()
    {
        Position = "0 0 0";
        Orientation = "0 0 0";
    }
}

class DeutschZConvoyZObjectDef
{
    string ClassName;
    vector Position;
    vector Orientation;
    int Critical;

    void DeutschZConvoyZObjectDef()
    {
        ClassName = "";
        Position = "0 0 0";
        Orientation = "0 0 0";
        Critical = 1;
    }
}

class DeutschZConvoyZVehicleDef: DeutschZConvoyZObjectDef
{
    // FIX26: Compatibility wrapper only.
    // This static ConvoyZ build does not spawn, lock, damage, fuel or prepare drivable vehicles.
    // Old Vehicles entries are converted to CrashObjects in Normalize() and then cleared.
}

class DeutschZConvoyZBlackboxDef: DeutschZConvoyZObjectDef
{
    void DeutschZConvoyZBlackboxDef()
    {
        ClassName = "Land_HACKEDCRATE";
        Critical = 1;
    }
}

class DeutschZConvoyZSmokeDef
{
    vector Position;
    string RedSmokeClassName;
    string YellowSmokeClassName;
    string GreenSmokeClassName;
    string WhiteSmokeClassName;
    int Count;
    float Radius;
    int RefreshSeconds;

    void DeutschZConvoyZSmokeDef()
    {
        Position = "0 0 0";
        RedSmokeClassName = "M18SmokeGrenade_Red";
        YellowSmokeClassName = "M18SmokeGrenade_Yellow";
        GreenSmokeClassName = "M18SmokeGrenade_Green";
        WhiteSmokeClassName = "M18SmokeGrenade_White";
        Count = 4;
        Radius = 12.0;
        RefreshSeconds = 90;
    }
}

class DeutschZConvoyZAIWaveDef
{
    string WaveId;
    int DelaySeconds;
    int Count;
    string AIClassName;
    string DeutschZAIProfileId;
    string LoadoutName;
    ref array<ref DeutschZConvoyZSpawnPoint> SpawnPoints;

    void DeutschZConvoyZAIWaveDef()
    {
        WaveId = "wave";
        DelaySeconds = 0;
        Count = 5;
        AIClassName = DeutschZConvoyZConstants.DEFAULT_EXPANSION_AI_CLASS;
        DeutschZAIProfileId = "";
        LoadoutName = "PoliceLoadout";
        SpawnPoints = new array<ref DeutschZConvoyZSpawnPoint>;
    }
}

class DeutschZConvoyZRewardItemDef
{
    string ClassName;
    int Quantity;
    float Chance;

    void DeutschZConvoyZRewardItemDef()
    {
        ClassName = "";
        Quantity = 1;
        Chance = 1.0;
    }
}

class DeutschZConvoyZRewardDef
{
    string RewardContainerClassName;
    vector RewardPosition;
    vector RewardOrientation;
    ref array<ref DeutschZConvoyZRewardItemDef> Items;

    void DeutschZConvoyZRewardDef()
    {
        RewardContainerClassName = "DZCV_ProtectedCase";
        RewardPosition = "0 0 0";
        RewardOrientation = "0 0 0";
        Items = new array<ref DeutschZConvoyZRewardItemDef>;
    }
}

class DeutschZConvoyZEventDef
{
    string EventName;
    string EventIdPrefix;
    vector EventCenter;
    float EventRadius;
    ref array<ref DeutschZConvoyZVehicleDef> Vehicles;
    ref array<ref DeutschZConvoyZObjectDef> CrashObjects;
    ref DeutschZConvoyZBlackboxDef Blackbox;
    ref DeutschZConvoyZSmokeDef Smoke;
    ref array<ref DeutschZConvoyZAIWaveDef> AIWaves;
    int RequiredAiKills;
    int HackDurationSeconds;
    ref DeutschZConvoyZRewardDef Reward;

    void DeutschZConvoyZEventDef()
    {
        EventName = "DeutschZ_ConvoyZ Static Crash Event";
        EventIdPrefix = "convoyz_static_crash";
        EventCenter = "7500 0 7500";
        EventRadius = 450.0;
        Vehicles = new array<ref DeutschZConvoyZVehicleDef>;
        CrashObjects = new array<ref DeutschZConvoyZObjectDef>;
        Blackbox = new DeutschZConvoyZBlackboxDef();
        Smoke = new DeutschZConvoyZSmokeDef();
        AIWaves = new array<ref DeutschZConvoyZAIWaveDef>;
        RequiredAiKills = 15;
        HackDurationSeconds = 120;
        Reward = new DeutschZConvoyZRewardDef();
    }
}


// DeutschZ unified event config standard v1.
// Same JSON block name in every event config: DeutschZEventSettings.
class DeutschZConvoyZEventCoreSettings
{
    int Enabled;
    int MinOnlinePlayers;
    int MaxSimultaneousEvents;
    int MaxEventsPerRestart;
    int MaxRuntimeSeconds;
    int CleanupDelaySeconds;
    int DebugLogs;

    void DeutschZConvoyZEventCoreSettings()
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

class DeutschZConvoyZEventSchedulingSettings
{
    int AutoStartAfterRestart;
    int StartDelayMinSeconds;
    int StartDelayMaxSeconds;
    int RestartAfterFinish;
    int RestartDelayMinSeconds;
    int RestartDelayMaxSeconds;
    int NoPlayerRetryDelaySeconds;

    void DeutschZConvoyZEventSchedulingSettings()
    {
        AutoStartAfterRestart = 1;
        StartDelayMinSeconds = 600;
        StartDelayMaxSeconds = 600;
        RestartAfterFinish = 1;
        RestartDelayMinSeconds = 1500;
        RestartDelayMaxSeconds = 1500;
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

class DeutschZConvoyZEventMarkerSettings
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

    void DeutschZConvoyZEventMarkerSettings()
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
        MarkerName = "DeutschZ ConvoyZ Crash";
        MarkerIcon = "Vehicle Crash";
        MarkerColorARGB = -65536;
        MarkerPrefix = "ConvoyZ_";
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

class DeutschZConvoyZEventNotificationSettings
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

    void DeutschZConvoyZEventNotificationSettings()
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

class DeutschZConvoyZEventRewardSettings
{
    int Enabled;
    int RewardLifetimeSeconds;
    int DespawnWarningEnabled;
    int DespawnWarningSeconds;

    void DeutschZConvoyZEventRewardSettings()
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

class DeutschZConvoyZEventTestingSettings
{
    int FastTestMode;
    int CaptureHoldSeconds;
    int RequiredKillsToWin;
    int HackDurationSeconds;
    int WaveDelaySeconds;
    int StageAutoCompleteSeconds;
    int FinalDefenseSeconds;
    int ExtractionDurationSeconds;

    void DeutschZConvoyZEventTestingSettings()
    {
        FastTestMode = 1;
        CaptureHoldSeconds = 45;
        RequiredKillsToWin = 3;
        HackDurationSeconds = 30;
        WaveDelaySeconds = 30;
        StageAutoCompleteSeconds = 180;
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
        if (StageAutoCompleteSeconds < 5) StageAutoCompleteSeconds = 5;
        if (FinalDefenseSeconds < 30) FinalDefenseSeconds = 30;
        if (ExtractionDurationSeconds < 5) ExtractionDurationSeconds = 5;
    }
}

class DeutschZConvoyZEventSettings
{
    int SchemaVersion;
    string PresetName;
    string ConfigMode;
    ref DeutschZConvoyZEventCoreSettings Event;
    ref DeutschZConvoyZEventSchedulingSettings Scheduling;
    ref DeutschZConvoyZEventMarkerSettings Markers;
    ref DeutschZConvoyZEventNotificationSettings Notifications;
    ref DeutschZConvoyZEventRewardSettings Rewards;
    ref DeutschZConvoyZEventTestingSettings Testing;

    void DeutschZConvoyZEventSettings()
    {
        SchemaVersion = 1;
        PresetName = "FAST_TEST";
        ConfigMode = "FastRestartTest";
        Event = new DeutschZConvoyZEventCoreSettings();
        Scheduling = new DeutschZConvoyZEventSchedulingSettings();
        Markers = new DeutschZConvoyZEventMarkerSettings();
        Notifications = new DeutschZConvoyZEventNotificationSettings();
        Rewards = new DeutschZConvoyZEventRewardSettings();
        Testing = new DeutschZConvoyZEventTestingSettings();
        Repair("DeutschZ ConvoyZ Crash", "Vehicle Crash", "ConvoyZ_");
    }

    void Repair(string fallbackName, string fallbackIcon, string fallbackPrefix)
    {
        if (SchemaVersion < 1) SchemaVersion = 1;
        if (PresetName == "") PresetName = "FAST_TEST";
        if (ConfigMode == "") ConfigMode = "FastRestartTest";
        if (!Event) Event = new DeutschZConvoyZEventCoreSettings();
        if (!Scheduling) Scheduling = new DeutschZConvoyZEventSchedulingSettings();
        if (!Markers) Markers = new DeutschZConvoyZEventMarkerSettings();
        if (!Notifications) Notifications = new DeutschZConvoyZEventNotificationSettings();
        if (!Rewards) Rewards = new DeutschZConvoyZEventRewardSettings();
        if (!Testing) Testing = new DeutschZConvoyZEventTestingSettings();
        Event.Repair();
        Scheduling.Repair();
        Markers.Repair(fallbackName, fallbackIcon, fallbackPrefix);
        Notifications.Repair();
        Rewards.Repair();
        Testing.Repair();
    }
}

class DeutschZConvoyZSettings
{
    ref DeutschZConvoyZEventSettings DeutschZEventSettings;
    int EnableConvoyZEvent;
    string EventConfigPath;
    int RequiredAiKills;
    int HackDurationSeconds;
    float BlackboxMaxHackDistance;
    int AllowHackProgressResetOnAbort;
    int EnableAiWaves;
    int WaveDelaySeconds;
    int UseEventMarker;
    int UseEvent3DMarker;
    string EventMarkerIcon;
    string EventMarkerName;
    int CleanupDelaySeconds;
    int RewardClaimOnce;
    int RejectParallelHackRequests;
    int RejectParallelEventStarts;
    int EnableDebugLogs;
    int StatusBarUpdateIntervalSeconds;
    int EnableStatusNotifications;
    int StatusNotifyIntervalSeconds;
    float StatusSyncRadius;
    int AutoStartOnMissionInit;
    int InitialStartDelayMinSeconds;
    int InitialStartDelayMaxSeconds;
    int RestartEventAfterCleanup;
    int RestartDelayMinSeconds;
    int RestartDelayMaxSeconds;
    int MaxSimultaneousEvents;
    int MaxEventsPerRestart;
    int MinOnlinePlayersToStart;
    int NoPlayerRetryDelaySeconds;
    int MaxEventRuntimeSeconds;
    int BlackboxReadyTimeoutSeconds;
    int AutoFailStuckEvent;


    void EnsureDeutschZEventSettings()
    {
        if (!DeutschZEventSettings)
            DeutschZEventSettings = new DeutschZConvoyZEventSettings();
        DeutschZEventSettings.Repair("DeutschZ ConvoyZ Crash", "Vehicle Crash", "ConvoyZ_");
    }

    void ApplyDeutschZEventSettings()
    {
        EnsureDeutschZEventSettings();
        EnableConvoyZEvent = DeutschZEventSettings.Event.Enabled;
        MinOnlinePlayersToStart = DeutschZEventSettings.Event.MinOnlinePlayers;
        MaxSimultaneousEvents = DeutschZEventSettings.Event.MaxSimultaneousEvents;
        MaxEventsPerRestart = DeutschZEventSettings.Event.MaxEventsPerRestart;
        MaxEventRuntimeSeconds = DeutschZEventSettings.Event.MaxRuntimeSeconds;
        CleanupDelaySeconds = DeutschZEventSettings.Event.CleanupDelaySeconds;
        EnableDebugLogs = DeutschZEventSettings.Event.DebugLogs;
        AutoStartOnMissionInit = DeutschZEventSettings.Scheduling.AutoStartAfterRestart;
        InitialStartDelayMinSeconds = DeutschZEventSettings.Scheduling.StartDelayMinSeconds;
        InitialStartDelayMaxSeconds = DeutschZEventSettings.Scheduling.StartDelayMaxSeconds;
        RestartEventAfterCleanup = DeutschZEventSettings.Scheduling.RestartAfterFinish;
        RestartDelayMinSeconds = DeutschZEventSettings.Scheduling.RestartDelayMinSeconds;
        RestartDelayMaxSeconds = DeutschZEventSettings.Scheduling.RestartDelayMaxSeconds;
        NoPlayerRetryDelaySeconds = DeutschZEventSettings.Scheduling.NoPlayerRetryDelaySeconds;
        UseEventMarker = DeutschZEventSettings.Markers.Enabled * DeutschZEventSettings.Markers.UseMapMarker;
        UseEvent3DMarker = DeutschZEventSettings.Markers.Enabled * DeutschZEventSettings.Markers.Use3DMarker;
        EventMarkerName = DeutschZEventSettings.Markers.MarkerName;
        EventMarkerIcon = DeutschZEventSettings.Markers.MarkerIcon;
        EnableStatusNotifications = DeutschZEventSettings.Notifications.Enabled * DeutschZEventSettings.Notifications.StatusNotifications;
        StatusNotifyIntervalSeconds = DeutschZEventSettings.Notifications.StatusIntervalSeconds;
        RequiredAiKills = DeutschZEventSettings.Testing.RequiredKillsToWin;
        HackDurationSeconds = DeutschZEventSettings.Testing.HackDurationSeconds;
        WaveDelaySeconds = DeutschZEventSettings.Testing.WaveDelaySeconds;
    }

    void DeutschZConvoyZSettings()
    {
        DeutschZEventSettings = new DeutschZConvoyZEventSettings();
        EnableConvoyZEvent = 1;
        EventConfigPath = DeutschZConvoyZConstants.EVENTS_FILE;
        RequiredAiKills = 15;
        HackDurationSeconds = 120;
        BlackboxMaxHackDistance = 3.0;
        AllowHackProgressResetOnAbort = 1;
        EnableAiWaves = 1;
        WaveDelaySeconds = 180;
        UseEventMarker = 1;
        UseEvent3DMarker = 1;
        EventMarkerIcon = "Vehicle Crash";
        EventMarkerName = "DeutschZ ConvoyZ Crash";
        CleanupDelaySeconds = 900;
        RewardClaimOnce = 1;
        RejectParallelHackRequests = 1;
        RejectParallelEventStarts = 1;
        EnableDebugLogs = 1;
        StatusBarUpdateIntervalSeconds = 1;
        EnableStatusNotifications = 1;
        StatusNotifyIntervalSeconds = 60;
        StatusSyncRadius = 750.0;
        AutoStartOnMissionInit = 1;
        InitialStartDelayMinSeconds = 600;
        InitialStartDelayMaxSeconds = 600;
        RestartEventAfterCleanup = 1;
        RestartDelayMinSeconds = 1500;
        RestartDelayMaxSeconds = 1500;
        MaxSimultaneousEvents = 1;
        MaxEventsPerRestart = 3;
        MinOnlinePlayersToStart = 1;
        NoPlayerRetryDelaySeconds = 300;
        MaxEventRuntimeSeconds = 5400;
        BlackboxReadyTimeoutSeconds = 1800;
        AutoFailStuckEvent = 1;
    }
}

class DeutschZConvoyZRewardClaim
{
    string EventId;
    int ClaimedAt;

    void DeutschZConvoyZRewardClaim()
    {
        EventId = "";
        ClaimedAt = 0;
    }
}

class DeutschZConvoyZRewardClaims
{
    ref array<ref DeutschZConvoyZRewardClaim> Claims;

    void DeutschZConvoyZRewardClaims()
    {
        Claims = new array<ref DeutschZConvoyZRewardClaim>;
    }
}

class DeutschZConvoyZStatusPayload
{
    string Text;
    int State;
    int Current;
    int Max;
    int Visible;

    void DeutschZConvoyZStatusPayload()
    {
        Text = "";
        State = 0;
        Current = 0;
        Max = 0;
        Visible = 0;
    }
}
