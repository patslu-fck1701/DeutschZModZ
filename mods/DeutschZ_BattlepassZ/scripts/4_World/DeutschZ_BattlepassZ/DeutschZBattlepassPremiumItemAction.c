class ActionDeutschZBattlepassActivatePremiumItem: ActionInteractBase
{
    void ActionDeutschZBattlepassActivatePremiumItem()
    {
        m_CommandUID = DayZPlayerConstants.CMD_ACTIONMOD_INTERACTONCE;
        m_StanceMask = DayZPlayerConstants.STANCEMASK_ERECT | DayZPlayerConstants.STANCEMASK_CROUCH;
        m_HUDCursorIcon = CursorIcons.CloseHood;
    }

    override string GetText()
    {
        DeutschZBattlepassManager manager = DeutschZBattlepassRuntime.GetManager();
        if (manager)
        {
            return manager.GetPremiumItemActionText();
        }
        return "Activate Premium";
    }

    override bool ActionCondition(PlayerBase player, ActionTarget target, ItemBase item)
    {
        if (!player || !item)
        {
            return false;
        }

        string itemClass = item.GetType();
        if (itemClass == "Chemlight_Red")
        {
            return true;
        }
        if (itemClass == "ABP_PremiumCoin_7Day")
        {
            return true;
        }
        if (itemClass == "ABP_PremiumCoin_30Day")
        {
            return true;
        }

        DeutschZBattlepassManager manager = DeutschZBattlepassRuntime.GetManager();
        if (manager && manager.IsPremiumItemClass(itemClass))
        {
            return true;
        }
        return false;
    }

    override void OnExecuteServer(ActionData action_data)
    {
        if (!action_data)
        {
            return;
        }
        PlayerBase player = PlayerBase.Cast(action_data.m_Player);
        ItemBase item = ItemBase.Cast(action_data.m_MainItem);
        DeutschZBattlepassManager manager = DeutschZBattlepassRuntime.GetManager();
        if (manager)
        {
            manager.ActivatePremiumItem(player, item);
        }
    }
}

modded class ItemBase
{
    override void SetActions()
    {
        super.SetActions();
        AddAction(ActionDeutschZBattlepassActivatePremiumItem);
    }
}
