class DeutschZBattlepassRewardData
{
    string RewardId;
    string DisplayName;
    int Level;
    int XPRequired;
    string RewardType;
    string ItemClass;
    int Quantity;
    int StackQuantity;
    int HealthPercent;
    int PremiumOnly;
    string AttachmentPreset;
    string AttachmentCSV;
    ref array<string> Attachments;
    int MoneyAmount;
    int XpAmount;
    string Command;
    string Comment;

    void DeutschZBattlepassRewardData()
    {
        RewardId = "";
        DisplayName = "Reward";
        Level = 1;
        XPRequired = 0;
        RewardType = DeutschZBattlepassRewardType.ITEM;
        ItemClass = "";
        Quantity = 1;
        StackQuantity = 0;
        HealthPercent = 100;
        PremiumOnly = 0;
        AttachmentPreset = "";
        AttachmentCSV = "";
        Attachments = new array<string>();
        MoneyAmount = 0;
        XpAmount = 0;
        Command = "";
        Comment = "";
    }
}

class DeutschZBattlepassTaskConditions
{
    float MinKillDistance;
    float MaxKillDistance;
    ref array<string> AllowedWeapons;
    ref array<string> BodyParts;
    ref array<string> ItemClassNames;
    ref array<string> ContainerClassNames;

    void DeutschZBattlepassTaskConditions()
    {
        MinKillDistance = -1.0;
        MaxKillDistance = -1.0;
        AllowedWeapons = new array<string>();
        BodyParts = new array<string>();
        ItemClassNames = new array<string>();
        ContainerClassNames = new array<string>();
    }
}

class DeutschZBattlepassTaskData
{
    string TaskId;
    string Name;
    string Description;
    string TaskType;
    int Type;
    int Cycle;
    int Target;
    int XP;
    int TargetCount;
    int XpReward;
    int Daily;
    int Weekly;
    int PremiumOnly;
    int Active;
    ref DeutschZBattlepassTaskConditions Conditions;

    void DeutschZBattlepassTaskData()
    {
        TaskId = "";
        Name = "Task";
        Description = "";
        TaskType = DeutschZBattlepassTaskType.CUSTOM;
        Type = 0;
        Cycle = 0;
        Target = 1;
        XP = 100;
        TargetCount = 1;
        XpReward = 100;
        Daily = 0;
        Weekly = 0;
        PremiumOnly = 0;
        Active = 1;
        Conditions = new DeutschZBattlepassTaskConditions();
    }
}

class DeutschZBattlepassFreeConfig
{
    int ConfigVersion;
    string SeasonId;
    string SeasonName;
    int Enabled;
    int MaxLevel;
    int XpPerLevel;
    int SyncIntervalSeconds;
    int PlaytimeXpPerMinute;
    int AutoGrantFreeRewards;
    int ShowClientNotifications;
    string MenuTitle;
    string MenuSubtitle;
    string RewardsButtonText;
    string TasksButtonText;
    string PermissionNotice;
    ref array<ref DeutschZBattlepassRewardData> FreeRewards;
    ref array<ref DeutschZBattlepassTaskData> Tasks;

    void DeutschZBattlepassFreeConfig()
    {
        ConfigVersion = 3;
        SeasonId = "season_01";
        SeasonName = "DeutschZ Season 1";
        Enabled = 1;
        MaxLevel = 29;
        XpPerLevel = 500;
        SyncIntervalSeconds = DeutschZBattlepassConstants.DEFAULT_SYNC_SECONDS;
        PlaytimeXpPerMinute = DeutschZBattlepassConstants.DEFAULT_PLAYTIME_XP_PER_MINUTE;
        AutoGrantFreeRewards = 0;
        ShowClientNotifications = 1;
        MenuTitle = "BATTLE PASS";
        MenuSubtitle = "CURRENT SEASON";
        RewardsButtonText = "REWARDS";
        TasksButtonText = "TASKS";
        PermissionNotice = "Only generated profile configs may be edited. Mod files may not be opened or changed without permission.";
        FreeRewards = new array<ref DeutschZBattlepassRewardData>();
        Tasks = new array<ref DeutschZBattlepassTaskData>();
    }

