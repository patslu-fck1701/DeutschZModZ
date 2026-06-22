/*
    DeutschZ_GroundZero
    Owner: Patrick Sluzalek / fck1701
    Module: 5_Mission / GroundZeroMissionHooks
    Purpose: Thin MissionServer wiring only. Player hooks stay in 4_World.
    Dependencies: DayZ MissionServer. No foreign mod code.
    Compliance: Original DeutschZ implementation. No copied foreign mod code, assets, configs or stubs.
*/

modded class MissionServer
{
    override void OnInit()
    {
        super.OnInit();
        GroundZeroCore.Get().InitServer();
    }

    override void OnUpdate(float timeslice)
    {
        super.OnUpdate(timeslice);
        GroundZeroCore.Get().Tick();
    }
}


modded class MissionGameplay
{
    protected ref GroundZeroHUD m_GroundZeroHUD;
    protected int m_GroundZeroLastRenderedUpdateMs;

    void MissionGameplay()
    {
        m_GroundZeroLastRenderedUpdateMs = -1;
    }

    override void OnInit()
    {
        super.OnInit();
        GroundZero_EnsureHUD();
    }

    override void OnMissionStart()
    {
        super.OnMissionStart();
        GroundZero_EnsureHUD();
    }

    override void OnUpdate(float timeslice)
    {
        super.OnUpdate(timeslice);
        GroundZero_UpdateHUDFromClientState();
    }

    void GroundZero_EnsureHUD()
    {
        if (!m_GroundZeroHUD)
            m_GroundZeroHUD = new GroundZeroHUD();
    }

    void GroundZero_UpdateHUDFromClientState()
    {
        GroundZero_EnsureHUD();
        if (!m_GroundZeroHUD)
            return;

        int lastUpdateMs = GroundZeroClientHUDState.GetLastUpdateMs();
        if (lastUpdateMs == m_GroundZeroLastRenderedUpdateMs)
            return;

        m_GroundZeroLastRenderedUpdateMs = lastUpdateMs;
        m_GroundZeroHUD.Update(GroundZeroClientHUDState.IsActive(), GroundZeroClientHUDState.GetTitle(), GroundZeroClientHUDState.GetPercent(), GroundZeroClientHUDState.GetCurrent(), GroundZeroClientHUDState.GetTotal(), GroundZeroClientHUDState.GetPlayersNear(), GroundZeroClientHUDState.GetState());
    }
}
