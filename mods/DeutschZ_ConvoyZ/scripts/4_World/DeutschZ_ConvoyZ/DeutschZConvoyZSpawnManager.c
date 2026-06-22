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

class DeutschZConvoyZSpawnManager
{
    Object SpawnObject(string className, vector pos, vector ori, string eventId, string label)
    {
        if (!GetGame() || !GetGame().IsServer()) return null;
        if (!DeutschZConvoyZValidator.IsClassNameUsable(className)) return null;
        vector p = pos;
        p[1] = GetGame().SurfaceY(p[0], p[2]);
        Object obj = GetGame().CreateObjectEx(className, p, ECE_PLACE_ON_SURFACE | ECE_NOLIFETIME);
        if (!obj)
        {
            DeutschZConvoyZLogger.Log("SpawnFailed", eventId, "SPAWNING", "", p, "FAILED", label + " " + className);
            return null;
        }
        obj.SetOrientation(ori);
        DeutschZConvoyZLogger.Log("SpawnSuccess", eventId, "SPAWNING", "", p, "OK", label + " " + className);
        return obj;
    }

    bool SpawnCrashSite(DeutschZConvoyZConfig cfg, DeutschZConvoyZRuntimeState state)
    {
        if (!cfg || !cfg.EventData || !state) return false;
        if (cfg.EventData.Vehicles && cfg.EventData.Vehicles.Count() > 0)
        {
            DeutschZConvoyZLogger.Log("DeprecatedVehiclesIgnored", state.EventId, "SPAWNING", "", cfg.EventData.EventCenter, "OK", "static only: Vehicles entries are ignored");
        }
        foreach (DeutschZConvoyZObjectDef def: cfg.EventData.CrashObjects)
        {
            if (!def) continue;
            Object obj = SpawnObject(def.ClassName, def.Position, def.Orientation, state.EventId, "crash_object");
            if (!obj && def.Critical == 1) return false;
            if (obj) state.SpawnedObjects.Insert(obj);
        }
        Object blackbox = SpawnObject(cfg.EventData.Blackbox.ClassName, cfg.EventData.Blackbox.Position, cfg.EventData.Blackbox.Orientation, state.EventId, "blackbox");
        if (!blackbox && cfg.EventData.Blackbox.Critical == 1) return false;
        state.BlackboxEntity = blackbox;
        if (blackbox) state.SpawnedObjects.Insert(blackbox);
        return true;
    }

    void SetSmoke(DeutschZConvoyZConfig cfg, DeutschZConvoyZRuntimeState state, string smokeState)
    {
        // FIX31: disabled physical smoke grenade spawning during crash isolation.
        // ConvoyZ visibility must come from real Expansion markers through DeutschZ_ExpansionBridge.
        if (state)
            state.SmokeState = smokeState;
    }


    void RefreshSmoke(DeutschZConvoyZConfig cfg, DeutschZConvoyZRuntimeState state)
    {
        // FIX33: compatibility no-op.
        // Physical smoke refresh remains disabled during crash isolation.
        // Visibility is handled by DeutschZ_ExpansionBridge real Expansion markers.
        if (!state)
            return;

        if (state.SmokeState == "")
            state.SmokeState = DeutschZConvoyZConstants.SMOKE_RED;
    }

    string GetSmokeClass(DeutschZConvoyZSmokeDef smoke, string smokeState)
    {
        if (smokeState == DeutschZConvoyZConstants.SMOKE_YELLOW) return smoke.YellowSmokeClassName;
        if (smokeState == DeutschZConvoyZConstants.SMOKE_GREEN) return smoke.GreenSmokeClassName;
        if (smokeState == DeutschZConvoyZConstants.SMOKE_WHITE) return smoke.WhiteSmokeClassName;
        return smoke.RedSmokeClassName;
    }

    void CleanupSmoke(DeutschZConvoyZRuntimeState state)
    {
        if (!state || !state.SmokeObjects) return;
        for (int i = state.SmokeObjects.Count() - 1; i >= 0; i--)
        {
            Object obj = state.SmokeObjects.Get(i);
            if (obj) GetGame().ObjectDelete(obj);
            state.SmokeObjects.Remove(i);
        }
    }
}
