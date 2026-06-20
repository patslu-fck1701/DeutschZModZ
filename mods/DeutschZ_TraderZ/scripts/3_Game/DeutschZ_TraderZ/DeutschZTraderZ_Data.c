class DeutschZTraderZ_Result
{
    bool Success;
    string Message;

    void DeutschZTraderZ_Result(bool success = false, string message = "")
    {
        Success = success;
        Message = message;
    }
}

class DeutschZTraderZ_CurrencyEntry
{
    string ClassName;
    int Value;

    void DeutschZTraderZ_CurrencyEntry(string className = "", int value = 0)
    {
        ClassName = className;
        Value = value;
    }
}

class DeutschZTraderZ_Settings
{
    int ConfigVersion;
    bool Enabled;
    bool SpawnTradersOnServerStart;
    bool EnablePhysicalCurrency;
    bool EnableBankingBridge;
    bool PreferBankingBalance;
    bool UseBankingBalanceIfInventoryMoneyMissing;
    bool GiveChangeForPhysicalCurrency;
    bool ForceMarkZDefaults;
    bool CreateMissingMarketFiles;
    bool CreateBundledMarketFiles;
    bool LoadRawMarketArrays;
    bool EnableSafezones;
    bool EnableStaticObjects;
    bool EnableVehicleSpawnPoints;
    bool EnableP2PMarket;
    bool EnableDeliveryOrders;
    bool DebugLogging;
    int MaxBuyAmount;
    int MaxSellAmount;
    float TraderActionDistance;
    string CurrencyName;
    string DefaultMarketSourceInfo;

    void DeutschZTraderZ_Settings()
    {
        ConfigVersion = DeutschZTraderZ_Constants.SETTINGS_VERSION;
        Enabled = true;
        SpawnTradersOnServerStart = true;
        EnablePhysicalCurrency = true;
        EnableBankingBridge = true;
        PreferBankingBalance = false;
        UseBankingBalanceIfInventoryMoneyMissing = true;
        GiveChangeForPhysicalCurrency = true;
        ForceMarkZDefaults = true;
        CreateMissingMarketFiles = true;
        CreateBundledMarketFiles = true;
        LoadRawMarketArrays = true;
        EnableSafezones = true;
        EnableStaticObjects = true;
        EnableVehicleSpawnPoints = true;
        EnableP2PMarket = false;
        EnableDeliveryOrders = false;
        DebugLogging = false;
        MaxBuyAmount = 50;
        MaxSellAmount = 50;
        TraderActionDistance = 5.0;
        CurrencyName = "MarkZ";
        DefaultMarketSourceInfo = "Bundled defaults are read from DeutschZ_TraderZ/data/default_market and written as profiles/DeutschZ/TraderZ/Market/{Category}.json when missing.";
    }
}

class DeutschZTraderZ_Appearance
{
    string Headgear;
    ref TStringArray HeadgearAttachments;
    string Mask;
    string Glasses;
    string Body;
    string Vest;
    ref TStringArray VestAttachments;
    string Backpack;
    string Gloves;
    string Pants;
    string Shoes;
    string Belt;
    ref TStringArray BeltAttachments;

    void DeutschZTraderZ_Appearance()
    {
        Headgear = "";
        Mask = "";
        Glasses = "";
        Body = "";
        Vest = "";
        Backpack = "";
        Gloves = "";
        Pants = "";
        Shoes = "";
        Belt = "";
        HeadgearAttachments = new TStringArray;
        VestAttachments = new TStringArray;
        BeltAttachments = new TStringArray;
    }
}

class DeutschZTraderZ_Trader
{
    string TraderID;
    string DisplayName;
    string ObjectClass;
    vector Position;
    vector Orientation;
    ref TStringArray Categories;
    ref DeutschZTraderZ_Appearance Appearance;
    string HandsItem;
    ref TStringArray HandsItemAttachments;
    bool Enabled;
    bool IsP2PTrader;
    bool IsDeliveryTrader;

    void DeutschZTraderZ_Trader()
    {
        TraderID = "";
        DisplayName = "DeutschZ Trader";
        ObjectClass = "DeutschZTraderZ_NPC_Mirek";
        Position = "0 0 0";
        Orientation = "0 0 0";
        Categories = new TStringArray;
        Appearance = new DeutschZTraderZ_Appearance;
        HandsItem = "";
        HandsItemAttachments = new TStringArray;
        Enabled = true;
        IsP2PTrader = false;
        IsDeliveryTrader = false;
    }
}

