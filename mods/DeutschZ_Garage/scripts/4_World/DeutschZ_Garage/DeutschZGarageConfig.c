class DeutschZGarageConfig
{
    static const int CURRENT_VERSION = 4;

    int ConfigVersion = CURRENT_VERSION;
    int StoreFee = 0;
    int RestoreFee = 0;
    int MaxVehiclesPerPlayer = 5;
    float MaxStoreDistance = 50.0;
    float RestoreSpawnDistance = 6.0;
    bool RestoreAtStoredPosition = true;
    bool StoreVehicleInventory = true;
    bool RestoreVehicleInventory = true;
    bool WriteParkingLog = true;
    bool AllowStore = true;
    bool AllowRestore = true;
    bool UseAllowedVehicleClassWhitelist = false;
    bool AllowVehicleByBaseClass = true;
    bool AllowVehicleByClassNameContains = true;
    bool AutoSpawnStationsFromConfig = false;
    ref array<string> AllowedVehicleClasses = new array<string>();

    protected static ref DeutschZGarageConfig m_Instance;

    static void EnsureFolders()
    {
        if (!FileExist(DeutschZGarageConstants.ROOT_FOLDER)) {
            MakeDirectory(DeutschZGarageConstants.ROOT_FOLDER);
        }
        if (!FileExist(DeutschZGarageConstants.GARAGE_FOLDER)) {
            MakeDirectory(DeutschZGarageConstants.GARAGE_FOLDER);
        }
        if (!FileExist(DeutschZGarageConstants.CONFIG_FOLDER)) {
            MakeDirectory(DeutschZGarageConstants.CONFIG_FOLDER);
        }
        if (!FileExist(DeutschZGarageConstants.DATA_FOLDER)) {
            MakeDirectory(DeutschZGarageConstants.DATA_FOLDER);
        }
        if (!FileExist(DeutschZGarageConstants.LOG_FOLDER)) {
            MakeDirectory(DeutschZGarageConstants.LOG_FOLDER);
        }
    }

    static DeutschZGarageConfig Get()
    {
        if (!m_Instance) {
            Load();
        }
        return m_Instance;
    }

    void SetDefaults()
    {
        ConfigVersion = CURRENT_VERSION;
        StoreFee = 0;
        RestoreFee = 0;
        MaxVehiclesPerPlayer = 5;
        MaxStoreDistance = 50.0;
        RestoreSpawnDistance = 6.0;
        RestoreAtStoredPosition = true;
        StoreVehicleInventory = true;
        RestoreVehicleInventory = true;
        WriteParkingLog = true;
        AllowStore = true;
        AllowRestore = true;
        UseAllowedVehicleClassWhitelist = false;
        AllowVehicleByBaseClass = true;
        AllowVehicleByClassNameContains = true;
        AutoSpawnStationsFromConfig = false;
        if (!AllowedVehicleClasses) {
            AllowedVehicleClasses = new array<string>();
        }
    }

    void Update()
    {
        if (!AllowedVehicleClasses) {
            AllowedVehicleClasses = new array<string>();
        }

        if (ConfigVersion < 3) {
            AllowVehicleByBaseClass = true;
            AllowVehicleByClassNameContains = true;
            AutoSpawnStationsFromConfig = false;
            RestoreSpawnDistance = 6.0;
        }

        if (ConfigVersion < 4) {
            RestoreAtStoredPosition = true;
        }

        ConfigVersion = CURRENT_VERSION;
    }

    static void Load()
    {
        EnsureFolders();
        if (FileExist(DeutschZGarageConstants.CONFIG_FILE)) {
            JsonFileLoader<DeutschZGarageConfig>.JsonLoadFile(DeutschZGarageConstants.CONFIG_FILE, m_Instance);
        }

        if (!m_Instance) {
            m_Instance = new DeutschZGarageConfig();
            m_Instance.SetDefaults();
        }

        m_Instance.Update();
        m_Instance.Save();

        DeutschZGarageVehicleRules.Load();
        DeutschZGarageStations.Load();
        DeutschZGarageImpoundConfig.Load();
    }

    void Save()
    {
        EnsureFolders();
        JsonFileLoader<DeutschZGarageConfig>.JsonSaveFile(DeutschZGarageConstants.CONFIG_FILE, this);
    }
}

class DeutschZGarageVehicleRules
{
    static const int CURRENT_VERSION = 1;

