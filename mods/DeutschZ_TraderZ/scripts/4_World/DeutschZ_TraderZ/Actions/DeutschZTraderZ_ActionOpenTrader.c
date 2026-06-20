class DeutschZTraderZ_ActionOpenTrader : ActionInteractBase
{
    void DeutschZTraderZ_ActionOpenTrader()
    {
        m_CommandUID = DayZPlayerConstants.CMD_ACTIONMOD_ATTACHITEM;
        m_StanceMask = DayZPlayerConstants.STANCEMASK_ERECT | DayZPlayerConstants.STANCEMASK_CROUCH;
        m_Text = "Open TraderZ";
    }

    override void CreateConditionComponents()
    {
        m_ConditionTarget = new CCTObject(6);
        m_ConditionItem = new CCINone;
    }

    override bool ActionCondition(PlayerBase player, ActionTarget target, ItemBase item)
    {
        if (!player || !target || !target.GetObject())
            return false;
        PlayerBase trader = PlayerBase.Cast(target.GetObject());
        if (!trader)
            return false;
        if (!trader.DeutschZTraderZ_IsTrader())
            return false;
        if (trader.DeutschZTraderZ_IsP2PTrader() || trader.DeutschZTraderZ_IsDeliveryTrader())
            return false;
        return true;
    }

    override void OnStartServer(ActionData action_data)
    {
        if (!action_data || !action_data.m_Player || !action_data.m_Target || !action_data.m_Target.GetObject())
            return;
        PlayerBase trader = PlayerBase.Cast(action_data.m_Target.GetObject());
        if (!trader)
            return;
        DeutschZTraderZ_TraderService.OpenTraderMenu(action_data.m_Player, trader.DeutschZTraderZ_GetTraderIndex());
    }
}
