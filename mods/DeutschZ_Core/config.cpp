class CfgPatches
{
    class DeutschZ_Core
    {
        units[] = {"DZ_EventToken", "DZ_BossDogtag", "DZ_RedZChip", "DZ_BrokenTransmitter", "DZ_BloodSample", "DZ_ContainmentSeal", "DZ_TacticalCase", "DZ_RewardKey", "DZ_SupplyVoucher", "DZ_HazardCanister", "DZ_MilitaryLedger", "DZ_SecureSSD", "DZ_FieldNote", "DZ_AccessFuse", "DZ_SignalBattery", "DZ_RadioCrystal", "DZ_EventCore", "DZ_RedSmokeBeacon", "DZOP_Keycard_ConvoyAlpha", "DZOP_ConvoyLeadNote", "DZOP_TreasureMapFragment_A", "DZOP_DamagedCardReader", "DZOP_DecodedKeycard", "DZOP_OperationTreasureMap", "DZOP_TreasureMapFragment_B", "DZOP_CipherFragment_Courier", "DZOP_RouteNote_Courier", "DZOP_TechnicalFragment_GroundZero", "DZOP_SignalFragment_KotHZ", "DZOP_BurnedNote", "DZOP_DestroyedBlackBox", "DZOP_EncryptedSignalCore"};
        weapons[] = {};
        requiredVersion = 0.1;
        requiredAddons[] = {"DZ_Data", "DZ_Scripts", "DZ_Gear_Containers", "DZ_Gear_Navigation", "DZ_Gear_Consumables", "DZ_Gear_Medical", "DZ_Gear_Tools"};
    };
};

class CfgMods
{
    class DeutschZ_Core
    {
        dir = "DeutschZ_Core";
        name = "DeutschZ Core";
        author = "Patrick Sluzalek / fck1701";
        type = "mod";
        dependencies[] = {"Game", "World", "Mission"};
        class defs
        {
            class gameScriptModule
            {
                value = "";
                files[] = {"DeutschZ_Core/scripts/3_Game", "scripts/3_Game"};
            };
            class worldScriptModule
            {
                value = "";
                files[] = {"DeutschZ_Core/scripts/4_World", "scripts/4_World"};
            };
            class missionScriptModule
            {
                value = "";
                files[] = {"DeutschZ_Core/scripts/5_Mission", "scripts/5_Mission"};
            };
        };
    };
};


class CfgVehicles
{
    class Paper;
    class PunchedCard;
    class GPSReceiver;
    class SmallProtectorCase;
    class Battery9V;
    class BloodTestKit;
    class GasMask_Filter;
    class Inventory_Base;
    class ElectronicRepairKit;

    class DZ_EventToken: PunchedCard
    {
        scope = 2;
        displayName = "$STR_DZCORE_DZ_EVENTTOKEN_NAME";
        descriptionShort = "$STR_DZCORE_DZ_EVENTTOKEN_DESC";
        itemSize[] = {1, 1};
        weight = 20;
    };

    class DZ_BossDogtag: PunchedCard
    {
        scope = 2;
        displayName = "$STR_DZCORE_DZ_BOSSDOGTAG_NAME";
        descriptionShort = "$STR_DZCORE_DZ_BOSSDOGTAG_DESC";
        itemSize[] = {1, 1};
        weight = 30;
    };

    class DZ_RedZChip: GPSReceiver
    {
        scope = 2;
        displayName = "$STR_DZCORE_DZ_REDZCHIP_NAME";
        descriptionShort = "$STR_DZCORE_DZ_REDZCHIP_DESC";
        itemSize[] = {1, 1};
        weight = 60;
    };

    class DZ_BrokenTransmitter: Inventory_Base
    {
        scope = 2;
        displayName = "$STR_DZCORE_DZ_BROKENTRANSMITTER_NAME";
        descriptionShort = "$STR_DZCORE_DZ_BROKENTRANSMITTER_DESC";
        itemSize[] = {2, 2};
        weight = 550;
    };

    class DZ_BloodSample: BloodTestKit
    {
        scope = 2;
        displayName = "$STR_DZCORE_DZ_BLOODSAMPLE_NAME";
        descriptionShort = "$STR_DZCORE_DZ_BLOODSAMPLE_DESC";
        itemSize[] = {1, 1};
        weight = 120;
    };

    class DZ_ContainmentSeal: GasMask_Filter
    {
        scope = 2;
        displayName = "$STR_DZCORE_DZ_CONTAINMENTSEAL_NAME";
        descriptionShort = "$STR_DZCORE_DZ_CONTAINMENTSEAL_DESC";
        itemSize[] = {1, 2};
        weight = 180;
    };

