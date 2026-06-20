modded class PlayerBase
{
    override void OnRPC(PlayerIdentity sender, int rpc_type, ParamsReadContext ctx)
    {
        if (rpc_type == DeutschZBattlepassRPC.SYNC)
        {
            Param1<DeutschZBattlepassSyncPacket> data = new Param1<DeutschZBattlepassSyncPacket>(new DeutschZBattlepassSyncPacket());
            if (ctx.Read(data) && data.param1)
            {
                DeutschZBattlepassClientState.SetSync(data.param1);
                return;
            }
        }

        if (GetGame().IsServer())
        {
            if (DeutschZBattlepass_HandleServerRPC(sender, rpc_type, ctx))
            {
                return;
            }
        }

        super.OnRPC(sender, rpc_type, ctx);
    }

    protected bool DeutschZBattlepass_HandleServerRPC(PlayerIdentity sender, int rpc_type, ParamsReadContext ctx)
    {
        if (!sender)
        {
            return false;
        }

        DeutschZBattlepassManager manager = DeutschZBattlepassRuntime.GetManager();
        if (!manager)
        {
            return false;
        }

        string steam64 = sender.GetPlainId();
        string name = sender.GetName();

        if (rpc_type == DeutschZBattlepassRPC.REQUEST_SYNC)
        {
            manager.SendSyncToPlayer(this);
            return true;
        }

        if (rpc_type == DeutschZBattlepassRPC.CLAIM_REWARD)
        {
            Param1<DeutschZBattlepassClaimRequest> claimData = new Param1<DeutschZBattlepassClaimRequest>(new DeutschZBattlepassClaimRequest());
            if (ctx.Read(claimData) && claimData.param1)
            {
                manager.ClaimReward(this, claimData.param1.RewardId, claimData.param1.Premium);
                manager.SendSyncToPlayer(this);
            }
            return true;
        }

        if (rpc_type == DeutschZBattlepassRPC.ADMIN_ADD_XP)
        {
            if (manager.GetPremiumConfig().Admins && manager.GetPremiumConfig().Admins.Count() > 0 && !manager.IsAdmin(steam64))
            {
                return true;
            }
            Param1<DeutschZBattlepassAdminXpRequest> xpData = new Param1<DeutschZBattlepassAdminXpRequest>(new DeutschZBattlepassAdminXpRequest());
            if (ctx.Read(xpData) && xpData.param1)
            {
                if (xpData.param1.Steam64 == "")
                {
                    xpData.param1.Steam64 = steam64;
                }
                manager.AddXP(xpData.param1.Steam64, name, xpData.param1.XP, xpData.param1.Reason);
                manager.SendSyncToPlayer(this);
            }
            return true;
        }

        if (rpc_type == DeutschZBattlepassRPC.ADMIN_SET_PREMIUM)
        {
            if (manager.GetPremiumConfig().Admins && manager.GetPremiumConfig().Admins.Count() > 0 && !manager.IsAdmin(steam64))
            {
                return true;
            }
            Param1<DeutschZBattlepassPremiumRequest> premiumData = new Param1<DeutschZBattlepassPremiumRequest>(new DeutschZBattlepassPremiumRequest());
            if (ctx.Read(premiumData) && premiumData.param1)
            {
                if (premiumData.param1.Steam64 == "")
                {
                    premiumData.param1.Steam64 = steam64;
                }
                manager.SetPremium(premiumData.param1.Steam64, premiumData.param1.Premium);
                manager.SendSyncToPlayer(this);
            }
            return true;
        }

        if (rpc_type == DeutschZBattlepassRPC.ACTIVATE_PREMIUM_ITEM)
        {
            ItemBase item = ItemBase.Cast(GetItemInHands());
            if (item)
            {
                manager.ActivatePremiumItem(this, item);
                manager.SendSyncToPlayer(this);
            }
            return true;
        }

        if (rpc_type == DeutschZBattlepassRPC.TASK_PROGRESS)
        {
            Param1<DeutschZBattlepassTaskProgressRequest> taskData = new Param1<DeutschZBattlepassTaskProgressRequest>(new DeutschZBattlepassTaskProgressRequest());
            if (ctx.Read(taskData) && taskData.param1)
            {
                manager.AddTaskProgress(steam64, name, taskData.param1.TaskId, taskData.param1.Amount);
                manager.SendSyncToPlayer(this);
            }
            return true;
        }

        return false;
    }
}
