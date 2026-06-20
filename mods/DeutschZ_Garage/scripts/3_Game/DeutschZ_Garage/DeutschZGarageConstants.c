enum DeutschZGarageRPCs
{
    DEUTSCHZ_GARAGE_RPC_START = 71383000,
    DEUTSCHZ_GARAGE_OPEN,
    DEUTSCHZ_GARAGE_STORE,
    DEUTSCHZ_GARAGE_RESTORE,
    DEUTSCHZ_GARAGE_SYNC,
    DEUTSCHZ_GARAGE_RPC_END
}

class DeutschZGarageConstants
{
    static const string ROOT_FOLDER = "$profile:DeutschZ/";
    static const string GARAGE_FOLDER = "$profile:DeutschZ/Garage/";
    static const string CONFIG_FOLDER = "$profile:DeutschZ/Garage/Config/";
    static const string DATA_FOLDER = "$profile:DeutschZ/Garage/Data/";
    static const string PLAYER_FOLDER = "$profile:DeutschZ/Garage/Data/Players/";
    static const string LOG_FOLDER = "$profile:DeutschZ/Garage/Data/Logs/";
    static const string CONFIG_FILE = "$profile:DeutschZ/Garage/Config/GarageConfig.json";
    static const string VEHICLE_RULES_FILE = "$profile:DeutschZ/Garage/Config/VehicleRules.json";
    static const string STATIONS_FILE = "$profile:DeutschZ/Garage/Config/GarageStations.json";
    static const string IMPOUND_CONFIG_FILE = "$profile:DeutschZ/Garage/Config/ImpoundConfig.json";
    static const string PARKING_LOG_FILE = "$profile:DeutschZ/Garage/Data/Logs/ParkingLog.json";
}

class DeutschZGarageInventoryItem
{
    string ClassName;
    int Quantity;
    float Health;

    void DeutschZGarageInventoryItem(string className = "", int quantity = 0, float health = 0)
    {
        ClassName = className;
        Quantity = quantity;
        Health = health;
    }
}

class DeutschZGarageVehicle
{
    string ClassName;
    string DisplayName;
    string OwnerSteamID;
    string OwnerName;
    string GarageID;
    vector LastPosition;
    vector LastOrientation;
    vector StationPosition;
    int StoredAt;
    ref array<ref DeutschZGarageInventoryItem> Inventory = new array<ref DeutschZGarageInventoryItem>();

    void DeutschZGarageVehicle()
    {
        ClassName = "";
        DisplayName = "";
        OwnerSteamID = "";
        OwnerName = "";
        GarageID = "default";
        LastPosition = vector.Zero;
        LastOrientation = vector.Zero;
        StationPosition = vector.Zero;
        StoredAt = 0;
    }
}

class DeutschZGarageParkingLogEntry
{
    string Action;
    string SteamID;
    string PlayerName;
    string VehicleClassName;
    string VehicleDisplayName;
    string GarageID;
    vector VehiclePosition;
    vector VehicleOrientation;
    vector StationPosition;
    int InventoryItems;
    int ServerTime;
}

class DeutschZGarageStationEntry
{
    string GarageID;
    string Name;
    string ClassName;
    vector Position;
    vector Orientation;
    bool Enabled;

    void DeutschZGarageStationEntry(string garageId = "default", string name = "Default Garage", string className = "DeutschZ_ParkingStation", vector position = "0 0 0", vector orientation = "0 0 0", bool enabled = false)
    {
        GarageID = garageId;
        Name = name;
        ClassName = className;
        Position = position;
        Orientation = orientation;
        Enabled = enabled;
    }
}
