class DeutschZGroupsManager
{
    protected ref DeutschZGroupsConfigManager m_ConfigManager;
    protected ref array<ref DeutschZGroupData> m_Groups;
    protected ref array<ref DeutschZGroupInviteData> m_Invites;
    protected int m_LastAutoSave;

    void DeutschZGroupsManager()
    {
        m_ConfigManager = new DeutschZGroupsConfigManager();
        m_Groups = new array<ref DeutschZGroupData>;
        m_Invites = new array<ref DeutschZGroupInviteData>;
        m_LastAutoSave = 0;
    }

    void Init()
    {
        DeutschZGroupsProfileFolders.Ensure();
        m_ConfigManager.LoadAll();
        LoadGroups();
        CleanupExpiredInvites();
        Print("[DeutschZ_Groups] Initialized v0.5.1. Groups loaded: " + m_Groups.Count());
    }

    DeutschZGroupsConfigManager GetConfigManager()
    {
        return m_ConfigManager;
    }

    void LoadGroups()
    {
        m_Groups.Clear();

        ref array<string> files = new array<string>;
        FindFilesInLocation(DeutschZGroupsConstants.PROFILE_GROUP_DATA_ROOT, files);

        foreach (string fileName: files)
        {
            if (fileName.Contains(".json"))
            {
                ref DeutschZGroupData group = new DeutschZGroupData();
                string fullPath = DeutschZGroupsConstants.PROFILE_GROUP_DATA_ROOT + "/" + fileName;
                JsonFileLoader<DeutschZGroupData>.JsonLoadFile(fullPath, group);
                if (group && group.GroupId != "")
                {
                    ValidateGroup(group);
                    m_Groups.Insert(group);
                }
            }
        }
    }

    protected void FindFilesInLocation(string folder, notnull array<string> outFiles)
    {
        outFiles.Clear();
        FindFileHandle handle;
        string fileName;
        int fileAttr;

        handle = FindFile(folder + "/*.json", fileName, fileAttr, 0);
        if (handle)
        {
            bool found = true;
            while (found)
            {
                outFiles.Insert(fileName);
                found = FindNextFile(handle, fileName, fileAttr);
            }
            CloseFindFile(handle);
        }
    }

    void ValidateGroup(DeutschZGroupData group)
    {
        if (!group)
        {
            return;
        }
        group.EnsureArrays();
        group.EnsureId();
        if (group.MaxMembers < 1)
        {
            group.MaxMembers = m_ConfigManager.MainConfig.MaxGroupMembersDefault;
        }
        if (group.MaxMarkers < 0)
        {
            group.MaxMarkers = m_ConfigManager.MainConfig.MaxGroupMarkersDefault;
        }
        foreach (DeutschZGroupMemberData member: group.Members)
        {
            if (member && !m_ConfigManager.LevelsConfig.IsValidRank(member.Rank))
            {
                member.Rank = m_ConfigManager.MainConfig.DefaultMemberRank;
            }
        }
        DeutschZGroupMemberData owner = group.FindMember(group.OwnerSteam64);
        if (owner)
        {
            owner.Rank = m_ConfigManager.MainConfig.OwnerRank;
        }
    }

    void SaveAllGroups()
    {
        foreach (DeutschZGroupData group: m_Groups)
        {
            SaveGroup(group);
        }
    }

    void SaveGroup(DeutschZGroupData group)
    {
        if (!group)
        {
            return;
        }
        group.EnsureId();
        string filePath = DeutschZGroupsConstants.PROFILE_GROUP_DATA_ROOT + "/" + group.GroupId + ".json";
        JsonFileLoader<DeutschZGroupData>.JsonSaveFile(filePath, group);
    }

    protected void DeleteGroupFile(DeutschZGroupData group)
    {
        if (!group)
        {
            return;
        }
        string filePath = DeutschZGroupsConstants.PROFILE_GROUP_DATA_ROOT + "/" + group.GroupId + ".json";
        if (FileExist(filePath))
        {
            DeleteFile(filePath);
        }
    }

