class DeutschZTools_TraderZBridge
{
    static bool BridgeEnabled(out string message)
    {
        if (DeutschZTools_SettingsService.Get().EnableTraderZBridge == 0)
        {
            message = "DeutschZ TraderZ bridge is disabled in settings.";
            return false;
        }

        return true;
    }

    static bool GetStatus(out string message)
    {
        if (!BridgeEnabled(message))
            return false;

        #ifdef DEUTSCHZ_TRADERZ
        return DeutschZTraderZAdminAPI.GetStatus(message);
        #else
        message = "DeutschZ_TraderZ is not loaded. Load @DeutschZ_TraderZ before @DeutschZ_Tools.";
        return false;
        #endif
    }

    static bool ReloadAll(out string message)
    {
        if (!BridgeEnabled(message))
            return false;

        #ifdef DEUTSCHZ_TRADERZ
        return DeutschZTraderZAdminAPI.ReloadAll(message);
        #else
        message = "DeutschZ_TraderZ is not loaded. Reload skipped.";
        return false;
        #endif
    }

    static bool ReloadSettings(out string message)
    {
        if (!BridgeEnabled(message))
            return false;

        #ifdef DEUTSCHZ_TRADERZ
        return DeutschZTraderZAdminAPI.ReloadSettings(message);
        #else
        message = "DeutschZ_TraderZ is not loaded. Settings reload skipped.";
        return false;
        #endif
    }

    static bool ReloadTraders(out string message)
    {
        if (!BridgeEnabled(message))
            return false;

        #ifdef DEUTSCHZ_TRADERZ
        return DeutschZTraderZAdminAPI.ReloadTraders(message);
        #else
        message = "DeutschZ_TraderZ is not loaded. Trader reload skipped.";
        return false;
        #endif
    }

    static bool ReloadMarket(out string message)
    {
        if (!BridgeEnabled(message))
            return false;

        #ifdef DEUTSCHZ_TRADERZ
        return DeutschZTraderZAdminAPI.ReloadMarket(message);
        #else
        message = "DeutschZ_TraderZ is not loaded. Market reload skipped.";
        return false;
        #endif
    }

    static bool ReloadCurrency(out string message)
    {
        if (!BridgeEnabled(message))
            return false;

        #ifdef DEUTSCHZ_TRADERZ
        return DeutschZTraderZAdminAPI.ReloadCurrency(message);
        #else
        message = "DeutschZ_TraderZ is not loaded. Currency reload skipped.";
        return false;
        #endif
    }

    static bool ReloadSafezones(out string message)
    {
        if (!BridgeEnabled(message))
            return false;

        #ifdef DEUTSCHZ_TRADERZ
        return DeutschZTraderZAdminAPI.ReloadSafezones(message);
        #else
        message = "DeutschZ_TraderZ is not loaded. Safezone reload skipped.";
        return false;
        #endif
    }

    static bool BuildTraderRows(array<string> rows, out string message)
    {
        if (!BridgeEnabled(message))
            return false;

        #ifdef DEUTSCHZ_TRADERZ
        return DeutschZTraderZAdminAPI.BuildTraderRows(rows, message);
        #else
        if (rows)
        {
            rows.Clear();
            rows.Insert("DeutschZ_TraderZ missing|Not loaded|0|No bridge");
        }
        message = "DeutschZ_TraderZ is not loaded.";
        return false;
        #endif
    }

    static bool BuildCategoryRows(array<string> rows, out string message)
    {
        if (!BridgeEnabled(message))
            return false;

        #ifdef DEUTSCHZ_TRADERZ
        return DeutschZTraderZAdminAPI.BuildCategoryRows(rows, message);
        #else
        if (rows)
        {
            rows.Clear();
            rows.Insert("Not loaded|0|0|DeutschZ_TraderZ missing");
        }
        message = "DeutschZ_TraderZ is not loaded.";
        return false;
        #endif
    }

    static bool BuildMarketRows(string category, array<string> rows, out string message)
    {
        if (!BridgeEnabled(message))
            return false;

        category.Trim();
        if (category == "")
            category = "Food";

        #ifdef DEUTSCHZ_TRADERZ
        return DeutschZTraderZAdminAPI.BuildMarketRows(category, rows, message);
        #else
        if (rows)
        {
            rows.Clear();
            rows.Insert(category + "|DeutschZ_TraderZ missing|0|0|No bridge");
        }
        message = "DeutschZ_TraderZ is not loaded.";
        return false;
        #endif
    }
}
