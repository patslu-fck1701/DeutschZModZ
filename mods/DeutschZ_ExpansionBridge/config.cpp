class CfgPatches
{
    class DeutschZ_ExpansionBridge
    {
        units[] = {};
        weapons[] = {};
        requiredVersion = 0.1;
        requiredAddons[] = {"DZ_Data", "DZ_Scripts", "DeutschZ_Core", "DayZExpansion_Core_Scripts", "DayZExpansion_Navigation_Scripts", "DayZExpansion_AI_Scripts"};
    };
};

class CfgMods
{
    class DeutschZ_ExpansionBridge
    {
        dir = "DeutschZ_ExpansionBridge";
        name = "DeutschZ Expansion Bridge";
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
