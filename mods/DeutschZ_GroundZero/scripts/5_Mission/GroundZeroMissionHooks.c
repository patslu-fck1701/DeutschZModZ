/*
    DeutschZ_GroundZero Mission hooks.
    Safe boot and HUD wiring only.
*/

modded class MissionServer
{
    protected int m_GroundZero_Bootstrapped;

    void MissionServer()
    {
        GroundZero_RequestBootstrap("MissionServer constructor");
        GroundZero_ScheduleDelayedBootstrap();
    }

    protected void GroundZero_RequestBootstrap(string source)
    {
        if (!GetGame() || !GetGame().IsServer())
            return;

        if (m_GroundZero_Bootstrapped == 1)
            return;

        m_GroundZero_Bootstrapped = 1;
        Print("[DeutschZ_GroundZero] Bootstrap requested source=" + source);
        GroundZero_GetCore().InitServer();
        Print("[DeutschZ_GroundZero] Bootstrap finished source=" + source);
    }

    protected void GroundZero_DelayedBootstrap()
    {
        GroundZero_RequestBootstrap("MissionServer delayed fallback");
    }

    protected void GroundZero_ScheduleDelayedBootstrap()
    {
        if (!GetGame())
            return;

        GetGame().GetCallQueue(CALL_CATEGORY_SYSTEM).CallLater(this.GroundZero_DelayedBootstrap, 1000, false);
        GetGame().GetCallQueue(CALL_CATEGORY_SYSTEM).CallLater(this.GroundZero_DelayedBootstrap, 5000, false);
    }

    override void OnInit()
    {
        super.OnInit();
        GroundZero_RequestBootstrap("MissionServer OnInit");
        GroundZero_ScheduleDelayedBootstrap();
    }

    override void OnMissionStart()
    {
        super.OnMissionStart();
        GroundZero_RequestBootstrap("MissionServer OnMissionStart");
        GroundZero_ScheduleDelayedBootstrap();
    }

    override void OnUpdate(float timeslice)
    {
        super.OnUpdate(timeslice);
        GroundZero_GetCore().Tick(timeslice);
    }
}

modded class MissionGameplay
{
    ref GroundZeroHUD m_GroundZeroHUD;

    void MissionGameplay()
    {
        m_GroundZeroHUD = null;
    }

    override void OnInit()
    {
        super.OnInit();
        if (!m_GroundZeroHUD)
        {
            m_GroundZeroHUD = new GroundZeroHUD();
        }
    }
}