    int ConfigVersion = CURRENT_VERSION;
    ref array<string> AllowedBaseClasses = new array<string>();
    ref array<string> AllowedClassNameContains = new array<string>();
    ref array<string> BlockedVehicleClasses = new array<string>();
    ref array<string> BlockedClassNameContains = new array<string>();

    protected static ref DeutschZGarageVehicleRules m_Instance;

    static DeutschZGarageVehicleRules Get()
    {
        if (!m_Instance) {
            Load();
        }
        return m_Instance;
    }

    static void Load()
    {
        DeutschZGarageConfig.EnsureFolders();

        if (FileExist(DeutschZGarageConstants.VEHICLE_RULES_FILE)) {
            JsonFileLoader<DeutschZGarageVehicleRules>.JsonLoadFile(DeutschZGarageConstants.VEHICLE_RULES_FILE, m_Instance);
        }

        if (!m_Instance) {
            m_Instance = new DeutschZGarageVehicleRules();
            m_Instance.LoadDefault();
        }

        m_Instance.Validate();
        m_Instance.Save();
    }

    void Validate()
    {
        ConfigVersion = CURRENT_VERSION;
        if (!AllowedBaseClasses) AllowedBaseClasses = new array<string>();
        if (!AllowedClassNameContains) AllowedClassNameContains = new array<string>();
        if (!BlockedVehicleClasses) BlockedVehicleClasses = new array<string>();
        if (!BlockedClassNameContains) BlockedClassNameContains = new array<string>();
    }

    void LoadDefault()
    {
        AllowedBaseClasses.Clear();
        AllowedClassNameContains.Clear();
        BlockedVehicleClasses.Clear();
        BlockedClassNameContains.Clear();

        // Vanilla DayZ / common vehicle inheritance.
        AllowedBaseClasses.Insert("Transport");
        AllowedBaseClasses.Insert("CarScript");
        AllowedBaseClasses.Insert("Truck_01_Base");
        AllowedBaseClasses.Insert("OffroadHatchback");
        AllowedBaseClasses.Insert("CivilianSedan");
        AllowedBaseClasses.Insert("Hatchback_02");
        AllowedBaseClasses.Insert("Sedan_02");
        AllowedBaseClasses.Insert("BoatScript");

        // Expansion vehicle inheritance. Safe when Expansion is not loaded.
        AllowedBaseClasses.Insert("ExpansionVehicleBase");
        AllowedBaseClasses.Insert("ExpansionCar");
        AllowedBaseClasses.Insert("ExpansionVehicleCarBase");
        AllowedBaseClasses.Insert("ExpansionVehicleBoatBase");
        AllowedBaseClasses.Insert("ExpansionBoatScript");
        AllowedBaseClasses.Insert("ExpansionVehicleHelicopterBase");
        AllowedBaseClasses.Insert("ExpansionHelicopterScript");

        // Mod fallbacks: A2Trucks, MBM, and broad class name detection.
        AllowedClassNameContains.Insert("a2truck");
        AllowedClassNameContains.Insert("a2_truck");
        AllowedClassNameContains.Insert("a2trucks");
        AllowedClassNameContains.Insert("mbm");
        AllowedClassNameContains.Insert("vehicle");
        AllowedClassNameContains.Insert("car");
        AllowedClassNameContains.Insert("truck");
        AllowedClassNameContains.Insert("heli");
        AllowedClassNameContains.Insert("helicopter");
        AllowedClassNameContains.Insert("boat");
        AllowedClassNameContains.Insert("bike");
        AllowedClassNameContains.Insert("quad");

        // Keep these blocked by default so placed stations/kits are never treated as vehicles.
        BlockedVehicleClasses.Insert("DeutschZ_ParkingStation");
        BlockedVehicleClasses.Insert("DeutschZ_Garage_Sign");
        BlockedVehicleClasses.Insert("DeutschZ_Garage_Kit");
        BlockedVehicleClasses.Insert("DeutschZ_Garage_Kit_Placing");
        BlockedClassNameContains.Insert("parkingstation");
        BlockedClassNameContains.Insert("garage_kit");
    }

    void Save()
    {
        DeutschZGarageConfig.EnsureFolders();
        JsonFileLoader<DeutschZGarageVehicleRules>.JsonSaveFile(DeutschZGarageConstants.VEHICLE_RULES_FILE, this);
    }

