class DeutschZTraderZ_ConfigManager
{
    protected static ref DeutschZTraderZ_Settings m_Settings;
    protected static ref array<ref DeutschZTraderZ_CurrencyEntry> m_Currencies;
    protected static ref array<ref DeutschZTraderZ_Trader> m_Traders;
    protected static ref array<ref DeutschZTraderZ_Safezone> m_Safezones;
    protected static ref array<ref DeutschZTraderZ_VehicleSpawnPoint> m_VehicleSpawns;
    protected static ref array<ref DeutschZTraderZ_StaticObject> m_StaticObjects;
    protected static ref DeutschZTraderZ_DeliverySettings m_DeliverySettings;
    protected static ref DeutschZTraderZ_P2PSettings m_P2PSettings;
    protected static ref map<string, ref DeutschZTraderZ_MarketFile> m_MarketFiles;
    protected static ref map<string, ref DeutschZTraderZ_MarketItem> m_GlobalItemIndex;

    static void LoadAll()
    {
        DeutschZTraderZ_FileUtil.EnsureFolders();
        LoadSettings();
        LoadCurrency();
        LoadTraders();
        LoadSafezones();
        LoadVehicleSpawns();
        LoadStaticObjects();
        LoadDelivery();
        LoadP2P();
        EnsureDefaultMarketFiles();
        LoadMarketFiles();
    }

    static DeutschZTraderZ_Settings GetSettings()
    {
        if (!m_Settings) LoadSettings();
        return m_Settings;
    }

    static array<ref DeutschZTraderZ_CurrencyEntry> GetCurrencies()
    {
        if (!m_Currencies) LoadCurrency();
        return m_Currencies;
    }

    static array<ref DeutschZTraderZ_Trader> GetTraders()
    {
        if (!m_Traders) LoadTraders();
        return m_Traders;
    }

    static array<ref DeutschZTraderZ_Safezone> GetSafezones()
    {
        if (!m_Safezones) LoadSafezones();
        return m_Safezones;
    }

    static array<ref DeutschZTraderZ_VehicleSpawnPoint> GetVehicleSpawns()
    {
        if (!m_VehicleSpawns) LoadVehicleSpawns();
        return m_VehicleSpawns;
    }

    static void LoadSettings()
    {
        DeutschZTraderZ_FileUtil.EnsureFolders();
        m_Settings = new DeutschZTraderZ_Settings();
        if (FileExist(DeutschZTraderZ_Constants.SETTINGS_FILE))
            JsonFileLoader<DeutschZTraderZ_Settings>.JsonLoadFile(DeutschZTraderZ_Constants.SETTINGS_FILE, m_Settings);
        if (!m_Settings) m_Settings = new DeutschZTraderZ_Settings();
        SaveSettings();
    }

    static void SaveSettings()
    {
        DeutschZTraderZ_FileUtil.EnsureFolders();
        JsonFileLoader<DeutschZTraderZ_Settings>.JsonSaveFile(DeutschZTraderZ_Constants.SETTINGS_FILE, m_Settings);
    }

    static void LoadCurrency()
    {
        DeutschZTraderZ_FileUtil.EnsureFolders();
        m_Currencies = new array<ref DeutschZTraderZ_CurrencyEntry>;
        if (FileExist(DeutschZTraderZ_Constants.CURRENCY_FILE))
            JsonFileLoader<array<ref DeutschZTraderZ_CurrencyEntry>>.JsonLoadFile(DeutschZTraderZ_Constants.CURRENCY_FILE, m_Currencies);
        if (!m_Currencies)
            m_Currencies = new array<ref DeutschZTraderZ_CurrencyEntry>;
        EnsureMarkZCurrencyDefaults();
        JsonFileLoader<array<ref DeutschZTraderZ_CurrencyEntry>>.JsonSaveFile(DeutschZTraderZ_Constants.CURRENCY_FILE, m_Currencies);
    }

    static void EnsureMarkZCurrencyDefaults()
    {
        EnsureCurrencyEntry("DZ_MarkZ_1", 1);
        EnsureCurrencyEntry("DZ_MarkZ_2", 2);
        EnsureCurrencyEntry("DZ_MarkZ_5", 5);
        EnsureCurrencyEntry("DZ_MarkZ_10", 10);
        EnsureCurrencyEntry("DZ_MarkZ_20", 20);
        EnsureCurrencyEntry("DZ_MarkZ_50", 50);
        EnsureCurrencyEntry("DZ_MarkZ_100", 100);
    }

