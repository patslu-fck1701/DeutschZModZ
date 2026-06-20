class DeutschZBattlepassRuntime
{
    protected static ref DeutschZBattlepassManager m_Manager;

    static void SetManager(DeutschZBattlepassManager manager)
    {
        m_Manager = manager;
    }

    static DeutschZBattlepassManager GetManager()
    {
        return m_Manager;
    }

    static bool IsReady()
    {
        if (m_Manager)
        {
            return true;
        }
        return false;
    }
}
