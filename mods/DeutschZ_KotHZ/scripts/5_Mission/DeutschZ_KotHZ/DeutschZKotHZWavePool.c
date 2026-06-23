/*
DeutschZ ModZ
Eigenstaendige Implementierung fuer DeutschZ.
Autor/Eigentuemer: Patrick Sluzalek / fck1701.
Keine direkte Codeuebernahme aus Drittquellen.
Oeffentliche Quellen werden nur zur Konzept- und API-Verifikation genutzt.
*/

class DeutschZKotHZWaveEntry
{
    string EditHint;
    string WaveName;
    int DelaySeconds;
    int EnemyCount;
    int UseExpansionAI;
    int AIEnemyCount;
    string AILoadoutId;
    ref array<string> AIClassNames;
    float SpawnRadiusMin;
    float SpawnRadiusMax;
    int SpawnOutdoorOnly;
    int ValidateClassBeforeSpawn;
    int EnableClassFallback;
    string FallbackClassName;
    ref array<string> EnemyClassNames;

    void DeutschZKotHZWaveEntry()
    {
        EditHint = "Wave entry. DelaySeconds starts after first player enters. EnemyCount controls amount for this wave.";
        WaveName = "Wave";
        DelaySeconds = 0;
        EnemyCount = 4;
        UseExpansionAI = 0;
        AIEnemyCount = 0;
        AILoadoutId = "DeutschZ_KotHZ_SNAFU_Military_AI";
        AIClassNames = new array<string>;
        AIClassNames.Insert("eAI_SurvivorM_Boris");
        AIClassNames.Insert("eAI_SurvivorM_Denis");
        AIClassNames.Insert("eAI_SurvivorM_Mirek");
        SpawnRadiusMin = 16.0;
        SpawnRadiusMax = 40.0;
        SpawnOutdoorOnly = 1;
        ValidateClassBeforeSpawn = 1;
        EnableClassFallback = 1;
        FallbackClassName = "ZmbM_CitizenASkinny_Brown";
        EnemyClassNames = new array<string>;
        EnemyClassNames.Insert("ZmbM_PatrolNormal_Autumn");
        EnemyClassNames.Insert("ZmbM_SoldierNormal_Beige");
        EnemyClassNames.Insert("ZmbM_PatrolNormal_Summer");
    }
}

class DeutschZKotHZWavePool
{
    string EditHint;
    string PoolName;
    int StartOnlyWhenPlayerInside;
    int CancelOnEventEnd;
    int MaxTotalZombies;
    ref array<ref DeutschZKotHZWaveEntry> Waves;

    void DeutschZKotHZWavePool()
    {
        EditHint = "Wave pool config. StartOnlyWhenPlayerInside 1 means waves start only when a player enters the KOTH radius.";
        PoolName = "NWAF_Military_Zombies";
        StartOnlyWhenPlayerInside = 1;
        CancelOnEventEnd = 1;
        MaxTotalZombies = 30;
        Waves = new array<ref DeutschZKotHZWaveEntry>;

        DeutschZKotHZWaveEntry initial = new DeutschZKotHZWaveEntry();
        initial.WaveName = "Initial Contact - 3 AI";
        initial.DelaySeconds = 0;
        initial.UseExpansionAI = 1;
        initial.AIEnemyCount = 3;
        initial.EnemyCount = 0;
        initial.SpawnRadiusMin = 16.0;
        initial.SpawnRadiusMax = 40.0;
        initial.EnemyClassNames.Clear();
        initial.EnemyClassNames.Insert("ZmbM_PatrolNormal_Autumn");
        initial.EnemyClassNames.Insert("ZmbM_PatrolNormal_Summer");
        initial.EnemyClassNames.Insert("ZmbM_SoldierNormal_Beige");
        initial.EnemyClassNames.Insert("ZmbM_CitizenASkinny_Brown");
        Waves.Insert(initial);

        DeutschZKotHZWaveEntry wave1 = new DeutschZKotHZWaveEntry();
        wave1.WaveName = "Military Wave 1";
        wave1.DelaySeconds = 45;
        wave1.EnemyCount = 3;
        wave1.SpawnRadiusMin = 16.0;
        wave1.SpawnRadiusMax = 40.0;
        wave1.EnemyClassNames.Clear();
        wave1.EnemyClassNames.Insert("ZmbM_PatrolNormal_Autumn");
        wave1.EnemyClassNames.Insert("ZmbM_SoldierNormal_Beige");
        wave1.EnemyClassNames.Insert("ZmbM_PatrolNormal_Summer");
        Waves.Insert(wave1);

        DeutschZKotHZWaveEntry wave2 = new DeutschZKotHZWaveEntry();
        wave2.WaveName = "Military Wave 2";
        wave2.DelaySeconds = 90;
        wave2.EnemyCount = 3;
        wave2.SpawnRadiusMin = 16.0;
        wave2.SpawnRadiusMax = 40.0;
        wave2.EnemyClassNames.Clear();
        wave2.EnemyClassNames.Insert("ZmbM_SoldierNormal_Beige");
        wave2.EnemyClassNames.Insert("ZmbM_NBC_Grey");
        wave2.EnemyClassNames.Insert("ZmbM_NBC_Yellow");
        Waves.Insert(wave2);

        DeutschZKotHZWaveEntry wave3 = new DeutschZKotHZWaveEntry();
        wave3.WaveName = "Final Pressure Wave";
        wave3.DelaySeconds = 135;
        wave3.EnemyCount = 4;
        wave3.SpawnRadiusMin = 16.0;
        wave3.SpawnRadiusMax = 40.0;
        wave3.EnemyClassNames.Clear();
        wave3.EnemyClassNames.Insert("ZmbM_SoldierNormal_Beige");
        wave3.EnemyClassNames.Insert("ZmbM_NBC_Grey");
        wave3.EnemyClassNames.Insert("ZmbM_NBC_Yellow");
        Waves.Insert(wave3);
    }
}

