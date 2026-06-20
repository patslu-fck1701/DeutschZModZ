class DeutschZGroupsClientState
{
    protected static ref DeutschZGroupSyncPacket m_LastSync;
    protected static ref array<ref DeutschZGroupInviteData> m_PendingInvites;

    static void Init()
    {
        if (!m_LastSync)
        {
            m_LastSync = new DeutschZGroupSyncPacket();
        }
        if (!m_PendingInvites)
        {
            m_PendingInvites = new array<ref DeutschZGroupInviteData>;
        }
    }

    static void SetSync(DeutschZGroupSyncPacket packet)
    {
        Init();
        if (!packet)
        {
            m_LastSync = new DeutschZGroupSyncPacket();
            m_PendingInvites.Clear();
            return;
        }
        m_LastSync = packet;
        m_PendingInvites.Clear();
        if (packet.Invites)
        {
            foreach (DeutschZGroupInviteData invite: packet.Invites)
            {
                if (invite)
                {
                    m_PendingInvites.Insert(invite);
                }
            }
        }
    }

    static DeutschZGroupSyncPacket GetSync()
    {
        Init();
        return m_LastSync;
    }

    static bool HasGroup()
    {
        Init();
        return m_LastSync && m_LastSync.GroupId != "";
    }

    static bool HasPermission(string permission)
    {
        Init();
        if (!m_LastSync || !m_LastSync.Permissions)
        {
            return false;
        }
        foreach (string entry: m_LastSync.Permissions)
        {
            if (entry == permission)
            {
                return true;
            }
        }
        return false;
    }

    static void SetPendingInvites(array<ref DeutschZGroupInviteData> invites)
    {
        Init();
        m_PendingInvites.Clear();
        if (!invites)
        {
            return;
        }
        foreach (DeutschZGroupInviteData invite: invites)
        {
            if (invite)
            {
                m_PendingInvites.Insert(invite);
            }
        }
    }

    static ref array<ref DeutschZGroupInviteData> GetPendingInvites()
    {
        Init();
        return m_PendingInvites;
    }
}
