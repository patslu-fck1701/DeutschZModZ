class DeutschZGroupsMarkerIcons
{
    static const string ADMIN = "dzm_admin";
    static const string AIRDROP = "dzm_airdrop";
    static const string BANK_ATM = "dzm_bank_atm";
    static const string BASE = "dzm_base";
    static const string BLACKMARKET = "dzm_blackmarket";
    static const string GROUP_PING = "dzm_group_ping";
    static const string TRADER = "dzm_trader";
    static const string WEAPON_TRADER = "dzm_weapon_trader";
    static const string EXTRACT = "dzm_extract";
    static const string FIREWORK = "dzm_firework";
    static const string FOOD = "dzm_food";
    static const string GARAGE = "dzm_garage";
    static const string BOAT_TRADER = "dzm_boat_trader";
    static const string BUNKER = "dzm_bunker";
    static const string CONVOY = "dzm_convoy";
    static const string EVENT = "dzm_event";
    static const string HELICRASH = "dzm_helicrash";
    static const string KOTH = "dzm_koth";
    static const string PATROLHELI = "dzm_patrolheli";
    static const string GROUP = "dzm_group";
    static const string PLAYER = "dzm_group";

    static string GetPath(string iconKey)
    {
        if (iconKey == ADMIN) return "DeutschZ_Groups\\data\\markers\\dzm_admin_ca.tga.paa";
        if (iconKey == AIRDROP) return "DeutschZ_Groups\\data\\markers\\dzm_airdrop_ca.tga.paa";
        if (iconKey == BANK_ATM) return "DeutschZ_Groups\\data\\markers\\dzm_bank_atm_ca.tga.paa";
        if (iconKey == BASE) return "DeutschZ_Groups\\data\\markers\\dzm_base_ca.tga.paa";
        if (iconKey == BLACKMARKET) return "DeutschZ_Groups\\data\\markers\\dzm_blackmarket_ca.tga.paa";
        if (iconKey == GROUP_PING) return "DeutschZ_Groups\\data\\markers\\dzm_group_ping_ca.tga.paa";
        if (iconKey == TRADER) return "DeutschZ_Groups\\data\\markers\\dzm_trader_ca.tga.paa";
        if (iconKey == WEAPON_TRADER) return "DeutschZ_Groups\\data\\markers\\dzm_weapon_trader_ca.tga.paa";
        if (iconKey == EXTRACT) return "DeutschZ_Groups\\data\\markers\\dzm_extract_ca.tga.paa";
        if (iconKey == FIREWORK) return "DeutschZ_Groups\\data\\markers\\dzm_firework_ca.tga.paa";
        if (iconKey == FOOD) return "DeutschZ_Groups\\data\\markers\\dzm_food_ca.tga.paa";
        if (iconKey == GARAGE) return "DeutschZ_Groups\\data\\markers\\dzm_garage_ca.tga.paa";
        if (iconKey == BOAT_TRADER) return "DeutschZ_Groups\\data\\markers\\dzm_boat_trader_ca.tga.paa";
        if (iconKey == BUNKER) return "DeutschZ_Groups\\data\\markers\\dzm_bunker_ca.tga.paa";
        if (iconKey == CONVOY) return "DeutschZ_Groups\\data\\markers\\dzm_convoy_ca.tga.paa";
        if (iconKey == EVENT) return "DeutschZ_Groups\\data\\markers\\dzm_event_ca.tga.paa";
        if (iconKey == HELICRASH) return "DeutschZ_Groups\\data\\markers\\dzm_helicrash_ca.tga.paa";
        if (iconKey == KOTH) return "DeutschZ_Groups\\data\\markers\\dzm_koth_ca.tga.paa";
        if (iconKey == PATROLHELI) return "DeutschZ_Groups\\data\\markers\\dzm_patrolheli_ca.tga.paa";
        if (iconKey == GROUP) return "DeutschZ_Groups\\data\\markers\\dzm_group_ca.tga.paa";
        if (iconKey.Contains(".paa")) return iconKey;
        return "DeutschZ_Groups\\data\\markers\\dzm_group_ca.tga.paa";
    }

    static string GetDefaultForMarkerType(int markerType)
    {
        if (markerType == DeutschZGroupMarkerType.GROUP_PING) return GROUP_PING;
        if (markerType == DeutschZGroupMarkerType.GROUP_MARKER) return GROUP;
        if (markerType == DeutschZGroupMarkerType.PRIVATE_MARKER) return BASE;
        if (markerType == DeutschZGroupMarkerType.SERVER_STATIC) return ADMIN;
        if (markerType == DeutschZGroupMarkerType.GARAGE_POINT) return GARAGE;
        if (markerType == DeutschZGroupMarkerType.BANK_POINT) return BANK_ATM;
        if (markerType == DeutschZGroupMarkerType.EVENT_POINT) return EVENT;
        if (markerType == DeutschZGroupMarkerType.TRADER_POINT) return TRADER;
        if (markerType == DeutschZGroupMarkerType.ATM_POINT) return BANK_ATM;
        if (markerType == DeutschZGroupMarkerType.KOTH_POINT) return KOTH;
        if (markerType == DeutschZGroupMarkerType.RALLY_POINT) return EXTRACT;
        return GROUP;
    }
}

class DeutschZGroupsMarkerIconEntry
{
    string Key = "";
    string DisplayName = "";
    string Path = "";
    int SizePx = 128;
    int DefaultMarkerType = 0;

    void Setup(string key, string displayName, string path, int sizePx, int defaultMarkerType)
    {
        Key = key;
        DisplayName = displayName;
        Path = path;
        SizePx = sizePx;
        DefaultMarkerType = defaultMarkerType;
    }
}
