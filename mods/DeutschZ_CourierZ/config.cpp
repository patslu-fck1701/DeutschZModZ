/*
DeutschZ ModZ
Eigenstaendige Implementierung fuer DeutschZ.
Autor/Eigentuemer: Patrick Sluzalek / fck1701.
Projekt: DeutschZ.
Modul: DeutschZ_CourierZ.
Zweck: Operation Aktenkoffer - serverautoritaeres Kurier-Event.
No-Copy-Bestaetigung: Kein Code, keine Assets und keine Configs aus fremden Mods kopiert.
*/

class CfgPatches
{
    class DeutschZ_CourierZ
    {
        units[] = {"DZCR_SealedLetter", "DZCR_ClassifiedDocument", "DZCR_EncryptedDataDrive", "DZCR_SecretOrder", "DZCR_Aktenkoffer", "DZCR_RewardChest", "DZCR_SealedCourierCase", "DZCR_CourierPackage", "DZCR_DeliveryStamp", "DZCR_CipherDocument", "DZ_CourierZ_Briefcase", "DZ_CourierZ_SealedCourierFolder", "DZ_CourierZ_SecretDeliveryContract", "DZ_CourierZ_GPSTracker", "DZ_CourierZ_CourierSeal", "DZ_CourierZ_BlackMarketReceipt"};
        weapons[] = {};
        requiredVersion = 0.1;
        requiredAddons[] = {"DZ_Data", "DZ_Scripts", "DZ_Gear_Containers", "DZ_Gear_Navigation", "DZ_Gear_Consumables", "DeutschZ_Core"};
    };
};

class CfgMods
{
    class DeutschZ_CourierZ
    {
        dir = "DeutschZ_CourierZ";
        picture = "";
        action = "";
        hideName = 0;
        hidePicture = 1;
        name = "DeutschZ CourierZ - Operation Aktenkoffer";
        credits = "Owner: Patrick Sluzalek / Player: fck1701 / Server: DeutschZ";
        author = "Patrick Sluzalek / fck1701";
        authorID = "0";
        version = "0.9.4-campaign-chain-test";
        extra = 0;
        type = "mod";
        dependencies[] = {"Game", "World", "Mission"};

        class defs
        {
            class gameScriptModule
            {
                value = "";
                files[] = {"DeutschZ_CourierZ/scripts/3_Game", "scripts/3_Game"};
            };
            class worldScriptModule
            {
                value = "";
                files[] = {"DeutschZ_CourierZ/scripts/4_World", "scripts/4_World"};
            };
            class missionScriptModule
            {
                value = "";
                files[] = {"DeutschZ_CourierZ/scripts/5_Mission", "scripts/5_Mission"};
            };
        };
    };
};

class CfgVehicles
{
    class Inventory_Base;
    class Paper;
    class GPSReceiver;
    class SmallProtectorCase;
    class SeaChest;

    class DZCR_SealedLetter: Paper
    {
        scope = 2;
        displayName = "$STR_DZCOURIERZ_DZCR_SEALEDLETTER_NAME";
        descriptionShort = "$STR_DZCOURIERZ_DZCR_SEALEDLETTER_DESC";
        itemSize[] = {1, 1};
        weight = 20;
    };

    class DZCR_ClassifiedDocument: Paper
    {
        scope = 2;
        displayName = "$STR_DZCOURIERZ_DZCR_CLASSIFIEDDOCUMENT_NAME";
        descriptionShort = "$STR_DZCOURIERZ_DZCR_CLASSIFIEDDOCUMENT_DESC";
        itemSize[] = {1, 2};
        weight = 30;
    };

    class DZCR_SecretOrder: Paper
    {
        scope = 2;
        displayName = "$STR_DZCOURIERZ_DZCR_SECRETORDER_NAME";
        descriptionShort = "$STR_DZCOURIERZ_DZCR_SECRETORDER_DESC";
        itemSize[] = {1, 2};
        weight = 30;
    };

    class DZCR_EncryptedDataDrive: GPSReceiver
    {
        scope = 2;
        displayName = "$STR_DZCOURIERZ_DZCR_ENCRYPTEDDATADRIVE_NAME";
        descriptionShort = "$STR_DZCOURIERZ_DZCR_ENCRYPTEDDATADRIVE_DESC";
        itemSize[] = {1, 2};
        weight = 150;
    };

    class DZCR_Aktenkoffer: SmallProtectorCase
    {
        scope = 2;
        displayName = "$STR_DZCOURIERZ_DZCR_AKTENKOFFER_NAME";
        descriptionShort = "$STR_DZCOURIERZ_DZCR_AKTENKOFFER_DESC";
        model = "DeutschZ_CourierZ/Assets/Case/protector_case.p3d";
        hiddenSelections[] = {"camo"};
        hiddenSelectionsTextures[] = {"DeutschZ_CourierZ/Assets/Case/Case.paa"};
        itemSize[] = {4, 3};
        weight = 2500;
        canBeSplit = 0;
        quantityBar = 0;
    };

