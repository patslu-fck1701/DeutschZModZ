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
        if (!state)
            return;

        state.SmokeState = smokeState;
        RefreshSmoke(cfg, state, true);
    }


    void RefreshSmoke(DeutschZConvoyZConfig cfg, DeutschZConvoyZRuntimeState state, bool force = false)
    {
        if (!cfg || !cfg.EventData || !cfg.EventData.Smoke || !state)
            return;

        if (cfg.EventData.Smoke.Enabled == 0)
        {
            CleanupSmoke(state);
            if (force)
                DeutschZConvoyZLogger.Log("SmokeDisabled", state.EventId, "SMOKE", state.SmokeState, cfg.EventData.EventCenter, "OK", "Physical smoke is disabled by FIX43 safe default");
            state.LastSmokeRefreshAt = GetGame().GetTime();
            return;
        }

        if (state.SmokeState == "")
            state.SmokeState = DeutschZConvoyZConstants.SMOKE_RED;

        int refreshSeconds = cfg.EventData.Smoke.RefreshSeconds;
        if (refreshSeconds < 45)
            refreshSeconds = 45;
        int nowMs = GetGame().GetTime();
        if (!force && state.LastSmokeRefreshAt > 0 && nowMs - state.LastSmokeRefreshAt < refreshSeconds * 1000)
            return;

        CleanupSmoke(state);

        string smokeClass = GetSmokeClass(cfg.EventData.Smoke, state.SmokeState);
        if (smokeClass == "")
            smokeClass = "M18SmokeGrenade_Red";

        int count = cfg.EventData.Smoke.Count;
        if (count < 1)
            count = 1;
        if (count > 3)
            count = 3;

        float radius = cfg.EventData.Smoke.Radius;
        if (radius < 0)
            radius = 0;
        if (radius > 25.0)
            radius = 25.0;

        vector center = cfg.EventData.Smoke.Position;
        if (center == vector.Zero)
            center = cfg.EventData.EventCenter;

        for (int i = 0; i < count; i++)
        {
            vector p = center;
            if (radius > 0)
            {
                p[0] = p[0] + Math.RandomFloat(-radius, radius);
                p[2] = p[2] + Math.RandomFloat(-radius, radius);
            }
            p[1] = GetGame().SurfaceY(p[0], p[2]) + 0.05;

            Object smokeObj = GetGame().CreateObjectEx(smokeClass, p, ECE_PLACE_ON_SURFACE | ECE_NOLIFETIME);
            if (!smokeObj)
            {
                DeutschZConvoyZLogger.Log("SmokeSpawnFailed", state.EventId, "SMOKE", state.SmokeState, p, "FAILED", smokeClass);
                continue;
            }

            smokeObj.SetPosition(p);
            state.SmokeObjects.Insert(smokeObj);
            ActivateSmokeGrenade(smokeObj, state);
            DeutschZConvoyZLogger.Log("SmokeSpawned", state.EventId, "SMOKE", state.SmokeState, p, "OK", smokeClass);
        }

        state.LastSmokeRefreshAt = GetGame().GetTime();
    }

    protected void ActivateSmokeGrenade(Object smokeObj, DeutschZConvoyZRuntimeState state)
    {
        if (!smokeObj)
            return;

        SmokeGrenadeBase smoke = SmokeGrenadeBase.Cast(smokeObj);
        if (smoke)
        {
            smoke.Unpin();
            DeutschZConvoyZLogger.Log("SmokeActivated", state.EventId, "SMOKE", state.SmokeState, smokeObj.GetPosition(), "OK", smokeObj.GetType() + " Unpin");
            return;
        }

        ItemBase item = ItemBase.Cast(smokeObj);
        if (item && item.GetCompEM())
        {
            item.GetCompEM().SwitchOn();
            DeutschZConvoyZLogger.Log("SmokeActivated", state.EventId, "SMOKE", state.SmokeState, smokeObj.GetPosition(), "OK", smokeObj.GetType() + " EM");
            return;
        }

        DeutschZConvoyZLogger.Log("SmokeActivationSkipped", state.EventId, "SMOKE", state.SmokeState, smokeObj.GetPosition(), "WARN", smokeObj.GetType());
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
