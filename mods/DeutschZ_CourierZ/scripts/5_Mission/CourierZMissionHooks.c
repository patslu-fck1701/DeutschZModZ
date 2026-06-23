/*
    DeutschZ_CourierZ
    Zweck: Robuster MissionServer-Bootstrap fuer Config/State-Erzeugung.
*/

static int g_CourierZ_Bootstrapped;

void CourierZ_RequestBootstrap(string source)
{
    if (!GetGame() || !GetGame().IsServer())
        return;

    if (g_CourierZ_Bootstrapped == 1)
        return;

    g_CourierZ_Bootstrapped = 1;

    Print("[DeutschZ_CourierZ] Bootstrap requested source=" + source);
    CourierZ_GetCore().InitServer();
    Print("[DeutschZ_CourierZ] Bootstrap finished source=" + source);
<<<<<<< Updated upstream
=======
}

void CourierZ_DelayedBootstrap()
{
    CourierZ_RequestBootstrap("MissionServer delayed fallback");
}

void CourierZ_ScheduleDelayedBootstrap()
{
    if (!GetGame())
        return;

    GetGame().GetCallQueue(CALL_CATEGORY_SYSTEM).CallLater(CourierZ_DelayedBootstrap, 1000, false);
    GetGame().GetCallQueue(CALL_CATEGORY_SYSTEM).CallLater(CourierZ_DelayedBootstrap, 5000, false);
>>>>>>> Stashed changes
}

modded class MissionServer
{
    void MissionServer()
    {
        CourierZ_RequestBootstrap("MissionServer constructor");
        CourierZ_ScheduleDelayedBootstrap();
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
