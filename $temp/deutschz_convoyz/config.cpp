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
        units[] = {"Land_HACKEDCRATE", "DZCV_ProtectedCase", "DZCV_AccessCard", "DZCV_CardReader", "DZCV_BlackboxCore", "DZCV_EncryptedDataDrive", "DZCV_ClassifiedIntel", "DZCV_SealedRewardChest", "DZ_ConvoyZ_Blackbox", "DZ_ConvoyZ_EncryptedDataModule", "DZ_ConvoyZ_SealedWeaponCase", "DZ_ConvoyZ_DieselManifest", "DZ_ConvoyZ_RadioKey", "DZ_ConvoyZ_ArmorPlateBundle"};
        weapons[] = {};
        requiredVersion = 0.1;
        requiredAddons[] = {"DZ_Data", "DZ_Scripts", "DZ_Vehicles_Wheeled", "DZ_Gear_Containers", "DZ_Gear_Navigation", "DZ_Gear_Consumables", "DZ_Gear_Tools", "DeutschZ_Core", "DeutschZ_ExpansionBridge"};
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
        version = "0.1.7-fix45-event-items";
        type = "mod";
        dependencies[] = {"Game", "World", "Mission"};
        class defs
        {
            class gameScriptModule
            {
                value = "";
                files[] = {"DeutschZ_ConvoyZ/scripts/3_Game"};
            };
            class worldScriptModule
            {
                value = "";
                files[] = {"DeutschZ_ConvoyZ/scripts/4_World"};
            };
            class missionScriptModule
            {
                value = "";
                files[] = {"DeutschZ_ConvoyZ/scripts/5_Mission"};
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
        displayName = "Top Secret Blackbox Terminal";
        descriptionShort = "DeutschZ_ConvoyZ hackable blackbox terminal.";
        model = "DeutschZ_ConvoyZ/Assets/HackedCrate/Shed.p3d";
        hiddenSelections[] = {"camo"};
        hiddenSelectionsTextures[] = {"DeutschZ_ConvoyZ/Assets/Case/CardReader.paa"};
    };

    class DZCV_ProtectedCase: HouseNoDestruct
    {
        scope = 2;
        displayName = "Classified Intelligence Case";
        descriptionShort = "A protected military data case recovered from a classified convoy crash.";
        model = "DeutschZ_ConvoyZ/Assets/Case/protector_case.p3d";
        hiddenSelections[] = {"camo"};
        hiddenSelectionsTextures[] = {"DeutschZ_ConvoyZ/Assets/Case/Case.paa"};
    };


    class DZCV_AccessCard: PunchedCard
    {
        scope = 2;
        displayName = "DeutschZ Convoy Access Card";
        descriptionShort = "Encrypted DeutschZ military convoy access card. Rare event key item.";
        hiddenSelections[] = {"camo"};
        hiddenSelectionsTextures[] = {"DeutschZ_ConvoyZ/Assets/Case/AccesCard.paa"};
        itemSize[] = {1,1};
        weight = 25;
    };

    class DZCV_CardReader: ElectronicRepairKit
    {
        scope = 2;
        displayName = "DeutschZ Blackbox Card Reader";
        descriptionShort = "Portable card reader for recovered convoy blackbox data.";
        hiddenSelections[] = {"camo"};
        hiddenSelectionsTextures[] = {"DeutschZ_ConvoyZ/Assets/Case/CardReader.paa"};
        itemSize[] = {2,2};
        weight = 450;
    };

    class DZCV_BlackboxCore: GPSReceiver
    {
        scope = 2;
        displayName = "DeutschZ Blackbox Core";
        descriptionShort = "Extremely valuable encrypted military blackbox core recovered from a top-secret convoy.";
        hiddenSelections[] = {"camo"};
        hiddenSelectionsTextures[] = {"DeutschZ_ConvoyZ/Assets/Case/CardReader.paa"};
        itemSize[] = {2,2};
        weight = 750;
    };

    class DZCV_EncryptedDataDrive: GPSReceiver
    {
        scope = 2;
        displayName = "DeutschZ Encrypted Data Drive";
        descriptionShort = "Encrypted tactical data drive. Valuable to traders and future mission chains.";
        hiddenSelections[] = {"camo"};
        hiddenSelectionsTextures[] = {"DeutschZ_ConvoyZ/Assets/Case/AccesCard.paa"};
        itemSize[] = {1,2};
        weight = 120;
    };

    class DZCV_ClassifiedIntel: Paper
    {
        scope = 2;
        displayName = "DeutschZ Classified Convoy Intel";
        descriptionShort = "Classified convoy intelligence documents. High-value event loot.";
        itemSize[] = {1,2};
        weight = 30;
    };

    class DZCV_SealedRewardChest: SeaChest
    {
        scope = 2;
        displayName = "DeutschZ ConvoyZ Rewardkiste";
        descriptionShort = "Versiegelte DeutschZ ConvoyZ Rewardkiste mit 500 Cargo-Slots.";
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
        displayName = "DeutschZ ConvoyZ Blackbox";
        descriptionShort = "Geborgene Blackbox eines DeutschZ Convoys. Event-only Reward-, Hack- oder Traderitem.";
        hiddenSelections[] = {"camo"};
        hiddenSelectionsTextures[] = {"DeutschZ_ConvoyZ/Assets/Case/CardReader.paa"};
        itemSize[] = {2, 2};
        weight = 900;
    };

    class DZ_ConvoyZ_EncryptedDataModule: GPSReceiver
    {
        scope = 2;
        displayName = "DeutschZ ConvoyZ Datenmodul";
        descriptionShort = "Verschluesseltes Datenmodul aus einem ConvoyZ-Fahrzeug. Fuer Quest- und Rewardlogik vorbereitet.";
        hiddenSelections[] = {"camo"};
        hiddenSelectionsTextures[] = {"DeutschZ_ConvoyZ/Assets/Case/CardReader.paa"};
        itemSize[] = {1, 2};
        weight = 180;
    };

    class DZ_ConvoyZ_SealedWeaponCase: SmallProtectorCase
    {
        scope = 2;
        displayName = "DeutschZ ConvoyZ versiegelter Waffenkoffer";
        descriptionShort = "Versiegelter Eventkoffer aus einem Convoy. Darf nur ueber Event, Adminspawn, Trader oder Reward ausgegeben werden.";
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
        displayName = "DeutschZ ConvoyZ Dieselmanifest";
        descriptionShort = "Transportmanifest mit Routen-, Diesel- und Ladungsdaten eines ConvoyZ-Events.";
        itemSize[] = {1, 2};
        weight = 25;
    };

    class DZ_ConvoyZ_RadioKey: PunchedCard
    {
        scope = 2;
        displayName = "DeutschZ ConvoyZ Funkschluessel";
        descriptionShort = "Verschluesselter Funkschluessel fuer ConvoyZ-Signale und spaetere Eventtrigger.";
        hiddenSelections[] = {"camo"};
        hiddenSelectionsTextures[] = {"DeutschZ_ConvoyZ/Assets/Case/AccesCard.paa"};
        itemSize[] = {1, 1};
        weight = 35;
    };

    class DZ_ConvoyZ_ArmorPlateBundle: SmallProtectorCase
    {
        scope = 2;
        displayName = "DeutschZ ConvoyZ Panzerplatten-Buendel";
        descriptionShort = "Schweres Buendel geborgener Schutzplatten aus einem ConvoyZ-Event. Reward- und Traderitem, kein normaler Mapspawn.";
        model = "DeutschZ_ConvoyZ/Assets/Case/protector_case.p3d";
        hiddenSelections[] = {"camo"};
        hiddenSelectionsTextures[] = {"DeutschZ_ConvoyZ/Assets/Case/Case.paa"};
        itemSize[] = {3, 3};
        weight = 6500;
        canBeSplit = 0;
    };

};
