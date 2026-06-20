class DeutschZGroupMarkerData
{
    string MarkerId = "";
    int MarkerType = DeutschZGroupMarkerType.GROUP_MARKER;
    string Name = "";
    string Icon = DeutschZGroupsMarkerIcons.BASE;
    vector Position = "0 0 0";
    int ColorR = 255;
    int ColorG = 0;
    int ColorB = 0;
    int ShowMap = 1;
    int Show3D = 0;
    int ShowGPS = 0;
    int Radius = 0;
    int RadiusColorR = 255;
    int RadiusColorG = 0;
    int RadiusColorB = 0;
    string CreatorSteam64 = "";
    string CreatedAt = "";
    int ExpiresAt = 0;

    void EnsureId()
    {
        if (MarkerId == "")
        {
            MarkerId = string.Format("DZM_%1_%2", GetGame().GetTime(), Math.RandomInt(1000, 9999));
        }
    }

    bool IsExpired(int now)
    {
        if (ExpiresAt <= 0)
        {
            return false;
        }
        return now >= ExpiresAt;
    }
}

class DeutschZGroupMemberData
{
    string Steam64 = "";
    string LastName = "";
    string Rank = "Rekrut";
    string JoinedAt = "";
    string LastSeenAt = "";
    int Online = 0;
    int Muted = 0;
    int ShowOnMap = 1;
    int ShowIn3D = 0;
    vector LastKnownPosition = "0 0 0";

    bool IsValid()
    {
        return Steam64 != "";
    }
}

class DeutschZGroupInviteData
{
    string InviteId = "";
    string GroupId = "";
    string InviterSteam64 = "";
    string InviterName = "";
    string TargetSteam64 = "";
    string TargetName = "";
    string CreatedAt = "";
    int ExpiresAt = 0;

    void EnsureId()
    {
        if (InviteId == "")
        {
            InviteId = string.Format("DZI_%1_%2", GetGame().GetTime(), Math.RandomInt(1000, 9999));
        }
    }

    bool IsExpired(int now)
    {
        if (ExpiresAt <= 0)
        {
            return false;
        }
        return now >= ExpiresAt;
    }
}

class DeutschZGroupChatMessageData
{
    string MessageId = "";
    string SenderSteam64 = "";
    string SenderName = "";
    string Message = "";
    string CreatedAt = "";

    void EnsureId()
    {
        if (MessageId == "")
        {
            MessageId = string.Format("DZC_%1_%2", GetGame().GetTime(), Math.RandomInt(1000, 9999));
        }
    }
}

class DeutschZGroupAuditEntryData
{
    string EntryId = "";
    string ActorSteam64 = "";
    string ActorName = "";
    string Action = "";
    string Target = "";
    string Message = "";
    string CreatedAt = "";

    void EnsureId()
    {
        if (EntryId == "")
        {
            EntryId = string.Format("DZA_%1_%2", GetGame().GetTime(), Math.RandomInt(1000, 9999));
        }
    }
}

class DeutschZGroupAllianceData
{
    string GroupId = "";
    string Tag = "";
    string Name = "";
    int Accepted = 0;
}

class DeutschZGroupData
{
    string GroupId = "";
    string Name = "";
    string Tag = "";
    string OwnerSteam64 = "";
    string CreatedAt = "";
    string LastActivity = "";
    string PublicDescription = "";
    string SharedGarageId = "";
    string SharedBankAccountId = "";
    int Level = 1;
    int Locked = 0;
    int ColorR = 200;
    int ColorG = 0;
    int ColorB = 0;
    int MaxMembers = 12;
    int MaxMarkers = 25;
    ref array<ref DeutschZGroupMemberData> Members;
    ref array<ref DeutschZGroupMarkerData> Markers;
    ref array<ref DeutschZGroupMarkerData> Pings;
    ref array<ref DeutschZGroupChatMessageData> ChatHistory;
    ref array<ref DeutschZGroupAuditEntryData> AuditLog;
    ref array<ref DeutschZGroupAllianceData> Alliances;

    void DeutschZGroupData()
    {
        Members = new array<ref DeutschZGroupMemberData>;
        Markers = new array<ref DeutschZGroupMarkerData>;
        Pings = new array<ref DeutschZGroupMarkerData>;
        ChatHistory = new array<ref DeutschZGroupChatMessageData>;
        AuditLog = new array<ref DeutschZGroupAuditEntryData>;
        Alliances = new array<ref DeutschZGroupAllianceData>;
    }

    void EnsureArrays()
    {
        if (!Members) Members = new array<ref DeutschZGroupMemberData>;
        if (!Markers) Markers = new array<ref DeutschZGroupMarkerData>;
        if (!Pings) Pings = new array<ref DeutschZGroupMarkerData>;
        if (!ChatHistory) ChatHistory = new array<ref DeutschZGroupChatMessageData>;
        if (!AuditLog) AuditLog = new array<ref DeutschZGroupAuditEntryData>;
        if (!Alliances) Alliances = new array<ref DeutschZGroupAllianceData>;
    }

    void EnsureId()
    {
        if (GroupId == "")
        {
            GroupId = string.Format("DZG_%1_%2", GetGame().GetTime(), Math.RandomInt(1000, 9999));
        }
        if (SharedGarageId == "") SharedGarageId = GroupId;
        if (SharedBankAccountId == "") SharedBankAccountId = GroupId;
    }

