/*
    DeutschZ_GroundZero
    Owner: Patrick Sluzalek / fck1701
    Module: 1_Core / GroundZeroTypes
    Purpose: Persistent and runtime DTOs only. No world access here.
    Dependencies: DayZ scripts; optional CF/Expansion APIs only through adapter methods.
    Compliance: Original DeutschZ implementation. No copied foreign mod code, assets, configs or stubs.
*/

class GroundZeroStageRuntime: Managed
{
    int StageId;
    int State;
    vector Position;
    float StartedAt;
    float ObjectiveStartedAt;
    float CompletedAt;
    bool RewardSpawned;
    string CompletedByPlayerId;
    int ObjectiveKillCount;
    int ObjectiveKillRequired;

    void GroundZeroStageRuntime()
    {
        StageId = 0;
        State = GroundZeroStageState.GZ_STAGE_LOCKED;
        Position = "0 0 0";
        StartedAt = 0;
        ObjectiveStartedAt = 0;
        CompletedAt = 0;
        RewardSpawned = false;
        CompletedByPlayerId = "";
        ObjectiveKillCount = 0;
        ObjectiveKillRequired = 3;
    }
}

class GroundZeroCarrierRuntime: Managed
{
    string PlayerId;
    string PlayerName;
    int ItemCount;
    vector LastKnownPosition;
    float LastMarkerUpdate;
    float LastAISearchSpawnedAt;

    void GroundZeroCarrierRuntime()
    {
        PlayerId = "";
        PlayerName = "";
        ItemCount = 0;
        LastKnownPosition = "0 0 0";
        LastMarkerUpdate = 0;
        LastAISearchSpawnedAt = 0;
    }
}

class GroundZeroDroppedItemRuntime: Managed
{
    string ItemClass;
    vector Position;
    float DroppedAt;
    bool Resolved;

    void GroundZeroDroppedItemRuntime()
    {
        ItemClass = "";
        Position = "0 0 0";
        DroppedAt = 0;
        Resolved = false;
    }
}

class GroundZeroCheckpointRuntime: Managed
{
    string PlayerId;
    vector Position;
    int StageId;
    int RetriesUsed;
    bool LastDeathWasPvP;
    bool HasPendingDeathChoice;
    bool HasAbortedEvent;

    void GroundZeroCheckpointRuntime()
    {
        PlayerId = "";
        Position = "0 0 0";
        StageId = 0;
        RetriesUsed = 0;
        LastDeathWasPvP = false;
        HasPendingDeathChoice = false;
        HasAbortedEvent = false;
    }
}

class GroundZeroPersistentState: Managed
{
    int StateVersion;
    int EventState;
    int CurrentStageId;
    float EventStartedAt;
    float EventEndsAt;
    float NextAutoStartAt;
    int BossState;
    bool ExtractionStarted;
    bool ExtractionSuccess;
    bool ExtractionFailed;
    float FinalStartedAt;
    float ExtractionStartedAt;
    vector FinalFacilityPosition;
    vector ExtractionPosition;

    ref array<ref GroundZeroStageRuntime> Stages;
    ref array<ref GroundZeroCarrierRuntime> Carriers;
    ref array<ref GroundZeroCheckpointRuntime> Checkpoints;
    ref array<ref GroundZeroDroppedItemRuntime> DroppedItems;

    void GroundZeroPersistentState()
    {
        StateVersion = 3;
        EventState = GroundZeroEventState.GZ_IDLE;
        CurrentStageId = 0;
        EventStartedAt = 0;
        EventEndsAt = 0;
        NextAutoStartAt = 0;
        BossState = GroundZeroBossState.GZ_BOSS_NONE;
        ExtractionStarted = false;
        ExtractionSuccess = false;
        ExtractionFailed = false;
        FinalStartedAt = 0;
        ExtractionStartedAt = 0;
        FinalFacilityPosition = "0 0 0";
        ExtractionPosition = "0 0 0";
        Stages = new array<ref GroundZeroStageRuntime>();
        Carriers = new array<ref GroundZeroCarrierRuntime>();
        Checkpoints = new array<ref GroundZeroCheckpointRuntime>();
        DroppedItems = new array<ref GroundZeroDroppedItemRuntime>();
    }
}
