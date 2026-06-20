class DeutschZBattlepassProfileFolders
{
    static void Ensure()
    {
        if (!FileExist(DeutschZBattlepassConstants.DEUTSCHZ_ROOT))
        {
            MakeDirectory(DeutschZBattlepassConstants.DEUTSCHZ_ROOT);
        }
        if (!FileExist(DeutschZBattlepassConstants.PROFILE_ROOT))
        {
            MakeDirectory(DeutschZBattlepassConstants.PROFILE_ROOT);
        }
        if (!FileExist(DeutschZBattlepassConstants.CONFIG_ROOT))
        {
            MakeDirectory(DeutschZBattlepassConstants.CONFIG_ROOT);
        }
        if (!FileExist(DeutschZBattlepassConstants.DATA_ROOT))
        {
            MakeDirectory(DeutschZBattlepassConstants.DATA_ROOT);
        }
        if (!FileExist(DeutschZBattlepassConstants.PLAYER_ROOT))
        {
            MakeDirectory(DeutschZBattlepassConstants.PLAYER_ROOT);
        }
        if (!FileExist(DeutschZBattlepassConstants.LOG_ROOT))
        {
            MakeDirectory(DeutschZBattlepassConstants.LOG_ROOT);
        }
        if (!FileExist(DeutschZBattlepassConstants.SPAWNSELECT_ROOT))
        {
            MakeDirectory(DeutschZBattlepassConstants.SPAWNSELECT_ROOT);
        }
        if (!FileExist(DeutschZBattlepassConstants.SPAWNSELECT_CONFIG_ROOT))
        {
            MakeDirectory(DeutschZBattlepassConstants.SPAWNSELECT_CONFIG_ROOT);
        }
    }
}
