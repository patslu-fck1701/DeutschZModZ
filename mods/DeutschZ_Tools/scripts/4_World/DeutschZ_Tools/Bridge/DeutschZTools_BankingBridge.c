class DeutschZTools_BankingBridge
{
    static bool BridgeEnabled(out string message)
    {
        if (DeutschZTools_SettingsService.Get().EnableBankingBridge == 0)
        {
            message = "DeutschZ Banking bridge is disabled in settings.";
            return false;
        }

        return true;
    }

    static bool GetStatus(out string message)
    {
        if (!BridgeEnabled(message))
            return false;

        #ifdef DEUTSCHZ_BANKING
        return DeutschZBankingAdminAPI.GetStatus(message);
        #else
        message = "DeutschZ_Banking is not loaded. Load @DeutschZ_Banking before/with @DeutschZ_Tools.";
        return false;
        #endif
    }

    static bool Reload(out string message)
    {
        if (!BridgeEnabled(message))
            return false;

        #ifdef DEUTSCHZ_BANKING
        return DeutschZBankingAdminAPI.ReloadAll(message);
        #else
        message = "DeutschZ_Banking is not loaded. Reload skipped.";
        return false;
        #endif
    }

    static bool Lookup(string steam64, array<string> rows, out string message)
    {
        if (!BridgeEnabled(message))
            return false;

        steam64.Trim();
        if (steam64 == "")
        {
            message = "Target Steam64 missing.";
            return false;
        }

        #ifdef DEUTSCHZ_BANKING
        return DeutschZBankingAdminAPI.BuildAccountRows(steam64, rows, message);
        #else
        if (rows)
        {
            rows.Clear();
            rows.Insert(steam64 + "|0|Not loaded|DeutschZ_Banking missing|0");
        }
        message = "DeutschZ_Banking is not loaded.";
        return false;
        #endif
    }

    static bool Audit(string steam64, array<string> rows, out string message)
    {
        if (!BridgeEnabled(message))
            return false;

        steam64.Trim();

        #ifdef DEUTSCHZ_BANKING
        return DeutschZBankingAdminAPI.BuildAuditRows(steam64, rows, 9, message);
        #else
        if (rows)
        {
            rows.Clear();
            rows.Insert(steam64 + "|0|Not loaded|DeutschZ_Banking missing|0");
        }
        message = "DeutschZ_Banking is not loaded.";
        return false;
        #endif
    }

    static bool AddMoney(string steam64, int amount, out string message)
    {
        if (!BridgeEnabled(message))
            return false;

        steam64.Trim();
        if (steam64 == "")
        {
            message = "Target Steam64 missing.";
            return false;
        }

        #ifdef DEUTSCHZ_BANKING
        return DeutschZBankingAdminAPI.AddMoneyBySteamID(steam64, amount, message);
        #else
        message = "DeutschZ_Banking is not loaded. Money action skipped.";
        return false;
        #endif
    }

    static bool RemoveMoney(string steam64, int amount, out string message)
    {
        if (!BridgeEnabled(message))
            return false;

        steam64.Trim();
        if (steam64 == "")
        {
            message = "Target Steam64 missing.";
            return false;
        }

        #ifdef DEUTSCHZ_BANKING
        return DeutschZBankingAdminAPI.RemoveMoneyBySteamID(steam64, amount, message);
        #else
        message = "DeutschZ_Banking is not loaded. Money action skipped.";
        return false;
        #endif
    }
}
