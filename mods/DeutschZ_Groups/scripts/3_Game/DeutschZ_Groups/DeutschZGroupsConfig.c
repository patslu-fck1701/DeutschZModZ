class DeutschZGroupsConfig
{
    int ConfigVersion = 6;
    int EnableGroups = 1;
    int EnableMapLayer = 1;
    int EnableGroupMarkers = 1;
    int EnablePrivateMarkers = 1;
    int EnableServerMarkers = 1;
    int EnablePlayerMarkers = 1;
    int EnableGroupChat = 1;
    int EnableAuditLog = 1;
    int EnableAlliances = 1;
    int EnableGarageBridge = 1;
    int EnableBankingBridge = 1;
    int EnableGPSHud = 0;
    int EnableCompassHud = 0;
    int MaxGroupMembersDefault = 12;
    int MaxGroupMarkersDefault = 25;
    int MaxPrivateMarkersPerPlayer = 35;
    int MaxChatHistory = 60;
    int MaxAuditEntries = 120;
    int AutoSaveIntervalSeconds = 120;
    int PlayerSyncIntervalSeconds = 10;
    int MarkerSyncIntervalSeconds = 10;
    int InviteLifetimeSeconds = 300;
    string RecruitRank = "Rekrut";
    string DefaultMemberRank = "Gefreiter";
    string OwnerRank = "Kommandant";
    string OfficerRank = "Hauptmann";
    string DefaultMapKeyHint = "M";
    int UILeftPanelWidthPx = 315;
    int UIRightPanelWidthPx = 330;
    int UIMainButtonHeightPx = 36;
    int UICompactButtonHeightPx = 32;

    void Defaults()
    {
        ConfigVersion = 6;
        EnableGroups = 1;
        EnableMapLayer = 1;
        EnableGroupMarkers = 1;
        EnablePrivateMarkers = 1;
        EnableServerMarkers = 1;
        EnablePlayerMarkers = 1;
        EnableGroupChat = 1;
        EnableAuditLog = 1;
        EnableAlliances = 1;
        EnableGarageBridge = 1;
        EnableBankingBridge = 1;
        EnableGPSHud = 0;
        EnableCompassHud = 0;
        MaxGroupMembersDefault = 12;
        MaxGroupMarkersDefault = 25;
        MaxPrivateMarkersPerPlayer = 35;
        MaxChatHistory = 60;
        MaxAuditEntries = 120;
        AutoSaveIntervalSeconds = 120;
        PlayerSyncIntervalSeconds = 10;
        MarkerSyncIntervalSeconds = 10;
        InviteLifetimeSeconds = 300;
        RecruitRank = "Rekrut";
        DefaultMemberRank = "Gefreiter";
        OwnerRank = "Kommandant";
        OfficerRank = "Hauptmann";
        DefaultMapKeyHint = "M";
        UILeftPanelWidthPx = 315;
        UIRightPanelWidthPx = 330;
        UIMainButtonHeightPx = 36;
        UICompactButtonHeightPx = 32;
    }

    void Validate()
    {
        if (ConfigVersion < 6) ConfigVersion = 6;
        if (MaxGroupMembersDefault < 1) MaxGroupMembersDefault = 1;
        if (MaxGroupMarkersDefault < 0) MaxGroupMarkersDefault = 0;
        if (MaxPrivateMarkersPerPlayer < 0) MaxPrivateMarkersPerPlayer = 0;
        if (MaxChatHistory < 5) MaxChatHistory = 5;
        if (MaxAuditEntries < 10) MaxAuditEntries = 10;
        if (AutoSaveIntervalSeconds < 30) AutoSaveIntervalSeconds = 30;
        if (PlayerSyncIntervalSeconds < 3) PlayerSyncIntervalSeconds = 3;
        if (MarkerSyncIntervalSeconds < 3) MarkerSyncIntervalSeconds = 3;
        if (InviteLifetimeSeconds < 30) InviteLifetimeSeconds = 30;
        if (RecruitRank == "") RecruitRank = "Rekrut";
        if (DefaultMemberRank == "") DefaultMemberRank = "Gefreiter";
        if (OwnerRank == "") OwnerRank = "Kommandant";
        if (OfficerRank == "") OfficerRank = "Hauptmann";
        if (UILeftPanelWidthPx < 240) UILeftPanelWidthPx = 315;
        if (UIRightPanelWidthPx < 260) UIRightPanelWidthPx = 330;
        if (UIMainButtonHeightPx < 28) UIMainButtonHeightPx = 36;
        if (UICompactButtonHeightPx < 24) UICompactButtonHeightPx = 32;
    }
}

