class CfgPatches
{
    class DeutschZ_Groups
    {
        units[] = {};
        weapons[] = {};
        requiredVersion = 0.1;
        requiredAddons[] = {"DZ_Data", "DZ_Scripts", "DZ_Gear_Navigation", "JM_CF_Scripts"};
    };
};

class CfgMods
{
    class DeutschZ_Groups
    {
        dir = "DeutschZ_Groups";
        picture = "";
        action = "";
        hideName = 0;
        hidePicture = 1;
        name = "DeutschZ Groups";
        credits = "DeutschZ own group, rank, map and marker system foundation by Patrick Sluzalek / fck1701";
        author = "Patrick Sluzalek / fck1701";
        authorID = "0";
        version = "0.5.2 ToolZ Map UI";
        extra = 0;
        type = "mod";
        defines[] = {"DEUTSCHZ_GROUPS"};
        inputs = "DeutschZ_Groups/inputsDeutschZGroups.xml";
        dependencies[] = {"Game", "World", "Mission"};

        class defs
        {
            class gameScriptModule
            {
                value = "";
                files[] = {"DeutschZ_Groups/scripts/3_Game"};
            };
            class worldScriptModule
            {
                value = "";
                files[] = {"DeutschZ_Groups/scripts/4_World"};
            };
            class missionScriptModule
            {
                value = "";
                files[] = {"DeutschZ_Groups/scripts/5_Mission"};
            };
        };
    };
};
