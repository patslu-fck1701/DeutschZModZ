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
                if (waveIndex == 0) wave.LoadoutName = "DZCV_MilitaryLight";
                else if (waveIndex == 1) wave.LoadoutName = "DZCV_MilitaryRifleman";
                else wave.LoadoutName = "DZCV_MilitaryHeavy";
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
        EventData.RequiredAiKills = 4;
        EventData.HackDurationSeconds = 30;

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

        for (int i = 0; i < 3; i++)
        {
            DeutschZConvoyZAIWaveDef wave = new DeutschZConvoyZAIWaveDef();
            wave.WaveId = "wave_" + (i + 1).ToString();
            wave.DelaySeconds = i * 90;
            wave.Count = 4;
            if (i == 0) wave.AIClassName = DeutschZConvoyZConstants.DEFAULT_EXPANSION_AI_CLASS;
            else if (i == 1) wave.AIClassName = "eAI_SurvivorM_Denis";
            else wave.AIClassName = "eAI_SurvivorM_Boris";
            wave.DeutschZAIProfileId = "";
            if (i == 0) wave.LoadoutName = "DZCV_MilitaryLight";
            else if (i == 1) wave.LoadoutName = "DZCV_MilitaryRifleman";
            else wave.LoadoutName = "DZCV_MilitaryHeavy";

            DeutschZConvoyZSpawnPoint sp = new DeutschZConvoyZSpawnPoint();
            sp.Position = EventData.EventCenter;
            float sx = Math.RandomFloat(-35, 35);
            float sz = Math.RandomFloat(-35, 35);
            sp.Position[0] = sp.Position[0] + sx;
            sp.Position[2] = sp.Position[2] + sz;
            wave.SpawnPoints.Insert(sp);

            EventData.AIWaves.Insert(wave);
        }
    }
}
