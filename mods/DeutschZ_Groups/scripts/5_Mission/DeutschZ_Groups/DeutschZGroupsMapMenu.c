class DeutschZGroupsMapMenu extends UIScriptedMenu
{
    protected Widget m_Root;
    protected MapWidget m_Map;
    protected TextWidget m_GroupHeader;
    protected TextWidget m_GroupInfo;
    protected TextWidget m_StatusText;
    protected TextWidget m_GarageState;
    protected TextWidget m_BankingState;
    protected TextWidget m_SelectedIconText;
    protected GridSpacerWidget m_MemberGrid;
    protected GridSpacerWidget m_MarkerGrid;
    protected ButtonWidget m_CloseButton;
    protected ButtonWidget m_CreateGroupButton;
    protected ButtonWidget m_InviteButton;
    protected ButtonWidget m_AddMarkerButton;
    protected ButtonWidget m_AddPingButton;
    protected ButtonWidget m_RefreshButton;
    protected ButtonWidget m_GarageButton;
    protected ButtonWidget m_BankingButton;
    protected ButtonWidget m_CenterPlayerButton;
    protected ButtonWidget m_IconPrevButton;
    protected ButtonWidget m_IconNextButton;
    protected ButtonWidget m_LeaveButton;
    protected ButtonWidget m_DisbandButton;
    protected ref array<string> m_IconKeys;
    protected int m_SelectedIconIndex;
    protected vector m_SelectedMapPosition;
    protected int m_HasSelectedMapPosition;
    protected ref DeutschZGroupsCreateGroupPopup m_CreateGroupPopup;
    protected ref DeutschZGroupsInvitePlayerPopup m_InvitePlayerPopup;
    protected ref DeutschZGroupsInvitePopup m_InvitePopup;
    protected ref DeutschZGroupsMarkerPopup m_MarkerPopup;

    override Widget Init()
    {
        m_Root = GetGame().GetWorkspace().CreateWidgets(DeutschZGroupsConstants.LAYOUT_MAP_MENU);
        if (!m_Root)
        {
            return NULL;
        }

        m_Map = MapWidget.Cast(m_Root.FindAnyWidget("DZG_Map"));
        m_GroupHeader = TextWidget.Cast(m_Root.FindAnyWidget("DZG_GroupHeader"));
        m_GroupInfo = TextWidget.Cast(m_Root.FindAnyWidget("DZG_GroupInfo"));
        m_StatusText = TextWidget.Cast(m_Root.FindAnyWidget("DZG_StatusText"));
        m_GarageState = TextWidget.Cast(m_Root.FindAnyWidget("DZG_GarageState"));
        m_BankingState = TextWidget.Cast(m_Root.FindAnyWidget("DZG_BankingState"));
        m_SelectedIconText = TextWidget.Cast(m_Root.FindAnyWidget("DZG_SelectedIconText"));
        m_MemberGrid = GridSpacerWidget.Cast(m_Root.FindAnyWidget("DZG_MemberGrid"));
        m_MarkerGrid = GridSpacerWidget.Cast(m_Root.FindAnyWidget("DZG_MarkerGrid"));
        m_CloseButton = ButtonWidget.Cast(m_Root.FindAnyWidget("DZG_CloseButton"));
        m_CreateGroupButton = ButtonWidget.Cast(m_Root.FindAnyWidget("DZG_CreateGroupButton"));
        m_InviteButton = ButtonWidget.Cast(m_Root.FindAnyWidget("DZG_InviteButton"));
        m_AddMarkerButton = ButtonWidget.Cast(m_Root.FindAnyWidget("DZG_AddMarkerButton"));
        m_AddPingButton = ButtonWidget.Cast(m_Root.FindAnyWidget("DZG_AddPingButton"));
        m_RefreshButton = ButtonWidget.Cast(m_Root.FindAnyWidget("DZG_RefreshButton"));
        m_GarageButton = ButtonWidget.Cast(m_Root.FindAnyWidget("DZG_GarageButton"));
        m_BankingButton = ButtonWidget.Cast(m_Root.FindAnyWidget("DZG_BankingButton"));
        m_CenterPlayerButton = ButtonWidget.Cast(m_Root.FindAnyWidget("DZG_CenterPlayerButton"));
        m_IconPrevButton = ButtonWidget.Cast(m_Root.FindAnyWidget("DZG_IconPrevButton"));
        m_IconNextButton = ButtonWidget.Cast(m_Root.FindAnyWidget("DZG_IconNextButton"));
        m_LeaveButton = ButtonWidget.Cast(m_Root.FindAnyWidget("DZG_LeaveButton"));
        m_DisbandButton = ButtonWidget.Cast(m_Root.FindAnyWidget("DZG_DisbandButton"));
        m_HasSelectedMapPosition = 0;

        InitIconPicker();
        RefreshView();
        return m_Root;
    }


    override void OnShow()
    {
        super.OnShow();

        if (GetGame() && GetGame().GetInput())
            GetGame().GetInput().ChangeGameFocus(1);

        if (GetGame() && GetGame().GetUIManager())
            GetGame().GetUIManager().ShowUICursor(true);

        if (GetGame() && GetGame().GetMission())
            GetGame().GetMission().PlayerControlDisable(INPUT_EXCLUDE_ALL);
    }

    override void OnHide()
    {
        super.OnHide();

        if (GetGame() && GetGame().GetInput())
            GetGame().GetInput().ResetGameFocus();

        if (GetGame() && GetGame().GetUIManager())
            GetGame().GetUIManager().ShowUICursor(false);

        if (GetGame() && GetGame().GetMission())
            GetGame().GetMission().PlayerControlEnable(true);
    }

    protected void InitIconPicker()
    {
        m_IconKeys = new array<string>;
        m_IconKeys.Insert(DeutschZGroupsMarkerIcons.GROUP);
        m_IconKeys.Insert(DeutschZGroupsMarkerIcons.GROUP_PING);
        m_IconKeys.Insert(DeutschZGroupsMarkerIcons.BASE);
        m_IconKeys.Insert(DeutschZGroupsMarkerIcons.GARAGE);
        m_IconKeys.Insert(DeutschZGroupsMarkerIcons.BANK_ATM);
        m_IconKeys.Insert(DeutschZGroupsMarkerIcons.TRADER);
        m_IconKeys.Insert(DeutschZGroupsMarkerIcons.WEAPON_TRADER);
        m_IconKeys.Insert(DeutschZGroupsMarkerIcons.BOAT_TRADER);
        m_IconKeys.Insert(DeutschZGroupsMarkerIcons.BLACKMARKET);
        m_IconKeys.Insert(DeutschZGroupsMarkerIcons.FOOD);
        m_IconKeys.Insert(DeutschZGroupsMarkerIcons.AIRDROP);
        m_IconKeys.Insert(DeutschZGroupsMarkerIcons.EVENT);
        m_IconKeys.Insert(DeutschZGroupsMarkerIcons.KOTH);
        m_IconKeys.Insert(DeutschZGroupsMarkerIcons.PATROLHELI);
        m_IconKeys.Insert(DeutschZGroupsMarkerIcons.HELICRASH);
        m_IconKeys.Insert(DeutschZGroupsMarkerIcons.CONVOY);
        m_IconKeys.Insert(DeutschZGroupsMarkerIcons.BUNKER);
        m_IconKeys.Insert(DeutschZGroupsMarkerIcons.EXTRACT);
        m_IconKeys.Insert(DeutschZGroupsMarkerIcons.FIREWORK);
        m_IconKeys.Insert(DeutschZGroupsMarkerIcons.ADMIN);
        m_SelectedIconIndex = 0;
        RefreshSelectedIconText();
    }

    void RefreshView()
    {
        DeutschZGroupsClientState.Init();
        DeutschZGroupSyncPacket packet = DeutschZGroupsClientState.GetSync();

        if (packet && packet.GroupId != "")
        {
            if (m_GroupHeader)
            {
                m_GroupHeader.SetText(packet.Tag + " - " + packet.Name);
            }
            if (m_GroupInfo)
            {
                m_GroupInfo.SetText("Rang: " + packet.Rank + " | Mitglieder: " + packet.Members.Count());
            }
        }
        else
        {
            if (m_GroupHeader)
            {
                m_GroupHeader.SetText("Keine Gruppe");
            }
            if (m_GroupInfo)
            {
                if (packet && packet.Invites && packet.Invites.Count() > 0)
                {
                    DeutschZGroupInviteData inviteInfo = packet.Invites.Get(0);
                    if (inviteInfo)
                    {
                        m_GroupInfo.SetText("Einladung offen von: " + inviteInfo.InviterName);
                    }
                    else
                    {
                        m_GroupInfo.SetText("Einladung offen. Invite Button nutzen.");
                    }
                }
                else
                {
                    m_GroupInfo.SetText("P druecken fuer Map. Gruppe erstellen oder Invite annehmen.");
                }
            }
        }

        if (m_GarageState)
        {
            m_GarageState.SetText("Garage: Gruppenrechte + Shared Garage ID aktiv");
        }
        if (m_BankingState)
        {
            m_BankingState.SetText("Banking: Gruppenrechte + Shared Bank ID aktiv");
        }
        if (m_StatusText)
        {
            m_StatusText.SetText("Klick waehlt Position | Marker + setzt direkt | Ping nutzt Position oder Spieler");
        }

        RefreshMembers(packet);
        RefreshMarkers(packet);
        if (m_HasSelectedMapPosition == 0)
            CenterMapOnPlayer();
        RenderMapMarkers(packet);
        RefreshSelectedIconText();
    }

    protected void RefreshMembers(DeutschZGroupSyncPacket packet)
    {
        if (!m_MemberGrid)
        {
            return;
        }
        ClearChildren(m_MemberGrid);
        if (!packet || !packet.Members)
        {
            return;
        }

        foreach (DeutschZGroupMemberData member: packet.Members)
        {
            if (!member)
            {
                continue;
            }
            Widget row = GetGame().GetWorkspace().CreateWidgets(DeutschZGroupsConstants.LAYOUT_MEMBER_ENTRY, m_MemberGrid);
            if (!row)
            {
                continue;
            }
            TextWidget nameText = TextWidget.Cast(row.FindAnyWidget("DZG_MemberName"));
            TextWidget rankText = TextWidget.Cast(row.FindAnyWidget("DZG_MemberRank"));
            TextWidget onlineText = TextWidget.Cast(row.FindAnyWidget("DZG_MemberOnline"));
            if (nameText)
            {
                nameText.SetText(member.LastName);
            }
            if (rankText)
            {
                rankText.SetText(member.Rank);
            }
            if (onlineText)
            {
                if (member.Online == 1)
                {
                    onlineText.SetText("online");
                    onlineText.SetColor(ARGB(255, 80, 255, 80));
                }
                else
                {
                    onlineText.SetText("offline");
                    onlineText.SetColor(ARGB(255, 255, 80, 80));
                }
            }
        }
    }

    protected void RefreshMarkers(DeutschZGroupSyncPacket packet)
    {
        if (!m_MarkerGrid)
        {
            return;
        }
        ClearChildren(m_MarkerGrid);
        if (!packet || !packet.Markers)
        {
            if (m_HasSelectedMapPosition == 1)
            {
                string selectedOnlyIconPath = DeutschZGroupsMarkerIcons.GetPath(GetSelectedIconKey());
                m_Map.AddUserMark(m_SelectedMapPosition, "Neue Position", ARGB(255, 255, 210, 0), selectedOnlyIconPath);
            }
            return;
        }

        foreach (DeutschZGroupMarkerData marker: packet.Markers)
        {
            if (!marker)
            {
                continue;
            }
            Widget row = GetGame().GetWorkspace().CreateWidgets(DeutschZGroupsConstants.LAYOUT_MARKER_ENTRY, m_MarkerGrid);
            if (!row)
            {
                continue;
            }
            TextWidget nameText = TextWidget.Cast(row.FindAnyWidget("DZG_MarkerName"));
            TextWidget typeText = TextWidget.Cast(row.FindAnyWidget("DZG_MarkerType"));
            if (nameText)
            {
                nameText.SetText(marker.Name);
            }
            if (typeText)
            {
                typeText.SetText(GetMarkerTypeLabel(marker.MarkerType) + " | " + GetIconDisplayName(marker.Icon));
            }
        }
    }

    protected void RenderMapMarkers(DeutschZGroupSyncPacket packet)
    {
        if (!m_Map)
        {
            return;
        }

        m_Map.ClearUserMarks();

        if (!packet || !packet.Markers)
        {
            if (m_HasSelectedMapPosition == 1)
            {
                string selectedOnlyIconPath = DeutschZGroupsMarkerIcons.GetPath(GetSelectedIconKey());
                m_Map.AddUserMark(m_SelectedMapPosition, "Neue Position", ARGB(255, 255, 210, 0), selectedOnlyIconPath);
            }
            return;
        }

        foreach (DeutschZGroupMarkerData marker: packet.Markers)
        {
            if (!marker || marker.ShowMap == 0)
            {
                continue;
            }

            string iconKey = marker.Icon;
            if (iconKey == "")
            {
                iconKey = DeutschZGroupsMarkerIcons.GetDefaultForMarkerType(marker.MarkerType);
            }
            string iconPath = DeutschZGroupsMarkerIcons.GetPath(iconKey);
            int color = ARGB(255, marker.ColorR, marker.ColorG, marker.ColorB);
            string label = marker.Name;
            if (label == "")
            {
                label = GetMarkerTypeLabel(marker.MarkerType);
            }

            m_Map.AddUserMark(marker.Position, label, color, iconPath);
        }

        if (m_HasSelectedMapPosition == 1)
        {
            string selectedIconPath = DeutschZGroupsMarkerIcons.GetPath(GetSelectedIconKey());
            m_Map.AddUserMark(m_SelectedMapPosition, "Neue Position", ARGB(255, 255, 210, 0), selectedIconPath);
        }
    }

    protected string GetMarkerTypeLabel(int markerType)
    {
        if (markerType == DeutschZGroupMarkerType.GROUP_PING)
        {
            return "Ping";
        }
        if (markerType == DeutschZGroupMarkerType.GROUP_PLAYER)
        {
            return "Spieler";
        }
        if (markerType == DeutschZGroupMarkerType.PRIVATE_MARKER)
        {
            return "Privat";
        }
        if (markerType == DeutschZGroupMarkerType.SERVER_STATIC)
        {
            return "Server";
        }
        if (markerType == DeutschZGroupMarkerType.GARAGE_POINT)
        {
            return "Garage";
        }
        if (markerType == DeutschZGroupMarkerType.BANK_POINT || markerType == DeutschZGroupMarkerType.ATM_POINT)
        {
            return "Banking";
        }
        if (markerType == DeutschZGroupMarkerType.EVENT_POINT)
        {
            return "Event";
        }
        if (markerType == DeutschZGroupMarkerType.TRADER_POINT)
        {
            return "Trader";
        }
        if (markerType == DeutschZGroupMarkerType.KOTH_POINT)
        {
            return "KOTH";
        }
        if (markerType == DeutschZGroupMarkerType.RALLY_POINT)
        {
            return "Extract";
        }
        return "Gruppe";
    }

    protected void CenterMapOnPlayer()
    {
        if (!m_Map)
        {
            return;
        }
        PlayerBase player = PlayerBase.Cast(GetGame().GetPlayer());
        if (!player)
        {
            return;
        }
        m_Map.SetScale(0.35);
        m_Map.SetMapPos(player.GetPosition());
    }

    protected void ClearChildren(Widget parent)
    {
        if (!parent)
        {
            return;
        }
        Widget child = parent.GetChildren();
        while (child)
        {
            Widget next = child.GetSibling();
            child.Unlink();
            child = next;
        }
    }

    override bool OnClick(Widget w, int x, int y, int button)
    {
        if (w == m_CloseButton)
        {
            Close();
            return true;
        }
        if (w == m_RefreshButton)
        {
            RequestFullSync();
            RefreshView();
            return true;
        }
        if (w == m_CenterPlayerButton)
        {
            CenterMapOnPlayer();
            return true;
        }
        if (w == m_IconPrevButton)
        {
            SelectPreviousIcon();
            return true;
        }
        if (w == m_IconNextButton)
        {
            SelectNextIcon();
            return true;
        }
        if (w == m_CreateGroupButton)
        {
            OpenCreateGroupPopup();
            return true;
        }
        if (w == m_InviteButton)
        {
            OpenInviteAction();
            return true;
        }
        if (w == m_AddMarkerButton)
        {
            RequestMarkerAtSelection(false);
            return true;
        }
        if (w == m_AddPingButton)
        {
            RequestPingAtPlayer();
            return true;
        }
        if (w == m_GarageButton)
        {
            SetStatus("DeutschZ Garage Bridge vorbereitet.");
            return true;
        }
        if (w == m_BankingButton)
        {
            SetStatus("DeutschZ Banking Bridge vorbereitet.");
            return true;
        }
        if (w == m_LeaveButton)
        {
            RequestLeaveGroup();
            return true;
        }
        if (w == m_DisbandButton)
        {
            RequestDisbandGroup();
            return true;
        }
        return super.OnClick(w, x, y, button);
    }

    override bool OnMouseButtonDown(Widget w, int x, int y, int button)
    {
        if (w == m_Map && button == 0)
        {
            SelectMapPosition(x, y);
            SetStatus("Markerposition gewaehlt: " + m_SelectedMapPosition.ToString() + " | Doppelklick oder Marker + nutzen.");
            RenderMapMarkers(DeutschZGroupsClientState.GetSync());
            return true;
        }
        return super.OnMouseButtonDown(w, x, y, button);
    }

    override bool OnDoubleClick(Widget w, int x, int y, int button)
    {
        if (w == m_Map && button == 0)
        {
            SelectMapPosition(x, y);
            RequestMarkerAtSelection(false);
            return true;
        }
        return super.OnDoubleClick(w, x, y, button);
    }

    protected void SelectMapPosition(int x, int y)
    {
        if (!m_Map)
        {
            return;
        }
        m_SelectedMapPosition = m_Map.ScreenToMap(Vector(x, y, 0));
        m_SelectedMapPosition[1] = GetGame().SurfaceY(m_SelectedMapPosition[0], m_SelectedMapPosition[2]);
        m_HasSelectedMapPosition = 1;
    }

    protected void OpenCreateGroupPopup()
    {
        m_CreateGroupPopup = new DeutschZGroupsCreateGroupPopup();
        m_CreateGroupPopup.SetParentMenu(this);
        GetGame().GetUIManager().ShowScriptedMenu(m_CreateGroupPopup, NULL);
    }

    protected void OpenInviteAction()
    {
        DeutschZGroupSyncPacket packet = DeutschZGroupsClientState.GetSync();
        if (packet && packet.GroupId == "" && packet.Invites && packet.Invites.Count() > 0)
        {
            OpenIncomingInvitePopup(packet.Invites.Get(0));
            return;
        }

        if (!packet || packet.GroupId == "")
        {
            SetStatus("Keine Gruppe: erst Gruppe erstellen oder Invite annehmen.");
            return;
        }

        m_InvitePlayerPopup = new DeutschZGroupsInvitePlayerPopup();
        m_InvitePlayerPopup.SetParentMenu(this);
        GetGame().GetUIManager().ShowScriptedMenu(m_InvitePlayerPopup, NULL);
    }

    void OpenIncomingInvitePopup(DeutschZGroupInviteData invite)
    {
        if (!invite)
        {
            SetStatus("Keine Einladung vorhanden.");
            return;
        }
        m_InvitePopup = new DeutschZGroupsInvitePopup();
        m_InvitePopup.SetParentMenu(this);
        GetGame().GetUIManager().ShowScriptedMenu(m_InvitePopup, NULL);
        m_InvitePopup.SetInvite(invite);
    }

    void AcceptFirstInvite()
    {
        DeutschZGroupSyncPacket packet = DeutschZGroupsClientState.GetSync();
        if (!packet || !packet.Invites || packet.Invites.Count() == 0)
        {
            SetStatus("Keine Einladung vorhanden.");
            return;
        }
        DeutschZGroupInviteData invite = packet.Invites.Get(0);
        if (!invite)
        {
            SetStatus("Einladung ungueltig.");
            return;
        }
        PlayerBase player = PlayerBase.Cast(GetGame().GetPlayer());
        if (!player)
        {
            return;
        }
        GetGame().RPCSingleParam(player, DeutschZGroupsRPC.GROUP_ACCEPT_INVITE, new Param1<string>(invite.InviteId), true);
        SetStatus("Einladung angenommen.");
        RequestFullSync();
    }

    protected void RequestLeaveGroup()
    {
        PlayerBase player = PlayerBase.Cast(GetGame().GetPlayer());
        if (!player)
        {
            return;
        }
        GetGame().RPCSingleParam(player, DeutschZGroupsRPC.GROUP_LEAVE, new Param1<int>(0), true);
        SetStatus("Gruppe verlassen an Server gesendet.");
        RequestFullSync();
    }

    protected void RequestDisbandGroup()
    {
        PlayerBase player = PlayerBase.Cast(GetGame().GetPlayer());
        if (!player)
        {
            return;
        }
        GetGame().RPCSingleParam(player, DeutschZGroupsRPC.GROUP_DISBAND, new Param1<int>(0), true);
        SetStatus("Gruppe aufloesen an Server gesendet.");
        RequestFullSync();
    }

    protected string GetSelectedIconKey()
    {
        if (!m_IconKeys || m_IconKeys.Count() == 0)
        {
            return DeutschZGroupsMarkerIcons.GROUP;
        }
        if (m_SelectedIconIndex < 0)
        {
            m_SelectedIconIndex = 0;
        }
        if (m_SelectedIconIndex >= m_IconKeys.Count())
        {
            m_SelectedIconIndex = m_IconKeys.Count() - 1;
        }
        return m_IconKeys.Get(m_SelectedIconIndex);
    }

    protected void SelectPreviousIcon()
    {
        if (!m_IconKeys || m_IconKeys.Count() == 0)
        {
            return;
        }
        m_SelectedIconIndex--;
        if (m_SelectedIconIndex < 0)
        {
            m_SelectedIconIndex = m_IconKeys.Count() - 1;
        }
        RefreshSelectedIconText();
    }

    protected void SelectNextIcon()
    {
        if (!m_IconKeys || m_IconKeys.Count() == 0)
        {
            return;
        }
        m_SelectedIconIndex++;
        if (m_SelectedIconIndex >= m_IconKeys.Count())
        {
            m_SelectedIconIndex = 0;
        }
        RefreshSelectedIconText();
    }

    protected void RefreshSelectedIconText()
    {
        if (m_SelectedIconText)
        {
            string iconKey = GetSelectedIconKey();
            m_SelectedIconText.SetText("Icon: " + GetIconDisplayName(iconKey));
        }
    }

    protected string GetIconDisplayName(string iconKey)
    {
        if (iconKey == DeutschZGroupsMarkerIcons.GROUP) return "Group";
        if (iconKey == DeutschZGroupsMarkerIcons.GROUP_PING) return "Group Ping";
        if (iconKey == DeutschZGroupsMarkerIcons.BASE) return "Base";
        if (iconKey == DeutschZGroupsMarkerIcons.GARAGE) return "Garage";
        if (iconKey == DeutschZGroupsMarkerIcons.BANK_ATM) return "Bank ATM";
        if (iconKey == DeutschZGroupsMarkerIcons.TRADER) return "Trader";
        if (iconKey == DeutschZGroupsMarkerIcons.WEAPON_TRADER) return "Weapon Trader";
        if (iconKey == DeutschZGroupsMarkerIcons.BOAT_TRADER) return "Boat Trader";
        if (iconKey == DeutschZGroupsMarkerIcons.BLACKMARKET) return "Blackmarket";
        if (iconKey == DeutschZGroupsMarkerIcons.FOOD) return "Food";
        if (iconKey == DeutschZGroupsMarkerIcons.AIRDROP) return "Airdrop";
        if (iconKey == DeutschZGroupsMarkerIcons.EVENT) return "Event";
        if (iconKey == DeutschZGroupsMarkerIcons.KOTH) return "KOTH";
        if (iconKey == DeutschZGroupsMarkerIcons.PATROLHELI) return "PatrolHeli";
        if (iconKey == DeutschZGroupsMarkerIcons.HELICRASH) return "Helicrash";
        if (iconKey == DeutschZGroupsMarkerIcons.CONVOY) return "Convoy";
        if (iconKey == DeutschZGroupsMarkerIcons.BUNKER) return "Bunker";
        if (iconKey == DeutschZGroupsMarkerIcons.EXTRACT) return "Extract";
        if (iconKey == DeutschZGroupsMarkerIcons.FIREWORK) return "Firework";
        if (iconKey == DeutschZGroupsMarkerIcons.ADMIN) return "Admin";
        return iconKey;
    }

    protected int GetMarkerTypeForIcon(string iconKey)
    {
        if (iconKey == DeutschZGroupsMarkerIcons.GROUP_PING) return DeutschZGroupMarkerType.GROUP_PING;
        if (iconKey == DeutschZGroupsMarkerIcons.GARAGE) return DeutschZGroupMarkerType.GARAGE_POINT;
        if (iconKey == DeutschZGroupsMarkerIcons.BANK_ATM) return DeutschZGroupMarkerType.ATM_POINT;
        if (iconKey == DeutschZGroupsMarkerIcons.TRADER || iconKey == DeutschZGroupsMarkerIcons.WEAPON_TRADER || iconKey == DeutschZGroupsMarkerIcons.BOAT_TRADER || iconKey == DeutschZGroupsMarkerIcons.BLACKMARKET || iconKey == DeutschZGroupsMarkerIcons.FOOD) return DeutschZGroupMarkerType.TRADER_POINT;
        if (iconKey == DeutschZGroupsMarkerIcons.AIRDROP || iconKey == DeutschZGroupsMarkerIcons.EVENT || iconKey == DeutschZGroupsMarkerIcons.PATROLHELI || iconKey == DeutschZGroupsMarkerIcons.HELICRASH || iconKey == DeutschZGroupsMarkerIcons.CONVOY || iconKey == DeutschZGroupsMarkerIcons.FIREWORK) return DeutschZGroupMarkerType.EVENT_POINT;
        if (iconKey == DeutschZGroupsMarkerIcons.KOTH) return DeutschZGroupMarkerType.KOTH_POINT;
        if (iconKey == DeutschZGroupsMarkerIcons.EXTRACT) return DeutschZGroupMarkerType.RALLY_POINT;
        if (iconKey == DeutschZGroupsMarkerIcons.ADMIN || iconKey == DeutschZGroupsMarkerIcons.BUNKER) return DeutschZGroupMarkerType.SERVER_STATIC;
        return DeutschZGroupMarkerType.GROUP_MARKER;
    }

    vector GetCurrentMarkerPosition()
    {
        if (m_HasSelectedMapPosition == 1)
        {
            return m_SelectedMapPosition;
        }
        PlayerBase player = PlayerBase.Cast(GetGame().GetPlayer());
        if (player)
        {
            return player.GetPosition();
        }
        return "0 0 0";
    }

    protected void OpenMarkerPopup()
    {
        string iconKey = GetSelectedIconKey();
        vector position = GetCurrentMarkerPosition();
        m_MarkerPopup = new DeutschZGroupsMarkerPopup();
        m_MarkerPopup.SetParentMenu(this);
        m_MarkerPopup.SetMarkerDefaults(position, iconKey, GetIconDisplayName(iconKey), GetMarkerTypeForIcon(iconKey));
        GetGame().GetUIManager().ShowScriptedMenu(m_MarkerPopup, NULL);
        SetStatus("Markerposition: " + position.ToString());
    }

    protected void RequestMarkerAtSelection(bool privateMarker)
    {
        PlayerBase player = PlayerBase.Cast(GetGame().GetPlayer());
        if (!player)
        {
            SetStatus("Marker nicht moeglich: kein Spieler.");
            return;
        }

        string iconKey = GetSelectedIconKey();
        vector position = GetCurrentMarkerPosition();
        DeutschZGroupSyncPacket packet = DeutschZGroupsClientState.GetSync();
        if (!packet || packet.GroupId == "")
            privateMarker = true;

        ref DeutschZGroupMarkerRequest request = new DeutschZGroupMarkerRequest();
        request.Marker.Name = GetIconDisplayName(iconKey);
        request.Marker.Icon = iconKey;
        request.Marker.Position = position;
        request.Marker.ColorR = 214;
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
            request.Marker.MarkerType = GetMarkerTypeForIcon(iconKey);
            GetGame().RPCSingleParam(player, DeutschZGroupsRPC.GROUP_ADD_MARKER, new Param1<DeutschZGroupMarkerRequest>(request), true);
        }

        m_HasSelectedMapPosition = 1;
        m_SelectedMapPosition = position;
        RenderMapMarkers(DeutschZGroupsClientState.GetSync());
        SetStatus("Marker gesendet: " + request.Marker.Name + " @ " + position.ToString());
        RequestFullSync();
    }

    void RequestPingAtPlayer()
    {
        PlayerBase player = PlayerBase.Cast(GetGame().GetPlayer());
        if (!player)
        {
            SetStatus("Ping nicht moeglich: kein Spieler.");
            return;
        }
        DeutschZGroupMarkerRequest request = new DeutschZGroupMarkerRequest();
        request.Marker.Name = "Ping";
        request.Marker.Position = GetCurrentMarkerPosition();
        request.Marker.MarkerType = DeutschZGroupMarkerType.GROUP_PING;
        request.Marker.Icon = DeutschZGroupsMarkerIcons.GROUP_PING;
        GetGame().RPCSingleParam(player, DeutschZGroupsRPC.GROUP_PING, new Param1<DeutschZGroupMarkerRequest>(request), true);
        SetStatus("Gruppenping an Server gesendet.");
    }

    void RequestFullSync()
    {
        PlayerBase player = PlayerBase.Cast(GetGame().GetPlayer());
        if (!player)
        {
            return;
        }
        GetGame().RPCSingleParam(player, DeutschZGroupsRPC.API_REFRESH, new Param1<int>(0), true);
        GetGame().GetCallQueue(CALL_CATEGORY_GUI).CallLater(RefreshView, 750, false);
    }

    void SetStatus(string text)
    {
        if (m_StatusText)
        {
            m_StatusText.SetText(text);
        }
    }
}
