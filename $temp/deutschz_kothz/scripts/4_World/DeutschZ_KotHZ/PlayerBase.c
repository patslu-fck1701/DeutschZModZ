/*
DeutschZ ModZ
Eigenstaendige Implementierung fuer DeutschZ.
Autor/Eigentuemer: Patrick Sluzalek / fck1701.
Keine direkte Codeuebernahme aus Drittquellen.
Oeffentliche Quellen werden nur zur Konzept- und API-Verifikation genutzt.
*/

modded class PlayerBase
{
    override void OnRPC(PlayerIdentity sender, int rpc_type, ParamsReadContext ctx)
    {
        if (rpc_type == DeutschZKotHZRPC.PLAY_MUSIC)
        {
            Param4<string, string, vector, float> music = new Param4<string, string, vector, float>("", "", vector.Zero, 0.0);
            if (ctx.Read(music) && music.param1 == DeutschZKotHZRPC.TOKEN)
            {
                DeutschZKotHZClientSound.PlayEventMusic(music.param2, music.param3);
                return;
            }
        }

        if (rpc_type == DeutschZKotHZRPC.SYNC_HUD)
        {
            Param8<string, bool, string, int, int, int, int, string> data = new Param8<string, bool, string, int, int, int, int, string>("", false, "", 0, 0, 0, 0, "");
            if (ctx.Read(data))
            {
                if (data.param1 == DeutschZKotHZRPC.TOKEN)
                {
                    DeutschZKotHZClientHUDState.Set(data.param2, data.param3, data.param4, data.param5, data.param6, data.param7, data.param8);
                    return;
                }
            }
        }

        super.OnRPC(sender, rpc_type, ctx);
    }
}
