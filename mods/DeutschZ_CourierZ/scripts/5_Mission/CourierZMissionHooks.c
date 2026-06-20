/* CourierZ MissionServer wiring only. */

modded class MissionServer
{
    override void OnInit()
    {
        super.OnInit();
        CourierZ_GetCore().InitServer();
    }

    override void OnUpdate(float timeslice)
    {
        super.OnUpdate(timeslice);
        CourierZ_GetCore().Tick();
    }
}
