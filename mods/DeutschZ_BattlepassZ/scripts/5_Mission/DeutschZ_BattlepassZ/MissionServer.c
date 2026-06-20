modded class MissionServer
{
    protected ref DeutschZBattlepassManager m_DeutschZBattlepassManager;

    override void OnInit()
    {
        super.OnInit();

        if (GetGame().IsServer())
        {
            DeutschZBattlepassProfileFolders.Ensure();
            m_DeutschZBattlepassManager = new DeutschZBattlepassManager();
            DeutschZBattlepassRuntime.SetManager(m_DeutschZBattlepassManager);
            m_DeutschZBattlepassManager.Init();
        }
    }

    override void OnUpdate(float timeslice)
    {
        super.OnUpdate(timeslice);
        if (m_DeutschZBattlepassManager)
        {
            m_DeutschZBattlepassManager.Tick();
        }
    }

    override void InvokeOnConnect(PlayerBase player, PlayerIdentity identity)
    {
        super.InvokeOnConnect(player, identity);
        if (m_DeutschZBattlepassManager && player && identity)
        {
            m_DeutschZBattlepassManager.GetPlayerData(identity.GetPlainId(), identity.GetName());
            m_DeutschZBattlepassManager.SendSyncToPlayer(player);
        }
    }

    override void PlayerDisconnected(PlayerBase player, PlayerIdentity identity, string uid)
    {
        super.PlayerDisconnected(player, identity, uid);
    }
}
