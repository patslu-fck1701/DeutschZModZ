/*
    DeutschZ ModZ
    Autor/Eigentuemer: Patrick Sluzalek / fck1701
    Projekt: DeutschZ
    Zweck: Eigene DeutschZ-Implementierung fuer Core, ExpansionBridge und Event-Module.
    Quellen-/Konzeptnachweis: Eigenentwickelte Struktur; DayZ, CF und Expansion nur als Laufzeit-API/Abhaengigkeit.
    No-Copy-Bestaetigung: Kein Code, keine Assets und keine Configs aus fremden Mods kopiert.
*/

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
