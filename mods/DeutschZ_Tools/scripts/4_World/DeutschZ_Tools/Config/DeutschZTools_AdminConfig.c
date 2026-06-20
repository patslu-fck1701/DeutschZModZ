class DeutschZTools_AdminEntry
{
    string Steam64;
    string Name;
    string Level;
    ref TStringArray Permissions;

    void DeutschZTools_AdminEntry()
    {
        Steam64 = "";
        Name = "";
        Level = "Admin";
        Permissions = new TStringArray;
    }
}

class DeutschZTools_AdminConfig
{
    int Version = 10;
    string ConfigInfo = "DeutschZ Tools admin list. Auto generated under profiles/DeutschZ/Toolz/Config. Owner can use tools.* for all permissions.";
    ref array<ref DeutschZTools_AdminEntry> Admins;

    void DeutschZTools_AdminConfig()
    {
        Admins = new array<ref DeutschZTools_AdminEntry>;
    }
}

class DeutschZTools_PermissionService
{
    protected static ref DeutschZTools_AdminConfig s_AdminConfig;
    protected static bool s_Loaded;

    static bool Load()
    {
        DeutschZTools_FileUtil.EnsureProfileDirs();
        s_AdminConfig = new DeutschZTools_AdminConfig();
        s_Loaded = true;

        if (!FileExist(DeutschZTools_Constants.ADMIN_FILE))
        {
            CreateDefaultAdmins(s_AdminConfig);
            JsonFileLoader<DeutschZTools_AdminConfig>.JsonSaveFile(DeutschZTools_Constants.ADMIN_FILE, s_AdminConfig);
            DeutschZTools_Logger.Info("Created default admin config: " + DeutschZTools_Constants.ADMIN_FILE);
            return true;
        }

        JsonFileLoader<DeutschZTools_AdminConfig>.JsonLoadFile(DeutschZTools_Constants.ADMIN_FILE, s_AdminConfig);

        if (!s_AdminConfig)
        {
            s_AdminConfig = new DeutschZTools_AdminConfig();
            DeutschZTools_Logger.Error("Failed to load admin config, no admins active.");
            return false;
        }

        if (!s_AdminConfig.Admins)
            s_AdminConfig.Admins = new array<ref DeutschZTools_AdminEntry>;

        if (EnsureDefaultRuntimeAdmins(s_AdminConfig))
            JsonFileLoader<DeutschZTools_AdminConfig>.JsonSaveFile(DeutschZTools_Constants.ADMIN_FILE, s_AdminConfig);

        DeutschZTools_Logger.Info("Admin config loaded. Admin entries: " + s_AdminConfig.Admins.Count());
        return true;
    }

    static bool HasAdminSteam64(DeutschZTools_AdminConfig cfg, string steam64)
    {
        if (!cfg || !cfg.Admins)
            return false;

        foreach (DeutschZTools_AdminEntry entry : cfg.Admins)
        {
            if (entry && entry.Steam64 == steam64)
                return true;
        }

        return false;
    }

    static bool EnsureOwnerAdmin(DeutschZTools_AdminConfig cfg, string name, string steam64)
    {
        if (!cfg || !cfg.Admins)
            return false;
        if (HasAdminSteam64(cfg, steam64))
            return false;

        DeutschZTools_AdminEntry entry = new DeutschZTools_AdminEntry();
        entry.Name = name;
        entry.Steam64 = steam64;
        entry.Level = "Admin";
        entry.Permissions.Insert(DeutschZTools_Constants.PERM_ALL);
        cfg.Admins.Insert(entry);
        return true;
    }

    static bool EnsureDefaultRuntimeAdmins(DeutschZTools_AdminConfig cfg)
    {
        bool changed = false;
        changed = EnsureOwnerAdmin(cfg, "fck1701", "76561199819501556") || changed;
        changed = EnsureOwnerAdmin(cfg, "Devilmagic", "76561198013329655") || changed;
        return changed;
    }

