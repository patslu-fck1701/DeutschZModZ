modded class MissionGameplay
{
    override void OnInit()
    {
        super.OnInit();
        GetDayZGame().Event_OnRPC.Insert(DeutschZBanking_ClientRPC);
    }

    override void OnMissionFinish()
    {
        if (GetDayZGame()) {
            GetDayZGame().Event_OnRPC.Remove(DeutschZBanking_ClientRPC);
        }
        super.OnMissionFinish();
    }

    void DeutschZBanking_ClientRPC(PlayerIdentity sender, Object target, int rpcType, ParamsReadContext ctx)
    {
        if (rpcType != DeutschZBankingRPCs.DEUTSCHZ_BANKING_SYNC) {
            return;
        }

        Param2<int, int> data;
        if (!ctx.Read(data)) {
            return;
        }

        if (!DeutschZBankingMenu.Current) {
            DeutschZBankingMenu.OpenLocal();
        }

        if (DeutschZBankingMenu.Current) {
            DeutschZBankingMenu.Current.SetState(data.param1, data.param2);
        }
    }
}