    DeutschZGroupData CreateGroup(string name, string tag, string ownerSteam64, string ownerName)
    {
        if (!m_ConfigManager.MainConfig || m_ConfigManager.MainConfig.EnableGroups == 0)
        {
            return NULL;
        }
        if (ownerSteam64 == "" || name == "" || tag == "")
        {
            return NULL;
        }
        if (GetPlayerGroup(ownerSteam64))
        {
            return NULL;
        }
        if (FindGroupByTag(tag))
        {
            return NULL;
        }

        ref DeutschZGroupData group = new DeutschZGroupData();
        group.Name = name;
        group.Tag = tag;
        group.OwnerSteam64 = ownerSteam64;
        group.CreatedAt = string.Format("%1", GetGame().GetTime());
        group.LastActivity = group.CreatedAt;
        group.MaxMembers = m_ConfigManager.MainConfig.MaxGroupMembersDefault;
        group.MaxMarkers = m_ConfigManager.MainConfig.MaxGroupMarkersDefault;
        group.EnsureId();
        group.AddMember(ownerSteam64, ownerName, m_ConfigManager.MainConfig.OwnerRank);

        m_Groups.Insert(group);
        AddAudit(group, ownerSteam64, ownerName, "group.create", group.Tag, "Group created");
        SaveGroup(group);
        return group;
    }

    DeutschZGroupData GetGroupById(string groupId)
    {
        foreach (DeutschZGroupData group: m_Groups)
        {
            if (group && group.GroupId == groupId)
            {
                return group;
            }
        }
        return NULL;
    }

    DeutschZGroupData FindGroupByTag(string tag)
    {
        foreach (DeutschZGroupData group: m_Groups)
        {
            if (group && group.Tag == tag)
            {
                return group;
            }
        }
        return NULL;
    }

    DeutschZGroupData GetPlayerGroup(string steam64)
    {
        foreach (DeutschZGroupData group: m_Groups)
        {
            if (group && group.HasMember(steam64))
            {
                return group;
            }
        }
        return NULL;
    }

    string GetPlayerGroupId(string steam64)
    {
        DeutschZGroupData group = GetPlayerGroup(steam64);
        if (!group)
        {
            return "";
        }
        return group.GroupId;
    }

    string GetPlayerGroupTag(string steam64)
    {
        DeutschZGroupData group = GetPlayerGroup(steam64);
        if (!group)
        {
            return "";
        }
        return group.Tag;
    }

    string GetPlayerRank(string steam64)
    {
        DeutschZGroupData group = GetPlayerGroup(steam64);
        if (!group)
        {
            return "";
        }
        DeutschZGroupMemberData member = group.FindMember(steam64);
        if (!member)
        {
            return "";
        }
        return member.Rank;
    }

    int GetPlayerRankPriority(string steam64)
    {
        return m_ConfigManager.LevelsConfig.GetPriority(GetPlayerRank(steam64));
    }

    bool HasPermission(string steam64, string permission)
    {
        string rank = GetPlayerRank(steam64);
        if (rank == "")
        {
            return false;
        }
        return m_ConfigManager.LevelsConfig.HasPermission(rank, permission);
    }

    bool CanActOnMember(string actorSteam64, string targetSteam64)
    {
        if (actorSteam64 == targetSteam64)
        {
            return false;
        }
        DeutschZGroupData actorGroup = GetPlayerGroup(actorSteam64);
        DeutschZGroupData targetGroup = GetPlayerGroup(targetSteam64);
        if (!actorGroup || !targetGroup || actorGroup.GroupId != targetGroup.GroupId)
        {
            return false;
        }
        return GetPlayerRankPriority(actorSteam64) > GetPlayerRankPriority(targetSteam64);
    }

