/*
DeutschZ ModZ
Eigenstaendige Implementierung fuer DeutschZ.
Autor/Eigentuemer: Patrick Sluzalek / fck1701.
Keine direkte Codeuebernahme aus Drittquellen.
Oeffentliche Quellen werden nur zur Konzept- und API-Verifikation genutzt.
*/

class DeutschZKotHZ_RuntimeFlagpole extends ItemBase
{
    protected float m_DeutschZKotHZ_ServerCaptureFraction;
    protected float m_DeutschZKotHZ_ClientCaptureFraction;
    protected int m_DeutschZKotHZ_SmokeState;
    protected int m_DeutschZKotHZ_SmokeStateLocal;
    protected float m_DeutschZKotHZ_SmokeHeight;
    protected float m_DeutschZKotHZ_SmokeHeightLocal;
    protected EntityAI m_DeutschZKotHZ_AttachedFlag;
    protected Particle m_DeutschZKotHZ_ParticleSmoke;
    protected int m_DeutschZKotHZ_MusicSerial;
    protected int m_DeutschZKotHZ_MusicSerialLocal;
    protected string m_DeutschZKotHZ_MusicSoundSetName;

    void DeutschZKotHZ_RuntimeFlagpole()
    {
        m_DeutschZKotHZ_ServerCaptureFraction = 0.0;
        m_DeutschZKotHZ_ClientCaptureFraction = -1.0;
        m_DeutschZKotHZ_SmokeState = -1;
        m_DeutschZKotHZ_SmokeStateLocal = -2;
        m_DeutschZKotHZ_SmokeHeight = 13.0;
        m_DeutschZKotHZ_SmokeHeightLocal = 13.0;
        m_DeutschZKotHZ_AttachedFlag = null;
        m_DeutschZKotHZ_ParticleSmoke = null;
        m_DeutschZKotHZ_MusicSerial = 0;
        m_DeutschZKotHZ_MusicSerialLocal = 0;
        m_DeutschZKotHZ_MusicSoundSetName = "DeutschZ_KotHZ_EventMusic_SoundSet";

        RegisterNetSyncVariableFloat("m_DeutschZKotHZ_ServerCaptureFraction");
        RegisterNetSyncVariableInt("m_DeutschZKotHZ_SmokeState");
        RegisterNetSyncVariableFloat("m_DeutschZKotHZ_SmokeHeight");
        RegisterNetSyncVariableInt("m_DeutschZKotHZ_MusicSerial");

        // DeutschZ visible runtime KOTH mast. Does not inherit BaseBuildingBase/TerritoryFlag.
    }

    void ~DeutschZKotHZ_RuntimeFlagpole()
    {
        DeutschZKotHZ_StopParticleSmoke();
    }

    override void EEDelete(EntityAI parent)
    {
        DeutschZKotHZ_StopParticleSmoke();
        super.EEDelete(parent);
    }

    bool SetupKOTHFlag(string flagClassName)
    {
        // Same principle as working KOTH implementations: create the flag as an attachment in Material_FPole_Flag,
        // then drive the built-in flag_mast animation instead of spawning a separate floating flag object.
        bool attached = DeutschZKotHZ_AttachSingleFlag(flagClassName);
        SetCaptureVisual(0.0);
        UpdateVisuals();
        return attached;
    }

    protected bool DeutschZKotHZ_AttachSingleFlag(string flagClassName)
    {
        if (flagClassName == "")
            flagClassName = "DeutschZKotHZ_DeutschZ_KotHZ_Flag";

        if (!GetGame().IsServer())
            return false;

        if (!GetGame().ConfigIsExisting("CfgVehicles " + flagClassName))
        {
            Print("[DeutschZ_KotHZ] Flag class not found, fallback to DeutschZKotHZ_DeutschZ_KotHZ_Flag: " + flagClassName);
            flagClassName = "DeutschZKotHZ_DeutschZ_KotHZ_Flag";
        }

        m_DeutschZKotHZ_AttachedFlag = GetInventory().CreateAttachment(flagClassName);
        if (m_DeutschZKotHZ_AttachedFlag)
        {
            Print("[DeutschZ_KotHZ] Single logo flag attached to KOTH pole: " + flagClassName);
            return true;
        }

        Print("[DeutschZ_KotHZ] Could not attach flag to KOTH pole/Material_FPole_Flag slot: " + flagClassName);
        return false;
    }