    static void EnsureCurrencyEntry(string className, int value)
    {
        if (!m_Currencies)
            m_Currencies = new array<ref DeutschZTraderZ_CurrencyEntry>;
        foreach (DeutschZTraderZ_CurrencyEntry entry : m_Currencies)
        {
            if (entry && entry.ClassName == className)
            {
                entry.Value = value;
                return;
            }
        }
        m_Currencies.Insert(new DeutschZTraderZ_CurrencyEntry(className, value));
    }

    static void LoadTraders()
    {
        DeutschZTraderZ_FileUtil.EnsureFolders();
        m_Traders = new array<ref DeutschZTraderZ_Trader>;
        if (FileExist(DeutschZTraderZ_Constants.TRADERS_FILE))
            JsonFileLoader<array<ref DeutschZTraderZ_Trader>>.JsonLoadFile(DeutschZTraderZ_Constants.TRADERS_FILE, m_Traders);
        if (!m_Traders || m_Traders.Count() == 0)
        {
            m_Traders = new array<ref DeutschZTraderZ_Trader>;
            CreateDefaultTraders(m_Traders);
            JsonFileLoader<array<ref DeutschZTraderZ_Trader>>.JsonSaveFile(DeutschZTraderZ_Constants.TRADERS_FILE, m_Traders);
        }
    }

