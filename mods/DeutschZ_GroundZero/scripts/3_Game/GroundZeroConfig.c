/*
    DeutschZ_GroundZero
    Owner: Patrick Sluzalek / fck1701
    Module: 3_Game / GroundZeroConfig
    Purpose: Central JSON config with Load, Validate, Repair and Save workflow.
    Dependencies: DayZ scripts; optional CF/Expansion APIs only through adapter methods.
    Compliance: Original DeutschZ implementation. No copied foreign mod code, assets, configs or stubs.
*/

class GroundZeroStageConfig
{
    int StageId;
    string StageName;
    string ObjectiveText;
    string RewardItemClass;
    int ZombieThreatLevel;
    int ZombieCount;
    int MilitaryAICount;
    int RogueAICount;
    float StageRadius;
    float CompletionHoldSeconds;
    bool RequireManualObjectiveCompletion;
}

class GroundZeroFinalWaveConfig
{
    int WaveId;
    string WaveName;
    int ZombieThreatLevel;
    int ZombieCount;
    int MilitaryAICount;
    int RogueAICount;
    float DelaySeconds;
}

class GroundZeroConfig
{
    int ConfigVersion;

    bool EnableGroundZero;
    bool AutoStartEnabled;
    int AutoStartMinDelaySeconds;
    int AutoStartMaxDelaySeconds;
    int MinOnlinePlayersToAutoStart;

    int EventMinDurationSeconds;
    int EventMaxDurationSeconds;
    int EventCleanupDelaySeconds;

    bool AllowTimedObjectiveFallback;
    int RetryLimitPerEvent;
    float RetrySpawnBackDistanceMin;
    float RetrySpawnBackDistanceMax;
    bool AllowRetryAfterPvPDeath;
    bool RemoveCampaignItemsOnDeath;
    ref array<string> RetryMinimalLoadout;

    float CarrierMarkerUpdateSeconds;
    float CarrierDropMarkerUpdateSeconds;
    float CarrierRadiusTwoItems;
    float CarrierRadiusThreeItems;
    float CarrierRadiusFourItems;
    float CarrierRadiusFiveItems;

    float DroppedItemMarkerLargeSeconds;
    float DroppedItemMarkerSmallSeconds;
    float DroppedItemLargeRadius;
    float DroppedItemSmallRadius;

    int RequiredCampaignItemCount;

    string ItemAlphaDataModule;
    string ItemEnergyCell;
    string ItemBioSample;
    string ItemAuthChip;
    string ItemContainmentKey;
    string ItemFinalResearchCore;

    bool EnableZombies;
    bool EnableExpansionAI;
    bool EnableMilitaryFaction;
    bool EnableRogueFaction;
    bool EnableCarrierAISearchTeams;
    bool EnableVanillaAISafetyFallback;

    int CarrierAISearchTeamsMinItems;
    int CarrierAISearchTeamSize;
    float CarrierAISearchTeamCooldownSeconds;

    bool EnableFinalBoss;
    string BossClassName;
    float BossHealth;
    float BossPhaseTwoHealthPercent;
    float BossPhaseThreeHealthPercent;

    float FinalActivationSeconds;
    float FinalDefenseSeconds;
    float ExtractionDurationSeconds;
    float ExtractionRadius;

    bool EnableRewards;
    int RewardMoneySuccess;
    int RewardBattlepassXPSuccess;
    int RewardMoneyFail;
    int RewardBattlepassXPFail;

    bool EnableGlobalNotifications;
    bool EnableMapMarkers;
    bool EnableDebugLogs;

    ref array<ref GroundZeroStageConfig> Stages;
    ref array<ref GroundZeroFinalWaveConfig> FinalWaves;
    ref array<vector> PossibleStagePositions;
    ref array<vector> PossibleFinalFacilityPositions;
    ref array<vector> PossibleExtractionPositions;