class DeutschZTraderZ_MarketItem
{
    string ClassName;
    string DisplayName;
    string Category;
    string DeliveryGroup;
    int BuyPrice;
    int SellPrice;
    bool CanBuy;
    bool CanSell;
    bool DeliveryItem;
    int DeliverySize;
    ref TStringArray SpawnAttachments;
    ref TStringArray OptionalAttachments;
    ref TStringArray Variants;
    bool IsVariant;

    void DeutschZTraderZ_MarketItem()
    {
        ClassName = "";
        DisplayName = "";
        Category = "";
        DeliveryGroup = "";
        BuyPrice = 0;
        SellPrice = 0;
        CanBuy = true;
        CanSell = true;
        DeliveryItem = false;
        DeliverySize = 1;
        SpawnAttachments = new TStringArray;
        OptionalAttachments = new TStringArray;
        Variants = new TStringArray;
        IsVariant = false;
    }
}

class DeutschZTraderZ_MarketFile
{
    string Category;
    ref array<ref DeutschZTraderZ_MarketItem> Items;

    void DeutschZTraderZ_MarketFile()
    {
        Category = "";
        Items = new array<ref DeutschZTraderZ_MarketItem>;
    }
}

class DeutschZTraderZ_Safezone
{
    string Name;
    vector Position;
    float Radius;
    bool Enabled;
    bool DisableDamage;
    bool BlockPlacement;
    bool BlockMelee;
    bool BlockFirearms;
    bool DeleteZombies;
    bool DeleteAnimals;
    bool DeleteDroppedItems;
    bool DeleteUnownedVehicles;
    int CleanupIntervalSeconds;
    bool AllowLoginInZone;
    string EnterMessage;
    string ExitMessage;
    string TeleportMessage;
    ref array<vector> TeleportPositions;
    ref TStringArray IgnoreClassNames;
    ref TStringArray BlockedPlacementClassNames;

    void DeutschZTraderZ_Safezone()
    {
        Name = "Trader Safezone";
        Position = "0 0 0";
        Radius = 50.0;
        Enabled = true;
        DisableDamage = true;
        BlockPlacement = true;
        BlockMelee = true;
        BlockFirearms = true;
        DeleteZombies = true;
        DeleteAnimals = false;
        DeleteDroppedItems = false;
        DeleteUnownedVehicles = false;
        CleanupIntervalSeconds = 300;
        AllowLoginInZone = false;
        EnterMessage = "Welcome to TraderZ.";
        ExitMessage = "You left TraderZ.";
        TeleportMessage = "You were moved out of a restricted trader zone.";
        TeleportPositions = new array<vector>;
        IgnoreClassNames = new TStringArray;
        BlockedPlacementClassNames = new TStringArray;
    }
}

class DeutschZTraderZ_VehicleSpawnPoint
{
    string GroupName;
    vector Position;
    vector Orientation;
    float SearchRadius;

    void DeutschZTraderZ_VehicleSpawnPoint(string groupName = "Cars", vector position = "0 0 0", vector orientation = "0 0 0", float radius = 8.0)
    {
        GroupName = groupName;
        Position = position;
        Orientation = orientation;
        SearchRadius = radius;
    }
}

class DeutschZTraderZ_StaticObject
{
    string ClassName;
    vector Position;
    vector Orientation;
    vector Scale;
    bool Enabled;

    void DeutschZTraderZ_StaticObject()
    {
        ClassName = "";
        Position = "0 0 0";
        Orientation = "0 0 0";
        Scale = "1 1 1";
        Enabled = true;
    }
}

class DeutschZTraderZ_DeliverySettings
{
    bool Enabled;
    int MaxDeliveryPoints;
    int BaseDeliveryFee;
    int CrateLifetimeSeconds;
    int OrderCooldownSeconds;

    void DeutschZTraderZ_DeliverySettings()
    {
        Enabled = false;
        MaxDeliveryPoints = 20;
        BaseDeliveryFee = 2000;
        CrateLifetimeSeconds = 1800;
        OrderCooldownSeconds = 86400;
    }
}

class DeutschZTraderZ_P2PSettings
{
    bool Enabled;
    int ListingLifetimeSeconds;
    int MaxListingsPerPlayer;
    bool ReturnExpiredItems;
    int MarketFee;

    void DeutschZTraderZ_P2PSettings()
    {
        Enabled = false;
        ListingLifetimeSeconds = 604800;
        MaxListingsPerPlayer = 5;
        ReturnExpiredItems = true;
        MarketFee = 100;
    }
}