    DeutschZGroupInviteData InvitePlayer(string inviterSteam64, string inviterName, string targetSteam64, string targetName)
    {
        if (!HasPermission(inviterSteam64, DeutschZGroupPermissionKeys.GROUP_INVITE))
        {
            return NULL;
        }
        DeutschZGroupData group = GetPlayerGroup(inviterSteam64);
        if (!group || targetSteam64 == "")
        {
            return NULL;
        }
        if (GetPlayerGroup(targetSteam64))
        {
            return NULL;
        }
        if (FindInvite(group.GroupId, targetSteam64))
        {
            return NULL;
        }

        ref DeutschZGroupInviteData invite = new DeutschZGroupInviteData();
        invite.GroupId = group.GroupId;
        invite.InviterSteam64 = inviterSteam64;
        invite.InviterName = inviterName;
        invite.TargetSteam64 = targetSteam64;
        invite.TargetName = targetName;
        invite.CreatedAt = string.Format("%1", GetGame().GetTime());
        invite.ExpiresAt = GetGame().GetTime() + (m_ConfigManager.MainConfig.InviteLifetimeSeconds * 1000);
        invite.EnsureId();
        m_Invites.Insert(invite);
        return invite;
    }

    DeutschZGroupInviteData FindInvite(string groupId, string targetSteam64)
    {
        CleanupExpiredInvites();
        foreach (DeutschZGroupInviteData invite: m_Invites)
        {
            if (invite && invite.GroupId == groupId && invite.TargetSteam64 == targetSteam64)
            {
                return invite;
            }
        }
        return NULL;
    }

    bool AcceptInvite(string inviteId, string targetSteam64, string targetName)
    {
        CleanupExpiredInvites();
        for (int i = m_Invites.Count() - 1; i >= 0; i--)
        {
            DeutschZGroupInviteData invite = m_Invites.Get(i);
            if (invite && invite.InviteId == inviteId && invite.TargetSteam64 == targetSteam64)
            {
                bool added = AddMemberToGroup(invite.GroupId, targetSteam64, targetName, m_ConfigManager.MainConfig.DefaultMemberRank);
                if (added)
                {
                    m_Invites.Remove(i);
                }
                return added;
            }
        }
        return false;
    }

    bool DeclineInvite(string inviteId, string targetSteam64)
    {
        for (int i = m_Invites.Count() - 1; i >= 0; i--)
        {
            DeutschZGroupInviteData invite = m_Invites.Get(i);
            if (invite && invite.InviteId == inviteId && invite.TargetSteam64 == targetSteam64)
            {
                m_Invites.Remove(i);
                return true;
            }
        }
        return false;
    }

    bool AddMemberToGroup(string groupId, string steam64, string name, string rank)
    {
        DeutschZGroupData group = GetGroupById(groupId);
        if (!group)
        {
            return false;
        }
        if (GetPlayerGroup(steam64))
        {
            return false;
        }
        if (!m_ConfigManager.LevelsConfig.IsValidRank(rank))
        {
            rank = m_ConfigManager.MainConfig.DefaultMemberRank;
        }
        bool added = group.AddMember(steam64, name, rank);
        if (added)
        {
            AddAudit(group, steam64, name, "group.member.add", steam64, "Member joined");
            SaveGroup(group);
        }
        return added;
    }

    bool KickMember(string actorSteam64, string targetSteam64)
    {
        if (!HasPermission(actorSteam64, DeutschZGroupPermissionKeys.GROUP_KICK))
        {
            return false;
        }
        if (!CanActOnMember(actorSteam64, targetSteam64))
        {
            return false;
        }
        return RemoveMemberFromGroup(targetSteam64);
    }

    bool LeaveGroup(string steam64)
    {
        DeutschZGroupData group = GetPlayerGroup(steam64);
        if (!group)
        {
            return false;
        }
        if (group.OwnerSteam64 == steam64)
        {
            return false;
        }
        return RemoveMemberFromGroup(steam64);
    }

    bool RemoveMemberFromGroup(string steam64)
    {
        DeutschZGroupData group = GetPlayerGroup(steam64);
        if (!group)
        {
            return false;
        }
        bool removed = group.RemoveMember(steam64);
        if (removed)
        {
            SaveGroup(group);
        }
        return removed;
    }

