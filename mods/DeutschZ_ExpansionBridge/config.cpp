class CfgPatches
{
    class DeutschZ_ExpansionBridge
    {
        units[] = {};
        weapons[] = {};
        requiredVersion = 0.1;
        requiredAddons[] = {"DZ_Data", "DeutschZ_Core"};
    };
};

class CfgMods
{
    class DeutschZ_ExpansionBridge
    {
        dir = "DeutschZ_ExpansionBridge";
        name = "DeutschZ_ExpansionBridge";
        author = "Patrick Sluzalek / fck1701";
        type = "mod";
        dependencies[] = {"Game", "World", "Mission"};
        class defs
        {
            class gameScriptModule
            {
                value = "";
                files[] = {"DeutschZ_ExpansionBridge/scripts/3_Game"};
            };
            class worldScriptModule
            {
                value = "";
                files[] = {"DeutschZ_ExpansionBridge/scripts/4_World"};
            };
            class missionScriptModule
            {
                value = "";
                files[] = {"DeutschZ_ExpansionBridge/scripts/5_Mission"};
            };
        };
    };
};
