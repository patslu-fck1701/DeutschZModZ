/*
DeutschZ ModZ
Eigenstaendige Implementierung fuer DeutschZ.
Autor/Eigentuemer: Patrick Sluzalek / fck1701.
Projekt: DeutschZ.
Modul: DeutschZ_ConvoyZ.
Zweck der Datei: Eigene serverseitige Blackbox-/Hack-Interaktion.
Quellen-/Konzeptnachweis: Eigene DeutschZ-Implementierung; DayZ/CF/Expansion werden nur als Laufzeit-Abhaengigkeit/API genutzt.
Keine direkte Codeuebernahme aus Drittquellen.
*/

class DeutschZConvoyZActionHackBlackboxCB : ActionContinuousBaseCB
{
    override void CreateActionComponent()
    {
        m_ActionData.m_ActionComponent = new CAContinuousTime(120.0);
    }
}

class DeutschZConvoyZActionHackBlackbox : ActionContinuousBase
{
    void DeutschZConvoyZActionHackBlackbox()
    {
        m_CallbackClass = DeutschZConvoyZActionHackBlackboxCB;
        m_CommandUID = DayZPlayerConstants.CMD_ACTIONFB_INTERACT;
        m_FullBody = true;
        m_StanceMask = DayZPlayerConstants.STANCEMASK_CROUCH | DayZPlayerConstants.STANCEMASK_ERECT;
        m_Text = "Blackbox entschluesseln";
    }

    override void CreateConditionComponents()
    {
        m_ConditionItem = new CCINone;
        m_ConditionTarget = new CCTNonRuined(3.0);
    }

    override bool ActionCondition(PlayerBase player, ActionTarget target, ItemBase item)
    {
        if (!player || !target) return false;
        Object obj = target.GetObject();
        if (!obj) return false;
        return DeutschZConvoyZ_GetManager().CanHack(player, obj);
    }

    override void OnStartServer(ActionData action_data)
    {
        super.OnStartServer(action_data);
        if (action_data && action_data.m_Player) DeutschZConvoyZ_GetManager().RequestHackStart(action_data.m_Player);
    }

    override void OnEndServer(ActionData action_data)
    {
        super.OnEndServer(action_data);
        if (action_data && action_data.m_Player) DeutschZConvoyZ_GetManager().RequestHackStop(action_data.m_Player);
    }
}

modded class PlayerBase
{
    override void SetActions(out TInputActionMap InputActionMap)
    {
        super.SetActions(InputActionMap);
        AddAction(DeutschZConvoyZActionHackBlackbox, InputActionMap);
    }
}
