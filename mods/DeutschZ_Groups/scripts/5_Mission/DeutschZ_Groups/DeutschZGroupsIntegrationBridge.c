class DeutschZGroupsIntegrationBridge
{
    static string GetGarageOwnerKey(string steam64)
    {
        string groupGarage = DeutschZGroupsAPI.GetSharedGarageId(steam64);
        if (groupGarage != "")
        {
            return "GROUP:" + groupGarage;
        }
        return "PLAYER:" + steam64;
    }

    static string GetBankAccountKey(string steam64)
    {
        string groupBank = DeutschZGroupsAPI.GetSharedBankAccountId(steam64);
        if (groupBank != "")
        {
            return "GROUP:" + groupBank;
        }
        return "PLAYER:" + steam64;
    }

    static bool CanVehicleAccess(string actorSteam64, string ownerSteam64)
    {
        return DeutschZGroupsAPI.CanAccessSharedVehicle(actorSteam64, ownerSteam64);
    }
}
