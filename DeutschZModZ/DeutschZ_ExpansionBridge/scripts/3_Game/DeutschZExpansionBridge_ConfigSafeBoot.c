/*
    DeutschZ ExpansionBridge Config SafeBoot.
    Purpose: Create canonical profile config on every server start when missing.
*/

class DeutschZExpansionBridgeConfig
{
    string Version;
    int EnableBridge;
    int EnableMarkerProvider;
    int EnableNotificationProvider;
    int EnableAIProvider;
    int EnableDebugLogs;

    void DeutschZExpansionBridgeConfig()
    {
        Version = "1";
        EnableBridge = 1;
        EnableMarkerProvider = 1;
        EnableNotificationProvider = 1;
        EnableAIProvider = 1;
        EnableDebugLogs = 0;
    }
}

class DeutschZExpansionBridge_ConfigSafeBoot
{
    static const string ROOT_PROFILE = "$profile:DeutschZ/";
    static const string PROFILE_DIR = "$profile:DeutschZ/ExpansionBridge/";
    static const string CONFIG_DIR = "$profile:DeutschZ/ExpansionBridge/Config/";
    static const string DATA_DIR = "$profile:DeutschZ/ExpansionBridge/Data/";
    static const string LOG_DIR = "$profile:DeutschZ/ExpansionBridge/Logs/";
    static const string CONFIG_PATH = "$profile:DeutschZ/ExpansionBridge/Config/ExpansionBridgeConfig.json";

    static ref DeutschZExpansionBridgeConfig s_Config;

    static void Ensure()
    {
        if (!GetGame() || !GetGame().IsClient())
        {
            MakeDirectory(ROOT_PROFILE);
            MakeDirectory(PROFILE_DIR);
            MakeDirectory(CONFIG_DIR);
            MakeDirectory(DATA_DIR);
            MakeDirectory(LOG_DIR);

            if (!s_Config)
                s_Config = new DeutschZExpansionBridgeConfig();

            if (!FileExist(CONFIG_PATH))
            {
                JsonFileLoader<DeutschZExpansionBridgeConfig>.JsonSaveFile(CONFIG_PATH, s_Config);
                Print("[DeutschZ_ExpansionBridge] Config created: " + CONFIG_PATH);
            }
            else
            {
                JsonFileLoader<DeutschZExpansionBridgeConfig>.JsonLoadFile(CONFIG_PATH, s_Config);
                Print("[DeutschZ_ExpansionBridge] Config loaded: " + CONFIG_PATH);
            }
        }
    }
}
