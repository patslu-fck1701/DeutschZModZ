class CfgPatches
{
    class DeutschZ_GroundZero
    {
        units[] =
        {
            "GroundZero_AlphaDataModule",
            "GroundZero_EnergyCell",
            "GroundZero_BioSample",
            "GroundZero_AuthChip",
            "GroundZero_ContainmentKey",
            "GroundZero_ResearchCore",
            "DZGZ_GeneratorSparkPlug",
            "DZGZ_EncryptedResearchData",
            "DZGZ_ContaminatedSample",
            "DZGZ_SignalCore",
            "DZ_GroundZero_ContaminatedDataCore",
            "DZ_GroundZero_Sample",
            "DZ_GroundZero_ReactorCode",
            "DZ_GroundZero_EvacuationOrder",
            "DZ_GroundZero_MilitaryAccessCard",
            "DZ_GroundZero_ZoneArtifact"
        };
        weapons[] = {};
        requiredVersion = 0.1;
        requiredAddons[] =
        {
            "DZ_Data",
            "DZ_Scripts",
            "DZ_Gear_Containers",
            "DeutschZ_Core",
            "DeutschZ_ExpansionBridge"
        };
    };
};

class CfgMods
{
    class DeutschZ_GroundZero
    {
        dir = "DeutschZ_GroundZero";
        name = "DeutschZ GroundZero";
        type = "mod";
        author = "Patrick Sluzalek / fck1701";
<<<<<<< HEAD
        version = "0.9.4-campaign-chain-test";
=======
        version = "0.9.3-online-test";
>>>>>>> 39fa93c734f52a69c045816aa7b5632b5a10d772
        dependencies[] = {"Game", "World", "Mission"};

        class defs
        {
            class engineScriptModule
            {
                value = "";
                files[] = {"DeutschZ_GroundZero/scripts/1_Core", "scripts/1_Core"};
            };
            class gameLibScriptModule
            {
                value = "";
                files[] = {"DeutschZ_GroundZero/scripts/2_GameLib", "scripts/2_GameLib"};
            };
            class gameScriptModule
            {
                value = "";
                files[] = {"DeutschZ_GroundZero/scripts/3_Game", "scripts/3_Game"};
            };
            class worldScriptModule
            {
                value = "";
                files[] = {"DeutschZ_GroundZero/scripts/4_World", "scripts/4_World"};
            };
            class missionScriptModule
            {
                value = "";
                files[] = {"DeutschZ_GroundZero/scripts/5_Mission", "scripts/5_Mission"};
            };
        };
    };
};

class CfgVehicles
{
    class Inventory_Base;

    class GroundZero_ComponentBase: Inventory_Base
    {
        scope = 0;
        displayName = "Ground Zero Component";
        descriptionShort = "Kritische Ground-Zero-Komponente.";
        weight = 1200;
        itemSize[] = {2, 2};
        quantityBar = 0;
        varQuantityInit = 1;
        varQuantityMin = 1;
        varQuantityMax = 1;
        canBeSplit = 0;
        stackedUnit = "";
        hiddenSelections[] = {};
    };

    class GroundZero_AlphaDataModule: GroundZero_ComponentBase
    {
        scope = 2;
        displayName = "GroundZero Alpha-Datenmodul";
        descriptionShort = "Gesichertes Datenmodul aus der Signalquelle. Event-only Bauteil fuer GroundZero und OperationDeutschZ.";
    };

    class GroundZero_EnergyCell: GroundZero_ComponentBase
    {
        scope = 2;
        displayName = "GroundZero Energiezelle";
        descriptionShort = "Instabile Energiezelle aus der Generatorstation. Nicht fuer normalen Mapspawn vorgesehen.";
    };

    class GroundZero_BioSample: GroundZero_ComponentBase
    {
        scope = 2;
        displayName = "GroundZero biologische Probe";
        descriptionShort = "Versiegelte Probe aus einer kontaminierten GroundZero-Zone.";
    };

    class GroundZero_AuthChip: GroundZero_ComponentBase
    {
        scope = 2;
        displayName = "GroundZero Authentifizierungschip";
        descriptionShort = "Authentifizierungschip fuer Terminal-, Cache- und Kampagnenlogik.";
    };

