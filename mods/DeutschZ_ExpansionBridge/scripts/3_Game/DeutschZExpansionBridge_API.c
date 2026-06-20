/*
    DeutschZ ModZ - DeutschZ_ExpansionBridge
    Autor/Eigentuemer: Patrick Sluzalek / fck1701
    Zweck: Eigene Adapterklasse fuer Expansion API.
    Quellen-/Konzeptnachweis: Eigenentwickelte DeutschZ-Struktur, DayZ/CF/Expansion nur als API-Abhaengigkeit vorgesehen.
    No-Copy-Bestaetigung: Kein Code, keine Assets und keine Configs aus fremden Mods kopiert.
*/
class DeutschZExpansionBridge_MarkerProvider: DeutschZCore_MarkerProviderAPI
{
    override bool CreateMarker(string id, string label, vector position, int colorARGB)
    {
        Print("[DeutschZ_ExpansionBridge] CreateMarker placeholder: " + id);
        return false;
    }
}

class DeutschZExpansionBridge_AIProvider: DeutschZCore_AIProviderAPI
{
    override bool SpawnGuard(string eventId, string loadoutId, vector position)
    {
        Print("[DeutschZ_ExpansionBridge] SpawnGuard placeholder: " + eventId);
        return false;
    }
}
