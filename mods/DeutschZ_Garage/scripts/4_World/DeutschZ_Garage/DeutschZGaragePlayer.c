class DeutschZGaragePlayer
{
    string SteamID;
    string PlayerName;
    ref array<ref DeutschZGarageVehicle> Vehicles = new array<ref DeutschZGarageVehicle>();

    static void EnsureFolders()
    {
        DeutschZGarageConfig.EnsureFolders();
        if (!FileExist(DeutschZGarageConstants.DATA_FOLDER)) {
            MakeDirectory(DeutschZGarageConstants.DATA_FOLDER);
        }
        if (!FileExist(DeutschZGarageConstants.PLAYER_FOLDER)) {
            MakeDirectory(DeutschZGarageConstants.PLAYER_FOLDER);
        }
    }

    static string GetPlayerPath(string steamId)
    {
        return DeutschZGarageConstants.PLAYER_FOLDER + steamId + ".json";
    }

    static DeutschZGaragePlayer CreateDefault(PlayerIdentity identity)
    {
        DeutschZGaragePlayer playerGarage = new DeutschZGaragePlayer();
        playerGarage.SteamID = identity.GetPlainId();
        playerGarage.PlayerName = identity.GetName();
        return playerGarage;
    }

    static DeutschZGaragePlayer Load(PlayerIdentity identity)
    {
        if (!identity) {
            return null;
        }

        EnsureFolders();

        DeutschZGaragePlayer playerGarage;
        string path = GetPlayerPath(identity.GetPlainId());
        if (FileExist(path)) {
            JsonFileLoader<DeutschZGaragePlayer>.JsonLoadFile(path, playerGarage);
        }

        if (!playerGarage) {
            playerGarage = CreateDefault(identity);
            playerGarage.Save();
        }

        playerGarage.PlayerName = identity.GetName();
        return playerGarage;
    }

    void Save()
    {
        EnsureFolders();
        JsonFileLoader<DeutschZGaragePlayer>.JsonSaveFile(GetPlayerPath(SteamID), this);
    }
}
