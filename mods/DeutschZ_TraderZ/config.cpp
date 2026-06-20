class CfgPatches
{
    class DeutschZ_TraderZ
    {
        units[] =
        {
            "DeutschZTraderZ_NPC_Mirek",
            "DeutschZTraderZ_NPC_Keiko",
            "DeutschZTraderZ_NPC_Boris",
            "DeutschZTraderZ_NPC_Linda",
            "DeutschZTraderZ_NPC_Denis"
        };
        weapons[] = {};
        requiredVersion = 0.1;
        requiredAddons[] = {"DZ_Data", "DZ_Scripts", "DZ_Characters", "JM_CF_Scripts"};
    };
};

class CfgMods
{
    class DeutschZ_TraderZ
    {
        dir = "DeutschZ_TraderZ";
        name = "DeutschZ TraderZ";
        type = "mod";
        author = "Patrick Sluzalek / fck1701 / DeutschZ";
        version = "0.1.6 Market Defaults";
        defines[] = {"DEUTSCHZ_TRADERZ"};
        dependencies[] = {"Game", "World", "Mission"};

        class defs
        {
            class gameScriptModule
            {
                value = "";
                files[] = {"DeutschZ_TraderZ/scripts/3_Game"};
            };
            class worldScriptModule
            {
                value = "";
                files[] = {"DeutschZ_TraderZ/scripts/4_World"};
            };
            class missionScriptModule
            {
                value = "";
                files[] = {"DeutschZ_TraderZ/scripts/5_Mission"};
            };
        };
    };
};

class CfgVehicles
{
    class SurvivorM_Mirek;
    class SurvivorF_Keiko;
    class SurvivorM_Boris;
    class SurvivorF_Linda;
    class SurvivorM_Denis;

    class DeutschZTraderZ_NPC_Mirek: SurvivorM_Mirek
    {
        scope = 2;
        displayName = "DeutschZ Trader";
    };
    class DeutschZTraderZ_NPC_Keiko: SurvivorF_Keiko
    {
        scope = 2;
        displayName = "DeutschZ Trader";
    };
    class DeutschZTraderZ_NPC_Boris: SurvivorM_Boris
    {
        scope = 2;
        displayName = "DeutschZ Trader";
    };
    class DeutschZTraderZ_NPC_Linda: SurvivorF_Linda
    {
        scope = 2;
        displayName = "DeutschZ Trader";
    };
    class DeutschZTraderZ_NPC_Denis: SurvivorM_Denis
    {
        scope = 2;
        displayName = "DeutschZ Trader";
    };
};