    void GroundZeroConfig()
    {
        Stages = new array<ref GroundZeroStageConfig>();
        FinalWaves = new array<ref GroundZeroFinalWaveConfig>();
        PossibleStagePositions = new array<vector>();
        PossibleFinalFacilityPositions = new array<vector>();
        PossibleExtractionPositions = new array<vector>();
        RetryMinimalLoadout = new array<string>();
        SetDefaults();
    }

    void SetDefaults()
    {
        ConfigVersion = 4;
        EnableGroundZero = true;
        AutoStartEnabled = false;
        AutoStartMinDelaySeconds = 1800;
        AutoStartMaxDelaySeconds = 5400;
        MinOnlinePlayersToAutoStart = 1;

        EventMinDurationSeconds = 2700;
        EventMaxDurationSeconds = 5400;
        EventCleanupDelaySeconds = 300;

        AllowTimedObjectiveFallback = true;
        RetryLimitPerEvent = 3;
        RetrySpawnBackDistanceMin = 300;
        RetrySpawnBackDistanceMax = 600;
        AllowRetryAfterPvPDeath = false;
        RemoveCampaignItemsOnDeath = true;
        RetryMinimalLoadout.Clear();
        RetryMinimalLoadout.Insert("BandageDressing");
        RetryMinimalLoadout.Insert("StoneKnife");
        RetryMinimalLoadout.Insert("WaterBottle");

        CarrierMarkerUpdateSeconds = 60;
        CarrierDropMarkerUpdateSeconds = 60;
        CarrierRadiusTwoItems = 500;
        CarrierRadiusThreeItems = 350;
        CarrierRadiusFourItems = 250;
        CarrierRadiusFiveItems = 0;

        DroppedItemMarkerLargeSeconds = 120;
        DroppedItemMarkerSmallSeconds = 300;
        DroppedItemLargeRadius = 500;
        DroppedItemSmallRadius = 150;

        RequiredCampaignItemCount = 5;
        ItemAlphaDataModule = "GroundZero_AlphaDataModule";
        ItemEnergyCell = "GroundZero_EnergyCell";
        ItemBioSample = "GroundZero_BioSample";
        ItemAuthChip = "GroundZero_AuthChip";
        ItemContainmentKey = "GroundZero_ContainmentKey";
        ItemFinalResearchCore = "GroundZero_ResearchCore";

        EnableZombies = true;
        EnableExpansionAI = true;
        EnableMilitaryFaction = true;
        EnableRogueFaction = true;
        EnableCarrierAISearchTeams = true;
        EnableVanillaAISafetyFallback = true;
        CarrierAISearchTeamsMinItems = 3;
        CarrierAISearchTeamSize = 4;
        CarrierAISearchTeamCooldownSeconds = 300;

        EnableFinalBoss = true;
        BossClassName = "ZmbM_usSoldier_Officer_Desert";
        BossHealth = 25000;
        BossPhaseTwoHealthPercent = 0.66;
        BossPhaseThreeHealthPercent = 0.33;

        FinalActivationSeconds = 30;
        FinalDefenseSeconds = 900;
        ExtractionDurationSeconds = 180;
        ExtractionRadius = 25;

        EnableRewards = true;
        RewardMoneySuccess = 250000;
        RewardBattlepassXPSuccess = 5000;
        RewardMoneyFail = 0;
        RewardBattlepassXPFail = 500;

        EnableGlobalNotifications = true;
        EnableMapMarkers = true;
        EnableDebugLogs = true;

        BuildDefaultStages();
        BuildDefaultFinalWaves();
        BuildDefaultPositions();
    }

