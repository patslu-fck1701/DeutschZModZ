/*
DeutschZ ModZ
Eigenstaendige Implementierung fuer DeutschZ.
Autor/Eigentuemer: Patrick Sluzalek / fck1701.
Keine direkte Codeuebernahme aus Drittquellen.
Oeffentliche Quellen werden nur zur Konzept- und API-Verifikation genutzt.
*/

class DeutschZKotHZConfigManager
{
    static const string ROOT_FOLDER = "$profile:DeutschZ";
    static const string KOTH_FOLDER = "$profile:DeutschZ/KotHZ/";
    static const string CONFIG_FOLDER = "$profile:DeutschZ/KotHZ/Config/";
    static const string KOTH_CONFIG = "$profile:DeutschZ/KotHZ/Config/KotH_Config_Chernarus.json";
    static const string LOOT_POOLS_CONFIG = "$profile:DeutschZ/KotHZ/Config/Loot_Pools.json";
    static const string KOTH_LEGACY_ZONES_CONFIG = "$profile:DeutschZ/KotHZ/KOTH_Zones.json";
    static const string KOTH_LEGACY_LOOTPOOLS_CONFIG = "$profile:DeutschZ/KotHZ/KOTH_LootPools.json";
    static const string KOTH_LEGACY_WAVEPOOLS_CONFIG = "$profile:DeutschZ/KotHZ/KOTH_WavePools.json";

    protected static ref array<ref DeutschZKotHZLootPool> s_LootPools;

    static ref DeutschZKotHZConfig Load()
    {
        EnsureProfileFolder();

        DeutschZKotHZConfig config;

        bool saveConsolidated = false;

        if (!FileExist(KOTH_CONFIG))
        {
            config = new DeutschZKotHZConfig();
            JsonFileLoader<DeutschZKotHZConfig>.JsonSaveFile(KOTH_CONFIG, config);
            Print("[DeutschZ_KotHZ] CREATED DEFAULT MAIN CONFIG: " + KOTH_CONFIG);
            saveConsolidated = true;
        }
        else
        {
            config = new DeutschZKotHZConfig();
            JsonFileLoader<DeutschZKotHZConfig>.JsonLoadFile(KOTH_CONFIG, config);
        }

        if (!config)
        {
            Print("[DeutschZ_KotHZ] Main config invalid, loading defaults in memory only.");
            config = new DeutschZKotHZConfig();
        }

        if (ImportLegacySplitConfigs(config))
            saveConsolidated = true;

        if (LoadOrCreateLootPools())
            saveConsolidated = true;

        Validate(config);

        // DeutschZ KotHZ Expansion marker build: persist marker mode changes even when an older profile JSON already exists.
        saveConsolidated = true;

        if (saveConsolidated)
        {
            SaveAll(config);
            Print("[DeutschZ_KotHZ] Consolidated profile config saved: " + KOTH_CONFIG);
        }

        return config;
    }

    static ref array<ref DeutschZKotHZLootPool> GetLootPools()
    {
        if (!s_LootPools || s_LootPools.Count() == 0)
        {
            DeutschZKotHZLootPoolsConfig defaultLoot = new DeutschZKotHZLootPoolsConfig();
            s_LootPools = defaultLoot.LootPools;
        }

        return s_LootPools;
    }

    static ref DeutschZKotHZConfig Reload()
    {
        Print("[DeutschZ_KotHZ] Manual JSON reload started.");
        return Load();
    }

    protected static void SaveAll(DeutschZKotHZConfig config)
    {
        if (!config)
            return;

        JsonFileLoader<DeutschZKotHZConfig>.JsonSaveFile(KOTH_CONFIG, config);

        DeutschZKotHZLootPoolsConfig lootPoolsConfig = new DeutschZKotHZLootPoolsConfig();
        lootPoolsConfig.LootPools = GetLootPools();
        JsonFileLoader<DeutschZKotHZLootPoolsConfig>.JsonSaveFile(LOOT_POOLS_CONFIG, lootPoolsConfig);
    }

    static bool SaveProfile(DeutschZKotHZConfig config)
    {
        if (!config)
            return false;

        EnsureProfileFolder();

        Validate(config);
        SaveAll(config);
        Print("[DeutschZ_KotHZ] Profile JSON saved from admin/editor action.");
        return true;
    }

