/*
DeutschZ ModZ
Eigenstaendige Implementierung fuer DeutschZ.
Autor/Eigentuemer: Patrick Sluzalek / fck1701.
Keine direkte Codeuebernahme aus Drittquellen.
Oeffentliche Quellen werden nur zur Konzept- und API-Verifikation genutzt.
*/

class CfgPatches
{
    class DeutschZ_KotHZ
    {
        units[] = {"DeutschZKotHZ_RuntimeFlagpole", "DeutschZKotHZ_EventFlagpole", "DeutschZKotHZ_RuntimeFogEmitter", "DeutschZKotHZ_RewardCrate", "DeutschZKotHZ_DropCrate", "DeutschZKotHZ_Flag", "DeutschZKotHZ_Alt_One_Flag", "DeutschZKotHZ_Alt_Two_Flag", "DeutschZKotHZ_Alt_Three_Flag", "DeutschZKotHZ_DeutschZ_KotHZ_Flag", "DeutschZKotHZ_NWAF_Flag", "DeutschZKotHZ_Tisy_Flag", "DeutschZKotHZ_LOPA_Flag", "DeutschZKotHZ_YRAP_Flag", "DeutschZKotHZ_Basebuild_Flag", "DeutschZKotHZ_BiohazardReader", "DeutschZKotHZ_AccessCard", "DeutschZKotHZ_ResearchDocument", "DeutschZKotHZ_CommanderInsignia"};
        weapons[] = {};
        requiredVersion = 0.1;
        requiredAddons[] = {"DZ_Data", "DZ_Scripts", "DZ_Sounds_Effects", "DZ_Gear_Camping", "DZ_Gear_Containers", "DZ_Gear_Navigation", "DZ_Gear_Consumables", "JM_CF_Scripts", "DeutschZ_Core", "DeutschZ_ExpansionBridge"};
    };
};

class CfgMods
{
    class DeutschZ_KotHZ
    {
        dir = "DeutschZ_KotHZ";
        picture = "";
        action = "";
        hideName = 0;
        hidePicture = 1;
        name = "DeutschZ_KotHZ - Infected Siege";
        credits = "Owner: Patrick Sluzalek / Player: fck1701 / Server: DeutschZ";
        author = "Patrick Sluzalek / fck1701";
        authorID = "0";
        version = "2.2.9 FIX23 NoMusic MarkerNotify TestReady";
        extra = 0;
        type = "mod";
        defines[] = {"DEUTSCHZ_KotHZ"};

        dependencies[] = {"Game", "World", "Mission"};

        class defs
        {
            class gameScriptModule
            {
                value = "";
                files[] = {"DeutschZ_KotHZ/scripts/3_Game"};
            };
            class worldScriptModule
            {
                value = "";
                files[] = {"DeutschZ_KotHZ/scripts/4_World"};
            };
            class missionScriptModule
            {
                value = "";
                files[] = {"DeutschZ_KotHZ/scripts/5_Mission"};
            };
        };
    };
};

// FIX21: KOTH event music disabled for Safe-Boot. SoundShader/SoundSet registration intentionally removed.

class CfgVehicles
{
    class Inventory_Base;
    class SeaChest;
    class GPSReceiver;
    class PunchedCard;
    class Paper;
    class Flag_Base;

    // SAFEBOOT: all risky runtime objects are non-persistent simple Inventory_Base objects.
    // This avoids native startup access violations from old BaseBuildingBase/TerritoryFlag persistence.
    class DeutschZKotHZ_RuntimeFogEmitter: Inventory_Base
    {
        scope = 1;
        displayName = "DeutschZ KotHZ Runtime Fog Emitter";
        descriptionShort = "Runtime-only disabled safe emitter.";
        model = "\DZ\gear\consumables\Stone.p3d";
        itemSize[] = {1,1};
        weight = 1;
        physLayer = "item_small";
    };