class DeutschZKotHZWavePoolsConfig
{
    string ConfigInfo;
    ref array<ref DeutschZKotHZWavePool> WavePools;

    void DeutschZKotHZWavePoolsConfig()
    {
        ConfigInfo = "DeutschZ_KotHZ wave pool config. V0.9.3 normal: first contact 3 Expansion AI, then 30 infected over controlled waves.";
        WavePools = new array<ref DeutschZKotHZWavePool>;

        CreateDeutschZNormalPool();
        CreateKVM1TestPool();

        DeutschZKotHZWavePool nwaf = new DeutschZKotHZWavePool();
        nwaf.PoolName = "NWAF_Military_Zombies";
        WavePools.Insert(nwaf);

        DeutschZKotHZWavePool light = new DeutschZKotHZWavePool();
        light.PoolName = "Military_Light_Zombies";
        light.Waves.Clear();
        DeutschZKotHZWaveEntry light1 = new DeutschZKotHZWaveEntry();
        light1.WaveName = "Light Contact";
        light1.DelaySeconds = 0;
        light1.EnemyCount = 2;
        light1.SpawnRadiusMin = 16.0;
        light1.SpawnRadiusMax = 40.0;
        light1.EnemyClassNames.Clear();
        light1.EnemyClassNames.Insert("ZmbM_PatrolNormal_Autumn");
        light1.EnemyClassNames.Insert("ZmbM_SoldierNormal_Beige");
        light.Waves.Insert(light1);
        DeutschZKotHZWaveEntry light2 = new DeutschZKotHZWaveEntry();
        light2.WaveName = "Light Reinforcement";
        light2.DelaySeconds = 60;
        light2.EnemyCount = 2;
        light2.SpawnRadiusMin = 16.0;
        light2.SpawnRadiusMax = 40.0;
        light2.EnemyClassNames.Clear();
        light2.EnemyClassNames.Insert("ZmbM_SoldierNormal_Beige");
        light2.EnemyClassNames.Insert("ZmbM_NBC_Grey");
        light.Waves.Insert(light2);
        WavePools.Insert(light);

        DeutschZKotHZWavePool base = new DeutschZKotHZWavePool();
        base.PoolName = "Basebuilding_Zombies";
        base.Waves.Clear();
        DeutschZKotHZWaveEntry b1 = new DeutschZKotHZWaveEntry();
        b1.WaveName = "Basebuilding Contact";
        b1.DelaySeconds = 0;
        b1.EnemyCount = 2;
        b1.SpawnRadiusMin = 16.0;
        b1.SpawnRadiusMax = 40.0;
        b1.EnemyClassNames.Clear();
        b1.EnemyClassNames.Insert("ZmbM_PatrolNormal_Autumn");
        b1.EnemyClassNames.Insert("ZmbM_CitizenASkinny_Brown");
        base.Waves.Insert(b1);
        DeutschZKotHZWaveEntry b2 = new DeutschZKotHZWaveEntry();
        b2.WaveName = "Basebuilding Reinforcement";
        b2.DelaySeconds = 75;
        b2.EnemyCount = 3;
        b2.SpawnRadiusMin = 16.0;
        b2.SpawnRadiusMax = 40.0;
        b2.EnemyClassNames.Clear();
        b2.EnemyClassNames.Insert("ZmbM_SoldierNormal_Beige");
        b2.EnemyClassNames.Insert("ZmbM_PatrolNormal_Summer");
        base.Waves.Insert(b2);
        WavePools.Insert(base);
    }

