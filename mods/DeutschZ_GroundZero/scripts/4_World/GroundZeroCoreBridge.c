/*
    DeutschZ ModZ
    Autor/Eigentuemer: Patrick Sluzalek / fck1701
    Projekt: DeutschZ
    Zweck: Eigene DeutschZ-Implementierung fuer Core, ExpansionBridge und Event-Module.
    Quellen-/Konzeptnachweis: Eigenentwickelte Struktur; DayZ, CF und Expansion nur als Laufzeit-API/Abhaengigkeit.
    No-Copy-Bestaetigung: Kein Code, keine Assets und keine Configs aus fremden Mods kopiert.
*/

class GroundZeroCoreBridge
{
    static string SystemName()
    {
        return "GroundZero";
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
        return provider.CreateMarker("GroundZero_" + id, label, position, 0xFFFF0000);
    }


    static bool CreateEvent3DMarker(string id, string label, vector position)
    {
        DeutschZCore_MarkerProviderAPI provider = DeutschZCore_ServiceLocator.GetMarkerProvider();
        if (!provider)
            return false;
        return provider.CreateMarker("GroundZero_3D_" + id, label, position, 0xFFFF0000);
    }

    static bool SendNotification(string channel, string title, string message, vector position)
    {
        DeutschZCore_NotificationProviderAPI provider = DeutschZCore_ServiceLocator.GetNotificationProvider();
        if (!provider)
            return false;
        return provider.SendEventNotification(SystemName(), channel, title, message, position);
    }

    static void CleanupMarkers()
    {
        DeutschZCore_MarkerProviderAPI provider = DeutschZCore_ServiceLocator.GetMarkerProvider();
        if (provider)
            provider.DeleteMarkersByPrefix("GroundZero_");
    }

    static bool DeleteEventMarker(string id)
    {
        DeutschZCore_MarkerProviderAPI provider = DeutschZCore_ServiceLocator.GetMarkerProvider();
        if (!provider)
            return false;
        bool removed = provider.DeleteMarker("GroundZero_" + id);
        removed = provider.DeleteMarker("GroundZero_3D_" + id) || removed;
        return removed;
    }

    static bool SpawnInfected(string eventId, string className, vector position)
    {
        DeutschZCore_AIProviderAPI provider = DeutschZCore_ServiceLocator.GetAIProvider();
        if (!provider)
            return false;
        return provider.SpawnInfected("GroundZero_" + eventId, className, position);
    }

    static void CleanupAI(string eventId)
    {
        DeutschZCore_AIProviderAPI provider = DeutschZCore_ServiceLocator.GetAIProvider();
        if (provider)
            provider.CleanupEventAI("GroundZero_" + eventId);
    }
}
