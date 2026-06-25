/*
    DeutschZ ConvoyZ Core/Bridge adapter.
    FIX HYBRID:
    - Eventmod compiles only against DeutschZ_Core provider APIs.
    - No direct ExpansionMarkerModule / ExpansionMarkerData usage in ConvoyZ.
    - Markers stay active through DeutschZ_ExpansionBridge registered provider.
    - Local infected fallback remains only for safe non-marker runtime behavior.
*/
class DeutschZConvoyZCoreBridge
{
    protected static ref map<string, ref array<Object>> s_AI;

    static void EnsureRuntime()
    {
        if (!s_AI) s_AI = new map<string, ref array<Object>>;
    }

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

    protected static string MarkerId(string id)
    {
        return "ConvoyZ_" + id;
    }

    static bool CreateEventMarker(string id, string label, vector position)
    {
        if (id == "") return false;

        DeutschZCore_MarkerProviderAPI provider = DeutschZCore_ServiceLocator.GetMarkerProvider();
        if (!provider)
        {
            Print("[DeutschZ_ConvoyZ] ERROR: DeutschZ marker provider missing. Check load order: Core -> ExpansionBridge -> ConvoyZ. id=" + id);
            return false;
        }

        return provider.CreateMarker(MarkerId(id), label, position, 0xFFFF8C00);
    }

    static bool CreateEvent3DMarker(string id, string label, vector position)
    {
        if (id == "") return false;

        DeutschZCore_MarkerProviderAPI provider = DeutschZCore_ServiceLocator.GetMarkerProvider();
        if (!provider)
        {
            Print("[DeutschZ_ConvoyZ] ERROR: DeutschZ 3D marker provider missing. Check load order: Core -> ExpansionBridge -> ConvoyZ. id=" + id);
            return false;
        }

        return provider.Create3DMarker(MarkerId(id), label, position, 0xFFFF8C00);
    }

    static void CleanupMarkers()
    {
        DeutschZCore_MarkerProviderAPI provider = DeutschZCore_ServiceLocator.GetMarkerProvider();
        if (provider)
            provider.DeleteMarkersByPrefix("ConvoyZ_");
    }

    static bool DeleteEventMarker(string id)
    {
        if (id == "") return false;

        DeutschZCore_MarkerProviderAPI provider = DeutschZCore_ServiceLocator.GetMarkerProvider();
        if (!provider)
        {
            Print("[DeutschZ_ConvoyZ] WARN: marker provider missing during delete id=" + id);
            return false;
        }

        return provider.DeleteMarker(MarkerId(id));
    }

    protected static void TrackAI(string eventId, Object obj)
    {
        if (!obj) return;
        EnsureRuntime();

        string key = "ConvoyZ_" + eventId;
        array<Object> list;
        if (!s_AI.Find(key, list))
        {
            list = new array<Object>;
            s_AI.Insert(key, list);
        }

        list.Insert(obj);
    }

    static bool SpawnLocalEnemy(string eventId, string className, vector position)
    {
        if (className == "") return false;
        if (DeutschZConvoyZClassGuard.IsBlockedClass(className)) return false;

        DeutschZCore_AIProviderAPI provider = DeutschZCore_ServiceLocator.GetAIProvider();
        if (provider && provider.SpawnInfected("ConvoyZ_" + eventId, className, position))
            return true;

        if (!GetGame() || !GetGame().IsServer()) return false;
        if (!GetGame().ConfigIsExisting("CfgVehicles " + className)) return false;

        vector p = position;
        p[1] = GetGame().SurfaceY(p[0], p[2]);

        Object obj = GetGame().CreateObjectEx(className, p, ECE_PLACE_ON_SURFACE | ECE_INITAI);
        if (!obj)
        {
            Print("[DeutschZ_ConvoyZ] Enemy spawn failed class=" + className + " pos=" + p.ToString());
            return false;
        }

        TrackAI(eventId, obj);
        return true;
    }

    static void CleanupAI(string eventId)
    {
        DeutschZCore_AIProviderAPI provider = DeutschZCore_ServiceLocator.GetAIProvider();
        if (provider)
            provider.CleanupEventAI("ConvoyZ_" + eventId);

        EnsureRuntime();
        string key = "ConvoyZ_" + eventId;
        array<Object> list;
        if (!s_AI.Find(key, list)) return;

        foreach (Object obj: list)
        {
            if (obj) GetGame().ObjectDelete(obj);
        }

        s_AI.Remove(key);
    }
}