    class DZ_TacticalCase: SmallProtectorCase
    {
        scope = 2;
        displayName = "$STR_DZCORE_DZ_TACTICALCASE_NAME";
        descriptionShort = "$STR_DZCORE_DZ_TACTICALCASE_DESC";
        itemSize[] = {4, 3};
        weight = 2600;
        canBeSplit = 0;
    };

    class DZ_RewardKey: PunchedCard
    {
        scope = 2;
        displayName = "$STR_DZCORE_DZ_REWARDKEY_NAME";
        descriptionShort = "$STR_DZCORE_DZ_REWARDKEY_DESC";
        itemSize[] = {1, 1};
        weight = 15;
    };

    class DZ_SupplyVoucher: Paper
    {
        scope = 2;
        displayName = "$STR_DZCORE_DZ_SUPPLYVOUCHER_NAME";
        descriptionShort = "$STR_DZCORE_DZ_SUPPLYVOUCHER_DESC";
        itemSize[] = {1, 2};
        weight = 20;
    };

    class DZ_HazardCanister: GasMask_Filter
    {
        scope = 2;
        displayName = "$STR_DZCORE_DZ_HAZARDCANISTER_NAME";
        descriptionShort = "$STR_DZCORE_DZ_HAZARDCANISTER_DESC";
        itemSize[] = {2, 2};
        weight = 900;
    };

    class DZ_MilitaryLedger: Paper
    {
        scope = 2;
        displayName = "$STR_DZCORE_DZ_MILITARYLEDGER_NAME";
        descriptionShort = "$STR_DZCORE_DZ_MILITARYLEDGER_DESC";
        itemSize[] = {1, 2};
        weight = 35;
    };

    class DZ_SecureSSD: GPSReceiver
    {
        scope = 2;
        displayName = "$STR_DZCORE_DZ_SECURESSD_NAME";
        descriptionShort = "$STR_DZCORE_DZ_SECURESSD_DESC";
        itemSize[] = {1, 1};
        weight = 80;
    };

    class DZ_FieldNote: Paper
    {
        scope = 2;
        displayName = "$STR_DZCORE_DZ_FIELDNOTE_NAME";
        descriptionShort = "$STR_DZCORE_DZ_FIELDNOTE_DESC";
        itemSize[] = {1, 1};
        weight = 10;
    };

    class DZ_AccessFuse: ElectronicRepairKit
    {
        scope = 2;
        displayName = "$STR_DZCORE_DZ_ACCESSFUSE_NAME";
        descriptionShort = "$STR_DZCORE_DZ_ACCESSFUSE_DESC";
        itemSize[] = {1, 2};
        weight = 180;
    };

    class DZ_SignalBattery: Battery9V
    {
        scope = 2;
        displayName = "$STR_DZCORE_DZ_SIGNALBATTERY_NAME";
        descriptionShort = "$STR_DZCORE_DZ_SIGNALBATTERY_DESC";
        itemSize[] = {1, 1};
        weight = 70;
    };

    class DZ_RadioCrystal: GPSReceiver
    {
        scope = 2;
        displayName = "$STR_DZCORE_DZ_RADIOCRYSTAL_NAME";
        descriptionShort = "$STR_DZCORE_DZ_RADIOCRYSTAL_DESC";
        itemSize[] = {1, 1};
        weight = 45;
    };

    class DZ_EventCore: GPSReceiver
    {
        scope = 2;
        displayName = "$STR_DZCORE_DZ_EVENTCORE_NAME";
        descriptionShort = "$STR_DZCORE_DZ_EVENTCORE_DESC";
        itemSize[] = {2, 2};
        weight = 800;
    };

    class DZ_RedSmokeBeacon: Inventory_Base
    {
        scope = 2;
        displayName = "$STR_DZCORE_DZ_REDSMOKEBEACON_NAME";
        descriptionShort = "$STR_DZCORE_DZ_REDSMOKEBEACON_DESC";
        itemSize[] = {2, 2};
        weight = 650;
    };

    class DZOP_Keycard_ConvoyAlpha: PunchedCard
    {
        scope = 2;
        displayName = "$STR_DZCORE_DZOP_KEYCARD_CONVOYALPHA_NAME";
        descriptionShort = "$STR_DZCORE_DZOP_KEYCARD_CONVOYALPHA_DESC";
        itemSize[] = {1, 1};
        weight = 35;
    };

    class DZOP_ConvoyLeadNote: Paper
    {
        scope = 2;
        displayName = "$STR_DZCORE_DZOP_CONVOYLEADNOTE_NAME";
        descriptionShort = "$STR_DZCORE_DZOP_CONVOYLEADNOTE_DESC";
        itemSize[] = {1, 1};
        weight = 10;
    };