    bool SetMemberRank(string actorSteam64, string targetSteam64, string newRank)
    {
        if (!HasPermission(actorSteam64, DeutschZGroupPermissionKeys.GROUP_SET_RANK))
        {
            return false;
        }
        if (!m_ConfigManager.LevelsConfig.IsValidRank(newRank))
        {
            return false;
        }
        if (!CanActOnMember(actorSteam64, targetSteam64))
        {
            return false;
        }
        if (m_ConfigManager.LevelsConfig.GetPriority(newRank) >= GetPlayerRankPriority(actorSteam64))
        {
            return false;
        }
        DeutschZGroupData group = GetPlayerGroup(actorSteam64);
        if (!group)
        {
            return false;
        }
        bool changed = group.SetMemberRank(targetSteam64, newRank);
        if (changed)
        {
            SaveGroup(group);
        }
        return changed;
    }

    bool TransferOwner(string actorSteam64, string targetSteam64)
    {
        DeutschZGroupData group = GetPlayerGroup(actorSteam64);
        if (!group || group.OwnerSteam64 != actorSteam64)
        {
            return false;
        }
        if (!group.HasMember(targetSteam64))
        {
            return false;
        }
        group.OwnerSteam64 = targetSteam64;
        group.SetMemberRank(actorSteam64, m_ConfigManager.MainConfig.OfficerRank);
        group.SetMemberRank(targetSteam64, m_ConfigManager.MainConfig.OwnerRank);
        SaveGroup(group);
        return true;
    }

    bool DisbandGroup(string actorSteam64)
    {
        DeutschZGroupData group = GetPlayerGroup(actorSteam64);
        if (!group || group.OwnerSteam64 != actorSteam64)
        {
            return false;
        }
        for (int i = m_Groups.Count() - 1; i >= 0; i--)
        {
            DeutschZGroupData entry = m_Groups.Get(i);
            if (entry && entry.GroupId == group.GroupId)
            {
                DeleteGroupFile(entry);
                m_Groups.Remove(i);
                return true;
            }
        }
        return false;
    }

    bool AddGroupMarker(string actorSteam64, DeutschZGroupMarkerData marker)
    {
        if (!HasPermission(actorSteam64, DeutschZGroupPermissionKeys.GROUP_MARKER_CREATE))
        {
            return false;
        }
        DeutschZGroupData group = GetPlayerGroup(actorSteam64);
        if (!group || !marker)
        {
            return false;
        }
        if (group.Markers.Count() >= group.MaxMarkers)
        {
            return false;
        }
        marker.MarkerType = DeutschZGroupMarkerType.GROUP_MARKER;
        marker.CreatorSteam64 = actorSteam64;
        marker.EnsureId();
        group.Markers.Insert(marker);
        SaveGroup(group);
        return true;
    }

    bool RemoveGroupMarker(string actorSteam64, string markerId)
    {
        if (!HasPermission(actorSteam64, DeutschZGroupPermissionKeys.GROUP_MARKER_DELETE))
        {
            return false;
        }
        DeutschZGroupData group = GetPlayerGroup(actorSteam64);
        if (!group)
        {
            return false;
        }
        for (int i = group.Markers.Count() - 1; i >= 0; i--)
        {
            DeutschZGroupMarkerData marker = group.Markers.Get(i);
            if (marker && marker.MarkerId == markerId)
            {
                group.Markers.Remove(i);
                SaveGroup(group);
                return true;
            }
        }
        return false;
    }

    bool AddGroupPing(string actorSteam64, vector position, string name)
    {
        if (!HasPermission(actorSteam64, DeutschZGroupPermissionKeys.GROUP_PING))
        {
            return false;
        }
        DeutschZGroupData group = GetPlayerGroup(actorSteam64);
        if (!group)
        {
            return false;
        }
        ref DeutschZGroupMarkerData ping = new DeutschZGroupMarkerData();
        ping.MarkerType = DeutschZGroupMarkerType.GROUP_PING;
        ping.Name = name;
        ping.Icon = m_ConfigManager.MarkerConfig.DefaultPingIcon;
        ping.Position = position;
        ping.CreatorSteam64 = actorSteam64;
        ping.CreatedAt = string.Format("%1", GetGame().GetTime());
        ping.ExpiresAt = GetGame().GetTime() + (m_ConfigManager.MarkerConfig.GroupPingLifetimeSeconds * 1000);
        ping.EnsureId();
        group.Pings.Insert(ping);
        return true;
    }

