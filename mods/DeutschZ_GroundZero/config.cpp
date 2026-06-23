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
            "DeutschZ_Core"
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
        version = "0.9.4-campaign-chain-test";
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
        displayName = "$STR_DZGROUNDZERO_GROUNDZERO_COMPONENTBASE_NAME";
        descriptionShort = "$STR_DZGROUNDZERO_GROUNDZERO_COMPONENTBASE_DESC";
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
        displayName = "$STR_DZGROUNDZERO_GROUNDZERO_ALPHADATAMODULE_NAME";
        descriptionShort = "$STR_DZGROUNDZERO_GROUNDZERO_ALPHADATAMODULE_DESC";
    };

    class GroundZero_EnergyCell: GroundZero_ComponentBase
    {
        scope = 2;
        displayName = "$STR_DZGROUNDZERO_GROUNDZERO_ENERGYCELL_NAME";
        descriptionShort = "$STR_DZGROUNDZERO_GROUNDZERO_ENERGYCELL_DESC";
    };

    class GroundZero_BioSample: GroundZero_ComponentBase
    {
        scope = 2;
        displayName = "$STR_DZGROUNDZERO_GROUNDZERO_BIOSAMPLE_NAME";
        descriptionShort = "$STR_DZGROUNDZERO_GROUNDZERO_BIOSAMPLE_DESC";
    };

    class GroundZero_AuthChip: GroundZero_ComponentBase
    {
        scope = 2;
        displayName = "$STR_DZGROUNDZERO_GROUNDZERO_AUTHCHIP_NAME";
        descriptionShort = "$STR_DZGROUNDZERO_GROUNDZERO_AUTHCHIP_DESC";
    };

    class GroundZero_ContainmentKey: GroundZero_ComponentBase
    {
        scope = 2;
        displayName = "$STR_DZGROUNDZERO_GROUNDZERO_CONTAINMENTKEY_NAME";
        descriptionShort = "$STR_DZGROUNDZERO_GROUNDZERO_CONTAINMENTKEY_DESC";
    };

    class GroundZero_ResearchCore: GroundZero_ComponentBase
    {
        scope = 2;
        displayName = "$STR_DZGROUNDZERO_GROUNDZERO_RESEARCHCORE_NAME";
        descriptionShort = "$STR_DZGROUNDZERO_GROUNDZERO_RESEARCHCORE_DESC";
        itemSize[] = {3, 3};
        weight = 3000;
    };

    class DZGZ_GeneratorSparkPlug: GroundZero_ComponentBase
    {
        scope = 2;
        displayName = "$STR_DZGROUNDZERO_DZGZ_GENERATORSPARKPLUG_NAME";
        descriptionShort = "$STR_DZGROUNDZERO_DZGZ_GENERATORSPARKPLUG_DESC";
        itemSize[] = {1, 2};
        weight = 260;
    };

    class DZGZ_EncryptedResearchData: GroundZero_ComponentBase
    {
        scope = 2;
        displayName = "$STR_DZGROUNDZERO_DZGZ_ENCRYPTEDRESEARCHDATA_NAME";
        descriptionShort = "$STR_DZGROUNDZERO_DZGZ_ENCRYPTEDRESEARCHDATA_DESC";
        itemSize[] = {1, 1};
        weight = 90;
    };

    class DZGZ_ContaminatedSample: GroundZero_ComponentBase
    {
        scope = 2;
        displayName = "$STR_DZGROUNDZERO_DZGZ_CONTAMINATEDSAMPLE_NAME";
        descriptionShort = "$STR_DZGROUNDZERO_DZGZ_CONTAMINATEDSAMPLE_DESC";
        itemSize[] = {1, 2};
        weight = 360;
    };

    class DZGZ_SignalCore: GroundZero_ComponentBase
    {
        scope = 2;
        displayName = "$STR_DZGROUNDZERO_DZGZ_SIGNALCORE_NAME";
        descriptionShort = "$STR_DZGROUNDZERO_DZGZ_SIGNALCORE_DESC";
        itemSize[] = {2, 2};
        weight = 950;
    };

    class DZ_GroundZero_ContaminatedDataCore: GroundZero_ComponentBase
    {
        scope = 2;
        displayName = "$STR_DZGROUNDZERO_DZ_GROUNDZERO_CONTAMINATEDDATACORE_NAME";
        descriptionShort = "$STR_DZGROUNDZERO_DZ_GROUNDZERO_CONTAMINATEDDATACORE_DESC";
        itemSize[] = {2, 2};
        weight = 1400;
    };

    class DZ_GroundZero_Sample: GroundZero_ComponentBase
    {
        scope = 2;
        displayName = "$STR_DZGROUNDZERO_DZ_GROUNDZERO_SAMPLE_NAME";
        descriptionShort = "$STR_DZGROUNDZERO_DZ_GROUNDZERO_SAMPLE_DESC";
        itemSize[] = {1, 2};
        weight = 350;
    };

    class DZ_GroundZero_ReactorCode: GroundZero_ComponentBase
    {
        scope = 2;
        displayName = "$STR_DZGROUNDZERO_DZ_GROUNDZERO_REACTORCODE_NAME";
        descriptionShort = "$STR_DZGROUNDZERO_DZ_GROUNDZERO_REACTORCODE_DESC";
        itemSize[] = {1, 1};
        weight = 60;
    };

    class DZ_GroundZero_EvacuationOrder: GroundZero_ComponentBase
    {
        scope = 2;
        displayName = "$STR_DZGROUNDZERO_DZ_GROUNDZERO_EVACUATIONORDER_NAME";
        descriptionShort = "$STR_DZGROUNDZERO_DZ_GROUNDZERO_EVACUATIONORDER_DESC";
        itemSize[] = {1, 2};
        weight = 35;
    };

    class DZ_GroundZero_MilitaryAccessCard: GroundZero_ComponentBase
    {
        scope = 2;
        displayName = "$STR_DZGROUNDZERO_DZ_GROUNDZERO_MILITARYACCESSCARD_NAME";
        descriptionShort = "$STR_DZGROUNDZERO_DZ_GROUNDZERO_MILITARYACCESSCARD_DESC";
        itemSize[] = {1, 1};
        weight = 25;
    };

    class DZ_GroundZero_ZoneArtifact: GroundZero_ComponentBase
    {
        scope = 2;
        displayName = "$STR_DZGROUNDZERO_DZ_GROUNDZERO_ZONEARTIFACT_NAME";
        descriptionShort = "$STR_DZGROUNDZERO_DZ_GROUNDZERO_ZONEARTIFACT_DESC";
        itemSize[] = {2, 2};
        weight = 900;
    };
};
