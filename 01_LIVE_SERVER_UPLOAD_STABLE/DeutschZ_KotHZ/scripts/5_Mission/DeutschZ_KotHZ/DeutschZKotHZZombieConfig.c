/*
DeutschZ ModZ
Eigenstaendige Implementierung fuer DeutschZ.
Autor/Eigentuemer: Patrick Sluzalek / fck1701.
Keine direkte Codeuebernahme aus Drittquellen.
Oeffentliche Quellen werden nur zur Konzept- und API-Verifikation genutzt.
*/

class DeutschZKotHZZombieConfig
{
    string EditHint;
    int EnableZombieSpawns;
    int InitialZombieSpawnCount;
    int ZombieWaveCount;
    int ZombiesPerWave;
    int MaxTotalZombies;
    int SecondsBetweenZombieWaves;
    int EnableZombieClassFallback;
    string ZombieFallbackClassName;
    ref array<string> ZombieFallbackClassNames;
    float ZombieSpawnMinDistance;
    float ZombieSpawnMaxDistance;
    int ValidateClassBeforeSpawn;
    int DespawnZombiesOnEventEnd;
    ref array<string> ZombieTypes;
    ref array<string> AnimalTypes;

    void DeutschZKotHZZombieConfig()
    {
        EditHint = "Global zombie fallback config. Zone WavePoolName is preferred for current test setup.";
        EnableZombieSpawns = 1;
        InitialZombieSpawnCount = 0;
        ZombieWaveCount = 5;
        ZombiesPerWave = 6;
        MaxTotalZombies = 30;
        SecondsBetweenZombieWaves = 45;
        EnableZombieClassFallback = 1;
        ZombieFallbackClassName = "ZmbM_CitizenASkinny_Brown";
        ZombieFallbackClassNames = new array<string>;
        ZombieFallbackClassNames.Insert("ZmbM_CitizenASkinny_Brown");
        ZombieFallbackClassNames.Insert("ZmbM_CitizenASkinny_Blue");
        ZombieFallbackClassNames.Insert("ZmbM_PatrolNormal_Autumn");
        ZombieFallbackClassNames.Insert("ZmbM_SoldierNormal_Beige");
        ZombieSpawnMinDistance = 18.0;
        ZombieSpawnMaxDistance = 42.0;
        ValidateClassBeforeSpawn = 1;
        DespawnZombiesOnEventEnd = 1;

        ZombieTypes = new array<string>;
        // Safe vanilla military/NBC infected set, aligned with DeutschZ wave-pool preset logic.
        ZombieTypes.Insert("ZmbM_PatrolNormal_Autumn");
        ZombieTypes.Insert("ZmbM_PatrolNormal_Summer");
        ZombieTypes.Insert("ZmbM_SoldierNormal_Beige");
        ZombieTypes.Insert("ZmbM_CitizenASkinny_Brown");
        ZombieTypes.Insert("ZmbM_CitizenASkinny_Blue");
        ZombieTypes.Insert("ZmbM_NBC_Grey");
        ZombieTypes.Insert("ZmbM_NBC_Yellow");

        AnimalTypes = new array<string>;
    }
}
