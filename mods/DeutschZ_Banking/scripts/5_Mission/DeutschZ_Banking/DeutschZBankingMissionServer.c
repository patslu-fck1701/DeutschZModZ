modded class MissionServer
{
    override void OnInit()
    {
        super.OnInit();
        DeutschZBankAccount.EnsureFolders();
        DeutschZBankingConfig.Load();
        DeutschZBankingCurrency.Load();
        DeutschZBankingAdmins.Load();
        DeutschZBankingATMPositions.Load();
        DeutschZBankingATMPositions.Get().SpawnConfiguredATMs();
        GetDayZGame().Event_OnRPC.Insert(DeutschZBanking_OnRPC);
    }

    void DeutschZBanking_OnRPC(PlayerIdentity sender, Object target, int rpcType, ParamsReadContext ctx)
    {
        if (!sender || rpcType <= DeutschZBankingRPCs.DEUTSCHZ_BANKING_RPC_START || rpcType >= DeutschZBankingRPCs.DEUTSCHZ_BANKING_RPC_END) {
            return;
        }

        PlayerBase player = DeutschZBankingPlayerLookup.GetPlayerByIdentity(sender);
        if (!player) {
            return;
        }

        if (rpcType == DeutschZBankingRPCs.DEUTSCHZ_BANKING_DEPOSIT) {
            Param1<int> depositParam;
            if (ctx.Read(depositParam)) {
                DeutschZ_Banking.DepositCash(player, depositParam.param1);
            }
        } else if (rpcType == DeutschZBankingRPCs.DEUTSCHZ_BANKING_WITHDRAW) {
            Param1<int> withdrawParam;
            if (ctx.Read(withdrawParam)) {
                DeutschZ_Banking.WithdrawCash(player, withdrawParam.param1);
            }
        }

        DeutschZBanking_SendState(player);
    }

    void DeutschZBanking_SendState(PlayerBase player)
    {
        if (!player || !player.GetIdentity()) {
            return;
        }

        int balance = DeutschZ_Banking.GetBalance(player.GetIdentity());
        int inventory = DeutschZBankingCurrency.GetInventoryMoney(player);
        GetGame().RPCSingleParam(null, DeutschZBankingRPCs.DEUTSCHZ_BANKING_SYNC, new Param2<int, int>(balance, inventory), true, player.GetIdentity());
    }
}
