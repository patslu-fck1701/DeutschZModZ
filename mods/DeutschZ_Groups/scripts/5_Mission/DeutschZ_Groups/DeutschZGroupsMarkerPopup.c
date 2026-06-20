class DeutschZGroupsMarkerPopup extends UIScriptedMenu
{
    protected Widget m_Root;
    protected EditBoxWidget m_NameInput;
    protected EditBoxWidget m_IconInput;
    protected EditBoxWidget m_RadiusInput;
    protected TextWidget m_Info;
    protected ButtonWidget m_GroupButton;
    protected ButtonWidget m_PrivateButton;
    protected ButtonWidget m_CancelButton;
    protected DeutschZGroupsMapMenu m_ParentMenu;
    protected vector m_MarkerPosition;
    protected string m_DefaultIcon;
    protected string m_DefaultName;
    protected int m_DefaultMarkerType;

    void SetParentMenu(DeutschZGroupsMapMenu parentMenu)
    {
        m_ParentMenu = parentMenu;
    }

    void SetMarkerDefaults(vector position, string iconKey, string markerName, int markerType)
    {
        m_MarkerPosition = position;
        m_DefaultIcon = iconKey;
        m_DefaultName = markerName;
        m_DefaultMarkerType = markerType;
    }

    override Widget Init()
    {
        m_Root = GetGame().GetWorkspace().CreateWidgets(DeutschZGroupsConstants.LAYOUT_MARKER_POPUP);
        if (!m_Root)
        {
            return NULL;
        }

        m_NameInput = EditBoxWidget.Cast(m_Root.FindAnyWidget("DZG_MarkerNameInput"));
        m_IconInput = EditBoxWidget.Cast(m_Root.FindAnyWidget("DZG_MarkerIconInput"));
        m_RadiusInput = EditBoxWidget.Cast(m_Root.FindAnyWidget("DZG_MarkerRadiusInput"));
        m_Info = TextWidget.Cast(m_Root.FindAnyWidget("DZG_Info"));
        m_GroupButton = ButtonWidget.Cast(m_Root.FindAnyWidget("DZG_SaveGroupMarker"));
        m_PrivateButton = ButtonWidget.Cast(m_Root.FindAnyWidget("DZG_SavePrivateMarker"));
        m_CancelButton = ButtonWidget.Cast(m_Root.FindAnyWidget("DZG_MarkerCancel"));

        if (m_NameInput)
        {
            m_NameInput.SetText(m_DefaultName);
        }
        if (m_IconInput)
        {
            m_IconInput.SetText(m_DefaultIcon);
        }
        if (m_RadiusInput)
        {
            m_RadiusInput.SetText("0");
        }
        SetInfo("Position: " + m_MarkerPosition.ToString());
        return m_Root;
    }

    override bool OnClick(Widget w, int x, int y, int button)
    {
        if (w == m_CancelButton)
        {
            Close();
            return true;
        }
        if (w == m_GroupButton)
        {
            SendMarker(false);
            return true;
        }
        if (w == m_PrivateButton)
        {
            SendMarker(true);
            return true;
        }
        return super.OnClick(w, x, y, button);
    }

    protected void SendMarker(bool privateMarker)
    {
        PlayerBase player = PlayerBase.Cast(GetGame().GetPlayer());
        if (!player)
        {
            SetInfo("Kein Spieler gefunden.");
            return;
        }

        string markerName = m_DefaultName;
        string iconKey = m_DefaultIcon;
        if (m_NameInput)
        {
            markerName = m_NameInput.GetText();
        }
        if (m_IconInput)
        {
            iconKey = m_IconInput.GetText();
        }
        if (markerName == "" || markerName == "Markername")
        {
            markerName = m_DefaultName;
        }
        if (iconKey == "" || iconKey == "Icon")
        {
            iconKey = m_DefaultIcon;
        }

        ref DeutschZGroupMarkerRequest request = new DeutschZGroupMarkerRequest();
        request.Marker.Name = markerName;
        request.Marker.Icon = iconKey;
        request.Marker.Position = m_MarkerPosition;
        request.Marker.ColorR = 255;
        request.Marker.ColorG = 0;
        request.Marker.ColorB = 0;
        request.Marker.ShowMap = 1;
        request.Marker.Show3D = 0;
        request.Marker.ShowGPS = 0;
        if (privateMarker)
        {
            request.Marker.MarkerType = DeutschZGroupMarkerType.PRIVATE_MARKER;
            GetGame().RPCSingleParam(player, DeutschZGroupsRPC.PRIVATE_MARKER_SAVE, new Param1<DeutschZGroupMarkerRequest>(request), true);
        }
        else
        {
            request.Marker.MarkerType = m_DefaultMarkerType;
            GetGame().RPCSingleParam(player, DeutschZGroupsRPC.GROUP_ADD_MARKER, new Param1<DeutschZGroupMarkerRequest>(request), true);
        }

        if (m_ParentMenu)
        {
            m_ParentMenu.SetStatus("Marker an Server gesendet: " + markerName);
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