    class DeutschZKotHZ_RuntimeFlagpole: Inventory_Base
    {
        scope = 2;
        displayName = "DeutschZ KotHZ Runtime Flagpole";
        descriptionShort = "Runtime-only KOTH capture mast. Non-BaseBuilding to avoid old storage crashes.";
        model = "\DZ\gear\camping\territory_flag.p3d";
        attachments[] = {"Material_FPole_Flag"};
        bounding = "BSphere";
        overrideDrawArea = "3.0";
        forceFarBubble = "true";
        handheld = "false";
        weight = 10000;
        itemBehaviour = 0;
        itemSize[] = {15,15};
        canBeDigged = 0;
        physLayer = "item_large";
        rotationFlags = 2;

        class DamageSystem
        {
            class GlobalHealth
            {
                class Health { hitpoints = 999999; };
            };
            class GlobalArmor
            {
                class Projectile { class Health { damage = 0; }; class Blood { damage = 0; }; class Shock { damage = 0; }; };
                class Melee { class Health { damage = 0; }; class Blood { damage = 0; }; class Shock { damage = 0; }; };
                class FragGrenade { class Health { damage = 0; }; class Blood { damage = 0; }; class Shock { damage = 0; }; };
            };
            class DamageZones {};
        };

        class AnimationSources
        {
            class AnimSourceShown { source = "user"; animPeriod = 0.01; initPhase = 0; };
            class AnimSourceHidden { source = "user"; animPeriod = 0.01; initPhase = 1; };
            class flag_mast { source = "user"; initPhase = 1; animPeriod = 1; };
            class Deployed: AnimSourceShown {};
            class Base: AnimSourceShown {};
            class Support: AnimSourceShown {};
            class Pole: AnimSourceShown {};
            class Material_FPole_WoodenLog: AnimSourceHidden {};
            class Material_FPole_Stones: AnimSourceHidden {};
            class Material_FPole_WoodenLog2: AnimSourceHidden {};
            class Material_FPole_MetalWire: AnimSourceHidden {};
            class Material_FPole_Rope: AnimSourceHidden {};
            class Material_FPole_Nails: AnimSourceHidden {};
            class Material_FPole_MagicStick: AnimSourceHidden {};
            class Material_FPole_Flag: AnimSourceShown {};
        };
    };

    class DeutschZKotHZ_EventFlagpole: DeutschZKotHZ_RuntimeFlagpole
    {
        scope = 1;
    };

    class DeutschZKotHZ_LegacyFlagpoleCleanupAlias: DeutschZKotHZ_RuntimeFlagpole
    {
        scope = 1;
    };

    // Reward crate: active DeutschZ KotHZ SeaChest skin.
    class DeutschZKotHZ_RewardCrate: SeaChest
    {
        scope = 2;
        displayName = "DeutschZ KotHZ Infected Siege Reward Chest";
        descriptionShort = "DeutschZ KotHZ reward chest with custom SeaChest skin.";
        hiddenSelections[] = {"camoground"};
        hiddenSelectionsTextures[] = {"/DeutschZ_KotHZ/data/textures/Seachest.paa"};
        itemsCargoSize[] = {10, 50};
        itemSize[] = {10, 10};
        weight = 15000;
        canBeDigged = 0;
        class Cargo
        {
            itemsCargoSize[] = {10, 50};
            openable = 0;
            allowOwnedCargoManipulation = 1;
        };
    };

    class DeutschZKotHZ_DropCrate: DeutschZKotHZ_RewardCrate
    {
        scope = 2;
        displayName = "DeutschZ KotHZ Drop Crate";
    };

    // Active KotHZ flags.
    class DeutschZKotHZ_Flag: Flag_Base
    {
        scope = 1;
        displayName = "DeutschZ KotHZ Flag";
        hiddenSelections[] = {"camo"};
        hiddenSelectionsTextures[] = {"/DeutschZ_KotHZ/data/flags/DeutschZ_KotHZ_Flag.paa"};
        inventorySlot[] = {"Material_FPole_Flag"};
    };