    protected static void EnsureProfileFolder()
    {
        // Same proven pattern as DeutschZ_ConvoyZ: do not rely on FileExist for folders.
        MakeDirectory(ROOT_FOLDER);
        MakeDirectory(KOTH_FOLDER);
        MakeDirectory(CONFIG_FOLDER);
        Print("[DeutschZ_KotHZ] Profile folders ensured: " + CONFIG_FOLDER);
    }

    protected static bool ImportLegacySplitConfigs(DeutschZKotHZConfig config)
    {
        bool imported = false;

        if ((!config.Zones || config.Zones.Count() == 0) && FileExist(KOTH_LEGACY_ZONES_CONFIG))
        {
            DeutschZKotHZZonesConfig zonesConfig = new DeutschZKotHZZonesConfig();
            JsonFileLoader<DeutschZKotHZZonesConfig>.JsonLoadFile(KOTH_LEGACY_ZONES_CONFIG, zonesConfig);

            if (zonesConfig && zonesConfig.Zones && zonesConfig.Zones.Count() > 0)
            {
                config.Zones = zonesConfig.Zones;
                imported = true;
                Print("[DeutschZ_KotHZ] Imported legacy zones into KotH_Config_Chernarus.json from: " + KOTH_LEGACY_ZONES_CONFIG);
            }
        }

        if ((!s_LootPools || s_LootPools.Count() == 0) && FileExist(KOTH_LEGACY_LOOTPOOLS_CONFIG))
        {
            DeutschZKotHZLootPoolsConfig lootPoolsConfig = new DeutschZKotHZLootPoolsConfig();
            JsonFileLoader<DeutschZKotHZLootPoolsConfig>.JsonLoadFile(KOTH_LEGACY_LOOTPOOLS_CONFIG, lootPoolsConfig);

            if (lootPoolsConfig && lootPoolsConfig.LootPools && lootPoolsConfig.LootPools.Count() > 0)
            {
                s_LootPools = lootPoolsConfig.LootPools;
                imported = true;
                Print("[DeutschZ_KotHZ] Imported legacy loot pools into Loot_Pools.json from: " + KOTH_LEGACY_LOOTPOOLS_CONFIG);
            }
        }

        if ((!config.WavePools || config.WavePools.Count() == 0) && FileExist(KOTH_LEGACY_WAVEPOOLS_CONFIG))
        {
            DeutschZKotHZWavePoolsConfig wavePoolsConfig = new DeutschZKotHZWavePoolsConfig();
            JsonFileLoader<DeutschZKotHZWavePoolsConfig>.JsonLoadFile(KOTH_LEGACY_WAVEPOOLS_CONFIG, wavePoolsConfig);

            if (wavePoolsConfig && wavePoolsConfig.WavePools && wavePoolsConfig.WavePools.Count() > 0)
            {
                config.WavePools = wavePoolsConfig.WavePools;
                imported = true;
                Print("[DeutschZ_KotHZ] Imported legacy wave pools into KotH_Config_Chernarus.json from: " + KOTH_LEGACY_WAVEPOOLS_CONFIG);
            }
        }

        return imported;
    }

    protected static bool LoadOrCreateLootPools()
    {
        DeutschZKotHZLootPoolsConfig lootPoolsConfig;
        bool changed = false;

        if (!FileExist(LOOT_POOLS_CONFIG))
        {
            lootPoolsConfig = new DeutschZKotHZLootPoolsConfig();

            if (s_LootPools && s_LootPools.Count() > 0)
                lootPoolsConfig.LootPools = s_LootPools;

            JsonFileLoader<DeutschZKotHZLootPoolsConfig>.JsonSaveFile(LOOT_POOLS_CONFIG, lootPoolsConfig);
            Print("[DeutschZ_KotHZ] CREATED DEFAULT LOOT CONFIG: " + LOOT_POOLS_CONFIG);
            changed = true;
        }
        else
        {
            lootPoolsConfig = new DeutschZKotHZLootPoolsConfig();
            JsonFileLoader<DeutschZKotHZLootPoolsConfig>.JsonLoadFile(LOOT_POOLS_CONFIG, lootPoolsConfig);
        }

        if (lootPoolsConfig && lootPoolsConfig.LootPools && lootPoolsConfig.LootPools.Count() > 0)
            s_LootPools = lootPoolsConfig.LootPools;
        else
        {
            DeutschZKotHZLootPoolsConfig defaultLoot = new DeutschZKotHZLootPoolsConfig();
            s_LootPools = defaultLoot.LootPools;
            changed = true;
            Print("[DeutschZ_KotHZ] Loot pools config was empty or invalid, defaults loaded: " + LOOT_POOLS_CONFIG);
        }

        if (EnsureFix17TestLootPool())
            changed = true;

        return changed;
    }

