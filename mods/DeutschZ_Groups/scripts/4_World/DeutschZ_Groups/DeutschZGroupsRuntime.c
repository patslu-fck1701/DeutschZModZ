class DeutschZGroupsRuntime
{
    protected static ref DeutschZGroupsManager m_Manager;

    static void SetManager(DeutschZGroupsManager manager)
    {
        m_Manager = manager;
    }

    static DeutschZGroupsManager GetManager()
    {
        return m_Manager;
    }

    static bool IsReady()
    {
        return m_Manager != NULL;
    }
}
