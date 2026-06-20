class DeutschZTools_GarageBridge
{
    static bool BridgeEnabled(out string message)
    {
        if (DeutschZTools_SettingsService.Get().EnableGarageBridge == 0)
        {
            message = "DeutschZ Garage bridge is disabled in settings.";
            return false;
        }

        return true;
    }

    static bool GetStatus(out string message)
    {
        if (!BridgeEnabled(message))
            return false;

        #ifdef DEUTSCHZ_GARAGE
        return DeutschZGarageAdminAPI.GetStatus(message);
        #else
        message = "DeutschZ_Garage is not loaded. Load @DeutschZ_Garage before/with @DeutschZ_Tools.";
        return false;
        #endif
    }

    static bool Reload(out string message)
    {
        if (!BridgeEnabled(message))
            return false;

        #ifdef DEUTSCHZ_GARAGE
        return DeutschZGarageAdminAPI.ReloadAll(message);
        #else
        message = "DeutschZ_Garage is not loaded. Reload skipped.";
        return false;
        #endif
    }

    static bool BuildVehicleRows(string steam64, array<string> rows, out string message)
    {
        if (!BridgeEnabled(message))
            return false;

        steam64.Trim();
        if (steam64 == "")
        {
            message = "Target Steam64 missing.";
            return false;
        }

        #ifdef DEUTSCHZ_GARAGE
        return DeutschZGarageAdminAPI.BuildVehicleRows(steam64, rows, 10, message);
        #else
        if (rows)
        {
            rows.Clear();
            rows.Insert("DeutschZ_Garage missing|Not loaded|" + steam64 + "|0 0 0");
        }
        message = "DeutschZ_Garage is not loaded.";
        return false;
        #endif
    }

    static bool ImpoundNearest(PlayerBase adminPlayer, string steam64, out string message)
    {
        if (!BridgeEnabled(message))
            return false;

        steam64.Trim();
        if (steam64 == "")
        {
            message = "Target Steam64 missing.";
            return false;
        }

        #ifdef DEUTSCHZ_GARAGE
        return DeutschZGarageAdminAPI.AdminImpoundNearest(adminPlayer, steam64, DeutschZTools_SettingsService.Get().VehicleActionRadius, message);
        #else
        message = "DeutschZ_Garage is not loaded. Impound skipped.";
        return false;
        #endif
    }
}