    DeutschZGroupMemberData FindMember(string steam64)
    {
        EnsureArrays();
        foreach (DeutschZGroupMemberData member: Members)
        {
            if (member && member.Steam64 == steam64) return member;
        }
        return NULL;
    }

    bool HasMember(string steam64)
    {
        return FindMember(steam64) != NULL;
    }

    bool AddMember(string steam64, string name, string rank)
    {
        EnsureArrays();
        if (steam64 == "" || HasMember(steam64) || Members.Count() >= MaxMembers) return false;
        ref DeutschZGroupMemberData member = new DeutschZGroupMemberData();
        member.Steam64 = steam64;
        member.LastName = name;
        member.Rank = rank;
        member.JoinedAt = string.Format("%1", GetGame().GetTime());
        Members.Insert(member);
        LastActivity = string.Format("%1", GetGame().GetTime());
        return true;
    }

    bool RemoveMember(string steam64)
    {
        EnsureArrays();
        for (int i = Members.Count() - 1; i >= 0; i--)
        {
            DeutschZGroupMemberData member = Members.Get(i);
            if (member && member.Steam64 == steam64)
            {
                Members.Remove(i);
                LastActivity = string.Format("%1", GetGame().GetTime());
                return true;
            }
        }
        return false;
    }

    bool SetMemberRank(string steam64, string rank)
    {
        DeutschZGroupMemberData member = FindMember(steam64);
        if (!member) return false;
        member.Rank = rank;
        LastActivity = string.Format("%1", GetGame().GetTime());
        return true;
    }

    int GetMemberCount()
    {
        EnsureArrays();
        return Members.Count();
    }

    void AddAudit(string actorSteam64, string actorName, string action, string target, string message, int maxEntries)
    {
        EnsureArrays();
        ref DeutschZGroupAuditEntryData entry = new DeutschZGroupAuditEntryData();
        entry.ActorSteam64 = actorSteam64;
        entry.ActorName = actorName;
        entry.Action = action;
        entry.Target = target;
        entry.Message = message;
        entry.CreatedAt = string.Format("%1", GetGame().GetTime());
        entry.EnsureId();
        AuditLog.Insert(entry);
        while (AuditLog.Count() > maxEntries && AuditLog.Count() > 0) AuditLog.Remove(0);
    }

    void AddChat(string steam64, string name, string message, int maxEntries)
    {
        EnsureArrays();
        ref DeutschZGroupChatMessageData entry = new DeutschZGroupChatMessageData();
        entry.SenderSteam64 = steam64;
        entry.SenderName = name;
        entry.Message = message;
        entry.CreatedAt = string.Format("%1", GetGame().GetTime());
        entry.EnsureId();
        ChatHistory.Insert(entry);
        while (ChatHistory.Count() > maxEntries && ChatHistory.Count() > 0) ChatHistory.Remove(0);
    }
}

class DeutschZPrivateMarkerSet
{
    string Steam64 = "";
    ref array<ref DeutschZGroupMarkerData> PrivateMarkers;

    void DeutschZPrivateMarkerSet()
    {
        PrivateMarkers = new array<ref DeutschZGroupMarkerData>;
    }

    void EnsureArray()
    {
        if (!PrivateMarkers) PrivateMarkers = new array<ref DeutschZGroupMarkerData>;
    }
}

class DeutschZStaticMarkerSet
{
    int ConfigVersion = 1;
    ref array<ref DeutschZGroupMarkerData> StaticMarkers;

    void DeutschZStaticMarkerSet()
    {
        StaticMarkers = new array<ref DeutschZGroupMarkerData>;
    }

    void Defaults()
    {
        if (!StaticMarkers) StaticMarkers = new array<ref DeutschZGroupMarkerData>;
        StaticMarkers.Clear();
    }
}

class DeutschZGroupSyncPacket
{
    string GroupId = "";
    string Name = "";
    string Tag = "";
    string Rank = "";
    int CanManageGarage = 0;
    int CanManageBank = 0;
    ref array<ref DeutschZGroupMemberData> Members;
    ref array<ref DeutschZGroupMarkerData> Markers;
    ref array<ref DeutschZGroupInviteData> Invites;
    ref array<ref DeutschZGroupChatMessageData> ChatHistory;
    ref array<string> Permissions;

    void DeutschZGroupSyncPacket()
    {
        Members = new array<ref DeutschZGroupMemberData>;
        Markers = new array<ref DeutschZGroupMarkerData>;
        Invites = new array<ref DeutschZGroupInviteData>;
        ChatHistory = new array<ref DeutschZGroupChatMessageData>;
        Permissions = new array<string>;
    }
}

class DeutschZGroupCreateRequest
{
    string Name = "";
    string Tag = "";
}

class DeutschZGroupInviteRequest
{
    string TargetSteam64 = "";
    string TargetName = "";
}

class DeutschZGroupRankRequest
{
    string TargetSteam64 = "";
    string NewRank = "";
}

class DeutschZGroupMarkerRequest
{
    ref DeutschZGroupMarkerData Marker;

    void DeutschZGroupMarkerRequest()
    {
        Marker = new DeutschZGroupMarkerData();
    }
}

class DeutschZGroupMarkerRemoveRequest
{
    string MarkerId = "";
}

class DeutschZGroupChatRequest
{
    string Message = "";
}