    void BuildDefaultStages()
    {
        Stages.Clear();
        AddStage(1, "Signalstation", "Funkstation aktivieren", ItemAlphaDataModule, 1, 12, 2, 0, 120, 60, false);
        AddStage(2, "Generatorstation", "Generator mit Treibstoff versorgen", ItemEnergyCell, 2, 18, 4, 0, 140, 90, false);
        AddStage(3, "Forschungsstation", "Forschungsdaten sichern", ItemBioSample, 3, 24, 6, 0, 160, 120, false);
        AddStage(4, "Absturzstelle", "Militärabsturz untersuchen", ItemAuthChip, 4, 28, 6, 6, 180, 120, false);
        AddStage(5, "Verseuchte Zone", "Containment-System erreichen", ItemContainmentKey, 5, 36, 8, 8, 220, 180, false);
    }

    void AddStage(int id, string name, string objective, string reward, int threat, int z, int m, int r, float radius, float hold, bool manual)
    {
        GroundZeroStageConfig s = new GroundZeroStageConfig();
        s.StageId = id;
        s.StageName = name;
        s.ObjectiveText = objective;
        s.RewardItemClass = reward;
        s.ZombieThreatLevel = threat;
        s.ZombieCount = z;
        s.MilitaryAICount = m;
        s.RogueAICount = r;
        s.StageRadius = radius;
        s.CompletionHoldSeconds = hold;
        s.RequireManualObjectiveCompletion = manual;
        Stages.Insert(s);
    }

    void BuildDefaultFinalWaves()
    {
        FinalWaves.Clear();
        AddFinalWave(1, "Militärzombies", 2, 20, 0, 0, 0);
        AddFinalWave(2, "Hunter", 3, 18, 0, 0, 90);
        AddFinalWave(3, "Militär AI", 3, 12, 8, 0, 180);
        AddFinalWave(4, "Rogue AI", 4, 14, 0, 8, 270);
        AddFinalWave(5, "Elite-Welle", 5, 24, 8, 8, 360);
    }

    void AddFinalWave(int id, string name, int threat, int z, int m, int r, float d)
    {
        GroundZeroFinalWaveConfig f = new GroundZeroFinalWaveConfig();
        f.WaveId = id;
        f.WaveName = name;
        f.ZombieThreatLevel = threat;
        f.ZombieCount = z;
        f.MilitaryAICount = m;
        f.RogueAICount = r;
        f.DelaySeconds = d;
        FinalWaves.Insert(f);
    }

    void BuildDefaultPositions()
    {
        PossibleStagePositions.Clear();
        PossibleFinalFacilityPositions.Clear();
        PossibleExtractionPositions.Clear();

        // ASSUMPTION: Default ChernarusPlus positions. Server owners should tune these in JSON.
        PossibleStagePositions.Insert("3700 0 5980");
        PossibleStagePositions.Insert("4510 0 8280");
        PossibleStagePositions.Insert("6570 0 6020");
        PossibleStagePositions.Insert("8250 0 10820");
        PossibleStagePositions.Insert("1660 0 14230");

        PossibleFinalFacilityPositions.Insert("1680 0 14240");
        PossibleFinalFacilityPositions.Insert("4500 0 8280");
        PossibleFinalFacilityPositions.Insert("12070 0 12600");

        PossibleExtractionPositions.Insert("7500 0 7500");
        PossibleExtractionPositions.Insert("10500 0 9800");
        PossibleExtractionPositions.Insert("3200 0 6800");
    }

