class CfgPatches
{
    class DeutschZ_BattlepassZ
    {
        units[] = {};
        weapons[] = {};
        requiredVersion = 0.1;
        requiredAddons[] = {"DZ_Data", "DZ_Scripts"};
    };
};

class CfgMods
{
    class DeutschZ_BattlepassZ
    {
        dir = "DeutschZ_BattlepassZ";
        picture = "";
        action = "";
        hideName = 0;
        hidePicture = 1;
        name = "DeutschZ BattlepassZ";
        credits = "DeutschZ BattlepassZ by Patrick Sluzalek / fck1701";
        author = "Patrick Sluzalek / fck1701";
        authorID = "0";
        version = "0.2.2";
        extra = 0;
        type = "mod";
        inputs = "DeutschZ_BattlepassZ/inputsDeutschZBattlepass.xml";
        dependencies[] = {"Game", "World", "Mission"};

        class defs
        {
            class gameScriptModule
            {
                value = "";
                files[] = {"DeutschZ_BattlepassZ/scripts/3_Game"};
            };
            class worldScriptModule
            {
                value = "";
                files[] = {"DeutschZ_BattlepassZ/scripts/4_World"};
            };
            class missionScriptModule
            {
                value = "";
                files[] = {"DeutschZ_BattlepassZ/scripts/5_Mission"};
            };
        };
    };
};



