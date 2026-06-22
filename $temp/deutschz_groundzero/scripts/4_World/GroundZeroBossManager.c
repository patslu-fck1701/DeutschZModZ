/*
    DeutschZ_GroundZero
    Owner: Patrick Sluzalek / fck1701
    Module: 4_World / GroundZeroBossManager
    Purpose: GroundZero Commander final-defense state machine and escalation waves.
    Dependencies: DayZ scripts; optional Expansion AI through GroundZeroAIBridge only.
    Compliance: Original DeutschZ implementation. No copied foreign mod code, assets, configs or stubs.
*/

class GroundZeroBossManager
{
    protected GroundZeroConfig m_Config;
    protected GroundZeroPersistentState m_State;
    protected GroundZeroZombieManager m_Zombies;
    protected GroundZeroAIBridge m_AI;
    protected GroundZeroNotificationManager m_Notifications;
    protected Object m_Boss;
    protected int m_BossState;
    protected float m_StartedAt;
    protected bool m_PhaseTwoDone;
    protected bool m_PhaseThreeDone;

    void GroundZeroBossManager(GroundZeroConfig cfg, GroundZeroPersistentState state, GroundZeroZombieManager z, GroundZeroAIBridge ai, GroundZeroNotificationManager n)
    {
        m_Config = cfg;
        m_State = state;
        m_Zombies = z;
        m_AI = ai;
        m_Notifications = n;
        m_BossState = GroundZeroBossState.GZ_BOSS_NONE;
    }

    void StartFinalIfNeeded()
    {
        if (m_BossState != GroundZeroBossState.GZ_BOSS_NONE) return;
        if (!m_Config.EnableFinalBoss) return;
        if (m_State.FinalFacilityPosition == "0 0 0") m_State.FinalFacilityPosition = m_Config.PossibleFinalFacilityPositions.Get(0);

        m_Boss = GetGame().CreateObjectEx(m_Config.BossClassName, m_State.FinalFacilityPosition, ECE_PLACE_ON_SURFACE);
        m_BossState = GroundZeroBossState.GZ_BOSS_PHASE_ONE;
        m_State.BossState = m_BossState;
        m_State.FinalStartedAt = GetGame().GetTime() * 0.001;
        m_StartedAt = m_State.FinalStartedAt;
        m_Notifications.Broadcast("Ground Zero Commander aktiv");
        GroundZeroLogging.Info("Boss", "Commander spawned pos=" + m_State.FinalFacilityPosition.ToString());
    }

    void Tick()
    {
        if (!m_Boss)
        {
            m_BossState = GroundZeroBossState.GZ_BOSS_DEAD;
            m_State.BossState = m_BossState;
            return;
        }

        float age = GetGame().GetTime() * 0.001 - m_StartedAt;

        if (!m_PhaseTwoDone && age >= m_Config.FinalDefenseSeconds * 0.33)
        {
            m_PhaseTwoDone = true;
            m_BossState = GroundZeroBossState.GZ_BOSS_PHASE_TWO;
            m_State.BossState = m_BossState;
            m_Zombies.SpawnWave(m_Boss.GetPosition(), 4, 16, 80);
            m_AI.SpawnMilitaryPatrol(m_Boss.GetPosition(), 6);
            GroundZeroLogging.Info("Boss", "Phase two entered");
        }

        if (!m_PhaseThreeDone && age >= m_Config.FinalDefenseSeconds * 0.66)
        {
            m_PhaseThreeDone = true;
            m_BossState = GroundZeroBossState.GZ_BOSS_PHASE_THREE;
            m_State.BossState = m_BossState;
            m_AI.SpawnRoguePatrol(m_Boss.GetPosition(), 6);
            m_Zombies.SpawnWave(m_Boss.GetPosition(), 5, 20, 100);
            GroundZeroLogging.Info("Boss", "Phase three entered");
        }

        if (age >= m_Config.FinalDefenseSeconds)
        {
            GetGame().ObjectDelete(m_Boss);
            m_Boss = null;
            m_BossState = GroundZeroBossState.GZ_BOSS_DEAD;
            m_State.BossState = m_BossState;
            GroundZeroLogging.Info("Boss", "Commander defense timer completed");
        }
    }

    bool IsDead()
    {
        return m_BossState == GroundZeroBossState.GZ_BOSS_DEAD;
    }

    void Cleanup()
    {
        if (m_Boss)
        {
            GetGame().ObjectDelete(m_Boss);
            m_Boss = null;
        }
        m_BossState = GroundZeroBossState.GZ_BOSS_NONE;
        m_PhaseTwoDone = false;
        m_PhaseThreeDone = false;
    }
}
