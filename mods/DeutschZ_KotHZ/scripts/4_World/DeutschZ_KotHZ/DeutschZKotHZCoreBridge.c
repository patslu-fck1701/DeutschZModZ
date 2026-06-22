/*
    DeutschZ ModZ
    Autor/Eigentuemer: Patrick Sluzalek / fck1701
    Projekt: DeutschZ
    Zweck: Eigene DeutschZ-Implementierung fuer Core, ExpansionBridge und Event-Module.
    Quellen-/Konzeptnachweis: Eigenentwickelte Struktur; DayZ, CF und Expansion nur als Laufzeit-API/Abhaengigkeit.
    No-Copy-Bestaetigung: Kein Code, keine Assets und keine Configs aus fremden Mods kopiert.
*/

class DeutschZKotHZCoreBridge
{
    static string SystemName()
    {
        return "KotHZ";
    }

    static string ConfigPath()
    {
        return DeutschZCore_ServerProfile.ConfigPath(SystemName());
    }

    static string StatePath()
    {
        return DeutschZCore_ServerProfile.StatePath(SystemName());
    }

    static bool CreateEventMarker(string id, string label, vector position)
    {
        DeutschZCore_MarkerProviderAPI provider = DeutschZCore_ServiceLocator.GetMarkerProvider();
        if (!provider)
            return false;
        return provider.CreateMarker("KotHZ_" + id, label, position, 0xFFFF0000);
    }


    static bool CreateEvent3DMarker(string id, string label, vector position)
    {
        DeutschZCore_MarkerProviderAPI provider = DeutschZCore_ServiceLocator.GetMarkerProvider();
        if (!provider)
            return false;
        // FIX35: Use the same server marker id as the map marker. Expansion server markers can be map+3D,
        // separate ids caused duplicate visible markers.
        return provider.Create3DMarker("KotHZ_" + id, label, position, 0xFFFF0000);
    }

    static bool DeleteEvent3DMarker(string id)
    {
        DeutschZCore_MarkerProviderAPI provider = DeutschZCore_ServiceLocator.GetMarkerProvider();
        if (!provider)
            return false;
        return provider.DeleteMarker("KotHZ_" + id);
    }

    static bool DeleteRawMarker(string markerId)
    {
        DeutschZCore_MarkerProviderAPI provider = DeutschZCore_ServiceLocator.GetMarkerProvider();
        if (!provider || markerId == "")
            return false;
        return provider.DeleteMarker(markerId);
    }

    static void CleanupMarkers()
    {
        DeutschZCore_MarkerProviderAPI provider = DeutschZCore_ServiceLocator.GetMarkerProvider();
        if (provider)
            provider.DeleteMarkersByPrefix("KotHZ_");
    }

    static bool DeleteEventMarker(string id)
    {
        DeutschZCore_MarkerProviderAPI provider = DeutschZCore_ServiceLocator.GetMarkerProvider();
        if (!provider)
            return false;
        return provider.DeleteMarker("KotHZ_" + id);
    }

    static bool SpawnInfected(string eventId, string className, vector position)
    {
        DeutschZCore_AIProviderAPI provider = DeutschZCore_ServiceLocator.GetAIProvider();
        if (!provider)
            return false;
        return provider.SpawnInfected("KotHZ_" + eventId, className, position);
    }

    static void CleanupAI(string eventId)
    {
        DeutschZCore_AIProviderAPI provider = DeutschZCore_ServiceLocator.GetAIProvider();
        if (provider)
            provider.CleanupEventAI("KotHZ_" + eventId);
    }
}
