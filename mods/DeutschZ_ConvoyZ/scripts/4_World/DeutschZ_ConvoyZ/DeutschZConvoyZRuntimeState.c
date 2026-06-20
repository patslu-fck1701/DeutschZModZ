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

class DeutschZConvoyZRuntimeState
{
    string EventId;
    int CurrentState;
    ref array<Object> SpawnedObjects;
    ref array<Object> SpawnedAI;
    ref array<Object> SpawnedRewards;
    ref array<Object> SmokeObjects;
    int RequiredKills;
    int CurrentKills;
    Object BlackboxEntity;
    string SmokeState;
    string ActiveHackerPlayerId;
    int HackProgressSeconds;
    int RewardUnlocked;
    int RewardClaimed;
    int CleanupPending;
    int EventProcessing;
    int HackProcessing;
    int RewardProcessing;
    int LastStatusSyncAt;
    int LastStatusNotifyAt;
    int LastSmokeRefreshAt;
    int CurrentWaveIndex;
    int NextWaveAt;
    int RewardUnlockedAt;
    int BlackboxReadyAt;
    int EventStartedAt;

    void DeutschZConvoyZRuntimeState()
    {
        EventId = "";
        CurrentState = DeutschZConvoyZConstants.STATE_NONE;
        SpawnedObjects = new array<Object>;
        SpawnedAI = new array<Object>;
        SpawnedRewards = new array<Object>;
        SmokeObjects = new array<Object>;
        RequiredKills = 15;
        CurrentKills = 0;
        BlackboxEntity = null;
        SmokeState = "";
        ActiveHackerPlayerId = "";
        HackProgressSeconds = 0;
        RewardUnlocked = 0;
        RewardClaimed = 0;
        CleanupPending = 0;
        EventProcessing = 0;
        HackProcessing = 0;
        RewardProcessing = 0;
        LastStatusSyncAt = 0;
        LastStatusNotifyAt = 0;
        LastSmokeRefreshAt = 0;
        CurrentWaveIndex = 0;
        NextWaveAt = 0;
        RewardUnlockedAt = 0;
        BlackboxReadyAt = 0;
        EventStartedAt = 0;
    }
}
