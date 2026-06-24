/*
    DeutschZ_GroundZero
    Owner: Patrick Sluzalek / fck1701
    Module: 4_World / GroundZeroRetryUI
    Purpose: Client-side retry/abort request helper; real layout follows after compile pass.
    Dependencies: DayZ RPC API, PlayerBase. No foreign mod code.
    Compliance: Original DeutschZ implementation. No copied foreign mod code, assets, configs or stubs.
*/

class GroundZeroRetryUI
{
    // ASSUMPTION: Real UI layout will be added after first compile pass.
    static void RequestRetry(PlayerBase player)
    {
        if (!GetGame())
        {
            return;
        }

        if (GetGame().IsServer())
        {
            GroundZeroCore.Get().RequestRetry(player);
            return;
        }

        if (!player)
        {
            player = PlayerBase.Cast(GetGame().GetPlayer());
        }

        if (!player)
        {
            return;
        }

        GetGame().RPCSingleParam(player, GroundZeroConstants.RPC_RETRY_REQUEST, new Param1<int>(0), true);
    }

    static void RequestAbort(PlayerBase player)
    {
        if (!GetGame())
        {
            return;
        }

        if (GetGame().IsServer())
        {
            GroundZeroCore.Get().RequestAbort(player);
            return;
        }

        if (!player)
        {
            player = PlayerBase.Cast(GetGame().GetPlayer());
        }

        if (!player)
        {
            return;
        }

        GetGame().RPCSingleParam(player, GroundZeroConstants.RPC_ABORT_REQUEST, new Param1<int>(0), true);
    }
}
