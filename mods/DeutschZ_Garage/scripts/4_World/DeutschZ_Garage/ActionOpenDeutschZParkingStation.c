class ActionOpenDeutschZParkingStation: ActionInteractBase
{
    override void CreateConditionComponents()
    {
        m_ConditionItem = new CCINone;
        m_ConditionTarget = new CCTCursor;
    }

    override string GetText()
    {
        return "Open Parking Station";
    }

    override bool ActionCondition(PlayerBase player, ActionTarget target, ItemBase item)
    {
        if (!player || !target || !target.GetObject()) {
            return false;
        }

        string targetType = target.GetObject().GetType();
        if (targetType != "DeutschZ_ParkingStation" && targetType != "DeutschZ_Garage_Sign") {
            return false;
        }

        if (GetGame().IsClient() && GetGame().GetUIManager() && GetGame().GetUIManager().GetMenu()) {
            return false;
        }

        return true;
    }

    override void OnExecuteClient(ActionData action_data)
    {
        GetGame().RPCSingleParam(action_data.m_Target.GetObject(), DeutschZGarageRPCs.DEUTSCHZ_GARAGE_SYNC, new Param1<bool>(true), true);
    }
}
