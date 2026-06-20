/*
    DeutschZ ModZ
    Autor/Eigentuemer: Patrick Sluzalek / fck1701
    Projekt: DeutschZ
    Zweck: Eigene DeutschZ-Implementierung fuer Core, ExpansionBridge und Event-Module.
    Quellen-/Konzeptnachweis: Eigenentwickelte Struktur; DayZ, CF und Expansion nur als Laufzeit-API/Abhaengigkeit.
    No-Copy-Bestaetigung: Kein Code, keine Assets und keine Configs aus fremden Mods kopiert.
*/

class DeutschZCore_ServiceLocator
{
    protected static ref DeutschZCore_MarkerProviderAPI s_MarkerProvider;
    protected static ref DeutschZCore_NotificationProviderAPI s_NotificationProvider;
    protected static ref DeutschZCore_AIProviderAPI s_AIProvider;
    protected static ref DeutschZCore_RateLimiter s_RateLimiter;

    static void RegisterMarkerProvider(DeutschZCore_MarkerProviderAPI provider)
    {
        s_MarkerProvider = provider;
        DeutschZCore_Log.Info("Core", "Marker provider registered");
    }

    static DeutschZCore_MarkerProviderAPI GetMarkerProvider()
    {
        return s_MarkerProvider;
    }

    static void RegisterNotificationProvider(DeutschZCore_NotificationProviderAPI provider)
    {
        s_NotificationProvider = provider;
        DeutschZCore_Log.Info("Core", "Notification provider registered");
    }

    static DeutschZCore_NotificationProviderAPI GetNotificationProvider()
    {
        return s_NotificationProvider;
    }

    static void RegisterAIProvider(DeutschZCore_AIProviderAPI provider)
    {
        s_AIProvider = provider;
        DeutschZCore_Log.Info("Core", "AI provider registered");
    }

    static DeutschZCore_AIProviderAPI GetAIProvider()
    {
        return s_AIProvider;
    }

    static DeutschZCore_RateLimiter GetRateLimiter()
    {
        if (!s_RateLimiter)
            s_RateLimiter = new DeutschZCore_RateLimiter;
        return s_RateLimiter;
    }
}
