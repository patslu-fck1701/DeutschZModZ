/*
DeutschZ ModZ
Eigenstaendige Implementierung fuer DeutschZ.
Autor/Eigentuemer: Patrick Sluzalek / fck1701.
Projekt: DeutschZ.
Modul: DeutschZ_ConvoyZ.
Zweck der Datei: Eigene DeutschZ-JSON-Konfiguration laden, erzeugen und normalisieren.
Quellen-/Konzeptnachweis: Eigene DeutschZ-Implementierung; DayZ/CF/Expansion werden nur als Laufzeit-Abhaengigkeit/API genutzt.
Keine direkte Codeuebernahme aus Drittquellen.
*/

class DeutschZConvoyZConfig
{
    ref DeutschZConvoyZSettings Settings;
    ref DeutschZConvoyZEventDef EventData;

    void DeutschZConvoyZConfig()
    {
        Settings = new DeutschZConvoyZSettings();
        EventData = new DeutschZConvoyZEventDef();
    }

    string NormalizeProfilePath(string path)
    {
        return DeutschZConvoyZConstants.EVENTS_FILE;
    }

    void EnsureFolders()
    {
        MakeDirectory("$profile:DeutschZ");
        MakeDirectory("$profile:DeutschZ/ConvoyZ");
        MakeDirectory("$profile:DeutschZ/ConvoyZ/Data");
        MakeDirectory("$profile:DeutschZ/ConvoyZ/Logs");
        Print("[DeutschZ_ConvoyZ] EnsureFolders done: $profile:DeutschZ/ConvoyZ");
    }

    void Load()
    {
        EnsureFolders();

        Settings = new DeutschZConvoyZSettings();
        EventData = new DeutschZConvoyZEventDef();

        if (FileExist(DeutschZConvoyZConstants.SETTINGS_FILE))
        {
            JsonFileLoader<DeutschZConvoyZSettings>.JsonLoadFile(DeutschZConvoyZConstants.SETTINGS_FILE, Settings);
            Print("[DeutschZ_ConvoyZ] Settings loaded: " + DeutschZConvoyZConstants.SETTINGS_FILE);
        }
        else
        {
            JsonFileLoader<DeutschZConvoyZSettings>.JsonSaveFile(DeutschZConvoyZConstants.SETTINGS_FILE, Settings);
            Print("[DeutschZ_ConvoyZ] Settings CREATED: " + DeutschZConvoyZConstants.SETTINGS_FILE);
        }

        if (!Settings) Settings = new DeutschZConvoyZSettings();
        Settings.EventConfigPath = DeutschZConvoyZConstants.EVENTS_FILE;

        if (FileExist(DeutschZConvoyZConstants.EVENTS_FILE))
        {
            JsonFileLoader<DeutschZConvoyZEventDef>.JsonLoadFile(DeutschZConvoyZConstants.EVENTS_FILE, EventData);
            Print("[DeutschZ_ConvoyZ] Events loaded: " + DeutschZConvoyZConstants.EVENTS_FILE);
        }
        else
        {
            CreateDefaultEvent();
            JsonFileLoader<DeutschZConvoyZEventDef>.JsonSaveFile(DeutschZConvoyZConstants.EVENTS_FILE, EventData);
            Print("[DeutschZ_ConvoyZ] Events CREATED: " + DeutschZConvoyZConstants.EVENTS_FILE);
        }

        Normalize();

        JsonFileLoader<DeutschZConvoyZSettings>.JsonSaveFile(DeutschZConvoyZConstants.SETTINGS_FILE, Settings);
        JsonFileLoader<DeutschZConvoyZEventDef>.JsonSaveFile(DeutschZConvoyZConstants.EVENTS_FILE, EventData);

        Print("[DeutschZ_ConvoyZ] Config final save OK");
        Print("[DeutschZ_ConvoyZ] Runtime config folder: $profile:DeutschZ/ConvoyZ");

        DeutschZConvoyZLogger.SetDebug(Settings.EnableDebugLogs);
        DeutschZConvoyZLogger.Log("ConfigLoad", "", "", "", EventData.EventCenter, "OK", DeutschZConvoyZConstants.EVENTS_FILE);
    }

