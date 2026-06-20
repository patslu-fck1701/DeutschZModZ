class CfgPatches
{
    class DeutschZ_Garage
    {
        units[] = {"DeutschZ_ParkingStation", "DeutschZ_Garage_Sign", "DeutschZ_Garage_Kit", "DeutschZ_Garage_Kit_Placing"};
        weapons[] = {};
        requiredVersion = 0.1;
        requiredAddons[] = {"DZ_Data", "DZ_Scripts"};
    };
};

class CfgMods
{
    class DeutschZ_Garage
    {
        dir = "DeutschZ_Garage";
        name = "DeutschZ Garage";
        credits = "Owner: Patrick Sluzalek / Server: DeutschZ";
        author = "Patrick Sluzalek / DeutschZ";
        authorID = "0";
        version = "0.1.9 ToolZ UI";
        type = "mod";
        hideName = 0;
        hidePicture = 1;
        defines[] = {"DEUTSCHZ_GARAGE"};
        dependencies[] = {"Game", "World", "Mission"};

        class defs
        {
            class gameScriptModule
            {
                value = "";
                files[] = {"DeutschZ_Garage/scripts/3_Game"};
            };
            class worldScriptModule
            {
                value = "";
                files[] = {"DeutschZ_Garage/scripts/4_World"};
            };
            class missionScriptModule
            {
                value = "";
                files[] = {"DeutschZ_Garage/scripts/5_Mission"};
            };
        };
    };
};

class CfgVehicles
{
    class Inventory_Base;

    class DeutschZ_ParkingStation: Inventory_Base
    {
        scope = 2;
        displayName = "DeutschZ Parking Station";
        descriptionShort = "DeutschZ virtual garage access point.";
        model = "\DeutschZ_Garage\items\parking_station\GaragePlaced.p3d";
        itemBehaviour = 2;
        slopeTolerance = 3.0;
        hiddenSelections[] = {"texture"};
        hiddenSelectionsTextures[] = {"\DeutschZ_Garage\items\parking_station\PlayerGaragePlaced_co.paa"};
        hiddenSelectionsMaterials[] = {"\DeutschZ_Garage\items\parking_station\PlayerGaragePlaced.rvmat"};
    };

    class DeutschZ_Garage_Sign: DeutschZ_ParkingStation
    {
        scope = 2;
        displayName = "DeutschZ Garage";
        descriptionShort = "Alias for DeutschZ Parking Station.";
    };

    class DeutschZ_Garage_Kit: Inventory_Base
    {
        scope = 2;
        displayName = "DeutschZ Garage Kit";
        descriptionShort = "Kit zum Platzieren einer DeutschZ Garage.";
        model = "\DeutschZ_Garage\items\parking_station\GaragePlaced.p3d";
        itemBehaviour = 2;
        slopeTolerance = 3.0;
        hiddenSelections[] = {"texture"};
        hiddenSelectionsTextures[] = {"\DeutschZ_Garage\items\parking_station\PlayerGaragePlaced_co.paa"};
        hiddenSelectionsMaterials[] = {"\DeutschZ_Garage\items\parking_station\PlayerGaragePlaced.rvmat"};
        itemSize[] = {2, 2};
        weight = 500;
    };

    class DeutschZ_Garage_Kit_Placing: DeutschZ_Garage_Kit
    {
        scope = 1;
        displayName = "DeutschZ Garage Placement";
        descriptionShort = "Placement preview for DeutschZ Garage.";
        storageCategory = 10;
        alignHologramToTerain = 1;
    };
};