class DeutschZGroupLevelConfigEntry
{
    string Name = "Rekrut";
    int Priority = 10;
    int MaxMembersBonus = 0;
    int MaxMarkersBonus = 0;
    ref array<string> Permissions;

    void DeutschZGroupLevelConfigEntry()
    {
        Permissions = new array<string>;
    }

    void AddPermission(string permission)
    {
        if (!Permissions)
        {
            Permissions = new array<string>;
        }
        foreach (string entry: Permissions)
        {
            if (entry == permission)
            {
                return;
            }
        }
        Permissions.Insert(permission);
    }
}

class DeutschZGroupLevelsConfig
{
    int ConfigVersion = 2;
    ref array<ref DeutschZGroupLevelConfigEntry> Levels;

    void DeutschZGroupLevelsConfig()
    {
        Levels = new array<ref DeutschZGroupLevelConfigEntry>;
    }

    void Defaults()
    {
        if (!Levels)
        {
            Levels = new array<ref DeutschZGroupLevelConfigEntry>;
        }
        Levels.Clear();

        InsertRank("Rekrut", 10, 0, 0, false, false, false, false, false);
        InsertRank("Gefreiter", 20, 0, 2, true, false, false, false, false);
        InsertRank("Obergefreiter", 30, 1, 3, true, false, false, false, false);
        InsertRank("Unteroffizier", 40, 2, 5, true, true, false, false, false);
        InsertRank("Feldwebel", 55, 4, 8, true, true, true, false, false);
        InsertRank("Leutnant", 70, 6, 12, true, true, true, true, false);
        InsertRank("Hauptmann", 85, 8, 16, true, true, true, true, true);
        InsertRank("Kommandant", 100, 12, 25, true, true, true, true, true);
    }

    protected void InsertRank(string name, int priority, int memberBonus, int markerBonus, bool markerRights, bool inviteRights, bool garageWithdraw, bool bankWithdraw, bool manageRights)
    {
        ref DeutschZGroupLevelConfigEntry rank = new DeutschZGroupLevelConfigEntry();
        rank.Name = name;
        rank.Priority = priority;
        rank.MaxMembersBonus = memberBonus;
        rank.MaxMarkersBonus = markerBonus;

        rank.AddPermission(DeutschZGroupPermissionKeys.GROUP_VIEW_MEMBERS);
        rank.AddPermission(DeutschZGroupPermissionKeys.GROUP_LEAVE);
        rank.AddPermission(DeutschZGroupPermissionKeys.GROUP_CHAT);
        rank.AddPermission(DeutschZGroupPermissionKeys.GARAGE_VIEW);
        rank.AddPermission(DeutschZGroupPermissionKeys.GARAGE_DEPOSIT);
        rank.AddPermission(DeutschZGroupPermissionKeys.BANK_VIEW);
        rank.AddPermission(DeutschZGroupPermissionKeys.BANK_DEPOSIT);

        if (markerRights)
        {
            rank.AddPermission(DeutschZGroupPermissionKeys.GROUP_MARKER_CREATE);
            rank.AddPermission(DeutschZGroupPermissionKeys.GROUP_MARKER_DELETE);
            rank.AddPermission(DeutschZGroupPermissionKeys.GROUP_PING);
            rank.AddPermission(DeutschZGroupPermissionKeys.PRIVATE_MARKER_CREATE);
            rank.AddPermission(DeutschZGroupPermissionKeys.PRIVATE_MARKER_DELETE);
        }
        if (inviteRights)
        {
            rank.AddPermission(DeutschZGroupPermissionKeys.GROUP_INVITE);
        }
        if (garageWithdraw)
        {
            rank.AddPermission(DeutschZGroupPermissionKeys.GARAGE_WITHDRAW);
        }
        if (bankWithdraw)
        {
            rank.AddPermission(DeutschZGroupPermissionKeys.BANK_WITHDRAW);
            rank.AddPermission(DeutschZGroupPermissionKeys.BANK_TRANSFER);
        }
        if (manageRights)
        {
            rank.AddPermission(DeutschZGroupPermissionKeys.GROUP_KICK);
            rank.AddPermission(DeutschZGroupPermissionKeys.GROUP_SET_RANK);
            rank.AddPermission(DeutschZGroupPermissionKeys.GROUP_TRANSFER_OWNER);
            rank.AddPermission(DeutschZGroupPermissionKeys.GROUP_SETTINGS);
            rank.AddPermission(DeutschZGroupPermissionKeys.GROUP_AUDIT_VIEW);
            rank.AddPermission(DeutschZGroupPermissionKeys.GROUP_ALLIANCE_MANAGE);
            rank.AddPermission(DeutschZGroupPermissionKeys.STATIC_MARKER_CREATE);
            rank.AddPermission(DeutschZGroupPermissionKeys.STATIC_MARKER_DELETE);
            rank.AddPermission(DeutschZGroupPermissionKeys.GARAGE_MANAGE);
            rank.AddPermission(DeutschZGroupPermissionKeys.BANK_MANAGE);
        }
        if (name == "Kommandant")
        {
            rank.AddPermission(DeutschZGroupPermissionKeys.GROUP_CREATE);
            rank.AddPermission(DeutschZGroupPermissionKeys.GROUP_DISBAND);
            rank.AddPermission(DeutschZGroupPermissionKeys.ADMIN_GROUPS);
        }

        Levels.Insert(rank);
    }