    string NormalizeCrashClassName(string className)
    {
        if (className == "Land_HACKEDCRATE") return "Land_HACKEDCRATE";
        if (className == "DZCV_ProtectedCase") return "DZCV_ProtectedCase";

        if (className == "Truck_01_Covered") return "Land_Wreck_V3S";
        if (className == "Truck_01_Chassis") return "Land_Wreck_V3S";
        if (className == "Truck_01_Box") return "Land_Wreck_V3S";
        if (className == "Truck_01_Cargo") return "Land_Wreck_V3S";
        if (className == "OffroadHatchback") return "Land_Wreck_Uaz";
        if (className == "Land_Wreck_UH1Y") return "Land_Wreck_Mi8";
        if (className.IndexOf("Land_Wreck_") == 0) return className;

        return className;
    }

    void AddOrRefreshRewardItem(string className, int quantity, float chance)
    {
        if (!EventData || !EventData.Reward || !EventData.Reward.Items || className == "") return;

        foreach (DeutschZConvoyZRewardItemDef existing: EventData.Reward.Items)
        {
            if (!existing) continue;
            if (existing.ClassName == className)
            {
                existing.Quantity = quantity;
                existing.Chance = chance;
                return;
            }
        }

        DeutschZConvoyZRewardItemDef item = new DeutschZConvoyZRewardItemDef();
        item.ClassName = className;
        item.Quantity = quantity;
        item.Chance = chance;
        EventData.Reward.Items.Insert(item);
    }

    void ApplyNormalOnlineSettings()
    {
        if (!Settings) Settings = new DeutschZConvoyZSettings();
        Settings.EnableConvoyZEvent = 1;
        Settings.RequiredAiKills = 6;
        Settings.HackDurationSeconds = 90;
        Settings.BlackboxMaxHackDistance = 3.5;
        Settings.EnableAiWaves = 1;
        Settings.WaveDelaySeconds = 150;
        Settings.UseEventMarker = 1;
        Settings.UseEvent3DMarker = 1;
        Settings.EventMarkerIcon = "Vehicle";
        Settings.EventMarkerName = "DeutschZ ConvoyZ Crash";
        Settings.EnableStatusNotifications = 1;
        Settings.StatusBarUpdateIntervalSeconds = 1;
        Settings.StatusNotifyIntervalSeconds = 20;
        Settings.StatusSyncRadius = 650.0;
        Settings.AutoStartOnMissionInit = 1;
        Settings.InitialStartDelayMinSeconds = 2100;
        Settings.InitialStartDelayMaxSeconds = 3300;
        Settings.RestartEventAfterCleanup = 1;
        Settings.RestartDelayMinSeconds = 2100;
        Settings.RestartDelayMaxSeconds = 3300;
        Settings.MaxSimultaneousEvents = 1;
        Settings.MaxEventsPerRestart = 0;
        Settings.MinOnlinePlayersToStart = 1;
        Settings.NoPlayerRetryDelaySeconds = 300;
        Settings.MaxEventRuntimeSeconds = 5400;
        Settings.BlackboxReadyTimeoutSeconds = 1800;
        Settings.AutoFailStuckEvent = 1;
        Settings.EnableDebugLogs = 0;
    }

