/*
DeutschZ ModZ
Eigenstaendige Implementierung fuer DeutschZ.
Autor/Eigentuemer: Patrick Sluzalek / fck1701.
Keine direkte Codeuebernahme aus Drittquellen.
Oeffentliche Quellen werden nur zur Konzept- und API-Verifikation genutzt.
*/

class DeutschZKotHZ_RuntimeFogEmitter extends ItemBase
{
    protected int m_DeutschZKotHZ_FogActive;
    protected int m_DeutschZKotHZ_FogActiveLocal;
    protected int m_DeutschZKotHZ_FogParticleType;
    protected int m_DeutschZKotHZ_FogParticleTypeLocal;
    protected Particle m_DeutschZKotHZ_FogParticle;

    void DeutschZKotHZ_RuntimeFogEmitter()
    {
        m_DeutschZKotHZ_FogActive = 0;
        m_DeutschZKotHZ_FogActiveLocal = 0;
        m_DeutschZKotHZ_FogParticleType = 3;
        m_DeutschZKotHZ_FogParticleTypeLocal = 3;

        RegisterNetSyncVariableInt("m_DeutschZKotHZ_FogActive");
        RegisterNetSyncVariableInt("m_DeutschZKotHZ_FogParticleType");
    }

    void SetPartsAfterStoreLoad()
    {
        // Runtime particle anchor only. No construction parts are restored.
    }

    void AfterStoreLoad()
    {
        // Runtime particle anchor only. Do not call BaseBuildingBase construction restore.
    }

    void EEOnAfterLoad()
    {
        // Runtime particle anchor only. Startup cleanup removes stale KOTH objects.
    }

    void DeutschZKotHZ_StartFog(int particleType)
    {
        m_DeutschZKotHZ_FogParticleType = particleType;
        m_DeutschZKotHZ_FogActive = 1;
        if (GetGame().IsServer())
            SetSynchDirty();
    }

    protected int DeutschZKotHZ_GetParticleId()
    {
        // FIX14 safe check: particle fog stays disabled.
        // Object smoke is handled by manager via vanilla M18 smoke classes.
        // Returning 0 avoids hard dependency on ParticleList constants across server builds.
        return 0;
    }

    protected void DeutschZKotHZ_StopParticle()
    {
        if (m_DeutschZKotHZ_FogParticle)
        {
            m_DeutschZKotHZ_FogParticle.Stop();
            m_DeutschZKotHZ_FogParticle = null;
        }
    }

    protected void DeutschZKotHZ_UpdateParticle()
    {
        DeutschZKotHZ_StopParticle();
        int particleId = DeutschZKotHZ_GetParticleId();
        if (m_DeutschZKotHZ_FogActiveLocal == 1 && particleId > 0 && !GetGame().IsServer())
            m_DeutschZKotHZ_FogParticle = ParticleManager.GetInstance().PlayOnObject(particleId, this, vector.Zero, vector.Zero, true);
    }

    override void OnVariablesSynchronized()
    {
        if (m_DeutschZKotHZ_FogActiveLocal != m_DeutschZKotHZ_FogActive || m_DeutschZKotHZ_FogParticleTypeLocal != m_DeutschZKotHZ_FogParticleType)
        {
            m_DeutschZKotHZ_FogActiveLocal = m_DeutschZKotHZ_FogActive;
            m_DeutschZKotHZ_FogParticleTypeLocal = m_DeutschZKotHZ_FogParticleType;
            DeutschZKotHZ_UpdateParticle();
        }
    }

    override void EEDelete(EntityAI parent)
    {
        DeutschZKotHZ_StopParticle();
        super.EEDelete(parent);
    }

    override bool CanPutIntoHands(EntityAI parent)
    {
        return false;
    }

    override bool CanPutInCargo(EntityAI parent)
    {
        return false;
    }
}
