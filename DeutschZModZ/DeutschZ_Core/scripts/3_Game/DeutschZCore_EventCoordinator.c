/*
    DeutschZ ModZ
    Autor/Eigentuemer: Patrick Sluzalek / fck1701
    Projekt: DeutschZ
    Zweck: Globaler Core-Event-Lock fuer DeutschZ Eventmodule.
    No-Copy-Bestaetigung: Eigene DeutschZ-Implementierung.

    FIX45:
    - KotHZ und ConvoyZ duerfen nicht gleichzeitig starten.
    - Eventmodule bleiben voneinander unabhaengig und koppeln nur gegen DeutschZ_Core.
    - ExpansionBridge bleibt optionaler Provider, nicht Teil dieses Locks.
*/

class DeutschZCore_EventCoordinator
{
    protected static string s_ActiveSystem;
    protected static string s_ActiveEventId;
    protected static int s_ReservedAtMs;
    protected static int s_LastReleaseAtMs;

    protected static int MinGapAfterReleaseMs()
    {
        return 120000;
    }

    protected static int NowMs()
    {
        if (!GetGame())
            return 0;
        return GetGame().GetTime();
    }

    static string GetActiveSystem()
    {
        return s_ActiveSystem;
    }

    static string GetActiveEventId()
    {
        return s_ActiveEventId;
    }

    static bool IsBusy()
    {
        return s_ActiveSystem != "";
    }

    static bool CanReserve(string systemName, out string reason)
    {
        reason = "";

        if (systemName == "")
        {
            reason = "missing system name";
            return false;
        }

        if (s_ActiveSystem != "")
        {
            reason = "active system=" + s_ActiveSystem + " event=" + s_ActiveEventId;
            return false;
        }

        int now = NowMs();
        if (s_LastReleaseAtMs > 0 && now > s_LastReleaseAtMs)
        {
            int elapsed = now - s_LastReleaseAtMs;
            int minGapMs = MinGapAfterReleaseMs();
            if (elapsed < minGapMs)
            {
                int waitMs = minGapMs - elapsed;
                reason = "global event cooldown " + (waitMs / 1000).ToString() + "s";
                return false;
            }
        }

        return true;
    }

    static bool TryReserve(string systemName, string eventId, out string reason)
    {
        if (!CanReserve(systemName, reason))
            return false;

        s_ActiveSystem = systemName;
        s_ActiveEventId = eventId;
        s_ReservedAtMs = NowMs();

        Print("[DeutschZ_Core] EventCoordinator reserved system=" + s_ActiveSystem + " event=" + s_ActiveEventId);
        DeutschZCore_Log.Info("EventCoordinator", "reserved system=" + s_ActiveSystem + " event=" + s_ActiveEventId);
        return true;
    }

    static void UpdateEventId(string systemName, string eventId)
    {
        if (systemName == "" || eventId == "")
            return;

        if (s_ActiveSystem != systemName)
            return;

        s_ActiveEventId = eventId;
        DeutschZCore_Log.Info("EventCoordinator", "updated event id system=" + systemName + " event=" + eventId);
    }

    static bool Release(string systemName, string eventId, string reason)
    {
        if (s_ActiveSystem == "")
            return true;

        if (systemName == "" || s_ActiveSystem != systemName)
        {
            Print("[DeutschZ_Core] EventCoordinator release ignored. requester=" + systemName + " active=" + s_ActiveSystem + " event=" + s_ActiveEventId);
            return false;
        }

        string oldSystem = s_ActiveSystem;
        string oldEvent = s_ActiveEventId;

        s_ActiveSystem = "";
        s_ActiveEventId = "";
        s_ReservedAtMs = 0;
        s_LastReleaseAtMs = NowMs();

        Print("[DeutschZ_Core] EventCoordinator released system=" + oldSystem + " event=" + oldEvent + " reason=" + reason);
        DeutschZCore_Log.Info("EventCoordinator", "released system=" + oldSystem + " event=" + oldEvent + " reason=" + reason);
        return true;
    }
}
