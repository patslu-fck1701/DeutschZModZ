/*
    DeutschZ_GroundZero
    Owner: Patrick Sluzalek / fck1701
    Module: 4_World / GroundZeroNotificationManager
    Purpose: Global server notifications with visible vanilla chat fallback.
    Dependencies: DayZ scripts; optional CF/Expansion APIs only through DeutschZ Core/Bridge.
    Compliance: Original DeutschZ implementation. No copied foreign mod code, assets, configs or stubs.
*/

class GroundZeroNotificationManager
{
    protected GroundZeroConfig m_Config;

    void GroundZeroNotificationManager(GroundZeroConfig config)
    {
        m_Config = config;
    }

    protected void SendChatFallback(string message)
    {
        if (!GetGame() || !GetGame().IsServer())
            return;

        array<Man> players = new array<Man>();
        GetGame().GetPlayers(players);

        foreach (Man man : players)
        {
            PlayerBase player = PlayerBase.Cast(man);
            if (!player || !player.GetIdentity())
                continue;

            Param1<string> data = new Param1<string>("[DeutschZ GroundZero] " + message);
            GetGame().RPCSingleParam(player, ERPCs.RPC_USER_ACTION_MESSAGE, data, true, player.GetIdentity());
        }

        GroundZeroLogging.Debug("Notify", "Chat fallback sent to " + players.Count().ToString() + " players");
    }

    void Broadcast(string message)
    {
        if (!m_Config || !m_Config.EnableGlobalNotifications)
            return;

        GroundZeroLogging.Info("Notify", message);

        bool bridgeSent = false;
        if (m_Config.UseExpansionNotifications())
            bridgeSent = GroundZeroCoreBridge.SendNotification("status", "DeutschZ GroundZero", message, "0 0 0");

        if (!bridgeSent && (m_Config.UseVanillaNotifications() || m_Config.UseChatMessages()))
            SendChatFallback(message);
    }
}