    class GroundZero_ContainmentKey: GroundZero_ComponentBase
    {
        scope = 2;
        displayName = "GroundZero Containment-Schluessel";
        descriptionShort = "Schluessel fuer den finalen Containment-Cache.";
    };

    class GroundZero_ResearchCore: GroundZero_ComponentBase
    {
        scope = 2;
        displayName = "GroundZero Forschungskern";
        descriptionShort = "Schwerer Forschungskern aus dem Final Cache. Seltenes Event- und Kampagnenitem.";
        itemSize[] = {3, 3};
        weight = 3000;
    };

    class DZGZ_GeneratorSparkPlug: GroundZero_ComponentBase
    {
        scope = 2;
        displayName = "GroundZero Generator-Zuendmodul";
        descriptionShort = "Spezialteil fuer die GroundZero-Generatorreparatur. Wird durch die Hold-Zone freigeschaltet und soll nicht normal spawnen.";
        itemSize[] = {1, 2};
        weight = 260;
    };

    class DZGZ_EncryptedResearchData: GroundZero_ComponentBase
    {
        scope = 2;
        displayName = "GroundZero verschluesselte Forschungsdaten";
        descriptionShort = "Extrahierte Terminaldaten aus GroundZero. Kann spaeter OperationDeutschZ-Hinweise freischalten.";
        itemSize[] = {1, 1};
        weight = 90;
    };

    class DZGZ_ContaminatedSample: GroundZero_ComponentBase
    {
        scope = 2;
        displayName = "GroundZero kontaminierte Probe";
        descriptionShort = "Versiegelte kontaminierte Probe. Nur fuer Event-, Trader- und Kampagnenlogik gedacht.";
        itemSize[] = {1, 2};
        weight = 360;
    };

    class DZGZ_SignalCore: GroundZero_ComponentBase
    {
        scope = 2;
        displayName = "GroundZero Signalkern";
        descriptionShort = "Geborgener Signalkern aus einer GroundZero-Anlage. Hochwertiges OperationDeutschZ-Verbindungsitem.";
        itemSize[] = {2, 2};
        weight = 950;
    };

    class DZ_GroundZero_ContaminatedDataCore: GroundZero_ComponentBase
    {
        scope = 2;
        displayName = "DeutschZ GroundZero kontaminierter Datenkern";
        descriptionShort = "Kontaminierter Datenkern aus der GroundZero-Zone. Event-only Reward- und Questitem.";
        itemSize[] = {2, 2};
        weight = 1400;
    };

    class DZ_GroundZero_Sample: GroundZero_ComponentBase
    {
        scope = 2;
        displayName = "DeutschZ GroundZero Probe";
        descriptionShort = "Gesicherte Probe aus einer GroundZero-Zone. Nur fuer Event-, Admin- und Traderlogik vorgesehen.";
        itemSize[] = {1, 2};
        weight = 350;
    };

    class DZ_GroundZero_ReactorCode: GroundZero_ComponentBase
    {
        scope = 2;
        displayName = "DeutschZ GroundZero Reaktorcode";
        descriptionShort = "Verschluesselter Reaktorcode fuer GroundZero-Trigger und spaetere Missionslogik.";
        itemSize[] = {1, 1};
        weight = 60;
    };

    class DZ_GroundZero_EvacuationOrder: GroundZero_ComponentBase
    {
        scope = 2;
        displayName = "DeutschZ GroundZero Evakuierungsbefehl";
        descriptionShort = "Befehl zur Evakuierung einer kontaminierten Zone. Event-only Dokument.";
        itemSize[] = {1, 2};
        weight = 35;
    };

    class DZ_GroundZero_MilitaryAccessCard: GroundZero_ComponentBase
    {
        scope = 2;
        displayName = "DeutschZ GroundZero Militaer-Zugangskarte";
        descriptionShort = "Militaerische Zugangskarte fuer GroundZero-Sperrzonen und Rewardlogik.";
        itemSize[] = {1, 1};
        weight = 25;
    };

    class DZ_GroundZero_ZoneArtifact: GroundZero_ComponentBase
    {
        scope = 2;
        displayName = "DeutschZ GroundZero Zonenartefakt";
        descriptionShort = "Seltenes Artefakt aus einer GroundZero-Zone. Hochwertiges Event-only Rewarditem.";
        itemSize[] = {2, 2};
        weight = 900;
    };
};