    static void CreateDefaultTraders(array<ref DeutschZTraderZ_Trader> traders)
    {
        DeutschZTraderZ_Trader t;

        t = new DeutschZTraderZ_Trader();
        t.TraderID = "GeneralTrader_001";
        t.DisplayName = "DeutschZ General Trader";
        t.ObjectClass = "DeutschZTraderZ_NPC_Mirek";
        t.Position = "3706.8 402 5982.5";
        t.Orientation = "-104.0 0 0";
        AddTraderCategory(t, "Food_Drinks");
        AddTraderCategory(t, "Utilities");
        AddTraderCategory(t, "Build_Utilities");
        AddTraderCategory(t, "Building_Supplies");
        AddTraderCategory(t, "Storage");
        AddTraderCategory(t, "Tools");
        AddTraderCategory(t, "Electronics");
        AddTraderCategory(t, "Batteries");
        AddTraderCategory(t, "Navigation");
        AddTraderCategory(t, "Fishing");
        AddTraderCategory(t, "Fish");
        AddTraderCategory(t, "Meat");
        AddTraderCategory(t, "Fruits_Vegtables");
        AddTraderCategory(t, "Hunting_Gear");
        AddTraderCategory(t, "Lights");
        AddTraderCategory(t, "Melee");
        AddTraderCategory(t, "Pelts");
        AddTraderCategory(t, "Supplies");
        AddTraderCategory(t, "Traps");
        AddTraderCategory(t, "Flags");
        AddTraderCategory(t, "Food");
        AddTraderCategory(t, "Drinks");
        t.Appearance.Body = "LabCoat";
        t.Appearance.Pants = "SlacksPants_Black";
        t.Appearance.Shoes = "DressShoes_Black";
        traders.Insert(t);

        t = new DeutschZTraderZ_Trader();
        t.TraderID = "MedicalTrader_001";
        t.DisplayName = "DeutschZ Medical Trader";
        t.ObjectClass = "DeutschZTraderZ_NPC_Keiko";
        t.Position = "3712.7 402 5963.4";
        t.Orientation = "-15.0 0 0";
        AddTraderCategory(t, "Medical");
        t.Appearance.Headgear = "MedicalScrubsHat_Blue";
        t.Appearance.Mask = "SurgicalMask";
        t.Appearance.Body = "MedicalScrubsShirt_Blue";
        t.Appearance.Pants = "MedicalScrubsPants_Blue";
        t.Appearance.Shoes = "AthleticShoes_Black";
        t.Appearance.Gloves = "SurgicalGloves_Blue";
        t.HandsItem = "ClearSyringe";
        traders.Insert(t);

        t = new DeutschZTraderZ_Trader();
        t.TraderID = "VehicleTrader_001";
        t.DisplayName = "DeutschZ Vehicle Trader";
        t.ObjectClass = "DeutschZTraderZ_NPC_Boris";
        t.Position = "3688.3 402 5990.9";
        t.Orientation = "72.0 0 0";
        AddTraderCategory(t, "Cars");
        AddTraderCategory(t, "Boats");
        AddTraderCategory(t, "Wheels");
        AddTraderCategory(t, "Parts");
        AddTraderCategory(t, "Batteries");
        AddTraderCategory(t, "Vehicles");
        AddTraderCategory(t, "VehicleParts");
        t.Appearance.Headgear = "ConstructionHelmet_Yellow";
        t.Appearance.Body = "Shirt_RedCheck";
        t.Appearance.Pants = "Jeans_Blue";
        t.Appearance.Shoes = "WorkingBoots_Brown";
        t.Appearance.Vest = "ReflexVest";
        t.HandsItem = "Wrench";
        traders.Insert(t);

        t = new DeutschZTraderZ_Trader();
        t.TraderID = "BlackmarketTrader_001";
        t.DisplayName = "DeutschZ Blackmarket";
        t.ObjectClass = "DeutschZTraderZ_NPC_Denis";
        t.Position = "3693.8 402 5976.7";
        t.Orientation = "72.0 0 0";
        AddTraderCategory(t, "Assault_Rifles");
        AddTraderCategory(t, "Sniper_Rifles");
        AddTraderCategory(t, "LMGs");
        AddTraderCategory(t, "Sub_Machine_Guns");
        AddTraderCategory(t, "Shotguns");
        AddTraderCategory(t, "Handguns");
        AddTraderCategory(t, "Rifles");
        AddTraderCategory(t, "Ammo");
        AddTraderCategory(t, "Ammo_Boxes");
        AddTraderCategory(t, "Magazines");
        AddTraderCategory(t, "Optics");
        AddTraderCategory(t, "Muzzles");
        AddTraderCategory(t, "Buttstocks");
        AddTraderCategory(t, "Handguards");
        AddTraderCategory(t, "Bayonets");
        AddTraderCategory(t, "Explosives");
        AddTraderCategory(t, "Launchers");
        AddTraderCategory(t, "Crossbows");
        AddTraderCategory(t, "Weapons");
        t.Appearance.Headgear = "BallisticHelmet_Black";
        t.Appearance.Body = "M65Jacket_Black";
        t.Appearance.Pants = "CargoPants_Black";
        t.Appearance.Shoes = "MilitaryBoots_Black";
        t.Appearance.Vest = "PlateCarrierVest_Black";
        traders.Insert(t);

        t = new DeutschZTraderZ_Trader();
        t.TraderID = "ClothingTrader_001";
        t.DisplayName = "DeutschZ Clothing Trader";
        t.ObjectClass = "DeutschZTraderZ_NPC_Linda";
        t.Position = "3703.6 402 5968.4";
        t.Orientation = "-55.0 0 0";
        AddTraderCategory(t, "Backpacks");
        AddTraderCategory(t, "Vest_Armor");
        AddTraderCategory(t, "Vests");
        AddTraderCategory(t, "Jackets");
        AddTraderCategory(t, "Pants");
        AddTraderCategory(t, "Shirts");
        AddTraderCategory(t, "Shoes");
        AddTraderCategory(t, "Gloves");
        AddTraderCategory(t, "Hats");
        AddTraderCategory(t, "Helmets");
        AddTraderCategory(t, "Masks");
        AddTraderCategory(t, "Eyewear");
        AddTraderCategory(t, "Belts");
        AddTraderCategory(t, "Holsters_Pouches");
        AddTraderCategory(t, "Armbands");
        AddTraderCategory(t, "DPM_UK");
        AddTraderCategory(t, "FLT_Germany");
        AddTraderCategory(t, "M05_Finnland");
        AddTraderCategory(t, "M84_DK");
        AddTraderCategory(t, "M98_Norway");
        AddTraderCategory(t, "Ghillies");
        AddTraderCategory(t, "Ghillie_Gun_Wraps");
        t.Appearance.Headgear = "BeanieHat_Grey";
        t.Appearance.Body = "WomanSuit";
        t.Appearance.Pants = "Jeans_Grey";
        t.Appearance.Shoes = "Sneakers_Gray";
        traders.Insert(t);
    }

    static void AddTraderCategory(DeutschZTraderZ_Trader trader, string category)
    {
        if (!trader || category == "")
            return;
        if (!trader.Categories)
            trader.Categories = new TStringArray;
        if (trader.Categories.Find(category) == -1)
            trader.Categories.Insert(category);
    }

