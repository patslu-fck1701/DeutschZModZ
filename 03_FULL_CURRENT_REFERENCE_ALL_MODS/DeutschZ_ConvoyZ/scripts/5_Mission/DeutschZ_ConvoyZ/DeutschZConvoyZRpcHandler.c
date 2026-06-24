/*
DeutschZ ModZ
Eigenstaendige Implementierung fuer DeutschZ.
Autor/Eigentuemer: Patrick Sluzalek / fck1701.
Projekt: DeutschZ.
Modul: DeutschZ_ConvoyZ.
Zweck der Datei: Eigene DeutschZ-Datei fuer ConvoyZ.
Quellen-/Konzeptnachweis: Eigene DeutschZ-Implementierung; DayZ/CF/Expansion werden nur als Laufzeit-Abhaengigkeit/API genutzt.
Keine direkte Codeuebernahme aus Drittquellen.
*/

class DeutschZConvoyZRpcHandler
{
    void DeutschZConvoyZRpcHandler()
    {
    }

    void Init()
    {
        // Compatibility-safe placeholder.
        // This build does not override MissionServer.OnRPC because this server script set
        // does not expose OnRPC in the Mission base class.
        // Hack start/stop is handled directly server-side by ActionHackBlackbox.
    }
}