    protected void CreateKVM1TestPool()
    {
        DeutschZKotHZWavePool pool = new DeutschZKotHZWavePool();
        pool.PoolName = "KVM1_Test_5x6_Zombies";
        pool.EditHint = "KVM1 test pool: 30 total vanilla infected. Final wave starts at 180s, leaving roughly 60s in a 240s capture.";
        pool.StartOnlyWhenPlayerInside = 1;
        pool.CancelOnEventEnd = 1;
        pool.MaxTotalZombies = 30;
        pool.Waves.Clear();

        AddKVM1FirstAIWave(pool);
        AddKVM1Wave(pool, "Test Wave 2", 45);
        AddKVM1Wave(pool, "Test Wave 3", 90);
        AddKVM1Wave(pool, "Test Wave 4", 135);
        AddKVM1Wave(pool, "Test Wave 5", 180);

        WavePools.Insert(pool);
    }

    protected void AddKVM1FirstAIWave(DeutschZKotHZWavePool pool)
    {
        DeutschZKotHZWaveEntry wave = new DeutschZKotHZWaveEntry();
        wave.EditHint = "First KotHZ contact wave. Spawns three Expansion AI guards through DeutschZ_ExpansionBridge with the DeutschZ_KotHZ_SNAFU_Military_AI loadout. Zombie waves continue after this.";
        wave.WaveName = "Test Wave 1 - 3 AI Guards";
        wave.DelaySeconds = 0;
        wave.EnemyCount = 0;
        wave.UseExpansionAI = 1;
        wave.AIEnemyCount = 3;
        wave.AILoadoutId = "DeutschZ_KotHZ_SNAFU_Military_AI";
        wave.SpawnRadiusMin = 18.0;
        wave.SpawnRadiusMax = 42.0;
        wave.SpawnOutdoorOnly = 1;
        wave.ValidateClassBeforeSpawn = 1;
        wave.EnableClassFallback = 0;
        wave.FallbackClassName = "";
        wave.AIClassNames.Clear();
        wave.AIClassNames.Insert("eAI_SurvivorM_Boris");
        wave.AIClassNames.Insert("eAI_SurvivorM_Denis");
        wave.AIClassNames.Insert("eAI_SurvivorM_Mirek");
        wave.EnemyClassNames.Clear();
        pool.Waves.Insert(wave);
    }

    protected void AddKVM1Wave(DeutschZKotHZWavePool pool, string waveName, int delaySeconds)
    {
        DeutschZKotHZWaveEntry wave = new DeutschZKotHZWaveEntry();
        wave.EditHint = "Test wave entry. Five vanilla infected waves with six infected each; delays are tuned for a tight but testable 240 second capture.";
        wave.WaveName = waveName;
        wave.DelaySeconds = delaySeconds;
        wave.EnemyCount = 6;
        wave.SpawnRadiusMin = 18.0;
        wave.SpawnRadiusMax = 42.0;
        wave.SpawnOutdoorOnly = 1;
        wave.ValidateClassBeforeSpawn = 1;
        wave.EnableClassFallback = 1;
        wave.FallbackClassName = "ZmbM_CitizenASkinny_Brown";
        wave.EnemyClassNames.Clear();
        wave.EnemyClassNames.Insert("ZmbM_PatrolNormal_Autumn");
        wave.EnemyClassNames.Insert("ZmbM_PatrolNormal_Summer");
        wave.EnemyClassNames.Insert("ZmbM_SoldierNormal_Beige");
        wave.EnemyClassNames.Insert("ZmbM_CitizenASkinny_Brown");
        wave.EnemyClassNames.Insert("ZmbM_CitizenASkinny_Blue");
        pool.Waves.Insert(wave);
    }
}
