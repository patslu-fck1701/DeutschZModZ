class DeutschZBattlepassConfigManager
{
    ref DeutschZBattlepassFreeConfig FreeConfig;
    ref DeutschZBattlepassPremiumConfig PremiumConfig;

    void DeutschZBattlepassConfigManager()
    {
        FreeConfig = new DeutschZBattlepassFreeConfig();
        PremiumConfig = new DeutschZBattlepassPremiumConfig();
    }

    void Load()
    {
        DeutschZBattlepassProfileFolders.Ensure();
        LoadFreeConfig();
        LoadPremiumConfig();
    }

    protected void LoadFreeConfig()
    {
        if (FileExist(DeutschZBattlepassConstants.FREE_CONFIG_FILE))
        {
            JsonFileLoader<DeutschZBattlepassFreeConfig>.JsonLoadFile(DeutschZBattlepassConstants.FREE_CONFIG_FILE, FreeConfig);
        }
        if (!FreeConfig)
        {
            FreeConfig = new DeutschZBattlepassFreeConfig();
        }
        FreeConfig.InsertDefaults();
        JsonFileLoader<DeutschZBattlepassFreeConfig>.JsonSaveFile(DeutschZBattlepassConstants.FREE_CONFIG_FILE, FreeConfig);
    }

    protected void LoadPremiumConfig()
    {
        if (FileExist(DeutschZBattlepassConstants.PREMIUM_CONFIG_FILE))
        {
            JsonFileLoader<DeutschZBattlepassPremiumConfig>.JsonLoadFile(DeutschZBattlepassConstants.PREMIUM_CONFIG_FILE, PremiumConfig);
        }
        if (!PremiumConfig)
        {
            PremiumConfig = new DeutschZBattlepassPremiumConfig();
        }
        PremiumConfig.InsertDefaults();
        JsonFileLoader<DeutschZBattlepassPremiumConfig>.JsonSaveFile(DeutschZBattlepassConstants.PREMIUM_CONFIG_FILE, PremiumConfig);
    }
}
