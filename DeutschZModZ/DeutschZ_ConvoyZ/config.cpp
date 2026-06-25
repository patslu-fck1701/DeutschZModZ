/*
DeutschZ ModZ
Eigenstaendige Implementierung fuer DeutschZ.
Autor/Eigentuemer: Patrick Sluzalek / fck1701.
Projekt: DeutschZ.
Modul: DeutschZ_ConvoyZ.
Zweck der Datei: DayZ-Mod-Konfiguration, eigene DeutschZ-Klassen und Abhaengigkeiten deklarieren.
Quellen-/Konzeptnachweis: Eigene DeutschZ-Implementierung; DayZ/CF/Expansion werden nur als Laufzeit-Abhaengigkeit/API genutzt.
Keine direkte Codeuebernahme aus Drittquellen.
*/

class CfgPatches
{
    class DeutschZ_ConvoyZ
    {
        units[] = {"Land_HACKEDCRATE", "DZCV_ProtectedCase", "DZCV_AccessCard", "DZCV_CardReader", "DZCV_BlackboxCore", "DZCV_EncryptedDataDrive", "DZCV_ClassifiedIntel", "DZCV_SealedRewardChest", "DZ_ConvoyZ_Blackbox", "DZ_ConvoyZ_EncryptedDataModule", "DZ_ConvoyZ_SealedWeaponCase", "DZ_ConvoyZ_DieselManifest", "DZ_ConvoyZ_RadioKey", "DZ_ConvoyZ_ArmorPlateBundle", "DZCV_ConvoyBlackBox", "DZCV_BlackboxDeliveryNote", "DZCV_OperationLead", "DZCV_CrashSiteKeyFragment"};
        weapons[] = {};
        requiredVersion = 0.1;
        requiredAddons[] = {"DZ_Data", "DZ_Scripts", "DZ_Vehicles_Wheeled", "DZ_Gear_Containers", "DZ_Gear_Navigation", "DZ_Gear_Consumables", "DZ_Gear_Tools", "DeutschZ_Core"};
    };
};

class CfgMods
{
    class DeutschZ_ConvoyZ
    {
        dir = "DeutschZ_ConvoyZ";
        picture = "";
        action = "";
        hideName = 0;
        hidePicture = 1;
        name = "DeutschZ_ConvoyZ";
        credits = "DeutschZ";
        author = "DeutschZ";
        version = "0.9.4-fix45-core-event-lock";
        type = "mod";
        dependencies[] = {"Game", "World", "Mission"};
        class defs
        {
            class gameScriptModule
            {
                value = "";
                files[] = {"DeutschZ_ConvoyZ/scripts/3_Game", "scripts/3_Game"};
            };
            class worldScriptModule
            {
                value = "";
                files[] = {"DeutschZ_ConvoyZ/scripts/4_World", "scripts/4_World"};
            };
            class missionScriptModule
            {
                value = "";
                files[] = {"DeutschZ_ConvoyZ/scripts/5_Mission", "scripts/5_Mission"};
            };
        };
    };
};

class CfgVehicles
{
    class Inventory_Base;
    class PunchedCard;
    class ElectronicRepairKit;
    class GPSReceiver;
    class Paper;
    class SeaChest;
    class SmallProtectorCase;

    class HouseNoDestruct;

    class Land_HACKEDCRATE: HouseNoDestruct
    {
        scope = 2;
        displayName = "$STR_DZCONVOYZ_LAND_HACKEDCRATE_NAME";
        descriptionShort = "$STR_DZCONVOYZ_LAND_HACKEDCRATE_DESC";
        model = "DeutschZ_ConvoyZ/Assets/HackedCrate/Shed.p3d";
        hiddenSelections[] = {"camo"};
        hiddenSelectionsTextures[] = {"DeutschZ_ConvoyZ/Assets/Case/CardReader.paa"};
    };

    class DZCV_ProtectedCase: HouseNoDestruct
    {
        scope = 2;
        displayName = "$STR_DZCONVOYZ_DZCV_PROTECTEDCASE_NAME";
        descriptionShort = "$STR_DZCONVOYZ_DZCV_PROTECTEDCASE_DESC";
        model = "DeutschZ_ConvoyZ/Assets/Case/protector_case.p3d";
        hiddenSelections[] = {"camo"};
        hiddenSelectionsTextures[] = {"DeutschZ_ConvoyZ/Assets/Case/Case.paa"};
    };


