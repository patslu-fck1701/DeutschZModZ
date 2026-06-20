class CfgPatches
{
    class DeutschZ_Banking
    {
        units[] =
        {
            "DZ_MarkZ_1",
            "DZ_MarkZ_2",
            "DZ_MarkZ_5",
            "DZ_MarkZ_10",
            "DZ_MarkZ_20",
            "DZ_MarkZ_50",
            "DZ_MarkZ_100",
            "DeutschZ_ATM"
        };
        weapons[] = {};
        requiredVersion = 0.1;
        requiredAddons[] = {"DZ_Data", "DZ_Scripts"};
    };
};

class CfgMods
{
    class DeutschZ_Banking
    {
        dir = "DeutschZ_Banking";
        name = "DeutschZ Banking";
        credits = "Owner: Patrick Sluzalek / Server: DeutschZ";
        author = "Patrick Sluzalek / DeutschZ";
        authorID = "0";
        version = "0.2.0 ToolZ UI";
        type = "mod";
        hideName = 0;
        hidePicture = 1;
        defines[] = {"DEUTSCHZ_BANKING"};
        dependencies[] = {"Game", "World", "Mission"};

        class defs
        {
            class gameScriptModule
            {
                value = "";
                files[] = {"DeutschZ_Banking/scripts/3_Game"};
            };
            class worldScriptModule
            {
                value = "";
                files[] = {"DeutschZ_Banking/scripts/4_World"};
            };
            class missionScriptModule
            {
                value = "";
                files[] = {"DeutschZ_Banking/scripts/5_Mission"};
            };
        };
    };
};

class CfgVehicles
{
    class Inventory_Base;
    class HouseNoDestruct;

    class DeutschZ_ATM: HouseNoDestruct
    {
        scope = 2;
        displayName = "DeutschZ ATM";
        descriptionShort = "DeutschZ Banking terminal.";
        model = "\DeutschZ_Banking\items\atm\atm_2.p3d";
        simulation = "house";
        physLayer = "item_large";
        hiddenSelections[] = {"texture"};
        hiddenSelectionsTextures[] = {"\DeutschZ_Banking\items\atm\atm_co.paa"};
        hiddenSelectionsMaterials[] = {"\DeutschZ_Banking\items\atm\atm.rvmat"};
    };

    class DZ_MarkZ_Base: Inventory_Base
    {
        scope = 0;
        displayName = "MarkZ";
        descriptionShort = "DeutschZ MarkZ banknote.";
        model = "\DeutschZ_Banking\data\money\MarkZ_Bill.p3d";
        hiddenSelections[] = {"texture"};
        hiddenSelectionsMaterials[] = {"\DeutschZ_Banking\data\money\MarkZ_Bill.rvmat"};
        itemSize[] = {1, 1};
        weight = 1;
        varQuantityInit = 1;
        varQuantityMin = 1;
        varQuantityMax = 1;
        quantityBar = 0;
        canBeSplit = 0;
        absorbency = 0;
    };

    class DZ_MarkZ_1: DZ_MarkZ_Base
    {
        scope = 2;
        displayName = "1 MarkZ";
        descriptionShort = "DeutschZ Geldschein im Wert von 1 MarkZ.";
        hiddenSelectionsTextures[] = {"\DeutschZ_Banking\data\money\1_MarkZ.paa"};
    };

    class DZ_MarkZ_2: DZ_MarkZ_Base
    {
        scope = 2;
        displayName = "2 MarkZ";
        descriptionShort = "DeutschZ Geldschein im Wert von 2 MarkZ.";
        hiddenSelectionsTextures[] = {"\DeutschZ_Banking\data\money\2_MarkZ.paa"};
    };

    class DZ_MarkZ_5: DZ_MarkZ_Base
    {
        scope = 2;
        displayName = "5 MarkZ";
        descriptionShort = "DeutschZ Geldschein im Wert von 5 MarkZ.";
        hiddenSelectionsTextures[] = {"\DeutschZ_Banking\data\money\5_MarkZ.paa"};
    };

    class DZ_MarkZ_10: DZ_MarkZ_Base
    {
        scope = 2;
        displayName = "10 MarkZ";
        descriptionShort = "DeutschZ Geldschein im Wert von 10 MarkZ.";
        hiddenSelectionsTextures[] = {"\DeutschZ_Banking\data\money\10_MarkZ.paa"};
    };

    class DZ_MarkZ_20: DZ_MarkZ_Base
    {
        scope = 2;
        displayName = "20 MarkZ";
        descriptionShort = "DeutschZ Geldschein im Wert von 20 MarkZ.";
        hiddenSelectionsTextures[] = {"\DeutschZ_Banking\data\money\20_MarkZ.paa"};
    };

    class DZ_MarkZ_50: DZ_MarkZ_Base
    {
        scope = 2;
        displayName = "50 MarkZ";
        descriptionShort = "DeutschZ Geldschein im Wert von 50 MarkZ.";
        hiddenSelectionsTextures[] = {"\DeutschZ_Banking\data\money\50_MarkZ.paa"};
    };

    class DZ_MarkZ_100: DZ_MarkZ_Base
    {
        scope = 2;
        displayName = "100 MarkZ";
        descriptionShort = "DeutschZ Geldschein im Wert von 100 MarkZ.";
        hiddenSelectionsTextures[] = {"\DeutschZ_Banking\data\money\100_MarkZ.paa"};
    };
};
