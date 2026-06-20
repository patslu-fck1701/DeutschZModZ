/*
    DeutschZ_GroundZero
    Owner: Patrick Sluzalek / fck1701
    Module: 5_Mission / GroundZeroMissionHooks
    Purpose: Thin mission wiring only. Core systems remain in 3_Game/4_World.
    Dependencies: DayZ MissionServer, PlayerBase. No foreign mod code.
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

    override void InvokeOnConnect(PlayerBase player, PlayerIdentity identity)
    {
        super.InvokeOnConnect(player, identity);
        GroundZeroLogging.Info("Mission", "Player connected");
    }

}

modded class PlayerBase
{
    override void OnRPC(PlayerIdentity sender, int rpc_type, ParamsReadContext ctx)
    {
        if (rpc_type == GroundZeroConstants.RPC_RETRY_REQUEST)
        {
            if (GetGame() && GetGame().IsServer() && sender)
            {
                GroundZeroLogging.Info(GroundZeroConstants.LOG_CAT_RETRY, "Retry RPC received");
                GroundZeroCore.Get().RequestRetryByIdentity(sender);
            }
            return;
        }

        if (rpc_type == GroundZeroConstants.RPC_ABORT_REQUEST)
        {
            if (GetGame() && GetGame().IsServer() && sender)
            {
                GroundZeroLogging.Info(GroundZeroConstants.LOG_CAT_RETRY, "Abort RPC received");
                GroundZeroCore.Get().RequestAbortByIdentity(sender);
            }
            return;
        }

        super.OnRPC(sender, rpc_type, ctx);
    }

    override void EEKilled(Object killer)
    {
        super.EEKilled(killer);
        if (GetGame() && GetGame().IsServer()) GroundZeroCore.Get().OnPlayerKilled(this, killer);
    }
}