    static void LoadSafezones()
    {
        DeutschZTraderZ_FileUtil.EnsureFolders();
        m_Safezones = new array<ref DeutschZTraderZ_Safezone>;
        if (FileExist(DeutschZTraderZ_Constants.SAFEZONES_FILE))
            JsonFileLoader<array<ref DeutschZTraderZ_Safezone>>.JsonLoadFile(DeutschZTraderZ_Constants.SAFEZONES_FILE, m_Safezones);
        if (!m_Safezones || m_Safezones.Count() == 0)
        {
            m_Safezones = new array<ref DeutschZTraderZ_Safezone>;
            DeutschZTraderZ_Safezone zone = new DeutschZTraderZ_Safezone();
            zone.Name = "Main Trader";
            zone.Position = "3700 402 5980";
            zone.Radius = 70;
            zone.TeleportPositions.Insert("3639.0 377.1 6154.8");
            zone.BlockedPlacementClassNames.Insert("FenceKit");
            zone.BlockedPlacementClassNames.Insert("WatchtowerKit");
            zone.BlockedPlacementClassNames.Insert("TerritoryFlagKit");
            zone.BlockedPlacementClassNames.Insert("MediumTent");
            zone.BlockedPlacementClassNames.Insert("LargeTent");
            zone.BlockedPlacementClassNames.Insert("CarTent");
            m_Safezones.Insert(zone);
            JsonFileLoader<array<ref DeutschZTraderZ_Safezone>>.JsonSaveFile(DeutschZTraderZ_Constants.SAFEZONES_FILE, m_Safezones);
        }
    }

    static void LoadVehicleSpawns()
    {
        DeutschZTraderZ_FileUtil.EnsureFolders();
        m_VehicleSpawns = new array<ref DeutschZTraderZ_VehicleSpawnPoint>;
        if (FileExist(DeutschZTraderZ_Constants.VEHICLE_SPAWNS_FILE))
            JsonFileLoader<array<ref DeutschZTraderZ_VehicleSpawnPoint>>.JsonLoadFile(DeutschZTraderZ_Constants.VEHICLE_SPAWNS_FILE, m_VehicleSpawns);
        if (!m_VehicleSpawns || m_VehicleSpawns.Count() == 0)
        {
            m_VehicleSpawns = new array<ref DeutschZTraderZ_VehicleSpawnPoint>;
            m_VehicleSpawns.Insert(new DeutschZTraderZ_VehicleSpawnPoint("Cars", "3730 402 5990", "0 0 0", 10));
            m_VehicleSpawns.Insert(new DeutschZTraderZ_VehicleSpawnPoint("Boats", "9762 2 1757", "0 0 0", 15));
            m_VehicleSpawns.Insert(new DeutschZTraderZ_VehicleSpawnPoint("Aircraft", "12000 140 12600", "0 0 0", 25));
            JsonFileLoader<array<ref DeutschZTraderZ_VehicleSpawnPoint>>.JsonSaveFile(DeutschZTraderZ_Constants.VEHICLE_SPAWNS_FILE, m_VehicleSpawns);
        }
    }

    static void LoadStaticObjects()
    {
        DeutschZTraderZ_FileUtil.EnsureFolders();
        m_StaticObjects = new array<ref DeutschZTraderZ_StaticObject>;
        if (FileExist(DeutschZTraderZ_Constants.STATIC_OBJECTS_FILE))
            JsonFileLoader<array<ref DeutschZTraderZ_StaticObject>>.JsonLoadFile(DeutschZTraderZ_Constants.STATIC_OBJECTS_FILE, m_StaticObjects);
        if (!m_StaticObjects)
            m_StaticObjects = new array<ref DeutschZTraderZ_StaticObject>;
        if (!FileExist(DeutschZTraderZ_Constants.STATIC_OBJECTS_FILE))
            JsonFileLoader<array<ref DeutschZTraderZ_StaticObject>>.JsonSaveFile(DeutschZTraderZ_Constants.STATIC_OBJECTS_FILE, m_StaticObjects);
    }

    static void LoadDelivery()
    {
        DeutschZTraderZ_FileUtil.EnsureFolders();
        m_DeliverySettings = new DeutschZTraderZ_DeliverySettings();
        if (FileExist(DeutschZTraderZ_Constants.DELIVERY_FILE))
            JsonFileLoader<DeutschZTraderZ_DeliverySettings>.JsonLoadFile(DeutschZTraderZ_Constants.DELIVERY_FILE, m_DeliverySettings);
        if (!m_DeliverySettings) m_DeliverySettings = new DeutschZTraderZ_DeliverySettings();
        JsonFileLoader<DeutschZTraderZ_DeliverySettings>.JsonSaveFile(DeutschZTraderZ_Constants.DELIVERY_FILE, m_DeliverySettings);
    }