    class DZOP_TreasureMapFragment_A: Paper
    {
        scope = 2;
        displayName = "$STR_DZCORE_DZOP_TREASUREMAPFRAGMENT_A_NAME";
        descriptionShort = "$STR_DZCORE_DZOP_TREASUREMAPFRAGMENT_A_DESC";
        itemSize[] = {1, 2};
        weight = 20;
    };

    class DZOP_DamagedCardReader: ElectronicRepairKit
    {
        scope = 2;
        displayName = "$STR_DZCORE_DZOP_DAMAGEDCARDREADER_NAME";
        descriptionShort = "$STR_DZCORE_DZOP_DAMAGEDCARDREADER_DESC";
        itemSize[] = {2, 2};
        weight = 420;
    };

    class DZOP_DecodedKeycard: PunchedCard
    {
        scope = 2;
        displayName = "$STR_DZCORE_DZOP_DECODEDKEYCARD_NAME";
        descriptionShort = "$STR_DZCORE_DZOP_DECODEDKEYCARD_DESC";
        itemSize[] = {1, 1};
        weight = 35;
    };

    class DZOP_OperationTreasureMap: Paper
    {
        scope = 2;
        displayName = "$STR_DZCORE_DZOP_OPERATIONTREASUREMAP_NAME";
        descriptionShort = "$STR_DZCORE_DZOP_OPERATIONTREASUREMAP_DESC";
        itemSize[] = {2, 2};
        weight = 30;
    };

    class DZOP_TreasureMapFragment_B: Paper
    {
        scope = 2;
        displayName = "$STR_DZCORE_DZOP_TREASUREMAPFRAGMENT_B_NAME";
        descriptionShort = "$STR_DZCORE_DZOP_TREASUREMAPFRAGMENT_B_DESC";
        itemSize[] = {1, 2};
        weight = 15;
    };

    class DZOP_CipherFragment_Courier: Paper
    {
        scope = 2;
        displayName = "$STR_DZCORE_DZOP_CIPHERFRAGMENT_COURIER_NAME";
        descriptionShort = "$STR_DZCORE_DZOP_CIPHERFRAGMENT_COURIER_DESC";
        itemSize[] = {1, 1};
        weight = 10;
    };

    class DZOP_RouteNote_Courier: Paper
    {
        scope = 2;
        displayName = "$STR_DZCORE_DZOP_ROUTENOTE_COURIER_NAME";
        descriptionShort = "$STR_DZCORE_DZOP_ROUTENOTE_COURIER_DESC";
        itemSize[] = {1, 1};
        weight = 10;
    };

    class DZOP_TechnicalFragment_GroundZero: ElectronicRepairKit
    {
        scope = 2;
        displayName = "$STR_DZCORE_DZOP_TECHNICALFRAGMENT_GROUNDZERO_NAME";
        descriptionShort = "$STR_DZCORE_DZOP_TECHNICALFRAGMENT_GROUNDZERO_DESC";
        itemSize[] = {1, 2};
        weight = 220;
    };

    class DZOP_SignalFragment_KotHZ: GPSReceiver
    {
        scope = 2;
        displayName = "$STR_DZCORE_DZOP_SIGNALFRAGMENT_KOTHZ_NAME";
        descriptionShort = "$STR_DZCORE_DZOP_SIGNALFRAGMENT_KOTHZ_DESC";
        itemSize[] = {1, 1};
        weight = 80;
    };

    class DZOP_BurnedNote: Paper
    {
        scope = 2;
        displayName = "$STR_DZCORE_DZOP_BURNEDNOTE_NAME";
        descriptionShort = "$STR_DZCORE_DZOP_BURNEDNOTE_DESC";
        itemSize[] = {1, 1};
        weight = 5;
    };

    class DZOP_DestroyedBlackBox: GPSReceiver
    {
        scope = 2;
        displayName = "$STR_DZCORE_DZOP_DESTROYEDBLACKBOX_NAME";
        descriptionShort = "$STR_DZCORE_DZOP_DESTROYEDBLACKBOX_DESC";
        itemSize[] = {2, 2};
        weight = 900;
    };

    class DZOP_EncryptedSignalCore: GPSReceiver
    {
        scope = 2;
        displayName = "$STR_DZCORE_DZOP_ENCRYPTEDSIGNALCORE_NAME";
        descriptionShort = "$STR_DZCORE_DZOP_ENCRYPTEDSIGNALCORE_DESC";
        itemSize[] = {2, 2};
        weight = 700;
    };

};
