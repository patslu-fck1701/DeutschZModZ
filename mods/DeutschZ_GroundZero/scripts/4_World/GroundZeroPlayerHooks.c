/*
    DeutschZ_GroundZero
    Owner: Patrick Sluzalek / fck1701
    Module: 4_World / GroundZeroPlayerHooks
    Purpose: PlayerBase RPC/death hooks. Kept in World module because PlayerBase is a World type.
    Dependencies: DayZ PlayerBase, PlayerIdentity, ParamsReadContext. No foreign mod code.
    Compliance: Original DeutschZ implementation. No copied foreign mod code, assets, configs or stubs.
*/

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

        if (GetGame() && GetGame().IsServer())
        {
            GroundZeroCore.Get().OnPlayerKilled(this, killer);
        }
    }
}