    void SetCaptureVisual(float fraction)
    {
        if (fraction < 0.0)
            fraction = 0.0;
        if (fraction > 1.0)
            fraction = 1.0;

        m_DeutschZKotHZ_ServerCaptureFraction = fraction;
        DeutschZKotHZ_ApplyFlagAnimation(fraction);

        if (GetGame().IsServer())
            SetSynchDirty();
    }

    void SetKOTHSmokeState(int smokeState, float smokeHeight)
    {
        m_DeutschZKotHZ_SmokeState = smokeState;
        m_DeutschZKotHZ_SmokeHeight = Math.Max(1.0, smokeHeight);

        if (GetGame().IsServer())
            SetSynchDirty();
    }

    void TriggerKOTHMusic(string soundSetName)
    {
        // FIX31: hard-disabled compatibility method. Do not dirty net-sync variables for music.
    }

    protected void DeutschZKotHZ_PlayLocalEventMusic()
    {
        // FIX31: music is disabled for KotHZ crash isolation.
    }

    protected int DeutschZKotHZ_GetParticleForState(int state)
    {
        // Particle ids stay disabled here. The manager uses vanilla M18 smoke objects
        // so the mod does not depend on unchecked engine particle names.
        return 0;
    }

    protected void DeutschZKotHZ_UpdateParticleSmoke()
    {
        DeutschZKotHZ_StopParticleSmoke();

        if (m_DeutschZKotHZ_SmokeStateLocal < 0)
            return;

        int particleId = DeutschZKotHZ_GetParticleForState(m_DeutschZKotHZ_SmokeStateLocal);
        if (particleId <= 0)
            return;

        vector offset = "0 0 0";
        offset[1] = Math.Max(1.0, m_DeutschZKotHZ_SmokeHeightLocal);
        m_DeutschZKotHZ_ParticleSmoke = ParticleManager.GetInstance().PlayOnObject(particleId, this, offset, vector.Zero, true);
    }

    protected void DeutschZKotHZ_StopParticleSmoke()
    {
        if (m_DeutschZKotHZ_ParticleSmoke)
        {
            m_DeutschZKotHZ_ParticleSmoke.Stop();
            m_DeutschZKotHZ_ParticleSmoke = null;
        }
    }

    protected void DeutschZKotHZ_ApplyFlagAnimation(float fraction)
    {
        SetAnimationPhase("Deployed", 0.0);
        SetAnimationPhase("Base", 0.0);
        SetAnimationPhase("Support", 0.0);
        SetAnimationPhase("Pole", 0.0);
        SetAnimationPhase("flag_mast", 1.0 - fraction);
    }

    override void OnVariablesSynchronized()
    {
        super.OnVariablesSynchronized();

        bool smokeChanged = false;
        if (m_DeutschZKotHZ_SmokeStateLocal != m_DeutschZKotHZ_SmokeState)
        {
            m_DeutschZKotHZ_SmokeStateLocal = m_DeutschZKotHZ_SmokeState;
            smokeChanged = true;
        }

        if (m_DeutschZKotHZ_SmokeHeightLocal != m_DeutschZKotHZ_SmokeHeight)
        {
            m_DeutschZKotHZ_SmokeHeightLocal = m_DeutschZKotHZ_SmokeHeight;
            smokeChanged = true;
        }

        if (smokeChanged)
            DeutschZKotHZ_UpdateParticleSmoke();

        if (m_DeutschZKotHZ_ClientCaptureFraction != m_DeutschZKotHZ_ServerCaptureFraction)
        {
            m_DeutschZKotHZ_ClientCaptureFraction = m_DeutschZKotHZ_ServerCaptureFraction;
            DeutschZKotHZ_ApplyFlagAnimation(m_DeutschZKotHZ_ClientCaptureFraction);
            UpdateVisuals();
        }
    }

    void SetPartsAfterStoreLoad()
    {
    }

    void UpdateVisuals()
    {
        DeutschZKotHZ_ApplyFlagAnimation(m_DeutschZKotHZ_ServerCaptureFraction);
    }

    override bool CanPutIntoHands(EntityAI parent) { return false; }
    override bool CanPutInCargo(EntityAI parent) { return false; }
    override bool CanReleaseAttachment(EntityAI attachment) { return false; }
}

// Compatibility aliases used for startup cleanup of existing event objects.
class DeutschZKotHZ_EventFlagpole extends DeutschZKotHZ_RuntimeFlagpole
{
}


class DeutschZKotHZ_LegacyFlagpoleCleanupAlias extends DeutschZKotHZ_RuntimeFlagpole
{
}
