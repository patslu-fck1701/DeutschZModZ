/*
DeutschZ ModZ
Eigenstaendige Implementierung fuer DeutschZ.
Autor/Eigentuemer: Patrick Sluzalek / fck1701.
Keine direkte Codeuebernahme aus Drittquellen.
Oeffentliche Quellen werden nur zur Konzept- und API-Verifikation genutzt.
*/

class DeutschZKotHZFlagpole
{
    protected Object m_PoleObject;
    protected Object m_FallbackFlagObject;
    protected vector m_Position;
    protected vector m_Orientation;
    protected float m_TopHeightOffset;
    protected float m_BottomHeightOffset;
    protected int m_DeleteOnEventEnd;

    void DeutschZKotHZFlagpole()
    {
        m_PoleObject = null;
        m_FallbackFlagObject = null;
        m_Position = vector.Zero;
        m_Orientation = vector.Zero;
        m_TopHeightOffset = 13.0;
        m_BottomHeightOffset = 1.4;
        m_DeleteOnEventEnd = 1;
    }

    bool Spawn(DeutschZKotHZZone zone)
    {
        if (!zone || !zone.EnableFlagpole)
            return false;

        m_Position = zone.FlagpolePosition;
        if (m_Position == vector.Zero)
            m_Position = zone.Position;

        m_Position[1] = GetGame().SurfaceY(m_Position[0], m_Position[2]);
        m_Orientation = zone.FlagpoleOrientation;
        m_TopHeightOffset = Math.Max(2.0, zone.FlagVisualHeightOffset);
        m_DeleteOnEventEnd = zone.DeleteFlagpoleOnEventEnd;

        string poleClass = zone.FlagpoleClassName;
        if (poleClass == "")
            poleClass = "DeutschZKotHZ_RuntimeFlagpole";

        // v1.0.18: use one stable visible active class. Compatibility class names are only aliases for cleanup.
        if (poleClass == "DeutschZKotHZ_EventFlagpole" || poleClass == "DeutschZKotHZ_RuntimeFlagpole" || poleClass == "DeutschZKotHZ_LegacyFlagpoleCleanupAlias")
        {
            Print("[DeutschZ_KotHZ] Compatibility flagpole class configured, forcing active DeutschZKotHZ_RuntimeFlagpole: " + poleClass);
            poleClass = "DeutschZKotHZ_RuntimeFlagpole";
        }

        if (!GetGame().ConfigIsExisting("CfgVehicles " + poleClass))
        {
            Print("[DeutschZ_KotHZ] Configured flagpole class missing, using DeutschZKotHZ_RuntimeFlagpole: " + poleClass);
            poleClass = "DeutschZKotHZ_RuntimeFlagpole";
        }

        // DeutschZ visible event-flagpole spawn path: keep physics creation, then clean up event objects on start/end.
        // Do not use ECE_NOPERSISTENCY_WORLD here; on this build it made the pole not appear reliably.
        m_PoleObject = GetGame().CreateObjectEx(poleClass, m_Position, ECE_PLACE_ON_SURFACE | ECE_CREATEPHYSICS);
        if (!m_PoleObject)
            m_PoleObject = GetGame().CreateObject(poleClass, m_Position);

        if (!m_PoleObject)
        {
            Print("[DeutschZ_KotHZ] Could not spawn flagpole class: " + poleClass);
            return false;
        }

        m_PoleObject.SetPosition(m_Position);
        m_PoleObject.SetOrientation(m_Orientation);

        EntityAI poleEntity = EntityAI.Cast(m_PoleObject);
        if (poleEntity)
            poleEntity.PlaceOnSurface();

        bool attachedFlag = false;
        DeutschZKotHZ_RuntimeFlagpole customPole = DeutschZKotHZ_RuntimeFlagpole.Cast(m_PoleObject);
        if (customPole)
        {
            attachedFlag = customPole.SetupKOTHFlag(zone.FlagClassName);
            customPole.SetCaptureVisual(0.0);
        }

        // v1.0.21: no free-floating fallback flag anymore.
        // If attachment fails, log it and keep the mast clean instead of spawning a giant detached flag.
        if (!attachedFlag)
            Print("[DeutschZ_KotHZ] WARNING: KOTH flag attachment failed. No fallback plane spawned, to avoid floating/off-scale flag visual.");

        SetCaptureVisual(0.0);

        Print("[DeutschZ_KotHZ] Flagpole spawned visible DeutschZ KotHZ path: " + poleClass + " at " + m_Position.ToString() + " ori=" + m_Orientation.ToString() + " attachedFlag=" + attachedFlag.ToString());
        return true;
    }