    void InsertDefaults()
    {
        ConfigVersion = 3;
        if (!FreeRewards)
        {
            FreeRewards = new array<ref DeutschZBattlepassRewardData>();
        }
        if (!Tasks)
        {
            Tasks = new array<ref DeutschZBattlepassTaskData>();
        }
        if (MenuTitle == "")
        {
            MenuTitle = "BATTLE PASS";
        }
        if (MenuSubtitle == "")
        {
            MenuSubtitle = "CURRENT SEASON";
        }
        if (RewardsButtonText == "")
        {
            RewardsButtonText = "REWARDS";
        }
        if (TasksButtonText == "")
        {
            TasksButtonText = "TASKS";
        }
        if (MaxLevel <= 0)
        {
            MaxLevel = 29;
        }
        if (XpPerLevel <= 0)
        {
            XpPerLevel = 500;
        }
        if (FreeRewards.Count() == 0)
        {
            ref DeutschZBattlepassRewardData rf_1_1 = new DeutschZBattlepassRewardData();
            rf_1_1.RewardId = "free_level_1_1_hatchet";
            rf_1_1.DisplayName = "Level 1 Free - Hatchet";
            rf_1_1.Level = 1;
            rf_1_1.XPRequired = 0;
            rf_1_1.RewardType = DeutschZBattlepassRewardType.ITEM;
            rf_1_1.ItemClass = "Hatchet";
            rf_1_1.Quantity = 1;
            rf_1_1.HealthPercent = 100;
            rf_1_1.PremiumOnly = 0;
            rf_1_1.AttachmentPreset = "";
            rf_1_1.AttachmentCSV = "";

            FreeRewards.Insert(rf_1_1);
            ref DeutschZBattlepassRewardData rf_2_1 = new DeutschZBattlepassRewardData();
            rf_2_1.RewardId = "free_level_2_1_petrollighter";
            rf_2_1.DisplayName = "Level 2 Free - PetrolLighter";
            rf_2_1.Level = 2;
            rf_2_1.XPRequired = 100;
            rf_2_1.RewardType = DeutschZBattlepassRewardType.ITEM;
            rf_2_1.ItemClass = "PetrolLighter";
            rf_2_1.Quantity = 1;
            rf_2_1.HealthPercent = 100;
            rf_2_1.PremiumOnly = 0;
            rf_2_1.AttachmentPreset = "";
            rf_2_1.AttachmentCSV = "";

            FreeRewards.Insert(rf_2_1);
            ref DeutschZBattlepassRewardData rf_3_1 = new DeutschZBattlepassRewardData();
            rf_3_1.RewardId = "free_level_3_1_nailbox";
            rf_3_1.DisplayName = "Level 3 Free - NailBox";
            rf_3_1.Level = 3;
            rf_3_1.XPRequired = 200;
            rf_3_1.RewardType = DeutschZBattlepassRewardType.ITEM;
            rf_3_1.ItemClass = "NailBox";
            rf_3_1.Quantity = 1;
            rf_3_1.HealthPercent = 100;
            rf_3_1.PremiumOnly = 0;
            rf_3_1.AttachmentPreset = "";
            rf_3_1.AttachmentCSV = "";

            FreeRewards.Insert(rf_3_1);
            ref DeutschZBattlepassRewardData rf_4_1 = new DeutschZBattlepassRewardData();
            rf_4_1.RewardId = "free_level_4_1_hammer";
            rf_4_1.DisplayName = "Level 4 Free - Hammer";
            rf_4_1.Level = 4;
            rf_4_1.XPRequired = 300;
            rf_4_1.RewardType = DeutschZBattlepassRewardType.ITEM;
            rf_4_1.ItemClass = "Hammer";
            rf_4_1.Quantity = 1;
            rf_4_1.HealthPercent = 100;
            rf_4_1.PremiumOnly = 0;
            rf_4_1.AttachmentPreset = "";
            rf_4_1.AttachmentCSV = "";

            FreeRewards.Insert(rf_4_1);
            ref DeutschZBattlepassRewardData rf_5_1 = new DeutschZBattlepassRewardData();
            rf_5_1.RewardId = "free_level_5_1_ducttape";
            rf_5_1.DisplayName = "Level 5 Free - DuctTape";
            rf_5_1.Level = 5;
            rf_5_1.XPRequired = 500;
            rf_5_1.RewardType = DeutschZBattlepassRewardType.ITEM;
            rf_5_1.ItemClass = "DuctTape";
            rf_5_1.Quantity = 1;
            rf_5_1.HealthPercent = 100;
            rf_5_1.PremiumOnly = 0;
            rf_5_1.AttachmentPreset = "";
            rf_5_1.AttachmentCSV = "";

            FreeRewards.Insert(rf_5_1);
            ref DeutschZBattlepassRewardData rf_6_1 = new DeutschZBattlepassRewardData();
            rf_6_1.RewardId = "free_level_6_1_tacticalbaconcan";
            rf_6_1.DisplayName = "Level 6 Free - TacticalBaconCan";
            rf_6_1.Level = 6;
            rf_6_1.XPRequired = 600;
            rf_6_1.RewardType = DeutschZBattlepassRewardType.ITEM;
            rf_6_1.ItemClass = "TacticalBaconCan";
            rf_6_1.Quantity = 1;
            rf_6_1.HealthPercent = 100;
            rf_6_1.PremiumOnly = 0;
            rf_6_1.AttachmentPreset = "";
            rf_6_1.AttachmentCSV = "";

            FreeRewards.Insert(rf_6_1);
            ref DeutschZBattlepassRewardData rf_7_1 = new DeutschZBattlepassRewardData();
            rf_7_1.RewardId = "free_level_7_1_fieldshovel";
            rf_7_1.DisplayName = "Level 7 Free - FieldShovel";
            rf_7_1.Level = 7;
            rf_7_1.XPRequired = 700;
            rf_7_1.RewardType = DeutschZBattlepassRewardType.ITEM;
            rf_7_1.ItemClass = "FieldShovel";
            rf_7_1.Quantity = 1;
            rf_7_1.HealthPercent = 100;
            rf_7_1.PremiumOnly = 0;
            rf_7_1.AttachmentPreset = "";
            rf_7_1.AttachmentCSV = "";

            FreeRewards.Insert(rf_7_1);
            ref DeutschZBattlepassRewardData rf_8_1 = new DeutschZBattlepassRewardData();
            rf_8_1.RewardId = "free_level_8_1_sledgehammer";
            rf_8_1.DisplayName = "Level 8 Free - SledgeHammer";
            rf_8_1.Level = 8;
            rf_8_1.XPRequired = 800;
            rf_8_1.RewardType = DeutschZBattlepassRewardType.ITEM;
            rf_8_1.ItemClass = "SledgeHammer";
            rf_8_1.Quantity = 1;
            rf_8_1.HealthPercent = 100;
            rf_8_1.PremiumOnly = 0;
            rf_8_1.AttachmentPreset = "";
            rf_8_1.AttachmentCSV = "";

            FreeRewards.Insert(rf_8_1);
            ref DeutschZBattlepassRewardData rf_9_1 = new DeutschZBattlepassRewardData();
            rf_9_1.RewardId = "free_level_9_1_woodaxe";
            rf_9_1.DisplayName = "Level 9 Free - WoodAxe";
            rf_9_1.Level = 9;
            rf_9_1.XPRequired = 900;
            rf_9_1.RewardType = DeutschZBattlepassRewardType.ITEM;
            rf_9_1.ItemClass = "WoodAxe";
            rf_9_1.Quantity = 1;
            rf_9_1.HealthPercent = 100;
            rf_9_1.PremiumOnly = 0;
            rf_9_1.AttachmentPreset = "";
            rf_9_1.AttachmentCSV = "";

            FreeRewards.Insert(rf_9_1);
            ref DeutschZBattlepassRewardData rf_10_1 = new DeutschZBattlepassRewardData();
            rf_10_1.RewardId = "free_level_10_1_canistergasoline";
            rf_10_1.DisplayName = "Level 10 Free - CanisterGasoline";
            rf_10_1.Level = 10;
            rf_10_1.XPRequired = 1000;
            rf_10_1.RewardType = DeutschZBattlepassRewardType.ITEM;
            rf_10_1.ItemClass = "CanisterGasoline";
            rf_10_1.Quantity = 1;
            rf_10_1.HealthPercent = 100;
            rf_10_1.PremiumOnly = 0;
            rf_10_1.AttachmentPreset = "";
            rf_10_1.AttachmentCSV = "";

            FreeRewards.Insert(rf_10_1);
            ref DeutschZBattlepassRewardData rf_11_1 = new DeutschZBattlepassRewardData();
            rf_11_1.RewardId = "free_level_11_1_firstaidkit";
            rf_11_1.DisplayName = "Level 11 Free - FirstAidKit";
            rf_11_1.Level = 11;
            rf_11_1.XPRequired = 1100;
            rf_11_1.RewardType = DeutschZBattlepassRewardType.ITEM;
            rf_11_1.ItemClass = "FirstAidKit";
            rf_11_1.Quantity = 1;
            rf_11_1.HealthPercent = 100;
            rf_11_1.PremiumOnly = 0;
            rf_11_1.AttachmentPreset = "";
            rf_11_1.AttachmentCSV = "";

            FreeRewards.Insert(rf_11_1);
            ref DeutschZBattlepassRewardData rf_12_1 = new DeutschZBattlepassRewardData();
            rf_12_1.RewardId = "free_level_12_1_weaponcleaningkit";
            rf_12_1.DisplayName = "Level 12 Free - WeaponCleaningKit";
            rf_12_1.Level = 12;
            rf_12_1.XPRequired = 1200;
            rf_12_1.RewardType = DeutschZBattlepassRewardType.ITEM;
            rf_12_1.ItemClass = "WeaponCleaningKit";
            rf_12_1.Quantity = 1;
            rf_12_1.HealthPercent = 100;
            rf_12_1.PremiumOnly = 0;
            rf_12_1.AttachmentPreset = "";
            rf_12_1.AttachmentCSV = "";

            FreeRewards.Insert(rf_12_1);
            ref DeutschZBattlepassRewardData rf_13_1 = new DeutschZBattlepassRewardData();
            rf_13_1.RewardId = "free_level_13_1_lbs_sleepingpacked_new_blue";
            rf_13_1.DisplayName = "Level 13 Free - LBS_SleepingPacked_New_Blue";
            rf_13_1.Level = 13;
            rf_13_1.XPRequired = 1300;
            rf_13_1.RewardType = DeutschZBattlepassRewardType.ITEM;
            rf_13_1.ItemClass = "LBS_SleepingPacked_New_Blue";
            rf_13_1.Quantity = 1;
            rf_13_1.HealthPercent = 100;
            rf_13_1.PremiumOnly = 0;
            rf_13_1.AttachmentPreset = "";
            rf_13_1.AttachmentCSV = "";

            FreeRewards.Insert(rf_13_1);
            ref DeutschZBattlepassRewardData rf_14_1 = new DeutschZBattlepassRewardData();
            rf_14_1.RewardId = "free_level_14_1_sparkplug";
            rf_14_1.DisplayName = "Level 14 Free - SparkPlug";
            rf_14_1.Level = 14;
            rf_14_1.XPRequired = 1400;
            rf_14_1.RewardType = DeutschZBattlepassRewardType.ITEM;
            rf_14_1.ItemClass = "SparkPlug";
            rf_14_1.Quantity = 1;
            rf_14_1.HealthPercent = 100;
            rf_14_1.PremiumOnly = 0;
            rf_14_1.AttachmentPreset = "";
            rf_14_1.AttachmentCSV = "";

            FreeRewards.Insert(rf_14_1);
            ref DeutschZBattlepassRewardData rf_15_1 = new DeutschZBattlepassRewardData();
            rf_15_1.RewardId = "free_level_15_1_carradiator";
            rf_15_1.DisplayName = "Level 15 Free - CarRadiator";
            rf_15_1.Level = 15;
            rf_15_1.XPRequired = 1500;
            rf_15_1.RewardType = DeutschZBattlepassRewardType.ITEM;
            rf_15_1.ItemClass = "CarRadiator";
            rf_15_1.Quantity = 1;
            rf_15_1.HealthPercent = 100;
            rf_15_1.PremiumOnly = 0;
            rf_15_1.AttachmentPreset = "";
            rf_15_1.AttachmentCSV = "";

            FreeRewards.Insert(rf_15_1);
            ref DeutschZBattlepassRewardData rf_16_1 = new DeutschZBattlepassRewardData();
            rf_16_1.RewardId = "free_level_16_1_tacticalbaconcan";
            rf_16_1.DisplayName = "Level 16 Free - TacticalBaconCan";
            rf_16_1.Level = 16;
            rf_16_1.XPRequired = 1600;
            rf_16_1.RewardType = DeutschZBattlepassRewardType.ITEM;
            rf_16_1.ItemClass = "TacticalBaconCan";
            rf_16_1.Quantity = 1;
            rf_16_1.HealthPercent = 100;
            rf_16_1.PremiumOnly = 0;
            rf_16_1.AttachmentPreset = "";
            rf_16_1.AttachmentCSV = "";

            FreeRewards.Insert(rf_16_1);
            ref DeutschZBattlepassRewardData rf_17_1 = new DeutschZBattlepassRewardData();
            rf_17_1.RewardId = "free_level_17_1_tacticalbaconcan";
            rf_17_1.DisplayName = "Level 17 Free - TacticalBaconCan";
            rf_17_1.Level = 17;
            rf_17_1.XPRequired = 1700;
            rf_17_1.RewardType = DeutschZBattlepassRewardType.ITEM;
            rf_17_1.ItemClass = "TacticalBaconCan";
            rf_17_1.Quantity = 1;
            rf_17_1.HealthPercent = 100;
            rf_17_1.PremiumOnly = 0;
            rf_17_1.AttachmentPreset = "";
            rf_17_1.AttachmentCSV = "";

            FreeRewards.Insert(rf_17_1);
            ref DeutschZBattlepassRewardData rf_18_1 = new DeutschZBattlepassRewardData();
            rf_18_1.RewardId = "free_level_18_1_pressvest_blue";
            rf_18_1.DisplayName = "Level 18 Free - PressVest_Blue";
            rf_18_1.Level = 18;
            rf_18_1.XPRequired = 1800;
            rf_18_1.RewardType = DeutschZBattlepassRewardType.ITEM;
            rf_18_1.ItemClass = "PressVest_Blue";
            rf_18_1.Quantity = 1;
            rf_18_1.HealthPercent = 100;
            rf_18_1.PremiumOnly = 0;
            rf_18_1.AttachmentPreset = "";
            rf_18_1.AttachmentCSV = "";

            FreeRewards.Insert(rf_18_1);
            ref DeutschZBattlepassRewardData rf_19_1 = new DeutschZBattlepassRewardData();
            rf_19_1.RewardId = "free_level_19_1_claymoremine";
            rf_19_1.DisplayName = "Level 19 Free - ClaymoreMine";
            rf_19_1.Level = 19;
            rf_19_1.XPRequired = 1900;
            rf_19_1.RewardType = DeutschZBattlepassRewardType.ITEM;
            rf_19_1.ItemClass = "ClaymoreMine";
            rf_19_1.Quantity = 1;
            rf_19_1.HealthPercent = 100;
            rf_19_1.PremiumOnly = 0;
            rf_19_1.AttachmentPreset = "";
            rf_19_1.AttachmentCSV = "";

            FreeRewards.Insert(rf_19_1);
            ref DeutschZBattlepassRewardData rf_20_1 = new DeutschZBattlepassRewardData();
            rf_20_1.RewardId = "free_level_20_1_ammobox";
            rf_20_1.DisplayName = "Level 20 Free - AmmoBox";
            rf_20_1.Level = 20;
            rf_20_1.XPRequired = 2000;
            rf_20_1.RewardType = DeutschZBattlepassRewardType.ITEM;
            rf_20_1.ItemClass = "AmmoBox";
            rf_20_1.Quantity = 1;
            rf_20_1.HealthPercent = 100;
            rf_20_1.PremiumOnly = 0;
            rf_20_1.AttachmentPreset = "";
            rf_20_1.AttachmentCSV = "";

            FreeRewards.Insert(rf_20_1);
            ref DeutschZBattlepassRewardData rf_21_1 = new DeutschZBattlepassRewardData();
            rf_21_1.RewardId = "free_level_21_1_nvgheadstrap";
            rf_21_1.DisplayName = "Level 21 Free - NVGHeadstrap";
            rf_21_1.Level = 21;
            rf_21_1.XPRequired = 2100;
            rf_21_1.RewardType = DeutschZBattlepassRewardType.ITEM;
            rf_21_1.ItemClass = "NVGHeadstrap";
            rf_21_1.Quantity = 1;
            rf_21_1.HealthPercent = 100;
            rf_21_1.PremiumOnly = 0;
            rf_21_1.AttachmentPreset = "";
            rf_21_1.AttachmentCSV = "";

            FreeRewards.Insert(rf_21_1);
            ref DeutschZBattlepassRewardData rf_22_1 = new DeutschZBattlepassRewardData();
            rf_22_1.RewardId = "free_level_22_1_gasmask";
            rf_22_1.DisplayName = "Level 22 Free - GasMask";
            rf_22_1.Level = 22;
            rf_22_1.XPRequired = 2200;
            rf_22_1.RewardType = DeutschZBattlepassRewardType.ITEM;
            rf_22_1.ItemClass = "GasMask";
            rf_22_1.Quantity = 1;
            rf_22_1.HealthPercent = 100;
            rf_22_1.PremiumOnly = 0;
            rf_22_1.AttachmentPreset = "";
            rf_22_1.AttachmentCSV = "";

            FreeRewards.Insert(rf_22_1);
            ref DeutschZBattlepassRewardData rf_23_1 = new DeutschZBattlepassRewardData();
            rf_23_1.RewardId = "free_level_23_1_ballistichelmet_woodland";
            rf_23_1.DisplayName = "Level 23 Free - BallisticHelmet_Woodland";
            rf_23_1.Level = 23;
            rf_23_1.XPRequired = 2300;
            rf_23_1.RewardType = DeutschZBattlepassRewardType.ITEM;
            rf_23_1.ItemClass = "BallisticHelmet_Woodland";
            rf_23_1.Quantity = 1;
            rf_23_1.HealthPercent = 100;
            rf_23_1.PremiumOnly = 0;
            rf_23_1.AttachmentPreset = "";
            rf_23_1.AttachmentCSV = "";

            FreeRewards.Insert(rf_23_1);
            ref DeutschZBattlepassRewardData rf_24_1 = new DeutschZBattlepassRewardData();
            rf_24_1.RewardId = "free_level_24_1_ghillieatt_mossy";
            rf_24_1.DisplayName = "Level 24 Free - GhillieAtt_Mossy";
            rf_24_1.Level = 24;
            rf_24_1.XPRequired = 2400;
            rf_24_1.RewardType = DeutschZBattlepassRewardType.ITEM;
            rf_24_1.ItemClass = "GhillieAtt_Mossy";
            rf_24_1.Quantity = 1;
            rf_24_1.HealthPercent = 100;
            rf_24_1.PremiumOnly = 0;
            rf_24_1.AttachmentPreset = "";
            rf_24_1.AttachmentCSV = "";

            FreeRewards.Insert(rf_24_1);
            ref DeutschZBattlepassRewardData rf_25_1 = new DeutschZBattlepassRewardData();
            rf_25_1.RewardId = "free_level_25_1_tacticalbaconcan";
            rf_25_1.DisplayName = "Level 25 Free - TacticalBaconCan";
            rf_25_1.Level = 25;
            rf_25_1.XPRequired = 2500;
            rf_25_1.RewardType = DeutschZBattlepassRewardType.ITEM;
            rf_25_1.ItemClass = "TacticalBaconCan";
            rf_25_1.Quantity = 1;
            rf_25_1.HealthPercent = 100;
            rf_25_1.PremiumOnly = 0;
            rf_25_1.AttachmentPreset = "";
            rf_25_1.AttachmentCSV = "";

            FreeRewards.Insert(rf_25_1);
            ref DeutschZBattlepassRewardData rf_26_1 = new DeutschZBattlepassRewardData();
            rf_26_1.RewardId = "free_level_26_1_tacticalbaconcan";
            rf_26_1.DisplayName = "Level 26 Free - TacticalBaconCan";
            rf_26_1.Level = 26;
            rf_26_1.XPRequired = 2600;
            rf_26_1.RewardType = DeutschZBattlepassRewardType.ITEM;
            rf_26_1.ItemClass = "TacticalBaconCan";
            rf_26_1.Quantity = 1;
            rf_26_1.HealthPercent = 100;
            rf_26_1.PremiumOnly = 0;
            rf_26_1.AttachmentPreset = "";
            rf_26_1.AttachmentCSV = "";

            FreeRewards.Insert(rf_26_1);
            ref DeutschZBattlepassRewardData rf_27_1 = new DeutschZBattlepassRewardData();
            rf_27_1.RewardId = "free_level_27_1_punchedcard";
            rf_27_1.DisplayName = "Level 27 Free - PunchedCard";
            rf_27_1.Level = 27;
            rf_27_1.XPRequired = 2700;
            rf_27_1.RewardType = DeutschZBattlepassRewardType.ITEM;
            rf_27_1.ItemClass = "PunchedCard";
            rf_27_1.Quantity = 1;
            rf_27_1.HealthPercent = 100;
            rf_27_1.PremiumOnly = 0;
            rf_27_1.AttachmentPreset = "";
            rf_27_1.AttachmentCSV = "";

            FreeRewards.Insert(rf_27_1);
            ref DeutschZBattlepassRewardData rf_28_1 = new DeutschZBattlepassRewardData();
            rf_28_1.RewardId = "free_level_28_1_hdsn_c4sticks";
            rf_28_1.DisplayName = "Level 28 Free - HDSN_C4Sticks";
            rf_28_1.Level = 28;
            rf_28_1.XPRequired = 2800;
            rf_28_1.RewardType = DeutschZBattlepassRewardType.ITEM;
            rf_28_1.ItemClass = "HDSN_C4Sticks";
            rf_28_1.Quantity = 1;
            rf_28_1.HealthPercent = 100;
            rf_28_1.PremiumOnly = 0;
            rf_28_1.AttachmentPreset = "";
            rf_28_1.AttachmentCSV = "";

            FreeRewards.Insert(rf_28_1);
            ref DeutschZBattlepassRewardData rf_29_1 = new DeutschZBattlepassRewardData();
            rf_29_1.RewardId = "free_level_29_1_smallprotectorcase";
            rf_29_1.DisplayName = "Level 29 Free - SmallProtectorCase";
            rf_29_1.Level = 29;
            rf_29_1.XPRequired = 2900;
            rf_29_1.RewardType = DeutschZBattlepassRewardType.ITEM;
            rf_29_1.ItemClass = "SmallProtectorCase";
            rf_29_1.Quantity = 1;
            rf_29_1.HealthPercent = 100;
            rf_29_1.PremiumOnly = 0;
            rf_29_1.AttachmentPreset = "";
            rf_29_1.AttachmentCSV = "";

            FreeRewards.Insert(rf_29_1);
        }
        if (Tasks.Count() == 0)
        {
            ref DeutschZBattlepassTaskData task_1 = new DeutschZBattlepassTaskData();
            task_1.TaskId = "lumberjack";
            task_1.Name = "Lumberjack";
            task_1.Description = "Chop down trees to gather wood and earn XP.";
            task_1.TaskType = DeutschZBattlepassTaskType.CUSTOM;
            task_1.Type = 12;
            task_1.Cycle = 1;
            task_1.Target = 5;
            task_1.XP = 75;
            task_1.TargetCount = 5;
            task_1.XpReward = 75;
            task_1.Daily = 1;
            task_1.Weekly = 0;
            task_1.PremiumOnly = 0;
            task_1.Conditions.MinKillDistance = -1.0;
            task_1.Conditions.MaxKillDistance = -1.0;


            task_1.Conditions.ItemClassNames.Insert("ActionMineTree");

            Tasks.Insert(task_1);
            ref DeutschZBattlepassTaskData task_2 = new DeutschZBattlepassTaskData();
            task_2.TaskId = "lumberjack_weekly";
            task_2.Name = "Lumberjack";
            task_2.Description = "Chop down trees to gather wood and earn XP.";
            task_2.TaskType = DeutschZBattlepassTaskType.CUSTOM;
            task_2.Type = 12;
            task_2.Cycle = 2;
            task_2.Target = 75;
            task_2.XP = 650;
            task_2.TargetCount = 75;
            task_2.XpReward = 650;
            task_2.Daily = 0;
            task_2.Weekly = 1;
            task_2.PremiumOnly = 0;
            task_2.Conditions.MinKillDistance = -1.0;
            task_2.Conditions.MaxKillDistance = -1.0;


            task_2.Conditions.ItemClassNames.Insert("ActionMineTree");

            Tasks.Insert(task_2);
            ref DeutschZBattlepassTaskData task_3 = new DeutschZBattlepassTaskData();
            task_3.TaskId = "miner";
            task_3.Name = "Miner";
            task_3.Description = "Mine rocks to collect valuable resources and earn XP.";
            task_3.TaskType = DeutschZBattlepassTaskType.CUSTOM;
            task_3.Type = 12;
            task_3.Cycle = 1;
            task_3.Target = 5;
            task_3.XP = 75;
            task_3.TargetCount = 5;
            task_3.XpReward = 75;
            task_3.Daily = 1;
            task_3.Weekly = 0;
            task_3.PremiumOnly = 0;
            task_3.Conditions.MinKillDistance = -1.0;
            task_3.Conditions.MaxKillDistance = -1.0;


            task_3.Conditions.ItemClassNames.Insert("ActionMineRock");

            Tasks.Insert(task_3);
            ref DeutschZBattlepassTaskData task_4 = new DeutschZBattlepassTaskData();
            task_4.TaskId = "gardener_dig";
            task_4.Name = "Gardener: Dig";
            task_4.Description = "Dig garden plots to prepare soil and earn XP.";
            task_4.TaskType = DeutschZBattlepassTaskType.CUSTOM;
            task_4.Type = 12;
            task_4.Cycle = 1;
            task_4.Target = 3;
            task_4.XP = 50;
            task_4.TargetCount = 3;
            task_4.XpReward = 50;
            task_4.Daily = 1;
            task_4.Weekly = 0;
            task_4.PremiumOnly = 0;
            task_4.Conditions.MinKillDistance = -1.0;
            task_4.Conditions.MaxKillDistance = -1.0;


            task_4.Conditions.ItemClassNames.Insert("ActionDigGardenPlot");

            Tasks.Insert(task_4);
            ref DeutschZBattlepassTaskData task_5 = new DeutschZBattlepassTaskData();
            task_5.TaskId = "gardener_water";
            task_5.Name = "Gardener: Water";
            task_5.Description = "Water your garden plots to help crops grow and earn XP.";
            task_5.TaskType = DeutschZBattlepassTaskType.CUSTOM;
            task_5.Type = 12;
            task_5.Cycle = 1;
            task_5.Target = 3;
            task_5.XP = 50;
            task_5.TargetCount = 3;
            task_5.XpReward = 50;
            task_5.Daily = 1;
            task_5.Weekly = 0;
            task_5.PremiumOnly = 0;
            task_5.Conditions.MinKillDistance = -1.0;
            task_5.Conditions.MaxKillDistance = -1.0;


            task_5.Conditions.ItemClassNames.Insert("ActionWaterGardenSlot");

            Tasks.Insert(task_5);
            ref DeutschZBattlepassTaskData task_6 = new DeutschZBattlepassTaskData();
            task_6.TaskId = "fisherman";
            task_6.Name = "Fisherman";
            task_6.Description = "Catch fish to gather food and earn XP.";
            task_6.TaskType = DeutschZBattlepassTaskType.CUSTOM;
            task_6.Type = 12;
            task_6.Cycle = 1;
            task_6.Target = 3;
            task_6.XP = 75;
            task_6.TargetCount = 3;
            task_6.XpReward = 75;
            task_6.Daily = 1;
            task_6.Weekly = 0;
            task_6.PremiumOnly = 0;
            task_6.Conditions.MinKillDistance = -1.0;
            task_6.Conditions.MaxKillDistance = -1.0;


            task_6.Conditions.ItemClassNames.Insert("ActionFishingNew");

            Tasks.Insert(task_6);
            ref DeutschZBattlepassTaskData task_7 = new DeutschZBattlepassTaskData();
            task_7.TaskId = "healer_bandage";
            task_7.Name = "Healer: Bandage";
            task_7.Description = "Apply bandages to yourself or others and earn XP.";
            task_7.TaskType = DeutschZBattlepassTaskType.CUSTOM;
            task_7.Type = 12;
            task_7.Cycle = 1;
            task_7.Target = 3;
            task_7.XP = 45;
            task_7.TargetCount = 3;
            task_7.XpReward = 45;
            task_7.Daily = 1;
            task_7.Weekly = 0;
            task_7.PremiumOnly = 0;
            task_7.Conditions.MinKillDistance = -1.0;
            task_7.Conditions.MaxKillDistance = -1.0;


            task_7.Conditions.ItemClassNames.Insert("ActionBandageSelf");
            task_7.Conditions.ItemClassNames.Insert("ActionBandageTarget");

            Tasks.Insert(task_7);
            ref DeutschZBattlepassTaskData task_8 = new DeutschZBattlepassTaskData();
            task_8.TaskId = "skinner";
            task_8.Name = "Skinner";
            task_8.Description = "Skin animals to collect resources and earn XP.";
            task_8.TaskType = DeutschZBattlepassTaskType.CUSTOM;
            task_8.Type = 12;
            task_8.Cycle = 1;
            task_8.Target = 3;
            task_8.XP = 70;
            task_8.TargetCount = 3;
            task_8.XpReward = 70;
            task_8.Daily = 1;
            task_8.Weekly = 0;
            task_8.PremiumOnly = 0;
            task_8.Conditions.MinKillDistance = -1.0;
            task_8.Conditions.MaxKillDistance = -1.0;


            task_8.Conditions.ItemClassNames.Insert("ActionSkinning");

            Tasks.Insert(task_8);
            ref DeutschZBattlepassTaskData task_9 = new DeutschZBattlepassTaskData();
            task_9.TaskId = "rescuer_cpr";
            task_9.Name = "Rescuer: CPR";
            task_9.Description = "Perform CPR to revive unconscious players and earn XP.";
            task_9.TaskType = DeutschZBattlepassTaskType.CUSTOM;
            task_9.Type = 12;
            task_9.Cycle = 1;
            task_9.Target = 1;
            task_9.XP = 100;
            task_9.TargetCount = 1;
            task_9.XpReward = 100;
            task_9.Daily = 1;
            task_9.Weekly = 0;
            task_9.PremiumOnly = 0;
            task_9.Conditions.MinKillDistance = -1.0;
            task_9.Conditions.MaxKillDistance = -1.0;


            task_9.Conditions.ItemClassNames.Insert("ActionCPR");

            Tasks.Insert(task_9);
            ref DeutschZBattlepassTaskData task_10 = new DeutschZBattlepassTaskData();
            task_10.TaskId = "dedicated_survivor";
            task_10.Name = "Dedicated Survivor";
            task_10.Description = "Stay connected and earn points for every hour you remain connected.";
            task_10.TaskType = DeutschZBattlepassTaskType.PLAYTIME_MINUTES;
            task_10.Type = 4;
            task_10.Cycle = 1;
            task_10.Target = 3600;
            task_10.XP = 100;
            task_10.TargetCount = 3600;
            task_10.XpReward = 100;
            task_10.Daily = 1;
            task_10.Weekly = 0;
            task_10.PremiumOnly = 0;
            task_10.Conditions.MinKillDistance = -1.0;
            task_10.Conditions.MaxKillDistance = -1.0;




            Tasks.Insert(task_10);
            ref DeutschZBattlepassTaskData task_11 = new DeutschZBattlepassTaskData();
            task_11.TaskId = "kill_players";
            task_11.Name = "Kill Players";
            task_11.Description = "Found in high-traffic areas like military bases, airfields, and big cities.";
            task_11.TaskType = DeutschZBattlepassTaskType.KILL_PLAYER;
            task_11.Type = 2;
            task_11.Cycle = 1;
            task_11.Target = 1;
            task_11.XP = 175;
            task_11.TargetCount = 1;
            task_11.XpReward = 175;
            task_11.Daily = 1;
            task_11.Weekly = 0;
            task_11.PremiumOnly = 0;
            task_11.Conditions.MinKillDistance = -1.0;
            task_11.Conditions.MaxKillDistance = -1.0;


            task_11.Conditions.ItemClassNames.Insert("SurvivorM_Mirek");
            task_11.Conditions.ItemClassNames.Insert("SurvivorM_Boris");
            task_11.Conditions.ItemClassNames.Insert("SurvivorM_Cyril");
            task_11.Conditions.ItemClassNames.Insert("SurvivorM_Denis");
            task_11.Conditions.ItemClassNames.Insert("SurvivorM_Elias");
            task_11.Conditions.ItemClassNames.Insert("SurvivorM_Francis");
            task_11.Conditions.ItemClassNames.Insert("SurvivorM_Guo");
            task_11.Conditions.ItemClassNames.Insert("SurvivorM_Hassan");
            task_11.Conditions.ItemClassNames.Insert("SurvivorM_Indar");
            task_11.Conditions.ItemClassNames.Insert("SurvivorM_Jose");
            task_11.Conditions.ItemClassNames.Insert("SurvivorM_Kaito");
            task_11.Conditions.ItemClassNames.Insert("SurvivorM_Lewis");
            task_11.Conditions.ItemClassNames.Insert("SurvivorM_Manua");
            task_11.Conditions.ItemClassNames.Insert("SurvivorM_Niki");
            task_11.Conditions.ItemClassNames.Insert("SurvivorM_Oliver");
            task_11.Conditions.ItemClassNames.Insert("SurvivorM_Peter");
            task_11.Conditions.ItemClassNames.Insert("SurvivorM_Quinn");
            task_11.Conditions.ItemClassNames.Insert("SurvivorM_Rolf");
            task_11.Conditions.ItemClassNames.Insert("SurvivorM_Seth");
            task_11.Conditions.ItemClassNames.Insert("SurvivorM_Taiki");
            task_11.Conditions.ItemClassNames.Insert("SurvivorF_Eva");
            task_11.Conditions.ItemClassNames.Insert("SurvivorF_Frida");
            task_11.Conditions.ItemClassNames.Insert("SurvivorF_Gabi");
            task_11.Conditions.ItemClassNames.Insert("SurvivorF_Helga");
            task_11.Conditions.ItemClassNames.Insert("SurvivorF_Irena");
            task_11.Conditions.ItemClassNames.Insert("SurvivorF_Judy");
            task_11.Conditions.ItemClassNames.Insert("SurvivorF_Keiko");
            task_11.Conditions.ItemClassNames.Insert("SurvivorF_Linda");
            task_11.Conditions.ItemClassNames.Insert("SurvivorF_Maria");
            task_11.Conditions.ItemClassNames.Insert("SurvivorF_Naomi");
            task_11.Conditions.ItemClassNames.Insert("SurvivorF_Baty");

            Tasks.Insert(task_11);
            ref DeutschZBattlepassTaskData task_12 = new DeutschZBattlepassTaskData();
            task_12.TaskId = "kill_ai";
            task_12.Name = "Kill AI";
            task_12.Description = "Found in high-traffic areas like military bases, airfields, and big cities.";
            task_12.TaskType = DeutschZBattlepassTaskType.CUSTOM;
            task_12.Type = 2;
            task_12.Cycle = 1;
            task_12.Target = 3;
            task_12.XP = 125;
            task_12.TargetCount = 3;
            task_12.XpReward = 125;
            task_12.Daily = 1;
            task_12.Weekly = 0;
            task_12.PremiumOnly = 0;
            task_12.Conditions.MinKillDistance = -1.0;
            task_12.Conditions.MaxKillDistance = -1.0;


            task_12.Conditions.ItemClassNames.Insert("eAI_SurvivorF_Eva");
            task_12.Conditions.ItemClassNames.Insert("eAI_SurvivorF_Frida");
            task_12.Conditions.ItemClassNames.Insert("eAI_SurvivorF_Gabi");
            task_12.Conditions.ItemClassNames.Insert("eAI_SurvivorF_Helga");
            task_12.Conditions.ItemClassNames.Insert("eAI_SurvivorF_Irena");
            task_12.Conditions.ItemClassNames.Insert("eAI_SurvivorF_Judy");
            task_12.Conditions.ItemClassNames.Insert("eAI_SurvivorF_Keiko");
            task_12.Conditions.ItemClassNames.Insert("eAI_SurvivorF_Linda");
            task_12.Conditions.ItemClassNames.Insert("eAI_SurvivorF_Maria");
            task_12.Conditions.ItemClassNames.Insert("eAI_SurvivorF_Naomi");
            task_12.Conditions.ItemClassNames.Insert("eAI_SurvivorF_Baty");
            task_12.Conditions.ItemClassNames.Insert("eAI_SurvivorM_Boris");
            task_12.Conditions.ItemClassNames.Insert("eAI_SurvivorM_Cyril");
            task_12.Conditions.ItemClassNames.Insert("eAI_SurvivorM_Denis");
            task_12.Conditions.ItemClassNames.Insert("eAI_SurvivorM_Elias");
            task_12.Conditions.ItemClassNames.Insert("eAI_SurvivorM_Francis");
            task_12.Conditions.ItemClassNames.Insert("eAI_SurvivorM_Guo");
            task_12.Conditions.ItemClassNames.Insert("eAI_SurvivorM_Hassan");
            task_12.Conditions.ItemClassNames.Insert("eAI_SurvivorM_Indar");
            task_12.Conditions.ItemClassNames.Insert("eAI_SurvivorM_Jose");
            task_12.Conditions.ItemClassNames.Insert("eAI_SurvivorM_Kaito");
            task_12.Conditions.ItemClassNames.Insert("eAI_SurvivorM_Lewis");
            task_12.Conditions.ItemClassNames.Insert("eAI_SurvivorM_Manua");
            task_12.Conditions.ItemClassNames.Insert("eAI_SurvivorM_Mirek");
            task_12.Conditions.ItemClassNames.Insert("eAI_SurvivorM_Niki");
            task_12.Conditions.ItemClassNames.Insert("eAI_SurvivorM_Oliver");
            task_12.Conditions.ItemClassNames.Insert("eAI_SurvivorM_Peter");
            task_12.Conditions.ItemClassNames.Insert("eAI_SurvivorM_Quinn");
            task_12.Conditions.ItemClassNames.Insert("eAI_SurvivorM_Rolf");
            task_12.Conditions.ItemClassNames.Insert("eAI_SurvivorM_Seth");
            task_12.Conditions.ItemClassNames.Insert("eAI_SurvivorM_Taiki");

            Tasks.Insert(task_12);
            ref DeutschZBattlepassTaskData task_13 = new DeutschZBattlepassTaskData();
            task_13.TaskId = "kill_foxes";
            task_13.Name = "Kill Foxes";
            task_13.Description = "Roam forested areas and near tree lines, especially around rural regions.";
            task_13.TaskType = DeutschZBattlepassTaskType.CUSTOM;
            task_13.Type = 1;
            task_13.Cycle = 1;
            task_13.Target = 2;
            task_13.XP = 55;
            task_13.TargetCount = 2;
            task_13.XpReward = 55;
            task_13.Daily = 1;
            task_13.Weekly = 0;
            task_13.PremiumOnly = 0;
            task_13.Conditions.MinKillDistance = -1.0;
            task_13.Conditions.MaxKillDistance = -1.0;


            task_13.Conditions.ItemClassNames.Insert("Animal_VulpesVulpes");

            Tasks.Insert(task_13);
            ref DeutschZBattlepassTaskData task_14 = new DeutschZBattlepassTaskData();
            task_14.TaskId = "kill_hares";
            task_14.Name = "Kill Hares";
            task_14.Description = "Common in open fields, farmlands, and grassy meadows.";
            task_14.TaskType = DeutschZBattlepassTaskType.CUSTOM;
            task_14.Type = 1;
            task_14.Cycle = 1;
            task_14.Target = 3;
            task_14.XP = 35;
            task_14.TargetCount = 3;
            task_14.XpReward = 35;
            task_14.Daily = 1;
            task_14.Weekly = 0;
            task_14.PremiumOnly = 0;
            task_14.Conditions.MinKillDistance = -1.0;
            task_14.Conditions.MaxKillDistance = -1.0;


            task_14.Conditions.ItemClassNames.Insert("Animal_LepusEuropaeus");

            Tasks.Insert(task_14);
            ref DeutschZBattlepassTaskData task_15 = new DeutschZBattlepassTaskData();
            task_15.TaskId = "kill_hens";
            task_15.Name = "Kill Hens";
            task_15.Description = "Usually found in villages, farmyards, and around houses in rural towns.";
            task_15.TaskType = DeutschZBattlepassTaskType.CUSTOM;
            task_15.Type = 1;
            task_15.Cycle = 1;
            task_15.Target = 5;
            task_15.XP = 30;
            task_15.TargetCount = 5;
            task_15.XpReward = 30;
            task_15.Daily = 1;
            task_15.Weekly = 0;
            task_15.PremiumOnly = 0;
            task_15.Conditions.MinKillDistance = -1.0;
            task_15.Conditions.MaxKillDistance = -1.0;


            task_15.Conditions.ItemClassNames.Insert("Animal_GallusGallusDomesticus");
            task_15.Conditions.ItemClassNames.Insert("Animal_GallusGallusDomesticusF_Brown");
            task_15.Conditions.ItemClassNames.Insert("Animal_GallusGallusDomesticusF_Spotted");
            task_15.Conditions.ItemClassNames.Insert("Animal_GallusGallusDomesticusF_White");

            Tasks.Insert(task_15);
            ref DeutschZBattlepassTaskData task_16 = new DeutschZBattlepassTaskData();
            task_16.TaskId = "kill_bears";
            task_16.Name = "Kill Bears";
            task_16.Description = "Spawn deep in forests and mountainous areas - often in the far north or wilderness zones.";
            task_16.TaskType = DeutschZBattlepassTaskType.CUSTOM;
            task_16.Type = 1;
            task_16.Cycle = 1;
            task_16.Target = 1;
            task_16.XP = 175;
            task_16.TargetCount = 1;
            task_16.XpReward = 175;
            task_16.Daily = 1;
            task_16.Weekly = 0;
            task_16.PremiumOnly = 0;
            task_16.Conditions.MinKillDistance = -1.0;
            task_16.Conditions.MaxKillDistance = -1.0;


            task_16.Conditions.ItemClassNames.Insert("Animal_UrsusArctos");

            Tasks.Insert(task_16);
            ref DeutschZBattlepassTaskData task_17 = new DeutschZBattlepassTaskData();
            task_17.TaskId = "kill_cows";
            task_17.Name = "Kill Cows";
            task_17.Description = "Grazing near barns, open pastures, and village outskirts.";
            task_17.TaskType = DeutschZBattlepassTaskType.CUSTOM;
            task_17.Type = 1;
            task_17.Cycle = 1;
            task_17.Target = 2;
            task_17.XP = 45;
            task_17.TargetCount = 2;
            task_17.XpReward = 45;
            task_17.Daily = 1;
            task_17.Weekly = 0;
            task_17.PremiumOnly = 0;
            task_17.Conditions.MinKillDistance = -1.0;
            task_17.Conditions.MaxKillDistance = -1.0;


            task_17.Conditions.ItemClassNames.Insert("Animal_BosTaurusF_Brown");
            task_17.Conditions.ItemClassNames.Insert("Animal_BosTaurusF_Spotted");
            task_17.Conditions.ItemClassNames.Insert("Animal_BosTaurusF_White");
            task_17.Conditions.ItemClassNames.Insert("Animal_BosTaurus_Brown");
            task_17.Conditions.ItemClassNames.Insert("Animal_BosTaurus_Spotted");
            task_17.Conditions.ItemClassNames.Insert("Animal_BosTaurus_White");

            Tasks.Insert(task_17);
            ref DeutschZBattlepassTaskData task_18 = new DeutschZBattlepassTaskData();
            task_18.TaskId = "kill_deers";
            task_18.Name = "Kill Deers";
            task_18.Description = "Found in dense forests and around clearings, especially early morning or dusk.";
            task_18.TaskType = DeutschZBattlepassTaskType.CUSTOM;
            task_18.Type = 1;
            task_18.Cycle = 1;
            task_18.Target = 2;
            task_18.XP = 65;
            task_18.TargetCount = 2;
            task_18.XpReward = 65;
            task_18.Daily = 1;
            task_18.Weekly = 0;
            task_18.PremiumOnly = 0;
            task_18.Conditions.MinKillDistance = -1.0;
            task_18.Conditions.MaxKillDistance = -1.0;


            task_18.Conditions.ItemClassNames.Insert("Animal_CervusElaphus");
            task_18.Conditions.ItemClassNames.Insert("Animal_CervusElaphusF");

            Tasks.Insert(task_18);
            ref DeutschZBattlepassTaskData task_19 = new DeutschZBattlepassTaskData();
            task_19.TaskId = "kill_goats";
            task_19.Name = "Kill Goats";
            task_19.Description = "Often spawn near rural homes, farms, and small village areas.";
            task_19.TaskType = DeutschZBattlepassTaskType.CUSTOM;
            task_19.Type = 1;
            task_19.Cycle = 1;
            task_19.Target = 2;
            task_19.XP = 45;
            task_19.TargetCount = 2;
            task_19.XpReward = 45;
            task_19.Daily = 1;
            task_19.Weekly = 0;
            task_19.PremiumOnly = 0;
            task_19.Conditions.MinKillDistance = -1.0;
            task_19.Conditions.MaxKillDistance = -1.0;


            task_19.Conditions.ItemClassNames.Insert("Animal_CapraHircusF");
            task_19.Conditions.ItemClassNames.Insert("Animal_CapraHircus_Black");
            task_19.Conditions.ItemClassNames.Insert("Animal_CapraHircus_Brown");
            task_19.Conditions.ItemClassNames.Insert("Animal_CapraHircus_White");

            Tasks.Insert(task_19);
            ref DeutschZBattlepassTaskData task_20 = new DeutschZBattlepassTaskData();
            task_20.TaskId = "kill_pigs";
            task_20.Name = "Kill Pigs";
            task_20.Description = "Common in farmlands, forest edges, and near agricultural buildings.";
            task_20.TaskType = DeutschZBattlepassTaskType.CUSTOM;
            task_20.Type = 1;
            task_20.Cycle = 1;
            task_20.Target = 2;
            task_20.XP = 45;
            task_20.TargetCount = 2;
            task_20.XpReward = 45;
            task_20.Daily = 1;
            task_20.Weekly = 0;
            task_20.PremiumOnly = 0;
            task_20.Conditions.MinKillDistance = -1.0;
            task_20.Conditions.MaxKillDistance = -1.0;


            task_20.Conditions.ItemClassNames.Insert("Animal_SusDomesticus");

            Tasks.Insert(task_20);
            ref DeutschZBattlepassTaskData task_21 = new DeutschZBattlepassTaskData();
            task_21.TaskId = "kill_roe_deers";
            task_21.Name = "Kill Roe Deers";
            task_21.Description = "Wander lightly wooded areas and grassy slopes.";
            task_21.TaskType = DeutschZBattlepassTaskType.CUSTOM;
            task_21.Type = 1;
            task_21.Cycle = 1;
            task_21.Target = 2;
            task_21.XP = 65;
            task_21.TargetCount = 2;
            task_21.XpReward = 65;
            task_21.Daily = 1;
            task_21.Weekly = 0;
            task_21.PremiumOnly = 0;
            task_21.Conditions.MinKillDistance = -1.0;
            task_21.Conditions.MaxKillDistance = -1.0;


            task_21.Conditions.ItemClassNames.Insert("Animal_CapreolusCapreolus");
            task_21.Conditions.ItemClassNames.Insert("Animal_CapreolusCapreolusF");

            Tasks.Insert(task_21);
            ref DeutschZBattlepassTaskData task_22 = new DeutschZBattlepassTaskData();
            task_22.TaskId = "kill_sheeps";
            task_22.Name = "Kill Sheeps";
            task_22.Description = "Typically appear around farmhouses and fenced-in rural yards.";
            task_22.TaskType = DeutschZBattlepassTaskType.CUSTOM;
            task_22.Type = 1;
            task_22.Cycle = 1;
            task_22.Target = 2;
            task_22.XP = 45;
            task_22.TargetCount = 2;
            task_22.XpReward = 45;
            task_22.Daily = 1;
            task_22.Weekly = 0;
            task_22.PremiumOnly = 0;
            task_22.Conditions.MinKillDistance = -1.0;
            task_22.Conditions.MaxKillDistance = -1.0;


            task_22.Conditions.ItemClassNames.Insert("Animal_OvisAries");
            task_22.Conditions.ItemClassNames.Insert("Animal_OvisAriesF");

            Tasks.Insert(task_22);
            ref DeutschZBattlepassTaskData task_23 = new DeutschZBattlepassTaskData();
            task_23.TaskId = "kill_wild_boars";
            task_23.Name = "Kill Wild Boars";
            task_23.Description = "Found in forests, forest clearings, and hilly wilderness regions.";
            task_23.TaskType = DeutschZBattlepassTaskType.CUSTOM;
            task_23.Type = 1;
            task_23.Cycle = 1;
            task_23.Target = 2;
            task_23.XP = 60;
            task_23.TargetCount = 2;
            task_23.XpReward = 60;
            task_23.Daily = 1;
            task_23.Weekly = 0;
            task_23.PremiumOnly = 0;
            task_23.Conditions.MinKillDistance = -1.0;
            task_23.Conditions.MaxKillDistance = -1.0;


            task_23.Conditions.ItemClassNames.Insert("Animal_SusScrofa");

            Tasks.Insert(task_23);
            ref DeutschZBattlepassTaskData task_24 = new DeutschZBattlepassTaskData();
            task_24.TaskId = "kill_wolves";
            task_24.Name = "Kill Wolves";
            task_24.Description = "Roam in packs within deep forests, especially in remote and northern parts of the map.";
            task_24.TaskType = DeutschZBattlepassTaskType.CUSTOM;
            task_24.Type = 1;
            task_24.Cycle = 1;
            task_24.Target = 3;
            task_24.XP = 100;
            task_24.TargetCount = 3;
            task_24.XpReward = 100;
            task_24.Daily = 1;
            task_24.Weekly = 0;
            task_24.PremiumOnly = 0;
            task_24.Conditions.MinKillDistance = -1.0;
            task_24.Conditions.MaxKillDistance = -1.0;


            task_24.Conditions.ItemClassNames.Insert("Animal_CanisLupus_Grey");
            task_24.Conditions.ItemClassNames.Insert("Animal_CanisLupus_White");

            Tasks.Insert(task_24);
            ref DeutschZBattlepassTaskData task_25 = new DeutschZBattlepassTaskData();
            task_25.TaskId = "kill_zombies";
            task_25.Name = "Kill Zombies";
            task_25.Description = "Present in nearly every town, village, and lootable building.";
            task_25.TaskType = DeutschZBattlepassTaskType.KILL_INFECTED;
            task_25.Type = 0;
            task_25.Cycle = 1;
            task_25.Target = 25;
            task_25.XP = 90;
            task_25.TargetCount = 25;
            task_25.XpReward = 90;
            task_25.Daily = 1;
            task_25.Weekly = 0;
            task_25.PremiumOnly = 0;
            task_25.Conditions.MinKillDistance = -1.0;
            task_25.Conditions.MaxKillDistance = -1.0;


            task_25.Conditions.ItemClassNames.Insert("ZmbM_CitizenASkinny_Blue");
            task_25.Conditions.ItemClassNames.Insert("ZmbM_CitizenASkinny_Grey");
            task_25.Conditions.ItemClassNames.Insert("ZmbM_CitizenASkinny_Red");
            task_25.Conditions.ItemClassNames.Insert("ZmbM_CitizenBFat_Blue");
            task_25.Conditions.ItemClassNames.Insert("ZmbM_CitizenBFat_Green");
            task_25.Conditions.ItemClassNames.Insert("ZmbM_CitizenBFat_Red");
            task_25.Conditions.ItemClassNames.Insert("ZmbM_ClerkFat_Grey");
            task_25.Conditions.ItemClassNames.Insert("ZmbM_ClerkFat_Khaki");
            task_25.Conditions.ItemClassNames.Insert("ZmbM_ClerkFat_White");
            task_25.Conditions.ItemClassNames.Insert("ZmbM_CommercialPilotOld_Blue");
            task_25.Conditions.ItemClassNames.Insert("ZmbM_CommercialPilotOld_Brown");
            task_25.Conditions.ItemClassNames.Insert("ZmbM_CommercialPilotOld_Olive");
            task_25.Conditions.ItemClassNames.Insert("ZmbM_Gamedev_Black");
            task_25.Conditions.ItemClassNames.Insert("ZmbM_Gamedev_Blue");
            task_25.Conditions.ItemClassNames.Insert("ZmbM_Gamedev_Gray");
            task_25.Conditions.ItemClassNames.Insert("ZmbM_JournalistSkinny");
            task_25.Conditions.ItemClassNames.Insert("ZmbM_MotobikerFat_Beige");
            task_25.Conditions.ItemClassNames.Insert("ZmbM_SkaterYoung_Brown");
            task_25.Conditions.ItemClassNames.Insert("ZmbM_SkaterYoung_Green");
            task_25.Conditions.ItemClassNames.Insert("ZmbM_SkaterYoung_Grey");
            task_25.Conditions.ItemClassNames.Insert("ZmbM_CitizenASkinny_Brown");
            task_25.Conditions.ItemClassNames.Insert("ZmbM_ClerkFat_Brown");
            task_25.Conditions.ItemClassNames.Insert("ZmbM_CommercialPilotOld_Grey");
            task_25.Conditions.ItemClassNames.Insert("ZmbM_MotobikerFat_Black");
            task_25.Conditions.ItemClassNames.Insert("ZmbM_SkaterYoung_Blue");
            task_25.Conditions.ItemClassNames.Insert("ZmbM_FirefighterNormal");
            task_25.Conditions.ItemClassNames.Insert("ZmbM_ConstrWorkerNormal_Beige");
            task_25.Conditions.ItemClassNames.Insert("ZmbM_ConstrWorkerNormal_Black");
            task_25.Conditions.ItemClassNames.Insert("ZmbM_ConstrWorkerNormal_Green");
            task_25.Conditions.ItemClassNames.Insert("ZmbM_ConstrWorkerNormal_Grey");
            task_25.Conditions.ItemClassNames.Insert("ZmbM_HandymanNormal_Beige");
            task_25.Conditions.ItemClassNames.Insert("ZmbM_HandymanNormal_Blue");
            task_25.Conditions.ItemClassNames.Insert("ZmbM_HandymanNormal_Green");
            task_25.Conditions.ItemClassNames.Insert("ZmbM_HandymanNormal_Grey");
            task_25.Conditions.ItemClassNames.Insert("ZmbM_HandymanNormal_White");
            task_25.Conditions.ItemClassNames.Insert("ZmbM_HeavyIndustryWorker");
            task_25.Conditions.ItemClassNames.Insert("ZmbM_MechanicSkinny_Blue");
            task_25.Conditions.ItemClassNames.Insert("ZmbM_MechanicSkinny_Green");
            task_25.Conditions.ItemClassNames.Insert("ZmbM_MechanicSkinny_Grey");
            task_25.Conditions.ItemClassNames.Insert("ZmbM_MechanicSkinny_Red");
            task_25.Conditions.ItemClassNames.Insert("ZmbM_OffshoreWorker_Green");
            task_25.Conditions.ItemClassNames.Insert("ZmbM_OffshoreWorker_Orange");
            task_25.Conditions.ItemClassNames.Insert("ZmbM_OffshoreWorker_Red");
            task_25.Conditions.ItemClassNames.Insert("ZmbM_OffshoreWorker_Yellow");
            task_25.Conditions.ItemClassNames.Insert("ZmbM_PrisonerSkinny");
            task_25.Conditions.ItemClassNames.Insert("ZmbM_priestPopSkinny");
            task_25.Conditions.ItemClassNames.Insert("ZmbM_FishermanOld_Blue");
            task_25.Conditions.ItemClassNames.Insert("ZmbM_FishermanOld_Green");
            task_25.Conditions.ItemClassNames.Insert("ZmbM_FishermanOld_Grey");
            task_25.Conditions.ItemClassNames.Insert("ZmbM_FishermanOld_Red");
            task_25.Conditions.ItemClassNames.Insert("ZmbM_HermitSkinny_Beige");
            task_25.Conditions.ItemClassNames.Insert("ZmbM_HermitSkinny_Black");
            task_25.Conditions.ItemClassNames.Insert("ZmbM_HermitSkinny_Green");
            task_25.Conditions.ItemClassNames.Insert("ZmbM_HermitSkinny_Red");
            task_25.Conditions.ItemClassNames.Insert("ZmbM_HikerSkinny_Blue");
            task_25.Conditions.ItemClassNames.Insert("ZmbM_HikerSkinny_Green");
            task_25.Conditions.ItemClassNames.Insert("ZmbM_HikerSkinny_Yellow");
            task_25.Conditions.ItemClassNames.Insert("ZmbM_HunterOld_Autumn");
            task_25.Conditions.ItemClassNames.Insert("ZmbM_HunterOld_Spring");
            task_25.Conditions.ItemClassNames.Insert("ZmbM_HunterOld_Summer");
            task_25.Conditions.ItemClassNames.Insert("ZmbM_HunterOld_Winter");
            task_25.Conditions.ItemClassNames.Insert("ZmbM_FarmerFat_Blue");
            task_25.Conditions.ItemClassNames.Insert("ZmbM_FarmerFat_Brown");
            task_25.Conditions.ItemClassNames.Insert("ZmbM_FarmerFat_Green");
            task_25.Conditions.ItemClassNames.Insert("ZmbM_Jacket_beige");
            task_25.Conditions.ItemClassNames.Insert("ZmbM_Jacket_black");
            task_25.Conditions.ItemClassNames.Insert("ZmbM_Jacket_blue");
            task_25.Conditions.ItemClassNames.Insert("ZmbM_Jacket_brown");
            task_25.Conditions.ItemClassNames.Insert("ZmbM_Jacket_greenchecks");
            task_25.Conditions.ItemClassNames.Insert("ZmbM_Jacket_grey");
            task_25.Conditions.ItemClassNames.Insert("ZmbM_Jacket_khaki");
            task_25.Conditions.ItemClassNames.Insert("ZmbM_Jacket_stripes");
            task_25.Conditions.ItemClassNames.Insert("ZmbM_JoggerSkinny_Blue");
            task_25.Conditions.ItemClassNames.Insert("ZmbM_JoggerSkinny_Green");
            task_25.Conditions.ItemClassNames.Insert("ZmbM_VillagerOld_Blue");
            task_25.Conditions.ItemClassNames.Insert("ZmbM_VillagerOld_White");
            task_25.Conditions.ItemClassNames.Insert("ZmbM_FarmerFat_Beige");
            task_25.Conditions.ItemClassNames.Insert("ZmbM_Jacket_bluechecks");
            task_25.Conditions.ItemClassNames.Insert("ZmbM_Jacket_magenta");
            task_25.Conditions.ItemClassNames.Insert("ZmbM_JoggerSkinny_Red");
            task_25.Conditions.ItemClassNames.Insert("ZmbM_VillagerOld_Green");

            Tasks.Insert(task_25);
            ref DeutschZBattlepassTaskData task_26 = new DeutschZBattlepassTaskData();
            task_26.TaskId = "kill_zombies_weekly";
            task_26.Name = "Kill Zombies";
            task_26.Description = "Present in nearly every town, village, and lootable building.";
            task_26.TaskType = DeutschZBattlepassTaskType.KILL_INFECTED;
            task_26.Type = 0;
            task_26.Cycle = 2;
            task_26.Target = 200;
            task_26.XP = 850;
            task_26.TargetCount = 200;
            task_26.XpReward = 850;
            task_26.Daily = 0;
            task_26.Weekly = 1;
            task_26.PremiumOnly = 0;
            task_26.Conditions.MinKillDistance = -1.0;
            task_26.Conditions.MaxKillDistance = -1.0;


            task_26.Conditions.ItemClassNames.Insert("ZmbM_CitizenASkinny_Blue");
            task_26.Conditions.ItemClassNames.Insert("ZmbM_CitizenASkinny_Grey");
            task_26.Conditions.ItemClassNames.Insert("ZmbM_CitizenASkinny_Red");
            task_26.Conditions.ItemClassNames.Insert("ZmbM_CitizenBFat_Blue");
            task_26.Conditions.ItemClassNames.Insert("ZmbM_CitizenBFat_Green");
            task_26.Conditions.ItemClassNames.Insert("ZmbM_CitizenBFat_Red");
            task_26.Conditions.ItemClassNames.Insert("ZmbM_ClerkFat_Grey");
            task_26.Conditions.ItemClassNames.Insert("ZmbM_ClerkFat_Khaki");
            task_26.Conditions.ItemClassNames.Insert("ZmbM_ClerkFat_White");
            task_26.Conditions.ItemClassNames.Insert("ZmbM_CommercialPilotOld_Blue");
            task_26.Conditions.ItemClassNames.Insert("ZmbM_CommercialPilotOld_Brown");
            task_26.Conditions.ItemClassNames.Insert("ZmbM_CommercialPilotOld_Olive");
            task_26.Conditions.ItemClassNames.Insert("ZmbM_Gamedev_Black");
            task_26.Conditions.ItemClassNames.Insert("ZmbM_Gamedev_Blue");
            task_26.Conditions.ItemClassNames.Insert("ZmbM_Gamedev_Gray");
            task_26.Conditions.ItemClassNames.Insert("ZmbM_JournalistSkinny");
            task_26.Conditions.ItemClassNames.Insert("ZmbM_MotobikerFat_Beige");
            task_26.Conditions.ItemClassNames.Insert("ZmbM_SkaterYoung_Brown");
            task_26.Conditions.ItemClassNames.Insert("ZmbM_SkaterYoung_Green");
            task_26.Conditions.ItemClassNames.Insert("ZmbM_SkaterYoung_Grey");
            task_26.Conditions.ItemClassNames.Insert("ZmbM_CitizenASkinny_Brown");
            task_26.Conditions.ItemClassNames.Insert("ZmbM_ClerkFat_Brown");
            task_26.Conditions.ItemClassNames.Insert("ZmbM_CommercialPilotOld_Grey");
            task_26.Conditions.ItemClassNames.Insert("ZmbM_MotobikerFat_Black");
            task_26.Conditions.ItemClassNames.Insert("ZmbM_SkaterYoung_Blue");
            task_26.Conditions.ItemClassNames.Insert("ZmbM_FirefighterNormal");
            task_26.Conditions.ItemClassNames.Insert("ZmbM_ConstrWorkerNormal_Beige");
            task_26.Conditions.ItemClassNames.Insert("ZmbM_ConstrWorkerNormal_Black");
            task_26.Conditions.ItemClassNames.Insert("ZmbM_ConstrWorkerNormal_Green");
            task_26.Conditions.ItemClassNames.Insert("ZmbM_ConstrWorkerNormal_Grey");
            task_26.Conditions.ItemClassNames.Insert("ZmbM_HandymanNormal_Beige");
            task_26.Conditions.ItemClassNames.Insert("ZmbM_HandymanNormal_Blue");
            task_26.Conditions.ItemClassNames.Insert("ZmbM_HandymanNormal_Green");
            task_26.Conditions.ItemClassNames.Insert("ZmbM_HandymanNormal_Grey");
            task_26.Conditions.ItemClassNames.Insert("ZmbM_HandymanNormal_White");
            task_26.Conditions.ItemClassNames.Insert("ZmbM_HeavyIndustryWorker");
            task_26.Conditions.ItemClassNames.Insert("ZmbM_MechanicSkinny_Blue");
            task_26.Conditions.ItemClassNames.Insert("ZmbM_MechanicSkinny_Green");
            task_26.Conditions.ItemClassNames.Insert("ZmbM_MechanicSkinny_Grey");
            task_26.Conditions.ItemClassNames.Insert("ZmbM_MechanicSkinny_Red");
            task_26.Conditions.ItemClassNames.Insert("ZmbM_OffshoreWorker_Green");
            task_26.Conditions.ItemClassNames.Insert("ZmbM_OffshoreWorker_Orange");
            task_26.Conditions.ItemClassNames.Insert("ZmbM_OffshoreWorker_Red");
            task_26.Conditions.ItemClassNames.Insert("ZmbM_OffshoreWorker_Yellow");
            task_26.Conditions.ItemClassNames.Insert("ZmbM_PrisonerSkinny");
            task_26.Conditions.ItemClassNames.Insert("ZmbM_priestPopSkinny");
            task_26.Conditions.ItemClassNames.Insert("ZmbM_FishermanOld_Blue");
            task_26.Conditions.ItemClassNames.Insert("ZmbM_FishermanOld_Green");
            task_26.Conditions.ItemClassNames.Insert("ZmbM_FishermanOld_Grey");
            task_26.Conditions.ItemClassNames.Insert("ZmbM_FishermanOld_Red");
            task_26.Conditions.ItemClassNames.Insert("ZmbM_HermitSkinny_Beige");
            task_26.Conditions.ItemClassNames.Insert("ZmbM_HermitSkinny_Black");
            task_26.Conditions.ItemClassNames.Insert("ZmbM_HermitSkinny_Green");
            task_26.Conditions.ItemClassNames.Insert("ZmbM_HermitSkinny_Red");
            task_26.Conditions.ItemClassNames.Insert("ZmbM_HikerSkinny_Blue");
            task_26.Conditions.ItemClassNames.Insert("ZmbM_HikerSkinny_Green");
            task_26.Conditions.ItemClassNames.Insert("ZmbM_HikerSkinny_Yellow");
            task_26.Conditions.ItemClassNames.Insert("ZmbM_HunterOld_Autumn");
            task_26.Conditions.ItemClassNames.Insert("ZmbM_HunterOld_Spring");
            task_26.Conditions.ItemClassNames.Insert("ZmbM_HunterOld_Summer");
            task_26.Conditions.ItemClassNames.Insert("ZmbM_HunterOld_Winter");
            task_26.Conditions.ItemClassNames.Insert("ZmbM_FarmerFat_Blue");
            task_26.Conditions.ItemClassNames.Insert("ZmbM_FarmerFat_Brown");
            task_26.Conditions.ItemClassNames.Insert("ZmbM_FarmerFat_Green");
            task_26.Conditions.ItemClassNames.Insert("ZmbM_Jacket_beige");
            task_26.Conditions.ItemClassNames.Insert("ZmbM_Jacket_black");
            task_26.Conditions.ItemClassNames.Insert("ZmbM_Jacket_blue");
            task_26.Conditions.ItemClassNames.Insert("ZmbM_Jacket_brown");
            task_26.Conditions.ItemClassNames.Insert("ZmbM_Jacket_greenchecks");
            task_26.Conditions.ItemClassNames.Insert("ZmbM_Jacket_grey");
            task_26.Conditions.ItemClassNames.Insert("ZmbM_Jacket_khaki");
            task_26.Conditions.ItemClassNames.Insert("ZmbM_Jacket_stripes");
            task_26.Conditions.ItemClassNames.Insert("ZmbM_JoggerSkinny_Blue");
            task_26.Conditions.ItemClassNames.Insert("ZmbM_JoggerSkinny_Green");
            task_26.Conditions.ItemClassNames.Insert("ZmbM_VillagerOld_Blue");
            task_26.Conditions.ItemClassNames.Insert("ZmbM_VillagerOld_White");
            task_26.Conditions.ItemClassNames.Insert("ZmbM_FarmerFat_Beige");
            task_26.Conditions.ItemClassNames.Insert("ZmbM_Jacket_bluechecks");
            task_26.Conditions.ItemClassNames.Insert("ZmbM_Jacket_magenta");
            task_26.Conditions.ItemClassNames.Insert("ZmbM_JoggerSkinny_Red");
            task_26.Conditions.ItemClassNames.Insert("ZmbM_VillagerOld_Green");

            Tasks.Insert(task_26);
            ref DeutschZBattlepassTaskData task_27 = new DeutschZBattlepassTaskData();
            task_27.TaskId = "kill_police_zombies";
            task_27.Name = "Kill Police Zombies";
            task_27.Description = "Found near police stations in towns and cities.";
            task_27.TaskType = DeutschZBattlepassTaskType.KILL_INFECTED;
            task_27.Type = 0;
            task_27.Cycle = 1;
            task_27.Target = 8;
            task_27.XP = 95;
            task_27.TargetCount = 8;
            task_27.XpReward = 95;
            task_27.Daily = 1;
            task_27.Weekly = 0;
            task_27.PremiumOnly = 0;
            task_27.Conditions.MinKillDistance = -1.0;
            task_27.Conditions.MaxKillDistance = -1.0;


            task_27.Conditions.ItemClassNames.Insert("ZmbM_PolicemanFat");
            task_27.Conditions.ItemClassNames.Insert("ZmbM_PolicemanSpecForce");
            task_27.Conditions.ItemClassNames.Insert("ZmbM_PolicemanSpecForce_Heavy");

            Tasks.Insert(task_27);
            ref DeutschZBattlepassTaskData task_28 = new DeutschZBattlepassTaskData();
            task_28.TaskId = "kill_army_zombies";
            task_28.Name = "Kill Army Zombies";
            task_28.Description = "Found in military bases, checkpoints, and airfields.";
            task_28.TaskType = DeutschZBattlepassTaskType.KILL_INFECTED;
            task_28.Type = 0;
            task_28.Cycle = 1;
            task_28.Target = 10;
            task_28.XP = 140;
            task_28.TargetCount = 10;
            task_28.XpReward = 140;
            task_28.Daily = 1;
            task_28.Weekly = 0;
            task_28.PremiumOnly = 0;
            task_28.Conditions.MinKillDistance = -1.0;
            task_28.Conditions.MaxKillDistance = -1.0;


            task_28.Conditions.ItemClassNames.Insert("ZmbM_PatrolNormal_Autumn");
            task_28.Conditions.ItemClassNames.Insert("ZmbM_PatrolNormal_Flat");
            task_28.Conditions.ItemClassNames.Insert("ZmbM_PatrolNormal_PautRev");
            task_28.Conditions.ItemClassNames.Insert("ZmbM_PatrolNormal_Summer");
            task_28.Conditions.ItemClassNames.Insert("ZmbM_SoldierNormal");
            task_28.Conditions.ItemClassNames.Insert("ZmbM_usSoldier_normal_Desert");
            task_28.Conditions.ItemClassNames.Insert("ZmbM_usSoldier_normal_Woodland");
            task_28.Conditions.ItemClassNames.Insert("ZmbM_usSoldier_Heavy_Woodland");
            task_28.Conditions.ItemClassNames.Insert("ZmbM_usSoldier_Officer_Desert");

            Tasks.Insert(task_28);
            ref DeutschZBattlepassTaskData task_29 = new DeutschZBattlepassTaskData();
            task_29.TaskId = "kill_army_zombies_weekly";
            task_29.Name = "Kill Army Zombies";
            task_29.Description = "Found in military bases, checkpoints, and airfields.";
            task_29.TaskType = DeutschZBattlepassTaskType.KILL_INFECTED;
            task_29.Type = 0;
            task_29.Cycle = 2;
            task_29.Target = 75;
            task_29.XP = 800;
            task_29.TargetCount = 75;
            task_29.XpReward = 800;
            task_29.Daily = 0;
            task_29.Weekly = 1;
            task_29.PremiumOnly = 0;
            task_29.Conditions.MinKillDistance = -1.0;
            task_29.Conditions.MaxKillDistance = -1.0;


            task_29.Conditions.ItemClassNames.Insert("ZmbM_PatrolNormal_Autumn");
            task_29.Conditions.ItemClassNames.Insert("ZmbM_PatrolNormal_Flat");
            task_29.Conditions.ItemClassNames.Insert("ZmbM_PatrolNormal_PautRev");
            task_29.Conditions.ItemClassNames.Insert("ZmbM_PatrolNormal_Summer");
            task_29.Conditions.ItemClassNames.Insert("ZmbM_SoldierNormal");
            task_29.Conditions.ItemClassNames.Insert("ZmbM_usSoldier_normal_Desert");
            task_29.Conditions.ItemClassNames.Insert("ZmbM_usSoldier_normal_Woodland");
            task_29.Conditions.ItemClassNames.Insert("ZmbM_usSoldier_Heavy_Woodland");
            task_29.Conditions.ItemClassNames.Insert("ZmbM_usSoldier_Officer_Desert");

            Tasks.Insert(task_29);
            ref DeutschZBattlepassTaskData task_30 = new DeutschZBattlepassTaskData();
            task_30.TaskId = "kill_medical_zombies";
            task_30.Name = "Kill Medical Zombies";
            task_30.Description = "Found around hospitals, clinics, field hospitals, and medical tents.";
            task_30.TaskType = DeutschZBattlepassTaskType.KILL_INFECTED;
            task_30.Type = 0;
            task_30.Cycle = 1;
            task_30.Target = 5;
            task_30.XP = 80;
            task_30.TargetCount = 5;
            task_30.XpReward = 80;
            task_30.Daily = 1;
            task_30.Weekly = 0;
            task_30.PremiumOnly = 0;
            task_30.Conditions.MinKillDistance = -1.0;
            task_30.Conditions.MaxKillDistance = -1.0;


            task_30.Conditions.ItemClassNames.Insert("ZmbM_DoctorFat");
            task_30.Conditions.ItemClassNames.Insert("ZmbM_ParamedicNormal_Black");
            task_30.Conditions.ItemClassNames.Insert("ZmbM_ParamedicNormal_Blue");
            task_30.Conditions.ItemClassNames.Insert("ZmbM_ParamedicNormal_Green");
            task_30.Conditions.ItemClassNames.Insert("ZmbM_ParamedicNormal_Red");
            task_30.Conditions.ItemClassNames.Insert("ZmbM_PatientSkinny");

            Tasks.Insert(task_30);
            ref DeutschZBattlepassTaskData task_31 = new DeutschZBattlepassTaskData();
            task_31.TaskId = "kill_nbc_zombies";
            task_31.Name = "Kill NBC Zombies";
            task_31.Description = "Appear near contaminated zones, quarantine areas, and scientific facilities.";
            task_31.TaskType = DeutschZBattlepassTaskType.KILL_INFECTED;
            task_31.Type = 0;
            task_31.Cycle = 1;
            task_31.Target = 3;
            task_31.XP = 110;
            task_31.TargetCount = 3;
            task_31.XpReward = 110;
            task_31.Daily = 1;
            task_31.Weekly = 0;
            task_31.PremiumOnly = 0;
            task_31.Conditions.MinKillDistance = -1.0;
            task_31.Conditions.MaxKillDistance = -1.0;


            task_31.Conditions.ItemClassNames.Insert("ZmbM_NBC_Grey");
            task_31.Conditions.ItemClassNames.Insert("ZmbM_NBC_Yellow");

            Tasks.Insert(task_31);
            ref DeutschZBattlepassTaskData task_32 = new DeutschZBattlepassTaskData();
            task_32.TaskId = "kill_special_zombies";
            task_32.Name = "Kill Special Zombies";
            task_32.Description = "Found in underground bunkers or high-tier zones.";
            task_32.TaskType = DeutschZBattlepassTaskType.KILL_INFECTED;
            task_32.Type = 0;
            task_32.Cycle = 1;
            task_32.Target = 1;
            task_32.XP = 150;
            task_32.TargetCount = 1;
            task_32.XpReward = 150;
            task_32.Daily = 1;
            task_32.Weekly = 0;
            task_32.PremiumOnly = 0;
            task_32.Conditions.MinKillDistance = -1.0;
            task_32.Conditions.MaxKillDistance = -1.0;


            task_32.Conditions.ItemClassNames.Insert("ZmbM_Santa");

            Tasks.Insert(task_32);
            ref DeutschZBattlepassTaskData task_33 = new DeutschZBattlepassTaskData();
            task_33.TaskId = "kill_animals_season";
            task_33.Name = "Kill Animals";
            task_33.Description = "Hunt and kill 200 animals during the season.";
            task_33.TaskType = DeutschZBattlepassTaskType.CUSTOM;
            task_33.Type = 1;
            task_33.Cycle = 0;
            task_33.Target = 200;
            task_33.XP = 1500;
            task_33.TargetCount = 200;
            task_33.XpReward = 1500;
            task_33.Daily = 0;
            task_33.Weekly = 0;
            task_33.PremiumOnly = 0;
            task_33.Conditions.MinKillDistance = -1.0;
            task_33.Conditions.MaxKillDistance = -1.0;


            task_33.Conditions.ItemClassNames.Insert("Animal_VulpesVulpes");
            task_33.Conditions.ItemClassNames.Insert("Animal_LepusEuropaeus");
            task_33.Conditions.ItemClassNames.Insert("Animal_GallusGallusDomesticus");
            task_33.Conditions.ItemClassNames.Insert("Animal_GallusGallusDomesticusF_Brown");
            task_33.Conditions.ItemClassNames.Insert("Animal_GallusGallusDomesticusF_Spotted");
            task_33.Conditions.ItemClassNames.Insert("Animal_GallusGallusDomesticusF_White");
            task_33.Conditions.ItemClassNames.Insert("Animal_UrsusArctos");
            task_33.Conditions.ItemClassNames.Insert("Animal_BosTaurusF_Brown");
            task_33.Conditions.ItemClassNames.Insert("Animal_BosTaurusF_Spotted");
            task_33.Conditions.ItemClassNames.Insert("Animal_BosTaurusF_White");
            task_33.Conditions.ItemClassNames.Insert("Animal_BosTaurus_Brown");
            task_33.Conditions.ItemClassNames.Insert("Animal_BosTaurus_Spotted");
            task_33.Conditions.ItemClassNames.Insert("Animal_BosTaurus_White");
            task_33.Conditions.ItemClassNames.Insert("Animal_CervusElaphus");
            task_33.Conditions.ItemClassNames.Insert("Animal_CervusElaphusF");
            task_33.Conditions.ItemClassNames.Insert("Animal_CapraHircusF");
            task_33.Conditions.ItemClassNames.Insert("Animal_CapraHircus_Black");
            task_33.Conditions.ItemClassNames.Insert("Animal_CapraHircus_Brown");
            task_33.Conditions.ItemClassNames.Insert("Animal_CapraHircus_White");
            task_33.Conditions.ItemClassNames.Insert("Animal_SusDomesticus");
            task_33.Conditions.ItemClassNames.Insert("Animal_CapreolusCapreolus");
            task_33.Conditions.ItemClassNames.Insert("Animal_CapreolusCapreolusF");
            task_33.Conditions.ItemClassNames.Insert("Animal_OvisAries");
            task_33.Conditions.ItemClassNames.Insert("Animal_OvisAriesF");
            task_33.Conditions.ItemClassNames.Insert("Animal_SusScrofa");
            task_33.Conditions.ItemClassNames.Insert("Animal_CanisLupus_Grey");
            task_33.Conditions.ItemClassNames.Insert("Animal_CanisLupus_White");

            Tasks.Insert(task_33);
            ref DeutschZBattlepassTaskData task_34 = new DeutschZBattlepassTaskData();
            task_34.TaskId = "action_master_season";
            task_34.Name = "Action Master";
            task_34.Description = "Complete a wide range of player actions during the season.";
            task_34.TaskType = DeutschZBattlepassTaskType.CUSTOM;
            task_34.Type = 12;
            task_34.Cycle = 0;
            task_34.Target = 500;
            task_34.XP = 1500;
            task_34.TargetCount = 500;
            task_34.XpReward = 1500;
            task_34.Daily = 0;
            task_34.Weekly = 0;
            task_34.PremiumOnly = 0;
            task_34.Conditions.MinKillDistance = -1.0;
            task_34.Conditions.MaxKillDistance = -1.0;


            task_34.Conditions.ItemClassNames.Insert("ActionActivateTrap");
            task_34.Conditions.ItemClassNames.Insert("ActionAnimateCarSelection");
            task_34.Conditions.ItemClassNames.Insert("ActionAnimateSeats");
            task_34.Conditions.ItemClassNames.Insert("ActionAttachOnProxy");
            task_34.Conditions.ItemClassNames.Insert("ActionAttachOnSelection");
            task_34.Conditions.ItemClassNames.Insert("ActionAttachPowerSourceToPanel");
            task_34.Conditions.ItemClassNames.Insert("ActionAttachToConstruction");
            task_34.Conditions.ItemClassNames.Insert("ActionAttachWheels");
            task_34.Conditions.ItemClassNames.Insert("ActionBandageBase");
            task_34.Conditions.ItemClassNames.Insert("ActionBandageSelf");
            task_34.Conditions.ItemClassNames.Insert("ActionBandageTarget");
            task_34.Conditions.ItemClassNames.Insert("ActionBase_Basic");
            task_34.Conditions.ItemClassNames.Insert("ActionBiteCharcoalTablets");
            task_34.Conditions.ItemClassNames.Insert("ActionBitePainkillerTablets");
            task_34.Conditions.ItemClassNames.Insert("ActionBitePurificationTablets");
            task_34.Conditions.ItemClassNames.Insert("ActionBiteTetracyclineAntibiotics");
            task_34.Conditions.ItemClassNames.Insert("ActionBiteVitaminBottle");
            task_34.Conditions.ItemClassNames.Insert("ActionBreakLongWoodenStick");
            task_34.Conditions.ItemClassNames.Insert("ActionBuildPart");
            task_34.Conditions.ItemClassNames.Insert("ActionBuildPartSwitch");
            task_34.Conditions.ItemClassNames.Insert("ActionBuildShelter");
            task_34.Conditions.ItemClassNames.Insert("ActionBurnSewSelf");
            task_34.Conditions.ItemClassNames.Insert("ActionBurnSewTarget");
            task_34.Conditions.ItemClassNames.Insert("ActionBuryBody");
            task_34.Conditions.ItemClassNames.Insert("ActionCarDoors");
            task_34.Conditions.ItemClassNames.Insert("ActionCarDoorsOutside");
            task_34.Conditions.ItemClassNames.Insert("ActionCheckPulse");
            task_34.Conditions.ItemClassNames.Insert("ActionClapBearTrapWithThisItem");
            task_34.Conditions.ItemClassNames.Insert("ActionClose");
            task_34.Conditions.ItemClassNames.Insert("ActionCloseBarrel");
            task_34.Conditions.ItemClassNames.Insert("ActionCloseBarrelHoles");
            task_34.Conditions.ItemClassNames.Insert("ActionCloseCarDoors");
            task_34.Conditions.ItemClassNames.Insert("ActionCloseCarDoorsOutside");
            task_34.Conditions.ItemClassNames.Insert("ActionCloseDoors");
            task_34.Conditions.ItemClassNames.Insert("ActionCloseFence");
            task_34.Conditions.ItemClassNames.Insert("ActionCollectBloodSelf");
            task_34.Conditions.ItemClassNames.Insert("ActionCollectBloodTarget");
            task_34.Conditions.ItemClassNames.Insert("ActionCollectBloodTargetLambda");
            task_34.Conditions.ItemClassNames.Insert("ActionCollectSampleSelf");
            task_34.Conditions.ItemClassNames.Insert("ActionCollectSampleTarget");
            task_34.Conditions.ItemClassNames.Insert("ActionConstructor");
            task_34.Conditions.ItemClassNames.Insert("ActionConsume");
            task_34.Conditions.ItemClassNames.Insert("ActionConsumeSingle");
            task_34.Conditions.ItemClassNames.Insert("ActionContinuousBase");
            task_34.Conditions.ItemClassNames.Insert("ActionCookOnStick");
            task_34.Conditions.ItemClassNames.Insert("ActionCoverHeadSelf");
            task_34.Conditions.ItemClassNames.Insert("ActionCoverHeadTarget");
            task_34.Conditions.ItemClassNames.Insert("ActionCPR");
            task_34.Conditions.ItemClassNames.Insert("ActionCraft");
            task_34.Conditions.ItemClassNames.Insert("ActionCreateIndoorFireplace");
            task_34.Conditions.ItemClassNames.Insert("ActionCreateIndoorOven");
            task_34.Conditions.ItemClassNames.Insert("ActionData");
            task_34.Conditions.ItemClassNames.Insert("ActionDebug");
            task_34.Conditions.ItemClassNames.Insert("ActionDebugReciveData");
            task_34.Conditions.ItemClassNames.Insert("ActionDeconstructShelter");
            task_34.Conditions.ItemClassNames.Insert("ActionDefibrilateBase");
            task_34.Conditions.ItemClassNames.Insert("ActionDefibrilateSelf");
            task_34.Conditions.ItemClassNames.Insert("ActionDefibrilateTarget");
            task_34.Conditions.ItemClassNames.Insert("ActionDeployObject");
            task_34.Conditions.ItemClassNames.Insert("ActionDestroyCombinationLock");
            task_34.Conditions.ItemClassNames.Insert("ActionDestroyPart");
            task_34.Conditions.ItemClassNames.Insert("ActionDetachFromTarget");
            task_34.Conditions.ItemClassNames.Insert("ActionDetachFromTarget_SpecificSlot_WoodenPlanks");
            task_34.Conditions.ItemClassNames.Insert("ActionDetachFromTarget_SpecificSlotsCategory");
            task_34.Conditions.ItemClassNames.Insert("ActionDetachFromTarget_SpecificSlotsCategory_Barrel");
            task_34.Conditions.ItemClassNames.Insert("ActionDetachPowerSourceFromPanel");
            task_34.Conditions.ItemClassNames.Insert("ActionDigGardenPlot");
            task_34.Conditions.ItemClassNames.Insert("ActionDigInStash");
            task_34.Conditions.ItemClassNames.Insert("ActionDigOutStash");
            task_34.Conditions.ItemClassNames.Insert("ActionDigWorms");
            task_34.Conditions.ItemClassNames.Insert("ActionDisinfectPlant");
            task_34.Conditions.ItemClassNames.Insert("ActionDisinfectPlantBit");
            task_34.Conditions.ItemClassNames.Insert("ActionDisinfectSelf");
            task_34.Conditions.ItemClassNames.Insert("ActionDisinfectTarget");
            task_34.Conditions.ItemClassNames.Insert("ActionDismantleGardenPlot");
            task_34.Conditions.ItemClassNames.Insert("ActionDismantlePart");
            task_34.Conditions.ItemClassNames.Insert("ActionDrink");
            task_34.Conditions.ItemClassNames.Insert("ActionDrinkAlcohol");
            task_34.Conditions.ItemClassNames.Insert("ActionDrinkCan");
            task_34.Conditions.ItemClassNames.Insert("ActionDrinkCookingPot");
            task_34.Conditions.ItemClassNames.Insert("ActionDrinkDisinfectant");
            task_34.Conditions.ItemClassNames.Insert("ActionDrinkDisinfectant2");
            task_34.Conditions.ItemClassNames.Insert("ActionDrinkPondContinuous");
            task_34.Conditions.ItemClassNames.Insert("ActionDrinkWellContinuous");
            task_34.Conditions.ItemClassNames.Insert("ActionDropItem");
            task_34.Conditions.ItemClassNames.Insert("ActionDropItemSimple");
            task_34.Conditions.ItemClassNames.Insert("ActionEat");
            task_34.Conditions.ItemClassNames.Insert("ActionEatCan");
            task_34.Conditions.ItemClassNames.Insert("ActionEatCharcoalTablets");
            task_34.Conditions.ItemClassNames.Insert("ActionEatFruit");
            task_34.Conditions.ItemClassNames.Insert("ActionEatMeat");
            task_34.Conditions.ItemClassNames.Insert("ActionEatPainkillerTablets");
            task_34.Conditions.ItemClassNames.Insert("ActionEatPurificationTablets");
            task_34.Conditions.ItemClassNames.Insert("ActionEatSmall");
            task_34.Conditions.ItemClassNames.Insert("ActionEatTetracyclineAntibiotics");
            task_34.Conditions.ItemClassNames.Insert("ActionEatVitaminBottle");
            task_34.Conditions.ItemClassNames.Insert("ActionEmptyBottleBase");
            task_34.Conditions.ItemClassNames.Insert("ActionEmptyCookingPot");
            task_34.Conditions.ItemClassNames.Insert("ActionEmptyMagazine");
            task_34.Conditions.ItemClassNames.Insert("ActionEmptySeedsPack");
            task_34.Conditions.ItemClassNames.Insert("ActionEnterLadder");
            task_34.Conditions.ItemClassNames.Insert("ActionExitLadder");
            task_34.Conditions.ItemClassNames.Insert("ActionExtinguishFireplaceByExtinguisher");
            task_34.Conditions.ItemClassNames.Insert("ActionExtinguishFireplaceByLiquid");
            task_34.Conditions.ItemClassNames.Insert("ActionFeedCharcoalTablets");
            task_34.Conditions.ItemClassNames.Insert("ActionFeedPainkillerTablets");
            task_34.Conditions.ItemClassNames.Insert("ActionFeedPurificationTablets");
            task_34.Conditions.ItemClassNames.Insert("ActionFeedTetracyclineAntibiotics");
            task_34.Conditions.ItemClassNames.Insert("ActionFeedVitaminBottle");
            task_34.Conditions.ItemClassNames.Insert("ActionFertilizeSlot");
            task_34.Conditions.ItemClassNames.Insert("ActionFillBottleBase");
            task_34.Conditions.ItemClassNames.Insert("ActionFillBrakes");
            task_34.Conditions.ItemClassNames.Insert("ActionFillCoolant");
            task_34.Conditions.ItemClassNames.Insert("ActionFillFuel");
            task_34.Conditions.ItemClassNames.Insert("ActionFillGeneratorTank");
            task_34.Conditions.ItemClassNames.Insert("ActionFillObject");
            task_34.Conditions.ItemClassNames.Insert("ActionFillOil");
            task_34.Conditions.ItemClassNames.Insert("ActionFishingNew");
            task_34.Conditions.ItemClassNames.Insert("ActionFoldBandanaToHead");
            task_34.Conditions.ItemClassNames.Insert("ActionFoldBandanaToMask");
            task_34.Conditions.ItemClassNames.Insert("ActionFoldEntityToSlot");
            task_34.Conditions.ItemClassNames.Insert("ActionFoldObject");
            task_34.Conditions.ItemClassNames.Insert("ActionForceABite");
            task_34.Conditions.ItemClassNames.Insert("ActionForceABiteCan");
            task_34.Conditions.ItemClassNames.Insert("ActionForceASip");
            task_34.Conditions.ItemClassNames.Insert("ActionForceBiteCharcoalTablets");
            task_34.Conditions.ItemClassNames.Insert("ActionForceBitePainkillerTablets");
            task_34.Conditions.ItemClassNames.Insert("ActionForceBitePurificationTablets");
            task_34.Conditions.ItemClassNames.Insert("ActionForceBiteTetracyclineAntibiotics");
            task_34.Conditions.ItemClassNames.Insert("ActionForceBiteVitaminBottle");
            task_34.Conditions.ItemClassNames.Insert("ActionForceConsume");
            task_34.Conditions.ItemClassNames.Insert("ActionForceConsumeSingle");
            task_34.Conditions.ItemClassNames.Insert("ActionForceDrink");
            task_34.Conditions.ItemClassNames.Insert("ActionForceDrinkAlcohol");
            task_34.Conditions.ItemClassNames.Insert("ActionForceDrinkDisinfectant");
            task_34.Conditions.ItemClassNames.Insert("ActionForceFeed");
            task_34.Conditions.ItemClassNames.Insert("ActionForceFeedCan");
            task_34.Conditions.ItemClassNames.Insert("ActionForceFeedMeat");
            task_34.Conditions.ItemClassNames.Insert("ActionGagSelf");
            task_34.Conditions.ItemClassNames.Insert("ActionGagTarget");
            task_34.Conditions.ItemClassNames.Insert("ActionGetInTransport");
            task_34.Conditions.ItemClassNames.Insert("ActionGiveBloodData");
            task_34.Conditions.ItemClassNames.Insert("ActionGiveBloodSelf");
            task_34.Conditions.ItemClassNames.Insert("ActionGiveBloodTarget");
            task_34.Conditions.ItemClassNames.Insert("ActionGiveSalineSelf");
            task_34.Conditions.ItemClassNames.Insert("ActionGiveSalineTarget");
            task_34.Conditions.ItemClassNames.Insert("ActionHandcuffTarget");
            task_34.Conditions.ItemClassNames.Insert("ActionHandsPartSwitch");
            task_34.Conditions.ItemClassNames.Insert("ActionHarvestCrops");
            task_34.Conditions.ItemClassNames.Insert("ActionIgniteFireplaceByAir");
            task_34.Conditions.ItemClassNames.Insert("ActionInjectEpinephrineSelf");
            task_34.Conditions.ItemClassNames.Insert("ActionInjectEpinephrineTarget");
            task_34.Conditions.ItemClassNames.Insert("ActionInjectMorphineSelf");
            task_34.Conditions.ItemClassNames.Insert("ActionInjectMorphineTarget");
            task_34.Conditions.ItemClassNames.Insert("ActionInjectSelf");
            task_34.Conditions.ItemClassNames.Insert("ActionInjectTarget");
            task_34.Conditions.ItemClassNames.Insert("ActionInput");
            task_34.Conditions.ItemClassNames.Insert("ActionInput_Basic");
            task_34.Conditions.ItemClassNames.Insert("ActionInsertSparkplug");
            task_34.Conditions.ItemClassNames.Insert("ActionInstantBase");
            task_34.Conditions.ItemClassNames.Insert("ActionInteractBase");
            task_34.Conditions.ItemClassNames.Insert("ActionInteractLoopBase");
            task_34.Conditions.ItemClassNames.Insert("ActionITest");
            task_34.Conditions.ItemClassNames.Insert("ActionLoadMagazine");
            task_34.Conditions.ItemClassNames.Insert("ActionLoadMagazineQuick");
            task_34.Conditions.ItemClassNames.Insert("ActionLockDoors");
            task_34.Conditions.ItemClassNames.Insert("ActionLockedDoors");
            task_34.Conditions.ItemClassNames.Insert("ActionLowerFlag");
            task_34.Conditions.ItemClassNames.Insert("ActionManagerBase");
            task_34.Conditions.ItemClassNames.Insert("ActionManagerClient");
            task_34.Conditions.ItemClassNames.Insert("ActionManagerServer");
            task_34.Conditions.ItemClassNames.Insert("ActionMeasureBattery");
            task_34.Conditions.ItemClassNames.Insert("ActionMeasureTemperatureSelf");
            task_34.Conditions.ItemClassNames.Insert("ActionMeasureTemperatureTarget");
            task_34.Conditions.ItemClassNames.Insert("ActionMenu");
            task_34.Conditions.ItemClassNames.Insert("ActionMineBush");
            task_34.Conditions.ItemClassNames.Insert("ActionMineBushByHand");
            task_34.Conditions.ItemClassNames.Insert("ActionMineRock");
            task_34.Conditions.ItemClassNames.Insert("ActionMineRock1H");
            task_34.Conditions.ItemClassNames.Insert("ActionMineTree");
            task_34.Conditions.ItemClassNames.Insert("ActionMineTreeBark");
            task_34.Conditions.ItemClassNames.Insert("ActionMountBarbedWire");
            task_34.Conditions.ItemClassNames.Insert("ActionNextCombinationLockDial");
            task_34.Conditions.ItemClassNames.Insert("ActionNextCombinationLockDialOnTarget");
            task_34.Conditions.ItemClassNames.Insert("ActionOpen");
            task_34.Conditions.ItemClassNames.Insert("ActionOpenBarrel");
            task_34.Conditions.ItemClassNames.Insert("ActionOpenBarrelHoles");
            task_34.Conditions.ItemClassNames.Insert("ActionOpenCarDoors");
            task_34.Conditions.ItemClassNames.Insert("ActionOpenCarDoorsOutside");
            task_34.Conditions.ItemClassNames.Insert("ActionOpenDoors");
            task_34.Conditions.ItemClassNames.Insert("ActionOpenFence");
            task_34.Conditions.ItemClassNames.Insert("ActionPickBerry");
            task_34.Conditions.ItemClassNames.Insert("ActionPlaceFireplaceIndoor");
            task_34.Conditions.ItemClassNames.Insert("ActionPlaceFireplaceIntoBarrel");
            task_34.Conditions.ItemClassNames.Insert("ActionPlaceObject");
            task_34.Conditions.ItemClassNames.Insert("ActionPlaceOnGround");
            task_34.Conditions.ItemClassNames.Insert("ActionPlaceOvenIndoor");
            task_34.Conditions.ItemClassNames.Insert("ActionPlantSeed");
            task_34.Conditions.ItemClassNames.Insert("ActionPlugIn");
            task_34.Conditions.ItemClassNames.Insert("ActionPlugIntoFence");
            task_34.Conditions.ItemClassNames.Insert("ActionPlugTargetIntoThis");
            task_34.Conditions.ItemClassNames.Insert("ActionPullBodyFromTransport");
            task_34.Conditions.ItemClassNames.Insert("ActionPullOutPlug");
            task_34.Conditions.ItemClassNames.Insert("ActionRaiseFlag");
            task_34.Conditions.ItemClassNames.Insert("ActionReadPaper");
            task_34.Conditions.ItemClassNames.Insert("ActionRemovePlant");
            task_34.Conditions.ItemClassNames.Insert("ActionRepackTent");
            task_34.Conditions.ItemClassNames.Insert("ActionRepairCarChassis");
            task_34.Conditions.ItemClassNames.Insert("ActionRepairCarEngine");
            task_34.Conditions.ItemClassNames.Insert("ActionRepairCarPart");
            task_34.Conditions.ItemClassNames.Insert("ActionRepairPart");
            task_34.Conditions.ItemClassNames.Insert("ActionRepairShelter");
            task_34.Conditions.ItemClassNames.Insert("ActionRepairTent");
            task_34.Conditions.ItemClassNames.Insert("ActionRepairTentPart");
            task_34.Conditions.ItemClassNames.Insert("ActionRepairWithToolFromHands");
            task_34.Conditions.ItemClassNames.Insert("ActionRepositionPluggedItem");
            task_34.Conditions.ItemClassNames.Insert("ActionRestrainSelf");
            task_34.Conditions.ItemClassNames.Insert("ActionRestrainTarget");
            task_34.Conditions.ItemClassNames.Insert("ActionSawPlanks");
            task_34.Conditions.ItemClassNames.Insert("ActionSewSelf");
            task_34.Conditions.ItemClassNames.Insert("ActionSewTarget");
            task_34.Conditions.ItemClassNames.Insert("ActionShave");
            task_34.Conditions.ItemClassNames.Insert("ActionShaveTarget");
            task_34.Conditions.ItemClassNames.Insert("ActionSidePlateInteract");
            task_34.Conditions.ItemClassNames.Insert("ActionSingleUseBase");
            task_34.Conditions.ItemClassNames.Insert("ActionSkinning");
            task_34.Conditions.ItemClassNames.Insert("ActionSortAmmoPile");
            task_34.Conditions.ItemClassNames.Insert("ActionSplintSelf");
            task_34.Conditions.ItemClassNames.Insert("ActionSplintTarget");
            task_34.Conditions.ItemClassNames.Insert("ActionStartEngine");
            task_34.Conditions.ItemClassNames.Insert("ActionStopEngine");
            task_34.Conditions.ItemClassNames.Insert("ActionStripCarrierVest");
            task_34.Conditions.ItemClassNames.Insert("ActionSwapItemToHands");
            task_34.Conditions.ItemClassNames.Insert("ActionSwitchLights");
            task_34.Conditions.ItemClassNames.Insert("ActionSwitchSeats");
            task_34.Conditions.ItemClassNames.Insert("ActionTakeABite");
            task_34.Conditions.ItemClassNames.Insert("ActionTakeABiteCan");
            task_34.Conditions.ItemClassNames.Insert("ActionTakeASip");
            task_34.Conditions.ItemClassNames.Insert("ActionTakeFireplaceFromBarrel");
            task_34.Conditions.ItemClassNames.Insert("ActionTakeFireplaceIndoor");
            task_34.Conditions.ItemClassNames.Insert("ActionTakeHybridAttachment");
            task_34.Conditions.ItemClassNames.Insert("ActionTakeHybridAttachmentToHands");
            task_34.Conditions.ItemClassNames.Insert("ActionTakeItem");
            task_34.Conditions.ItemClassNames.Insert("ActionTakeItemToHands");
            task_34.Conditions.ItemClassNames.Insert("ActionTakeMaterialToHands");
            task_34.Conditions.ItemClassNames.Insert("ActionTakeMaterialToHandsSwitch");
            task_34.Conditions.ItemClassNames.Insert("ActionTakeOvenIndoor");
            task_34.Conditions.ItemClassNames.Insert("ActionTargetLighSource");
            task_34.Conditions.ItemClassNames.Insert("ActionTargets");
            task_34.Conditions.ItemClassNames.Insert("ActionTestBloodSelf");
            task_34.Conditions.ItemClassNames.Insert("ActionTestBloodTarget");
            task_34.Conditions.ItemClassNames.Insert("ActionToggleNVG");
            task_34.Conditions.ItemClassNames.Insert("ActionTogglePlaceObject");
            task_34.Conditions.ItemClassNames.Insert("ActionToggleTentOpen");
            task_34.Conditions.ItemClassNames.Insert("ActionTransferLiquid");
            task_34.Conditions.ItemClassNames.Insert("ActionTuneFrequencyOnGround");
            task_34.Conditions.ItemClassNames.Insert("ActionTurnOffHeadtorch");
            task_34.Conditions.ItemClassNames.Insert("ActionTurnOffHelmetFlashlight");
            task_34.Conditions.ItemClassNames.Insert("ActionTurnOffPowerGenerator");
            task_34.Conditions.ItemClassNames.Insert("ActionTurnOffSpotlight");
            task_34.Conditions.ItemClassNames.Insert("ActionTurnOffTransmitterOnGround");
            task_34.Conditions.ItemClassNames.Insert("ActionTurnOffWeaponFlashlight");
            task_34.Conditions.ItemClassNames.Insert("ActionTurnOffWhileInHands");
            task_34.Conditions.ItemClassNames.Insert("ActionTurnOffWhileOnGround");
            task_34.Conditions.ItemClassNames.Insert("ActionTurnOnChemlight");
            task_34.Conditions.ItemClassNames.Insert("ActionTurnOnHeadtorch");
            task_34.Conditions.ItemClassNames.Insert("ActionTurnOnHeatpack");
            task_34.Conditions.ItemClassNames.Insert("ActionTurnOnHelmetFlashlight");
            task_34.Conditions.ItemClassNames.Insert("ActionTurnOnPowerGenerator");
            task_34.Conditions.ItemClassNames.Insert("ActionTurnOnSpotlight");
            task_34.Conditions.ItemClassNames.Insert("ActionTurnOnTransmitterOnGround");
            task_34.Conditions.ItemClassNames.Insert("ActionTurnOnWeaponFlashlight");
            task_34.Conditions.ItemClassNames.Insert("ActionTurnOnWhileInHands");
            task_34.Conditions.ItemClassNames.Insert("ActionTurnOnWhileOnGround");
            task_34.Conditions.ItemClassNames.Insert("ActionUncoverHeadSelf");
            task_34.Conditions.ItemClassNames.Insert("ActionUncoverHeadTarget");
            task_34.Conditions.ItemClassNames.Insert("ActionUnfoldBandana");
            task_34.Conditions.ItemClassNames.Insert("ActionUnfoldEntity");
            task_34.Conditions.ItemClassNames.Insert("ActionUngagSelf");
            task_34.Conditions.ItemClassNames.Insert("ActionUngagTarget");
            task_34.Conditions.ItemClassNames.Insert("ActionUnlockDoors");
            task_34.Conditions.ItemClassNames.Insert("ActionUnmountBarbedWire");
            task_34.Conditions.ItemClassNames.Insert("ActionUnpackBox");
            task_34.Conditions.ItemClassNames.Insert("ActionUnplugThisByCord");
            task_34.Conditions.ItemClassNames.Insert("ActionUnrestrainSelf");
            task_34.Conditions.ItemClassNames.Insert("ActionUnrestrainTarget");
            task_34.Conditions.ItemClassNames.Insert("ActionUpgradeTorchFromGasPump");
            task_34.Conditions.ItemClassNames.Insert("ActionUseRangefinder");
            task_34.Conditions.ItemClassNames.Insert("ActionViewBinoculars");
            task_34.Conditions.ItemClassNames.Insert("ActionViewCompass");
            task_34.Conditions.ItemClassNames.Insert("ActionViewOptics");
            task_34.Conditions.ItemClassNames.Insert("ActionWashHandsItem");
            task_34.Conditions.ItemClassNames.Insert("ActionWashHandsWater");
            task_34.Conditions.ItemClassNames.Insert("ActionWashHandsWell");
            task_34.Conditions.ItemClassNames.Insert("ActionWaterGardenSlot");
            task_34.Conditions.ItemClassNames.Insert("ActionWaterPlant");
            task_34.Conditions.ItemClassNames.Insert("ActionWorldCraft");
            task_34.Conditions.ItemClassNames.Insert("ActionWorldCraftCancel");
            task_34.Conditions.ItemClassNames.Insert("ActionWorldCraftSwitch");
            task_34.Conditions.ItemClassNames.Insert("ActionWorldFlagActionSwitch");
            task_34.Conditions.ItemClassNames.Insert("ActionWorldLiquidActionSwitch");
            task_34.Conditions.ItemClassNames.Insert("ActionWringClothes");
            task_34.Conditions.ItemClassNames.Insert("ActionWritePaper");
            task_34.Conditions.ItemClassNames.Insert("ActionZoomIn");
            task_34.Conditions.ItemClassNames.Insert("ActionZoomOut");

            Tasks.Insert(task_34);
        }
    }
}

