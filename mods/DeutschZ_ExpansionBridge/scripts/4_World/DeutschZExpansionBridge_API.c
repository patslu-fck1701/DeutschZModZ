/*
    DeutschZ ModZ
    Autor/Eigentuemer: Patrick Sluzalek / fck1701
    Projekt: DeutschZ
    Zweck: Eigene DeutschZ-Implementierung fuer Core, ExpansionBridge und Event-Module.
    Quellen-/Konzeptnachweis: Eigenentwickelte Struktur; DayZ, CF und Expansion nur als Laufzeit-API/Abhaengigkeit.
    No-Copy-Bestaetigung: Kein Code, keine Assets und keine Configs aus fremden Mods kopiert.
*/

class DeutschZExpansionBridge_MarkerProvider: DeutschZCore_MarkerProviderAPI
{
    protected ref map<string, vector> m_Markers;
    protected ref map<string, Object> m_VisualObjects;

    void DeutschZExpansionBridge_MarkerProvider()
    {
        m_Markers = new map<string, vector>;
        m_VisualObjects = new map<string, Object>;
    }

    protected string VisibleMarkerClassName(string id)
    {
        // FIX28: physical marker fallback objects are disabled for regression testing.
        // Keep this helper API-stable, but do not select/spawn world objects here.
        return "";
    }


    protected void CreateOrMoveVisibleFallback(string id, vector position)
    {
        // FIX28 regression hardening:
        // The previous physical marker fallback spawned barrels/smoke grenades on marker requests.
        // In the last crash timeline the server crashed immediately after repeated KotHZ marker requests.
        // Until the real Expansion marker API is verified, marker requests are stored/logged only.
        // This keeps events functional and prevents marker fallback objects from becoming a native-crash variable.
        return;
    }


    protected void SwitchOnSmokeMarker(Object markerObject)
    {
        SmokeGrenadeBase smoke = SmokeGrenadeBase.Cast(markerObject);
        if (!smoke)
            return;

        if (smoke.GetCompEM() && smoke.GetCompEM().CanWork() && !smoke.GetCompEM().IsWorking())
            smoke.GetCompEM().SwitchOn();
    }

    protected void NotifyMarkerCreated(string id, string label, vector position)
    {
        // FIX25: Marker requests must not spam chat/popup.
        // Map/3D marker creation is logged and represented by a safe world fallback object.
        // Real Expansion map markers stay behind the Bridge provider and can be added here after API verification.
        return;
    }

    override bool CreateMarker(string id, string label, vector position, int colorARGB)
    {
        if (id == "")
            return false;

        m_Markers.Set(id, position);
        CreateOrMoveVisibleFallback(id, position);
        NotifyMarkerCreated(id, label, position);
        DeutschZCore_Log.Info("ExpansionBridge", "marker create request id=" + id + " label=" + label + " pos=" + position.ToString());
        return true;
    }


    override bool Create3DMarker(string id, string label, vector position, int colorARGB)
    {
        string markerId = id;
        if (markerId.IndexOf("_3D_") < 0 && markerId.IndexOf("3D_") < 0)
            markerId = id + "_3D_";

        return CreateMarker(markerId, label, position, colorARGB);
    }

    override bool UpdateMarker(string id, vector position)
    {
        if (!m_Markers.Contains(id))
            return false;

        m_Markers.Set(id, position);
        CreateOrMoveVisibleFallback(id, position);
        DeutschZCore_Log.Info("ExpansionBridge", "marker update request id=" + id);
        return true;
    }

    override bool DeleteMarker(string id)
    {
        if (!m_Markers.Contains(id) && !m_VisualObjects.Contains(id))
            return false;

        if (m_Markers.Contains(id))
            m_Markers.Remove(id);

        Object obj;
        if (m_VisualObjects.Find(id, obj))
        {
            if (obj)
                GetGame().ObjectDelete(obj);
            m_VisualObjects.Remove(id);
        }

        DeutschZCore_Log.Info("ExpansionBridge", "marker delete request id=" + id);
        return true;
    }

    override void DeleteMarkersByPrefix(string prefix)
    {
        array<string> remove = new array<string>;
        foreach (string id, vector pos: m_Markers)
        {
            if (id.IndexOf(prefix) == 0)
                remove.Insert(id);
        }

        foreach (string visualId, Object visualObj: m_VisualObjects)
        {
            if (visualId.IndexOf(prefix) == 0 && remove.Find(visualId) < 0)
                remove.Insert(visualId);
        }

        foreach (string removeId: remove)
        {
            DeleteMarker(removeId);
        }
    }
}

class DeutschZExpansionBridge_AIProvider: DeutschZCore_AIProviderAPI
{
    protected ref map<string, ref array<Object>> m_RuntimeObjects;

    void DeutschZExpansionBridge_AIProvider()
    {
        m_RuntimeObjects = new map<string, ref array<Object>>;
    }

    protected void Track(string eventId, Object obj)
    {
        if (!obj)
            return;

        array<Object> list;
        if (!m_RuntimeObjects.Find(eventId, list))
        {
            list = new array<Object>;
            m_RuntimeObjects.Insert(eventId, list);
        }

        list.Insert(obj);
    }

    override bool SpawnGuard(string eventId, string loadoutId, vector position)
    {
        // Safe test fallback: spawn a vanilla military infected instead of guessing Expansion AI constructors.
        return SpawnInfected(eventId, "ZmbM_usSoldier_Officer_Desert", position);
    }

    override bool SpawnInfected(string eventId, string className, vector position)
    {
        if (!GetGame().IsServer() || className == "")
            return false;

        string spawnClass = className;
        if (!GetGame().ConfigIsExisting("CfgVehicles " + spawnClass))
            spawnClass = "ZmbM_usSoldier_Officer_Desert";

        vector p = position;
        p[1] = GetGame().SurfaceY(p[0], p[2]);

        Object obj = GetGame().CreateObjectEx(spawnClass, p, ECE_PLACE_ON_SURFACE | ECE_INITAI);
        if (!obj)
        {
            DeutschZCore_Log.Warn("ExpansionBridge", "infected spawn failed class=" + spawnClass + " pos=" + p.ToString());
            return false;
        }

        Track(eventId, obj);
        DeutschZCore_Log.Info("ExpansionBridge", "spawned fallback enemy event=" + eventId + " class=" + spawnClass + " pos=" + p.ToString());
        return true;
    }

    override bool CleanupEventAI(string eventId)
    {
        array<Object> list;
        if (!m_RuntimeObjects.Find(eventId, list))
            return true;

        foreach (Object obj: list)
        {
            if (obj)
                GetGame().ObjectDelete(obj);
        }

        list.Clear();
        m_RuntimeObjects.Remove(eventId);
        return true;
    }
}
