/*
    DeutschZ ModZ
    Autor/Eigentuemer: Patrick Sluzalek / fck1701
    Projekt: DeutschZ
    Zweck: Register DeutschZ ExpansionBridge providers and visible notification fallback.
    No-Copy-Bestaetigung: Kein Code, keine Assets und keine Configs aus fremden Mods kopiert.
*/

class DeutschZExpansionBridge_NotificationProvider: DeutschZCore_NotificationProviderAPI
{
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
    override void OnInit()
    {
        super.OnInit();
        DeutschZCore_ServiceLocator.RegisterMarkerProvider(new DeutschZExpansionBridge_MarkerProvider);
        DeutschZCore_ServiceLocator.RegisterNotificationProvider(new DeutschZExpansionBridge_NotificationProvider);
        DeutschZCore_ServiceLocator.RegisterAIProvider(new DeutschZExpansionBridge_AIProvider);
        DeutschZCore_Log.Info("ExpansionBridge", "providers registered");
    }
}
