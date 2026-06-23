class DeutschZOperationDeutschZConstants
{
    static const string PREFIX = "[DeutschZ_OperationDeutschZ]";
    static const string ROOT_PROFILE = "$profile:DeutschZ/";
    static const string PROFILE_DIR = "$profile:DeutschZ/OperationDeutschZ/";
    static const string LOG_DIR = "$profile:DeutschZ/OperationDeutschZ/Logs/";
    static const string CONFIG_PATH = "$profile:DeutschZ/OperationDeutschZ/OperationDeutschZConfig.json";
    static const string STATE_PATH = "$profile:DeutschZ/OperationDeutschZ/OperationDeutschZState.json";
    static const string VERSION = "0.1.0-online-test-safe";
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
    ref array<string> RequiredEventMods;
    int SafeBootOnly;

    void DeutschZOperationDeutschZConfig()
    {
        Defaults();
    }

    void Defaults()
    {
        Version = DeutschZOperationDeutschZConstants.VERSION;
        EnableOperationDeutschZ = 0;
        EnableDebugLogs = 1;
        EnableCampaignProgression = 0;
        EnableThreatLevel = 0;
        EnableEventChain = 0;
        EnableVipCrateUnlock = 0;
        SafeBootOnly = 1;

        RequiredEventMods = new array<string>;
        RequiredEventMods.Insert("DeutschZ_KotHZ");
        RequiredEventMods.Insert("DeutschZ_ConvoyZ");
        RequiredEventMods.Insert("DeutschZ_GroundZero");
        RequiredEventMods.Insert("DeutschZ_CourierZ");
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