    void EnsureNormalRewardItems()
    {
        if (!EventData.Reward) EventData.Reward = new DeutschZConvoyZRewardDef();
        if (!EventData.Reward.Items) EventData.Reward.Items = new array<ref DeutschZConvoyZRewardItemDef>;

        AddOrRefreshRewardItem("DZCV_BlackboxCore", 1, 1.0);
        AddOrRefreshRewardItem("DZCV_EncryptedDataDrive", 1, 1.0);
        AddOrRefreshRewardItem("DZCV_ClassifiedIntel", 2, 1.0);
        AddOrRefreshRewardItem("DZCV_AccessCard", 1, 1.0);
        AddOrRefreshRewardItem("DZCV_CardReader", 1, 0.8);
        AddOrRefreshRewardItem("DZ_ConvoyZ_Blackbox", 1, 1.0);
        AddOrRefreshRewardItem("DZ_ConvoyZ_EncryptedDataModule", 1, 0.9);
        AddOrRefreshRewardItem("DZ_ConvoyZ_SealedWeaponCase", 1, 0.7);
        AddOrRefreshRewardItem("DZ_ConvoyZ_DieselManifest", 1, 0.8);
        AddOrRefreshRewardItem("DZ_ConvoyZ_RadioKey", 1, 0.7);
        AddOrRefreshRewardItem("DZ_ConvoyZ_ArmorPlateBundle", 1, 0.7);
        AddOrRefreshRewardItem("DZ_EventToken", 2, 1.0);
        AddOrRefreshRewardItem("DZ_SecureSSD", 1, 0.8);
        AddOrRefreshRewardItem("DZ_MilitaryLedger", 1, 0.8);
        AddOrRefreshRewardItem("WeaponCleaningKit", 2, 1.0);
        AddOrRefreshRewardItem("NailBox", 3, 1.0);
        AddOrRefreshRewardItem("MetalPlate", 6, 0.8);
    }

    void RebuildNormalAIWaves()
    {
        if (!EventData.AIWaves) EventData.AIWaves = new array<ref DeutschZConvoyZAIWaveDef>;
        EventData.AIWaves.Clear();

        InsertNormalAIWave("wave_1", 0, 3, "eAI_SurvivorM_Denis", "DZCV_SNAFU_Rifleman", 32.0);
        InsertNormalAIWave("wave_2", 150, 3, "eAI_SurvivorM_Boris", "DZCV_SNAFU_Assault", 38.0);
        InsertNormalAIWave("wave_3", 300, 3, "eAI_SurvivorM_Elias", "DZCV_SNAFU_Heavy", 44.0);
    }

    void InsertNormalAIWave(string waveId, int delaySeconds, int count, string aiClass, string loadoutName, float radius)
    {
        DeutschZConvoyZAIWaveDef wave = new DeutschZConvoyZAIWaveDef();
        wave.WaveId = waveId;
        wave.DelaySeconds = delaySeconds;
        wave.Count = count;
        wave.AIClassName = aiClass;
        wave.DeutschZAIProfileId = "";
        wave.LoadoutName = loadoutName;

        for (int i = 0; i < 3; i++)
        {
            DeutschZConvoyZSpawnPoint sp = new DeutschZConvoyZSpawnPoint();
            sp.Position = EventData.EventCenter;
            if (i == 0)
            {
                sp.Position[0] = sp.Position[0] + radius;
                sp.Position[2] = sp.Position[2] + Math.RandomFloat(-6.0, 6.0);
            }
            else if (i == 1)
            {
                sp.Position[0] = sp.Position[0] - radius;
                sp.Position[2] = sp.Position[2] + Math.RandomFloat(-6.0, 6.0);
            }
            else
            {
                sp.Position[0] = sp.Position[0] + Math.RandomFloat(-6.0, 6.0);
                sp.Position[2] = sp.Position[2] + radius;
            }
            sp.Orientation = "0 0 0";
            wave.SpawnPoints.Insert(sp);
        }

        EventData.AIWaves.Insert(wave);
    }