    class DeutschZKotHZ_DeutschZ_KotHZ_Flag: DeutschZKotHZ_Flag { scope = 2; hiddenSelectionsTextures[] = {"/DeutschZ_KotHZ/data/flags/DeutschZ_KotHZ_Flag.paa"}; };
    class DeutschZKotHZ_NWAF_Flag: DeutschZKotHZ_Flag { scope = 2; hiddenSelectionsTextures[] = {"/DeutschZ_KotHZ/data/flags/DeutschZ_KotH_NWAF.paa"}; };
    class DeutschZKotHZ_Tisy_Flag: DeutschZKotHZ_Flag { scope = 2; hiddenSelectionsTextures[] = {"/DeutschZ_KotHZ/data/flags/DeutschZ_KotH_Tisy.paa"}; };
    class DeutschZKotHZ_LOPA_Flag: DeutschZKotHZ_Flag { scope = 2; hiddenSelectionsTextures[] = {"/DeutschZ_KotHZ/data/flags/DeutschZ_KotH_LOPA.paa"}; };
    class DeutschZKotHZ_YRAP_Flag: DeutschZKotHZ_Flag { scope = 2; hiddenSelectionsTextures[] = {"/DeutschZ_KotHZ/data/flags/DeutschZ_KotH_YRAP.paa"}; };
    class DeutschZKotHZ_Basebuild_Flag: DeutschZKotHZ_Flag { scope = 2; hiddenSelectionsTextures[] = {"/DeutschZ_KotHZ/data/flags/DeutschZ_KotH_Basebuild.paa"}; };
    class DeutschZKotHZ_Alt_One_Flag: DeutschZKotHZ_Flag { scope = 2; hiddenSelectionsTextures[] = {"/DeutschZ_KotHZ/data/flags/DeutschZ_Alt_One_Flag.paa"}; };
    class DeutschZKotHZ_Alt_Two_Flag: DeutschZKotHZ_Flag { scope = 2; hiddenSelectionsTextures[] = {"/DeutschZ_KotHZ/data/flags/DeutschZ_Alt_Two_Flag.paa"}; };
    class DeutschZKotHZ_Alt_Three_Flag: DeutschZKotHZ_Flag { scope = 2; hiddenSelectionsTextures[] = {"/DeutschZ_KotHZ/data/flags/DeutschZ_Alt_Three_Flag.paa"}; };

    class DeutschZKotHZ_BiohazardReader: GPSReceiver
    {
        scope = 2;
        displayName = "DeutschZ KotHZ Biohazard Reader";
        descriptionShort = "GPSReceiver based KotHZ card reader.";
        hiddenSelections[] = {"gpsreceiver"};
        hiddenSelectionsTextures[] = {"/DeutschZ_KotHZ/data/textures/CardReader.paa"};
    };

    class DeutschZKotHZ_AccessCard: PunchedCard
    {
        scope = 2;
        displayName = "DeutschZ KotHZ Access Card";
        descriptionShort = "PunchedCard based KotHZ access card.";
        hiddenSelections[] = {"component01"};
        hiddenSelectionsTextures[] = {"/DeutschZ_KotHZ/data/textures/AccesCard.paa"};
    };

    class DeutschZKotHZ_ResearchDocument: Paper
    {
        scope = 2;
        displayName = "DeutschZ KotHZ Research Document";
        descriptionShort = "Classified research document from an Infected Siege zone.";
        weight = 10;
        itemSize[] = {1,1};
    };

    class DeutschZKotHZ_CommanderInsignia: DeutschZKotHZ_AccessCard
    {
        scope = 2;
        displayName = "DeutschZ KotHZ Commander Insignia";
        descriptionShort = "Insignia token dropped by the strongest infected encounter.";
    };
};