    ref array<ref DeutschZGroupMarkerData> GetVisibleMarkersForPlayer(string steam64)
    {
        ref array<ref DeutschZGroupMarkerData> result = new array<ref DeutschZGroupMarkerData>;
        int now = GetGame().GetTime();

        if (m_ConfigManager.MarkerConfig && m_ConfigManager.MarkerConfig.ShowGroupMarkersOnMap == 1)
        {
            DeutschZGroupData group = GetPlayerGroup(steam64);
            if (group)
            {
                foreach (DeutschZGroupMarkerData marker: group.Markers)
                {
                    if (marker)
                    {
                        result.Insert(marker);
                    }
                }
                for (int p = group.Pings.Count() - 1; p >= 0; p--)
                {
                    DeutschZGroupMarkerData ping = group.Pings.Get(p);
                    if (ping && !ping.IsExpired(now))
                    {
                        result.Insert(ping);
                    }
                    else if (ping && ping.IsExpired(now))
                    {
                        group.Pings.Remove(p);
                    }
                }
            }
        }

        if (m_ConfigManager.StaticMarkers && m_ConfigManager.StaticMarkers.StaticMarkers)
        {
            foreach (DeutschZGroupMarkerData staticMarker: m_ConfigManager.StaticMarkers.StaticMarkers)
            {
                if (staticMarker)
                {
                    result.Insert(staticMarker);
                }
            }
        }

        return result;
    }



    void UpdateOnlineMembers()
    {
        foreach (DeutschZGroupData group: m_Groups)
        {
            if (!group) continue;
            group.EnsureArrays();
            foreach (DeutschZGroupMemberData member: group.Members)
            {
                if (member)
                {
                    member.Online = 0;
                }
            }
        }

        ref array<Man> players = new array<Man>;
        GetGame().GetPlayers(players);

        foreach (Man man: players)
        {
            PlayerBase player = PlayerBase.Cast(man);
            if (!player || !player.GetIdentity())
            {
                continue;
            }

            string steam64 = player.GetIdentity().GetPlainId();
            DeutschZGroupData playerGroup = GetPlayerGroup(steam64);
            if (!playerGroup)
            {
                continue;
            }

            DeutschZGroupMemberData memberData = playerGroup.FindMember(steam64);
            if (memberData)
            {
                memberData.Online = 1;
                memberData.LastName = player.GetIdentity().GetName();
                memberData.LastKnownPosition = player.GetPosition();
                memberData.LastSeenAt = string.Format("%1", GetGame().GetTime());
                player.DeutschZGroups_SetGroupCache(playerGroup.GroupId, playerGroup.Tag, memberData.Rank);
            }
        }
    }

    ref array<ref DeutschZGroupInviteData> GetInvitesForPlayer(string steam64)
    {
        CleanupExpiredInvites();
        ref array<ref DeutschZGroupInviteData> result = new array<ref DeutschZGroupInviteData>;
        foreach (DeutschZGroupInviteData invite: m_Invites)
        {
            if (invite && invite.TargetSteam64 == steam64)
            {
                result.Insert(invite);
            }
        }
        return result;
    }

    protected string GetPrivateMarkerPath(string steam64)
    {
        return DeutschZGroupsConstants.PROFILE_PRIVATE_MARKER_ROOT + "/" + steam64 + ".json";
    }

