/*
    DeutschZ ModZ - DeutschZ_Core
    Autor/Eigentuemer: Patrick Sluzalek / fck1701
    Zweck: Provider-APIs fuer gekapselte externe Systeme.
    Quellen-/Konzeptnachweis: Eigenentwickelte DeutschZ-Struktur, DayZ/CF/Expansion nur als API-Abhaengigkeit vorgesehen.
    No-Copy-Bestaetigung: Kein Code, keine Assets und keine Configs aus fremden Mods kopiert.
*/
class DeutschZCore_MarkerProviderAPI
{
    bool CreateMarker(string id, string label, vector position, int colorARGB) { return false; }
    bool UpdateMarker(string id, vector position) { return false; }
    bool DeleteMarker(string id) { return false; }
}

class DeutschZCore_AIProviderAPI
{
    bool SpawnGuard(string eventId, string loadoutId, vector position) { return false; }
    bool CleanupEventAI(string eventId) { return false; }
}
