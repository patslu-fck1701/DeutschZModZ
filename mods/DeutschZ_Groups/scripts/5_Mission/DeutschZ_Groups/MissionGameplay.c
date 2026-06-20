modded class MissionGameplay
{
    protected ref DeutschZGroupsMapMenu m_DeutschZGroupsMapMenu;
    protected ref DeutschZGroupsGpsHud m_DeutschZGroupsGpsHud;
    protected ref DeutschZGroupsCompassHud m_DeutschZGroupsCompassHud;
    protected int m_DeutschZGroupsLastHudUpdate;
    protected int m_DeutschZGroupsGpsVisible;
    protected int m_DeutschZGroupsCompassVisible;

    override void OnInit()
    {
        super.OnInit();
        DeutschZGroupsClientState.Init();
        m_DeutschZGroupsGpsHud = new DeutschZGroupsGpsHud();
        m_DeutschZGroupsCompassHud = new DeutschZGroupsCompassHud();
        m_DeutschZGroupsLastHudUpdate = 0;
        m_DeutschZGroupsGpsVisible = 0;
        m_DeutschZGroupsCompassVisible = 0;
        Print("[DeutschZ_Groups] Client mission initialized. UI layer v0.5.1 LB-style inputs and playable map ready.");
    }

    override void OnUpdate(float timeslice)
    {
        super.OnUpdate(timeslice);
        DeutschZGroups_HandleInputs();

        int now = GetGame().GetTime();
        if (now - m_DeutschZGroupsLastHudUpdate > 1000)
        {
            if (m_DeutschZGroupsGpsHud)
            {
                m_DeutschZGroupsGpsHud.Update();
            }
            if (m_DeutschZGroupsCompassHud)
            {
                m_DeutschZGroupsCompassHud.Update();
            }
            m_DeutschZGroupsLastHudUpdate = now;
        }
    }

    protected void DeutschZGroups_HandleInputs()
    {
        if (!GetUApi())
        {
            return;
        }

        int openRequested = 0;

        UAInput openMapInput = GetUApi().GetInputByName("UADZGGroupOpenMap");
        if (openMapInput && openMapInput.LocalPress())
        {
            openRequested = 1;
        }

        UAInput openGroupInput = GetUApi().GetInputByName("UADZGGroupOpenMapGroup");
        if (openGroupInput && openGroupInput.LocalPress())
        {
            openRequested = 1;
        }

        if (!openMapInput && !openGroupInput)
        {
            UAInput vanillaMapInput = GetUApi().GetInputByName("UAMap");
            if (vanillaMapInput && vanillaMapInput.LocalPress())
            {
                openRequested = 1;
            }
        }

        if (openRequested == 1)
        {
            DeutschZGroups_ToggleMapMenu();
            return;
        }

        UAInput pingInput = GetUApi().GetInputByName("UADZGGroupPing");
        if (pingInput && pingInput.LocalPress())
        {
            if (DeutschZGroups_IsNoBlockingMenuOpen())
            {
                DeutschZGroups_SendQuickPing();
            }
            return;
        }

        UAInput acceptInput = GetUApi().GetInputByName("UADZGGroupAcceptInvite");
        if (acceptInput && acceptInput.LocalPress())
        {
            if (DeutschZGroups_IsNoBlockingMenuOpen())
            {
                DeutschZGroups_AcceptFirstInvite();
            }
            return;
        }

        UAInput gpsInput = GetUApi().GetInputByName("UADZGGroupToggleGPS");
        if (gpsInput && gpsInput.LocalPress())
        {
            if (DeutschZGroups_IsNoBlockingMenuOpen())
            {
                DeutschZGroups_ToggleGPS();
            }
            return;
        }

        UAInput compassInput = GetUApi().GetInputByName("UADZGGroupToggleCompass");
        if (compassInput && compassInput.LocalPress())
        {
            if (DeutschZGroups_IsNoBlockingMenuOpen())
            {
                DeutschZGroups_ToggleCompass();
            }
            return;
        }
    }

    protected bool DeutschZGroups_IsNoBlockingMenuOpen()
    {
        if (GetGame().GetUIManager().GetMenu())
        {
            return false;
        }
        if (GetGame().GetUIManager().IsCursorVisible())
        {
            return false;
        }
        return true;
    }

    void DeutschZGroups_ToggleMapMenu()
    {
        if (m_DeutschZGroupsMapMenu && GetGame().GetUIManager().GetMenu() == m_DeutschZGroupsMapMenu)
        {
            m_DeutschZGroupsMapMenu.Close();
            return;
        }

        if (GetGame().GetUIManager().GetMenu() || GetGame().GetUIManager().IsCursorVisible())
        {
            return;
        }

        DeutschZGroups_OpenMapMenu();
    }

    void DeutschZGroups_OpenMapMenu()
    {
        DeutschZGroups_RequestSync();
        m_DeutschZGroupsMapMenu = new DeutschZGroupsMapMenu();
        GetGame().GetUIManager().ShowScriptedMenu(m_DeutschZGroupsMapMenu, NULL);
    }

    void DeutschZGroups_CloseMapMenu()
    {
        if (m_DeutschZGroupsMapMenu)
        {
            m_DeutschZGroupsMapMenu.Close();
        }
    }

    void DeutschZGroups_RequestSync()
    {
        PlayerBase player = PlayerBase.Cast(GetGame().GetPlayer());
        if (!player)
        {
            return;
        }
        GetGame().RPCSingleParam(player, DeutschZGroupsRPC.API_REFRESH, new Param1<int>(0), true);
    }

    void DeutschZGroups_SendQuickPing()
    {
        PlayerBase player = PlayerBase.Cast(GetGame().GetPlayer());
        if (!player)
        {
            return;
        }

        ref DeutschZGroupMarkerRequest request = new DeutschZGroupMarkerRequest();
        request.Marker.Name = "Ping";
        request.Marker.Position = player.GetPosition();
        request.Marker.MarkerType = DeutschZGroupMarkerType.GROUP_PING;
        request.Marker.Icon = DeutschZGroupsMarkerIcons.GROUP_PING;
        GetGame().RPCSingleParam(player, DeutschZGroupsRPC.GROUP_PING, new Param1<DeutschZGroupMarkerRequest>(request), true);
    }

    void DeutschZGroups_AcceptFirstInvite()
    {
        DeutschZGroupSyncPacket packet = DeutschZGroupsClientState.GetSync();
        if (!packet || !packet.Invites || packet.Invites.Count() == 0)
        {
            return;
        }
        DeutschZGroupInviteData invite = packet.Invites.Get(0);
        if (!invite)
        {
            return;
        }
        PlayerBase player = PlayerBase.Cast(GetGame().GetPlayer());
        if (!player)
        {
            return;
        }
        GetGame().RPCSingleParam(player, DeutschZGroupsRPC.GROUP_ACCEPT_INVITE, new Param1<string>(invite.InviteId), true);
    }

    void DeutschZGroups_ShowGPS(bool show)
    {
        if (!m_DeutschZGroupsGpsHud)
        {
            m_DeutschZGroupsGpsHud = new DeutschZGroupsGpsHud();
        }
        if (show)
        {
            m_DeutschZGroupsGpsHud.Show();
        }
        else
        {
            m_DeutschZGroupsGpsHud.Hide();
        }
    }

    void DeutschZGroups_ShowCompass(bool show)
    {
        if (!m_DeutschZGroupsCompassHud)
        {
            m_DeutschZGroupsCompassHud = new DeutschZGroupsCompassHud();
        }
        if (show)
        {
            m_DeutschZGroupsCompassHud.Show();
        }
        else
        {
            m_DeutschZGroupsCompassHud.Hide();
        }
    }

    void DeutschZGroups_ToggleGPS()
    {
        if (m_DeutschZGroupsGpsVisible == 1)
        {
            m_DeutschZGroupsGpsVisible = 0;
            DeutschZGroups_ShowGPS(false);
        }
        else
        {
            m_DeutschZGroupsGpsVisible = 1;
            DeutschZGroups_ShowGPS(true);
        }
    }

    void DeutschZGroups_ToggleCompass()
    {
        if (m_DeutschZGroupsCompassVisible == 1)
        {
            m_DeutschZGroupsCompassVisible = 0;
            DeutschZGroups_ShowCompass(false);
        }
        else
        {
            m_DeutschZGroupsCompassVisible = 1;
            DeutschZGroups_ShowCompass(true);
        }
    }
}
