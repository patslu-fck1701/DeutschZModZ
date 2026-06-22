/*
    DeutschZ ModZ
    Autor/Eigentuemer: Patrick Sluzalek / fck1701
    Projekt: DeutschZ
    Zweck: Eigene DeutschZ-Implementierung fuer Core, ExpansionBridge und Event-Module.
    Quellen-/Konzeptnachweis: Eigenentwickelte Struktur; DayZ, CF und Expansion nur als Laufzeit-API/Abhaengigkeit.
    No-Copy-Bestaetigung: Kein Code, keine Assets und keine Configs aus fremden Mods kopiert.

    FIX31:
    - MarkerProvider nutzt die vorhandene DayZ Expansion Navigation Marker API.
    - Event-Mods rufen weiterhin nur DeutschZ Core/Bridge auf.
    - Keine physischen Marker-Fallbackobjekte.
*/

class DeutschZExpansionBridge_MarkerProvider: DeutschZCore_MarkerProviderAPI
{
    protected ref map<string, vector> m_Markers;
    protected ref map<string, int> m_MarkerIs3D;
    protected ref map<string, string> m_MarkerLabels;
    protected ref map<string, int> m_MarkerColors;

    void DeutschZExpansionBridge_MarkerProvider()
    {
        m_Markers = new map<string, vector>;
        m_MarkerIs3D = new map<string, int>;
        m_MarkerLabels = new map<string, string>;
        m_MarkerColors = new map<string, int>;
    }

    protected ExpansionMarkerModule GetExpansionMarkerModuleSafe()
    {
        return ExpansionMarkerModule.GetModuleInstance();
    }

    protected string GetIconName(string id)
    {
        // FIX44: event-specific marker symbols. Keep conservative names and fall back to Territory.
        if (id.IndexOf("KotHZ_") == 0) return "Territory";
        if (id.IndexOf("ConvoyZ_") == 0) return "Vehicle";
        if (id.IndexOf("GroundZero_") == 0) return "ContaminatedArea";
        if (id.IndexOf("CourierZ_") == 0) return "Deliver";
        return "Territory";
    }

    protected bool CreateOrReplaceExpansionMarker(string id, string label, vector position, int colorARGB, bool marker3D)
    {
        if (!GetGame() || !GetGame().IsClient() && !GetGame().IsServer())
            return false;

        ExpansionMarkerModule module = GetExpansionMarkerModuleSafe();
        if (!module)
        {
            DeutschZCore_Log.Warn("ExpansionBridge", "ExpansionMarkerModule unavailable for id=" + id);
            return false;
        }

        module.RemoveServerMarker(id);
        ExpansionMarkerData marker = module.CreateServerMarker(label, GetIconName(id), position, colorARGB, marker3D, id);
        if (!marker)
        {
            DeutschZCore_Log.Warn("ExpansionBridge", "Expansion server marker create failed id=" + id + " label=" + label);
            return false;
        }

        DeutschZCore_Log.Info("ExpansionBridge", "Expansion server marker created id=" + id + " label=" + label + " 3d=" + marker3D.ToString() + " pos=" + position.ToString());
        return true;
    }

    override bool CreateMarker(string id, string label, vector position, int colorARGB)
    {
        if (id == "")
            return false;

        m_Markers.Set(id, position);
        m_MarkerIs3D.Set(id, 0);
        m_MarkerLabels.Set(id, label);
        m_MarkerColors.Set(id, colorARGB);
        return CreateOrReplaceExpansionMarker(id, label, position, colorARGB, false);
    }

    override bool Create3DMarker(string id, string label, vector position, int colorARGB)
    {
        if (id == "")
            return false;

        m_Markers.Set(id, position);
        m_MarkerIs3D.Set(id, 1);
        m_MarkerLabels.Set(id, label);
        m_MarkerColors.Set(id, colorARGB);
        return CreateOrReplaceExpansionMarker(id, label, position, colorARGB, true);
    }

    override bool UpdateMarker(string id, vector position)
    {
        if (!m_Markers.Contains(id))
            return false;

        m_Markers.Set(id, position);
        int is3D = 0;
        m_MarkerIs3D.Find(id, is3D);
        string label = id;
        int color = 0xFFFF0000;
        if (m_MarkerLabels.Contains(id)) m_MarkerLabels.Find(id, label);
        if (m_MarkerColors.Contains(id)) m_MarkerColors.Find(id, color);
        return CreateOrReplaceExpansionMarker(id, label, position, color, is3D == 1);
    }

    override bool DeleteMarker(string id)
    {
        bool known = m_Markers.Contains(id);
        if (known)
            m_Markers.Remove(id);
        if (m_MarkerIs3D.Contains(id))
            m_MarkerIs3D.Remove(id);
        if (m_MarkerLabels.Contains(id))
            m_MarkerLabels.Remove(id);
        if (m_MarkerColors.Contains(id))
            m_MarkerColors.Remove(id);

        ExpansionMarkerModule module = GetExpansionMarkerModuleSafe();
        if (module)
            module.RemoveServerMarker(id);

        DeutschZCore_Log.Info("ExpansionBridge", "Expansion server marker delete request id=" + id);
        return known;
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
            return false;

        foreach (Object obj: list)
        {
            if (obj)
                GetGame().ObjectDelete(obj);
        }

        m_RuntimeObjects.Remove(eventId);
        DeutschZCore_Log.Info("ExpansionBridge", "cleaned fallback enemies event=" + eventId);
        return true;
    }
}
