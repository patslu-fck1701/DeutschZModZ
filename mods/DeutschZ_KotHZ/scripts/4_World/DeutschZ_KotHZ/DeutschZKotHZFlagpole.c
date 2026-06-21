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

        // FIX25: do not spawn the custom runtime flagpole during live tests.
        // The previous custom flag attachment path could show a white/invisible flag and was suspect for native crashes.
        // Use stable vanilla world objects only: a red barrel as capture mast and a separate vanilla/custom flag object above it.
        string poleClass = "Barrel_Red";
        if (!GetGame().ConfigIsExisting("CfgVehicles " + poleClass))
            poleClass = "M18SmokeGrenade_Red";

        m_PoleObject = GetGame().CreateObjectEx(poleClass, m_Position, ECE_PLACE_ON_SURFACE);
        if (!m_PoleObject)
            m_PoleObject = GetGame().CreateObject(poleClass, m_Position);

        if (!m_PoleObject)
        {
            Print("[DeutschZ_KotHZ] Could not spawn safe KOTH marker object: " + poleClass);
            return false;
        }

        m_PoleObject.SetPosition(m_Position);
        m_PoleObject.SetOrientation(m_Orientation);

        EntityAI poleEntity = EntityAI.Cast(m_PoleObject);
        if (poleEntity)
            poleEntity.PlaceOnSurface();

        string flagClass = zone.FlagClassName;
        if (flagClass == "" || !GetGame().ConfigIsExisting("CfgVehicles " + flagClass))
            flagClass = "Flag_Chernarus";
        if (!GetGame().ConfigIsExisting("CfgVehicles " + flagClass))
            flagClass = "Flag_White";

        if (GetGame().ConfigIsExisting("CfgVehicles " + flagClass))
        {
            vector flagPos = GetFallbackFlagPositionForFraction(1.0);
            m_FallbackFlagObject = GetGame().CreateObjectEx(flagClass, flagPos, ECE_PLACE_ON_SURFACE);
            if (m_FallbackFlagObject)
            {
                m_FallbackFlagObject.SetPosition(flagPos);
                m_FallbackFlagObject.SetOrientation(m_Orientation);
                string texturePath = DeutschZKotHZ_GetSafeFlagTexture(flagClass);
                if (texturePath != "")
                    m_FallbackFlagObject.SetObjectTexture(0, texturePath);
            }
        }

        Print("[DeutschZ_KotHZ] FIX25 safe KOTH beacon spawned: pole=" + poleClass + " flag=" + flagClass + " pos=" + m_Position.ToString());
        return true;
    }

    protected string DeutschZKotHZ_GetSafeFlagTexture(string flagClassName)
    {
        if (flagClassName == "DeutschZKotHZ_NWAF_Flag") return "/DeutschZ_KotHZ/data/flags/DeutschZ_KotH_NWAF.paa";
        if (flagClassName == "DeutschZKotHZ_Tisy_Flag") return "/DeutschZ_KotHZ/data/flags/DeutschZ_KotH_Tisy.paa";
        if (flagClassName == "DeutschZKotHZ_LOPA_Flag") return "/DeutschZ_KotHZ/data/flags/DeutschZ_KotH_LOPA.paa";
        if (flagClassName == "DeutschZKotHZ_YRAP_Flag") return "/DeutschZ_KotHZ/data/flags/DeutschZ_KotH_YRAP.paa";
        if (flagClassName == "DeutschZKotHZ_Basebuild_Flag") return "/DeutschZ_KotHZ/data/flags/DeutschZ_KotH_Basebuild.paa";
        if (flagClassName == "DeutschZKotHZ_DeutschZ_KotHZ_Flag") return "/DeutschZ_KotHZ/data/flags/DeutschZ_KotHZ_Flag.paa";
        return "";
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
