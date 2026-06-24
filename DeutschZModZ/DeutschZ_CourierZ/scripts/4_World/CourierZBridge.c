/* CourierZ Core/Bridge adapter. No direct Expansion calls. */

class CourierZBridge
{
    static void Notify(string channel, string title, string message, vector position)
    {
        DeutschZCore_NotificationProviderAPI notify = DeutschZCore_ServiceLocator.GetNotificationProvider();
        if (notify)
        {
            notify.SendEventNotification("CourierZ", channel, title, message, position);
        }
        else
        {
            DeutschZCore_Log.Info(CourierZConstants.LOG_SCOPE, "notify fallback: " + title + " - " + message);
        }
    }

    static void Marker(string id, string label, vector position, int color)
    {
        DeutschZCore_MarkerProviderAPI markers = DeutschZCore_ServiceLocator.GetMarkerProvider();
        if (markers)
            markers.CreateMarker(id, label, position, color);
        else
            DeutschZCore_Log.Warn(CourierZConstants.LOG_SCOPE, "marker provider missing id=" + id);
    }

    static void Marker3D(string id, string label, vector position, int color)
    {
        DeutschZCore_MarkerProviderAPI markers = DeutschZCore_ServiceLocator.GetMarkerProvider();
        if (markers)
            markers.Create3DMarker(id, label, position, color);
        else
            DeutschZCore_Log.Warn(CourierZConstants.LOG_SCOPE, "3D marker provider missing id=" + id);
    }

    static void DeleteMarkers(string prefix)
    {
        DeutschZCore_MarkerProviderAPI markers = DeutschZCore_ServiceLocator.GetMarkerProvider();
        if (markers)
            markers.DeleteMarkersByPrefix(prefix);
    }

    static bool SpawnEnemy(string eventId, string className, vector position)
    {
        DeutschZCore_AIProviderAPI ai = DeutschZCore_ServiceLocator.GetAIProvider();
        if (ai && ai.SpawnInfected(eventId, className, position))
            return true;

        if (!GetGame() || !GetGame().IsServer())
            return false;

        string spawnClass = className;
        if (!GetGame().ConfigIsExisting("CfgVehicles " + spawnClass))
            spawnClass = "ZmbM_usSoldier_Officer_Desert";

        vector p = position;
        p[1] = GetGame().SurfaceY(p[0], p[2]);
        Object obj = GetGame().CreateObjectEx(spawnClass, p, ECE_PLACE_ON_SURFACE);
        return obj != null;
    }
}
