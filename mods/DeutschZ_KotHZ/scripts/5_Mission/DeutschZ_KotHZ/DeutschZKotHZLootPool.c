/*
DeutschZ ModZ
Eigenstaendige Implementierung fuer DeutschZ.
Autor/Eigentuemer: Patrick Sluzalek / fck1701.
Keine direkte Codeuebernahme aus Drittquellen.
Oeffentliche Quellen werden nur zur Konzept- und API-Verifikation genutzt.
*/

class DeutschZKotHZLootPool
{
    string EditHint;
    string PoolName;

    // RewardMode:
    // 0 = give rewards directly to winner inventory
    // 1 = spawn reward crate and place rewards inside
    int RewardMode;
    string CrateClassName;
    int CrateSpawnAtFlagpole;
    float CrateSpawnDistanceFromFlagpole;
    int CrateLifetimeSeconds;
    int DeleteCrateOnEventEnd;

    ref array<ref DeutschZKotHZReward> Rewards;

    void DeutschZKotHZLootPool()
    {
        EditHint = "Loot pool config. Default pools are vanilla-safe. Add modded classnames only when those mods are loaded.";
        PoolName = "Default";
        RewardMode = 1;
        CrateClassName = "DeutschZKotHZ_RewardCrate";
        CrateSpawnAtFlagpole = 1;
        CrateSpawnDistanceFromFlagpole = 6.0;
        CrateLifetimeSeconds = 1800;
        DeleteCrateOnEventEnd = 0;

        Rewards = new array<ref DeutschZKotHZReward>;
    }
}

class DeutschZKotHZLootPoolsConfig
{
    string ConfigInfo;
    ref array<ref DeutschZKotHZLootPool> LootPools;

    void DeutschZKotHZLootPoolsConfig()
    {
        ConfigInfo = "DeutschZ_KotHZ loot pool config. Shipped defaults are vanilla-safe so the core mod needs only CF. Add REV/SNAFU/MMG/BBP/RaG/etc. rewards manually if those mods are loaded.";
        LootPools = new array<ref DeutschZKotHZLootPool>;

        CreateDeutschZTestHighValuePool();
        CreateKVM1TestPool();
        CreateDefaultPool();
        CreateDeutschZMilitaryPool();
        CreateDeutschZBasebuildingPool();
    }


