/*
DeutschZ ModZ
Eigenstaendige Implementierung fuer DeutschZ.
Autor/Eigentuemer: Patrick Sluzalek / fck1701.
Keine direkte Codeuebernahme aus Drittquellen.
Oeffentliche Quellen werden nur zur Konzept- und API-Verifikation genutzt.

FIX35:
- Visible KOTH mast restored with a vanilla TerritoryFlag first, custom runtime fallback second.
- No loose/folded flag as the primary visual anymore.
- Flag is attached to the mast and raised by flag_mast animation according to capture progress.
- No music and no particle smoke/net-sync path.
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
        m_TopHeightOffset = 8.0;
        m_BottomHeightOffset = 2.0;
        m_DeleteOnEventEnd = 1;
    }

    bool Spawn(DeutschZKotHZZone zone)
    {
        if (!zone || !zone.EnableFlagpole)
            return false;

        m_Position = zone.FlagpolePosition;
        if (m_Position == vector.Zero)
            m_Position = zone.Position;

        if (m_Position == vector.Zero)
            return false;

        m_Position[1] = GetGame().SurfaceY(m_Position[0], m_Position[2]);
        m_Orientation = zone.FlagpoleOrientation;
        m_TopHeightOffset = Math.Max(4.0, zone.FlagVisualHeightOffset);
        m_BottomHeightOffset = 2.0;
        m_DeleteOnEventEnd = zone.DeleteFlagpoleOnEventEnd;

        string flagClass = zone.FlagClassName;
        if (flagClass == "")
            flagClass = "DeutschZKotHZ_DeutschZ_KotHZ_Flag";

        if (!GetGame().ConfigIsExisting("CfgVehicles " + flagClass))
        {
            Print("[DeutschZ_KotHZ] Flag class missing, fallback to DeutschZKotHZ_DeutschZ_KotHZ_Flag: " + flagClass);
            flagClass = "DeutschZKotHZ_DeutschZ_KotHZ_Flag";
        }

        // FIX44: Use the own runtime mast first. Vanilla TerritoryFlag can show its default green flag
        // underneath the attachment on some servers, which made the KotHZ flag look green/wrongly scaled.
        if (!SpawnMastWithAttachedFlag("DeutschZKotHZ_RuntimeFlagpole", flagClass))
        {
            // Last mast fallback only; custom texture is still applied to the attached flag.
            SpawnMastWithAttachedFlag("TerritoryFlag", flagClass);
        }

        if (m_PoleObject)
        {
            SetCaptureVisual(0.0);
            Print("[DeutschZ_KotHZ] FIX35 visible KOTH mast spawned at " + m_Position.ToString() + " flag=" + flagClass + " pole=" + m_PoleObject.GetType());
            return true;
        }

        // Last visual fallback only if a mast cannot be spawned. This should not be the normal path.
        vector flagPos = GetFallbackFlagPositionForFraction(0.0);
        m_FallbackFlagObject = GetGame().CreateObjectEx(flagClass, flagPos, ECE_NOLIFETIME | ECE_PLACE_ON_SURFACE);
        if (!m_FallbackFlagObject)
        {
            Print("[DeutschZ_KotHZ] Could not spawn KOTH mast or fallback flag object: " + flagClass);
            return false;
        }

        m_FallbackFlagObject.SetPosition(flagPos);
        m_FallbackFlagObject.SetOrientation(m_Orientation);
        SetCaptureVisual(0.0);
        Print("[DeutschZ_KotHZ] FIX35 fallback visible KOTH flag spawned without mast: " + flagClass + " at " + flagPos.ToString());
        return true;
    }

    protected bool SpawnMastWithAttachedFlag(string poleClass, string flagClass)
    {
        if (poleClass == "" || !GetGame().ConfigIsExisting("CfgVehicles " + poleClass))
            return false;

        Object pole = GetGame().CreateObjectEx(poleClass, m_Position, ECE_NOLIFETIME | ECE_PLACE_ON_SURFACE);
        if (!pole)
            return false;

        pole.SetPosition(m_Position);
        pole.SetOrientation(m_Orientation);
        ApplyMastAnimation(pole, 0.0);

        EntityAI poleEntity = EntityAI.Cast(pole);
        if (!poleEntity)
        {
            GetGame().ObjectDelete(pole);
            return false;
        }

        EntityAI flag = poleEntity.GetInventory().CreateAttachment(flagClass);
        if (!flag)
        {
            Print("[DeutschZ_KotHZ] KOTH mast spawned but flag attachment failed. pole=" + poleClass + " flag=" + flagClass);
            GetGame().ObjectDelete(pole);
            return false;
        }

        pole.SetScale(1.0);
        flag.SetScale(1.0);
        ApplyDeutschZFlagTexture(flag);
        flag.SetLifetimeMax(7200);
        flag.SetLifetime(7200);
        m_PoleObject = pole;
        m_FallbackFlagObject = flag;
        return true;
    }

    void SetCaptureVisual(float fraction)
    {
        if (fraction < 0.0)
            fraction = 0.0;
        if (fraction > 1.0)
            fraction = 1.0;

        if (m_PoleObject)
        {
            ApplyMastAnimation(m_PoleObject, fraction);
            m_PoleObject.SetPosition(m_Position);
            m_PoleObject.SetOrientation(m_Orientation);
            return;
        }

        if (m_FallbackFlagObject)
        {
            m_FallbackFlagObject.SetPosition(GetFallbackFlagPositionForFraction(fraction));
            m_FallbackFlagObject.SetOrientation(m_Orientation);
        }
    }

    protected void ApplyDeutschZFlagTexture(EntityAI flag)
    {
        if (!flag)
            return;

        // FIX42/FIX44: SetObjectTexture is only called on EntityAI. Resolve zone-specific flag skins
        // so attached flags do not fall back to the vanilla green visual.
        string texture = "DeutschZ_KotHZ/data/flags/DeutschZ_KotHZ_Flag.paa";
        string type = flag.GetType();
        if (type == "DeutschZKotHZ_NWAF_Flag") texture = "DeutschZ_KotHZ/data/flags/DeutschZ_KotH_NWAF.paa";
        else if (type == "DeutschZKotHZ_Tisy_Flag") texture = "DeutschZ_KotHZ/data/flags/DeutschZ_KotH_Tisy.paa";
        else if (type == "DeutschZKotHZ_LOPA_Flag") texture = "DeutschZ_KotHZ/data/flags/DeutschZ_KotH_LOPA.paa";
        else if (type == "DeutschZKotHZ_YRAP_Flag") texture = "DeutschZ_KotHZ/data/flags/DeutschZ_KotH_YRAP.paa";
        else if (type == "DeutschZKotHZ_Basebuild_Flag") texture = "DeutschZ_KotHZ/data/flags/DeutschZ_KotH_Basebuild.paa";
        else if (type == "DeutschZKotHZ_Alt_One_Flag") texture = "DeutschZ_KotHZ/data/flags/DeutschZ_Alt_One_Flag.paa";
        else if (type == "DeutschZKotHZ_Alt_Two_Flag") texture = "DeutschZ_KotHZ/data/flags/DeutschZ_Alt_Two_Flag.paa";
        else if (type == "DeutschZKotHZ_Alt_Three_Flag") texture = "DeutschZ_KotHZ/data/flags/DeutschZ_Alt_Three_Flag.paa";
        flag.SetObjectTexture(0, texture);
    }

    protected void ApplyMastAnimation(Object pole, float fraction)
    {
        if (!pole)
            return;

        // FIX39: SetAnimationPhase is not available on generic Object in DayZ script.
        // Cast to EntityAI before touching animation phases so World module compiles.
        EntityAI poleEntity = EntityAI.Cast(pole);
        if (!poleEntity)
            return;

        poleEntity.SetAnimationPhase("Deployed", 0.0);
        poleEntity.SetAnimationPhase("Base", 0.0);
        poleEntity.SetAnimationPhase("Support", 0.0);
        poleEntity.SetAnimationPhase("Pole", 0.0);
        poleEntity.SetAnimationPhase("flag_mast", 1.0 - fraction);
    }

    protected vector GetFallbackFlagPositionForFraction(float fraction)
    {
        vector pos = m_Position;
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
        // Disabled for crash isolation. Visual event state is marker + HUD + mast animation only.
    }

    bool TriggerEventMusic(string soundSetName)
    {
        // Music remains disabled for KotHZ crash isolation.
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