    void Validate()
    {
        if (!Levels)
        {
            Levels = new array<ref DeutschZGroupLevelConfigEntry>;
        }
        if (Levels.Count() == 0)
        {
            Defaults();
        }
    }

    DeutschZGroupLevelConfigEntry FindLevel(string name)
    {
        foreach (DeutschZGroupLevelConfigEntry level: Levels)
        {
            if (level && level.Name == name)
            {
                return level;
            }
        }
        return NULL;
    }

    bool IsValidRank(string name)
    {
        return FindLevel(name) != NULL;
    }

    int GetPriority(string name)
    {
        DeutschZGroupLevelConfigEntry level = FindLevel(name);
        if (!level)
        {
            return 0;
        }
        return level.Priority;
    }

    bool HasPermission(string levelName, string permission)
    {
        DeutschZGroupLevelConfigEntry level = FindLevel(levelName);
        if (!level || !level.Permissions)
        {
            return false;
        }

        foreach (string entry: level.Permissions)
        {
            if (entry == permission)
            {
                return true;
            }
        }
        return false;
    }
}

class DeutschZGroupsMarkerConfig
{
    int ConfigVersion = 6;
    int ShowGroupMembersOnMap = 1;
    int ShowGroupMembersIn3D = 0;
    int ShowGroupMarkersOnMap = 1;
    int ShowGroupPingsOnMap = 1;
    int ShowPrivateMarkersOnMap = 1;
    int ShowStaticMarkersOnMap = 1;
    int ShowGarageMarkersOnMap = 1;
    int ShowBankMarkersOnMap = 1;
    int ShowEventMarkersOnMap = 1;
    int GroupPingLifetimeSeconds = 45;
    int ServerMarkerDefaultColorR = 255;
    int ServerMarkerDefaultColorG = 0;
    int ServerMarkerDefaultColorB = 0;
    string DefaultGroupIcon = DeutschZGroupsMarkerIcons.GROUP;
    string DefaultPlayerIcon = DeutschZGroupsMarkerIcons.GROUP;
    string DefaultPingIcon = DeutschZGroupsMarkerIcons.GROUP_PING;
    string DefaultGarageIcon = DeutschZGroupsMarkerIcons.GARAGE;
    string DefaultBankIcon = DeutschZGroupsMarkerIcons.BANK_ATM;
    string DefaultEventIcon = DeutschZGroupsMarkerIcons.EVENT;
    string DefaultSafezoneIcon = DeutschZGroupsMarkerIcons.ADMIN;
    string DefaultTraderIcon = DeutschZGroupsMarkerIcons.TRADER;
    string DefaultAdminIcon = DeutschZGroupsMarkerIcons.ADMIN;
    string DefaultAirdropIcon = DeutschZGroupsMarkerIcons.AIRDROP;
    string DefaultBaseIcon = DeutschZGroupsMarkerIcons.BASE;
    string DefaultBlackmarketIcon = DeutschZGroupsMarkerIcons.BLACKMARKET;
    string DefaultWeaponTraderIcon = DeutschZGroupsMarkerIcons.WEAPON_TRADER;
    string DefaultExtractIcon = DeutschZGroupsMarkerIcons.EXTRACT;
    string DefaultFireworkIcon = DeutschZGroupsMarkerIcons.FIREWORK;
    string DefaultFoodIcon = DeutschZGroupsMarkerIcons.FOOD;
    string DefaultBoatTraderIcon = DeutschZGroupsMarkerIcons.BOAT_TRADER;
    string DefaultBunkerIcon = DeutschZGroupsMarkerIcons.BUNKER;
    string DefaultConvoyIcon = DeutschZGroupsMarkerIcons.CONVOY;
    string DefaultHelicrashIcon = DeutschZGroupsMarkerIcons.HELICRASH;
    string DefaultKothIcon = DeutschZGroupsMarkerIcons.KOTH;
    string DefaultPatrolHeliIcon = DeutschZGroupsMarkerIcons.PATROLHELI;
    ref array<ref DeutschZGroupsMarkerIconEntry> MarkerIcons;