    protected static bool EnsureFix17TestLootPool()
    {
        if (!s_LootPools)
            s_LootPools = new array<ref DeutschZKotHZLootPool>;

        DeutschZKotHZLootPool defaultTestPool = null;
        DeutschZKotHZLootPoolsConfig defaults = new DeutschZKotHZLootPoolsConfig();
        if (defaults && defaults.LootPools)
        {
            foreach (DeutschZKotHZLootPool defaultPool : defaults.LootPools)
            {
                if (defaultPool && defaultPool.PoolName == "DeutschZ_Test_HighValue")
                {
                    defaultTestPool = defaultPool;
                    break;
                }
            }
        }

        if (!defaultTestPool)
            return false;

        for (int i = 0; i < s_LootPools.Count(); i++)
        {
            DeutschZKotHZLootPool existingPool = s_LootPools.Get(i);
            if (existingPool && existingPool.PoolName == "DeutschZ_Test_HighValue")
            {
                // FIX17 TESTVERSION: refresh old profile test pool in-place so the real high-value items are definitely active.
                existingPool.EditHint = defaultTestPool.EditHint;
                existingPool.RewardMode = defaultTestPool.RewardMode;
                existingPool.CrateClassName = defaultTestPool.CrateClassName;
                existingPool.CrateSpawnAtFlagpole = defaultTestPool.CrateSpawnAtFlagpole;
                existingPool.CrateSpawnDistanceFromFlagpole = defaultTestPool.CrateSpawnDistanceFromFlagpole;
                existingPool.CrateLifetimeSeconds = defaultTestPool.CrateLifetimeSeconds;
                existingPool.DeleteCrateOnEventEnd = defaultTestPool.DeleteCrateOnEventEnd;
                existingPool.Rewards = defaultTestPool.Rewards;
                Print("[DeutschZ_KotHZ] FIX17 refreshed active DeutschZ_Test_HighValue loot pool in existing profile loot config.");
                return true;
            }
        }

        s_LootPools.Insert(defaultTestPool);
        Print("[DeutschZ_KotHZ] FIX17 inserted active DeutschZ_Test_HighValue loot pool into existing profile loot config.");
        return true;
    }

