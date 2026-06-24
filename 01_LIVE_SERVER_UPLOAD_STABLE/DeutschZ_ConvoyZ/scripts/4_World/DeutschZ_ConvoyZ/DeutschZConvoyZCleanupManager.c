/*
DeutschZ ModZ
Eigenstaendige Implementierung fuer DeutschZ.
Autor/Eigentuemer: Patrick Sluzalek / fck1701.
Projekt: DeutschZ.
Modul: DeutschZ_ConvoyZ.
Zweck der Datei: Serverseitige ConvoyZ-Eventlogik, Ablauf, Status und Sicherheitspruefung.
Quellen-/Konzeptnachweis: Eigene DeutschZ-Implementierung; DayZ/CF/Expansion werden nur als Laufzeit-Abhaengigkeit/API genutzt.
Keine direkte Codeuebernahme aus Drittquellen.
*/

class DeutschZConvoyZCleanupManager
{
    DeutschZConvoyZManager Manager;

    void DeutschZConvoyZCleanupManager(DeutschZConvoyZManager manager)
    {
        Manager = manager;
    }

    void Cleanup(string reason)
    {
        if (!Manager || !Manager.State) return;
        DeutschZConvoyZRuntimeState state = Manager.State;
        if (state.CleanupPending == 1 && state.CurrentState == DeutschZConvoyZConstants.STATE_CLEANUP) return;
        state.CleanupPending = 1;
        state.CurrentState = DeutschZConvoyZConstants.STATE_CLEANUP;
        DeutschZConvoyZLogger.Log("CleanupStarted", state.EventId, "CLEANUP", "", "0 0 0", "OK", reason);
        if (Manager.Hack) Manager.Hack.StopTimer();
        GetGame().GetCallQueue(CALL_CATEGORY_SYSTEM).Remove(Manager.Tick);
        GetGame().GetCallQueue(CALL_CATEGORY_SYSTEM).Remove(Manager.DelayedCleanup);
        DeleteArray(state.SpawnedAI);
        DeleteArray(state.SpawnedObjects);
        DeleteArray(state.SpawnedRewards);
        DeleteArray(state.SmokeObjects);
        DeutschZConvoyZ_RemoveEventMarker(state.EventId);
        DeutschZConvoyZ_RemoveEventMarker(state.EventId + "_carrier");
        DeutschZConvoyZ_RemoveEventMarker(state.EventId + "_delivery");
        DeutschZConvoyZ_AIProviderCleanupForEvent(state.EventId, reason);
        
        string eid = state.EventId;
        Manager.State = null;
        DeutschZConvoyZLogger.Log("CleanupFinished", eid, "CLEANUP", "", "0 0 0", "OK", reason);
        Manager.OnEventCleanupFinished(eid, reason);
    }

    void DeleteArray(array<Object> objects)
    {
        if (!objects) return;
        for (int i = objects.Count() - 1; i >= 0; i--)
        {
            Object obj = objects.Get(i);
            if (obj) GetGame().ObjectDelete(obj);
            objects.Remove(i);
        }
    }
}
