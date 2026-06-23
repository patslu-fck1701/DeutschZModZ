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
        version = "0.9.3-online-test";
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
        displayName = "Alpha-Datenmodul";
    };

    class GroundZero_EnergyCell: GroundZero_ComponentBase
    {
        scope = 2;
        displayName = "Energiezelle";
    };

    class GroundZero_BioSample: GroundZero_ComponentBase
    {
        scope = 2;
        displayName = "Biologische Probe";
    };

    class GroundZero_AuthChip: GroundZero_ComponentBase
    {
        scope = 2;
        displayName = "Authentifizierungschip";
    };

    class GroundZero_ContainmentKey: GroundZero_ComponentBase
    {
        scope = 2;
        displayName = "Containment-Schlüssel";
    };

    class GroundZero_ResearchCore: GroundZero_ComponentBase
    {
        scope = 2;
        displayName = "Forschungskern";
        itemSize[] = {3, 3};
        weight = 3000;
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