    void Repair()
    {
        if (!Stages) Stages = new array<ref GroundZeroStageConfig>();
        if (!FinalWaves) FinalWaves = new array<ref GroundZeroFinalWaveConfig>();
        if (!PossibleStagePositions) PossibleStagePositions = new array<vector>();
        if (!PossibleFinalFacilityPositions) PossibleFinalFacilityPositions = new array<vector>();
        if (!PossibleExtractionPositions) PossibleExtractionPositions = new array<vector>();
        if (!RetryMinimalLoadout) RetryMinimalLoadout = new array<string>();

        if (ConfigVersion < 4) ConfigVersion = 4;
        if (AutoStartMaxDelaySeconds < AutoStartMinDelaySeconds) AutoStartMaxDelaySeconds = AutoStartMinDelaySeconds + 1800;
        if (MinOnlinePlayersToAutoStart < 0) MinOnlinePlayersToAutoStart = 0;
        if (EventMinDurationSeconds < 600) EventMinDurationSeconds = 2700;
        if (EventMaxDurationSeconds < EventMinDurationSeconds) EventMaxDurationSeconds = EventMinDurationSeconds + 1800;
        if (RetryLimitPerEvent < 0) RetryLimitPerEvent = 0;
        if (RetrySpawnBackDistanceMin < 50) RetrySpawnBackDistanceMin = 300;
        if (RetrySpawnBackDistanceMax < RetrySpawnBackDistanceMin) RetrySpawnBackDistanceMax = RetrySpawnBackDistanceMin + 200;
        if (CarrierMarkerUpdateSeconds < 10) CarrierMarkerUpdateSeconds = 60;
        if (CarrierDropMarkerUpdateSeconds < 10) CarrierDropMarkerUpdateSeconds = 60;
        if (RequiredCampaignItemCount != 5) RequiredCampaignItemCount = 5;
        if (RetryMinimalLoadout.Count() < 1) RetryMinimalLoadout.Insert("BandageDressing");
        if (Stages.Count() < 5) BuildDefaultStages();
        if (FinalWaves.Count() < 1) BuildDefaultFinalWaves();
        if (PossibleStagePositions.Count() < 1 || PossibleFinalFacilityPositions.Count() < 1 || PossibleExtractionPositions.Count() < 1) BuildDefaultPositions();
    }

    bool Validate()
    {
        if (!EnableGroundZero) return true;
        if (EventMaxDurationSeconds < EventMinDurationSeconds) return false;
        if (!Stages || Stages.Count() < 5) return false;
        if (!PossibleStagePositions || PossibleStagePositions.Count() < 1) return false;
        if (!PossibleFinalFacilityPositions || PossibleFinalFacilityPositions.Count() < 1) return false;
        if (!PossibleExtractionPositions || PossibleExtractionPositions.Count() < 1) return false;
        return true;
    }

    bool IsCampaignItemClass(string className)
    {
        return className == ItemAlphaDataModule || className == ItemEnergyCell || className == ItemBioSample || className == ItemAuthChip || className == ItemContainmentKey;
    }

    GroundZeroStageConfig GetStageConfig(int id)
    {
        foreach (GroundZeroStageConfig s : Stages)
        {
            if (s && s.StageId == id) return s;
        }
        return null;
    }

    float GetCarrierRadius(int count)
    {
        if (count <= 1) return -1;
        if (count == 2) return CarrierRadiusTwoItems;
        if (count == 3) return CarrierRadiusThreeItems;
        if (count == 4) return CarrierRadiusFourItems;
        return CarrierRadiusFiveItems;
    }

    static GroundZeroConfig Load()
    {
        GroundZeroConfig cfg = new GroundZeroConfig();
        GroundZeroPersistence.EnsureProfileDirs();

        if (!FileExist(GroundZeroConstants.CONFIG_PATH))
        {
            cfg.Save();
            GroundZeroLogging.Info("Config", "Created default config");
            return cfg;
        }

        JsonFileLoader<GroundZeroConfig>.JsonLoadFile(GroundZeroConstants.CONFIG_PATH, cfg);
        cfg.Repair();

        if (!cfg.Validate())
        {
            GroundZeroLogging.Warn("Config", "Config invalid after load, rebuilding defaults");
            cfg.SetDefaults();
        }

        cfg.Save();
        GroundZeroLogging.Info("Config", "Loaded config version " + cfg.ConfigVersion.ToString());
        return cfg;
    }

    void Save()
    {
        GroundZeroPersistence.EnsureProfileDirs();
        JsonFileLoader<GroundZeroConfig>.JsonSaveFile(GroundZeroConstants.CONFIG_PATH, this);
    }
}