    class DZCR_SealedCourierCase: DZCR_Aktenkoffer
    {
        scope = 2;
        displayName = "$STR_DZCOURIERZ_DZCR_SEALEDCOURIERCASE_NAME";
        descriptionShort = "$STR_DZCOURIERZ_DZCR_SEALEDCOURIERCASE_DESC";
    };

    class DZCR_CourierPackage: SmallProtectorCase
    {
        scope = 2;
        displayName = "$STR_DZCOURIERZ_DZCR_COURIERPACKAGE_NAME";
        descriptionShort = "$STR_DZCOURIERZ_DZCR_COURIERPACKAGE_DESC";
        model = "DeutschZ_CourierZ/Assets/Case/protector_case.p3d";
        hiddenSelections[] = {"camo"};
        hiddenSelectionsTextures[] = {"DeutschZ_CourierZ/Assets/Case/Case.paa"};
        itemSize[] = {3, 2};
        weight = 1800;
        canBeSplit = 0;
    };

    class DZCR_DeliveryStamp: Paper
    {
        scope = 2;
        displayName = "$STR_DZCOURIERZ_DZCR_DELIVERYSTAMP_NAME";
        descriptionShort = "$STR_DZCOURIERZ_DZCR_DELIVERYSTAMP_DESC";
        itemSize[] = {1, 1};
        weight = 10;
    };

    class DZCR_CipherDocument: Paper
    {
        scope = 2;
        displayName = "$STR_DZCOURIERZ_DZCR_CIPHERDOCUMENT_NAME";
        descriptionShort = "$STR_DZCOURIERZ_DZCR_CIPHERDOCUMENT_DESC";
        itemSize[] = {1, 2};
        weight = 25;
    };

    class DZCR_RewardChest: SeaChest
    {
        scope = 2;
        displayName = "$STR_DZCOURIERZ_DZCR_REWARDCHEST_NAME";
        descriptionShort = "$STR_DZCOURIERZ_DZCR_REWARDCHEST_DESC";
        hiddenSelections[] = {"camoGround"};
        hiddenSelectionsTextures[] = {"DeutschZ_CourierZ/Assets/Case/Seachest.paa"};
        itemSize[] = {10, 10};
        itemsCargoSize[] = {10, 50};
        weight = 15000;
        canBeDigged = 0;
        class Cargo
        {
            itemsCargoSize[] = {10, 50};
            openable = 0;
            allowOwnedCargoManipulation = 1;
        };
    };

    class DZ_CourierZ_Briefcase: SmallProtectorCase
    {
        scope = 2;
        displayName = "$STR_DZCOURIERZ_DZ_COURIERZ_BRIEFCASE_NAME";
        descriptionShort = "$STR_DZCOURIERZ_DZ_COURIERZ_BRIEFCASE_DESC";
        model = "DeutschZ_CourierZ/Assets/Case/protector_case.p3d";
        hiddenSelections[] = {"camo"};
        hiddenSelectionsTextures[] = {"DeutschZ_CourierZ/Assets/Case/Case.paa"};
        itemSize[] = {4, 3};
        weight = 2500;
        canBeSplit = 0;
    };

    class DZ_CourierZ_SealedCourierFolder: Paper
    {
        scope = 2;
        displayName = "$STR_DZCOURIERZ_DZ_COURIERZ_SEALEDCOURIERFOLDER_NAME";
        descriptionShort = "$STR_DZCOURIERZ_DZ_COURIERZ_SEALEDCOURIERFOLDER_DESC";
        itemSize[] = {1, 2};
        weight = 35;
    };

    class DZ_CourierZ_SecretDeliveryContract: Paper
    {
        scope = 2;
        displayName = "$STR_DZCOURIERZ_DZ_COURIERZ_SECRETDELIVERYCONTRACT_NAME";
        descriptionShort = "$STR_DZCOURIERZ_DZ_COURIERZ_SECRETDELIVERYCONTRACT_DESC";
        itemSize[] = {1, 2};
        weight = 30;
    };

    class DZ_CourierZ_GPSTracker: GPSReceiver
    {
        scope = 2;
        displayName = "$STR_DZCOURIERZ_DZ_COURIERZ_GPSTRACKER_NAME";
        descriptionShort = "$STR_DZCOURIERZ_DZ_COURIERZ_GPSTRACKER_DESC";
        itemSize[] = {1, 2};
        weight = 160;
    };

    class DZ_CourierZ_CourierSeal: Paper
    {
        scope = 2;
        displayName = "$STR_DZCOURIERZ_DZ_COURIERZ_COURIERSEAL_NAME";
        descriptionShort = "$STR_DZCOURIERZ_DZ_COURIERZ_COURIERSEAL_DESC";
        itemSize[] = {1, 1};
        weight = 15;
    };

    class DZ_CourierZ_BlackMarketReceipt: Paper
    {
        scope = 2;
        displayName = "$STR_DZCOURIERZ_DZ_COURIERZ_BLACKMARKETRECEIPT_NAME";
        descriptionShort = "$STR_DZCOURIERZ_DZ_COURIERZ_BLACKMARKETRECEIPT_DESC";
        itemSize[] = {1, 2};
        weight = 20;
    };
};
