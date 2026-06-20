class DeutschZGroupsInvitePopup extends UIScriptedMenu
{
    protected Widget m_Root;
    protected TextWidget m_Title;
    protected TextWidget m_Text;
    protected ButtonWidget m_AcceptButton;
    protected ButtonWidget m_DeclineButton;
    protected string m_InviteId;
    protected DeutschZGroupsMapMenu m_ParentMenu;

    void SetParentMenu(DeutschZGroupsMapMenu parentMenu)
    {
        m_ParentMenu = parentMenu;
    }

    override Widget Init()
    {
        m_Root = GetGame().GetWorkspace().CreateWidgets(DeutschZGroupsConstants.LAYOUT_INVITE_POPUP);
        if (!m_Root)
        {
            return NULL;
        }
        m_Title = TextWidget.Cast(m_Root.FindAnyWidget("DZG_PopupTitle"));
        m_Text = TextWidget.Cast(m_Root.FindAnyWidget("DZG_PopupText"));
        m_AcceptButton = ButtonWidget.Cast(m_Root.FindAnyWidget("DZG_AcceptInviteButton"));
        m_DeclineButton = ButtonWidget.Cast(m_Root.FindAnyWidget("DZG_DeclineInviteButton"));
        return m_Root;
    }

    void SetInvite(DeutschZGroupInviteData invite)
    {
        if (!invite)
        {
            return;
        }
        m_InviteId = invite.InviteId;
        if (m_Text)
        {
            m_Text.SetText(invite.InviterName + " hat dich in eine DeutschZ Gruppe eingeladen.");
        }
    }

    override bool OnClick(Widget w, int x, int y, int button)
    {
        if (w == m_AcceptButton)
        {
            SendResponse(true);
            return true;
        }
        if (w == m_DeclineButton)
        {
            SendResponse(false);
            return true;
        }
        return super.OnClick(w, x, y, button);
    }

    protected void SendResponse(bool accept)
    {
        PlayerBase player = PlayerBase.Cast(GetGame().GetPlayer());
        if (!player || m_InviteId == "")
        {
            Close();
            return;
        }

        if (accept)
        {
            GetGame().RPCSingleParam(player, DeutschZGroupsRPC.GROUP_ACCEPT_INVITE, new Param1<string>(m_InviteId), true);
            if (m_ParentMenu)
            {
                m_ParentMenu.SetStatus("Einladung angenommen.");
            }
        }
        else
        {
            GetGame().RPCSingleParam(player, DeutschZGroupsRPC.GROUP_DECLINE_INVITE, new Param1<string>(m_InviteId), true);
            if (m_ParentMenu)
            {
                m_ParentMenu.SetStatus("Einladung abgelehnt.");
            }
        }

        if (m_ParentMenu)
        {
            m_ParentMenu.RequestFullSync();
        }
        Close();
    }
}