    DeutschZPrivateMarkerSet LoadPrivateMarkers(string steam64)
    {
        ref DeutschZPrivateMarkerSet markerSet = new DeutschZPrivateMarkerSet();
        markerSet.Steam64 = steam64;
        string filePath = GetPrivateMarkerPath(steam64);
        if (FileExist(filePath))
        {
            JsonFileLoader<DeutschZPrivateMarkerSet>.JsonLoadFile(filePath, markerSet);
        }
        markerSet.Steam64 = steam64;
        markerSet.EnsureArray();
        return markerSet;
    }

    void SavePrivateMarkers(DeutschZPrivateMarkerSet markerSet)
    {
        if (!markerSet || markerSet.Steam64 == "")
        {
            return;
        }
        markerSet.EnsureArray();
        JsonFileLoader<DeutschZPrivateMarkerSet>.JsonSaveFile(GetPrivateMarkerPath(markerSet.Steam64), markerSet);
    }

    bool AddPrivateMarker(string steam64, DeutschZGroupMarkerData marker)
    {
        if (!m_ConfigManager.MainConfig || m_ConfigManager.MainConfig.EnablePrivateMarkers == 0)
        {
            return false;
        }
        if (steam64 == "" || !marker)
        {
            return false;
        }
        ref DeutschZPrivateMarkerSet markerSet = LoadPrivateMarkers(steam64);
        if (markerSet.PrivateMarkers.Count() >= m_ConfigManager.MainConfig.MaxPrivateMarkersPerPlayer)
        {
            return false;
        }
        marker.MarkerType = DeutschZGroupMarkerType.PRIVATE_MARKER;
        marker.CreatorSteam64 = steam64;
        marker.EnsureId();
        markerSet.PrivateMarkers.Insert(marker);
        SavePrivateMarkers(markerSet);
        return true;
    }

    bool RemovePrivateMarker(string steam64, string markerId)
    {
        if (!m_ConfigManager.MainConfig || m_ConfigManager.MainConfig.EnablePrivateMarkers == 0)
        {
            return false;
        }
        if (steam64 == "" || markerId == "")
        {
            return false;
        }
        ref DeutschZPrivateMarkerSet markerSet = LoadPrivateMarkers(steam64);
        for (int i = markerSet.PrivateMarkers.Count() - 1; i >= 0; i--)
        {
            DeutschZGroupMarkerData marker = markerSet.PrivateMarkers.Get(i);
            if (marker && marker.MarkerId == markerId)
            {
                markerSet.PrivateMarkers.Remove(i);
                SavePrivateMarkers(markerSet);
                return true;
            }
        }
        return false;
    }

    bool AddStaticMarker(string actorSteam64, DeutschZGroupMarkerData marker)
    {
        if (!HasPermission(actorSteam64, DeutschZGroupPermissionKeys.STATIC_MARKER_CREATE) && !HasPermission(actorSteam64, DeutschZGroupPermissionKeys.ADMIN_GROUPS))
        {
            return false;
        }
        if (!m_ConfigManager.StaticMarkers || !m_ConfigManager.StaticMarkers.StaticMarkers || !marker)
        {
            return false;
        }
        marker.MarkerType = DeutschZGroupMarkerType.SERVER_STATIC;
        marker.CreatorSteam64 = actorSteam64;
        marker.EnsureId();
        m_ConfigManager.StaticMarkers.StaticMarkers.Insert(marker);
        m_ConfigManager.SaveAll();
        return true;
    }

    bool RemoveStaticMarker(string actorSteam64, string markerId)
    {
        if (!HasPermission(actorSteam64, DeutschZGroupPermissionKeys.STATIC_MARKER_DELETE) && !HasPermission(actorSteam64, DeutschZGroupPermissionKeys.ADMIN_GROUPS))
        {
            return false;
        }
        if (!m_ConfigManager.StaticMarkers || !m_ConfigManager.StaticMarkers.StaticMarkers)
        {
            return false;
        }
        for (int i = m_ConfigManager.StaticMarkers.StaticMarkers.Count() - 1; i >= 0; i--)
        {
            DeutschZGroupMarkerData marker = m_ConfigManager.StaticMarkers.StaticMarkers.Get(i);
            if (marker && marker.MarkerId == markerId)
            {
                m_ConfigManager.StaticMarkers.StaticMarkers.Remove(i);
                m_ConfigManager.SaveAll();
                return true;
            }
        }
        return false;
    }

