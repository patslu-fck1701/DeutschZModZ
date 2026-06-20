class DeutschZTraderZ_Constants
{
    static const string MOD_NAME = "DeutschZ_TraderZ";
    static const string LOG_PREFIX = "[DeutschZ_TraderZ] ";

    static const string ROOT_FOLDER = "$profile:DeutschZ/";
    static const string TRADERZ_FOLDER = "$profile:DeutschZ/TraderZ/";
    static const string CONFIG_FOLDER = "$profile:DeutschZ/TraderZ/Config/";
    static const string MARKET_FOLDER = "$profile:DeutschZ/TraderZ/Market/";
    static const string DATA_FOLDER = "$profile:DeutschZ/TraderZ/Data/";
    static const string LOG_FOLDER = "$profile:DeutschZ/TraderZ/Data/Logs/";
    static const string DEFAULT_MARKET_FOLDER = "DeutschZ_TraderZ/data/default_market/";

    static const string SETTINGS_FILE = "$profile:DeutschZ/TraderZ/Config/TraderZ_Settings.json";
    static const string TRADERS_FILE = "$profile:DeutschZ/TraderZ/Config/TraderZ_Traders.json";
    static const string CURRENCY_FILE = "$profile:DeutschZ/TraderZ/Config/TraderZ_Currency.json";
    static const string SAFEZONES_FILE = "$profile:DeutschZ/TraderZ/Config/TraderZ_Safezones.json";
    static const string VEHICLE_SPAWNS_FILE = "$profile:DeutschZ/TraderZ/Config/TraderZ_VehicleSpawns.json";
    static const string STATIC_OBJECTS_FILE = "$profile:DeutschZ/TraderZ/Config/TraderZ_StaticObjects.json";
    static const string DELIVERY_FILE = "$profile:DeutschZ/TraderZ/Config/TraderZ_Delivery.json";
    static const string P2P_FILE = "$profile:DeutschZ/TraderZ/Config/TraderZ_P2P.json";

    static const int SETTINGS_VERSION = 6;

    static const string RPC_MOD = "DeutschZ_TraderZ";
    static const string RPC_OPEN_MENU = "RPC_OpenMenu";
    static const string RPC_SYNC_ITEMS = "RPC_SyncItems";
    static const string RPC_NOTIFY = "RPC_Notify";
    static const string RPC_BUY = "RPC_Buy";
    static const string RPC_SELL = "RPC_Sell";
    static const string RPC_REQUEST_CATEGORY = "RPC_RequestCategory";
    static const string RPC_ADMIN_STATUS = "RPC_AdminStatus";
    static const string RPC_ADMIN_RELOAD = "RPC_AdminReload";
}

enum DeutschZTraderZ_RPCs
{
    DEUTSCHZ_TRADERZ_RPC_START = 71386000,
    DEUTSCHZ_TRADERZ_OPEN_MENU,
    DEUTSCHZ_TRADERZ_SYNC_ITEMS,
    DEUTSCHZ_TRADERZ_BUY,
    DEUTSCHZ_TRADERZ_SELL,
    DEUTSCHZ_TRADERZ_REQUEST_CATEGORY,
    DEUTSCHZ_TRADERZ_NOTIFY,
    DEUTSCHZ_TRADERZ_ADMIN_STATUS,
    DEUTSCHZ_TRADERZ_ADMIN_RELOAD,
    DEUTSCHZ_TRADERZ_ADMIN_ROWS,
    DEUTSCHZ_TRADERZ_RPC_END
}
