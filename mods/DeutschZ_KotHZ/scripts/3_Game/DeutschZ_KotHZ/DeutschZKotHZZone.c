/*
DeutschZ ModZ
Eigenstaendige Implementierung fuer DeutschZ.
Autor/Eigentuemer: Patrick Sluzalek / fck1701.
Keine direkte Codeuebernahme aus Drittquellen.
Oeffentliche Quellen werden nur zur Konzept- und API-Verifikation genutzt.
*/

class DeutschZKotHZZone
{
    string EditHint;
    string ZoneName;
    vector Position;
    vector FlagpolePosition;
    vector FlagpoleOrientation;
    vector RewardCratePosition;
    vector RewardCrateOrientation;
    int UseExactRewardCratePosition;
    float Radius;
    int CaptureTimeSeconds;
    string RewardPoolName;
    string WavePoolName;
    int StartWavesOnlyWhenPlayerInside;
    int SpawnOutdoorOnly;
    int MaxTotalZombies;

    // Optional public workshop decoration near the event.
    int EnableCrashedHeliDecoration;
    string CrashedHeliClassName;
    vector CrashedHeliOffset;
    vector CrashedHeliOrientation;


    // Visible KOTH flagpole / flag setup.
    int EnableFlagpole;
    string FlagpoleClassName;
    string FlagClassName;
    float FlagVisualHeightOffset;
    int DeleteFlagpoleOnEventEnd;

    // Zone-specific spawn control. If enabled, this zone overrides the global NPC/Zombie config.
    int UseZoneSpawnSettings;

    // Optional DeutschZ NPC reserve per zone. Disabled; KotHZ currently uses infected waves only.
    int EnableOptionalNPC;
    int NPCAmount;
    float NPCSpawnRadius;
    int NPCSpawnHeightOffset;
    int NPCDespawnOnEventEnd;
    int ValidateNPCClassBeforeSpawn;
    ref array<string> NPCClassNames;
    ref array<string> NPCLoadoutClassNames;

    // Infected/Zombie enemies per zone.
    int EnableZombieSpawns;
    int InitialZombieSpawnCount;
    int ZombieWaveCount;
    int ZombiesPerWave;
    int SecondsBetweenZombieWaves;
    float ZombieSpawnMinDistance;
    float ZombieSpawnMaxDistance;
    int ValidateZombieClassBeforeSpawn;
    int DespawnZombiesOnEventEnd;
    ref array<string> ZombieTypes;

    void DeutschZKotHZZone()
    {
        EditHint = "Zone config. Position/FlagpolePosition are x y z. Radius is capture radius. FlagClassName selects the location flag. WavePoolName selects zombie waves.";
        ZoneName = "NWAF KOTH";
        Position = "4500 0 10300";
        FlagpolePosition = "4500 0 10300";
        FlagpoleOrientation = "0 0 0";
        RewardCratePosition = "0 0 0";
        RewardCrateOrientation = "0 0 0";
        UseExactRewardCratePosition = 0;
        Radius = 25.0;
        CaptureTimeSeconds = 240;
        RewardPoolName = "TestVanillaCombat";
        WavePoolName = "KVM1_Test_5x6_Zombies";
        StartWavesOnlyWhenPlayerInside = 1;
        SpawnOutdoorOnly = 1;
        EnableCrashedHeliDecoration = 0;
        CrashedHeliClassName = "Wreck_Mi8";
        CrashedHeliOffset = "16 0 10";
        CrashedHeliOrientation = "35 0 0";

        EnableFlagpole = 1;
        FlagpoleClassName = "DeutschZKotHZ_RuntimeFlagpole";
        FlagClassName = "";
        FlagVisualHeightOffset = 13.0;
        DeleteFlagpoleOnEventEnd = 1;

        UseZoneSpawnSettings = 1;

        EnableOptionalNPC = 0;
        NPCAmount = 0;
        NPCSpawnRadius = 25.0;
        NPCSpawnHeightOffset = 0;
        NPCDespawnOnEventEnd = 1;
        ValidateNPCClassBeforeSpawn = 1;

        NPCClassNames = new array<string>;

        NPCLoadoutClassNames = new array<string>;

        EnableZombieSpawns = 1;
        InitialZombieSpawnCount = 0;
        ZombieWaveCount = 5;
        ZombiesPerWave = 6;
        MaxTotalZombies = 30;
        SecondsBetweenZombieWaves = 45;
        ZombieSpawnMinDistance = 18.0;
        ZombieSpawnMaxDistance = 42.0;
        ValidateZombieClassBeforeSpawn = 1;
        DespawnZombiesOnEventEnd = 1;

        ZombieTypes = new array<string>;
        ZombieTypes.Insert("ZmbM_usSoldier_Officer_Desert");
        ZombieTypes.Insert("ZmbM_PatrolNormal_Summer");
        ZombieTypes.Insert("ZmbM_usSoldier_Officer_Desert");
        ZombieTypes.Insert("ZmbM_usSoldier_Officer_Desert");
        ZombieTypes.Insert("ZmbM_CitizenASkinny_Blue");
        ZombieTypes.Insert("ZmbM_NBC_Yellow");
    }
}
