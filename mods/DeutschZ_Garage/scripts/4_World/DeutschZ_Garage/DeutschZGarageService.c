class DeutschZGarageService
{
    protected static void EnsureLogFile()
    {
        DeutschZGarageConfig.EnsureFolders();
    }

    protected static void WriteLog(string action, PlayerBase player, DeutschZGarageVehicle vehicle)
    {
        if (!DeutschZGarageConfig.Get().WriteParkingLog || !player || !player.GetIdentity() || !vehicle) {
            return;
        }

        ref array<ref DeutschZGarageParkingLogEntry> entries;
        if (FileExist(DeutschZGarageConstants.PARKING_LOG_FILE)) {
            JsonFileLoader<array<ref DeutschZGarageParkingLogEntry>>.JsonLoadFile(DeutschZGarageConstants.PARKING_LOG_FILE, entries);
        }
        if (!entries) {
            entries = new array<ref DeutschZGarageParkingLogEntry>();
        }

        DeutschZGarageParkingLogEntry entry = new DeutschZGarageParkingLogEntry();
        entry.Action = action;
        entry.SteamID = player.GetIdentity().GetPlainId();
        entry.PlayerName = player.GetIdentity().GetName();
        entry.VehicleClassName = vehicle.ClassName;
        entry.VehicleDisplayName = vehicle.DisplayName;
        entry.GarageID = vehicle.GarageID;
        entry.VehiclePosition = vehicle.LastPosition;
        entry.VehicleOrientation = vehicle.LastOrientation;
        entry.StationPosition = vehicle.StationPosition;
        entry.ServerTime = GetGame().GetTime();
        if (vehicle.Inventory) {
            entry.InventoryItems = vehicle.Inventory.Count();
        }

        entries.Insert(entry);
        JsonFileLoader<array<ref DeutschZGarageParkingLogEntry>>.JsonSaveFile(DeutschZGarageConstants.PARKING_LOG_FILE, entries);
    }

    protected static void CaptureVehicleInventory(Object vehicle, DeutschZGarageVehicle stored)
    {
        if (!vehicle || !stored || !DeutschZGarageConfig.Get().StoreVehicleInventory) {
            return;
        }

        EntityAI vehicleEntity = EntityAI.Cast(vehicle);
        if (!vehicleEntity || !vehicleEntity.GetInventory()) {
            return;
        }

        ref array<EntityAI> items = new array<EntityAI>();
        vehicleEntity.GetInventory().EnumerateInventory(InventoryTraversalType.PREORDER, items);
        foreach (EntityAI item : items) {
            if (!item || item == vehicleEntity) {
                continue;
            }

            int quantity = Math.Round(item.GetQuantity());
            if (quantity <= 0) {
                quantity = 1;
            }
            float health = item.GetHealth();
            stored.Inventory.Insert(new DeutschZGarageInventoryItem(item.GetType(), quantity, health));
        }
    }

    protected static void RestoreVehicleInventory(Object spawned, DeutschZGarageVehicle stored)
    {
        if (!spawned || !stored || !stored.Inventory || !DeutschZGarageConfig.Get().RestoreVehicleInventory) {
            return;
        }

        EntityAI vehicleEntity = EntityAI.Cast(spawned);
        if (!vehicleEntity || !vehicleEntity.GetInventory()) {
            return;
        }

        foreach (DeutschZGarageInventoryItem inventoryItem : stored.Inventory) {
            if (!inventoryItem || inventoryItem.ClassName == "") {
                continue;
            }

            EntityAI created = vehicleEntity.GetInventory().CreateInInventory(inventoryItem.ClassName);
            if (!created) {
                continue;
            }

            if (inventoryItem.Quantity > 0) {
                created.SetQuantity(inventoryItem.Quantity);
            }
            if (inventoryItem.Health > 0) {
                created.SetHealth(inventoryItem.Health);
            }
        }
    }

    static bool ConfigIsKindOf(string className, string baseName)
    {
        if (className == "" || baseName == "") {
            return false;
        }

        return GetGame().IsKindOf(className, baseName);
    }

    static bool IsKnownVehicleClass(string className)
    {
        if (className == "") {
            return false;
        }

        DeutschZGarageVehicleRules rules = DeutschZGarageVehicleRules.Get();
        if (rules && rules.IsBlocked(className)) {
            return false;
        }

        DeutschZGarageConfig config = DeutschZGarageConfig.Get();

        if (config && config.AllowVehicleByBaseClass && rules && rules.IsAllowedByBase(className)) {
            return true;
        }

        if (config && config.AllowVehicleByClassNameContains && rules && rules.IsAllowedByName(className)) {
            return true;
        }

        // Hard fallback for unusual mods when config files were not generated yet.
        if (GetGame().IsKindOf(className, "Transport")) return true;
        if (GetGame().IsKindOf(className, "CarScript")) return true;
        if (GetGame().IsKindOf(className, "ExpansionVehicleBase")) return true;

        return false;
    }

    static bool IsAllowedVehicleClass(string className)
    {
        if (!IsKnownVehicleClass(className)) {
            return false;
        }

        if (!DeutschZGarageConfig.Get().UseAllowedVehicleClassWhitelist) {
            return true;
        }

        ref array<string> allowed = DeutschZGarageConfig.Get().AllowedVehicleClasses;
        if (!allowed || allowed.Count() == 0) {
            return true;
        }

        return allowed.Find(className) >= 0;
    }

    static Object FindNearestVehicle(PlayerBase player, Object station)
    {
        if (!player || !station) {
            return null;
        }

        ref array<Object> objects = new array<Object>();
        ref array<CargoBase> cargos = new array<CargoBase>();
        GetGame().GetObjectsAtPosition(station.GetPosition(), DeutschZGarageConfig.Get().MaxStoreDistance, objects, cargos);

        float bestDistance = 999999.0;
        Object bestVehicle;
        foreach (Object obj : objects) {
            if (!obj || obj == station || obj == player) {
                continue;
            }
            if (!IsAllowedVehicleClass(obj.GetType())) {
                continue;
            }

            float distance = vector.Distance(station.GetPosition(), obj.GetPosition());
            if (distance < bestDistance) {
                bestDistance = distance;
                bestVehicle = obj;
            }
        }

        return bestVehicle;
    }

    static bool CanStoreMoreVehicles(DeutschZGaragePlayer playerGarage)
    {
        if (!playerGarage) {
            return false;
        }

        int maxVehicles = DeutschZGarageConfig.Get().MaxVehiclesPerPlayer;
        return maxVehicles < 0 || playerGarage.Vehicles.Count() < maxVehicles;
    }

    static bool ChargeFee(PlayerIdentity identity, int fee)
    {
        if (fee <= 0) {
            return true;
        }

        #ifdef DEUTSCHZ_BANKING
        return DeutschZ_Banking.RemoveMoney(identity, fee);
        #else
        return false;
        #endif
    }

    static bool StoreVehicle(PlayerBase player, Object vehicle, string garageId = "default", Object station = null)
    {
        if (!player || !player.GetIdentity() || !vehicle) {
            return false;
        }

        if (!DeutschZGarageConfig.Get().AllowStore || !IsAllowedVehicleClass(vehicle.GetType())) {
            return false;
        }

        DeutschZGaragePlayer playerGarage = DeutschZGaragePlayer.Load(player.GetIdentity());
        if (!CanStoreMoreVehicles(playerGarage)) {
            return false;
        }

        if (!ChargeFee(player.GetIdentity(), DeutschZGarageConfig.Get().StoreFee)) {
            return false;
        }

        DeutschZGarageVehicle stored = new DeutschZGarageVehicle();
        stored.ClassName = vehicle.GetType();
        stored.DisplayName = vehicle.GetDisplayName();
        if (stored.DisplayName == "") {
            stored.DisplayName = stored.ClassName;
        }
        stored.OwnerSteamID = player.GetIdentity().GetPlainId();
        stored.OwnerName = player.GetIdentity().GetName();
        stored.GarageID = garageId;
        stored.LastPosition = vehicle.GetPosition();
        stored.LastOrientation = vehicle.GetOrientation();
        stored.StationPosition = vector.Zero;
        if (station) {
            stored.StationPosition = station.GetPosition();
        }
        stored.StoredAt = GetGame().GetTime();
        CaptureVehicleInventory(vehicle, stored);

        playerGarage.Vehicles.Insert(stored);
        playerGarage.Save();
        WriteLog("Stored", player, stored);
        GetGame().ObjectDelete(vehicle);
        return true;
    }

    static bool StoreNearestVehicle(PlayerBase player, Object station)
    {
        Object vehicle = FindNearestVehicle(player, station);
        if (!vehicle) {
            return false;
        }

        return StoreVehicle(player, vehicle, "default", station);
    }

    static bool RestoreVehicle(PlayerBase player, Object station, int index)
    {
        if (!player || !player.GetIdentity() || !station || index < 0) {
            return false;
        }

        DeutschZGaragePlayer playerGarage = DeutschZGaragePlayer.Load(player.GetIdentity());
        if (!playerGarage || index >= playerGarage.Vehicles.Count()) {
            return false;
        }

        if (!DeutschZGarageConfig.Get().AllowRestore) {
            return false;
        }

        if (!ChargeFee(player.GetIdentity(), DeutschZGarageConfig.Get().RestoreFee)) {
            return false;
        }

        DeutschZGarageVehicle stored = playerGarage.Vehicles.Get(index);
        vector spawnPos = stored.LastPosition;
        if (!DeutschZGarageConfig.Get().RestoreAtStoredPosition && station) {
            spawnPos = station.GetPosition() + (station.GetDirection() * DeutschZGarageConfig.Get().RestoreSpawnDistance);
        }

        Object spawned = GetGame().CreateObjectEx(stored.ClassName, spawnPos, ECE_CREATEPHYSICS | ECE_UPDATEPATHGRAPH);
        if (!spawned) {
            return false;
        }

        spawned.SetPosition(spawnPos);
        spawned.SetOrientation(stored.LastOrientation);
        RestoreVehicleInventory(spawned, stored);
        WriteLog("Restored", player, stored);
        playerGarage.Vehicles.Remove(index);
        playerGarage.Save();
        return true;
    }

    static int GetVehicleCount(PlayerIdentity identity)
    {
        DeutschZGaragePlayer playerGarage = DeutschZGaragePlayer.Load(identity);
        if (!playerGarage) {
            return 0;
        }
        return playerGarage.Vehicles.Count();
    }
}
