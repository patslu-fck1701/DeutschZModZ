class DeutschZTools_KOTHBridge
{
    static bool BridgeEnabled(out string message)
    {
        if (DeutschZTools_SettingsService.Get().EnableKOTHBridge == 0)
        {
            message = "DeutschZ KOTH bridge is disabled in settings.";
            return false;
        }

        return true;
    }

    protected static bool QueueCommand(PlayerIdentity admin, string command, out string message)
    {
        if (!BridgeEnabled(message))
            return false;

        #ifdef DEUTSCHZ_KOTH
        string adminName = "server";
        string adminSteam64 = "";
        if (admin)
        {
            adminName = admin.GetName();
            adminSteam64 = admin.GetPlainId();
        }
        bool queued = DeutschZKOTHAdminCommandBus.Enqueue(command, adminSteam64, adminName);
        message = DeutschZKOTHAdminCommandBus.GetLastResult();
        return queued;
        #else
        message = "DeutschZ_KOTH is not loaded. Load @DeutschZ_KOTH before/with @DeutschZ_Tools.";
        return false;
        #endif
    }

    static bool KOTHStatus(PlayerIdentity admin, out string message)
    {
        return QueueCommand(admin, "status", message);
    }

    static bool ForceStartKOTH(PlayerIdentity admin, out string message)
    {
        return QueueCommand(admin, "start", message);
    }

    static bool ForceStopKOTH(PlayerIdentity admin, out string message)
    {
        return QueueCommand(admin, "stop", message);
    }

    static bool ReloadKOTHConfigs(PlayerIdentity admin, out string message)
    {
        return QueueCommand(admin, "reload", message);
    }

    static bool SaveKOTHSettings(PlayerIdentity admin, out string message)
    {
        message = "KOTH settings save is prepared. Use reload after file edits.";
        return false;
    }

    static bool ReloadKOTHSettings(PlayerIdentity admin, out string message)
    {
        return QueueCommand(admin, "reload_settings", message);
    }

    static bool ReloadKOTHZones(PlayerIdentity admin, out string message)
    {
        return QueueCommand(admin, "reload_zones", message);
    }

    static bool ReloadKOTHLoot(PlayerIdentity admin, out string message)
    {
        return QueueCommand(admin, "reload_loot", message);
    }

    static bool ReloadKOTHAll(PlayerIdentity admin, out string message)
    {
        return QueueCommand(admin, "reload_all", message);
    }
}