    class DZCV_AccessCard: PunchedCard
    {
        scope = 2;
        displayName = "$STR_DZCONVOYZ_DZCV_ACCESSCARD_NAME";
        descriptionShort = "$STR_DZCONVOYZ_DZCV_ACCESSCARD_DESC";
        hiddenSelections[] = {"camo"};
        hiddenSelectionsTextures[] = {"DeutschZ_ConvoyZ/Assets/Case/AccesCard.paa"};
        itemSize[] = {1,1};
        weight = 25;
    };

    class DZCV_CardReader: ElectronicRepairKit
    {
        scope = 2;
        displayName = "$STR_DZCONVOYZ_DZCV_CARDREADER_NAME";
        descriptionShort = "$STR_DZCONVOYZ_DZCV_CARDREADER_DESC";
        hiddenSelections[] = {"camo"};
        hiddenSelectionsTextures[] = {"DeutschZ_ConvoyZ/Assets/Case/CardReader.paa"};
        itemSize[] = {2,2};
        weight = 450;
    };

    class DZCV_BlackboxCore: GPSReceiver
    {
        scope = 2;
        displayName = "$STR_DZCONVOYZ_DZCV_BLACKBOXCORE_NAME";
        descriptionShort = "$STR_DZCONVOYZ_DZCV_BLACKBOXCORE_DESC";
        hiddenSelections[] = {"camo"};
        hiddenSelectionsTextures[] = {"DeutschZ_ConvoyZ/Assets/Case/CardReader.paa"};
        itemSize[] = {2,2};
        weight = 750;
    };

    class DZCV_EncryptedDataDrive: GPSReceiver
    {
        scope = 2;
        displayName = "$STR_DZCONVOYZ_DZCV_ENCRYPTEDDATADRIVE_NAME";
        descriptionShort = "$STR_DZCONVOYZ_DZCV_ENCRYPTEDDATADRIVE_DESC";
        hiddenSelections[] = {"camo"};
        hiddenSelectionsTextures[] = {"DeutschZ_ConvoyZ/Assets/Case/AccesCard.paa"};
        itemSize[] = {1,2};
        weight = 120;
    };

    class DZCV_ClassifiedIntel: Paper
    {
        scope = 2;
        displayName = "$STR_DZCONVOYZ_DZCV_CLASSIFIEDINTEL_NAME";
        descriptionShort = "$STR_DZCONVOYZ_DZCV_CLASSIFIEDINTEL_DESC";
        itemSize[] = {1,2};
        weight = 30;
    };

    class DZCV_SealedRewardChest: SeaChest
    {
        scope = 2;
        displayName = "$STR_DZCONVOYZ_DZCV_SEALEDREWARDCHEST_NAME";
        descriptionShort = "$STR_DZCONVOYZ_DZCV_SEALEDREWARDCHEST_DESC";
        hiddenSelections[] = {"camoGround"};
        hiddenSelectionsTextures[] = {"DeutschZ_ConvoyZ/Assets/Case/Seachest.paa"};
        itemSize[] = {10, 10};
        itemsCargoSize[] = {10, 50};
        weight = 15000;
        class Cargo
        {
            itemsCargoSize[] = {10, 50};
            openable = 0;
            allowOwnedCargoManipulation = 1;
        };
    };

    class DZ_ConvoyZ_Blackbox: GPSReceiver
    {
        scope = 2;
        displayName = "$STR_DZCONVOYZ_DZ_CONVOYZ_BLACKBOX_NAME";
        descriptionShort = "$STR_DZCONVOYZ_DZ_CONVOYZ_BLACKBOX_DESC";
        hiddenSelections[] = {"camo"};
        hiddenSelectionsTextures[] = {"DeutschZ_ConvoyZ/Assets/Case/CardReader.paa"};
        itemSize[] = {2, 2};
        weight = 900;
    };

    class DZ_ConvoyZ_EncryptedDataModule: GPSReceiver
    {
        scope = 2;
        displayName = "$STR_DZCONVOYZ_DZ_CONVOYZ_ENCRYPTEDDATAMODULE_NAME";
        descriptionShort = "$STR_DZCONVOYZ_DZ_CONVOYZ_ENCRYPTEDDATAMODULE_DESC";
        hiddenSelections[] = {"camo"};
        hiddenSelectionsTextures[] = {"DeutschZ_ConvoyZ/Assets/Case/CardReader.paa"};
        itemSize[] = {1, 2};
        weight = 180;
    };

