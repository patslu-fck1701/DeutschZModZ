modded class PlayerBase
{
    protected string m_DeutschZGroups_GroupId = "";
    protected string m_DeutschZGroups_GroupTag = "";
    protected string m_DeutschZGroups_GroupRank = "";

    override void OnRPC(PlayerIdentity sender, int rpc_type, ParamsReadContext ctx)
    {
        if (rpc_type == DeutschZGroupsRPC.GROUP_SYNC)
        {
            Param1<DeutschZGroupSyncPacket> data = new Param1<DeutschZGroupSyncPacket>(new DeutschZGroupSyncPacket());
            if (ctx.Read(data) && data.param1)
            {
                DeutschZGroupsClientState.SetSync(data.param1);
                DeutschZGroups_SetGroupCache(data.param1.GroupId, data.param1.Tag, data.param1.Rank);
                return;
            }
        }

        if (GetGame().IsServer())
        {
            if (DeutschZGroups_HandleServerRPC(sender, rpc_type, ctx))
            {
                return;
            }
        }

        super.OnRPC(sender, rpc_type, ctx);
    }

    protected bool DeutschZGroups_HandleServerRPC(PlayerIdentity sender, int rpc_type, ParamsReadContext ctx)
    {
        if (!sender)
        {
            return false;
        }

        DeutschZGroupsManager manager = DeutschZGroupsRuntime.GetManager();
        if (!manager)
        {
            return false;
        }

        string steam64 = sender.GetPlainId();
        string name = sender.GetName();

        if (rpc_type == DeutschZGroupsRPC.API_REFRESH)
        {
            manager.SendSyncToPlayer(this);
            return true;
        }

        if (rpc_type == DeutschZGroupsRPC.GROUP_CREATE)
        {
            Param1<DeutschZGroupCreateRequest> createData = new Param1<DeutschZGroupCreateRequest>(new DeutschZGroupCreateRequest());
            if (ctx.Read(createData) && createData.param1)
            {
                manager.CreateGroup(createData.param1.Name, createData.param1.Tag, steam64, name);
                manager.SendSyncToPlayer(this);
            }
            return true;
        }

        if (rpc_type == DeutschZGroupsRPC.GROUP_INVITE)
        {
            Param1<DeutschZGroupInviteRequest> inviteData = new Param1<DeutschZGroupInviteRequest>(new DeutschZGroupInviteRequest());
            if (ctx.Read(inviteData) && inviteData.param1)
            {
                manager.InvitePlayer(steam64, name, inviteData.param1.TargetSteam64, inviteData.param1.TargetName);
                manager.SendSyncToAllOnline();
            }
            return true;
        }


        if (rpc_type == DeutschZGroupsRPC.GROUP_ACCEPT_INVITE)
        {
            Param1<string> acceptData = new Param1<string>("");
            if (ctx.Read(acceptData) && acceptData.param1 != "")
            {
                manager.AcceptInvite(acceptData.param1, steam64, name);
                manager.SendSyncToAllOnline();
            }
            return true;
        }

        if (rpc_type == DeutschZGroupsRPC.GROUP_DECLINE_INVITE)
        {
            Param1<string> declineData = new Param1<string>("");
            if (ctx.Read(declineData) && declineData.param1 != "")
            {
                manager.DeclineInvite(declineData.param1, steam64);
                manager.SendSyncToPlayer(this);
            }
            return true;
        }

        if (rpc_type == DeutschZGroupsRPC.GROUP_REMOVE_MARKER)
        {
            Param1<DeutschZGroupMarkerRemoveRequest> removeMarkerData = new Param1<DeutschZGroupMarkerRemoveRequest>(new DeutschZGroupMarkerRemoveRequest());
            if (ctx.Read(removeMarkerData) && removeMarkerData.param1)
            {
                manager.RemoveGroupMarker(steam64, removeMarkerData.param1.MarkerId);
                manager.SendSyncToAllOnline();
            }
            return true;
        }

        if (rpc_type == DeutschZGroupsRPC.PRIVATE_MARKER_REMOVE)
        {
            Param1<DeutschZGroupMarkerRemoveRequest> removePrivateData = new Param1<DeutschZGroupMarkerRemoveRequest>(new DeutschZGroupMarkerRemoveRequest());
            if (ctx.Read(removePrivateData) && removePrivateData.param1)
            {
                manager.RemovePrivateMarker(steam64, removePrivateData.param1.MarkerId);
                manager.SendSyncToPlayer(this);
            }
            return true;
        }

        if (rpc_type == DeutschZGroupsRPC.GROUP_ADD_MARKER)
        {
            Param1<DeutschZGroupMarkerRequest> markerData = new Param1<DeutschZGroupMarkerRequest>(new DeutschZGroupMarkerRequest());
            if (ctx.Read(markerData) && markerData.param1 && markerData.param1.Marker)
            {
                manager.AddGroupMarker(steam64, markerData.param1.Marker);
                manager.SendSyncToAllOnline();
            }
            return true;
        }

        if (rpc_type == DeutschZGroupsRPC.GROUP_PING)
        {
            Param1<DeutschZGroupMarkerRequest> pingData = new Param1<DeutschZGroupMarkerRequest>(new DeutschZGroupMarkerRequest());
            if (ctx.Read(pingData) && pingData.param1 && pingData.param1.Marker)
            {
                manager.AddGroupPing(steam64, pingData.param1.Marker.Position, pingData.param1.Marker.Name);
                manager.SendSyncToAllOnline();
            }
            return true;
        }

        if (rpc_type == DeutschZGroupsRPC.PRIVATE_MARKER_SAVE)
        {
            Param1<DeutschZGroupMarkerRequest> privateData = new Param1<DeutschZGroupMarkerRequest>(new DeutschZGroupMarkerRequest());
            if (ctx.Read(privateData) && privateData.param1 && privateData.param1.Marker)
            {
                manager.AddPrivateMarker(steam64, privateData.param1.Marker);
                manager.SendSyncToPlayer(this);
            }
            return true;
        }

        if (rpc_type == DeutschZGroupsRPC.GROUP_SET_RANK)
        {
            Param1<DeutschZGroupRankRequest> rankData = new Param1<DeutschZGroupRankRequest>(new DeutschZGroupRankRequest());
            if (ctx.Read(rankData) && rankData.param1)
            {
                manager.SetMemberRank(steam64, rankData.param1.TargetSteam64, rankData.param1.NewRank);
                manager.SendSyncToAllOnline();
            }
            return true;
        }

        if (rpc_type == DeutschZGroupsRPC.GROUP_LEAVE)
        {
            manager.LeaveGroup(steam64);
            manager.SendSyncToAllOnline();
            return true;
        }

        if (rpc_type == DeutschZGroupsRPC.GROUP_DISBAND)
        {
            manager.DisbandGroup(steam64);
            manager.SendSyncToAllOnline();
            return true;
        }

        return false;
    }

    void DeutschZGroups_SetGroupCache(string groupId, string groupTag, string rank)
    {
        m_DeutschZGroups_GroupId = groupId;
        m_DeutschZGroups_GroupTag = groupTag;
        m_DeutschZGroups_GroupRank = rank;
    }

    string DeutschZGroups_GetGroupId()
    {
        return m_DeutschZGroups_GroupId;
    }

    string DeutschZGroups_GetGroupTag()
    {
        return m_DeutschZGroups_GroupTag;
    }

    string DeutschZGroups_GetGroupRank()
    {
        return m_DeutschZGroups_GroupRank;
    }

    bool DeutschZGroups_IsInGroup()
    {
        return m_DeutschZGroups_GroupId != "";
    }

    bool DeutschZGroups_IsGroupOfficer()
    {
        return m_DeutschZGroups_GroupRank == "Leutnant" || m_DeutschZGroups_GroupRank == "Hauptmann" || m_DeutschZGroups_GroupRank == "Kommandant";
    }
}
