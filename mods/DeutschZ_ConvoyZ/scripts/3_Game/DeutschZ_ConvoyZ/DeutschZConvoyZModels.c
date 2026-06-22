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
    int Enabled;
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
        Enabled = 0;
        Position = "0 0 0";
        RedSmokeClassName = "M18SmokeGrenade_Red";
        YellowSmokeClassName = "M18SmokeGrenade_Yellow";
        GreenSmokeClassName = "M18SmokeGrenade_Green";
        WhiteSmokeClassName = "M18SmokeGrenade_White";
        Count = 0;
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
        RewardContainerClassName = "DZCV_SealedRewardChest";
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
        EventCenter = "10120 0 5410";
        EventRadius = 450.0;
        Vehicles = new array<ref DeutschZConvoyZVehicleDef>;
        CrashObjects = new array<ref DeutschZConvoyZObjectDef>;
        Blackbox = new DeutschZConvoyZBlackboxDef();
        Smoke = new DeutschZConvoyZSmokeDef();
        AIWaves = new array<ref DeutschZConvoyZAIWaveDef>;
        RequiredAiKills = 4;
        HackDurationSeconds = 30;
        Reward = new DeutschZConvoyZRewardDef();
    }
}

class DeutschZConvoyZSettings
{
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

    void DeutschZConvoyZSettings()
    {
        EnableConvoyZEvent = 1;
        EventConfigPath = DeutschZConvoyZConstants.EVENTS_FILE;
        RequiredAiKills = 4;
        HackDurationSeconds = 30;
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
        StatusNotifyIntervalSeconds = 30;
        StatusSyncRadius = 750.0;
        AutoStartOnMissionInit = 1;
        InitialStartDelayMinSeconds = 180;
        InitialStartDelayMaxSeconds = 180;
        RestartEventAfterCleanup = 1;
        RestartDelayMinSeconds = 900;
        RestartDelayMaxSeconds = 900;
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
