
class CfgPatches
{
    class DeutschZ_SpawnSelectZ
    {
        units[]={};
        weapons[]={};
        requiredVersion=0.1;
        requiredAddons[]={"DZ_Data","DZ_Scripts"};
    };
};
class CfgMods
{
    class DeutschZ_SpawnSelectZ
    {
        dir="DeutschZ_SpawnSelectZ";
        name="DeutschZ_SpawnSelectZ";
        type="mod";
        dependencies[]={"Game","World","Mission"};
        inputs="DeutschZ_SpawnSelectZ/inputsDeutschZSpawnSelect.xml";
        class defs
        {
            class gameScriptModule{files[]={"DeutschZ_SpawnSelectZ/scripts/3_Game"};};
            class worldScriptModule{files[]={"DeutschZ_SpawnSelectZ/scripts/4_World"};};
            class missionScriptModule{files[]={"DeutschZ_SpawnSelectZ/scripts/5_Mission"};};
        };
    };
};