    protected void CreateDeutschZTestHighValuePool()
    {
        DeutschZKotHZLootPool pool = new DeutschZKotHZLootPool();
        pool.PoolName = "DeutschZ_Test_HighValue";
        pool.EditHint = "FIX17 TESTVERSION: echte wertvolle Beute aus All-classes-and-their-attachments.json, plus Custom-KotHZ Items. Sichtbarer Reward in DeutschZKotHZ_RewardCrate. Primaere Mod-Classnames haben sichere Fallbacks, falls einzelne Waffenmods fehlen.";
        pool.RewardMode = 1;
        pool.CrateClassName = "DeutschZKotHZ_RewardCrate";
        pool.CrateSpawnAtFlagpole = 1;
        pool.CrateSpawnDistanceFromFlagpole = 6.0;
        pool.CrateLifetimeSeconds = 7200;
        pool.DeleteCrateOnEventEnd = 0;

        DeutschZKotHZReward m82 = AddReward(pool, "GCGN_M82_Barret", -1, 100.0, 1, "GCGN_M82_Mag");
        AddAlternative(m82, "SNAFUGM6Lynx");
        AddAlternative(m82, "SVD");
        AddAttachment(m82, "SNAFU_Nightforce", -1, 100.0, 1);
        AddAttachment(m82, "SNAFU_50bmg_Suppressor_B", -1, 75.0, 1);
        AddCargo(m82, "GCGN_M82_Mag", 3, 100.0, 3);
        AddCargo(m82, "GCGN_Ammo_50Cal", 2, 100.0, 2);
        AddCargo(m82, "TTC_Ammo_50BMG", 2, 80.0, 2);

        DeutschZKotHZReward lynx = AddReward(pool, "SNAFUGM6Lynx", -1, 75.0, 1, "SNAFUGM6Lynx_5rdMag");
        AddAlternative(lynx, "GCGN_M82_Barret");
        AddAlternative(lynx, "SVD");
        AddAttachment(lynx, "SNAFU_Nightforce", -1, 100.0, 1);
        AddCargo(lynx, "SNAFUGM6Lynx_5rdMag", 3, 100.0, 3);
        AddCargo(lynx, "GCGN_Ammo_50Cal", 2, 100.0, 2);

        DeutschZKotHZReward as50 = AddReward(pool, "SNAFU_AS50_GUN", -1, 65.0, 1, "SNAFU_AS50_Mag");
        AddAlternative(as50, "GCGN_M82_Barret");
        AddAlternative(as50, "SVD");
        AddAttachment(as50, "SNAFU_Nightforce", -1, 100.0, 1);
        AddAttachment(as50, "Snafu_ScarH_SIL_Black", -1, 45.0, 1);
        AddCargo(as50, "SNAFU_AS50_Mag", 3, 100.0, 3);
        AddCargo(as50, "GCGN_Ammo_50Cal", 2, 100.0, 2);
        AddCargo(as50, "TTC_Ammo_50BMG", 2, 80.0, 2);

        DeutschZKotHZReward tac = AddReward(pool, "SNAFUTac21", -1, 100.0, 1, "SNAFUTac21_5rdMag");
        AddAlternative(tac, "Winchester70");
        AddAttachment(tac, "SNAFU_Nightforce", -1, 100.0, 1);
        AddAttachment(tac, "SNAFUKivaari_338_Supp", -1, 50.0, 1);
        AddCargo(tac, "SNAFUTac21_5rdMag", 4, 100.0, 4);
        AddCargo(tac, "SNAFU_Ammo_338", 3, 100.0, 3);
        AddCargo(tac, "Ammo_Expansion_338", 2, 60.0, 2);

        DeutschZKotHZReward scar = AddReward(pool, "Snafu_ScarH_Black_GUN", -1, 80.0, 1, "SNAFU_ScarH_100RND_Mag_Black");
        AddAlternative(scar, "FAL");
        AddAttachment(scar, "SNAFU_HNightforce", -1, 80.0, 1);
        AddAttachment(scar, "Snafu_ScarH_SIL_Black", -1, 70.0, 1);
        AddCargo(scar, "SNAFU_ScarH_100RND_Mag_Black", 2, 100.0, 2);
        AddCargo(scar, "Snafu_ScarH_25RND_Mag_BK", 4, 100.0, 4);
        AddCargo(scar, "AmmoBox_308Win_20Rnd", 4, 100.0, 4);

        // FIX38: Vanilla M249/Mag_M249_Box200Rnd removed from KotHZ default rewards because it can crash on CreateInInventory.
        // GCGN_M249 stays allowed as requested.
        DeutschZKotHZReward gcgnM249 = AddReward(pool, "GCGN_M249", -1, 100.0, 1, "GCGN_M249_Mag");
        AddAlternative(gcgnM249, "M4A1");
        AddAttachment(gcgnM249, "SNAFU_EOTech_EXPS3", -1, 80.0, 1);
        AddCargo(gcgnM249, "GCGN_M249_Mag", 2, 80.0, 2);
        AddCargo(gcgnM249, "AmmoBox_556x45_20Rnd", 6, 100.0, 6);

        DeutschZKotHZReward m4 = AddReward(pool, "M4A1", -1, 100.0, 1, "Mag_STANAG_60Rnd");
        AddAttachment(m4, "M4_PlasticHndgrd", -1, 100.0, 1);
        AddAttachment(m4, "M4_OEBttstck", -1, 100.0, 1);
        AddAttachment(m4, "M68Optic", -1, 100.0, 1);
        AddAttachment(m4, "M4_Suppressor", -1, 80.0, 1);
        AddCargo(m4, "Mag_STANAG_60Rnd", 4, 100.0, 4);
        AddCargo(m4, "AmmoBox_556x45_20Rnd", 5, 100.0, 5);

        DeutschZKotHZReward akm = AddReward(pool, "AKM", -1, 100.0, 1, "Mag_AKM_Drum75Rnd");
        AddAttachment(akm, "AK_PlasticBttstck_Black", -1, 100.0, 1);
        AddAttachment(akm, "KobraOptic", -1, 80.0, 1);
        AddAttachment(akm, "AK_Suppressor", -1, 80.0, 1);
        AddCargo(akm, "Mag_AKM_Drum75Rnd", 2, 100.0, 2);
        AddCargo(akm, "Mag_AKM_30Rnd", 4, 100.0, 4);
        AddCargo(akm, "AmmoBox_762x39_20Rnd", 5, 100.0, 5);

        DeutschZKotHZReward svd = AddReward(pool, "SVD", -1, 100.0, 1, "Mag_SVD_10Rnd");
        AddAttachment(svd, "PSO1Optic", -1, 100.0, 1);
        AddAttachment(svd, "AK_Suppressor", -1, 90.0, 1);
        AddCargo(svd, "Mag_SVD_10Rnd", 4, 100.0, 4);
        AddCargo(svd, "AmmoBox_762x54_20Rnd", 4, 100.0, 4);

        AddReward(pool, "NVGoggles", -1, 100.0, 2, "");
        AddReward(pool, "NVGHeadstrap", -1, 100.0, 1, "");
        AddReward(pool, "PlateCarrierVest", -1, 100.0, 1, "");
        AddReward(pool, "PlateCarrierPouches", -1, 100.0, 1, "");
        AddReward(pool, "PlateCarrierHolster", -1, 100.0, 1, "");
        AddReward(pool, "Mich2001Helmet", -1, 100.0, 1, "");
        AddReward(pool, "Rangefinder", -1, 100.0, 1, "");
        AddReward(pool, "Battery9V", 4, 100.0, 4, "");
        AddReward(pool, "TetracyclineAntibiotics", -1, 100.0, 2, "");
        AddReward(pool, "Morphine", 3, 100.0, 3, "");
        AddReward(pool, "Epinephrine", 3, 100.0, 3, "");
        AddReward(pool, "SalineBagIV", 3, 100.0, 3, "");
        AddReward(pool, "WeaponCleaningKit", 2, 100.0, 2, "");
        AddReward(pool, "DuctTape", 2, 100.0, 2, "");
        AddReward(pool, "NailBox", 5, 100.0, 5, "");
        AddReward(pool, "MetalPlate", 8, 100.0, 8, "");
        AddReward(pool, "CombinationLock", 2, 100.0, 2, "");

        AddReward(pool, "DeutschZKotHZ_BiohazardReader", -1, 100.0, 1, "");
        AddReward(pool, "DeutschZKotHZ_AccessCard", -1, 100.0, 2, "");
        AddReward(pool, "DeutschZKotHZ_ResearchDocument", -1, 100.0, 2, "");
        AddReward(pool, "DeutschZKotHZ_CommanderInsignia", -1, 100.0, 1, "");

        // V0.9.3 Operation/Convoy/GroundZero prep items. Missing optional classnames are skipped safely by the reward resolver.
        AddReward(pool, "DZ_EventToken", -1, 100.0, 3, "");
        AddReward(pool, "DZ_BossDogtag", -1, 100.0, 1, "");
        AddReward(pool, "DZ_RedZChip", -1, 100.0, 1, "");
        AddReward(pool, "DZ_RewardKey", -1, 100.0, 1, "");
        AddReward(pool, "DZ_SecureSSD", -1, 100.0, 1, "");
        AddReward(pool, "DZ_MilitaryLedger", -1, 100.0, 1, "");
        AddReward(pool, "DZ_HazardCanister", -1, 80.0, 1, "");
        AddReward(pool, "DZCV_EncryptedDataDrive", -1, 100.0, 1, "");
        AddReward(pool, "DZCV_ClassifiedIntel", -1, 100.0, 1, "");
        AddReward(pool, "DZ_ConvoyZ_Blackbox", -1, 70.0, 1, "");
        AddReward(pool, "DZ_ConvoyZ_DieselManifest", -1, 70.0, 1, "");
        AddReward(pool, "DZ_ConvoyZ_RadioKey", -1, 70.0, 1, "");
        AddReward(pool, "DZ_ConvoyZ_ArmorPlateBundle", -1, 60.0, 1, "");

        LootPools.Insert(pool);
    }


