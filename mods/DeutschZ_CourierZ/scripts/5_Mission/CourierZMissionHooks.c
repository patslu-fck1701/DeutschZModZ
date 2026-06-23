/*
    DeutschZ_CourierZ MissionServer wiring.
    Zweck: Robuster MissionServer-Bootstrap fuer Config/State-Erzeugung.
*/

modded class MissionServer
{
    protected int m_CourierZ_Bootstrapped;

    void MissionServer()
    {
        CourierZ_RequestBootstrap("MissionServer constructor");
        CourierZ_ScheduleDelayedBootstrap();
    }

    protected void CourierZ_RequestBootstrap(string source)
    {
        if (!GetGame() || !GetGame().IsServer())
            return;

        if (m_CourierZ_Bootstrapped == 1)
            return;

        m_CourierZ_Bootstrapped = 1;
        Print("[DeutschZ_CourierZ] Bootstrap requested source=" + source);
        CourierZ_GetCore().InitServer();
        Print("[DeutschZ_CourierZ] Bootstrap finished source=" + source);
    }

    protected void CourierZ_DelayedBootstrap()
    {
        CourierZ_RequestBootstrap("MissionServer delayed fallback");
    }

    protected void CourierZ_ScheduleDelayedBootstrap()
    {
        if (!GetGame())
            return;

        GetGame().GetCallQueue(CALL_CATEGORY_SYSTEM).CallLater(this.CourierZ_DelayedBootstrap, 1000, false);
        GetGame().GetCallQueue(CALL_CATEGORY_SYSTEM).CallLater(this.CourierZ_DelayedBootstrap, 5000, false);
    }

    override void OnInit()
    {
        super.OnInit();
        CourierZ_RequestBootstrap("MissionServer OnInit");
        CourierZ_ScheduleDelayedBootstrap();
    }

    override void OnMissionStart()
    {
        super.OnMissionStart();
        CourierZ_RequestBootstrap("MissionServer OnMissionStart");
        CourierZ_ScheduleDelayedBootstrap();
    }

    override void OnUpdate(float timeslice)
    {
        super.OnUpdate(timeslice);
        CourierZ_GetCore().Tick();
    }
}
