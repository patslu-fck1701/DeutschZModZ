class DeutschZTraderZ_FileUtil
{
    static void EnsureFolders()
    {
        if (!FileExist(DeutschZTraderZ_Constants.ROOT_FOLDER)) MakeDirectory(DeutschZTraderZ_Constants.ROOT_FOLDER);
        if (!FileExist(DeutschZTraderZ_Constants.TRADERZ_FOLDER)) MakeDirectory(DeutschZTraderZ_Constants.TRADERZ_FOLDER);
        if (!FileExist(DeutschZTraderZ_Constants.CONFIG_FOLDER)) MakeDirectory(DeutschZTraderZ_Constants.CONFIG_FOLDER);
        if (!FileExist(DeutschZTraderZ_Constants.MARKET_FOLDER)) MakeDirectory(DeutschZTraderZ_Constants.MARKET_FOLDER);
        if (!FileExist(DeutschZTraderZ_Constants.DATA_FOLDER)) MakeDirectory(DeutschZTraderZ_Constants.DATA_FOLDER);
        if (!FileExist(DeutschZTraderZ_Constants.LOG_FOLDER)) MakeDirectory(DeutschZTraderZ_Constants.LOG_FOLDER);
    }
}
