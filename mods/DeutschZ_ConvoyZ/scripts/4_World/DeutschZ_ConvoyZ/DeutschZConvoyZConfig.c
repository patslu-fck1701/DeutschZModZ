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

        if (className == "Truck_01_Covered") return "Land_Wreck_UH1Y";
        if (className == "Truck_01_Chassis") return "Land_Wreck_UH1Y";
        if (className == "Truck_01_Box") return "Land_Wreck_UH1Y";
        if (className == "Truck_01_Cargo") return "Land_Wreck_UH1Y";
        if (className == "OffroadHatchback") return "Land_Wreck_Volha_Police";
        if (className == "Land_Wreck_UH1Y") return "Land_Wreck_UH1Y";
        if (className == "Land_Wreck_Volha_Police") return "Land_Wreck_Volha_Police";

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
        if (!Settings) Settings = new DeutschZConvoyZSettings();
        Settings.EnsureDeutschZEventSettings();
        Settings.ApplyDeutschZEventSettings();

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
                EventData.CrashObjects.Insert(oldVehicleAsStatic);
            }
            EventData.Vehicles.Clear();
            Print("[DeutschZ_ConvoyZ] Static-only mode: deprecated Vehicles entries converted to CrashObjects and cleared.");
        }

        foreach (DeutschZConvoyZObjectDef crashObj: EventData.CrashObjects)
        {
            if (!crashObj) continue;
            crashObj.ClassName = NormalizeCrashClassName(crashObj.ClassName);
        }

        foreach (DeutschZConvoyZAIWaveDef wave: EventData.AIWaves)
        {
            if (!wave) continue;
            if (wave.LoadoutName == "") wave.LoadoutName = "PoliceLoadout";
            if (wave.DeutschZAIProfileId == "convoy_guard") wave.DeutschZAIProfileId = "";
        }
        EventData.RequiredAiKills = Settings.RequiredAiKills;
        EventData.HackDurationSeconds = Settings.HackDurationSeconds;

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

    void CreateDefaultEvent()
    {
        EventData = new DeutschZConvoyZEventDef();
        EventData.EventCenter = "7500 0 7500";
        EventData.RequiredAiKills = 3;
        EventData.HackDurationSeconds = 30;

        // FIX26 static-only: Do not spawn drivable trucks here.
        // Convoy visuals use real vanilla static Land_Wreck_* objects only.
        DeutschZConvoyZObjectDef wreck1 = new DeutschZConvoyZObjectDef();
        wreck1.ClassName = "Land_Wreck_UH1Y";
        wreck1.Position = "7500 0 7500";
        wreck1.Orientation = "35 0 0";
        wreck1.Critical = 0;
        EventData.CrashObjects.Insert(wreck1);

        DeutschZConvoyZObjectDef wreck2 = new DeutschZConvoyZObjectDef();
        wreck2.ClassName = "Land_Wreck_Volha_Police";
        wreck2.Position = "7492 0 7507";
        wreck2.Orientation = "120 0 0";
        wreck2.Critical = 0;
        EventData.CrashObjects.Insert(wreck2);

        DeutschZConvoyZObjectDef wreck3 = new DeutschZConvoyZObjectDef();
        wreck3.ClassName = "Land_Wreck_HMMWV";
        wreck3.Position = "7511 0 7493";
        wreck3.Orientation = "260 0 0";
        wreck3.Critical = 0;
        EventData.CrashObjects.Insert(wreck3);

        EventData.Blackbox.Position = "7504 0 7502";
        EventData.Blackbox.ClassName = "Land_HACKEDCRATE";
        EventData.Smoke.Position = EventData.EventCenter;

        EventData.Reward.RewardContainerClassName = "DZCV_ProtectedCase";
        EventData.Reward.RewardPosition = "7507 0 7505";

        DeutschZConvoyZRewardItemDef item = new DeutschZConvoyZRewardItemDef();
        item.ClassName = "PunchedCard";
        item.Quantity = 1;
        item.Chance = 1.0;
        EventData.Reward.Items.Insert(item);

        for (int i = 0; i < 3; i++)
        {
            DeutschZConvoyZAIWaveDef wave = new DeutschZConvoyZAIWaveDef();
            wave.WaveId = "wave_" + (i + 1).ToString();
            wave.DelaySeconds = i * 30;
            wave.Count = 4;
            wave.AIClassName = "ZmbM_usSoldier_Officer_Desert";
            wave.DeutschZAIProfileId = "";
            wave.LoadoutName = "PoliceLoadout";

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
