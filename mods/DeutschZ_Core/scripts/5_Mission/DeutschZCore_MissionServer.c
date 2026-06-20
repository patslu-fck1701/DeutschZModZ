/*
    DeutschZ ModZ - DeutschZ_Core
    Autor/Eigentuemer: Patrick Sluzalek / fck1701
    Zweck: MissionServer-Hook fuer Core-Initialisierung.
    Quellen-/Konzeptnachweis: Eigenentwickelte DeutschZ-Struktur, DayZ/CF/Expansion nur als API-Abhaengigkeit vorgesehen.
    No-Copy-Bestaetigung: Kein Code, keine Assets und keine Configs aus fremden Mods kopiert.
*/
modded class MissionServer
{
    override void OnInit()
    {
        super.OnInit();
        Print("[DeutschZ_Core] MissionServer initialized");
    }
}