    bool AddGroupChatMessage(string steam64, string senderName, string message)
    {
        if (!HasPermission(steam64, DeutschZGroupPermissionKeys.GROUP_CHAT))
        {
            return false;
        }
        if (message == "")
        {
            return false;
        }
        DeutschZGroupData group = GetPlayerGroup(steam64);
        if (!group)
        {
            return false;
        }
        group.AddChat(steam64, senderName, message, m_ConfigManager.MainConfig.MaxChatHistory);
        SaveGroup(group);
        return true;
    }

    protected void AddAudit(DeutschZGroupData group, string actorSteam64, string actorName, string action, string target, string message)
    {
        if (!group || !m_ConfigManager.MainConfig || m_ConfigManager.MainConfig.EnableAuditLog == 0)
        {
            return;
        }
        group.AddAudit(actorSteam64, actorName, action, target, message, m_ConfigManager.MainConfig.MaxAuditEntries);
    }

    protected void InsertPlayerMarkers(string steam64, notnull array<ref DeutschZGroupMarkerData> outMarkers)
    {
        if (!m_ConfigManager.MarkerConfig || m_ConfigManager.MarkerConfig.ShowGroupMembersOnMap == 0)
        {
            return;
        }
        DeutschZGroupData group = GetPlayerGroup(steam64);
        if (!group)
        {
            return;
        }
        foreach (DeutschZGroupMemberData member: group.Members)
        {
            if (!member || member.Steam64 == steam64 || member.ShowOnMap == 0)
            {
                continue;
            }
            ref DeutschZGroupMarkerData playerMarker = new DeutschZGroupMarkerData();
            playerMarker.MarkerId = "PLAYER_" + member.Steam64;
            playerMarker.MarkerType = DeutschZGroupMarkerType.GROUP_PLAYER;
            playerMarker.Name = member.LastName;
            playerMarker.Icon = m_ConfigManager.MarkerConfig.DefaultPlayerIcon;
            playerMarker.Position = member.LastKnownPosition;
            playerMarker.ColorR = group.ColorR;
            playerMarker.ColorG = group.ColorG;
            playerMarker.ColorB = group.ColorB;
            playerMarker.ShowMap = member.ShowOnMap;
            playerMarker.Show3D = member.ShowIn3D;
            playerMarker.CreatorSteam64 = member.Steam64;
            outMarkers.Insert(playerMarker);
        }
    }

    protected void InsertPrivateMarkers(string steam64, notnull array<ref DeutschZGroupMarkerData> outMarkers)
    {
        if (!m_ConfigManager.MarkerConfig || m_ConfigManager.MarkerConfig.ShowPrivateMarkersOnMap == 0)
        {
            return;
        }
        ref DeutschZPrivateMarkerSet markerSet = LoadPrivateMarkers(steam64);
        foreach (DeutschZGroupMarkerData marker: markerSet.PrivateMarkers)
        {
            if (marker)
            {
                outMarkers.Insert(marker);
            }
        }
    }

    void SendSyncToPlayer(PlayerBase player)
    {
        if (!player || !player.GetIdentity())
        {
            return;
        }
        string steam64 = player.GetIdentity().GetPlainId();
        ref DeutschZGroupSyncPacket packet = BuildSyncPacket(steam64);
        Param1<DeutschZGroupSyncPacket> data = new Param1<DeutschZGroupSyncPacket>(packet);
        GetGame().RPCSingleParam(player, DeutschZGroupsRPC.GROUP_SYNC, data, true, player.GetIdentity());
    }

    void SendSyncToAllOnline()
    {
        ref array<Man> players = new array<Man>;
        GetGame().GetPlayers(players);
        foreach (Man man: players)
        {
            PlayerBase player = PlayerBase.Cast(man);
            if (player && player.GetIdentity())
            {
                SendSyncToPlayer(player);
            }
        }
    }