    void Normalize()
    {
        if (!EventData) EventData = new DeutschZConvoyZEventDef();
        if (!EventData.Vehicles) EventData.Vehicles = new array<ref DeutschZConvoyZVehicleDef>;
        if (!EventData.CrashObjects) EventData.CrashObjects = new array<ref DeutschZConvoyZObjectDef>;
        if (!EventData.Blackbox) EventData.Blackbox = new DeutschZConvoyZBlackboxDef();
        if (!EventData.Smoke) EventData.Smoke = new DeutschZConvoyZSmokeDef();
        if (!EventData.AIWaves) EventData.AIWaves = new array<ref DeutschZConvoyZAIWaveDef>;
        if (!EventData.Reward) EventData.Reward = new DeutschZConvoyZRewardDef();
        if (!EventData.Reward.Items) EventData.Reward.Items = new array<ref DeutschZConvoyZRewardItemDef>;

        ApplyNormalOnlineSettings();
        EventData.EventRadius = 450.0;
        EventData.RequiredAiKills = 6;
        EventData.HackDurationSeconds = 90;
        EventData.Blackbox.ClassName = "Land_HACKEDCRATE";
        if (EventData.Blackbox.Position == vector.Zero) EventData.Blackbox.Position = "10124 0 5414";
        EventData.Reward.RewardContainerClassName = "DZCV_SealedRewardChest";
        EnsureNormalRewardItems();
        RebuildNormalAIWaves();

        if (EventData.Vehicles && EventData.Vehicles.Count() > 0)
        {
            foreach (DeutschZConvoyZVehicleDef veh: EventData.Vehicles)
            {
                if (!veh) continue;
                DeutschZConvoyZObjectDef oldVehicleAsStatic = new DeutschZConvoyZObjectDef();
                oldVehicleAsStatic.ClassName = NormalizeCrashClassName(veh.ClassName);
                oldVehicleAsStatic.Position = veh.Position;
                oldVehicleAsStatic.Orientation = veh.Orientation;
                oldVehicleAsStatic.Critical = veh.Critical;
                oldVehicleAsStatic.HeightOffset = Math.Max(1.0, veh.HeightOffset);
                EventData.CrashObjects.Insert(oldVehicleAsStatic);
            }
            EventData.Vehicles.Clear();
            Print("[DeutschZ_ConvoyZ] Static-only mode: deprecated Vehicles entries converted to CrashObjects and cleared.");
        }

        foreach (DeutschZConvoyZObjectDef crashObj: EventData.CrashObjects)
        {
            if (!crashObj) continue;
            crashObj.ClassName = NormalizeCrashClassName(crashObj.ClassName);
            if (crashObj.HeightOffset < 1.0)
                crashObj.HeightOffset = 1.0;
        }
        if (EventData.Blackbox.HeightOffset < 1.35)
            EventData.Blackbox.HeightOffset = 1.35;

        int waveIndex = 0;
        foreach (DeutschZConvoyZAIWaveDef wave: EventData.AIWaves)
        {
            if (!wave) continue;
            if (wave.LoadoutName == "")
            {
                if (waveIndex == 0) wave.LoadoutName = "DZCV_SNAFU_Rifleman";
                else if (waveIndex == 1) wave.LoadoutName = "DZCV_SNAFU_Assault";
                else wave.LoadoutName = "DZCV_SNAFU_Heavy";
            }
            if (wave.DeutschZAIProfileId == "convoy_guard") wave.DeutschZAIProfileId = "";
            waveIndex++;
        }
        if (EventData.RequiredAiKills <= 0) EventData.RequiredAiKills = Settings.RequiredAiKills;
        if (EventData.HackDurationSeconds <= 0) EventData.HackDurationSeconds = Settings.HackDurationSeconds;

        if (EventData.Smoke)
        {
            if (EventData.Smoke.Enabled != 0) EventData.Smoke.Enabled = 1;
            if (EventData.Smoke.Position == vector.Zero) EventData.Smoke.Position = EventData.EventCenter;
            if (EventData.Smoke.RedSmokeClassName == "") EventData.Smoke.RedSmokeClassName = "M18SmokeGrenade_Red";
            if (EventData.Smoke.YellowSmokeClassName == "") EventData.Smoke.YellowSmokeClassName = "M18SmokeGrenade_Yellow";
            if (EventData.Smoke.GreenSmokeClassName == "") EventData.Smoke.GreenSmokeClassName = "M18SmokeGrenade_Green";
            if (EventData.Smoke.WhiteSmokeClassName == "") EventData.Smoke.WhiteSmokeClassName = "M18SmokeGrenade_White";
            if (EventData.Smoke.Enabled == 0)
            {
                EventData.Smoke.Count = 0;
            }
            else
            {
                if (EventData.Smoke.Count < 1) EventData.Smoke.Count = 1;
                if (EventData.Smoke.Count > 3) EventData.Smoke.Count = 3;
            }
            if (EventData.Smoke.Radius < 0) EventData.Smoke.Radius = 0;
            if (EventData.Smoke.Radius > 25.0) EventData.Smoke.Radius = 25.0;
            if (EventData.Smoke.RefreshSeconds < 90) EventData.Smoke.RefreshSeconds = 90;
        }

        if (Settings.InitialStartDelayMinSeconds < 0) Settings.InitialStartDelayMinSeconds = 0;
        if (Settings.InitialStartDelayMaxSeconds < Settings.InitialStartDelayMinSeconds) Settings.InitialStartDelayMaxSeconds = Settings.InitialStartDelayMinSeconds;
        if (Settings.RestartDelayMinSeconds < 0) Settings.RestartDelayMinSeconds = 0;
        if (Settings.RestartDelayMaxSeconds < Settings.RestartDelayMinSeconds) Settings.RestartDelayMaxSeconds = Settings.RestartDelayMinSeconds;
        if (Settings.MaxSimultaneousEvents < 1) Settings.MaxSimultaneousEvents = 1;
        if (Settings.MaxEventsPerRestart < 0) Settings.MaxEventsPerRestart = 0;
        if (Settings.MinOnlinePlayersToStart < 0) Settings.MinOnlinePlayersToStart = 0;
        if (Settings.NoPlayerRetryDelaySeconds < 30) Settings.NoPlayerRetryDelaySeconds = 30;
        if (Settings.EnableStatusNotifications < 0) Settings.EnableStatusNotifications = 0;
        if (Settings.StatusNotifyIntervalSeconds < 3) Settings.StatusNotifyIntervalSeconds = 3;
        if (Settings.MaxEventRuntimeSeconds < 0) Settings.MaxEventRuntimeSeconds = 0;
        if (Settings.BlackboxReadyTimeoutSeconds < 0) Settings.BlackboxReadyTimeoutSeconds = 0;
    }

