class DeutschZOperationDeutschZConstants
{
    static const string PREFIX = "[DeutschZ_OperationDeutschZ]";
    static const string ROOT_PROFILE = "$profile:DeutschZ/";
    static const string PROFILE_DIR = "$profile:DeutschZ/OperationDeutschZ/";
    static const string CONFIG_DIR = "$profile:DeutschZ/OperationDeutschZ/Config/";
    static const string DATA_DIR = "$profile:DeutschZ/OperationDeutschZ/Data/";
    static const string LOG_DIR = "$profile:DeutschZ/OperationDeutschZ/Logs/";
    static const string CONFIG_PATH = "$profile:DeutschZ/OperationDeutschZ/OperationDeutschZConfig.json";
    static const string STATE_PATH = "$profile:DeutschZ/OperationDeutschZ/OperationDeutschZState.json";
    static const string VERSION = "0.9.4-campaign-chain-test";
}

class DeutschZOperationDeutschZConfig
{
    string Version;
    int EnableOperationDeutschZ;
    int EnableDebugLogs;
    int EnableCampaignProgression;
    int EnableThreatLevel;
    int EnableEventChain;
    int EnableVipCrateUnlock;
    int EnableRiddleStart;
    int InitialSignalDelayMinMinutes;
    int InitialSignalDelayMaxMinutes;
    int PingIntervalMinMinutes;
    int PingIntervalMaxMinutes;
    int PingMarkerLifetimeSeconds;
    int PingMarkerRadiusMeters;
    int ExactFindRadiusMeters;
    int EnableItemCombination;
    int EnableFinalLocation;
    int EnableFinalReward;
    ref array<string> CampaignStates;
    ref array<string> StartFindItems;
    ref array<string> RequiredProgressionItems;
    ref array<string> CombinationPlan;
    ref array<string> RequiredEventMods;
    int SafeBootOnly;

    void DeutschZOperationDeutschZConfig()
    {
        Defaults();
    }

    void Defaults()
    {
        Version = DeutschZOperationDeutschZConstants.VERSION;
        EnableOperationDeutschZ = 1;
        EnableDebugLogs = 1;
        EnableCampaignProgression = 1;
        EnableThreatLevel = 0;
        EnableEventChain = 1;
        EnableVipCrateUnlock = 0;
        EnableRiddleStart = 1;
        InitialSignalDelayMinMinutes = 20;
        InitialSignalDelayMaxMinutes = 45;
        PingIntervalMinMinutes = 30;
        PingIntervalMaxMinutes = 60;
        PingMarkerLifetimeSeconds = 90;
        PingMarkerRadiusMeters = 250;
        ExactFindRadiusMeters = 8;
        EnableItemCombination = 1;
        EnableFinalLocation = 0;
        EnableFinalReward = 0;
        SafeBootOnly = 0;

        RequiredEventMods = new array<string>;
        RequiredEventMods.Insert("DeutschZ_KotHZ");
        RequiredEventMods.Insert("DeutschZ_ConvoyZ");
        RequiredEventMods.Insert("DeutschZ_GroundZero");
        RequiredEventMods.Insert("DeutschZ_CourierZ");

        CampaignStates = new array<string>;
        CampaignStates.Insert("WAITING_FOR_SIGNAL");
        CampaignStates.Insert("SIGNAL_NOTIFY_SENT");
        CampaignStates.Insert("PING_ACTIVE");
        CampaignStates.Insert("PING_SILENT_COOLDOWN");
        CampaignStates.Insert("BLACKBOX_DISCOVERED");
        CampaignStates.Insert("FIRST_FRAGMENT_FOUND");
        CampaignStates.Insert("EVENT_ITEMS_REQUIRED");
        CampaignStates.Insert("COMBINATION_READY");
        CampaignStates.Insert("TREASURE_MAP_CREATED");
        CampaignStates.Insert("FINAL_LOCATION_UNLOCKED");
        CampaignStates.Insert("OPERATION_COMPLETE");

        StartFindItems = new array<string>;
        StartFindItems.Insert("DZOP_DestroyedBlackBox");
        StartFindItems.Insert("DZOP_BurnedNote");
        StartFindItems.Insert("DZOP_TreasureMapFragment_A");

        RequiredProgressionItems = new array<string>;
        RequiredProgressionItems.Insert("DZOP_Keycard_ConvoyAlpha");
        RequiredProgressionItems.Insert("DZOP_DamagedCardReader");
        RequiredProgressionItems.Insert("DZCR_CipherDocument");
        RequiredProgressionItems.Insert("DZOP_CipherFragment_Courier");
        RequiredProgressionItems.Insert("DZOP_TechnicalFragment_GroundZero");
        RequiredProgressionItems.Insert("DZGZ_SignalCore");
        RequiredProgressionItems.Insert("DZ_BossDogtag");
        RequiredProgressionItems.Insert("DZ_RadioCrystal");
        RequiredProgressionItems.Insert("DZOP_SignalFragment_KotHZ");

        CombinationPlan = new array<string>;
        CombinationPlan.Insert("DZOP_Keycard_ConvoyAlpha + DZOP_DamagedCardReader = DZOP_DecodedKeycard");
        CombinationPlan.Insert("DZOP_DecodedKeycard + DZCR_CipherDocument + DZOP_TreasureMapFragment_A = DZOP_TreasureMapFragment_B");
        CombinationPlan.Insert("DZOP_TreasureMapFragment_B + DZ_BossDogtag + DZ_RadioCrystal = DZOP_OperationTreasureMap");
    }
}

