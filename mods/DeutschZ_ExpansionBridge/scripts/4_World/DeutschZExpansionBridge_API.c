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

    void DeutschZExpansionBridge_MarkerProvider()
    {
        m_Markers = new map<string, vector>;
    }

    override bool CreateMarker(string id, string label, vector position, int colorARGB)
    {
        if (id == string.Empty)
            return false;
        m_Markers.Set(id, position);
        DeutschZCore_Log.Info("ExpansionBridge", "marker create request id=" + id + " label=" + label + " pos=" + position.ToString());
        return true;
    }

    override bool UpdateMarker(string id, vector position)
    {
        if (!m_Markers.Contains(id))
            return false;
        m_Markers.Set(id, position);
        DeutschZCore_Log.Info("ExpansionBridge", "marker update request id=" + id);
        return true;
    }

    override bool DeleteMarker(string id)
    {
        if (!m_Markers.Contains(id))
            return false;
        m_Markers.Remove(id);
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
        // Real Expansion-AI spawning remains intentionally behind this adapter.
        // Until exact public constructor/API is confirmed in the target Expansion version, this is safe-noop.
        DeutschZCore_Log.Warn("ExpansionBridge", "SpawnGuard noop until target Expansion AI API is confirmed event=" + eventId + " loadout=" + loadoutId);
        return false;
    }

    override bool SpawnInfected(string eventId, string className, vector position)
    {
        if (!GetGame().IsServer() || className == string.Empty)
            return false;

        Object obj = GetGame().CreateObjectEx(className, position, ECE_PLACE_ON_SURFACE);
        if (!obj)
        {
            DeutschZCore_Log.Warn("ExpansionBridge", "infected spawn failed class=" + className + " pos=" + position.ToString());
            return false;
        }

        Track(eventId, obj);
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