    void InsertCrashObject(string className, vector position, vector orientation, int critical, float heightOffset)
    {
        DeutschZConvoyZObjectDef wreck = new DeutschZConvoyZObjectDef();
        wreck.ClassName = className;
        wreck.Position = position;
        wreck.Orientation = orientation;
        wreck.Critical = critical;
        wreck.HeightOffset = heightOffset;
        EventData.CrashObjects.Insert(wreck);
    }

    void CreateDefaultEvent()
    {
        EventData = new DeutschZConvoyZEventDef();
        EventData.EventCenter = "10120 0 5410";
        EventData.RequiredAiKills = 6;
        EventData.HackDurationSeconds = 90;

        // FIX44: static military convoy scene. No drivable vehicles; use raised vanilla wreck objects.
        InsertCrashObject("Land_Wreck_V3S", "10120 0 5410", "35 0 0", 1, 1.0);
        InsertCrashObject("Land_Wreck_BMP2", "10110 0 5421", "120 0 0", 0, 1.0);
        InsertCrashObject("Land_Wreck_BRDM2", "10136 0 5400", "260 0 0", 0, 1.0);
        InsertCrashObject("Land_Wreck_Uaz", "10102 0 5404", "310 0 0", 0, 1.0);
        InsertCrashObject("Land_Wreck_HMMWV", "10143 0 5422", "80 0 0", 0, 1.0);

        EventData.Blackbox.Position = "10124 0 5414";
        EventData.Blackbox.ClassName = "Land_HACKEDCRATE";
        EventData.Smoke.Position = EventData.EventCenter;

        EventData.Reward.RewardContainerClassName = "DZCV_SealedRewardChest";
        EventData.Reward.RewardPosition = "10128 0 5417";

        DeutschZConvoyZRewardItemDef item = new DeutschZConvoyZRewardItemDef();
        item.ClassName = "PunchedCard";
        item.Quantity = 1;
        item.Chance = 1.0;
        EventData.Reward.Items.Insert(item);

        EnsureNormalRewardItems();
        RebuildNormalAIWaves();
    }
}
