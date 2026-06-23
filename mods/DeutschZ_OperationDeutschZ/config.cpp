class CfgPatches
{
    class DeutschZ_OperationDeutschZ
    {
        units[] = {};
        weapons[] = {};
        requiredVersion = 0.1;
        requiredAddons[] =
        {
            "DZ_Data",
            "DZ_Scripts",
            "DeutschZ_Core",
            "DeutschZ_KotHZ",
            "DeutschZ_ConvoyZ",
            "DeutschZ_GroundZero",
            "DeutschZ_CourierZ"
        };
    };
};

class CfgMods
{
    class DeutschZ_OperationDeutschZ
    {
        dir = "DeutschZ_OperationDeutschZ";
        name = "DeutschZ OperationDeutschZ";
        picture = "";
        action = "";
        hideName = 0;
        hidePicture = 0;
        type = "mod";
        author = "Patrick Sluzalek / fck1701 / DeutschZ";
        version = "0.9.4-campaign-chain-test";
        dependencies[] = {"Game", "World", "Mission"};

        class defs
        {
            class gameScriptModule
            {
                value = "";
                files[] = {"DeutschZ_OperationDeutschZ/scripts/3_Game", "scripts/3_Game"};
            };
            class worldScriptModule
            {
                value = "";
                files[] = {"DeutschZ_OperationDeutschZ/scripts/4_World", "scripts/4_World"};
            };
            class missionScriptModule
            {
                value = "";
                files[] = {"DeutschZ_OperationDeutschZ/scripts/5_Mission", "scripts/5_Mission"};
            };
        };
    };
};