    protected void CreateKVM1TestPool()
    {
        DeutschZKotHZLootPool pool = new DeutschZKotHZLootPool();
        pool.PoolName = "TestVanillaCombat";
        pool.EditHint = "KVM1 vanilla test pool. All entries are vanilla-safe and set to 100 percent for reliable test runs.";
        pool.RewardMode = 1;
        pool.CrateClassName = "DeutschZKotHZ_RewardCrate";
        pool.CrateSpawnAtFlagpole = 1;
        pool.CrateSpawnDistanceFromFlagpole = 6.0;
        pool.CrateLifetimeSeconds = 3600;
        pool.DeleteCrateOnEventEnd = 0;

        DeutschZKotHZReward m4 = AddReward(pool, "M4A1", -1, 100.0, 1, "Mag_STANAG_60Rnd");
        AddAttachment(m4, "M4_PlasticHndgrd", -1, 100.0, 1);
        AddAttachment(m4, "M4_OEBttstck", -1, 100.0, 1);
        AddAttachment(m4, "ReflexOptic", -1, 100.0, 1);
        AddAttachment(m4, "M4_Suppressor", -1, 100.0, 1);
        AddCargo(m4, "Mag_STANAG_60Rnd", 3, 100.0, 3);
        AddCargo(m4, "AmmoBox_556x45_20Rnd", 2, 100.0, 2);

        DeutschZKotHZReward svd = AddReward(pool, "SVD", -1, 100.0, 1, "Mag_SVD_10Rnd");
        AddAttachment(svd, "PSO1Optic", -1, 100.0, 1);
        AddAttachment(svd, "AK_Suppressor", -1, 100.0, 1);
        AddCargo(svd, "Mag_SVD_10Rnd", 3, 100.0, 3);
        AddCargo(svd, "AmmoBox_762x54_20Rnd", 2, 100.0, 2);

        AddReward(pool, "TacticalBaconCan", 2, 100.0, 2, "");
        AddReward(pool, "SpaghettiCan", 2, 100.0, 2, "");
        AddReward(pool, "WaterBottle", 2, 100.0, 2, "");
        AddReward(pool, "Canteen", -1, 100.0, 1, "");
        AddReward(pool, "BandageDressing", 4, 100.0, 4, "");
        AddReward(pool, "Morphine", 2, 100.0, 2, "");
        AddReward(pool, "Epinephrine", 2, 100.0, 2, "");
        AddReward(pool, "TetracyclineAntibiotics", -1, 100.0, 1, "");
        AddReward(pool, "SalineBagIV", 2, 100.0, 2, "");
        AddReward(pool, "WeaponCleaningKit", -1, 100.0, 1, "");
        AddReward(pool, "LeatherSewingKit", -1, 100.0, 1, "");

        LootPools.Insert(pool);
    }

