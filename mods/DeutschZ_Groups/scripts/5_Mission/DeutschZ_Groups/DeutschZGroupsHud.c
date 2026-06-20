class DeutschZGroupsGpsHud
{
    protected Widget m_Root;
    protected TextWidget m_Text;

    void Show()
    {
        if (!m_Root)
        {
            m_Root = GetGame().GetWorkspace().CreateWidgets(DeutschZGroupsConstants.LAYOUT_GPS_HUD);
            m_Text = TextWidget.Cast(m_Root.FindAnyWidget("DZG_GPSText"));
        }
        if (m_Root)
        {
            m_Root.Show(true);
        }
        Update();
    }

    void Hide()
    {
        if (m_Root)
        {
            m_Root.Show(false);
        }
    }

    void Update()
    {
        if (!m_Text)
        {
            return;
        }
        PlayerBase player = PlayerBase.Cast(GetGame().GetPlayer());
        if (!player)
        {
            m_Text.SetText("DeutschZ GPS: kein Spieler");
            return;
        }
        vector pos = player.GetPosition();
        m_Text.SetText(string.Format("GPS X:%1 Z:%2", pos[0], pos[2]));
    }
}

class DeutschZGroupsCompassHud
{
    protected Widget m_Root;
    protected TextWidget m_Text;

    void Show()
    {
        if (!m_Root)
        {
            m_Root = GetGame().GetWorkspace().CreateWidgets(DeutschZGroupsConstants.LAYOUT_COMPASS_HUD);
            m_Text = TextWidget.Cast(m_Root.FindAnyWidget("DZG_CompassText"));
        }
        if (m_Root)
        {
            m_Root.Show(true);
        }
        Update();
    }

    void Hide()
    {
        if (m_Root)
        {
            m_Root.Show(false);
        }
    }

    void Update()
    {
        if (!m_Text)
        {
            return;
        }
        PlayerBase player = PlayerBase.Cast(GetGame().GetPlayer());
        if (!player)
        {
            m_Text.SetText("N | NE | E | SE | S | SW | W | NW");
            return;
        }
        vector direction = player.GetDirection();
        m_Text.SetText("DeutschZ Compass | Dir " + direction.ToString());
    }
}
