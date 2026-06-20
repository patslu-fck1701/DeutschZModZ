/*
    DeutschZ ModZ - DeutschZ_Core
    Autor/Eigentuemer: Patrick Sluzalek / fck1701
    Zweck: Serverseitige Profilepfade.
    Quellen-/Konzeptnachweis: Eigenentwickelte DeutschZ-Struktur, DayZ/CF/Expansion nur als API-Abhaengigkeit vorgesehen.
    No-Copy-Bestaetigung: Kein Code, keine Assets und keine Configs aus fremden Mods kopiert.
*/
class DeutschZCore_ServerProfile
{
    static string SystemPath(string systemName)
    {
        return DeutschZCore_Constants.ROOT_PROFILE + systemName + "/";
    }
}
