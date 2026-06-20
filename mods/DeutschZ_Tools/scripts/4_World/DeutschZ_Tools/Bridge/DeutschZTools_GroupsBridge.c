class DeutschZTools_GroupsBridge
{
    static bool BridgeEnabled(out string message)
    {
        if (DeutschZTools_SettingsService.Get().EnableGroupsBridge == 0)
        {
            message = "DeutschZ Groups bridge is disabled in settings.";
            return false;
        }

        return true;
    }

    static bool GetStatus(out string message)
    {
        if (!BridgeEnabled(message))
            return false;

        #ifdef DEUTSCHZ_GROUPS
        return DeutschZGroupsAdminAPI.GetStatus(message);
        #else
        message = "DeutschZ_Groups is not loaded. Load @DeutschZ_Groups before/with @DeutschZ_Tools.";
        return false;
        #endif
    }

    static bool Reload(out string message)
    {
        if (!BridgeEnabled(message))
            return false;

        #ifdef DEUTSCHZ_GROUPS
        return DeutschZGroupsAdminAPI.ReloadAll(message);
        #else
        message = "DeutschZ_Groups is not loaded. Reload skipped.";
        return false;
        #endif
    }

    static bool BuildGroupRows(array<string> rows, out string message)
    {
        if (!BridgeEnabled(message))
            return false;

        #ifdef DEUTSCHZ_GROUPS
        return DeutschZGroupsAdminAPI.BuildGroupRows(rows, 12, message);
        #else
        if (rows)
        {
            rows.Clear();
            rows.Insert("DeutschZ_Groups missing|Not loaded|0|0|No bridge");
        }
        message = "DeutschZ_Groups is not loaded.";
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

        #ifdef DEUTSCHZ_GROUPS
        return DeutschZGroupsAdminAPI.BuildPlayerGroupRows(steam64, rows, message);
        #else
        if (rows)
        {
            rows.Clear();
            rows.Insert(steam64 + "|Not loaded|0|0|DeutschZ_Groups missing");
        }
        message = "DeutschZ_Groups is not loaded.";
        return false;
        #endif
    }
}