    static void LoadP2P()
    {
        DeutschZTraderZ_FileUtil.EnsureFolders();
        m_P2PSettings = new DeutschZTraderZ_P2PSettings();
        if (FileExist(DeutschZTraderZ_Constants.P2P_FILE))
            JsonFileLoader<DeutschZTraderZ_P2PSettings>.JsonLoadFile(DeutschZTraderZ_Constants.P2P_FILE, m_P2PSettings);
        if (!m_P2PSettings) m_P2PSettings = new DeutschZTraderZ_P2PSettings();
        JsonFileLoader<DeutschZTraderZ_P2PSettings>.JsonSaveFile(DeutschZTraderZ_Constants.P2P_FILE, m_P2PSettings);
    }

    static void EnsureDefaultMarketFiles()
    {
        DeutschZTraderZ_Settings settings = GetSettings();
        if (!settings || !settings.CreateMissingMarketFiles)
            return;

        EnsureMarketFile("Ammo", CreateAmmoDefaults());
        EnsureMarketFile("Ammo_Boxes");
        EnsureMarketFile("Armbands");
        EnsureMarketFile("Assault_Rifles");
        EnsureMarketFile("Backpacks");
        EnsureMarketFile("Batteries");
        EnsureMarketFile("Bayonets");
        EnsureMarketFile("Belts");
        EnsureMarketFile("Boats");
        EnsureMarketFile("Build_Utilities");
        EnsureMarketFile("Building_Supplies");
        EnsureMarketFile("Buttstocks");
        EnsureMarketFile("Cars");
        EnsureMarketFile("Crossbows");
        EnsureMarketFile("DPM_UK");
        EnsureMarketFile("Drinks", CreateDrinkDefaults());
        EnsureMarketFile("Electronics");
        EnsureMarketFile("Explosives");
        EnsureMarketFile("Eyewear");
        EnsureMarketFile("Fish");
        EnsureMarketFile("Fishing");
        EnsureMarketFile("Flags");
        EnsureMarketFile("FLT_Germany");
        EnsureMarketFile("Food", CreateFoodDefaults());
        EnsureMarketFile("Food_Drinks");
        EnsureMarketFile("Fruits_Vegtables");
        EnsureMarketFile("Ghillie_Gun_Wraps");
        EnsureMarketFile("Ghillies");
        EnsureMarketFile("Gloves");
        EnsureMarketFile("Handguards");
        EnsureMarketFile("Handguns");
        EnsureMarketFile("Hats");
        EnsureMarketFile("Helmets");
        EnsureMarketFile("Holsters_Pouches");
        EnsureMarketFile("Hunting_Gear");
        EnsureMarketFile("Jackets");
        EnsureMarketFile("Launchers");
        EnsureMarketFile("Lights");
        EnsureMarketFile("LMGs");
        EnsureMarketFile("M05_Finnland");
        EnsureMarketFile("M84_DK");
        EnsureMarketFile("M98_Norway");
        EnsureMarketFile("Magazines");
        EnsureMarketFile("Masks");
        EnsureMarketFile("Meat");
        EnsureMarketFile("Medical", CreateMedicalDefaults());
        EnsureMarketFile("Melee");
        EnsureMarketFile("Muzzles");
        EnsureMarketFile("Navigation");
        EnsureMarketFile("Optics", CreateOpticDefaults());
        EnsureMarketFile("Pants");
        EnsureMarketFile("Parts");
        EnsureMarketFile("Pelts");
        EnsureMarketFile("Rifles");
        EnsureMarketFile("Shirts");
        EnsureMarketFile("Shoes");
        EnsureMarketFile("Shotguns");
        EnsureMarketFile("Sniper_Rifles");
        EnsureMarketFile("Storage");
        EnsureMarketFile("Sub_Machine_Guns");
        EnsureMarketFile("Supplies");
        EnsureMarketFile("Tools", CreateToolDefaults());
        EnsureMarketFile("Traps");
        EnsureMarketFile("Utilities");
        EnsureMarketFile("Vest_Armor");
        EnsureMarketFile("Vests");
        EnsureMarketFile("Wheels");

        EnsureMarketFile("Building", CreateBuildingDefaults());
        EnsureMarketFile("Clothing", CreateClothingDefaults());
        EnsureMarketFile("Vehicles", CreateVehicleDefaults());
        EnsureMarketFile("VehicleParts", CreateVehiclePartDefaults());
        EnsureMarketFile("Weapons", CreateWeaponDefaults());
    }

