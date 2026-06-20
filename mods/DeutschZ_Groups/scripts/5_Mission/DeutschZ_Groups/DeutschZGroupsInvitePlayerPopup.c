class DeutschZGroupsInvitePlayerPopup extends UIScriptedMenu
{
    protected Widget m_Root;
    protected EditBoxWidget m_TargetSteamInput;
    protected EditBoxWidget m_TargetNameInput;
    protected TextWidget m_Info;
    protected ButtonWidget m_ConfirmButton;
    protected ButtonWidget m_CancelButton;
    protected DeutschZGroupsMapMenu m_ParentMenu;

    void SetParentMenu(DeutschZGroupsMapMenu parentMenu)
    {
        m_ParentMenu = parentMenu;
    }

    override Widget Init()
    {
        m_Root = GetGame().GetWorkspace().CreateWidgets(DeutschZGroupsConstants.LAYOUT_INVITE_PLAYER_POPUP);
        if (!m_Root)
        {
            return NULL;
        }

        m_TargetSteamInput = EditBoxWidget.Cast(m_Root.FindAnyWidget("DZG_TargetSteamInput"));
        m_TargetNameInput = EditBoxWidget.Cast(m_Root.FindAnyWidget("DZG_TargetNameInput"));
        m_Info = TextWidget.Cast(m_Root.FindAnyWidget("DZG_Info"));
        m_ConfirmButton = ButtonWidget.Cast(m_Root.FindAnyWidget("DZG_InviteConfirm"));
        m_CancelButton = ButtonWidget.Cast(m_Root.FindAnyWidget("DZG_InviteCancel"));
        return m_Root;
    }

    override bool OnClick(Widget w, int x, int y, int button)
    {
        if (w == m_CancelButton)
        {
            Close();
            return true;
        }
        if (w == m_ConfirmButton)
        {
            SendInviteRequest();
            return true;
        }
        return super.OnClick(w, x, y, button);
    }

    protected void SendInviteRequest()
    {
        PlayerBase player = PlayerBase.Cast(GetGame().GetPlayer());
        if (!player)
        {
            SetInfo("Kein Spieler gefunden.");
            return;
        }

        string targetSteam = "";
        string targetName = "";
        if (m_TargetSteamInput)
        {
            targetSteam = m_TargetSteamInput.GetText();
        }
        if (m_TargetNameInput)
        {
            targetName = m_TargetNameInput.GetText();
        }

        if (targetSteam == "" || targetSteam == "Steam64")
        {
            SetInfo("Bitte Steam64 eintragen.");
            return;
        }
        if (targetName == "" || targetName == "Name optional")
        {
            targetName = targetSteam;
        }

        ref DeutschZGroupInviteRequest request = new DeutschZGroupInviteRequest();
        request.TargetSteam64 = targetSteam;
        request.TargetName = targetName;
        GetGame().RPCSingleParam(player, DeutschZGroupsRPC.GROUP_INVITE, new Param1<DeutschZGroupInviteRequest>(request), true);

        if (m_ParentMenu)
        {
            m_ParentMenu.SetStatus("Einladung gesendet an Steam64: " + targetSteam);
            m_ParentMenu.RequestFullSync();
        }
        Close();
    }

    protected void SetInfo(string text)
    {
        if (m_Info)
        {
            m_Info.SetText(text);
        }
    }
}
