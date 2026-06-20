class DeutschZBattlepassAPI
{
    static void AddXP(string steam64, string name, int xp, string reason)
    {
        DeutschZBattlepassManager manager = DeutschZBattlepassRuntime.GetManager();
        if (!manager)
        {
            return;
        }
        manager.AddXP(steam64, name, xp, reason);
    }

    static void SetPremium(string steam64, int premium)
    {
        DeutschZBattlepassManager manager = DeutschZBattlepassRuntime.GetManager();
        if (!manager)
        {
            return;
        }
        manager.SetPremium(steam64, premium);
    }

    static void AddTaskProgress(string steam64, string name, string taskId, int amount)
    {
        DeutschZBattlepassManager manager = DeutschZBattlepassRuntime.GetManager();
        if (!manager)
        {
            return;
        }
        manager.AddTaskProgress(steam64, name, taskId, amount);
    }
}