    protected void SpawnFallbackMovableFlag(string flagClass)
    {
        // Disabled in v1.0.21. The floating rectangle seen in testing came from this fallback path.
        // The correct path is inventory attachment on the flagpole via Material_FPole_Flag.
        Print("[DeutschZ_KotHZ] Fallback movable flag spawn disabled; using attached flag only.");
    }

    void SetCaptureVisual(float fraction)
    {
        if (fraction < 0.0)
            fraction = 0.0;
        if (fraction > 1.0)
            fraction = 1.0;

        DeutschZKotHZ_RuntimeFlagpole customPole = DeutschZKotHZ_RuntimeFlagpole.Cast(m_PoleObject);
        if (customPole)
            customPole.SetCaptureVisual(fraction);

        if (m_FallbackFlagObject)
        {
            m_FallbackFlagObject.SetPosition(GetFallbackFlagPositionForFraction(fraction));
            m_FallbackFlagObject.SetOrientation(m_Orientation);
        }
    }

    protected vector GetFallbackFlagPositionForFraction(float fraction)
    {
        vector pos = m_Position;
        if (pos == vector.Zero && m_PoleObject)
            pos = m_PoleObject.GetPosition();

        if (pos != vector.Zero)
        {
            float height = m_BottomHeightOffset + ((m_TopHeightOffset - m_BottomHeightOffset) * fraction);
            pos[1] = GetGame().SurfaceY(pos[0], pos[2]) + height;
        }

        return pos;
    }

    vector GetBasePosition()
    {
        return m_Position;
    }

    vector GetTopPosition()
    {
        vector pos = m_Position;
        if (pos == vector.Zero && m_PoleObject)
            pos = m_PoleObject.GetPosition();

        if (pos != vector.Zero)
            pos[1] = GetGame().SurfaceY(pos[0], pos[2]) + m_TopHeightOffset;

        return pos;
    }

    Object GetPoleObject()
    {
        return m_PoleObject;
    }

    Object GetFlagObject()
    {
        return m_FallbackFlagObject;
    }

    void SetSmokeVisual(int smokeState, float smokeHeight)
    {
        DeutschZKotHZ_RuntimeFlagpole customPole = DeutschZKotHZ_RuntimeFlagpole.Cast(m_PoleObject);
        if (customPole)
            customPole.SetKOTHSmokeState(smokeState, smokeHeight);
    }

    bool TriggerEventMusic(string soundSetName)
    {
        // FIX21 Safe-Boot: KOTH music is disabled. Keep API stable but do not trigger sound sync.
        return false;
    }

    bool ShouldDeleteOnEventEnd()
    {
        return m_DeleteOnEventEnd == 1;
    }

    void Cleanup()
    {
        if (!ShouldDeleteOnEventEnd())
        {
            m_PoleObject = null;
            m_FallbackFlagObject = null;
            return;
        }

        if (m_FallbackFlagObject)
        {
            GetGame().ObjectDelete(m_FallbackFlagObject);
            m_FallbackFlagObject = null;
        }

        if (m_PoleObject)
        {
            GetGame().ObjectDelete(m_PoleObject);
            m_PoleObject = null;
        }
    }
}