    static void EnsureMarketFile(string category, array<ref DeutschZTraderZ_MarketItem> fallbackItems = null)
    {
        if (category == "")
            return;

        string path = DeutschZTraderZ_Constants.MARKET_FOLDER + category + ".json";
        if (FileExist(path))
            return;

        DeutschZTraderZ_MarketFile file = new DeutschZTraderZ_MarketFile();
        file.Category = category;
        file.Items = LoadBundledMarketItems(category);
        if (!file.Items || file.Items.Count() == 0)
        {
            if (fallbackItems)
                file.Items = fallbackItems;
            else
                file.Items = new array<ref DeutschZTraderZ_MarketItem>;
        }

        NormalizeMarketFile(file, category);
        JsonFileLoader<DeutschZTraderZ_MarketFile>.JsonSaveFile(path, file);
    }

    static array<ref DeutschZTraderZ_MarketItem> LoadBundledMarketItems(string category)
    {
        DeutschZTraderZ_Settings settings = GetSettings();
        if (!settings || !settings.CreateBundledMarketFiles)
            return null;

        string path = DeutschZTraderZ_Constants.DEFAULT_MARKET_FOLDER + category + ".json";
        if (!FileExist(path))
            return null;

        ref array<ref DeutschZTraderZ_MarketItem> items = new array<ref DeutschZTraderZ_MarketItem>;
        JsonFileLoader<array<ref DeutschZTraderZ_MarketItem>>.JsonLoadFile(path, items);
        return items;
    }

    static void NormalizeMarketFile(DeutschZTraderZ_MarketFile file, string category)
    {
        if (!file)
            return;
        if (file.Category == "")
            file.Category = category;
        if (!file.Items)
            file.Items = new array<ref DeutschZTraderZ_MarketItem>;

        foreach (DeutschZTraderZ_MarketItem item : file.Items)
        {
            if (!item)
                continue;
            if (item.Category == "")
                item.Category = file.Category;
            if (item.DeliveryGroup == "")
                item.DeliveryGroup = item.Category;
            if (item.DeliverySize < 1)
                item.DeliverySize = 1;
            if (!item.SpawnAttachments)
                item.SpawnAttachments = new TStringArray;
            if (!item.OptionalAttachments)
                item.OptionalAttachments = new TStringArray;
            if (!item.Variants)
                item.Variants = new TStringArray;
        }
    }

    static DeutschZTraderZ_MarketItem NewItem(string className, string displayName, string category, int buy, int sell, bool canBuy = true, bool canSell = true)
    {
        DeutschZTraderZ_MarketItem item = new DeutschZTraderZ_MarketItem();
        item.ClassName = className;
        item.DisplayName = displayName;
        item.Category = category;
        item.BuyPrice = buy;
        item.SellPrice = sell;
        item.CanBuy = canBuy;
        item.CanSell = canSell;
        return item;
    }

    static array<ref DeutschZTraderZ_MarketItem> CreateFoodDefaults()
    {
        ref array<ref DeutschZTraderZ_MarketItem> items = new array<ref DeutschZTraderZ_MarketItem>;
        items.Insert(NewItem("BakedBeansCan", "Baked Beans", "Food", 120, 45));
        items.Insert(NewItem("PeachesCan", "Peaches", "Food", 120, 45));
        items.Insert(NewItem("SpaghettiCan", "Spaghetti", "Food", 120, 45));
        items.Insert(NewItem("TacticalBaconCan", "Tactical Bacon", "Food", 180, 70));
        return items;
    }

    static array<ref DeutschZTraderZ_MarketItem> CreateDrinkDefaults()
    {
        ref array<ref DeutschZTraderZ_MarketItem> items = new array<ref DeutschZTraderZ_MarketItem>;
        items.Insert(NewItem("SodaCan_Cola", "Cola", "Drinks", 90, 30));
        items.Insert(NewItem("SodaCan_Pipsi", "Pipsi", "Drinks", 90, 30));
        items.Insert(NewItem("WaterBottle", "Water Bottle", "Drinks", 150, 45));
        return items;
    }

    static array<ref DeutschZTraderZ_MarketItem> CreateMedicalDefaults()
    {
        ref array<ref DeutschZTraderZ_MarketItem> items = new array<ref DeutschZTraderZ_MarketItem>;
        items.Insert(NewItem("BandageDressing", "Bandage", "Medical", 100, 30));
        items.Insert(NewItem("Morphine", "Morphine", "Medical", 450, 120));
        items.Insert(NewItem("Epinephrine", "Epinephrine", "Medical", 450, 120));
        items.Insert(NewItem("TetracyclineAntibiotics", "Tetracycline", "Medical", 600, 180));
        return items;
    }

