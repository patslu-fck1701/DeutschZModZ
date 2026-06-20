class DeutschZBattlepassMenu extends UIScriptedMenu
{
    protected TextWidget m_Title;
    protected TextWidget m_Status;
    protected TextWidget m_Progress;
    protected TextListboxWidget m_FreeList;
    protected TextListboxWidget m_PremiumList;
    protected ButtonWidget m_CloseButton;
    protected ButtonWidget m_SyncButton;
    protected ButtonWidget m_ClaimFreeButton;
    protected ButtonWidget m_ClaimPremiumButton;
    protected string m_SelectedFreeReward;
    protected string m_SelectedPremiumReward;

    override Widget Init()
    {
        layoutRoot = GetGame().GetWorkspace().CreateWidgets("DeutschZ_BattlepassZ/gui/layouts/DeutschZBattlepassMenu.layout");
        m_Title = TextWidget.Cast(layoutRoot.FindAnyWidget("DZBP_Title"));
        m_Status = TextWidget.Cast(layoutRoot.FindAnyWidget("DZBP_Status"));
        m_Progress = TextWidget.Cast(layoutRoot.FindAnyWidget("DZBP_Progress"));
        m_FreeList = TextListboxWidget.Cast(layoutRoot.FindAnyWidget("DZBP_FreeList"));
        m_PremiumList = TextListboxWidget.Cast(layoutRoot.FindAnyWidget("DZBP_PremiumList"));
        m_CloseButton = ButtonWidget.Cast(layoutRoot.FindAnyWidget("DZBP_Close"));
        m_SyncButton = ButtonWidget.Cast(layoutRoot.FindAnyWidget("DZBP_Sync"));
        m_ClaimFreeButton = ButtonWidget.Cast(layoutRoot.FindAnyWidget("DZBP_ClaimFree"));
        m_ClaimPremiumButton = ButtonWidget.Cast(layoutRoot.FindAnyWidget("DZBP_ClaimPremium"));
        m_SelectedFreeReward = "";
        m_SelectedPremiumReward = "";
        RefreshView();
        return layoutRoot;
    }

    override void OnShow()
    {
        super.OnShow();
        PPEffects.SetBlurMenu(0.35);
        GetGame().GetUIManager().ShowCursor(true);
        GetGame().GetInput().ChangeGameFocus(1);
        SetFocus(layoutRoot);
        RefreshView();
    }

    override void OnHide()
    {
        super.OnHide();
        PPEffects.SetBlurMenu(0.0);
        GetGame().GetUIManager().ShowCursor(false);
        GetGame().GetInput().ResetGameFocus();
    }

    void RefreshView()
    {
        DeutschZBattlepassSyncPacket packet = DeutschZBattlepassClientState.GetSync();
        if (!packet)
        {
            return;
        }
        if (m_Title && packet.FreeConfig)
        {
            m_Title.SetText("DeutschZ BattlepassZ - " + packet.FreeConfig.SeasonName);
        }
        if (m_Status)
        {
            m_Status.SetText("O = open | CTRL+O = sync | CTRL+B = claim first available");
        }
        if (m_Progress && packet.Player && packet.FreeConfig)
        {
            int currentLevelXP = (packet.Player.Level - 1) * packet.FreeConfig.XpPerLevel;
            int nextLevelXP = packet.Player.Level * packet.FreeConfig.XpPerLevel;
            string premium = "Free";
            if (packet.Player.Premium == 1)
            {
                premium = "Premium";
            }
            m_Progress.SetText("Level " + packet.Player.Level.ToString() + " | XP " + packet.Player.XP.ToString() + " / " + nextLevelXP.ToString() + " | " + premium);
        }
        FillFreeList(packet);
        FillPremiumList(packet);
    }

    protected void FillFreeList(DeutschZBattlepassSyncPacket packet)
    {
        if (!m_FreeList)
        {
            return;
        }
        m_FreeList.ClearItems();
        if (!packet || !packet.FreeConfig || !packet.FreeConfig.FreeRewards)
        {
            return;
        }
        int i;
        for (i = 0; i < packet.FreeConfig.FreeRewards.Count(); i++)
        {
            DeutschZBattlepassRewardData reward = packet.FreeConfig.FreeRewards.Get(i);
            if (reward)
            {
                string claimed = "open";
                if (packet.Player && packet.Player.HasClaimed(reward.RewardId, 0))
                {
                    claimed = "claimed";
                }
                m_FreeList.AddItem("L" + reward.Level.ToString() + " | " + reward.DisplayName + " | " + claimed, reward, 0);
            }
        }
    }

    protected void FillPremiumList(DeutschZBattlepassSyncPacket packet)
    {
        if (!m_PremiumList)
        {
            return;
        }
        m_PremiumList.ClearItems();
        if (!packet || !packet.PremiumConfig || !packet.PremiumConfig.PremiumRewards)
        {
            return;
        }
        int i;
        for (i = 0; i < packet.PremiumConfig.PremiumRewards.Count(); i++)
        {
            DeutschZBattlepassRewardData reward = packet.PremiumConfig.PremiumRewards.Get(i);
            if (reward)
            {
                string claimed = "open";
                if (packet.Player && packet.Player.HasClaimed(reward.RewardId, 1))
                {
                    claimed = "claimed";
                }
                m_PremiumList.AddItem("L" + reward.Level.ToString() + " | " + reward.DisplayName + " | " + claimed, reward, 0);
            }
        }
    }

    override bool OnClick(Widget w, int x, int y, int button)
    {
        if (w == m_CloseButton)
        {
            Close();
            return true;
        }
        if (w == m_SyncButton)
        {
            RequestSync();
            return true;
        }
        if (w == m_ClaimFreeButton)
        {
            ClaimSelectedFree();
            return true;
        }
        if (w == m_ClaimPremiumButton)
        {
            ClaimSelectedPremium();
            return true;
        }
        return super.OnClick(w, x, y, button);
    }

    override bool OnChange(Widget w, int x, int y, bool finished)
    {
        if (w == m_FreeList)
        {
            int row = m_FreeList.GetSelectedRow();
            DeutschZBattlepassRewardData reward;
            m_FreeList.GetItemData(row, 0, reward);
            if (reward)
            {
                m_SelectedFreeReward = reward.RewardId;
            }
            return true;
        }
        if (w == m_PremiumList)
        {
            int premiumRow = m_PremiumList.GetSelectedRow();
            DeutschZBattlepassRewardData premiumReward;
            m_PremiumList.GetItemData(premiumRow, 0, premiumReward);
            if (premiumReward)
            {
                m_SelectedPremiumReward = premiumReward.RewardId;
            }
            return true;
        }
        return super.OnChange(w, x, y, finished);
    }

    protected void RequestSync()
    {
        PlayerBase player = PlayerBase.Cast(GetGame().GetPlayer());
        if (!player)
        {
            return;
        }
        GetGame().RPCSingleParam(player, DeutschZBattlepassRPC.REQUEST_SYNC, new Param1<int>(0), true);
        if (m_Status)
        {
            m_Status.SetText("Sync requested...");
        }
    }

    protected void ClaimSelectedFree()
    {
        if (m_SelectedFreeReward == "")
        {
            if (m_Status)
            {
                m_Status.SetText("Select a free reward first.");
            }
            return;
        }
        SendClaim(m_SelectedFreeReward, 0);
    }

    protected void ClaimSelectedPremium()
    {
        if (m_SelectedPremiumReward == "")
        {
            if (m_Status)
            {
                m_Status.SetText("Select a premium reward first.");
            }
            return;
        }
        SendClaim(m_SelectedPremiumReward, 1);
    }

    protected void SendClaim(string rewardId, int premium)
    {
        PlayerBase player = PlayerBase.Cast(GetGame().GetPlayer());
        if (!player)
        {
            return;
        }
        ref DeutschZBattlepassClaimRequest request = new DeutschZBattlepassClaimRequest();
        request.RewardId = rewardId;
        request.Premium = premium;
        GetGame().RPCSingleParam(player, DeutschZBattlepassRPC.CLAIM_REWARD, new Param1<DeutschZBattlepassClaimRequest>(request), true);
        if (m_Status)
        {
            m_Status.SetText("Claim sent: " + rewardId);
        }
    }
}