    bool IsBlocked(string className)
    {
        if (className == "") {
            return true;
        }

        if (BlockedVehicleClasses && BlockedVehicleClasses.Find(className) >= 0) {
            return true;
        }

        string lower = className;
        lower.ToLower();
        foreach (string part : BlockedClassNameContains) {
            string needle = part;
            needle.ToLower();
            if (needle != "" && lower.Contains(needle)) {
                return true;
            }
        }

        return false;
    }

    bool IsAllowedByBase(string className)
    {
        foreach (string baseName : AllowedBaseClasses) {
            if (baseName != "" && GetGame().IsKindOf(className, baseName)) {
                return true;
            }
        }

        return false;
    }

    bool IsAllowedByName(string className)
    {
        string lower = className;
        lower.ToLower();

        foreach (string part : AllowedClassNameContains) {
            string needle = part;
            needle.ToLower();
            if (needle != "" && lower.Contains(needle)) {
                return true;
            }
        }

        return false;
    }
}

class DeutschZGarageStations
{
    ref array<ref DeutschZGarageStationEntry> Stations = new array<ref DeutschZGarageStationEntry>();

    protected static ref DeutschZGarageStations m_Instance;

    static DeutschZGarageStations Get()
    {
        if (!m_Instance) {
            Load();
        }
        return m_Instance;
    }

    static void Load()
    {
        DeutschZGarageConfig.EnsureFolders();

        if (FileExist(DeutschZGarageConstants.STATIONS_FILE)) {
            JsonFileLoader<DeutschZGarageStations>.JsonLoadFile(DeutschZGarageConstants.STATIONS_FILE, m_Instance);
        }

        if (!m_Instance) {
            m_Instance = new DeutschZGarageStations();
            m_Instance.LoadDefault();
        }

        if (!m_Instance.Stations) {
            m_Instance.Stations = new array<ref DeutschZGarageStationEntry>();
        }

        m_Instance.Save();
    }

    void LoadDefault()
    {
        Stations.Clear();
        Stations.Insert(new DeutschZGarageStationEntry("default", "Example Garage - disabled", "DeutschZ_ParkingStation", "0 0 0", "0 0 0", false));
    }

    void Save()
    {
        DeutschZGarageConfig.EnsureFolders();
        JsonFileLoader<DeutschZGarageStations>.JsonSaveFile(DeutschZGarageConstants.STATIONS_FILE, this);
    }

    void SpawnConfiguredStations()
    {
        if (!GetGame().IsServer()) {
            return;
        }

        if (!DeutschZGarageConfig.Get().AutoSpawnStationsFromConfig) {
            return;
        }

        foreach (DeutschZGarageStationEntry entry : Stations) {
            if (!entry || !entry.Enabled || entry.ClassName == "" || entry.Position == vector.Zero) {
                continue;
            }

            Object station = GetGame().CreateObjectEx(entry.ClassName, entry.Position, ECE_PLACE_ON_SURFACE | ECE_UPDATEPATHGRAPH);
            if (station) {
                station.SetOrientation(entry.Orientation);
                station.SetPosition(entry.Position);
            }
        }
    }
}

class DeutschZGarageImpoundConfig
{
    static const int CURRENT_VERSION = 1;

    int ConfigVersion = CURRENT_VERSION;
    bool EnableAutoImpound = false;
    int DefaultImpoundAfterSeconds = 86400;
    float MinPlayerDistanceForImpound = 50.0;
    bool ImpoundRuinedVehicles = false;
    bool ReturnToOriginalGarage = true;
    string ImpoundGarageID = "impound";

    protected static ref DeutschZGarageImpoundConfig m_Instance;

    static DeutschZGarageImpoundConfig Get()
    {
        if (!m_Instance) {
            Load();
        }
        return m_Instance;
    }

    static void Load()
    {
        DeutschZGarageConfig.EnsureFolders();
        if (FileExist(DeutschZGarageConstants.IMPOUND_CONFIG_FILE)) {
            JsonFileLoader<DeutschZGarageImpoundConfig>.JsonLoadFile(DeutschZGarageConstants.IMPOUND_CONFIG_FILE, m_Instance);
        }
        if (!m_Instance) {
            m_Instance = new DeutschZGarageImpoundConfig();
        }
        m_Instance.ConfigVersion = CURRENT_VERSION;
        m_Instance.Save();
    }

    void Save()
    {
        DeutschZGarageConfig.EnsureFolders();
        JsonFileLoader<DeutschZGarageImpoundConfig>.JsonSaveFile(DeutschZGarageConstants.IMPOUND_CONFIG_FILE, this);
    }
}
