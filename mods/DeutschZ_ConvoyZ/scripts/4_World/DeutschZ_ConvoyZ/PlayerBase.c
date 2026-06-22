/*
DeutschZ ModZ
Eigenstaendige Implementierung fuer DeutschZ.
Autor/Eigentuemer: Patrick Sluzalek / fck1701.
Keine direkte Codeuebernahme aus Drittquellen.
*/

modded class PlayerBase
{
    override void OnRPC(PlayerIdentity sender, int rpc_type, ParamsReadContext ctx)
    {
        if (rpc_type == DeutschZConvoyZConstants.RPC_STATUS_SYNC)
        {
            Param6<string, bool, string, string, int, string> data = new Param6<string, bool, string, string, int, string>("", false, "", "", 0, "");
            if (ctx.Read(data))
            {
                if (data.param1 == DeutschZConvoyZRPC.TOKEN)
                {
                    DeutschZConvoyZClientHUDState.Set(data.param2, data.param3, data.param4, data.param5, data.param6);
                    return;
                }
            }
        }

        super.OnRPC(sender, rpc_type, ctx);
    }
}
