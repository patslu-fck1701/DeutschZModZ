class DeutschZGroupsCreateGroupPopup extends UIScriptedMenu
{
    protected Widget m_Root;
    protected EditBoxWidget m_NameInput;
    protected EditBoxWidget m_TagInput;
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
        m_Root = GetGame().GetWorkspace().CreateWidgets(DeutschZGroupsConstants.LAYOUT_CREATE_GROUP_POPUP);
        if (!m_Root)
        {
            return NULL;
        }

        m_NameInput = EditBoxWidget.Cast(m_Root.FindAnyWidget("DZG_GroupNameInput"));
        m_TagInput = EditBoxWidget.Cast(m_Root.FindAnyWidget("DZG_GroupTagInput"));
        m_Info = TextWidget.Cast(m_Root.FindAnyWidget("DZG_Info"));
        m_ConfirmButton = ButtonWidget.Cast(m_Root.FindAnyWidget("DZG_CreateConfirm"));
        m_CancelButton = ButtonWidget.Cast(m_Root.FindAnyWidget("DZG_CreateCancel"));

        if (m_NameInput)
        {
            m_NameInput.SetText("Meine Gruppe");
        }
        if (m_TagInput)
        {
            m_TagInput.SetText("DZG");
        }
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
            SendCreateRequest();
            return true;
        }

        return super.OnClick(w, x, y, button);
    }

    protected void SendCreateRequest()
    {
        PlayerBase player = PlayerBase.Cast(GetGame().GetPlayer());
        if (!player)
        {
            SetInfo("Kein Spieler gefunden.");
            return;
        }

        string groupName = "";
        string groupTag = "";
        if (m_NameInput)
        {
            groupName = m_NameInput.GetText();
        }
        if (m_TagInput)
        {
            groupTag = m_TagInput.GetText();
        }

        if (groupName == "" || groupName == "Gruppenname")
        {
            SetInfo("Bitte Gruppennamen eintragen.");
            return;
        }
        if (groupTag == "" || groupTag == "TAG")
        {
            SetInfo("Bitte Gruppen-Tag eintragen.");
            return;
        }

        ref DeutschZGroupCreateRequest request = new DeutschZGroupCreateRequest();
        request.Name = groupName;
        request.Tag = groupTag;
        GetGame().RPCSingleParam(player, DeutschZGroupsRPC.GROUP_CREATE, new Param1<DeutschZGroupCreateRequest>(request), true);

        if (m_ParentMenu)
        {
            m_ParentMenu.SetStatus("Gruppe erstellen an Server gesendet: " + groupTag);
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
