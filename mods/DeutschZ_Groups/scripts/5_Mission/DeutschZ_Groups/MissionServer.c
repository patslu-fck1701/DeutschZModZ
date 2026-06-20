modded class MissionServer
{
    protected ref DeutschZGroupsManager m_DeutschZGroupsManager;

    override void OnInit()
    {
        super.OnInit();

        if (GetGame().IsServer())
        {
            DeutschZGroupsProfileFolders.Ensure();
            m_DeutschZGroupsManager = new DeutschZGroupsManager();
            DeutschZGroupsRuntime.SetManager(m_DeutschZGroupsManager);
            m_DeutschZGroupsManager.Init();
        }
    }

    override void OnUpdate(float timeslice)
    {
        super.OnUpdate(timeslice);

        if (m_DeutschZGroupsManager)
        {
            m_DeutschZGroupsManager.Tick();
        }
    }

    override void InvokeOnConnect(PlayerBase player, PlayerIdentity identity)
    {
        super.InvokeOnConnect(player, identity);
        if (m_DeutschZGroupsManager && player && identity)
        {
            m_DeutschZGroupsManager.UpdateOnlineMembers();
            m_DeutschZGroupsManager.SendSyncToPlayer(player);
        }
    }

    override void PlayerDisconnected(PlayerBase player, PlayerIdentity identity, string uid)
    {
        super.PlayerDisconnected(player, identity, uid);
        if (m_DeutschZGroupsManager)
        {
            m_DeutschZGroupsManager.UpdateOnlineMembers();
            m_DeutschZGroupsManager.SaveAllGroups();
        }
    }

    DeutschZGroupsManager DeutschZGroups_GetManager()
    {
        return m_DeutschZGroupsManager;
    }
}
