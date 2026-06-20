class DeutschZKotHZ_MarkerBridge
{
#ifdef LBmaster_Core
    protected ref LBUniversalServerMarker m_LBMarker;
#endif
    protected string m_Name;
    protected vector m_Position;
    protected int m_Color;
    protected string m_Icon;
    protected float m_Radius;
    protected int m_RadiusColor;
    protected bool m_RadiusStriked;
    protected bool m_DisplayMap;
    protected bool m_Display3D;
    protected bool m_Active;
    protected bool m_NoProviderLogged;

    void DeutschZKotHZ_MarkerBridge()
    {
        m_Name = "";
        m_Position = vector.Zero;
        m_Color = ARGB(255, 255, 0, 0);
        m_Icon = "";
        m_Radius = 0.0;
        m_RadiusColor = -1;
        m_RadiusStriked = false;
        m_DisplayMap = true;
        m_Display3D = true;
        m_Active = false;
        m_NoProviderLogged = false;
    }

    void ~DeutschZKotHZ_MarkerBridge()
    {
        Remove();
    }

    void CreateOrUpdate(string name, vector position, int color, string icon)
    {
        m_Name = name;
        m_Position = position;
        m_Color = color;
        m_Icon = icon;
        m_RadiusStriked = false;
        m_DisplayMap = true;
        m_Display3D = true;

#ifdef LBmaster_Core
        if (m_LBMarker)
        {
            ApplyCachedValues();
            m_Active = true;
            return;
        }

        m_LBMarker = GetElevatorMission().CreateServerMarker(m_Name, m_Position, m_Color, m_Icon, m_DisplayMap, m_Display3D);
        if (m_LBMarker)
        {
            ApplyCachedValues();
            m_Active = true;
            Print("[DeutschZ_KotHZ] LB marker bridge created marker: " + m_Name);
            return;
        }
#endif

        m_Active = false;
        LogNoProviderOnce();
    }

    void UpdateName(string name)
    {
        m_Name = name;
#ifdef LBmaster_Core
        if (m_LBMarker)
            m_LBMarker.SetName(m_Name);
#endif
    }

    void UpdatePosition(vector position)
    {
        m_Position = position;
#ifdef LBmaster_Core
        if (m_LBMarker)
            m_LBMarker.SetPosition(m_Position);
#endif
    }

    void UpdateColor(int color)
    {
        m_Color = color;
#ifdef LBmaster_Core
        if (m_LBMarker)
            m_LBMarker.SetColor(m_Color);
#endif
    }

    void UpdateIcon(string icon)
    {
        m_Icon = icon;
#ifdef LBmaster_Core
        if (m_LBMarker)
            m_LBMarker.SetIcon(m_Icon);
#endif
    }

    void UpdateRadius(float radius, int radiusColor)
    {
        m_Radius = radius;
        m_RadiusColor = radiusColor;
        m_RadiusStriked = false;
#ifdef LBmaster_Core
        if (m_LBMarker)
            m_LBMarker.SetRadius(m_Radius, m_RadiusColor, m_RadiusStriked);
#endif
    }

    void Remove()
    {
#ifdef LBmaster_Core
        if (m_LBMarker)
            Print("[DeutschZ_KotHZ] LB marker bridge removed marker: " + m_Name);

        m_LBMarker = null;
#endif
        m_Active = false;
    }

    bool IsActive()
    {
        return m_Active;
    }

    protected void ApplyCachedValues()
    {
#ifdef LBmaster_Core
        if (!m_LBMarker)
            return;

        m_LBMarker.SetName(m_Name);
        m_LBMarker.SetPosition(m_Position);
        m_LBMarker.SetColor(m_Color);
        m_LBMarker.SetIcon(m_Icon);
        m_LBMarker.SetRadius(m_Radius, m_RadiusColor, m_RadiusStriked);
#endif
    }

    protected void LogNoProviderOnce()
    {
        if (m_NoProviderLogged)
            return;

        Print("[DeutschZ_KotHZ] LB marker bridge has no active LBmaster_Core provider. Event continues without external map marker.");
        m_NoProviderLogged = true;
    }
}
