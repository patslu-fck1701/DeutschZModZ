class DeutschZBattlepassClientState
{
    protected static ref DeutschZBattlepassSyncPacket m_Sync;

    static void Init()
    {
        if (!m_Sync)
        {
            m_Sync = new DeutschZBattlepassSyncPacket();
        }
    }

    static void SetSync(DeutschZBattlepassSyncPacket packet)
    {
        if (!packet)
        {
            return;
        }
        m_Sync = packet;
    }

    static DeutschZBattlepassSyncPacket GetSync()
    {
        Init();
        return m_Sync;
    }

    static DeutschZBattlepassPlayerData GetPlayer()
    {
        Init();
        return m_Sync.Player;
    }

    static int GetLevel()
    {
        Init();
        if (!m_Sync.Player)
        {
            return 1;
        }
        return m_Sync.Player.Level;
    }

    static int GetXP()
    {
        Init();
        if (!m_Sync.Player)
        {
            return 0;
        }
        return m_Sync.Player.XP;
    }
}