    void DeutschZGroupsMarkerConfig()
    {
        MarkerIcons = new array<ref DeutschZGroupsMarkerIconEntry>;
    }

    void Defaults()
    {
        ConfigVersion = 6;
        ShowGroupMembersOnMap = 1;
        ShowGroupMembersIn3D = 0;
        ShowGroupMarkersOnMap = 1;
        ShowGroupPingsOnMap = 1;
        ShowPrivateMarkersOnMap = 1;
        ShowStaticMarkersOnMap = 1;
        ShowGarageMarkersOnMap = 1;
        ShowBankMarkersOnMap = 1;
        ShowEventMarkersOnMap = 1;
        GroupPingLifetimeSeconds = 45;
        ServerMarkerDefaultColorR = 255;
        ServerMarkerDefaultColorG = 0;
        ServerMarkerDefaultColorB = 0;
        DefaultGroupIcon = DeutschZGroupsMarkerIcons.GROUP;
        DefaultPlayerIcon = DeutschZGroupsMarkerIcons.GROUP;
        DefaultPingIcon = DeutschZGroupsMarkerIcons.GROUP_PING;
        DefaultGarageIcon = DeutschZGroupsMarkerIcons.GARAGE;
        DefaultBankIcon = DeutschZGroupsMarkerIcons.BANK_ATM;
        DefaultEventIcon = DeutschZGroupsMarkerIcons.EVENT;
        DefaultSafezoneIcon = DeutschZGroupsMarkerIcons.ADMIN;
        DefaultTraderIcon = DeutschZGroupsMarkerIcons.TRADER;
        DefaultAdminIcon = DeutschZGroupsMarkerIcons.ADMIN;
        DefaultAirdropIcon = DeutschZGroupsMarkerIcons.AIRDROP;
        DefaultBaseIcon = DeutschZGroupsMarkerIcons.BASE;
        DefaultBlackmarketIcon = DeutschZGroupsMarkerIcons.BLACKMARKET;
        DefaultWeaponTraderIcon = DeutschZGroupsMarkerIcons.WEAPON_TRADER;
        DefaultExtractIcon = DeutschZGroupsMarkerIcons.EXTRACT;
        DefaultFireworkIcon = DeutschZGroupsMarkerIcons.FIREWORK;
        DefaultFoodIcon = DeutschZGroupsMarkerIcons.FOOD;
        DefaultBoatTraderIcon = DeutschZGroupsMarkerIcons.BOAT_TRADER;
        DefaultBunkerIcon = DeutschZGroupsMarkerIcons.BUNKER;
        DefaultConvoyIcon = DeutschZGroupsMarkerIcons.CONVOY;
        DefaultHelicrashIcon = DeutschZGroupsMarkerIcons.HELICRASH;
        DefaultKothIcon = DeutschZGroupsMarkerIcons.KOTH;
        DefaultPatrolHeliIcon = DeutschZGroupsMarkerIcons.PATROLHELI;
        EnsureDefaultIcons();
    }

    protected void AddIcon(string key, string displayName, string path, int sizePx, int markerType)
    {
        if (!MarkerIcons)
        {
            MarkerIcons = new array<ref DeutschZGroupsMarkerIconEntry>;
        }
        ref DeutschZGroupsMarkerIconEntry icon = new DeutschZGroupsMarkerIconEntry();
        icon.Setup(key, displayName, path, sizePx, markerType);
        MarkerIcons.Insert(icon);
    }

