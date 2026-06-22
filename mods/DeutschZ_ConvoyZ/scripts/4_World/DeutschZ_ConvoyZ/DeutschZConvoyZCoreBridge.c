/*
    DeutschZ ModZ
    Autor/Eigentuemer: Patrick Sluzalek / fck1701
    Projekt: DeutschZ
    Zweck: Eigene DeutschZ-Implementierung fuer Core, ExpansionBridge und Event-Module.
    Quellen-/Konzeptnachweis: Eigenentwickelte Struktur; DayZ, CF und Expansion nur als Laufzeit-API/Abhaengigkeit.
    No-Copy-Bestaetigung: Kein Code, keine Assets und keine Configs aus fremden Mods kopiert.
*/

class DeutschZConvoyZCoreBridge
{
    static string SystemName()
    {
        return "ConvoyZ";
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
        return provider.CreateMarker("ConvoyZ_" + id, label, position, 0xFFFF0000);
    }

    static bool CreateEvent3DMarker(string id, string label, vector position)
    {
        DeutschZCore_MarkerProviderAPI provider = DeutschZCore_ServiceLocator.GetMarkerProvider();
        if (!provider)
            return false;
        // FIX36: use the same marker id and let ExpansionBridge create a 3D server marker.
        return provider.Create3DMarker("ConvoyZ_" + id, label, position, 0xFFFF0000);
    }

    static void CleanupMarkers()
    {
        DeutschZCore_MarkerProviderAPI provider = DeutschZCore_ServiceLocator.GetMarkerProvider();
        if (provider)
            provider.DeleteMarkersByPrefix("ConvoyZ_");
    }

    static bool DeleteEventMarker(string id)
    {
        DeutschZCore_MarkerProviderAPI provider = DeutschZCore_ServiceLocator.GetMarkerProvider();
        if (!provider)
            return false;
        return provider.DeleteMarker("ConvoyZ_" + id);
    }

    static bool SpawnLocalEnemy(string eventId, string className, vector position)
    {
        DeutschZCore_AIProviderAPI provider = DeutschZCore_ServiceLocator.GetAIProvider();
        if (!provider)
            return false;
        return provider.SpawnInfected("ConvoyZ_" + eventId, className, position);
    }

    static void CleanupAI(string eventId)
    {
        DeutschZCore_AIProviderAPI provider = DeutschZCore_ServiceLocator.GetAIProvider();
        if (provider)
            provider.CleanupEventAI("ConvoyZ_" + eventId);
    }
}