    protected void CreateDefaultPool()
    {
        DeutschZKotHZLootPool pool = new DeutschZKotHZLootPool();
        pool.PoolName = "Default";
        pool.EditHint = "Small vanilla fallback pool.";
        AddReward(pool, "NailBox", -1, 100.0, 1, "");
        AddReward(pool, "AmmoBox_556x45_20Rnd", -1, 80.0, 2, "");
        AddReward(pool, "BandageDressing", -1, 100.0, 4, "");
        AddReward(pool, "DeutschZKotHZ_ResearchDocument", -1, 35.0, 1, "");
        LootPools.Insert(pool);
    }

    protected void CreateDeutschZMilitaryPool()
    {
        DeutschZKotHZLootPool pool = new DeutschZKotHZLootPool();
        pool.PoolName = "MilitaryVanilla";
        pool.EditHint = "Vanilla-safe military reward pool. Replace or extend via DeutschZ JSON when custom weapon mods are loaded.";
        pool.CrateLifetimeSeconds = 3600;

        AddReward(pool, "M4A1", -1, 100.0, 1, "Mag_STANAG_30Rnd");
        AddReward(pool, "AKM", -1, 90.0, 1, "Mag_AKM_30Rnd");
        AddReward(pool, "FAL", -1, 70.0, 1, "Mag_FAL_20Rnd");
        AddReward(pool, "SVD", -1, 55.0, 1, "Mag_SVD_10Rnd");
        AddReward(pool, "Mag_STANAG_30Rnd", -1, 100.0, 4, "");
        AddReward(pool, "Mag_AKM_30Rnd", -1, 90.0, 4, "");
        AddReward(pool, "Mag_FAL_20Rnd", -1, 70.0, 3, "");
        AddReward(pool, "Mag_SVD_10Rnd", -1, 55.0, 3, "");
        AddReward(pool, "ACOGOptic", -1, 45.0, 1, "");
        AddReward(pool, "PSO1Optic", -1, 45.0, 1, "");
        AddReward(pool, "NVGoggles", -1, 35.0, 1, "");
        AddReward(pool, "PlateCarrierVest", -1, 45.0, 1, "");
        AddReward(pool, "PlateCarrierPouches", -1, 45.0, 1, "");
        AddReward(pool, "PlateCarrierHolster", -1, 45.0, 1, "");
        AddReward(pool, "AmmoBox_556x45_20Rnd", -1, 70.0, 2, "");
        AddReward(pool, "AmmoBox_762x39_20Rnd", -1, 70.0, 2, "");
        AddReward(pool, "AmmoBox_308Win_20Rnd", -1, 45.0, 2, "");
        AddReward(pool, "AmmoBox_762x54_20Rnd", -1, 45.0, 2, "");
        AddReward(pool, "NailBox", -1, 50.0, 2, "");
        AddReward(pool, "EpoxyPutty", -1, 55.0, 2, "");
        AddReward(pool, "WeaponCleaningKit", -1, 55.0, 2, "");
        AddReward(pool, "WeaponCleaningKit", -1, 20.0, 1, "");
        AddReward(pool, "LeatherSewingKit", -1, 45.0, 2, "");
        AddReward(pool, "DeutschZKotHZ_CommanderInsignia", -1, 15.0, 1, "");
        AddReward(pool, "DeutschZKotHZ_ResearchDocument", -1, 55.0, 2, "");

        LootPools.Insert(pool);
    }

