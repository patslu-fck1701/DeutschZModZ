class DeutschZTools_FeatureEntry
{
    string Key;
    string Label;
    string State;
    string Permission;
    string Notes;

    void DeutschZTools_FeatureEntry()
    {
        Key = "";
        Label = "";
        State = "prepared";
        Permission = "";
        Notes = "";
    }
}

class DeutschZTools_FeatureConfig
{
    int Version = 5;
    string ConfigInfo = "DeutschZ feature parity map. Auto generated under profiles/DeutschZ/Toolz/Config. State values: active, bridge, prepared, disabled. This file is generated for config planning and admin permission mapping.";
    ref array<ref DeutschZTools_FeatureEntry> Features;

    void DeutschZTools_FeatureConfig()
    {
        Features = new array<ref DeutschZTools_FeatureEntry>;
    }
}

class DeutschZTools_FeatureConfigService
{
    protected static ref DeutschZTools_FeatureConfig s_Features;

    static bool Load()
    {
        DeutschZTools_FileUtil.EnsureProfileDirs();

        if (!FileExist(DeutschZTools_Constants.FEATURE_FILE))
        {
            s_Features = CreateDefaults();
            JsonFileLoader<DeutschZTools_FeatureConfig>.JsonSaveFile(DeutschZTools_Constants.FEATURE_FILE, s_Features);
            DeutschZTools_Logger.Info("Created default feature config: " + DeutschZTools_Constants.FEATURE_FILE);
            return true;
        }

        s_Features = new DeutschZTools_FeatureConfig();
        JsonFileLoader<DeutschZTools_FeatureConfig>.JsonLoadFile(DeutschZTools_Constants.FEATURE_FILE, s_Features);
        if (!s_Features)
        {
            s_Features = CreateDefaults();
            DeutschZTools_Logger.Error("Failed to load feature config, fallback defaults active.");
            return false;
        }

        if (!s_Features.Features)
            s_Features.Features = new array<ref DeutschZTools_FeatureEntry>;

        DeutschZTools_Logger.Info("Feature config loaded. Entries: " + s_Features.Features.Count());
        return true;
    }

