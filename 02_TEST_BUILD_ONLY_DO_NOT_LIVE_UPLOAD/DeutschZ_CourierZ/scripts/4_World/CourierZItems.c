/* CourierZ item helpers and runtime classes. */

class CourierZItems
{
    static Object SpawnObject(string className, vector position)
    {
        if (!GetGame() || !GetGame().IsServer())
            return null;

        if (!GetGame().ConfigIsExisting("CfgVehicles " + className))
        {
            DeutschZCore_Log.Warn(CourierZConstants.LOG_SCOPE, "missing class " + className);
            return null;
        }

        vector p = position;
        p[1] = GetGame().SurfaceY(p[0], p[2]);
        return GetGame().CreateObjectEx(className, p, ECE_PLACE_ON_SURFACE | ECE_CREATEPHYSICS | ECE_SETUP);
    }
}

modded class PlayerBase
{
    override void EEKilled(Object killer)
    {
        super.EEKilled(killer);
        if (GetGame() && GetGame().IsServer())
            CourierZ_GetCore().OnPlayerKilled(this);
    }
}
