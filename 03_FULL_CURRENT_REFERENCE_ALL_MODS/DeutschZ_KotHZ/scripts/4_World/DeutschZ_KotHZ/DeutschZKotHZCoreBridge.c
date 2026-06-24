/*
    DeutschZ KotHZ Core/Bridge adapter.
    FIX HYBRID:
    - Eventmod compiles only against DeutschZ_Core provider APIs.
    - No direct ExpansionMarkerModule / ExpansionMarkerData usage in KotHZ.
    - Markers stay active through DeutschZ_ExpansionBridge registered provider.
    - Signalstation remains separate; cleanup only touches KotHZ marker ids passed here.
*/
class DeutschZKotHZCoreBridge
{
    protected static ref map<string, ref array<Object>> s_AI;

    static void EnsureRuntime()
    {
        if (!s_AI) s_AI = new map<string, ref array<Object>>;
    }

    static string SystemName()
    {
        return "KotHZ";
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
        return "KotHZ_" + id;
    }

    static bool CreateEventMarker(string id, string label, vector position)
    {
        return CreateEventMarker(id, label, position, 0xFFFF0000);
    }

    static bool CreateEventMarker(string id, string label, vector position, int colorARGB)
    {
        if (id == "") return false;

        DeutschZCore_MarkerProviderAPI provider = DeutschZCore_ServiceLocator.GetMarkerProvider();
        if (!provider)
        {
            Print("[DeutschZ_KotHZ] ERROR: DeutschZ marker provider missing. Check load order: Core -> ExpansionBridge -> KotHZ. id=" + id);
            return false;
        }

        return provider.CreateMarker(MarkerId(id), label, position, colorARGB);
    }

    static bool CreateEvent3DMarker(string id, string label, vector position)
    {
        return CreateEvent3DMarker(id, label, position, 0xFFFF0000);
    }

    static bool CreateEvent3DMarker(string id, string label, vector position, int colorARGB)
    {
        if (id == "") return false;

        DeutschZCore_MarkerProviderAPI provider = DeutschZCore_ServiceLocator.GetMarkerProvider();
        if (!provider)
        {
            Print("[DeutschZ_KotHZ] ERROR: DeutschZ 3D marker provider missing. Check load order: Core -> ExpansionBridge -> KotHZ. id=" + id);
            return false;
        }

        return provider.Create3DMarker(MarkerId(id), label, position, colorARGB);
    }

    static bool UpdateEventMarker(string id, vector position)
    {
        if (id == "") return false;

        DeutschZCore_MarkerProviderAPI provider = DeutschZCore_ServiceLocator.GetMarkerProvider();
        if (!provider)
        {
            Print("[DeutschZ_KotHZ] WARN: marker provider missing during update id=" + id);
            return false;
        }

        return provider.UpdateMarker(MarkerId(id), position);
    }

    static void CleanupMarkers()
    {
        DeutschZCore_MarkerProviderAPI provider = DeutschZCore_ServiceLocator.GetMarkerProvider();
        if (!provider) return;

        provider.DeleteMarkersByPrefix("KotHZ_");
        provider.DeleteMarkersByPrefix("DeutschZ_KotHZ_");
    }

    static bool DeleteEventMarker(string id)
    {
        if (id == "") return false;

        DeutschZCore_MarkerProviderAPI provider = DeutschZCore_ServiceLocator.GetMarkerProvider();
        if (!provider)
        {
            Print("[DeutschZ_KotHZ] WARN: marker provider missing during delete id=" + id);
            return false;
        }

        return provider.DeleteMarker(MarkerId(id));
    }

    static bool DeleteEvent3DMarker(string id)
    {
        return DeleteEventMarker(id);
    }

    static bool DeleteRawMarker(string rawId)
    {
        if (rawId == "") return false;

        DeutschZCore_MarkerProviderAPI provider = DeutschZCore_ServiceLocator.GetMarkerProvider();
        if (!provider)
        {
            Print("[DeutschZ_KotHZ] WARN: marker provider missing during raw delete id=" + rawId);
            return false;
        }

        return provider.DeleteMarker(rawId);
    }

    protected static void TrackAI(string eventId, Object obj)
    {
        if (!obj) return;
        EnsureRuntime();

        string key = "KotHZ_" + eventId;
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
        if (DeutschZKotHZClassGuard.IsBlockedClass(className)) return false;

        DeutschZCore_AIProviderAPI provider = DeutschZCore_ServiceLocator.GetAIProvider();
        if (provider && provider.SpawnInfected("KotHZ_" + eventId, className, position))
            return true;

        if (!GetGame() || !GetGame().IsServer()) return false;
        if (!GetGame().ConfigIsExisting("CfgVehicles " + className)) return false;

        vector p = position;
        p[1] = GetGame().SurfaceY(p[0], p[2]);

        Object obj = GetGame().CreateObjectEx(className, p, ECE_PLACE_ON_SURFACE | ECE_INITAI);
        if (!obj)
            return false;

        TrackAI(eventId, obj);
        return true;
    }

    static bool SpawnGuard(string eventId, string loadoutId, vector position)
    {
        DeutschZCore_AIProviderAPI provider = DeutschZCore_ServiceLocator.GetAIProvider();
        if (provider && provider.SpawnGuard("KotHZ_" + eventId, loadoutId, position))
            return true;

        return SpawnLocalEnemy(eventId, "ZmbM_SoldierNormal_Beige", position);
    }

    static bool SpawnInfected(string eventId, string className, vector position)
    {
        return SpawnLocalEnemy(eventId, className, position);
    }

    static void CleanupAI(string eventId)
    {
        DeutschZCore_AIProviderAPI provider = DeutschZCore_ServiceLocator.GetAIProvider();
        if (provider)
            provider.CleanupEventAI("KotHZ_" + eventId);

        EnsureRuntime();
        string key = "KotHZ_" + eventId;
        array<Object> list;
        if (!s_AI.Find(key, list)) return;

        foreach (Object obj: list)
        {
            if (obj) GetGame().ObjectDelete(obj);
        }

        s_AI.Remove(key);
    }
}
