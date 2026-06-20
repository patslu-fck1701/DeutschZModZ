class DeutschZGroupsAPI
{
    static bool IsAvailable()
    {
        return GetManager() != NULL;
    }

    static DeutschZGroupsManager GetManager()
    {
        return DeutschZGroupsRuntime.GetManager();
    }

    static string GetPlayerGroupId(string steam64)
    {
        DeutschZGroupsManager manager = GetManager();
        if (!manager) return "";
        return manager.GetPlayerGroupId(steam64);
    }

    static string GetPlayerGroupTag(string steam64)
    {
        DeutschZGroupsManager manager = GetManager();
        if (!manager) return "";
        return manager.GetPlayerGroupTag(steam64);
    }

    static string GetPlayerRank(string steam64)
    {
        DeutschZGroupsManager manager = GetManager();
        if (!manager) return "";
        return manager.GetPlayerRank(steam64);
    }

    static bool IsSameGroup(string steam64A, string steam64B)
    {
        string groupA = GetPlayerGroupId(steam64A);
        if (groupA == "") return false;
        return groupA == GetPlayerGroupId(steam64B);
    }

    static bool HasPermission(string steam64, string permission)
    {
        DeutschZGroupsManager manager = GetManager();
        if (!manager) return false;
        return manager.HasPermission(steam64, permission);
    }

    static bool CanUseGroupGarage(string steam64)
    {
        return HasPermission(steam64, DeutschZGroupPermissionKeys.GARAGE_VIEW);
    }

    static bool CanWithdrawGroupVehicle(string steam64)
    {
        return HasPermission(steam64, DeutschZGroupPermissionKeys.GARAGE_WITHDRAW);
    }

    static bool CanDepositGroupVehicle(string steam64)
    {
        return HasPermission(steam64, DeutschZGroupPermissionKeys.GARAGE_DEPOSIT);
    }

    static bool CanManageGroupGarage(string steam64)
    {
        return HasPermission(steam64, DeutschZGroupPermissionKeys.GARAGE_MANAGE);
    }

    static bool CanViewGroupBank(string steam64)
    {
        return HasPermission(steam64, DeutschZGroupPermissionKeys.BANK_VIEW);
    }

    static bool CanWithdrawGroupMoney(string steam64)
    {
        return HasPermission(steam64, DeutschZGroupPermissionKeys.BANK_WITHDRAW);
    }

    static bool CanDepositGroupMoney(string steam64)
    {
        return HasPermission(steam64, DeutschZGroupPermissionKeys.BANK_DEPOSIT);
    }

    static bool CanTransferGroupMoney(string steam64)
    {
        return HasPermission(steam64, DeutschZGroupPermissionKeys.BANK_TRANSFER);
    }

    static bool CanManageGroupBank(string steam64)
    {
        return HasPermission(steam64, DeutschZGroupPermissionKeys.BANK_MANAGE);
    }

    static string GetSharedGarageId(string steam64)
    {
        DeutschZGroupsManager manager = GetManager();
        if (!manager) return "";
        return manager.GetSharedGarageId(steam64);
    }

    static string GetSharedBankAccountId(string steam64)
    {
        DeutschZGroupsManager manager = GetManager();
        if (!manager) return "";
        return manager.GetSharedBankAccountId(steam64);
    }

    static bool AddGroupChatMessage(string steam64, string senderName, string message)
    {
        DeutschZGroupsManager manager = GetManager();
        if (!manager) return false;
        return manager.AddGroupChatMessage(steam64, senderName, message);
    }

    static bool CanAccessSharedVehicle(string actorSteam64, string ownerSteam64)
    {
        if (actorSteam64 == ownerSteam64) return true;
        return IsSameGroup(actorSteam64, ownerSteam64) && CanUseGroupGarage(actorSteam64);
    }
}
