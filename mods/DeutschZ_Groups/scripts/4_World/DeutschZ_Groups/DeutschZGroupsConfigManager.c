class DeutschZGroupsConfigManager
{
    ref DeutschZGroupsConfig MainConfig;
    ref DeutschZGroupLevelsConfig LevelsConfig;
    ref DeutschZGroupsMarkerConfig MarkerConfig;
    ref DeutschZStaticMarkerSet StaticMarkers;

    void DeutschZGroupsConfigManager()
    {
        MainConfig = new DeutschZGroupsConfig();
        LevelsConfig = new DeutschZGroupLevelsConfig();
        MarkerConfig = new DeutschZGroupsMarkerConfig();
        StaticMarkers = new DeutschZStaticMarkerSet();
    }

    void LoadAll()
    {
        DeutschZGroupsProfileFolders.Ensure();
        LoadMain();
        LoadLevels();
        LoadMarkers();
        LoadStaticMarkers();
        SaveAll();
    }

    void LoadMain()
    {
        if (FileExist(DeutschZGroupsConstants.CONFIG_MAIN))
        {
            JsonFileLoader<DeutschZGroupsConfig>.JsonLoadFile(DeutschZGroupsConstants.CONFIG_MAIN, MainConfig);
        }
        else
        {
            MainConfig.Defaults();
        }
        MainConfig.Validate();
    }

    void LoadLevels()
    {
        if (FileExist(DeutschZGroupsConstants.CONFIG_LEVELS))
        {
            JsonFileLoader<DeutschZGroupLevelsConfig>.JsonLoadFile(DeutschZGroupsConstants.CONFIG_LEVELS, LevelsConfig);
        }
        else
        {
            LevelsConfig.Defaults();
        }
        LevelsConfig.Validate();
    }

    void LoadMarkers()
    {
        if (FileExist(DeutschZGroupsConstants.CONFIG_MARKERS))
        {
            JsonFileLoader<DeutschZGroupsMarkerConfig>.JsonLoadFile(DeutschZGroupsConstants.CONFIG_MARKERS, MarkerConfig);
        }
        else
        {
            MarkerConfig.Defaults();
        }
        MarkerConfig.Validate();
    }

    void LoadStaticMarkers()
    {
        if (FileExist(DeutschZGroupsConstants.CONFIG_STATIC_MARKERS))
        {
            JsonFileLoader<DeutschZStaticMarkerSet>.JsonLoadFile(DeutschZGroupsConstants.CONFIG_STATIC_MARKERS, StaticMarkers);
        }
        else
        {
            StaticMarkers.Defaults();
        }
        if (!StaticMarkers.StaticMarkers)
        {
            StaticMarkers.StaticMarkers = new array<ref DeutschZGroupMarkerData>;
        }
    }

    void SaveAll()
    {
        JsonFileLoader<DeutschZGroupsConfig>.JsonSaveFile(DeutschZGroupsConstants.CONFIG_MAIN, MainConfig);
        JsonFileLoader<DeutschZGroupLevelsConfig>.JsonSaveFile(DeutschZGroupsConstants.CONFIG_LEVELS, LevelsConfig);
        JsonFileLoader<DeutschZGroupsMarkerConfig>.JsonSaveFile(DeutschZGroupsConstants.CONFIG_MARKERS, MarkerConfig);
        JsonFileLoader<DeutschZStaticMarkerSet>.JsonSaveFile(DeutschZGroupsConstants.CONFIG_STATIC_MARKERS, StaticMarkers);
    }
}