    class DZ_ConvoyZ_SealedWeaponCase: SmallProtectorCase
    {
        scope = 2;
        displayName = "$STR_DZCONVOYZ_DZ_CONVOYZ_SEALEDWEAPONCASE_NAME";
        descriptionShort = "$STR_DZCONVOYZ_DZ_CONVOYZ_SEALEDWEAPONCASE_DESC";
        model = "DeutschZ_ConvoyZ/Assets/Case/protector_case.p3d";
        hiddenSelections[] = {"camo"};
        hiddenSelectionsTextures[] = {"DeutschZ_ConvoyZ/Assets/Case/Case.paa"};
        itemSize[] = {4, 3};
        weight = 3200;
        canBeSplit = 0;
    };

    class DZ_ConvoyZ_DieselManifest: Paper
    {
        scope = 2;
        displayName = "$STR_DZCONVOYZ_DZ_CONVOYZ_DIESELMANIFEST_NAME";
        descriptionShort = "$STR_DZCONVOYZ_DZ_CONVOYZ_DIESELMANIFEST_DESC";
        itemSize[] = {1, 2};
        weight = 25;
    };

    class DZ_ConvoyZ_RadioKey: PunchedCard
    {
        scope = 2;
        displayName = "$STR_DZCONVOYZ_DZ_CONVOYZ_RADIOKEY_NAME";
        descriptionShort = "$STR_DZCONVOYZ_DZ_CONVOYZ_RADIOKEY_DESC";
        hiddenSelections[] = {"camo"};
        hiddenSelectionsTextures[] = {"DeutschZ_ConvoyZ/Assets/Case/AccesCard.paa"};
        itemSize[] = {1, 1};
        weight = 35;
    };

    class DZ_ConvoyZ_ArmorPlateBundle: SmallProtectorCase
    {
        scope = 2;
        displayName = "$STR_DZCONVOYZ_DZ_CONVOYZ_ARMORPLATEBUNDLE_NAME";
        descriptionShort = "$STR_DZCONVOYZ_DZ_CONVOYZ_ARMORPLATEBUNDLE_DESC";
        model = "DeutschZ_ConvoyZ/Assets/Case/protector_case.p3d";
        hiddenSelections[] = {"camo"};
        hiddenSelectionsTextures[] = {"DeutschZ_ConvoyZ/Assets/Case/Case.paa"};
        itemSize[] = {3, 3};
        weight = 6500;
        canBeSplit = 0;
    };


    class DZCV_ConvoyBlackBox: GPSReceiver
    {
        scope = 2;
        displayName = "$STR_DZCONVOYZ_DZCV_CONVOYBLACKBOX_NAME";
        descriptionShort = "$STR_DZCONVOYZ_DZCV_CONVOYBLACKBOX_DESC";
        hiddenSelections[] = {"camo"};
        hiddenSelectionsTextures[] = {"DeutschZ_ConvoyZ/Assets/Case/CardReader.paa"};
        itemSize[] = {2, 2};
        weight = 900;
    };

    class DZCV_BlackboxDeliveryNote: Paper
    {
        scope = 2;
        displayName = "$STR_DZCONVOYZ_DZCV_BLACKBOXDELIVERYNOTE_NAME";
        descriptionShort = "$STR_DZCONVOYZ_DZCV_BLACKBOXDELIVERYNOTE_DESC";
        itemSize[] = {1, 1};
        weight = 10;
    };

    class DZCV_OperationLead: PunchedCard
    {
        scope = 2;
        displayName = "$STR_DZCONVOYZ_DZCV_OPERATIONLEAD_NAME";
        descriptionShort = "$STR_DZCONVOYZ_DZCV_OPERATIONLEAD_DESC";
        hiddenSelections[] = {"camo"};
        hiddenSelectionsTextures[] = {"DeutschZ_ConvoyZ/Assets/Case/AccesCard.paa"};
        itemSize[] = {1, 1};
        weight = 35;
    };

    class DZCV_CrashSiteKeyFragment: PunchedCard
    {
        scope = 2;
        displayName = "$STR_DZCONVOYZ_DZCV_CRASHSITEKEYFRAGMENT_NAME";
        descriptionShort = "$STR_DZCONVOYZ_DZCV_CRASHSITEKEYFRAGMENT_DESC";
        hiddenSelections[] = {"camo"};
        hiddenSelectionsTextures[] = {"DeutschZ_ConvoyZ/Assets/Case/AccesCard.paa"};
        itemSize[] = {1, 1};
        weight = 25;
    };

};