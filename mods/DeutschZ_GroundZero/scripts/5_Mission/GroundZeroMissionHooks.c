/*
    DeutschZ_GroundZero
    Owner: Patrick Sluzalek / fck1701
    Module: 5_Mission / GroundZeroMissionHooks
    Purpose: Robust MissionServer bootstrap. Player hooks stay in 4_World.
    Compliance: Original DeutschZ implementation. No copied foreign mod code, assets, configs or stubs.
*/

static int g_GroundZero_Bootstrapped;

void GroundZero_RequestBootstrap(string source)
{
    if (!GetGame() || !GetGame().IsServer())
        return;

    if (g_GroundZero_Bootstrapped == 1)
        return;

    g_GroundZero_Bootstrapped = 1;

    Print("[DeutschZ_GroundZero] Bootstrap requested source=" + source);
    GroundZeroCore.Get().InitServer();
    Print("[DeutschZ_GroundZero] Bootstrap finished source=" + source);
}

<<<<<<< Updated upstream
=======
void GroundZero_DelayedBootstrap()
{
    GroundZero_RequestBootstrap("MissionServer delayed fallback");
}

void GroundZero_ScheduleDelayedBootstrap()
{
    if (!GetGame())
        return;

    GetGame().GetCallQueue(CALL_CATEGORY_SYSTEM).CallLater(GroundZero_DelayedBootstrap, 1000, false);
    GetGame().GetCallQueue(CALL_CATEGORY_SYSTEM).CallLater(GroundZero_DelayedBootstrap, 5000, false);
}

>>>>>>> Stashed changes
modded class MissionServer
{
    void MissionServer()
    {
        GroundZero_RequestBootstrap("MissionServer constructor");
<<<<<<< Updated upstream
=======
        GroundZero_ScheduleDelayedBootstrap();
>>>>>>> Stashed changes
    }

    override void OnInit()
    {
        super.OnInit();
        GroundZero_RequestBootstrap("MissionServer OnInit");
<<<<<<< Updated upstream
=======
        GroundZero_ScheduleDelayedBootstrap();
>>>>>>> Stashed changes
    }

    override void OnMissionStart()
    {
        super.OnMissionStart();
        GroundZero_RequestBootstrap("MissionServer OnMissionStart");
<<<<<<< Updated upstream
=======
        GroundZero_ScheduleDelayedBootstrap();
>>>>>>> Stashed changes
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
