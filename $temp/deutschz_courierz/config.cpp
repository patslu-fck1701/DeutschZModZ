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
        units[] = {"DZCR_SealedLetter", "DZCR_ClassifiedDocument", "DZCR_EncryptedDataDrive", "DZCR_SecretOrder", "DZCR_Aktenkoffer", "DZCR_RewardChest", "DZ_CourierZ_Briefcase", "DZ_CourierZ_SealedCourierFolder", "DZ_CourierZ_SecretDeliveryContract", "DZ_CourierZ_GPSTracker", "DZ_CourierZ_CourierSeal", "DZ_CourierZ_BlackMarketReceipt"};
        weapons[] = {};
        requiredVersion = 0.1;
        requiredAddons[] = {"DZ_Data", "DZ_Scripts", "DZ_Gear_Containers", "DZ_Gear_Navigation", "DZ_Gear_Consumables", "DeutschZ_Core", "DeutschZ_ExpansionBridge"};
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
        version = "0.1.7-fix45-event-items";
        extra = 0;
        type = "mod";
        dependencies[] = {"Game", "World", "Mission"};

        class defs
        {
            class gameScriptModule
            {
                value = "";
                files[] = {"DeutschZ_CourierZ/scripts/3_Game"};
            };
            class worldScriptModule
            {
                value = "";
                files[] = {"DeutschZ_CourierZ/scripts/4_World"};
            };
            class missionScriptModule
            {
                value = "";
                files[] = {"DeutschZ_CourierZ/scripts/5_Mission"};
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
        displayName = "Versiegelter Kurierbrief";
        descriptionShort = "DeutschZ CourierZ Startdokument fuer Operation Aktenkoffer.";
        itemSize[] = {1, 1};
        weight = 20;
    };

    class DZCR_ClassifiedDocument: Paper
    {
        scope = 2;
        displayName = "Geheimdokument";
        descriptionShort = "Klassifiziertes DeutschZ Kurierdokument.";
        itemSize[] = {1, 2};
        weight = 30;
    };

    class DZCR_SecretOrder: Paper
    {
        scope = 2;
        displayName = "Geheimauftrag";
        descriptionShort = "Verschluesselter Auftrag fuer Operation Aktenkoffer.";
        itemSize[] = {1, 2};
        weight = 30;
    };

    class DZCR_EncryptedDataDrive: GPSReceiver
    {
        scope = 2;
        displayName = "Verschluesselter Datentraeger";
        descriptionShort = "Seltener DeutschZ Kurier-Datentraeger.";
        itemSize[] = {1, 2};
        weight = 150;
    };

    class DZCR_Aktenkoffer: SmallProtectorCase
    {
        scope = 2;
        displayName = "DeutschZ Aktenkoffer";
        descriptionShort = "Versiegelter DeutschZ CourierZ Eventkoffer. Zum Ziel bringen, nicht einlagern.";
        model = "DeutschZ_CourierZ/Assets/Case/protector_case.p3d";
        hiddenSelections[] = {"camo"};
        hiddenSelectionsTextures[] = {"DeutschZ_CourierZ/Assets/Case/Case.paa"};
        itemSize[] = {4, 3};
        weight = 2500;
        canBeSplit = 0;
        quantityBar = 0;
    };

    class DZCR_RewardChest: SeaChest
    {
        scope = 2;
        displayName = "DeutschZ CourierZ Rewardkiste";
        descriptionShort = "DeutschZ CourierZ Rewardkiste mit 500 Cargo-Slots fuer erfolgreiche Lieferungen.";
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
        displayName = "DeutschZ CourierZ Aktenkoffer";
        descriptionShort = "Event-only Aktenkoffer fuer CourierZ-Lieferungen. Zielobjekt fuer Liefer-, Reward- und Adminlogik.";
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
        displayName = "DeutschZ CourierZ versiegelte Kuriermappe";
        descriptionShort = "Versiegelte Mappe mit Kurierunterlagen. Event-only Dokument fuer CourierZ.";
        itemSize[] = {1, 2};
        weight = 35;
    };

    class DZ_CourierZ_SecretDeliveryContract: Paper
    {
        scope = 2;
        displayName = "DeutschZ CourierZ geheimer Liefervertrag";
        descriptionShort = "Geheimer Liefervertrag mit Route, Zielort und Empfaengerkennung.";
        itemSize[] = {1, 2};
        weight = 30;
    };

    class DZ_CourierZ_GPSTracker: GPSReceiver
    {
        scope = 2;
        displayName = "DeutschZ CourierZ GPS-Tracker";
        descriptionShort = "Tracker fuer Kurierkoffer und Zielmarker. Event-only Technikitem.";
        itemSize[] = {1, 2};
        weight = 160;
    };

    class DZ_CourierZ_CourierSeal: Paper
    {
        scope = 2;
        displayName = "DeutschZ CourierZ Kuriersiegel";
        descriptionShort = "Rotes DeutschZ-Kuriersiegel als Nachweis fuer eine erfolgreiche Lieferung.";
        itemSize[] = {1, 1};
        weight = 15;
    };

    class DZ_CourierZ_BlackMarketReceipt: Paper
    {
        scope = 2;
        displayName = "DeutschZ CourierZ Schwarzmarktbeleg";
        descriptionShort = "Verdeckter Beleg fuer eine CourierZ-Lieferung. Event-only Dokument fuer Rewards, Trader oder Folgeaufgaben.";
        itemSize[] = {1, 2};
        weight = 20;
    };
};
