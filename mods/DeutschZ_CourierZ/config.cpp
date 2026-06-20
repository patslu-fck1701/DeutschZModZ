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
        units[] = {"DZCR_SealedLetter", "DZCR_ClassifiedDocument", "DZCR_EncryptedDataDrive", "DZCR_SecretOrder", "DZCR_Aktenkoffer", "DZCR_RewardChest"};
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
        version = "0.1.0-safe-boot-event-skeleton";
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
        displayName = "Versiegelter Aktenkoffer";
        descriptionShort = "DeutschZ CourierZ Eventkoffer. Serverautoritaer verwaltet.";
        itemSize[] = {4, 3};
        weight = 2500;
        canBeSplit = 0;
        quantityBar = 0;
    };

    class DZCR_RewardChest: SeaChest
    {
        scope = 2;
        displayName = "DeutschZ CourierZ Belohnungskiste";
        descriptionShort = "Belohnung fuer eine erfolgreiche Kurierlieferung.";
        itemSize[] = {10, 10};
        weight = 15000;
    };
};