    static array<ref DeutschZTraderZ_MarketItem> CreateToolDefaults()
    {
        ref array<ref DeutschZTraderZ_MarketItem> items = new array<ref DeutschZTraderZ_MarketItem>;
        items.Insert(NewItem("Hatchet", "Hatchet", "Tools", 650, 150));
        items.Insert(NewItem("Hammer", "Hammer", "Tools", 550, 120));
        items.Insert(NewItem("Shovel", "Shovel", "Tools", 750, 180));
        items.Insert(NewItem("Wrench", "Wrench", "Tools", 500, 100));
        return items;
    }

    static array<ref DeutschZTraderZ_MarketItem> CreateWeaponDefaults()
    {
        ref array<ref DeutschZTraderZ_MarketItem> items = new array<ref DeutschZTraderZ_MarketItem>;
        DeutschZTraderZ_MarketItem item;
        item = NewItem("Mosin9130", "Mosin 91/30", "Weapons", 6500, 1900);
        item.OptionalAttachments.Insert("PUScopeOptic");
        items.Insert(item);
        item = NewItem("SKS", "SKS", "Weapons", 7200, 2100);
        items.Insert(item);
        item = NewItem("Winchester70", "Winchester 70", "Weapons", 8000, 2400);
        items.Insert(item);
        return items;
    }

    static array<ref DeutschZTraderZ_MarketItem> CreateAmmoDefaults()
    {
        ref array<ref DeutschZTraderZ_MarketItem> items = new array<ref DeutschZTraderZ_MarketItem>;
        items.Insert(NewItem("Ammo_762x54", "7.62x54", "Ammo", 450, 90));
        items.Insert(NewItem("Ammo_762x39", "7.62x39", "Ammo", 350, 70));
        items.Insert(NewItem("Ammo_308Win", ".308 Win", "Ammo", 500, 100));
        return items;
    }

    static array<ref DeutschZTraderZ_MarketItem> CreateOpticDefaults()
    {
        ref array<ref DeutschZTraderZ_MarketItem> items = new array<ref DeutschZTraderZ_MarketItem>;
        items.Insert(NewItem("PUScopeOptic", "PU Scope", "Optics", 2500, 600));
        items.Insert(NewItem("HuntingOptic", "Hunting Scope", "Optics", 3500, 900));
        return items;
    }

    static array<ref DeutschZTraderZ_MarketItem> CreateVehicleDefaults()
    {
        ref array<ref DeutschZTraderZ_MarketItem> items = new array<ref DeutschZTraderZ_MarketItem>;
        DeutschZTraderZ_MarketItem item;
        item = NewItem("OffroadHatchback", "Ada 4x4", "Vehicles", 45000, 15000);
        item.DeliveryGroup = "Cars";
        item.DeliveryItem = true;
        items.Insert(item);
        item = NewItem("CivilianSedan", "Olga", "Vehicles", 55000, 18000);
        item.DeliveryGroup = "Cars";
        item.DeliveryItem = true;
        items.Insert(item);
        return items;
    }

    static array<ref DeutschZTraderZ_MarketItem> CreateVehiclePartDefaults()
    {
        ref array<ref DeutschZTraderZ_MarketItem> items = new array<ref DeutschZTraderZ_MarketItem>;
        items.Insert(NewItem("SparkPlug", "Spark Plug", "VehicleParts", 1000, 200));
        items.Insert(NewItem("CarBattery", "Car Battery", "VehicleParts", 2500, 500));
        items.Insert(NewItem("TireRepairKit", "Tire Repair Kit", "VehicleParts", 1200, 250));
        return items;
    }

    static array<ref DeutschZTraderZ_MarketItem> CreateBuildingDefaults()
    {
        ref array<ref DeutschZTraderZ_MarketItem> items = new array<ref DeutschZTraderZ_MarketItem>;
        items.Insert(NewItem("NailBox", "Nail Box", "Building", 950, 180));
        items.Insert(NewItem("WoodenPlank", "Wooden Plank", "Building", 35, 5));
        items.Insert(NewItem("MetalPlate", "Metal Plate", "Building", 450, 80));
        return items;
    }

    static array<ref DeutschZTraderZ_MarketItem> CreateClothingDefaults()
    {
        ref array<ref DeutschZTraderZ_MarketItem> items = new array<ref DeutschZTraderZ_MarketItem>;
        items.Insert(NewItem("TacticalGloves_Black", "Tactical Gloves", "Clothing", 500, 100));
        items.Insert(NewItem("MilitaryBoots_Black", "Military Boots", "Clothing", 900, 200));
        items.Insert(NewItem("CargoPants_Black", "Cargo Pants", "Clothing", 800, 160));
        return items;
    }