    protected static void Validate(DeutschZKotHZConfig config)
    {
        if (config.MaxSimultaneousEvents <= 0)
            config.MaxSimultaneousEvents = 1;

        if (config.OwnerName == "")
            config.OwnerName = "Patrick Sluzalek";
        if (config.OwnerPlayerName == "")
            config.OwnerPlayerName = "fck1701";
        if (config.ServerName == "")
            config.ServerName = "DeutschZ";
        if (config.OwnershipNotice == "")
            config.OwnershipNotice = "DeutschZ_KotHZ is the custom KOTH framework owned and maintained by Patrick Sluzalek / fck1701 for the DeutschZ server.";

        // FIX17 TESTVERSION: force quick event start and active high-value test loot even when an older profile JSON already exists.
        config.MinStartDelayMinutes = 1;
        config.MaxStartDelayMinutes = 1;
        config.MinPlayersToStart = 1;
        config.DebugMode = 1;

        if (!config.Zones)
            config.Zones = new array<ref DeutschZKotHZZone>;

        if (!config.Rewards)
            config.Rewards = new array<ref DeutschZKotHZReward>;

        if (!s_LootPools || s_LootPools.Count() == 0)
        {
            DeutschZKotHZLootPoolsConfig defaultLoot = new DeutschZKotHZLootPoolsConfig();
            s_LootPools = defaultLoot.LootPools;
        }

        if (!config.WavePools)
        {
            DeutschZKotHZWavePoolsConfig defaultWaves = new DeutschZKotHZWavePoolsConfig();
            config.WavePools = defaultWaves.WavePools;
        }

        if (!config.NPC)
            config.NPC = new DeutschZKotHZNPCConfig();

        if (config.NPC && !config.NPC.NPCLoadoutClassNames)
            config.NPC.NPCLoadoutClassNames = new array<string>;

        if (config.NPC && !config.NPC.NPCClassNames)
            config.NPC.NPCClassNames = new array<string>;

        if (config.NPC)
        {
            // Optional NPC is parked for now. Force existing profile JSONs back to zombie-wave-only mode.
            config.NPC.EnableOptionalNPC = 0;
            config.NPC.NPCAmount = 0;
            config.NPC.NPCClassName = "";
            config.NPC.NPCClassNames.Clear();
            config.NPC.NPCLoadoutClassNames.Clear();
            if (config.NPC.NPCModelClassNames)
                config.NPC.NPCModelClassNames.Clear();
            if (config.NPC.KnownOptionalNPCClassNames)
                config.NPC.KnownOptionalNPCClassNames.Clear();
        }

        if (!config.Smoke)
            config.Smoke = new DeutschZKotHZSmokeConfig();

        if (!config.Zombies)
            config.Zombies = new DeutschZKotHZZombieConfig();

        // Backfill missing settings for existing profile JSON files.
        if (config.EnableHUD && !config.EnableProgressHUD)
            config.EnableProgressHUD = 1;

        // FIX13: statusbar distance limiter. Existing JSONs are backfilled to 500m.
        config.EnableHUDDistanceLimit = 1;
        if (config.HUDMaxDisplayDistanceMeters <= 0)
            config.HUDMaxDisplayDistanceMeters = 500.0;

        if (config.MarkerMode == "" || config.MarkerMode == "ExpansionOnly")
            config.MarkerMode = "Expansion";

        if (config.MarkerMode == "NotificationsOnly")
            config.MarkerMode = "VanillaNotifications";

        if (config.MarkerMode == "Auto" || config.MarkerMode == "Multi")
            config.MarkerMode = "Expansion";

        if (config.MarkerMode != "Off" && config.MarkerMode != "VanillaNotifications" && config.MarkerMode != "Expansion")
            config.MarkerMode = "Expansion";

        // DeutschZ KotHZ test build: markers stay routed through DeutschZ_ExpansionBridge,
        // but visible player feedback must also work through vanilla popup/chat fallback.
        config.EnsureDeutschZEventSettings();
        config.DeutschZEventSettings.Notifications.UseExpansionNotifications = 1;
        config.DeutschZEventSettings.Notifications.UseVanillaNotifications = 1;
        config.DeutschZEventSettings.Notifications.UseChatMessages = 1;
        config.DeutschZEventSettings.Markers.UseMapMarker = 1;
        config.DeutschZEventSettings.Markers.Use3DMarker = 1;
        config.ApplyDeutschZEventSettings();

        config.MarkerMode = "Expansion";
        config.EnableExpansionMarker = 1;
        config.EnableExpansion3DMarker = 1;
        config.EnableVanillaNotifications = 1;
        config.EnableVanillaChatMessages = 1;
        config.EnableMarkerFallbackNotifications = 1;

        config.MarkerEditHint = "DeutschZ KotHZ test default: map marker and 3D marker enabled through DeutschZ_ExpansionBridge; vanilla popup and chat fallback enabled for visible testing.";

        if (config.ExpansionMarkerIcon == "")
            config.ExpansionMarkerIcon = "Territory";

        if (config.RewardCrateMinimumLifetimeSeconds < 300)
            config.RewardCrateMinimumLifetimeSeconds = 1800;

        if (config.RewardCrateDespawnWarningSeconds < 0)
            config.RewardCrateDespawnWarningSeconds = 0;

        if (config.RewardCrateDespawnWarningText == "")
            config.RewardCrateDespawnWarningText = "KotH Reward-Crate despawnt in 5 Minuten: {ZONE}.";

        if (config.WinFireworkClassName == "")
            config.WinFireworkClassName = "FireworksLauncher";

        if (config.WinFireworkCount <= 0)
            config.WinFireworkCount = 3;

        if (config.WinFireworkRadius <= 0)
            config.WinFireworkRadius = 6.0;

        // Helicopter reward delivery is optional. Do not backfill Expansion helicopter classes on vanilla/CF-only servers.
        if (!config.EnableHelicopterRewardDelivery)
            config.DeliveryHelicopterClassName = "";

        if (config.DeliveryHelicopterHeight <= 0)
            config.DeliveryHelicopterHeight = 35.0;

        if (config.DeliveryHelicopterOffsetDistance <= 0)
            config.DeliveryHelicopterOffsetDistance = 120.0;

        if (config.DeliveryCrateDropHeight <= 0)
            config.DeliveryCrateDropHeight = 8.0;

        if (config.DeliveryCrateDropDelaySeconds < 0)
            config.DeliveryCrateDropDelaySeconds = 2.0;

        if (config.DeliveryHelicopterCleanupSeconds <= 0)
            config.DeliveryHelicopterCleanupSeconds = 25.0;

        if (config.DeliveryCrateLandingConfirmSeconds <= 0)
            config.DeliveryCrateLandingConfirmSeconds = 10.0;

        // FIX21: Event music is disabled by default for Safe-Boot. The previous client-synced
        // sound path could trigger native instability on some hosted servers. Re-enable only
        // after the soundset is verified on a local test server.
        config.EnableEventMusic = 0;
        config.EventMusicSoundSetName = "";
        config.EventMusicPlayOnReady = 0;
        config.EventMusicPlayOnStart = 0;
        config.EventMusicPlayOnCaptured = 0;
        config.EventMusicRadius = 0.0;
        config.EventMusicVolume = 0.0;

        // DeutschZ KotHZ marker stays red in memory for consistent event presentation.
        config.ExpansionMarkerColorARGB = ARGB(255, 255, 0, 0);


        // KOTH rewards spawn as a visible DeutschZ reward crate by default.
        foreach (DeutschZKotHZLootPool poolCheck : GetLootPools())
        {
            if (!poolCheck)
                continue;

            poolCheck.RewardMode = 1;
            if (poolCheck.CrateClassName == "" || poolCheck.CrateClassName == "SeaChest" || poolCheck.CrateClassName == "WoodenCrate" || poolCheck.CrateClassName == "DeutschZKotHZ_DropCrate")
                poolCheck.CrateClassName = "DeutschZKotHZ_RewardCrate";
            if (poolCheck.CrateSpawnDistanceFromFlagpole < 6.0)
                poolCheck.CrateSpawnDistanceFromFlagpole = 6.0;
            if (poolCheck.CrateLifetimeSeconds < config.RewardCrateMinimumLifetimeSeconds)
                poolCheck.CrateLifetimeSeconds = config.RewardCrateMinimumLifetimeSeconds;
            poolCheck.DeleteCrateOnEventEnd = 0;
        }

        if (config.Smoke)
        {
            // v1.0.30: keep red captured smoke and the mast visible longer after win.
            if (config.Smoke.CompletedSmokeSeconds < 120.0)
                config.Smoke.CompletedSmokeSeconds = 180.0;

            config.Smoke.UseObjectSmoke = 1;
            config.Smoke.UseParticleSmoke = 0;
            config.Smoke.EnableSmoke = 1;
            config.Smoke.EnableFogHazard = 0;
            config.Smoke.FogStartOnReady = 0;
            config.Smoke.FogStartOnProgress = 0;
            config.Smoke.FogEmitterCount = 0;
            config.Smoke.SmokeObjectClassNameGreen = "M18SmokeGrenade_Green";
            config.Smoke.SmokeObjectClassNameYellow = "M18SmokeGrenade_Yellow";
            config.Smoke.SmokeObjectClassNameRed = "M18SmokeGrenade_Red";
            config.Smoke.ParticleIdGreen = 0;
            config.Smoke.ParticleIdYellow = 0;
            config.Smoke.ParticleIdRed = 0;
            config.Smoke.ParticleIdWhite = 0;
            config.Smoke.ParticleIdBlack = 0;
            config.Smoke.ParticleIdBlue = 0;
            config.Smoke.FogEmitterObjectType = "";
            if (config.Smoke.FogPulseSeconds < 10)
                config.Smoke.FogPulseSeconds = 45;
            if (config.Smoke.FogEmitterCount < 0)
                config.Smoke.FogEmitterCount = 0;
            if (config.Smoke.FogRadius <= 0)
                config.Smoke.FogRadius = 85.0;
            if (!config.Smoke.SmokeCannonClassNames)
                config.Smoke.SmokeCannonClassNames = new array<string>;
            if (config.Smoke.SmokeCannonClassNames.Count() == 0)
            {
                config.Smoke.SmokeCannonClassNames.Insert("M18SmokeGrenade_Yellow");
                config.Smoke.SmokeCannonClassNames.Insert("M18SmokeGrenade_Red");
            }
        }

        if (config.Zombies)
        {
            if (config.Zombies.ZombieFallbackClassName == "")
                config.Zombies.ZombieFallbackClassName = "ZmbM_CitizenASkinny_Brown";
            if (!config.Zombies.ZombieFallbackClassNames)
                config.Zombies.ZombieFallbackClassNames = new array<string>;
            if (config.Zombies.ZombieFallbackClassNames.Count() == 0)
            {
                config.Zombies.ZombieFallbackClassNames.Insert("ZmbM_CitizenASkinny_Brown");
                config.Zombies.ZombieFallbackClassNames.Insert("ZmbM_CitizenASkinny_Blue");
                config.Zombies.ZombieFallbackClassNames.Insert("ZmbM_PatrolNormal_Autumn");
                config.Zombies.ZombieFallbackClassNames.Insert("ZmbM_SoldierNormal_Beige");
            }
        }

        foreach (DeutschZKotHZZone zone : config.Zones)
        {
            if (!zone)
                continue;

            // FIX17 TESTVERSION: all zones use the high-value loot pool and reduced capture time.
            zone.RewardPoolName = "DeutschZ_Test_HighValue";
            zone.CaptureTimeSeconds = 90;
            zone.ZombieWaveCount = 3;
            zone.ZombiesPerWave = 4;
            zone.MaxTotalZombies = 18;

            // v1.0.30: Reward crates should always spawn slightly offset from the KOTH mast.
            // Exact reward positions stay disabled by default because the crate should spawn offset from the mast.
            zone.UseExactRewardCratePosition = 0;

            if (zone.WavePoolName == "")
                zone.WavePoolName = "KVM1_Test_5x6_Zombies";

            if (!zone.StartWavesOnlyWhenPlayerInside)
                zone.StartWavesOnlyWhenPlayerInside = 1;

            if (!zone.SpawnOutdoorOnly)
                zone.SpawnOutdoorOnly = 1;

            zone.EnableFlagpole = 1;
            zone.FlagpoleClassName = "DeutschZKotHZ_RuntimeFlagpole";
            zone.EnableCrashedHeliDecoration = 0;

            if (zone.FlagClassName == "" || zone.FlagClassName == "DeutschZKotHZ_Alt_One_Flag" || zone.FlagClassName == "DeutschZKotHZ_Flag" || zone.FlagClassName == "DeutschZKotHZ_DeutschZ_KotHZ_Flag")
            {
                if (zone.ZoneName == "NWAF" || zone.ZoneName == "NWAF KOTH" || zone.ZoneName == "NWAF KOTH TEST")
                    zone.FlagClassName = "DeutschZKotHZ_NWAF_Flag";
                else if (zone.ZoneName == "Tisy" || zone.ZoneName == "TISY" || zone.ZoneName == "Tisy KOTH")
                    zone.FlagClassName = "DeutschZKotHZ_Tisy_Flag";
                else if (zone.ZoneName == "LOPA" || zone.ZoneName == "Lopa" || zone.ZoneName == "LOPA KOTH")
                    zone.FlagClassName = "DeutschZKotHZ_LOPA_Flag";
                else if (zone.ZoneName == "YRAP" || zone.ZoneName == "Yrap" || zone.ZoneName == "YRAP KOTH")
                    zone.FlagClassName = "DeutschZKotHZ_YRAP_Flag";
                else if (zone.ZoneName == "Basebuilding" || zone.ZoneName == "BaseBuilding" || zone.ZoneName == "Basebuilding KOTH")
                    zone.FlagClassName = "DeutschZKotHZ_Basebuild_Flag";
                else
                    zone.FlagClassName = "DeutschZKotHZ_DeutschZ_KotHZ_Flag";
            }

            if (zone.FlagVisualHeightOffset <= 0)
                zone.FlagVisualHeightOffset = 13.0;

            if (!zone.NPCClassNames)
                zone.NPCClassNames = new array<string>;

            if (!zone.NPCLoadoutClassNames)
                zone.NPCLoadoutClassNames = new array<string>;

            zone.EnableOptionalNPC = 0;
            zone.NPCAmount = 0;
            zone.NPCClassNames.Clear();
            zone.NPCLoadoutClassNames.Clear();

            if (!zone.ZombieTypes)
                zone.ZombieTypes = new array<string>;

            if (zone.ZombieTypes.Count() == 0)
            {
                zone.ZombieTypes.Insert("ZmbM_PatrolNormal_Autumn");
                zone.ZombieTypes.Insert("ZmbM_PatrolNormal_Summer");
                zone.ZombieTypes.Insert("ZmbM_SoldierNormal_Beige");
                zone.ZombieTypes.Insert("ZmbM_CitizenASkinny_Brown");
                zone.ZombieTypes.Insert("ZmbM_CitizenASkinny_Blue");
                zone.ZombieTypes.Insert("ZmbM_NBC_Yellow");
            }
        }
    }
}
