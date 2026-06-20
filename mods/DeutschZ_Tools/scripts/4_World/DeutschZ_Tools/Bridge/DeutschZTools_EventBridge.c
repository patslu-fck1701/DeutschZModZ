class DeutschZTools_EventBridge
{
    protected static bool DispatchKOTHCommand(PlayerIdentity admin, string command, out string message)
    {
        if (!GetGame() || !GetGame().IsServer())
        {
            message = "KOTH bridge can only run on server.";
            return false;
        }

        if (!admin)
        {
            message = "KOTH bridge rejected: missing admin identity.";
            return false;
        }

        Mission mission = GetGame().GetMission();
        if (!mission)
        {
            message = "KOTH bridge rejected: mission not available.";
            return false;
        }

        string adminName = admin.GetName();
        if (adminName == "")
            adminName = admin.GetPlainId();

        ChatMessageEventParams chatParams = new ChatMessageEventParams(CCAdmin, adminName, command, "");
        mission.OnEvent(ChatMessageEventTypeID, chatParams);

        message = "KOTH command sent to EventCore: " + command;
        return true;
    }

    static bool KOTHStatus(PlayerIdentity admin, out string message)
    {
        return DeutschZTools_KOTHBridge.KOTHStatus(admin, message);
    }

    static bool ForceStartKOTH(PlayerIdentity admin, out string message)
    {
        return DeutschZTools_KOTHBridge.ForceStartKOTH(admin, message);
    }

    static bool ForceStopKOTH(PlayerIdentity admin, out string message)
    {
        return DeutschZTools_KOTHBridge.ForceStopKOTH(admin, message);
    }

    static bool ReloadKOTHConfigs(PlayerIdentity admin, out string message)
    {
        return DeutschZTools_KOTHBridge.ReloadKOTHConfigs(admin, message);
    }

    static bool SaveKOTHSettings(PlayerIdentity admin, out string message)
    {
        return DeutschZTools_KOTHBridge.SaveKOTHSettings(admin, message);
    }

    static bool ReloadKOTHSettings(PlayerIdentity admin, out string message)
    {
        return DeutschZTools_KOTHBridge.ReloadKOTHSettings(admin, message);
    }

    static bool ReloadKOTHZones(PlayerIdentity admin, out string message)
    {
        return DeutschZTools_KOTHBridge.ReloadKOTHZones(admin, message);
    }

    static bool ReloadKOTHLoot(PlayerIdentity admin, out string message)
    {
        return DeutschZTools_KOTHBridge.ReloadKOTHLoot(admin, message);
    }

    static bool ReloadKOTHAll(PlayerIdentity admin, out string message)
    {
        return DeutschZTools_KOTHBridge.ReloadKOTHAll(admin, message);
    }
}