class DeutschZBattlepassPremiumItemConfig
{
    string ClassName;
    int Days;
    int ConsumeOnUse;
    string DisplayName;

    void DeutschZBattlepassPremiumItemConfig()
    {
        ClassName = "Chemlight_Red";
        Days = 30;
        ConsumeOnUse = 1;
        DisplayName = "DeutschZ Premium Glowstick";
    }
}

class DeutschZBattlepassPremiumConfig
{
    int ConfigVersion;
    int PremiumEnabled;
    string PremiumInfo;
    int PremiumItemActivationEnabled;
    int ExtendExistingPremium;
    int RevokePremiumOnExpiry;
    int ExpiryCheckIntervalSeconds;
    string ActivateActionText;
    string ActivatedMessagePrefix;
    string ExtendedMessagePrefix;
    string ExpiredMessage;
    string DisabledMessage;
    string InvalidItemMessage;
    string PremiumDisabledMessage;
    int DebugLogging;
    ref array<string> Admins;
    ref array<string> PremiumPlayers;
    ref array<ref DeutschZBattlepassPremiumItemConfig> PremiumItems;
    ref array<ref DeutschZBattlepassRewardData> PremiumRewards;

    void DeutschZBattlepassPremiumConfig()
    {
        ConfigVersion = 3;
        PremiumEnabled = 1;
        PremiumInfo = "Premium rewards are server controlled. Premium can be unlocked by configured premium items or admin config.";
        PremiumItemActivationEnabled = 1;
        ExtendExistingPremium = 1;
        RevokePremiumOnExpiry = 1;
        ExpiryCheckIntervalSeconds = 60;
        ActivateActionText = "Activate Premium";
        ActivatedMessagePrefix = "Premium Battlepass activated for";
        ExtendedMessagePrefix = "Premium Battlepass extended by";
        ExpiredMessage = "Premium Battlepass access has expired.";
        DisabledMessage = "Premium activation items are disabled on this server.";
        InvalidItemMessage = "This item is not configured as a Premium activation item.";
        PremiumDisabledMessage = "Premium Battlepass rewards are disabled on this server.";
        DebugLogging = 0;
        Admins = new array<string>();
        PremiumPlayers = new array<string>();
        PremiumItems = new array<ref DeutschZBattlepassPremiumItemConfig>();
        PremiumRewards = new array<ref DeutschZBattlepassRewardData>();
    }

