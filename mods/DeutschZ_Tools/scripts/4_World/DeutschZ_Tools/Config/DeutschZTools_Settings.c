class DeutschZTools_Settings
{
    int Version = 9;
    int DebugMode = 1;
    int EnableAdminMenuHotkey = 1;
    string MenuHotkeyInfo = "Default input UADeutschZToolsMenu = F10. Input XML uses actions and preset block.";

    string DefaultMapTheme = "Light";
    string LightMapTexture = "DeutschZ_Tools\\data\\maps\\DeutschZ_Map_Chernarus_Base_4096.paa";
    string DarkMapTexture = "DeutschZ_Tools\\data\\maps\\DeutschZ_Map_Chernarus_Dark_4096.paa";
    string ServerLogoTexture = "DeutschZ_Tools\\data\\logos\\DeutschZ_Logo.paa";
    float WorldSize = 15360.0;

    string UIThemeName = "Anthracite Neon Green";
    float UIBackgroundOpacity = 0.86;
    float UIPanelOpacity = 0.78;
    float RepairVehicleRadius = 8.0;
    float SpawnObjectDistance = 4.0;
    float VehicleActionRadius = 10.0;
    int PlayerFunFreezeTickMs = 250;
    float PlayerFunTinyScale = 0.65;
    float PlayerFunGiantScale = 1.35;
    int AllowScriptedRestart = 0;
    int RestartCountdownDefaultSeconds = 300;
    int AllowDangerousActions = 0;
    int EnableAuditLog = 1;
    int EnablePlayerTools = 1;
    int EnableMapTeleport = 1;
    int EnableSpawnTools = 1;
    int EnableVehicleTools = 1;
    int EnableWeatherTools = 1;
    int EnableEventTools = 1;
    int EnableKOTHSettingsTab = 1;
    int EnableESPTools = 0;
    int EnableObjectBuilder = 0;
    int EnableBanManager = 0;
    int EnableWatchlist = 0;
    int EnableFreecam = 0;
    int EnableGarageBridge = 1;
    int EnableBankingBridge = 1;
    int EnableGroupsBridge = 1;
    int EnableKOTHBridge = 1;
    int EnablePlayerFunTools = 1;
    int EnableTraderZBridge = 1;
    string ActiveFeatureInfo = "Active now: menu, own RPC, permission check, player list, heal, teleport, bring, map teleport fields, spawn object with attachments, vehicle repair/flip/teleport, weather presets, config reload, KOTH bridge, Groups bridge, Banking/Garage bridge, TraderZ bridge and PlayerFun tools.";
    string PlannedParityInfo = "Prepared LBmaster parity: inventory view/edit, spectate/freecam, ESP, object builder, item presets, ban/watchlist, server monitor, audit UI and marker/group admin. Banking/Garage/Groups/KOTH/TraderZ bridges are connected when the mods are loaded.";
    string ConfigInfo = "DeutschZ_Tools settings. Auto generated under profiles/DeutschZ/Toolz/Config. Scripted restart and dangerous actions are disabled by default. Expansion is optional only.";
}

class DeutschZTools_SettingsService
{
    protected static ref DeutschZTools_Settings s_Settings;

    static DeutschZTools_Settings Get()
    {
        if (!s_Settings)
            Load();

        return s_Settings;
    }

    static bool Load()
    {
        DeutschZTools_FileUtil.EnsureProfileDirs();

        if (!FileExist(DeutschZTools_Constants.SETTINGS_FILE))
        {
            s_Settings = new DeutschZTools_Settings();
            JsonFileLoader<DeutschZTools_Settings>.JsonSaveFile(DeutschZTools_Constants.SETTINGS_FILE, s_Settings);
            DeutschZTools_Logger.Info("Created default settings: " + DeutschZTools_Constants.SETTINGS_FILE);
            return true;
        }

        s_Settings = new DeutschZTools_Settings();
        JsonFileLoader<DeutschZTools_Settings>.JsonLoadFile(DeutschZTools_Constants.SETTINGS_FILE, s_Settings);

        if (!s_Settings)
        {
            s_Settings = new DeutschZTools_Settings();
            DeutschZTools_Logger.Error("Failed to load settings, fallback defaults active.");
            return false;
        }

        DeutschZTools_Logger.Info("Settings loaded.");
        return true;
    }

    static bool Reload()
    {
        s_Settings = null;
        return Load();
    }
}
