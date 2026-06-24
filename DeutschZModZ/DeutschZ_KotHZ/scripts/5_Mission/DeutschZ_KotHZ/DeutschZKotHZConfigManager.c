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
        // DeutschZ HARD AUTOCONFIG SAFEBOOT 2026-06-23
        // Do not JsonLoadFile old profile configs during mission bootstrap.
        // Broken/old JSON can crash the DayZ VM before Validate() can repair it.
        // Always create a fresh default config and write it to profile first.
        EnsureProfileFolder();

        DeutschZKotHZConfig config = new DeutschZKotHZConfig();

        DeutschZKotHZLootPoolsConfig defaultLoot = new DeutschZKotHZLootPoolsConfig();
        if (defaultLoot && defaultLoot.LootPools)
            s_LootPools = defaultLoot.LootPools;

        EnsureFix17TestLootPool();
        Validate(config);
        SaveAll(config);

        Print("[DeutschZ_KotHZ] HARD AUTOCONFIG: default configs generated/refreshed; old profile JSON was not loaded.");
        Print("[DeutschZ_KotHZ] Generated: " + KOTH_CONFIG);
        Print("[DeutschZ_KotHZ] Generated: " + LOOT_POOLS_CONFIG);

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

    protected static bool SanitizeMainConfigBeforeLoad()
    {
        // FIX: Some generated/test configs used unsigned ARGB JSON (4294909984).
        // DayZ Enforce int is signed; JsonLoadFile throws before Validate() can repair it.
        // Repair the file as plain text before JsonLoadFile touches it.
        if (!FileExist(KOTH_CONFIG))
            return false;

        string content = ReadTextFile(KOTH_CONFIG);
        if (content == "")
            return false;

        bool changed = false;

        if (content.IndexOf("\"ExpansionMarkerColorARGB\": 4294909984") >= 0)
        {
            content.Replace("\"ExpansionMarkerColorARGB\": 4294909984", "\"ExpansionMarkerColorARGB\": -57312");
            changed = true;
        }

        if (content.IndexOf("\"ExpansionMarkerColorARGB\": \"4294909984\"") >= 0)
        {
            content.Replace("\"ExpansionMarkerColorARGB\": \"4294909984\"", "\"ExpansionMarkerColorARGB\": -57312");
            changed = true;
        }

        if (content.IndexOf("\"ExpansionMarkerColorARGB\": 4278190335") >= 0)
        {
            content.Replace("\"ExpansionMarkerColorARGB\": 4278190335", "\"ExpansionMarkerColorARGB\": -16776961");
            changed = true;
        }

        if (changed)
        {
            WriteTextFile(KOTH_CONFIG, content);
            Print("[DeutschZ_KotHZ] Repaired JSON-safe signed ExpansionMarkerColorARGB before JsonLoadFile: " + KOTH_CONFIG);
        }

        return changed;
    }

    protected static string ReadTextFile(string path)
    {
        string content = "";
        FileHandle file = OpenFile(path, FileMode.READ);
        if (!file)
            return content;

        string line;
        while (FGets(file, line) >= 0)
        {
            content = content + line + "\n";
        }

        CloseFile(file);
        return content;
    }

    protected static bool WriteTextFile(string path, string content)
    {
        FileHandle file = OpenFile(path, FileMode.WRITE);
        if (!file)
            return false;

        FPrintln(file, content);
        CloseFile(file);
        return true;
    }

    protected static bool ImportLegacySplitConfigs(DeutschZKotHZConfig config)
    {
        // HARD AUTOCONFIG SAFEBOOT: legacy split configs are intentionally not loaded during startup.
        // Reason: JsonLoadFile on stale profile files can crash the VM before fallback code executes.
        return false;
    }

    protected static bool LoadOrCreateLootPools()
    {
        // HARD AUTOCONFIG SAFEBOOT: never load old Loot_Pools.json during startup.
        DeutschZKotHZLootPoolsConfig defaultLoot = new DeutschZKotHZLootPoolsConfig();
        if (defaultLoot && defaultLoot.LootPools)
            s_LootPools = defaultLoot.LootPools;

        EnsureFix17TestLootPool();

        DeutschZKotHZLootPoolsConfig saveLoot = new DeutschZKotHZLootPoolsConfig();
        saveLoot.LootPools = GetLootPools();
        JsonFileLoader<DeutschZKotHZLootPoolsConfig>.JsonSaveFile(LOOT_POOLS_CONFIG, saveLoot);
        Print("[DeutschZ_KotHZ] HARD AUTOCONFIG: Loot_Pools.json generated/refreshed without JsonLoadFile.");
        return true;
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

    protected static int GetNormalCaptureTimeSeconds(string zoneName)
    {
        if (zoneName == "NWAF" || zoneName == "NWAF KOTH" || zoneName == "NWAF KOTH TEST")
            return 720;
        if (zoneName == "Tisy" || zoneName == "TISY" || zoneName == "Tisy KOTH")
            return 720;
        if (zoneName == "LOPA" || zoneName == "Lopa" || zoneName == "LOPA KOTH")
            return 660;
        if (zoneName == "YRAP" || zoneName == "Yrap" || zoneName == "YRAP KOTH")
            return 660;
        return 600;
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

        // V0.9.3 NORMAL: online-test rotation. No more one-minute test spam.
        config.MinStartDelayMinutes = 35;
        config.MaxStartDelayMinutes = 55;
        config.MinPlayersToStart = 1;
        config.DebugMode = 0;
        config.EnableHUD = 1;
        config.EnableProgressHUD = 1;
        config.HUDUpdateIntervalSeconds = 1;

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

        // DeutschZ KotHZ Expansion marker build: force generated and existing profile JSON files to Expansion markers for this build.
        config.MarkerMode = "Expansion";
        config.EnableExpansionMarker = 1;
        config.EnableExpansion3DMarker = 1;
        config.EnableExpansionNotifications = 1;
        config.EnableVanillaNotifications = 0;
        config.EnableMarkerFallbackNotifications = 0;

        config.MarkerEditHint = "DeutschZ KotHZ default: Expansion marker only. Third-party marker modes are intentionally disabled. Expansion notification only; vanilla popup disabled to avoid duplicates.";

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

        if (config.EventMusicSoundSetName == "")
            config.EventMusicSoundSetName = "DeutschZ_KotHZ_EventMusic_SoundSet";

        // V093 gameplay test: music is enabled for KotHZ start/captured phases. Ready phase stays quiet.
        config.EnableEventMusic = 1;
        config.EventMusicPlayOnReady = 0;
        config.EventMusicPlayOnStart = 1;
        config.EventMusicPlayOnCaptured = 1;

        if (config.EventMusicRadius <= 0)
            config.EventMusicRadius = 180.0;

        if (config.EventMusicVolume <= 0)
            config.EventMusicVolume = 1.0;

        // DeutschZ KotHZ marker: klares Rot, getrennt von ConvoyZ/CourierZ/GroundZero.
        // IMPORTANT: keep this as signed 32-bit JSON-safe int. 0xFFFF2020 as unsigned (4294909984)
        // crashes JsonLoadFile with "Cannot convert to int" on DayZ servers.
        config.ExpansionMarkerColorARGB = -57312;


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
            // FIX42: Stage-0 safe default. Risky visual systems stay off until tested separately.
            if (config.Smoke.CompletedSmokeSeconds < 120.0)
                config.Smoke.CompletedSmokeSeconds = 180.0;

            config.Smoke.UseObjectSmoke = 0;
            config.Smoke.UseParticleSmoke = 0;
            config.Smoke.EnableSmoke = 0;
            config.Smoke.EnableFogHazard = 0;
            config.Smoke.EnableSmokeCannons = 0;
            config.Smoke.FogStartOnReady = 0;
            config.Smoke.FogStartOnProgress = 0;
            config.Smoke.FogStartOnCompleted = 0;
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

            // V0.9.3 NORMAL: all zones use the high-value event item pool and normal online-test pacing.
            zone.RewardPoolName = "DeutschZ_Test_HighValue";
            zone.Radius = 25.0;
            zone.CaptureTimeSeconds = GetNormalCaptureTimeSeconds(zone.ZoneName);
            zone.EnableZombieSpawns = 1;
            zone.InitialZombieSpawnCount = 0;
            zone.ZombieWaveCount = 5;
            zone.ZombiesPerWave = 6;
            zone.MaxTotalZombies = 30;
            zone.SecondsBetweenZombieWaves = 120;
            zone.ZombieSpawnMinDistance = 18.0;
            zone.ZombieSpawnMaxDistance = 42.0;
            zone.WavePoolName = "DeutschZ_Normal_3AI_30Zombies";

            // v1.0.30: Reward crates should always spawn slightly offset from the KOTH mast.
            // Exact reward positions stay disabled by default because the crate should spawn offset from the mast.
            zone.UseExactRewardCratePosition = 0;

            if (zone.WavePoolName == "" || zone.WavePoolName == "KVM1_Test_5x6_Zombies" || zone.WavePoolName == "NWAF_Military_Zombies" || zone.WavePoolName == "Military_Light_Zombies")
                zone.WavePoolName = "DeutschZ_Normal_3AI_30Zombies";

            if (!zone.StartWavesOnlyWhenPlayerInside)
                zone.StartWavesOnlyWhenPlayerInside = 1;

            if (!zone.SpawnOutdoorOnly)
                zone.SpawnOutdoorOnly = 1;

            zone.EnableFlagpole = 1;
            zone.FlagpoleClassName = "SAFE_VISIBLE_FLAG_ONLY";
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