    string GetSharedGarageId(string steam64)
    {
        DeutschZGroupData group = GetPlayerGroup(steam64);
        if (!group) return "";
        group.EnsureId();
        return group.SharedGarageId;
    }

    string GetSharedBankAccountId(string steam64)
    {
        DeutschZGroupData group = GetPlayerGroup(steam64);
        if (!group) return "";
        group.EnsureId();
        return group.SharedBankAccountId;
    }

    DeutschZGroupSyncPacket BuildSyncPacket(string steam64)
    {
        ref DeutschZGroupSyncPacket packet = new DeutschZGroupSyncPacket();

        ref array<ref DeutschZGroupInviteData> pendingInvites = GetInvitesForPlayer(steam64);
        foreach (DeutschZGroupInviteData pendingInvite: pendingInvites)
        {
            if (pendingInvite)
            {
                packet.Invites.Insert(pendingInvite);
            }
        }

        DeutschZGroupData group = GetPlayerGroup(steam64);
        if (group)
        {
            packet.GroupId = group.GroupId;
            packet.Name = group.Name;
            packet.Tag = group.Tag;
            packet.Rank = GetPlayerRank(steam64);

            foreach (DeutschZGroupMemberData member: group.Members)
            {
                if (member)
                {
                    packet.Members.Insert(member);
                }
            }

            packet.CanManageGarage = 0;
            if (HasPermission(steam64, DeutschZGroupPermissionKeys.GARAGE_MANAGE))
            {
                packet.CanManageGarage = 1;
            }

            packet.CanManageBank = 0;
            if (HasPermission(steam64, DeutschZGroupPermissionKeys.BANK_MANAGE))
            {
                packet.CanManageBank = 1;
            }

            foreach (DeutschZGroupChatMessageData chatEntry: group.ChatHistory)
            {
                if (chatEntry)
                {
                    packet.ChatHistory.Insert(chatEntry);
                }
            }

            DeutschZGroupLevelConfigEntry level = m_ConfigManager.LevelsConfig.FindLevel(packet.Rank);
            if (level && level.Permissions)
            {
                foreach (string permission: level.Permissions)
                {
                    packet.Permissions.Insert(permission);
                }
            }
        }

        ref array<ref DeutschZGroupMarkerData> visible = GetVisibleMarkersForPlayer(steam64);
        if (group)
        {
            InsertPlayerMarkers(steam64, visible);
        }
        InsertPrivateMarkers(steam64, visible);

        foreach (DeutschZGroupMarkerData marker: visible)
        {
            if (marker)
            {
                packet.Markers.Insert(marker);
            }
        }
        return packet;
    }

    protected void CleanupExpiredInvites()
    {
        int now = GetGame().GetTime();
        for (int i = m_Invites.Count() - 1; i >= 0; i--)
        {
            DeutschZGroupInviteData invite = m_Invites.Get(i);
            if (!invite || invite.IsExpired(now))
            {
                m_Invites.Remove(i);
            }
        }
    }

    protected void CleanupExpiredPings()
    {
        int now = GetGame().GetTime();
        foreach (DeutschZGroupData group: m_Groups)
        {
            if (group && group.Pings)
            {
                for (int i = group.Pings.Count() - 1; i >= 0; i--)
                {
                    DeutschZGroupMarkerData ping = group.Pings.Get(i);
                    if (!ping || ping.IsExpired(now))
                    {
                        group.Pings.Remove(i);
                    }
                }
            }
        }
    }

    void Tick()
    {
        if (!m_ConfigManager.MainConfig)
        {
            return;
        }
        CleanupExpiredInvites();
        CleanupExpiredPings();
        UpdateOnlineMembers();

        int now = GetGame().GetTime();
        int intervalMs = m_ConfigManager.MainConfig.AutoSaveIntervalSeconds * 1000;
        if (now - m_LastAutoSave >= intervalMs)
        {
            SaveAllGroups();
            SendSyncToAllOnline();
            m_LastAutoSave = now;
        }
    }
}