    void EnsureDefaultIcons()
    {
        if (!MarkerIcons)
        {
            MarkerIcons = new array<ref DeutschZGroupsMarkerIconEntry>;
        }
        MarkerIcons.Clear();
        AddIcon(DeutschZGroupsMarkerIcons.ADMIN, "Admin", DeutschZGroupsMarkerIcons.GetPath(DeutschZGroupsMarkerIcons.ADMIN), 128, DeutschZGroupMarkerType.SERVER_STATIC);
        AddIcon(DeutschZGroupsMarkerIcons.AIRDROP, "Airdrop", DeutschZGroupsMarkerIcons.GetPath(DeutschZGroupsMarkerIcons.AIRDROP), 128, DeutschZGroupMarkerType.EVENT_POINT);
        AddIcon(DeutschZGroupsMarkerIcons.BANK_ATM, "Bank ATM", DeutschZGroupsMarkerIcons.GetPath(DeutschZGroupsMarkerIcons.BANK_ATM), 128, DeutschZGroupMarkerType.ATM_POINT);
        AddIcon(DeutschZGroupsMarkerIcons.BASE, "Base", DeutschZGroupsMarkerIcons.GetPath(DeutschZGroupsMarkerIcons.BASE), 128, DeutschZGroupMarkerType.GROUP_MARKER);
        AddIcon(DeutschZGroupsMarkerIcons.BLACKMARKET, "Blackmarket", DeutschZGroupsMarkerIcons.GetPath(DeutschZGroupsMarkerIcons.BLACKMARKET), 128, DeutschZGroupMarkerType.TRADER_POINT);
        AddIcon(DeutschZGroupsMarkerIcons.GROUP_PING, "Group Ping", DeutschZGroupsMarkerIcons.GetPath(DeutschZGroupsMarkerIcons.GROUP_PING), 128, DeutschZGroupMarkerType.GROUP_PING);
        AddIcon(DeutschZGroupsMarkerIcons.TRADER, "Trader", DeutschZGroupsMarkerIcons.GetPath(DeutschZGroupsMarkerIcons.TRADER), 128, DeutschZGroupMarkerType.TRADER_POINT);
        AddIcon(DeutschZGroupsMarkerIcons.WEAPON_TRADER, "Weapon Trader", DeutschZGroupsMarkerIcons.GetPath(DeutschZGroupsMarkerIcons.WEAPON_TRADER), 128, DeutschZGroupMarkerType.TRADER_POINT);
        AddIcon(DeutschZGroupsMarkerIcons.EXTRACT, "Extract", DeutschZGroupsMarkerIcons.GetPath(DeutschZGroupsMarkerIcons.EXTRACT), 128, DeutschZGroupMarkerType.RALLY_POINT);
        AddIcon(DeutschZGroupsMarkerIcons.FIREWORK, "Firework", DeutschZGroupsMarkerIcons.GetPath(DeutschZGroupsMarkerIcons.FIREWORK), 128, DeutschZGroupMarkerType.EVENT_POINT);
        AddIcon(DeutschZGroupsMarkerIcons.FOOD, "Food", DeutschZGroupsMarkerIcons.GetPath(DeutschZGroupsMarkerIcons.FOOD), 128, DeutschZGroupMarkerType.TRADER_POINT);
        AddIcon(DeutschZGroupsMarkerIcons.GARAGE, "Garage", DeutschZGroupsMarkerIcons.GetPath(DeutschZGroupsMarkerIcons.GARAGE), 128, DeutschZGroupMarkerType.GARAGE_POINT);
        AddIcon(DeutschZGroupsMarkerIcons.BOAT_TRADER, "Boat Trader", DeutschZGroupsMarkerIcons.GetPath(DeutschZGroupsMarkerIcons.BOAT_TRADER), 128, DeutschZGroupMarkerType.TRADER_POINT);
        AddIcon(DeutschZGroupsMarkerIcons.BUNKER, "Bunker", DeutschZGroupsMarkerIcons.GetPath(DeutschZGroupsMarkerIcons.BUNKER), 128, DeutschZGroupMarkerType.SERVER_STATIC);
        AddIcon(DeutschZGroupsMarkerIcons.CONVOY, "Convoy", DeutschZGroupsMarkerIcons.GetPath(DeutschZGroupsMarkerIcons.CONVOY), 128, DeutschZGroupMarkerType.EVENT_POINT);
        AddIcon(DeutschZGroupsMarkerIcons.EVENT, "Event", DeutschZGroupsMarkerIcons.GetPath(DeutschZGroupsMarkerIcons.EVENT), 128, DeutschZGroupMarkerType.EVENT_POINT);
        AddIcon(DeutschZGroupsMarkerIcons.HELICRASH, "Helicrash", DeutschZGroupsMarkerIcons.GetPath(DeutschZGroupsMarkerIcons.HELICRASH), 128, DeutschZGroupMarkerType.EVENT_POINT);
        AddIcon(DeutschZGroupsMarkerIcons.KOTH, "KOTH", DeutschZGroupsMarkerIcons.GetPath(DeutschZGroupsMarkerIcons.KOTH), 128, DeutschZGroupMarkerType.KOTH_POINT);
        AddIcon(DeutschZGroupsMarkerIcons.PATROLHELI, "PatrolHeli", DeutschZGroupsMarkerIcons.GetPath(DeutschZGroupsMarkerIcons.PATROLHELI), 128, DeutschZGroupMarkerType.EVENT_POINT);
        AddIcon(DeutschZGroupsMarkerIcons.GROUP, "Group", DeutschZGroupsMarkerIcons.GetPath(DeutschZGroupsMarkerIcons.GROUP), 128, DeutschZGroupMarkerType.GROUP_MARKER);
    }