    static void CreateDefaultAdmins(DeutschZTools_AdminConfig cfg)
    {
        if (!cfg || !cfg.Admins)
            return;

        DeutschZTools_AdminEntry owner = new DeutschZTools_AdminEntry();
        owner.Name = "fck1701";
        owner.Steam64 = "76561199819501556";
        owner.Level = "Owner";
        owner.Permissions.Insert(DeutschZTools_Constants.PERM_ALL);
        cfg.Admins.Insert(owner);

        DeutschZTools_AdminEntry admin = new DeutschZTools_AdminEntry();
        admin.Name = "Halftan Fenrisson";
        admin.Steam64 = "76561198114486994";
        admin.Level = "Admin";
        admin.Permissions.Insert(DeutschZTools_Constants.PERM_MENU_OPEN);
        admin.Permissions.Insert(DeutschZTools_Constants.PERM_MAP_VIEW);
        admin.Permissions.Insert(DeutschZTools_Constants.PERM_MAP_TELEPORT);
        admin.Permissions.Insert(DeutschZTools_Constants.PERM_PLAYER_LIST);
        admin.Permissions.Insert(DeutschZTools_Constants.PERM_PLAYER_HEAL);
        admin.Permissions.Insert(DeutschZTools_Constants.PERM_PLAYER_TELEPORT);
        admin.Permissions.Insert(DeutschZTools_Constants.PERM_VEHICLE_REPAIR);
        admin.Permissions.Insert(DeutschZTools_Constants.PERM_VEHICLE_FLIP);
        admin.Permissions.Insert(DeutschZTools_Constants.PERM_VEHICLE_TELEPORT);
        admin.Permissions.Insert(DeutschZTools_Constants.PERM_PLAYER_INVENTORY_VIEW);
        admin.Permissions.Insert(DeutschZTools_Constants.PERM_SPAWN_PRESET);
        admin.Permissions.Insert(DeutschZTools_Constants.PERM_WEATHER_TIME_SET);
        admin.Permissions.Insert(DeutschZTools_Constants.PERM_SERVER_MESSAGE);
        admin.Permissions.Insert(DeutschZTools_Constants.PERM_GARAGE_ADMIN);
        admin.Permissions.Insert(DeutschZTools_Constants.PERM_BANKING_ADMIN);
        admin.Permissions.Insert(DeutschZTools_Constants.PERM_GROUPS_ADMIN);
        admin.Permissions.Insert(DeutschZTools_Constants.PERM_MARKERS_ADMIN);
        admin.Permissions.Insert(DeutschZTools_Constants.PERM_TRADERZ_ADMIN);
        admin.Permissions.Insert(DeutschZTools_Constants.PERM_PLAYER_FUN);
        admin.Permissions.Insert(DeutschZTools_Constants.PERM_SPAWN_OBJECT);
        admin.Permissions.Insert(DeutschZTools_Constants.PERM_WEATHER_SET);
        admin.Permissions.Insert(DeutschZTools_Constants.PERM_SERVER_CONFIG_RELOAD);
        admin.Permissions.Insert(DeutschZTools_Constants.PERM_EVENT_STATUS);
        admin.Permissions.Insert(DeutschZTools_Constants.PERM_EVENT_FORCE_START);
        admin.Permissions.Insert(DeutschZTools_Constants.PERM_EVENT_FORCE_STOP);
        admin.Permissions.Insert(DeutschZTools_Constants.PERM_EVENT_RELOAD);
        cfg.Admins.Insert(admin);

        DeutschZTools_AdminEntry devilmagic = new DeutschZTools_AdminEntry();
        devilmagic.Name = "Devilmagic";
        devilmagic.Steam64 = "76561198013329655";
        devilmagic.Level = "Admin";
        devilmagic.Permissions.Insert(DeutschZTools_Constants.PERM_ALL);
        cfg.Admins.Insert(devilmagic);
    }

    static bool Reload()
    {
        s_AdminConfig = null;
        s_Loaded = false;
        return Load();
    }

    static bool IsAdmin(PlayerIdentity identity)
    {
        return HasPermission(identity, DeutschZTools_Constants.PERM_MENU_OPEN);
    }

    static bool HasPermission(PlayerIdentity identity, string permission)
    {
        if (!identity)
            return false;

        if (!s_Loaded)
            Load();

        if (!s_AdminConfig || !s_AdminConfig.Admins)
            return false;

        string steam64 = identity.GetPlainId();
        if (steam64 == "")
            return false;

        foreach (DeutschZTools_AdminEntry entry : s_AdminConfig.Admins)
        {
            if (!entry)
                continue;

            if (entry.Steam64 != steam64)
                continue;

            if (!entry.Permissions)
                return false;

            if (entry.Permissions.Find(DeutschZTools_Constants.PERM_ALL) > -1)
                return true;

            if (entry.Permissions.Find(permission) > -1)
                return true;

            return false;
        }

        return false;
    }

    static string GetMissingPermissionText(string permission)
    {
        return "No permission: " + permission;
    }
}
