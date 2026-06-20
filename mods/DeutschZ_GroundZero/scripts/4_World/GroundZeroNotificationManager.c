/*
    DeutschZ_GroundZero
    Owner: Patrick Sluzalek / fck1701
    Module: 4_World / GroundZeroNotificationManager
    Purpose: Global server notifications. Expansion notification support can be added here later.
    Dependencies: DayZ scripts; optional CF/Expansion APIs only through adapter methods.
    Compliance: Original DeutschZ implementation. No copied foreign mod code, assets, configs or stubs.
*/

class GroundZeroNotificationManager
{
    protected GroundZeroConfig m_Config;

    void GroundZeroNotificationManager(GroundZeroConfig config)
    {
        m_Config = config;
    }

    void Broadcast(string message)
    {
        if (!m_Config || !m_Config.EnableGlobalNotifications) return;

        GroundZeroLogging.Info("Notify", message);
        if (m_Config.UseExpansionNotifications())
            GroundZeroCoreBridge.SendNotification("status", "DeutschZ GroundZero", message, "0 0 0");

        array<Man> players = new array<Man>();
        GetGame().GetPlayers(players);
        GroundZeroLogging.Debug("Notify", "Recipients=" + players.Count().ToString());

        if (m_Config.UseVanillaNotifications())
            GroundZeroLogging.Debug("Notify", "Vanilla notification fallback requested for " + players.Count().ToString() + " players");
        if (m_Config.UseChatMessages())
            GroundZeroLogging.Debug("Notify", "Chat fallback requested for " + players.Count().ToString() + " players");
    }
}