    string ResolveIconPath(string iconKey)
    {
        if (!MarkerIcons || MarkerIcons.Count() == 0)
        {
            EnsureDefaultIcons();
        }
        foreach (DeutschZGroupsMarkerIconEntry icon: MarkerIcons)
        {
            if (icon && icon.Key == iconKey)
            {
                return icon.Path;
            }
        }
        return DeutschZGroupsMarkerIcons.GetPath(iconKey);
    }

    void Validate()
    {
        if (ConfigVersion < 6) ConfigVersion = 6;
        if (GroupPingLifetimeSeconds < 5) GroupPingLifetimeSeconds = 5;
        if (DefaultGroupIcon == "") DefaultGroupIcon = DeutschZGroupsMarkerIcons.GROUP;
        if (DefaultPlayerIcon == "") DefaultPlayerIcon = DeutschZGroupsMarkerIcons.GROUP;
        if (DefaultPingIcon == "") DefaultPingIcon = DeutschZGroupsMarkerIcons.GROUP_PING;
        if (DefaultGarageIcon == "") DefaultGarageIcon = DeutschZGroupsMarkerIcons.GARAGE;
        if (DefaultBankIcon == "") DefaultBankIcon = DeutschZGroupsMarkerIcons.BANK_ATM;
        if (DefaultEventIcon == "") DefaultEventIcon = DeutschZGroupsMarkerIcons.EVENT;
        if (DefaultSafezoneIcon == "") DefaultSafezoneIcon = DeutschZGroupsMarkerIcons.ADMIN;
        if (DefaultTraderIcon == "") DefaultTraderIcon = DeutschZGroupsMarkerIcons.TRADER;
        if (DefaultAdminIcon == "") DefaultAdminIcon = DeutschZGroupsMarkerIcons.ADMIN;
        if (DefaultAirdropIcon == "") DefaultAirdropIcon = DeutschZGroupsMarkerIcons.AIRDROP;
        if (DefaultBaseIcon == "") DefaultBaseIcon = DeutschZGroupsMarkerIcons.BASE;
        if (DefaultBlackmarketIcon == "") DefaultBlackmarketIcon = DeutschZGroupsMarkerIcons.BLACKMARKET;
        if (DefaultWeaponTraderIcon == "") DefaultWeaponTraderIcon = DeutschZGroupsMarkerIcons.WEAPON_TRADER;
        if (DefaultExtractIcon == "") DefaultExtractIcon = DeutschZGroupsMarkerIcons.EXTRACT;
        if (DefaultFireworkIcon == "") DefaultFireworkIcon = DeutschZGroupsMarkerIcons.FIREWORK;
        if (DefaultFoodIcon == "") DefaultFoodIcon = DeutschZGroupsMarkerIcons.FOOD;
        if (DefaultBoatTraderIcon == "") DefaultBoatTraderIcon = DeutschZGroupsMarkerIcons.BOAT_TRADER;
        if (DefaultBunkerIcon == "") DefaultBunkerIcon = DeutschZGroupsMarkerIcons.BUNKER;
        if (DefaultConvoyIcon == "") DefaultConvoyIcon = DeutschZGroupsMarkerIcons.CONVOY;
        if (DefaultHelicrashIcon == "") DefaultHelicrashIcon = DeutschZGroupsMarkerIcons.HELICRASH;
        if (DefaultKothIcon == "") DefaultKothIcon = DeutschZGroupsMarkerIcons.KOTH;
        if (DefaultPatrolHeliIcon == "") DefaultPatrolHeliIcon = DeutschZGroupsMarkerIcons.PATROLHELI;
        EnsureDefaultIcons();
    }
}