    static DeutschZTools_FeatureConfig CreateDefaults()
    {
        DeutschZTools_FeatureConfig cfg = new DeutschZTools_FeatureConfig();
        Add(cfg, "dashboard", "Dashboard", "active", DeutschZTools_Constants.PERM_MENU_OPEN, "Main status and fast actions.");
        Add(cfg, "players.list", "Player list", "active", DeutschZTools_Constants.PERM_PLAYER_LIST, "Online list with name, Steam64, position and health values.");
        Add(cfg, "players.heal", "Heal players", "active", DeutschZTools_Constants.PERM_PLAYER_HEAL, "Heal self and heal target by Steam64.");
        Add(cfg, "players.teleport", "Teleport players", "active", DeutschZTools_Constants.PERM_PLAYER_TELEPORT, "Teleport to player and bring player.");
        Add(cfg, "players.inventory", "Inventory view/edit", "prepared", DeutschZTools_Constants.PERM_PLAYER_INVENTORY_VIEW, "UI slot prepared; server inventory snapshot is not bound yet.");
        Add(cfg, "players.spectate", "Spectate and freecam", "prepared", DeutschZTools_Constants.PERM_PLAYER_SPECTATE, "Camera support planned as own DeutschZ implementation.");
        Add(cfg, "map.teleport", "Map and coord teleport", "active", DeutschZTools_Constants.PERM_MAP_TELEPORT, "Native map frame plus X/Z teleport fields.");
        Add(cfg, "spawn.object", "Object/item spawn", "active", DeutschZTools_Constants.PERM_SPAWN_OBJECT, "Classname spawn with optional attachment CSV.");
        Add(cfg, "spawn.presets", "Preset spawner", "prepared", DeutschZTools_Constants.PERM_SPAWN_PRESET, "Preset config planned; no third party preset code copied.");
        Add(cfg, "vehicles.repair", "Vehicle repair", "active", DeutschZTools_Constants.PERM_VEHICLE_REPAIR, "Repairs nearest vehicle and inventory health.");
        Add(cfg, "vehicles.flip", "Vehicle flip", "active", DeutschZTools_Constants.PERM_VEHICLE_FLIP, "Levels nearest vehicle orientation.");
        Add(cfg, "vehicles.teleport", "Vehicle teleport", "active", DeutschZTools_Constants.PERM_VEHICLE_TELEPORT, "Moves nearest vehicle to admin position.");
        Add(cfg, "weather.presets", "Weather presets", "active", DeutschZTools_Constants.PERM_WEATHER_SET, "Clear, rain, storm and fog presets.");
        Add(cfg, "weather.time", "Time manager", "prepared", DeutschZTools_Constants.PERM_WEATHER_TIME_SET, "Time controls are planned after weather presets.");
        Add(cfg, "events.koth", "KOTH bridge", "bridge", DeutschZTools_Constants.PERM_EVENT_RELOAD, "Status/start/stop/reload routed to DeutschZ KOTH AdminCommandBus when loaded.");
        Add(cfg, "esp", "ESP tools", "prepared", DeutschZTools_Constants.PERM_ESP_VIEW, "Own ESP/drag system planned.");
        Add(cfg, "objectbuilder", "Object builder", "prepared", DeutschZTools_Constants.PERM_OBJECT_BUILDER, "Own builder and building sets planned.");
        Add(cfg, "banmanager", "Ban manager", "prepared", DeutschZTools_Constants.PERM_BAN_MANAGER, "Own local/global ban config planned.");
        Add(cfg, "watchlist", "Watchlist", "prepared", DeutschZTools_Constants.PERM_WATCHLIST, "Own watchlist config planned.");
        Add(cfg, "garage.status", "DeutschZ Garage status", "active", DeutschZTools_Constants.PERM_GARAGE_ADMIN, "Status and reload call DeutschZ_Garage when loaded.");
        Add(cfg, "garage.admin", "DeutschZ Garage admin", "active", DeutschZTools_Constants.PERM_GARAGE_ADMIN, "Vehicle list and nearest vehicle impound are connected to DeutschZ_Garage.");
        Add(cfg, "banking.status", "DeutschZ Banking status", "active", DeutschZTools_Constants.PERM_BANKING_ADMIN, "Status and reload call DeutschZ_Banking when loaded.");
        Add(cfg, "banking.admin", "DeutschZ Banking admin", "active", DeutschZTools_Constants.PERM_BANKING_ADMIN, "Account lookup, add/remove money and audit rows are connected to DeutschZ_Banking.");
        Add(cfg, "groups", "DeutschZ Groups and markers", "bridge", DeutschZTools_Constants.PERM_GROUPS_ADMIN, "DeutschZ_Groups admin status/list/reload bridge.");
        Add(cfg, "traderz", "DeutschZ TraderZ", "bridge", DeutschZTools_Constants.PERM_TRADERZ_ADMIN, "DeutschZ_TraderZ status, reload, trader list and market category bridge.");
        Add(cfg, "playerfun", "PlayerFun", "active", DeutschZTools_Constants.PERM_PLAYER_FUN, "Freeze, unfreeze, vomit, size, spin and animal prank tools for admins.");
        return cfg;
    }

    static void Add(DeutschZTools_FeatureConfig cfg, string key, string label, string state, string permission, string notes)
    {
        if (!cfg || !cfg.Features)
            return;

        DeutschZTools_FeatureEntry entry = new DeutschZTools_FeatureEntry();
        entry.Key = key;
        entry.Label = label;
        entry.State = state;
        entry.Permission = permission;
        entry.Notes = notes;
        cfg.Features.Insert(entry);
    }

    static bool Reload()
    {
        s_Features = null;
        return Load();
    }
}
