modded class MissionGameplay
{
    protected ref DeutschZBattlepassMenu m_DeutschZBattlepassMenu;

    override void OnInit()
    {
        super.OnInit();
        DeutschZBattlepassClientState.Init();
        Print("[DeutschZ_BattlepassZ] Client initialized.");
    }

    override void OnUpdate(float timeslice)
    {
        super.OnUpdate(timeslice);
        DeutschZBattlepass_HandleInputs();
    }

    protected void DeutschZBattlepass_HandleInputs()
    {
        if (!GetUApi())
        {
            return;
        }

        UAInput openInput = GetUApi().GetInputByName("UADZBPOpenMenu");
        if (openInput && openInput.LocalPress())
        {
            DeutschZBattlepass_ToggleMenu();
            return;
        }

        UAInput syncInput = GetUApi().GetInputByName("UADZBPRequestSync");
        if (syncInput && syncInput.LocalPress())
        {
            DeutschZBattlepass_RequestSync();
            return;
        }

        UAInput claimInput = GetUApi().GetInputByName("UADZBPClaimFirst");
        if (claimInput && claimInput.LocalPress())
        {
            DeutschZBattlepass_ClaimFirstAvailable();
            return;
        }
    }

    void DeutschZBattlepass_ToggleMenu()
    {
        if (m_DeutschZBattlepassMenu && GetGame().GetUIManager().GetMenu() == m_DeutschZBattlepassMenu)
        {
            m_DeutschZBattlepassMenu.Close();
            return;
        }
        if (GetGame().GetUIManager().GetMenu() || GetGame().GetUIManager().IsCursorVisible())
        {
            return;
        }
        DeutschZBattlepass_OpenMenu();
    }

    void DeutschZBattlepass_OpenMenu()
    {
        DeutschZBattlepass_RequestSync();
        m_DeutschZBattlepassMenu = new DeutschZBattlepassMenu();
        GetGame().GetUIManager().ShowScriptedMenu(m_DeutschZBattlepassMenu, NULL);
    }

    void DeutschZBattlepass_RequestSync()
    {
        PlayerBase player = PlayerBase.Cast(GetGame().GetPlayer());
        if (!player)
        {
            return;
        }
        GetGame().RPCSingleParam(player, DeutschZBattlepassRPC.REQUEST_SYNC, new Param1<int>(0), true);
    }

    void DeutschZBattlepass_ClaimFirstAvailable()
    {
        DeutschZBattlepassSyncPacket packet = DeutschZBattlepassClientState.GetSync();
        if (!packet || !packet.Player || !packet.FreeConfig)
        {
            return;
        }
        int i;
        for (i = 0; i < packet.FreeConfig.FreeRewards.Count(); i++)
        {
            DeutschZBattlepassRewardData reward = packet.FreeConfig.FreeRewards.Get(i);
            if (reward && packet.Player.Level >= reward.Level && !packet.Player.HasClaimed(reward.RewardId, 0))
            {
                DeutschZBattlepass_SendClaim(reward.RewardId, 0);
                return;
            }
        }
        if (packet.Player.Premium == 1 && packet.PremiumConfig && packet.PremiumConfig.PremiumRewards)
        {
            for (i = 0; i < packet.PremiumConfig.PremiumRewards.Count(); i++)
            {
                DeutschZBattlepassRewardData premiumReward = packet.PremiumConfig.PremiumRewards.Get(i);
                if (premiumReward && packet.Player.Level >= premiumReward.Level && !packet.Player.HasClaimed(premiumReward.RewardId, 1))
                {
                    DeutschZBattlepass_SendClaim(premiumReward.RewardId, 1);
                    return;
                }
            }
        }
    }

    void DeutschZBattlepass_SendClaim(string rewardId, int premium)
    {
        PlayerBase player = PlayerBase.Cast(GetGame().GetPlayer());
        if (!player || rewardId == "")
        {
            return;
        }
        ref DeutschZBattlepassClaimRequest request = new DeutschZBattlepassClaimRequest();
        request.RewardId = rewardId;
        request.Premium = premium;
        GetGame().RPCSingleParam(player, DeutschZBattlepassRPC.CLAIM_REWARD, new Param1<DeutschZBattlepassClaimRequest>(request), true);
    }
}
