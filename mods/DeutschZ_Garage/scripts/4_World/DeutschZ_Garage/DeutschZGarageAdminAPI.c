class DeutschZGarageAdminAPI
{
    static PlayerBase FindOnlinePlayerBySteamID(string steamId)
    {
        if (steamId == "") {
            return null;
        }

        ref array<Man> players = new array<Man>();
        GetGame().GetPlayers(players);

        foreach (Man man : players) {
            PlayerBase player = PlayerBase.Cast(man);
            if (!player || !player.GetIdentity()) {
                continue;
            }

            if (player.GetIdentity().GetPlainId() == steamId) {
                return player;
            }
        }

        return null;
    }

    static string GetOnlineNameOrFallback(string steamId, string fallbackName = "")
    {
        PlayerBase player = FindOnlinePlayerBySteamID(steamId);
        if (player && player.GetIdentity()) {
            return player.GetIdentity().GetName();
        }

        if (fallbackName != "") {
            return fallbackName;
        }

        return steamId;
    }

    static DeutschZGaragePlayer LoadGarageBySteamID(string steamId, bool createIfMissing = true, string fallbackName = "")
    {
        steamId.Trim();
        if (steamId == "") {
            return null;
        }

        DeutschZGaragePlayer.EnsureFolders();

        DeutschZGaragePlayer playerGarage;
        string path = DeutschZGaragePlayer.GetPlayerPath(steamId);
        if (FileExist(path)) {
            JsonFileLoader<DeutschZGaragePlayer>.JsonLoadFile(path, playerGarage);
        }

        if (!playerGarage && createIfMissing) {
            playerGarage = new DeutschZGaragePlayer();
            playerGarage.SteamID = steamId;
            playerGarage.PlayerName = GetOnlineNameOrFallback(steamId, fallbackName);
            playerGarage.Vehicles = new array<ref DeutschZGarageVehicle>();
            playerGarage.Save();
        }

        if (playerGarage) {
            if (!playerGarage.Vehicles) {
                playerGarage.Vehicles = new array<ref DeutschZGarageVehicle>();
            }

            string name = GetOnlineNameOrFallback(steamId, playerGarage.PlayerName);
            if (name != "") {
                playerGarage.PlayerName = name;
            }
            if (playerGarage.PlayerName == "") {
                playerGarage.PlayerName = steamId;
            }
        }

        return playerGarage;
    }

    static bool ReloadAll(out string message)
    {
        DeutschZGarageConfig.Load();
        DeutschZGaragePlayer.EnsureFolders();
        DeutschZGarageVehicleRules.Load();
        DeutschZGarageStations.Load();
        DeutschZGarageImpoundConfig.Load();
        message = "DeutschZ_Garage configs reloaded.";
        return true;
    }

    static bool GetStatus(out string message)
    {
        DeutschZGarageConfig config = DeutschZGarageConfig.Get();
        if (!config) {
            message = "DeutschZ_Garage config not loaded.";
            return false;
        }

        message = "DeutschZ_Garage connected. maxSlots=" + config.MaxVehiclesPerPlayer.ToString() + " storeFee=" + config.StoreFee.ToString() + " restoreFee=" + config.RestoreFee.ToString();
        return true;
    }

    static bool BuildVehicleRows(string steamId, array<string> rows, int maxRows, out string message)
    {
        if (!rows) {
            message = "Garage rows target missing.";
            return false;
        }

        rows.Clear();
        if (maxRows <= 0) {
            maxRows = 10;
        }

        DeutschZGaragePlayer playerGarage = LoadGarageBySteamID(steamId, false);
        if (!playerGarage) {
            rows.Insert("No garage file|Missing|" + steamId + "|0 0 0");
            message = "No Garage data found for " + steamId + ".";
            return false;
        }

        for (int i = 0; i < playerGarage.Vehicles.Count(); i++) {
            if (rows.Count() >= maxRows) {
                break;
            }

            DeutschZGarageVehicle vehicle = playerGarage.Vehicles.Get(i);
            if (!vehicle) {
                continue;
            }

            string display = vehicle.DisplayName;
            if (display == "") {
                display = vehicle.ClassName;
            }

            rows.Insert(display + "|Stored|" + playerGarage.PlayerName + "|" + vehicle.LastPosition.ToString());
        }

        message = "Garage vehicles loaded for " + playerGarage.PlayerName + ". Count " + playerGarage.Vehicles.Count().ToString() + ".";
        return true;
    }

    static void CaptureVehicleInventory(Object vehicle, DeutschZGarageVehicle stored)
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

    static Object FindNearestAllowedVehicle(vector position, float radius, Object ignoreObject = null)
    {
        if (radius <= 0) {
            radius = 25.0;
        }

        ref array<Object> objects = new array<Object>();
        ref array<CargoBase> cargos = new array<CargoBase>();
        GetGame().GetObjectsAtPosition(position, radius, objects, cargos);

        float bestDistance = 999999.0;
        Object bestVehicle;
        foreach (Object obj : objects) {
            if (!obj || obj == ignoreObject) {
                continue;
            }

            if (!DeutschZGarageService.IsAllowedVehicleClass(obj.GetType())) {
                continue;
            }

            float distance = vector.Distance(position, obj.GetPosition());
            if (distance < bestDistance) {
                bestDistance = distance;
                bestVehicle = obj;
            }
        }

        return bestVehicle;
    }

    static bool AdminImpoundNearest(PlayerBase adminPlayer, string ownerSteamId, float radius, out string message)
    {
        message = "";
        if (!adminPlayer) {
            message = "Admin player not found.";
            return false;
        }

        ownerSteamId.Trim();
        if (ownerSteamId == "") {
            message = "Target Steam64 missing.";
            return false;
        }

        Object vehicle = FindNearestAllowedVehicle(adminPlayer.GetPosition(), radius, adminPlayer);
        if (!vehicle) {
            message = "No allowed vehicle found near admin.";
            return false;
        }

        DeutschZGaragePlayer playerGarage = LoadGarageBySteamID(ownerSteamId, true);
        if (!playerGarage) {
            message = "Could not load or create Garage data for " + ownerSteamId + ".";
            return false;
        }

        if (!DeutschZGarageService.CanStoreMoreVehicles(playerGarage)) {
            message = "Garage slot limit reached for " + playerGarage.PlayerName + ".";
            return false;
        }

        DeutschZGarageVehicle stored = new DeutschZGarageVehicle();
        stored.ClassName = vehicle.GetType();
        stored.DisplayName = vehicle.GetDisplayName();
        if (stored.DisplayName == "") {
            stored.DisplayName = stored.ClassName;
        }
        stored.OwnerSteamID = ownerSteamId;
        stored.OwnerName = playerGarage.PlayerName;
        stored.GarageID = DeutschZGarageImpoundConfig.Get().ImpoundGarageID;
        if (stored.GarageID == "") {
            stored.GarageID = "admin_impound";
        }
        stored.LastPosition = vehicle.GetPosition();
        stored.LastOrientation = vehicle.GetOrientation();
        stored.StationPosition = adminPlayer.GetPosition();
        stored.StoredAt = GetGame().GetTime();
        CaptureVehicleInventory(vehicle, stored);

        playerGarage.Vehicles.Insert(stored);
        playerGarage.Save();
        GetGame().ObjectDelete(vehicle);

        message = "Impounded nearest vehicle " + stored.DisplayName + " into Garage of " + playerGarage.PlayerName + ".";
        return true;
    }
}
