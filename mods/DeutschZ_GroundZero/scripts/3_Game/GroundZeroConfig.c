/*
    DeutschZ_GroundZero
    Owner: Patrick Sluzalek / fck1701
    Module: 3_Game / GroundZeroConfig
    Purpose: Central JSON config with Load, Validate, Repair and Save workflow.
    Dependencies: DayZ scripts; optional CF/Expansion APIs only through adapter methods.
    Compliance: Original DeutschZ implementation. No copied foreign mod code, assets, configs or stubs.
*/

class GroundZeroStageConfig: Managed
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

class GroundZeroFinalWaveConfig: Managed
{
    int WaveId;
    string WaveName;
    int ZombieThreatLevel;
    int ZombieCount;
    int MilitaryAICount;
    int RogueAICount;
    float DelaySeconds;
}


// DeutschZ unified event config standard v1.
// Same JSON block name in every event config: DeutschZEventSettings.
class GroundZeroEventCoreSettings
{
    int Enabled;
    int MinOnlinePlayers;
    int MaxSimultaneousEvents;
    int MaxEventsPerRestart;
    int MaxRuntimeSeconds;
    int CleanupDelaySeconds;
    int DebugLogs;

    void GroundZeroEventCoreSettings()
    {
        Enabled = 1;
        MinOnlinePlayers = 1;
        MaxSimultaneousEvents = 1;
        MaxEventsPerRestart = 999;
        MaxRuntimeSeconds = 5400;
        CleanupDelaySeconds = 300;
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

class GroundZeroEventSchedulingSettings
{
    int AutoStartAfterRestart;
    int StartDelayMinSeconds;
    int StartDelayMaxSeconds;
    int RestartAfterFinish;
    int RestartDelayMinSeconds;
    int RestartDelayMaxSeconds;
    int NoPlayerRetryDelaySeconds;

    void GroundZeroEventSchedulingSettings()
    {
        AutoStartAfterRestart = 1;
        StartDelayMinSeconds = 4200;
        StartDelayMaxSeconds = 6600;
        RestartAfterFinish = 1;
        RestartDelayMinSeconds = 4200;
        RestartDelayMaxSeconds = 6600;
        NoPlayerRetryDelaySeconds = 600;
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

class GroundZeroEventMarkerSettings
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

    void GroundZeroEventMarkerSettings()
    {
        Enabled = 1;
        UseMapMarker = 1;
        Use3DMarker = 1;
        UseDynamicPositionUpdates = 1;
        UpdateIntervalSeconds = 30;
        ShowEventRadius = 1;
        ShowCarrierMarker = 1;
        ShowDroppedItemMarker = 1;
        ShowFinalMarker = 1;
        ShowExtractionMarker = 1;
        MarkerName = "DeutschZ GroundZero";
        MarkerIcon = "ContaminatedArea";
        MarkerColorARGB = -16711834;
        MarkerPrefix = "GroundZero_";
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
        if (MarkerColorARGB == 0) MarkerColorARGB = -16711834;
    }
}

class GroundZeroEventNotificationSettings
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

    void GroundZeroEventNotificationSettings()
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

class GroundZeroEventRewardSettings
{
    int Enabled;
    int RewardLifetimeSeconds;
    int DespawnWarningEnabled;
    int DespawnWarningSeconds;

    void GroundZeroEventRewardSettings()
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

class GroundZeroEventTestingSettings
{
    int FastTestMode;
    int CaptureHoldSeconds;
    int RequiredKillsToWin;
    int HackDurationSeconds;
    int WaveDelaySeconds;
    int StageAutoCompleteSeconds;
    int FinalDefenseSeconds;
    int ExtractionDurationSeconds;

    void GroundZeroEventTestingSettings()
    {
        FastTestMode = 0;
        CaptureHoldSeconds = 420;
        RequiredKillsToWin = 12;
        HackDurationSeconds = 90;
        WaveDelaySeconds = 90;
        StageAutoCompleteSeconds = 0;
        FinalDefenseSeconds = 420;
        ExtractionDurationSeconds = 60;
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

class GroundZeroEventSettings
{
    int SchemaVersion;
    string PresetName;
    string ConfigMode;
    ref GroundZeroEventCoreSettings Event;
    ref GroundZeroEventSchedulingSettings Scheduling;
    ref GroundZeroEventMarkerSettings Markers;
    ref GroundZeroEventNotificationSettings Notifications;
    ref GroundZeroEventRewardSettings Rewards;
    ref GroundZeroEventTestingSettings Testing;

    void GroundZeroEventSettings()
    {
        SchemaVersion = 1;
        PresetName = "GROUNDZERO_LIVE_CAMPAIGN_CHAIN";
        ConfigMode = "LiveCampaignChain";
        Event = new GroundZeroEventCoreSettings();
        Scheduling = new GroundZeroEventSchedulingSettings();
        Markers = new GroundZeroEventMarkerSettings();
        Notifications = new GroundZeroEventNotificationSettings();
        Rewards = new GroundZeroEventRewardSettings();
        Testing = new GroundZeroEventTestingSettings();
        Repair("DeutschZ GroundZero", "ContaminatedArea", "GroundZero_");
    }

    void Repair(string fallbackName, string fallbackIcon, string fallbackPrefix)
    {
        if (SchemaVersion < 1) SchemaVersion = 1;
        if (PresetName == "") PresetName = "GROUNDZERO_LIVE_CAMPAIGN_CHAIN";
        if (ConfigMode == "") ConfigMode = "LiveCampaignChain";
        if (!Event) Event = new GroundZeroEventCoreSettings();
        if (!Scheduling) Scheduling = new GroundZeroEventSchedulingSettings();
        if (!Markers) Markers = new GroundZeroEventMarkerSettings();
        if (!Notifications) Notifications = new GroundZeroEventNotificationSettings();
        if (!Rewards) Rewards = new GroundZeroEventRewardSettings();
        if (!Testing) Testing = new GroundZeroEventTestingSettings();
        Event.Repair();
        Scheduling.Repair();
        Markers.Repair(fallbackName, fallbackIcon, fallbackPrefix);
        Notifications.Repair();
        Rewards.Repair();
        Testing.Repair();
    }
}

class GroundZeroConfig
{
    ref GroundZeroEventSettings DeutschZEventSettings;
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
    float MarkerUpdateIntervalSeconds;
    int MaxActiveInfected;
    int MaxSpawnPerBatch;
    int SpawnBatchDelaySeconds;
    int WaveDelaySeconds;
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
    bool Enable3DMarkers;
    bool EnableDebugLogs;

    ref array<ref GroundZeroStageConfig> Stages;
    ref array<ref GroundZeroFinalWaveConfig> FinalWaves;
    ref array<vector> PossibleStagePositions;
    ref array<vector> PossibleFinalFacilityPositions;
    ref array<vector> PossibleExtractionPositions;


    void EnsureDeutschZEventSettings()
    {
        if (!DeutschZEventSettings)
            DeutschZEventSettings = new GroundZeroEventSettings();
        DeutschZEventSettings.Repair("DeutschZ GroundZero", "ContaminatedArea", "GroundZero_");
    }

    void ApplyDeutschZEventSettings()
    {
        EnsureDeutschZEventSettings();
        EnableGroundZero = DeutschZEventSettings.Event.Enabled == 1;
        AutoStartEnabled = DeutschZEventSettings.Scheduling.AutoStartAfterRestart == 1;
        AutoStartMinDelaySeconds = DeutschZEventSettings.Scheduling.StartDelayMinSeconds;
        AutoStartMaxDelaySeconds = DeutschZEventSettings.Scheduling.StartDelayMaxSeconds;
        MinOnlinePlayersToAutoStart = DeutschZEventSettings.Event.MinOnlinePlayers;
        EventMinDurationSeconds = DeutschZEventSettings.Event.MaxRuntimeSeconds;
        EventMaxDurationSeconds = DeutschZEventSettings.Event.MaxRuntimeSeconds;
        EventCleanupDelaySeconds = DeutschZEventSettings.Event.CleanupDelaySeconds;
        EnableMapMarkers = DeutschZEventSettings.Markers.Enabled == 1 && DeutschZEventSettings.Markers.UseMapMarker == 1;
        Enable3DMarkers = DeutschZEventSettings.Markers.Enabled == 1 && DeutschZEventSettings.Markers.Use3DMarker == 1;
        EnableGlobalNotifications = DeutschZEventSettings.Notifications.Enabled == 1;
        EnableDebugLogs = DeutschZEventSettings.Event.DebugLogs == 1;
        CarrierMarkerUpdateSeconds = DeutschZEventSettings.Markers.UpdateIntervalSeconds;
        CarrierDropMarkerUpdateSeconds = DeutschZEventSettings.Markers.UpdateIntervalSeconds;
        MarkerUpdateIntervalSeconds = DeutschZEventSettings.Markers.UpdateIntervalSeconds;
        if (MarkerUpdateIntervalSeconds < 3) MarkerUpdateIntervalSeconds = 3;
        FinalDefenseSeconds = DeutschZEventSettings.Testing.FinalDefenseSeconds;
        ExtractionDurationSeconds = DeutschZEventSettings.Testing.ExtractionDurationSeconds;

        foreach (GroundZeroStageConfig stage: Stages)
        {
            if (!stage) continue;
            if (DeutschZEventSettings.Testing.FastTestMode == 1)
                stage.CompletionHoldSeconds = DeutschZEventSettings.Testing.StageAutoCompleteSeconds;
        }

        foreach (GroundZeroFinalWaveConfig wave: FinalWaves)
        {
            if (!wave) continue;
            if (DeutschZEventSettings.Testing.FastTestMode == 1)
                wave.DelaySeconds = DeutschZEventSettings.Testing.WaveDelaySeconds;
        }
    }

    bool MarkersEnabled()
    {
        EnsureDeutschZEventSettings();
        return DeutschZEventSettings.Markers.Enabled == 1;
    }

    bool UseMapMarker()
    {
        EnsureDeutschZEventSettings();
        return DeutschZEventSettings.Markers.Enabled == 1 && DeutschZEventSettings.Markers.UseMapMarker == 1;
    }

    bool Use3DMarker()
    {
        EnsureDeutschZEventSettings();
        return DeutschZEventSettings.Markers.Enabled == 1 && DeutschZEventSettings.Markers.Use3DMarker == 1;
    }

    bool UseDynamicMarkerUpdates()
    {
        EnsureDeutschZEventSettings();
        return DeutschZEventSettings.Markers.Enabled == 1 && DeutschZEventSettings.Markers.UseDynamicPositionUpdates == 1;
    }

    bool ShowCarrierMarker()
    {
        EnsureDeutschZEventSettings();
        return DeutschZEventSettings.Markers.Enabled == 1 && DeutschZEventSettings.Markers.ShowCarrierMarker == 1;
    }

    bool ShowDroppedItemMarker()
    {
        EnsureDeutschZEventSettings();
        return DeutschZEventSettings.Markers.Enabled == 1 && DeutschZEventSettings.Markers.ShowDroppedItemMarker == 1;
    }

    bool ShowFinalMarker()
    {
        EnsureDeutschZEventSettings();
        return DeutschZEventSettings.Markers.Enabled == 1 && DeutschZEventSettings.Markers.ShowFinalMarker == 1;
    }

    bool ShowExtractionMarker()
    {
        EnsureDeutschZEventSettings();
        return DeutschZEventSettings.Markers.Enabled == 1 && DeutschZEventSettings.Markers.ShowExtractionMarker == 1;
    }

    bool UseExpansionNotifications()
    {
        EnsureDeutschZEventSettings();
        return DeutschZEventSettings.Notifications.Enabled == 1 && DeutschZEventSettings.Notifications.UseExpansionNotifications == 1;
    }

    bool UseVanillaNotifications()
    {
        EnsureDeutschZEventSettings();
        return DeutschZEventSettings.Notifications.Enabled == 1 && DeutschZEventSettings.Notifications.UseVanillaNotifications == 1;
    }

    bool UseChatMessages()
    {
        EnsureDeutschZEventSettings();
        return DeutschZEventSettings.Notifications.Enabled == 1 && DeutschZEventSettings.Notifications.UseChatMessages == 1;
    }

    int GetStageRequiredKills()
    {
        EnsureDeutschZEventSettings();
        int required = DeutschZEventSettings.Testing.RequiredKillsToWin;
        if (required < 1) required = 1;
        return required;
    }

    void GroundZeroConfig()
    {
        DeutschZEventSettings = new GroundZeroEventSettings();
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
        ConfigVersion = 6;
        EnableGroundZero = true;
        AutoStartEnabled = true;
        AutoStartMinDelaySeconds = 4200;
        AutoStartMaxDelaySeconds = 6600;
        MinOnlinePlayersToAutoStart = 1;

        EventMinDurationSeconds = 2700;
        EventMaxDurationSeconds = 5400;
        EventCleanupDelaySeconds = 300;

        AllowTimedObjectiveFallback = false;
        RetryLimitPerEvent = 3;
        RetrySpawnBackDistanceMin = 300;
        RetrySpawnBackDistanceMax = 600;
        AllowRetryAfterPvPDeath = false;
        RemoveCampaignItemsOnDeath = true;
        RetryMinimalLoadout.Clear();
        RetryMinimalLoadout.Insert("BandageDressing");
        RetryMinimalLoadout.Insert("StoneKnife");
        RetryMinimalLoadout.Insert("WaterBottle");

        CarrierMarkerUpdateSeconds = 30;
        CarrierDropMarkerUpdateSeconds = 30;
        MarkerUpdateIntervalSeconds = 30;
        MaxActiveInfected = 25;
        MaxSpawnPerBatch = 5;
        SpawnBatchDelaySeconds = 8;
        WaveDelaySeconds = 90;
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
        FinalDefenseSeconds = 420;
        ExtractionDurationSeconds = 60;
        ExtractionRadius = 25;

        EnableRewards = true;
        RewardMoneySuccess = 250000;
        RewardBattlepassXPSuccess = 5000;
        RewardMoneyFail = 0;
        RewardBattlepassXPFail = 500;

        EnableGlobalNotifications = true;
        EnableMapMarkers = true;
        Enable3DMarkers = true;
        EnableDebugLogs = true;

        BuildDefaultStages();
        BuildDefaultFinalWaves();
        BuildDefaultPositions();
        EnsureDeutschZEventSettings();
        ApplyDeutschZEventSettings();
    }

    void BuildDefaultStages()
    {
        Stages.Clear();
        AddStage(1, "Signalstation", "Signalquelle untersuchen und Datenfragment sichern", ItemAlphaDataModule, 1, 4, 0, 0, 120, 60, true);
        AddStage(2, "Generatorstation", "Generator pruefen: Spezialteil erforderlich", "DZOP_TechnicalFragment_GroundZero", 2, 4, 0, 0, 120, 60, true);
        AddStage(3, "Hold-Zone", "Zone halten, letzte Welle traegt das Generator-Zuendmodul", "DZGZ_GeneratorSparkPlug", 3, 12, 0, 0, 35, 420, true);
        AddStage(4, "Datenterminal", "Containment-Protokoll laden und Forschungsdaten extrahieren", "DZGZ_EncryptedResearchData", 4, 8, 0, 0, 120, 90, true);
        AddStage(5, "Containment Cache", "Probe sichern, CardReader bergen und finalen Cache freigeben", "DZOP_DamagedCardReader", 5, 10, 0, 0, 120, 120, true);
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
        AddFinalWave(1, "Militaerzombies", 2, 4, 0, 0, 0);
        AddFinalWave(2, "Hunter", 3, 4, 0, 0, 30);
        AddFinalWave(3, "Elite-Welle", 5, 5, 0, 0, 60);
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
        // FIX43: Green Mountain is Trader/SafeZone and must never be used for GroundZero.
        // Stage positions are intentionally different so the campaign does not stack every task on one spot.
        PossibleStagePositions.Insert("4510 0 8280");
        PossibleStagePositions.Insert("6570 0 6020");
        PossibleStagePositions.Insert("8250 0 10820");
        PossibleStagePositions.Insert("1660 0 14230");
        PossibleStagePositions.Insert("12070 0 12600");

        PossibleFinalFacilityPositions.Insert("1680 0 14240");
        PossibleFinalFacilityPositions.Insert("12070 0 12600");
        PossibleFinalFacilityPositions.Insert("10450 0 9800");

        PossibleExtractionPositions.Insert("10500 0 9800");
        PossibleExtractionPositions.Insert("3200 0 6800");
        PossibleExtractionPositions.Insert("11950 0 3480");
    }

    void Repair()
    {
        if (!Stages) Stages = new array<ref GroundZeroStageConfig>();
        if (!FinalWaves) FinalWaves = new array<ref GroundZeroFinalWaveConfig>();
        if (!PossibleStagePositions) PossibleStagePositions = new array<vector>();
        if (!PossibleFinalFacilityPositions) PossibleFinalFacilityPositions = new array<vector>();
        if (!PossibleExtractionPositions) PossibleExtractionPositions = new array<vector>();
        if (!RetryMinimalLoadout) RetryMinimalLoadout = new array<string>();

        EnsureDeutschZEventSettings();
        ApplyDeutschZEventSettings();

        if (ConfigVersion < 6) ConfigVersion = 6;
        if (AutoStartMaxDelaySeconds < AutoStartMinDelaySeconds) AutoStartMaxDelaySeconds = AutoStartMinDelaySeconds + 1800;
        if (MinOnlinePlayersToAutoStart < 0) MinOnlinePlayersToAutoStart = 0;
        if (EventMinDurationSeconds < 600) EventMinDurationSeconds = 2700;
        if (EventMaxDurationSeconds < EventMinDurationSeconds) EventMaxDurationSeconds = EventMinDurationSeconds + 1800;
        if (RetryLimitPerEvent < 0) RetryLimitPerEvent = 0;
        if (RetrySpawnBackDistanceMin < 50) RetrySpawnBackDistanceMin = 300;
        if (RetrySpawnBackDistanceMax < RetrySpawnBackDistanceMin) RetrySpawnBackDistanceMax = RetrySpawnBackDistanceMin + 200;
        if (CarrierMarkerUpdateSeconds < 1) CarrierMarkerUpdateSeconds = 1;
        if (CarrierDropMarkerUpdateSeconds < 1) CarrierDropMarkerUpdateSeconds = 1;
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