    protected void CreateDeutschZBasebuildingPool()
    {
        DeutschZKotHZLootPool pool = new DeutschZKotHZLootPool();
        pool.PoolName = "Basebuilding";
        pool.EditHint = "Vanilla-safe building reward pool. Add BBP/RaG classnames manually when those mods are loaded.";
        pool.CrateLifetimeSeconds = 3600;

        AddReward(pool, "NailBox", -1, 100.0, 4, "");
        AddReward(pool, "WoodenPlank", -1, 100.0, 10, "");
        AddReward(pool, "MetalPlate", -1, 75.0, 6, "");
        AddReward(pool, "Hammer", -1, 70.0, 1, "");
        AddReward(pool, "Hatchet", -1, 70.0, 1, "");
        AddReward(pool, "Shovel", -1, 70.0, 1, "");
        AddReward(pool, "Pliers", -1, 70.0, 1, "");
        AddReward(pool, "Handsaw", -1, 70.0, 1, "");
        AddReward(pool, "MetalWire", -1, 60.0, 2, "");
        AddReward(pool, "CombinationLock", -1, 45.0, 1, "");
        AddReward(pool, "BarbedWire", -1, 45.0, 2, "");

        LootPools.Insert(pool);
    }

    protected DeutschZKotHZReward AddReward(DeutschZKotHZLootPool pool, string className, int quantity, float chance, int maxSpawnable, string magazineClassName)
    {
        DeutschZKotHZReward reward = new DeutschZKotHZReward();
        reward.ClassName = className;
        reward.Quantity = quantity;
        reward.SpawnChance = chance;
        reward.MaxSpawnable = maxSpawnable;
        reward.MagazineClassName = magazineClassName;
        pool.Rewards.Insert(reward);
        return reward;
    }

    protected void AddAlternative(DeutschZKotHZReward parent, string className)
    {
        if (!parent)
            return;

        if (!parent.AlternativeClassNames)
            parent.AlternativeClassNames = new array<string>;

        parent.AlternativeClassNames.Insert(className);
    }

    protected DeutschZKotHZReward AddAttachment(DeutschZKotHZReward parent, string className, int quantity, float chance, int maxSpawnable)
    {
        DeutschZKotHZReward reward = CreateNestedReward(className, quantity, chance, maxSpawnable);
        parent.AttachmentItems.Insert(reward);
        return reward;
    }

    protected DeutschZKotHZReward AddCargo(DeutschZKotHZReward parent, string className, int quantity, float chance, int maxSpawnable)
    {
        DeutschZKotHZReward reward = CreateNestedReward(className, quantity, chance, maxSpawnable);
        parent.CargoItems.Insert(reward);
        return reward;
    }

    protected DeutschZKotHZReward CreateNestedReward(string className, int quantity, float chance, int maxSpawnable)
    {
        DeutschZKotHZReward reward = new DeutschZKotHZReward();
        reward.ClassName = className;
        reward.Quantity = quantity;
        reward.SpawnChance = chance;
        reward.MaxSpawnable = maxSpawnable;
        reward.MagazineClassName = "";
        return reward;
    }
}