    void InsertDefaults()
    {
        ConfigVersion = 3;
        if (ActivateActionText == "")
        {
            ActivateActionText = "Activate Premium";
        }
        if (ExpiryCheckIntervalSeconds <= 0)
        {
            ExpiryCheckIntervalSeconds = 60;
        }
        if (ActivatedMessagePrefix == "")
        {
            ActivatedMessagePrefix = "Premium Battlepass activated for";
        }
        if (ExtendedMessagePrefix == "")
        {
            ExtendedMessagePrefix = "Premium Battlepass extended by";
        }
        if (ExpiredMessage == "")
        {
            ExpiredMessage = "Premium Battlepass access has expired.";
        }
        if (DisabledMessage == "")
        {
            DisabledMessage = "Premium activation items are disabled on this server.";
        }
        if (InvalidItemMessage == "")
        {
            InvalidItemMessage = "This item is not configured as a Premium activation item.";
        }
        if (PremiumDisabledMessage == "")
        {
            PremiumDisabledMessage = "Premium Battlepass rewards are disabled on this server.";
        }
        if (!Admins)
        {
            Admins = new array<string>();
        }
        if (!PremiumPlayers)
        {
            PremiumPlayers = new array<string>();
        }
        if (!PremiumItems)
        {
            PremiumItems = new array<ref DeutschZBattlepassPremiumItemConfig>();
        }
        if (!PremiumRewards)
        {
            PremiumRewards = new array<ref DeutschZBattlepassRewardData>();
        }
        if (PremiumItems.Count() == 0)
        {
            ref DeutschZBattlepassPremiumItemConfig glow = new DeutschZBattlepassPremiumItemConfig();
            glow.ClassName = "Chemlight_Red";
            glow.Days = 30;
            glow.ConsumeOnUse = 1;
            glow.DisplayName = "DeutschZ Premium Glowstick";
            PremiumItems.Insert(glow);

            ref DeutschZBattlepassPremiumItemConfig coin7 = new DeutschZBattlepassPremiumItemConfig();
            coin7.ClassName = "ABP_PremiumCoin_7Day";
            coin7.Days = 7;
            coin7.ConsumeOnUse = 1;
            coin7.DisplayName = "Premium Coin 7 Days";
            PremiumItems.Insert(coin7);

            ref DeutschZBattlepassPremiumItemConfig coin30 = new DeutschZBattlepassPremiumItemConfig();
            coin30.ClassName = "ABP_PremiumCoin_30Day";
            coin30.Days = 30;
            coin30.ConsumeOnUse = 1;
            coin30.DisplayName = "Premium Coin 30 Days";
            PremiumItems.Insert(coin30);
        }
        if (PremiumRewards.Count() == 0)
        {
            ref DeutschZBattlepassRewardData rp_1_1 = new DeutschZBattlepassRewardData();
            rp_1_1.RewardId = "premium_level_1_1_mkii";
            rp_1_1.DisplayName = "Level 1 Premium - MKII";
            rp_1_1.Level = 1;
            rp_1_1.XPRequired = 0;
            rp_1_1.RewardType = DeutschZBattlepassRewardType.ITEM;
            rp_1_1.ItemClass = "MKII";
            rp_1_1.Quantity = 1;
            rp_1_1.HealthPercent = 100;
            rp_1_1.PremiumOnly = 1;
            rp_1_1.AttachmentPreset = "";
            rp_1_1.AttachmentCSV = "Mag_MKII_10Rnd";
            rp_1_1.Attachments.Insert("Mag_MKII_10Rnd");
            PremiumRewards.Insert(rp_1_1);
            ref DeutschZBattlepassRewardData rp_2_1 = new DeutschZBattlepassRewardData();
            rp_2_1.RewardId = "premium_level_2_1_cz75";
            rp_2_1.DisplayName = "Level 2 Premium - CZ75";
            rp_2_1.Level = 2;
            rp_2_1.XPRequired = 100;
            rp_2_1.RewardType = DeutschZBattlepassRewardType.ITEM;
            rp_2_1.ItemClass = "CZ75";
            rp_2_1.Quantity = 1;
            rp_2_1.HealthPercent = 100;
            rp_2_1.PremiumOnly = 1;
            rp_2_1.AttachmentPreset = "";
            rp_2_1.AttachmentCSV = "Mag_CZ75_15Rnd";
            rp_2_1.Attachments.Insert("Mag_CZ75_15Rnd");
            PremiumRewards.Insert(rp_2_1);
            ref DeutschZBattlepassRewardData rp_3_1 = new DeutschZBattlepassRewardData();
            rp_3_1.RewardId = "premium_level_3_1_metalwire";
            rp_3_1.DisplayName = "Level 3 Premium - MetalWire";
            rp_3_1.Level = 3;
            rp_3_1.XPRequired = 200;
            rp_3_1.RewardType = DeutschZBattlepassRewardType.ITEM;
            rp_3_1.ItemClass = "MetalWire";
            rp_3_1.Quantity = 1;
            rp_3_1.HealthPercent = 100;
            rp_3_1.PremiumOnly = 1;
            rp_3_1.AttachmentPreset = "";
            rp_3_1.AttachmentCSV = "";

            PremiumRewards.Insert(rp_3_1);
            ref DeutschZBattlepassRewardData rp_4_1 = new DeutschZBattlepassRewardData();
            rp_4_1.RewardId = "premium_level_4_1_fnx45";
            rp_4_1.DisplayName = "Level 4 Premium - FNX45";
            rp_4_1.Level = 4;
            rp_4_1.XPRequired = 300;
            rp_4_1.RewardType = DeutschZBattlepassRewardType.ITEM;
            rp_4_1.ItemClass = "FNX45";
            rp_4_1.Quantity = 1;
            rp_4_1.HealthPercent = 100;
            rp_4_1.PremiumOnly = 1;
            rp_4_1.AttachmentPreset = "";
            rp_4_1.AttachmentCSV = "Mag_FNX45_15Rnd";
            rp_4_1.Attachments.Insert("Mag_FNX45_15Rnd");
            PremiumRewards.Insert(rp_4_1);
            ref DeutschZBattlepassRewardData rp_4_2 = new DeutschZBattlepassRewardData();
            rp_4_2.RewardId = "premium_level_4_2_ammo_45acp";
            rp_4_2.DisplayName = "Level 4 Premium - Ammo_45ACP";
            rp_4_2.Level = 4;
            rp_4_2.XPRequired = 300;
            rp_4_2.RewardType = DeutschZBattlepassRewardType.ITEM;
            rp_4_2.ItemClass = "Ammo_45ACP";
            rp_4_2.Quantity = 20;
            rp_4_2.HealthPercent = 100;
            rp_4_2.PremiumOnly = 1;
            rp_4_2.AttachmentPreset = "";
            rp_4_2.AttachmentCSV = "";

            PremiumRewards.Insert(rp_4_2);
            ref DeutschZBattlepassRewardData rp_5_1 = new DeutschZBattlepassRewardData();
            rp_5_1.RewardId = "premium_level_5_1_ducttape";
            rp_5_1.DisplayName = "Level 5 Premium - DuctTape";
            rp_5_1.Level = 5;
            rp_5_1.XPRequired = 500;
            rp_5_1.RewardType = DeutschZBattlepassRewardType.ITEM;
            rp_5_1.ItemClass = "DuctTape";
            rp_5_1.Quantity = 3;
            rp_5_1.HealthPercent = 100;
            rp_5_1.PremiumOnly = 1;
            rp_5_1.AttachmentPreset = "";
            rp_5_1.AttachmentCSV = "";

            PremiumRewards.Insert(rp_5_1);
            ref DeutschZBattlepassRewardData rp_5_2 = new DeutschZBattlepassRewardData();
            rp_5_2.RewardId = "premium_level_5_2_sewingkit";
            rp_5_2.DisplayName = "Level 5 Premium - SewingKit";
            rp_5_2.Level = 5;
            rp_5_2.XPRequired = 500;
            rp_5_2.RewardType = DeutschZBattlepassRewardType.ITEM;
            rp_5_2.ItemClass = "SewingKit";
            rp_5_2.Quantity = 1;
            rp_5_2.HealthPercent = 100;
            rp_5_2.PremiumOnly = 1;
            rp_5_2.AttachmentPreset = "";
            rp_5_2.AttachmentCSV = "";

            PremiumRewards.Insert(rp_5_2);
            ref DeutschZBattlepassRewardData rp_6_1 = new DeutschZBattlepassRewardData();
            rp_6_1.RewardId = "premium_level_6_1_deagle";
            rp_6_1.DisplayName = "Level 6 Premium - Deagle";
            rp_6_1.Level = 6;
            rp_6_1.XPRequired = 600;
            rp_6_1.RewardType = DeutschZBattlepassRewardType.ITEM;
            rp_6_1.ItemClass = "Deagle";
            rp_6_1.Quantity = 1;
            rp_6_1.HealthPercent = 100;
            rp_6_1.PremiumOnly = 1;
            rp_6_1.AttachmentPreset = "";
            rp_6_1.AttachmentCSV = "Mag_Deagle_9rnd";
            rp_6_1.Attachments.Insert("Mag_Deagle_9rnd");
            PremiumRewards.Insert(rp_6_1);
            ref DeutschZBattlepassRewardData rp_6_2 = new DeutschZBattlepassRewardData();
            rp_6_2.RewardId = "premium_level_6_2_ammo_357";
            rp_6_2.DisplayName = "Level 6 Premium - Ammo_357";
            rp_6_2.Level = 6;
            rp_6_2.XPRequired = 600;
            rp_6_2.RewardType = DeutschZBattlepassRewardType.ITEM;
            rp_6_2.ItemClass = "Ammo_357";
            rp_6_2.Quantity = 20;
            rp_6_2.HealthPercent = 100;
            rp_6_2.PremiumOnly = 1;
            rp_6_2.AttachmentPreset = "";
            rp_6_2.AttachmentCSV = "";

            PremiumRewards.Insert(rp_6_2);
            ref DeutschZBattlepassRewardData rp_7_1 = new DeutschZBattlepassRewardData();
            rp_7_1.RewardId = "premium_level_7_1_firstaidkit";
            rp_7_1.DisplayName = "Level 7 Premium - FirstAidKit";
            rp_7_1.Level = 7;
            rp_7_1.XPRequired = 700;
            rp_7_1.RewardType = DeutschZBattlepassRewardType.ITEM;
            rp_7_1.ItemClass = "FirstAidKit";
            rp_7_1.Quantity = 1;
            rp_7_1.HealthPercent = 100;
            rp_7_1.PremiumOnly = 1;
            rp_7_1.AttachmentPreset = "";
            rp_7_1.AttachmentCSV = "";

            PremiumRewards.Insert(rp_7_1);
            ref DeutschZBattlepassRewardData rp_8_1 = new DeutschZBattlepassRewardData();
            rp_8_1.RewardId = "premium_level_8_1_pp19";
            rp_8_1.DisplayName = "Level 8 Premium - PP19";
            rp_8_1.Level = 8;
            rp_8_1.XPRequired = 800;
            rp_8_1.RewardType = DeutschZBattlepassRewardType.ITEM;
            rp_8_1.ItemClass = "PP19";
            rp_8_1.Quantity = 1;
            rp_8_1.HealthPercent = 100;
            rp_8_1.PremiumOnly = 1;
            rp_8_1.AttachmentPreset = "";
            rp_8_1.AttachmentCSV = "PP19_Bttstck,Mag_PP19_64Rnd";
            rp_8_1.Attachments.Insert("PP19_Bttstck");
            rp_8_1.Attachments.Insert("Mag_PP19_64Rnd");
            PremiumRewards.Insert(rp_8_1);
            ref DeutschZBattlepassRewardData rp_9_1 = new DeutschZBattlepassRewardData();
            rp_9_1.RewardId = "premium_level_9_1_tacticalbaconcan";
            rp_9_1.DisplayName = "Level 9 Premium - TacticalBaconCan";
            rp_9_1.Level = 9;
            rp_9_1.XPRequired = 900;
            rp_9_1.RewardType = DeutschZBattlepassRewardType.ITEM;
            rp_9_1.ItemClass = "TacticalBaconCan";
            rp_9_1.Quantity = 3;
            rp_9_1.HealthPercent = 100;
            rp_9_1.PremiumOnly = 1;
            rp_9_1.AttachmentPreset = "";
            rp_9_1.AttachmentCSV = "";

            PremiumRewards.Insert(rp_9_1);
            ref DeutschZBattlepassRewardData rp_10_1 = new DeutschZBattlepassRewardData();
            rp_10_1.RewardId = "premium_level_10_1_seachest";
            rp_10_1.DisplayName = "Level 10 Premium - SeaChest";
            rp_10_1.Level = 10;
            rp_10_1.XPRequired = 1000;
            rp_10_1.RewardType = DeutschZBattlepassRewardType.ITEM;
            rp_10_1.ItemClass = "SeaChest";
            rp_10_1.Quantity = 1;
            rp_10_1.HealthPercent = 100;
            rp_10_1.PremiumOnly = 1;
            rp_10_1.AttachmentPreset = "";
            rp_10_1.AttachmentCSV = "";

            PremiumRewards.Insert(rp_10_1);
            ref DeutschZBattlepassRewardData rp_11_1 = new DeutschZBattlepassRewardData();
            rp_11_1.RewardId = "premium_level_11_1_mp5k";
            rp_11_1.DisplayName = "Level 11 Premium - MP5K";
            rp_11_1.Level = 11;
            rp_11_1.XPRequired = 1100;
            rp_11_1.RewardType = DeutschZBattlepassRewardType.ITEM;
            rp_11_1.ItemClass = "MP5K";
            rp_11_1.Quantity = 1;
            rp_11_1.HealthPercent = 100;
            rp_11_1.PremiumOnly = 1;
            rp_11_1.AttachmentPreset = "";
            rp_11_1.AttachmentCSV = "MP5_RailHndgrd,MP5k_StockBttstck,Mag_MP5_30Rnd";
            rp_11_1.Attachments.Insert("MP5_RailHndgrd");
            rp_11_1.Attachments.Insert("MP5k_StockBttstck");
            rp_11_1.Attachments.Insert("Mag_MP5_30Rnd");
            PremiumRewards.Insert(rp_11_1);
            ref DeutschZBattlepassRewardData rp_12_1 = new DeutschZBattlepassRewardData();
            rp_12_1.RewardId = "premium_level_12_1_platecarriervest";
            rp_12_1.DisplayName = "Level 12 Premium - PlateCarrierVest";
            rp_12_1.Level = 12;
            rp_12_1.XPRequired = 1200;
            rp_12_1.RewardType = DeutschZBattlepassRewardType.ITEM;
            rp_12_1.ItemClass = "PlateCarrierVest";
            rp_12_1.Quantity = 1;
            rp_12_1.HealthPercent = 100;
            rp_12_1.PremiumOnly = 1;
            rp_12_1.AttachmentPreset = "";
            rp_12_1.AttachmentCSV = "";

            PremiumRewards.Insert(rp_12_1);
            ref DeutschZBattlepassRewardData rp_13_1 = new DeutschZBattlepassRewardData();
            rp_13_1.RewardId = "premium_level_13_1_vss";
            rp_13_1.DisplayName = "Level 13 Premium - VSS";
            rp_13_1.Level = 13;
            rp_13_1.XPRequired = 1300;
            rp_13_1.RewardType = DeutschZBattlepassRewardType.ITEM;
            rp_13_1.ItemClass = "VSS";
            rp_13_1.Quantity = 1;
            rp_13_1.HealthPercent = 100;
            rp_13_1.PremiumOnly = 1;
            rp_13_1.AttachmentPreset = "";
            rp_13_1.AttachmentCSV = "KashtanOptic,Mag_VSS_10Rnd";
            rp_13_1.Attachments.Insert("KashtanOptic");
            rp_13_1.Attachments.Insert("Mag_VSS_10Rnd");
            PremiumRewards.Insert(rp_13_1);
            ref DeutschZBattlepassRewardData rp_14_1 = new DeutschZBattlepassRewardData();
            rp_14_1.RewardId = "premium_level_14_1_sparkplug";
            rp_14_1.DisplayName = "Level 14 Premium - SparkPlug";
            rp_14_1.Level = 14;
            rp_14_1.XPRequired = 1400;
            rp_14_1.RewardType = DeutschZBattlepassRewardType.ITEM;
            rp_14_1.ItemClass = "SparkPlug";
            rp_14_1.Quantity = 1;
            rp_14_1.HealthPercent = 100;
            rp_14_1.PremiumOnly = 1;
            rp_14_1.AttachmentPreset = "";
            rp_14_1.AttachmentCSV = "";

            PremiumRewards.Insert(rp_14_1);
            ref DeutschZBattlepassRewardData rp_15_1 = new DeutschZBattlepassRewardData();
            rp_15_1.RewardId = "premium_level_15_1_canistergasoline";
            rp_15_1.DisplayName = "Level 15 Premium - CanisterGasoline";
            rp_15_1.Level = 15;
            rp_15_1.XPRequired = 1500;
            rp_15_1.RewardType = DeutschZBattlepassRewardType.ITEM;
            rp_15_1.ItemClass = "CanisterGasoline";
            rp_15_1.Quantity = 1;
            rp_15_1.HealthPercent = 100;
            rp_15_1.PremiumOnly = 1;
            rp_15_1.AttachmentPreset = "";
            rp_15_1.AttachmentCSV = "";

            PremiumRewards.Insert(rp_15_1);
            ref DeutschZBattlepassRewardData rp_16_1 = new DeutschZBattlepassRewardData();
            rp_16_1.RewardId = "premium_level_16_1_winchester70";
            rp_16_1.DisplayName = "Level 16 Premium - Winchester70";
            rp_16_1.Level = 16;
            rp_16_1.XPRequired = 1600;
            rp_16_1.RewardType = DeutschZBattlepassRewardType.ITEM;
            rp_16_1.ItemClass = "Winchester70";
            rp_16_1.Quantity = 1;
            rp_16_1.HealthPercent = 100;
            rp_16_1.PremiumOnly = 1;
            rp_16_1.AttachmentPreset = "";
            rp_16_1.AttachmentCSV = "HuntingOptic";
            rp_16_1.Attachments.Insert("HuntingOptic");
            PremiumRewards.Insert(rp_16_1);
            ref DeutschZBattlepassRewardData rp_17_1 = new DeutschZBattlepassRewardData();
            rp_17_1.RewardId = "premium_level_17_1_nvgheadstrap";
            rp_17_1.DisplayName = "Level 17 Premium - NVGHeadstrap";
            rp_17_1.Level = 17;
            rp_17_1.XPRequired = 1700;
            rp_17_1.RewardType = DeutschZBattlepassRewardType.ITEM;
            rp_17_1.ItemClass = "NVGHeadstrap";
            rp_17_1.Quantity = 1;
            rp_17_1.HealthPercent = 100;
            rp_17_1.PremiumOnly = 1;
            rp_17_1.AttachmentPreset = "";
            rp_17_1.AttachmentCSV = "NVGoggles";
            rp_17_1.Attachments.Insert("NVGoggles");
            PremiumRewards.Insert(rp_17_1);
            ref DeutschZBattlepassRewardData rp_18_1 = new DeutschZBattlepassRewardData();
            rp_18_1.RewardId = "premium_level_18_1_ballistichelmet_woodland";
            rp_18_1.DisplayName = "Level 18 Premium - BallisticHelmet_Woodland";
            rp_18_1.Level = 18;
            rp_18_1.XPRequired = 1800;
            rp_18_1.RewardType = DeutschZBattlepassRewardType.ITEM;
            rp_18_1.ItemClass = "BallisticHelmet_Woodland";
            rp_18_1.Quantity = 1;
            rp_18_1.HealthPercent = 100;
            rp_18_1.PremiumOnly = 1;
            rp_18_1.AttachmentPreset = "";
            rp_18_1.AttachmentCSV = "";

            PremiumRewards.Insert(rp_18_1);
            ref DeutschZBattlepassRewardData rp_19_1 = new DeutschZBattlepassRewardData();
            rp_19_1.RewardId = "premium_level_19_1_akm";
            rp_19_1.DisplayName = "Level 19 Premium - AKM";
            rp_19_1.Level = 19;
            rp_19_1.XPRequired = 1900;
            rp_19_1.RewardType = DeutschZBattlepassRewardType.ITEM;
            rp_19_1.ItemClass = "AKM";
            rp_19_1.Quantity = 1;
            rp_19_1.HealthPercent = 100;
            rp_19_1.PremiumOnly = 1;
            rp_19_1.AttachmentPreset = "";
            rp_19_1.AttachmentCSV = "AK_PlasticBttstck,AK_PlasticHndgrd,Mag_AKM_30Rnd";
            rp_19_1.Attachments.Insert("AK_PlasticBttstck");
            rp_19_1.Attachments.Insert("AK_PlasticHndgrd");
            rp_19_1.Attachments.Insert("Mag_AKM_30Rnd");
            PremiumRewards.Insert(rp_19_1);
            ref DeutschZBattlepassRewardData rp_20_1 = new DeutschZBattlepassRewardData();
            rp_20_1.RewardId = "premium_level_20_1_weaponcleaningkit";
            rp_20_1.DisplayName = "Level 20 Premium - WeaponCleaningKit";
            rp_20_1.Level = 20;
            rp_20_1.XPRequired = 2000;
            rp_20_1.RewardType = DeutschZBattlepassRewardType.ITEM;
            rp_20_1.ItemClass = "WeaponCleaningKit";
            rp_20_1.Quantity = 2;
            rp_20_1.HealthPercent = 100;
            rp_20_1.PremiumOnly = 1;
            rp_20_1.AttachmentPreset = "";
            rp_20_1.AttachmentCSV = "";

            PremiumRewards.Insert(rp_20_1);
            ref DeutschZBattlepassRewardData rp_21_1 = new DeutschZBattlepassRewardData();
            rp_21_1.RewardId = "premium_level_21_1_aks74u";
            rp_21_1.DisplayName = "Level 21 Premium - AKS74U";
            rp_21_1.Level = 21;
            rp_21_1.XPRequired = 2100;
            rp_21_1.RewardType = DeutschZBattlepassRewardType.ITEM;
            rp_21_1.ItemClass = "AKS74U";
            rp_21_1.Quantity = 1;
            rp_21_1.HealthPercent = 100;
            rp_21_1.PremiumOnly = 1;
            rp_21_1.AttachmentPreset = "";
            rp_21_1.AttachmentCSV = "AKS74U_Bttstck,Mag_AK74_30Rnd";
            rp_21_1.Attachments.Insert("AKS74U_Bttstck");
            rp_21_1.Attachments.Insert("Mag_AK74_30Rnd");
            PremiumRewards.Insert(rp_21_1);
            ref DeutschZBattlepassRewardData rp_22_1 = new DeutschZBattlepassRewardData();
            rp_22_1.RewardId = "premium_level_22_1_poxantidote";
            rp_22_1.DisplayName = "Level 22 Premium - POXAntidote";
            rp_22_1.Level = 22;
            rp_22_1.XPRequired = 2200;
            rp_22_1.RewardType = DeutschZBattlepassRewardType.ITEM;
            rp_22_1.ItemClass = "POXAntidote";
            rp_22_1.Quantity = 1;
            rp_22_1.HealthPercent = 100;
            rp_22_1.PremiumOnly = 1;
            rp_22_1.AttachmentPreset = "";
            rp_22_1.AttachmentCSV = "";

            PremiumRewards.Insert(rp_22_1);
            ref DeutschZBattlepassRewardData rp_23_1 = new DeutschZBattlepassRewardData();
            rp_23_1.RewardId = "premium_level_23_1_m4a1";
            rp_23_1.DisplayName = "Level 23 Premium - M4A1";
            rp_23_1.Level = 23;
            rp_23_1.XPRequired = 2300;
            rp_23_1.RewardType = DeutschZBattlepassRewardType.ITEM;
            rp_23_1.ItemClass = "M4A1";
            rp_23_1.Quantity = 1;
            rp_23_1.HealthPercent = 100;
            rp_23_1.PremiumOnly = 1;
            rp_23_1.AttachmentPreset = "";
            rp_23_1.AttachmentCSV = "M4_OEBttstck,M4_PlasticHndgrd,M4_CarryHandleOptic,Mag_CMAG_30Rnd";
            rp_23_1.Attachments.Insert("M4_OEBttstck");
            rp_23_1.Attachments.Insert("M4_PlasticHndgrd");
            rp_23_1.Attachments.Insert("M4_CarryHandleOptic");
            rp_23_1.Attachments.Insert("Mag_CMAG_30Rnd");
            PremiumRewards.Insert(rp_23_1);
            ref DeutschZBattlepassRewardData rp_24_1 = new DeutschZBattlepassRewardData();
            rp_24_1.RewardId = "premium_level_24_1_ghillieatt_mossy";
            rp_24_1.DisplayName = "Level 24 Premium - GhillieAtt_Mossy";
            rp_24_1.Level = 24;
            rp_24_1.XPRequired = 2400;
            rp_24_1.RewardType = DeutschZBattlepassRewardType.ITEM;
            rp_24_1.ItemClass = "GhillieAtt_Mossy";
            rp_24_1.Quantity = 1;
            rp_24_1.HealthPercent = 100;
            rp_24_1.PremiumOnly = 1;
            rp_24_1.AttachmentPreset = "";
            rp_24_1.AttachmentCSV = "";

            PremiumRewards.Insert(rp_24_1);
            ref DeutschZBattlepassRewardData rp_25_1 = new DeutschZBattlepassRewardData();
            rp_25_1.RewardId = "premium_level_25_1_famas";
            rp_25_1.DisplayName = "Level 25 Premium - FAMAS";
            rp_25_1.Level = 25;
            rp_25_1.XPRequired = 2500;
            rp_25_1.RewardType = DeutschZBattlepassRewardType.ITEM;
            rp_25_1.ItemClass = "FAMAS";
            rp_25_1.Quantity = 1;
            rp_25_1.HealthPercent = 100;
            rp_25_1.PremiumOnly = 1;
            rp_25_1.AttachmentPreset = "";
            rp_25_1.AttachmentCSV = "Mag_FAMAS_25Rnd";
            rp_25_1.Attachments.Insert("Mag_FAMAS_25Rnd");
            PremiumRewards.Insert(rp_25_1);
            ref DeutschZBattlepassRewardData rp_26_1 = new DeutschZBattlepassRewardData();
            rp_26_1.RewardId = "premium_level_26_1_camonet";
            rp_26_1.DisplayName = "Level 26 Premium - CamoNet";
            rp_26_1.Level = 26;
            rp_26_1.XPRequired = 2600;
            rp_26_1.RewardType = DeutschZBattlepassRewardType.ITEM;
            rp_26_1.ItemClass = "CamoNet";
            rp_26_1.Quantity = 1;
            rp_26_1.HealthPercent = 100;
            rp_26_1.PremiumOnly = 1;
            rp_26_1.AttachmentPreset = "";
            rp_26_1.AttachmentCSV = "";

            PremiumRewards.Insert(rp_26_1);
            ref DeutschZBattlepassRewardData rp_27_1 = new DeutschZBattlepassRewardData();
            rp_27_1.RewardId = "premium_level_27_1_lockpick";
            rp_27_1.DisplayName = "Level 27 Premium - Lockpick";
            rp_27_1.Level = 27;
            rp_27_1.XPRequired = 2700;
            rp_27_1.RewardType = DeutschZBattlepassRewardType.ITEM;
            rp_27_1.ItemClass = "Lockpick";
            rp_27_1.Quantity = 1;
            rp_27_1.HealthPercent = 100;
            rp_27_1.PremiumOnly = 1;
            rp_27_1.AttachmentPreset = "";
            rp_27_1.AttachmentCSV = "";

            PremiumRewards.Insert(rp_27_1);
            ref DeutschZBattlepassRewardData rp_28_1 = new DeutschZBattlepassRewardData();
            rp_28_1.RewardId = "premium_level_28_1_ammo_762x54";
            rp_28_1.DisplayName = "Level 28 Premium - Ammo_762x54";
            rp_28_1.Level = 28;
            rp_28_1.XPRequired = 2800;
            rp_28_1.RewardType = DeutschZBattlepassRewardType.ITEM;
            rp_28_1.ItemClass = "Ammo_762x54";
            rp_28_1.Quantity = 20;
            rp_28_1.HealthPercent = 100;
            rp_28_1.PremiumOnly = 1;
            rp_28_1.AttachmentPreset = "";
            rp_28_1.AttachmentCSV = "";

            PremiumRewards.Insert(rp_28_1);
            ref DeutschZBattlepassRewardData rp_29_1 = new DeutschZBattlepassRewardData();
            rp_29_1.RewardId = "premium_level_29_1_fal";
            rp_29_1.DisplayName = "Level 29 Premium - FAL";
            rp_29_1.Level = 29;
            rp_29_1.XPRequired = 2900;
            rp_29_1.RewardType = DeutschZBattlepassRewardType.ITEM;
            rp_29_1.ItemClass = "FAL";
            rp_29_1.Quantity = 1;
            rp_29_1.HealthPercent = 100;
            rp_29_1.PremiumOnly = 1;
            rp_29_1.AttachmentPreset = "";
            rp_29_1.AttachmentCSV = "Fal_FoldingBttstck,Mag_FAL_20Rnd";
            rp_29_1.Attachments.Insert("Fal_FoldingBttstck");
            rp_29_1.Attachments.Insert("Mag_FAL_20Rnd");
            PremiumRewards.Insert(rp_29_1);
        }
    }
}