class DeutschZOperationDeutschZState
{
    string Version;
    int CampaignProgress;
    int ThreatLevel;
    int LastEventChainStep;
    int VipCrateUnlocked;
    string LastBootUtc;

    void DeutschZOperationDeutschZState()
    {
        Defaults();
    }

    void Defaults()
    {
        Version = DeutschZOperationDeutschZConstants.VERSION;
        CampaignProgress = 0;
        ThreatLevel = 0;
        LastEventChainStep = 0;
        VipCrateUnlocked = 0;
        LastBootUtc = "safe-boot-created";
    }
}

class DeutschZOperationDeutschZSafeBoot
{
    static ref DeutschZOperationDeutschZConfig s_Config;
    static ref DeutschZOperationDeutschZState s_State;

    static void Init()
    {
        if (!GetGame() || !GetGame().IsServer())
            return;

        Print(DeutschZOperationDeutschZConstants.PREFIX + " Init start");
        EnsureFolders();
        LoadConfig();
        LoadState();
        Print(DeutschZOperationDeutschZConstants.PREFIX + " Init done");
    }

    static void EnsureFolders()
    {
        MakeDirectory(DeutschZOperationDeutschZConstants.ROOT_PROFILE);
        MakeDirectory(DeutschZOperationDeutschZConstants.PROFILE_DIR);
        MakeDirectory(DeutschZOperationDeutschZConstants.CONFIG_DIR);
        MakeDirectory(DeutschZOperationDeutschZConstants.DATA_DIR);
        MakeDirectory(DeutschZOperationDeutschZConstants.LOG_DIR);
        Print(DeutschZOperationDeutschZConstants.PREFIX + " Profile folders ensured");
    }

    static void LoadConfig()
    {
        s_Config = new DeutschZOperationDeutschZConfig();

        if (!FileExist(DeutschZOperationDeutschZConstants.CONFIG_PATH))
        {
            JsonFileLoader<DeutschZOperationDeutschZConfig>.JsonSaveFile(DeutschZOperationDeutschZConstants.CONFIG_PATH, s_Config);
            Print(DeutschZOperationDeutschZConstants.PREFIX + " Config created");
        }

        JsonFileLoader<DeutschZOperationDeutschZConfig>.JsonLoadFile(DeutschZOperationDeutschZConstants.CONFIG_PATH, s_Config);
        Print(DeutschZOperationDeutschZConstants.PREFIX + " Config loaded");
    }

    static void LoadState()
    {
        s_State = new DeutschZOperationDeutschZState();

        if (!FileExist(DeutschZOperationDeutschZConstants.STATE_PATH))
        {
            JsonFileLoader<DeutschZOperationDeutschZState>.JsonSaveFile(DeutschZOperationDeutschZConstants.STATE_PATH, s_State);
            Print(DeutschZOperationDeutschZConstants.PREFIX + " State created");
        }

        JsonFileLoader<DeutschZOperationDeutschZState>.JsonLoadFile(DeutschZOperationDeutschZConstants.STATE_PATH, s_State);
        Print(DeutschZOperationDeutschZConstants.PREFIX + " State loaded");
    }
}
