class ActionOpenDeutschZATM: ActionInteractBase
{
    override void CreateConditionComponents()
    {
        m_ConditionItem = new CCINone;
        m_ConditionTarget = new CCTCursor;
    }

    override string GetText()
    {
        return "Open DeutschZ ATM";
    }

    override bool ActionCondition(PlayerBase player, ActionTarget target, ItemBase item)
    {
        if (!player || !target || !target.GetObject()) {
            return false;
        }

        if (target.GetObject().GetType() != "DeutschZ_ATM") {
            return false;
        }

        if (GetGame().IsClient() && GetGame().GetUIManager() && GetGame().GetUIManager().GetMenu()) {
            return false;
        }

        return true;
    }

    override void OnExecuteClient(ActionData action_data)
    {
        GetGame().RPCSingleParam(null, DeutschZBankingRPCs.DEUTSCHZ_BANKING_SYNC, new Param1<bool>(true), true);
    }
}
