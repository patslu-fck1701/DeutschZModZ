/*
    DeutschZ ModZ
    Autor/Eigentuemer: Patrick Sluzalek / fck1701
    Projekt: DeutschZ
    Zweck: Register DeutschZ ExpansionBridge providers and visible notification fallback.
    No-Copy-Bestaetigung: Kein Code, keine Assets und keine Configs aus fremden Mods kopiert.
*/

class DeutschZExpansionBridge_NotificationProvider: DeutschZCore_NotificationProviderAPI
{
    protected ref map<string, int> m_LastSentAt;

    void DeutschZExpansionBridge_NotificationProvider()
    {
        m_LastSentAt = new map<string, int>;
    }

    protected bool IsMutedChannel(string channel)
    {
        if (channel == "marker") return true;
        if (channel == "debug") return true;
        return false;
    }

    protected bool MaySend(string eventName, string channel)
    {
        if (IsMutedChannel(channel))
            return false;

        string key = eventName + "|" + channel;
        int now = GetGame().GetTime();
        int last = 0;
        if (m_LastSentAt && m_LastSentAt.Find(key, last))
        {
            // FIX25: hard notification throttle so fast test events do not flood Discord/chat/popup.
            if ((now - last) < 60000)
                return false;
        }
        m_LastSentAt.Set(key, now);
        return true;
    }

    protected void SendChatFallback(PlayerBase player, string text)
    {
        if (!player || !player.GetIdentity())
            return;

        Param1<string> data = new Param1<string>(text);
        GetGame().RPCSingleParam(player, ERPCs.RPC_USER_ACTION_MESSAGE, data, true, player.GetIdentity());
    }

    protected void SendPopupFallback(PlayerBase player, string title, string message)
    {
        if (!player)
            return;

        NotificationSystem.SendNotificationToPlayerExtended(player, 10.0, title, message, "set:dayz_gui image:icon_info");
    }

    override bool SendEventNotification(string eventName, string channel, string title, string message, vector position)
    {
        if (message == "")
            return false;

        if (!MaySend(eventName, channel))
        {
            DeutschZCore_Log.Info("ExpansionBridge", "notification throttled event=" + eventName + " channel=" + channel);
            return true;
        }

        string finalTitle = title;
        if (finalTitle == "")
            finalTitle = eventName;

        string text = "[" + eventName + "] " + message;
        array<Man> players = new array<Man>;
        GetGame().GetPlayers(players);

        foreach (Man man: players)
        {
            PlayerBase player = PlayerBase.Cast(man);
            if (!player || !player.GetIdentity())
                continue;

            SendChatFallback(player, text);
            SendPopupFallback(player, finalTitle, message);
        }

        DeutschZCore_Log.Info("ExpansionBridge", "notification sent event=" + eventName + " channel=" + channel + " players=" + players.Count().ToString() + " pos=" + position.ToString());
        return true;
    }
}

modded class MissionServer
{
    void MissionServer()
    {
        DeutschZExpansionBridge_RegisterProvidersSafe("MissionServer constructor");
    }

    protected void DeutschZExpansionBridge_RegisterProvidersSafe(string source)
    {
        if (!GetGame() || !GetGame().IsServer())
            return;

        DeutschZExpansionBridge_ConfigSafeBoot.Ensure();

        DeutschZExpansionBridge_MarkerProvider markerProvider = new DeutschZExpansionBridge_MarkerProvider();
        DeutschZExpansionBridge_NotificationProvider notificationProvider = new DeutschZExpansionBridge_NotificationProvider();
        DeutschZExpansionBridge_AIProvider aiProvider = new DeutschZExpansionBridge_AIProvider();

        DeutschZCore_ServiceLocator.RegisterMarkerProvider(markerProvider);
        DeutschZCore_ServiceLocator.RegisterNotificationProvider(notificationProvider);
        DeutschZCore_ServiceLocator.RegisterAIProvider(aiProvider);

        DeutschZCore_Log.Info("ExpansionBridge", "providers registered source=" + source);
        Print("[DeutschZ_ExpansionBridge] providers registered source=" + source);
    }

    override void OnInit()
    {
        super.OnInit();
        DeutschZExpansionBridge_RegisterProvidersSafe("MissionServer OnInit");
    }

    override void OnMissionStart()
    {
        super.OnMissionStart();
        DeutschZExpansionBridge_RegisterProvidersSafe("MissionServer OnMissionStart");
    }
}
