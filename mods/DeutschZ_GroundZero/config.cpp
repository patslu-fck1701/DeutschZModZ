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
            "GroundZero_ResearchCore"
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
        version = "0.4.0-source";
        dependencies[] = {"Game", "World", "Mission"};

        class defs
        {
            class engineScriptModule
            {
                value = "";
                files[] = {"DeutschZ_GroundZero/scripts/1_Core"};
            };
            class gameLibScriptModule
            {
                value = "";
                files[] = {"DeutschZ_GroundZero/scripts/2_GameLib"};
            };
            class gameScriptModule
            {
                value = "";
                files[] = {"DeutschZ_GroundZero/scripts/3_Game"};
            };
            class worldScriptModule
            {
                value = "";
                files[] = {"DeutschZ_GroundZero/scripts/4_World"};
            };
            class missionScriptModule
            {
                value = "";
                files[] = {"DeutschZ_GroundZero/scripts/5_Mission"};
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
};
