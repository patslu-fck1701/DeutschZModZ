class CfgPatches
{
    class DeutschZ_Tools
    {
        units[] = {};
        weapons[] = {};
        requiredVersion = 0.1;
        requiredAddons[] =
        {
            "DZ_Data"
        };
    };
};

class CfgMods
{
    class DeutschZ_Tools
    {
        dir = "DeutschZ_Tools";
        name = "DeutschZ ServerCore - Tools";
        type = "mod";
        author = "Patrick Sluzalek / fck1701 / DeutschZ";
        version = "1.4.1 Player Picker Polish";
        inputs = "DeutschZ_Tools/inputs.xml";

        dependencies[] =
        {
            "Game",
            "World",
            "Mission"
        };

        class defs
        {
            class gameScriptModule
            {
                value = "";
                files[] =
                {
                    "DeutschZ_Tools/scripts/3_Game"
                };
            };

            class worldScriptModule
            {
                value = "";
                files[] =
                {
                    "DeutschZ_Tools/scripts/4_World"
                };
            };

            class missionScriptModule
            {
                value = "";
                files[] =
                {
                    "DeutschZ_Tools/scripts/5_Mission"
                };
            };
        };
    };
};
