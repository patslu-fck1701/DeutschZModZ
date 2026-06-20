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
