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
}

modded class MissionServer
{
    void MissionServer()
    {
        CourierZ_RequestBootstrap("MissionServer constructor");
    }

    override void OnInit()
    {
        super.OnInit();
        CourierZ_RequestBootstrap("MissionServer OnInit");
    }

    override void OnMissionStart()
    {
        super.OnMissionStart();
        CourierZ_RequestBootstrap("MissionServer OnMissionStart");
    }

    override void OnUpdate(float timeslice)
    {
        super.OnUpdate(timeslice);
        CourierZ_GetCore().Tick();
    }
}