    static void LoadMarketFiles()
    {
        m_MarketFiles = new map<string, ref DeutschZTraderZ_MarketFile>;
        m_GlobalItemIndex = new map<string, ref DeutschZTraderZ_MarketItem>;

        ref array<string> categories = GetAllConfiguredCategories();
        foreach (string category : categories)
        {
            LoadMarketFile(category);
        }
    }

    static array<string> GetAllConfiguredCategories()
    {
        ref array<string> categories = new array<string>;
        array<ref DeutschZTraderZ_Trader> traders = GetTraders();
        foreach (DeutschZTraderZ_Trader trader : traders)
        {
            if (!trader || !trader.Categories)
                continue;
            foreach (string category : trader.Categories)
            {
                if (category != "" && categories.Find(category) == -1)
                    categories.Insert(category);
            }
        }
        return categories;
    }

    static DeutschZTraderZ_MarketFile LoadMarketFile(string category)
    {
        if (!m_MarketFiles)
            m_MarketFiles = new map<string, ref DeutschZTraderZ_MarketFile>;
        if (!m_GlobalItemIndex)
            m_GlobalItemIndex = new map<string, ref DeutschZTraderZ_MarketItem>;

        if (m_MarketFiles.Contains(category))
            return m_MarketFiles.Get(category);

        string path = DeutschZTraderZ_Constants.MARKET_FOLDER + category + ".json";
        DeutschZTraderZ_MarketFile file = new DeutschZTraderZ_MarketFile();
        file.Category = category;
        if (FileExist(path))
        {
            JsonFileLoader<DeutschZTraderZ_MarketFile>.JsonLoadFile(path, file);
            if (ShouldTryRawMarketArray(file))
            {
                ref array<ref DeutschZTraderZ_MarketItem> rawItems = new array<ref DeutschZTraderZ_MarketItem>;
                JsonFileLoader<array<ref DeutschZTraderZ_MarketItem>>.JsonLoadFile(path, rawItems);
                if (rawItems)
                {
                    file = new DeutschZTraderZ_MarketFile();
                    file.Category = category;
                    file.Items = rawItems;
                    NormalizeMarketFile(file, category);
                    JsonFileLoader<DeutschZTraderZ_MarketFile>.JsonSaveFile(path, file);
                }
            }
        }
        if (!file)
            file = new DeutschZTraderZ_MarketFile();
        NormalizeMarketFile(file, category);

        foreach (DeutschZTraderZ_MarketItem item : file.Items)
        {
            if (!item || item.ClassName == "")
                continue;
            string key = item.ClassName;
            key.ToLower();
            m_GlobalItemIndex.Set(key, item);
        }

        m_MarketFiles.Set(category, file);
        return file;
    }

    static bool ShouldTryRawMarketArray(DeutschZTraderZ_MarketFile file)
    {
        DeutschZTraderZ_Settings settings = GetSettings();
        if (!settings || !settings.LoadRawMarketArrays)
            return false;
        if (!file)
            return true;
        if (file.Category != "")
            return false;
        if (file.Items && file.Items.Count() > 0)
            return false;
        return true;
    }

    static array<ref DeutschZTraderZ_MarketItem> GetItemsForCategories(array<string> categories)
    {
        ref array<ref DeutschZTraderZ_MarketItem> result = new array<ref DeutschZTraderZ_MarketItem>;
        ref TStringArray known = new TStringArray;
        if (!categories)
            return result;
        foreach (string category : categories)
        {
            DeutschZTraderZ_MarketFile file = LoadMarketFile(category);
            if (!file || !file.Items)
                continue;
            foreach (DeutschZTraderZ_MarketItem item : file.Items)
            {
                if (!item || item.ClassName == "")
                    continue;
                string key = item.ClassName;
                key.ToLower();
                if (known.Find(key) == -1)
                {
                    known.Insert(key);
                    result.Insert(item);
                }
            }
        }
        return result;
    }

    static DeutschZTraderZ_MarketItem FindMarketItem(string className)
    {
        if (className == "")
            return null;
        if (!m_GlobalItemIndex)
            LoadMarketFiles();
        string key = className;
        key.ToLower();
        if (m_GlobalItemIndex && m_GlobalItemIndex.Contains(key))
            return m_GlobalItemIndex.Get(key);
        return null;
    }
}
