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
        MakeDirectory(DeutschZConvoyZConstants.CONFIG_DIR);
        MakeDirectory("$profile:DeutschZ/ConvoyZ/Data");
        MakeDirectory("$profile:DeutschZ/ConvoyZ/Logs");
        Print("[DeutschZ_ConvoyZ] EnsureFolders done: $profile:DeutschZ/ConvoyZ + Config/Data/Logs");
    }

    bool IsSettingsFileSafe(string path)
    {
        if (!FileExist(path))
            return false;

        if (FileContainsText(path, "\"Settings\"") && FileContainsText(path, "\"EventData\""))
            return false;

        if (!FileContainsText(path, "\"EnableConvoyZEvent\""))
            return false;

        return true;
    }

    bool IsEventsFileSafe(string path)
    {
        if (!FileExist(path))
            return false;

        if (FileContainsText(path, "\"Settings\"") && FileContainsText(path, "\"EventData\""))
            return false;

        if (!FileContainsText(path, "\"EventName\""))
            return false;

        if (!FileContainsText(path, "\"Blackbox\""))
            return false;

        if (!FileContainsText(path, "\"Reward\""))
            return false;

        return true;
    }

    bool FileContainsText(string path, string needle)
    {
        if (!FileExist(path))
            return false;

        FileHandle file = OpenFile(path, FileMode.READ);
        if (!file)
            return false;

        string line;
        while (FGets(file, line) >= 0)
        {
            if (line.IndexOf(needle) >= 0)
            {
                CloseFile(file);
                return true;
            }
        }

        CloseFile(file);
        return false;
    }

    void Load()
    {
        EnsureFolders();

        bool generatedSettings = false;
        bool generatedEvents = false;

        Settings = new DeutschZConvoyZSettings();
        EventData = new DeutschZConvoyZEventDef();

        // DeutschZ FIX: Do NOT overwrite existing profile JSON on every server start.
        // Defaults are generated only when the file is missing/deleted.
        if (FileExist(DeutschZConvoyZConstants.SETTINGS_FILE))
        {
            JsonFileLoader<DeutschZConvoyZSettings>.JsonLoadFile(DeutschZConvoyZConstants.SETTINGS_FILE, Settings);
            Print("[DeutschZ_ConvoyZ] Loaded existing config: " + DeutschZConvoyZConstants.SETTINGS_FILE);
        }
        else
        {
            generatedSettings = true;
            Print("[DeutschZ_ConvoyZ] Settings missing, generating defaults once: " + DeutschZConvoyZConstants.SETTINGS_FILE);
        }

        if (FileExist(DeutschZConvoyZConstants.EVENTS_FILE))
        {
            JsonFileLoader<DeutschZConvoyZEventDef>.JsonLoadFile(DeutschZConvoyZConstants.EVENTS_FILE, EventData);
            Print("[DeutschZ_ConvoyZ] Loaded existing events: " + DeutschZConvoyZConstants.EVENTS_FILE);
        }
        else
        {
            generatedEvents = true;
            CreateDefaultEvent();
            Print("[DeutschZ_ConvoyZ] Events missing, generating defaults once: " + DeutschZConvoyZConstants.EVENTS_FILE);
        }

        if (!Settings) Settings = new DeutschZConvoyZSettings();
        if (!EventData) EventData = new DeutschZConvoyZEventDef();

        Settings.EventConfigPath = DeutschZConvoyZConstants.EVENTS_FILE;
        Normalize();

        // Only persist defaults for missing files. Existing admin-edited JSON stays untouched.
        if (generatedSettings)
            JsonFileLoader<DeutschZConvoyZSettings>.JsonSaveFile(DeutschZConvoyZConstants.SETTINGS_FILE, Settings);

        if (generatedEvents)
            JsonFileLoader<DeutschZConvoyZEventDef>.JsonSaveFile(DeutschZConvoyZConstants.EVENTS_FILE, EventData);

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

        if (Settings.EventConfigPath == "") Settings.EventConfigPath = DeutschZConvoyZConstants.EVENTS_FILE;
        if (Settings.RequiredAiKills <= 0) Settings.RequiredAiKills = 9;
        if (Settings.HackDurationSeconds <= 0) Settings.HackDurationSeconds = 90;
        if (Settings.BlackboxMaxHackDistance <= 0) Settings.BlackboxMaxHackDistance = 3.5;
        if (Settings.WaveDelaySeconds <= 0) Settings.WaveDelaySeconds = 150;
        if (Settings.EventMarkerIcon == "") Settings.EventMarkerIcon = "Vehicle";
        if (Settings.EventMarkerName == "") Settings.EventMarkerName = "DeutschZ ConvoyZ Crash";
        if (Settings.StatusBarUpdateIntervalSeconds <= 0) Settings.StatusBarUpdateIntervalSeconds = 1;
        if (Settings.StatusNotifyIntervalSeconds <= 0) Settings.StatusNotifyIntervalSeconds = 20;
        if (Settings.StatusSyncRadius <= 0) Settings.StatusSyncRadius = 650.0;
        if (Settings.InitialStartDelayMinSeconds < 0) Settings.InitialStartDelayMinSeconds = 2700;
        if (Settings.InitialStartDelayMaxSeconds < Settings.InitialStartDelayMinSeconds) Settings.InitialStartDelayMaxSeconds = Settings.InitialStartDelayMinSeconds;
        if (Settings.RestartDelayMinSeconds < 0) Settings.RestartDelayMinSeconds = 2700;
        if (Settings.RestartDelayMaxSeconds < Settings.RestartDelayMinSeconds) Settings.RestartDelayMaxSeconds = Settings.RestartDelayMinSeconds;
        if (Settings.MaxSimultaneousEvents < 1) Settings.MaxSimultaneousEvents = 1;
        if (Settings.MinOnlinePlayersToStart < 0) Settings.MinOnlinePlayersToStart = 0;
        if (Settings.NoPlayerRetryDelaySeconds < 30) Settings.NoPlayerRetryDelaySeconds = 300;
        if (Settings.MaxEventRuntimeSeconds < 0) Settings.MaxEventRuntimeSeconds = 5400;
        if (Settings.BlackboxReadyTimeoutSeconds < 0) Settings.BlackboxReadyTimeoutSeconds = 1800;
        if (Settings.MinCrashSiteDistanceMeters < 0) Settings.MinCrashSiteDistanceMeters = 500;
        if (Settings.CarrierMarkerUpdateSeconds < 10) Settings.CarrierMarkerUpdateSeconds = 25;
        if (Settings.DeliveryRadius < 2.0) Settings.DeliveryRadius = 6.0;
        if (Settings.DeliveryNpcName == "") Settings.DeliveryNpcName = "DeutschZ Kontaktmann";
        if (Settings.DeliveryNpcPosition == vector.Zero) Settings.DeliveryNpcPosition = "10620 0 5410";
        if (Settings.DeliveryHintText == "") Settings.DeliveryHintText = "Behalte das mal. Das kann spaeter noch wichtig sein.";
        if (Settings.CarryItemClassName == "") Settings.CarryItemClassName = "DZCV_ConvoyBlackBox";

        // ConvoyZ must remain standalone with Core only. Do not default to OperationDeutschZ classes here.
        if (Settings.DeliveryRewardItemClassName == "" || Settings.DeliveryRewardItemClassName.IndexOf("DZOP_") == 0) Settings.DeliveryRewardItemClassName = "DZCV_CrashSiteKeyFragment";
        if (Settings.DeliveryMapFragmentClassName == "" || Settings.DeliveryMapFragmentClassName.IndexOf("DZOP_") == 0) Settings.DeliveryMapFragmentClassName = "DZCV_ClassifiedIntel";
        if (Settings.DeliveryNoteItemClassName == "" || Settings.DeliveryNoteItemClassName.IndexOf("DZOP_") == 0) Settings.DeliveryNoteItemClassName = "DZCV_BlackboxDeliveryNote";
    }

    void RemoveOperationOnlyRewardItems()
    {
        if (!EventData || !EventData.Reward || !EventData.Reward.Items) return;

        for (int i = EventData.Reward.Items.Count() - 1; i >= 0; i--)
        {
            DeutschZConvoyZRewardItemDef existing = EventData.Reward.Items.Get(i);
            if (!existing || existing.ClassName == "" || existing.ClassName.IndexOf("DZOP_") == 0)
                EventData.Reward.Items.Remove(i);
        }
    }

    void EnsureNormalRewardItems()
    {
        if (!EventData.Reward) EventData.Reward = new DeutschZConvoyZRewardDef();
        if (!EventData.Reward.Items) EventData.Reward.Items = new array<ref DeutschZConvoyZRewardItemDef>;
        RemoveOperationOnlyRewardItems();

        AddOrRefreshRewardItem("DZCV_BlackboxCore", 1, 1.0);
        AddOrRefreshRewardItem("DZCV_EncryptedDataDrive", 1, 1.0);
        AddOrRefreshRewardItem("DZCV_ClassifiedIntel", 2, 1.0);
        AddOrRefreshRewardItem("DZCV_ConvoyBlackBox", 1, 1.0);
        AddOrRefreshRewardItem("DZCV_BlackboxDeliveryNote", 1, 1.0);
        AddOrRefreshRewardItem("DZCV_OperationLead", 1, 1.0);
        AddOrRefreshRewardItem("DZCV_CrashSiteKeyFragment", 1, 0.9);
        // OperationDeutschZ may evaluate these ConvoyZ-owned clues later; ConvoyZ must not require DZOP classes.
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

        InsertNormalAIWave("team_alpha_crash_security", 0, 3, "ZmbM_SoldierNormal_Beige", "DZCV_InfectedFallback", 42.0);
        InsertNormalAIWave("team_bravo_flank_patrol", 150, 3, "ZmbM_SoldierHeavy_Green", "DZCV_InfectedFallback", 68.0);
        InsertNormalAIWave("team_charlie_response", 300, 3, "ZmbM_PatrolNormal_Autumn", "DZCV_InfectedFallback", 96.0);
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
            float angle = (120.0 * i) + Math.RandomFloat(-18.0, 18.0);
            sp.Position[0] = sp.Position[0] + Math.Cos(angle) * radius;
            sp.Position[2] = sp.Position[2] + Math.Sin(angle) * radius;
            sp.Orientation = angle.ToString() + " 0 0";
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

        if (!EventData.CrashObjects || EventData.CrashObjects.Count() == 0)
            RebuildConvoyBlackboxChainScene();

        if (EventData.EventRadius <= 0) EventData.EventRadius = 500.0;
        if (EventData.RequiredAiKills <= 0) EventData.RequiredAiKills = Settings.RequiredAiKills;
        if (EventData.HackDurationSeconds <= 0) EventData.HackDurationSeconds = Settings.HackDurationSeconds;
        if (EventData.Blackbox.ClassName == "") EventData.Blackbox.ClassName = "Land_HACKEDCRATE";
        if (EventData.Blackbox.Position == vector.Zero) EventData.Blackbox.Position = "10124 0 5414";
        if (EventData.Reward.RewardContainerClassName == "") EventData.Reward.RewardContainerClassName = "DZCV_SealedRewardChest";
        if (EventData.Reward.RewardPosition == vector.Zero) EventData.Reward.RewardPosition = "10620 0 5410";
        EnsureNormalRewardItems();

        if (!EventData.AIWaves || EventData.AIWaves.Count() == 0)
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
                oldVehicleAsStatic.HeightOffset = veh.HeightOffset;
                if (oldVehicleAsStatic.HeightOffset < 1.0) oldVehicleAsStatic.HeightOffset = 1.0;
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

        if (Settings.InitialStartDelayMinSeconds < 0) Settings.InitialStartDelayMinSeconds = 2700;
        if (Settings.InitialStartDelayMaxSeconds < Settings.InitialStartDelayMinSeconds) Settings.InitialStartDelayMaxSeconds = Settings.InitialStartDelayMinSeconds;
        if (Settings.RestartDelayMinSeconds < 0) Settings.RestartDelayMinSeconds = 2700;
        if (Settings.RestartDelayMaxSeconds < Settings.RestartDelayMinSeconds) Settings.RestartDelayMaxSeconds = Settings.RestartDelayMinSeconds;
        if (Settings.MaxSimultaneousEvents < 1) Settings.MaxSimultaneousEvents = 1;
        if (Settings.MaxEventsPerRestart < 0) Settings.MaxEventsPerRestart = 0;
        if (Settings.MinOnlinePlayersToStart < 0) Settings.MinOnlinePlayersToStart = 0;
        if (Settings.NoPlayerRetryDelaySeconds < 30) Settings.NoPlayerRetryDelaySeconds = 30;
        if (Settings.EnableStatusNotifications < 0) Settings.EnableStatusNotifications = 0;
        if (Settings.StatusNotifyIntervalSeconds < 3) Settings.StatusNotifyIntervalSeconds = 3;
        if (Settings.MaxEventRuntimeSeconds < 0) Settings.MaxEventRuntimeSeconds = 0;
        if (Settings.BlackboxReadyTimeoutSeconds < 0) Settings.BlackboxReadyTimeoutSeconds = 0;
        if (Settings.MinCrashSiteDistanceMeters < 500) Settings.MinCrashSiteDistanceMeters = 500;
        if (Settings.CarrierMarkerUpdateSeconds < 10) Settings.CarrierMarkerUpdateSeconds = 10;
        if (Settings.DeliveryRadius < 2.0) Settings.DeliveryRadius = 2.0;
        if (Settings.DeliveryNpcPosition == vector.Zero) Settings.DeliveryNpcPosition = "10620 0 5410";
        if (Settings.DeliveryNpcName == "") Settings.DeliveryNpcName = "DeutschZ Kontaktmann";
        if (Settings.DeliveryHintText == "") Settings.DeliveryHintText = "Behalte das mal. Das kann spaeter noch wichtig sein.";
        if (Settings.CarryItemClassName == "") Settings.CarryItemClassName = "DZCV_ConvoyBlackBox";
        if (Settings.DeliveryRewardItemClassName == "") Settings.DeliveryRewardItemClassName = "DZCV_CrashSiteKeyFragment";
        if (Settings.DeliveryMapFragmentClassName == "") Settings.DeliveryMapFragmentClassName = "DZCV_ClassifiedIntel";
        if (Settings.DeliveryNoteItemClassName == "") Settings.DeliveryNoteItemClassName = "DZCV_BlackboxDeliveryNote";
    }

    void RebuildConvoyBlackboxChainScene()
    {
        if (!EventData) EventData = new DeutschZConvoyZEventDef();
        if (!EventData.CrashObjects) EventData.CrashObjects = new array<ref DeutschZConvoyZObjectDef>;
        EventData.CrashObjects.Clear();

        EventData.EventName = "DeutschZ ConvoyZ - Blackbox Operation";
        EventData.EventIdPrefix = "convoyz_blackbox_operation";
        EventData.EventCenter = "10120 0 5410";
        EventData.EventRadius = 500.0;
        EventData.RequiredAiKills = 9;
        EventData.HackDurationSeconds = 90;

        InsertCrashObject("Land_Wreck_V3S", "10120 0 5410", "35 0 0", 1, 1.0);
        InsertCrashObject("Land_Wreck_BMP2", "10110 0 5421", "120 0 0", 0, 1.0);
        InsertCrashObject("Land_Wreck_BRDM2", "10136 0 5400", "260 0 0", 0, 1.0);
        InsertCrashObject("Land_Wreck_Uaz", "10102 0 5404", "310 0 0", 0, 1.0);
        InsertCrashObject("Land_Wreck_HMMWV", "10143 0 5422", "80 0 0", 0, 1.0);
        InsertCrashObject("DZCV_ProtectedCase", "10133 0 5435", "15 0 0", 0, 0.85);

        if (!EventData.Blackbox) EventData.Blackbox = new DeutschZConvoyZBlackboxDef();
        EventData.Blackbox.Position = "10124 0 5414";
        EventData.Blackbox.Orientation = "30 0 0";
        EventData.Blackbox.ClassName = "Land_HACKEDCRATE";
        EventData.Blackbox.HeightOffset = 1.35;

        if (!EventData.Smoke) EventData.Smoke = new DeutschZConvoyZSmokeDef();
        EventData.Smoke.Position = EventData.EventCenter;

        if (!EventData.Reward) EventData.Reward = new DeutschZConvoyZRewardDef();
        EventData.Reward.RewardContainerClassName = "DZCV_SealedRewardChest";
        EventData.Reward.RewardPosition = "10620 0 5410";
        EventData.Reward.RewardOrientation = "90 0 0";
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
        RebuildConvoyBlackboxChainScene();

        DeutschZConvoyZRewardItemDef item = new DeutschZConvoyZRewardItemDef();
        item.ClassName = "PunchedCard";
        item.Quantity = 1;
        item.Chance = 1.0;
        EventData.Reward.Items.Insert(item);

        EnsureNormalRewardItems();
        RebuildNormalAIWaves();
    }
}
