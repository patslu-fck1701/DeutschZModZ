class DeutschZGroupsAdminBridge
{
    static bool ForceCreateGroup(string name, string tag, string ownerSteam64, string ownerName)
    {
        DeutschZGroupsManager manager = DeutschZGroupsAPI.GetManager();
        if (!manager)
        {
            return false;
        }
        return manager.CreateGroup(name, tag, ownerSteam64, ownerName) != NULL;
    }

    static bool ForceDisbandGroupByOwner(string ownerSteam64)
    {
        DeutschZGroupsManager manager = DeutschZGroupsAPI.GetManager();
        if (!manager)
        {
            return false;
        }
        return manager.DisbandGroup(ownerSteam64);
    }

    static bool AddServerMarker(string adminSteam64, DeutschZGroupMarkerData marker)
    {
        DeutschZGroupsManager manager = DeutschZGroupsAPI.GetManager();
        if (!manager)
        {
            return false;
        }
        return manager.AddStaticMarker(adminSteam64, marker);
    }
}
