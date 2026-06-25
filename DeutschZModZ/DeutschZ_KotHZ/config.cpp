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
        units[] = {"DeutschZKotHZ_RuntimeFlagpole", "DeutschZKotHZ_EventFlagpole", "DeutschZKotHZ_RuntimeFogEmitter", "DeutschZKotHZ_RewardCrate", "DeutschZKotHZ_DropCrate", "DeutschZKotHZ_Flag", "DeutschZKotHZ_Alt_One_Flag", "DeutschZKotHZ_Alt_Two_Flag", "DeutschZKotHZ_Alt_Three_Flag", "DeutschZKotHZ_DeutschZ_KotHZ_Flag", "DeutschZKotHZ_NWAF_Flag", "DeutschZKotHZ_Tisy_Flag", "DeutschZKotHZ_LOPA_Flag", "DeutschZKotHZ_YRAP_Flag", "DeutschZKotHZ_Basebuild_Flag", "DeutschZKotHZ_BiohazardReader", "DeutschZKotHZ_AccessCard", "DeutschZKotHZ_ResearchDocument", "DeutschZKotHZ_CommanderInsignia", "DZ_KotHZ_SiegeToken", "DZ_KotHZ_InfectedSample", "DZ_KotHZ_BossTrophy", "DZ_KotHZ_ControlChip", "DZ_KotHZ_BloodyZBadge"};
        weapons[] = {};
        requiredVersion = 0.1;
        requiredAddons[] = {"DZ_Data", "DZ_Scripts", "DZ_Sounds_Effects", "DZ_Gear_Camping", "DZ_Gear_Containers", "DZ_Gear_Navigation", "DZ_Gear_Consumables", "DeutschZ_Core"};
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
        version = "0.9.4-fix45-core-event-lock";
        extra = 0;
        type = "mod";
        defines[] = {"DEUTSCHZ_KotHZ"};

        dependencies[] = {"Game", "World", "Mission"};

        class defs
        {
            class gameScriptModule
            {
                value = "";
                files[] = {"DeutschZ_KotHZ/scripts/3_Game", "scripts/3_Game"};
            };
            class worldScriptModule
            {
                value = "";
                files[] = {"DeutschZ_KotHZ/scripts/4_World", "scripts/4_World"};
            };
            class missionScriptModule
            {
                value = "";
                files[] = {"DeutschZ_KotHZ/scripts/5_Mission", "scripts/5_Mission"};
            };
        };
    };
};

class CfgSoundShaders
{
    class DeutschZ_KotHZ_EventMusic_SoundShader
    {
        samples[] =
        {
            {"DeutschZ_KotHZ/data/sounds/DeutschZ_KotHZ_RoterRauch", 1}
        };
        volume = 0.55;
        range = 180;
        rangeCurve[] =
        {
            {0, 1},
            {0.35, 0.75},
            {0.7, 0.35},
            {1, 0}
        };
    };
};

class CfgSoundSets
{
    class DeutschZ_KotHZ_EventMusic_SoundSet
    {
        soundShaders[] = {"DeutschZ_KotHZ_EventMusic_SoundShader"};
        volumeFactor = 1.0;
        frequencyFactor = 1.0;
        spatial = 1;
        loop = 0;
        sound3DProcessingType = "default3DProcessingType";
        distanceFilter = "defaultDistanceFilter";
        volumeCurve = "defaultAttenuationCurve";
    };
};

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
        displayName = "$STR_DZKOTHZ_DZKOTHZ_RUNTIMEFOGEMITTER_NAME";
        descriptionShort = "$STR_DZKOTHZ_DZKOTHZ_RUNTIMEFOGEMITTER_DESC";
        model = "\DZ\gear\consumables\Stone.p3d";
        itemSize[] = {1,1};
        weight = 1;
        physLayer = "item_small";
    };

    class DeutschZKotHZ_RuntimeFlagpole: Inventory_Base
    {
        scope = 2;
        displayName = "$STR_DZKOTHZ_DZKOTHZ_RUNTIMEFLAGPOLE_NAME";
        descriptionShort = "$STR_DZKOTHZ_DZKOTHZ_RUNTIMEFLAGPOLE_DESC";
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
        displayName = "$STR_DZKOTHZ_DZKOTHZ_REWARDCRATE_NAME";
        descriptionShort = "$STR_DZKOTHZ_DZKOTHZ_REWARDCRATE_DESC";
        hiddenSelections[] = {"camoGround"};
        hiddenSelectionsTextures[] = {"DeutschZ_KotHZ/data/textures/Seachest.paa"};
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
        displayName = "$STR_DZKOTHZ_DZKOTHZ_DROPCRATE_NAME";
    };

    // Active KotHZ flags.
    class DeutschZKotHZ_Flag: Flag_Base
    {
        scope = 1;
        displayName = "$STR_DZKOTHZ_DZKOTHZ_FLAG_NAME";
        hiddenSelections[] = {"camo"};
        hiddenSelectionsTextures[] = {"DeutschZ_KotHZ/data/flags/DeutschZ_KotHZ_Flag.paa"};
        inventorySlot[] = {"Material_FPole_Flag"};
    };

    class DeutschZKotHZ_DeutschZ_KotHZ_Flag: DeutschZKotHZ_Flag { scope = 2; hiddenSelectionsTextures[] = {"DeutschZ_KotHZ/data/flags/DeutschZ_KotHZ_Flag.paa"}; };
    class DeutschZKotHZ_NWAF_Flag: DeutschZKotHZ_Flag { scope = 2; hiddenSelectionsTextures[] = {"DeutschZ_KotHZ/data/flags/DeutschZ_KotH_NWAF.paa"}; };
    class DeutschZKotHZ_Tisy_Flag: DeutschZKotHZ_Flag { scope = 2; hiddenSelectionsTextures[] = {"DeutschZ_KotHZ/data/flags/DeutschZ_KotH_Tisy.paa"}; };
    class DeutschZKotHZ_LOPA_Flag: DeutschZKotHZ_Flag { scope = 2; hiddenSelectionsTextures[] = {"DeutschZ_KotHZ/data/flags/DeutschZ_KotH_LOPA.paa"}; };
    class DeutschZKotHZ_YRAP_Flag: DeutschZKotHZ_Flag { scope = 2; hiddenSelectionsTextures[] = {"DeutschZ_KotHZ/data/flags/DeutschZ_KotH_YRAP.paa"}; };
    class DeutschZKotHZ_Basebuild_Flag: DeutschZKotHZ_Flag { scope = 2; hiddenSelectionsTextures[] = {"DeutschZ_KotHZ/data/flags/DeutschZ_KotH_Basebuild.paa"}; };
    class DeutschZKotHZ_Alt_One_Flag: DeutschZKotHZ_Flag { scope = 2; hiddenSelectionsTextures[] = {"DeutschZ_KotHZ/data/flags/DeutschZ_Alt_One_Flag.paa"}; };
    class DeutschZKotHZ_Alt_Two_Flag: DeutschZKotHZ_Flag { scope = 2; hiddenSelectionsTextures[] = {"DeutschZ_KotHZ/data/flags/DeutschZ_Alt_Two_Flag.paa"}; };
    class DeutschZKotHZ_Alt_Three_Flag: DeutschZKotHZ_Flag { scope = 2; hiddenSelectionsTextures[] = {"DeutschZ_KotHZ/data/flags/DeutschZ_Alt_Three_Flag.paa"}; };

    class DeutschZKotHZ_BiohazardReader: GPSReceiver
    {
        scope = 2;
        displayName = "$STR_DZKOTHZ_DZKOTHZ_BIOHAZARDREADER_NAME";
        descriptionShort = "$STR_DZKOTHZ_DZKOTHZ_BIOHAZARDREADER_DESC";
        hiddenSelections[] = {"gpsreceiver"};
        hiddenSelectionsTextures[] = {"DeutschZ_KotHZ/data/textures/CardReader.paa"};
    };

    class DeutschZKotHZ_AccessCard: PunchedCard
    {
        scope = 2;
        displayName = "$STR_DZKOTHZ_DZKOTHZ_ACCESSCARD_NAME";
        descriptionShort = "$STR_DZKOTHZ_DZKOTHZ_ACCESSCARD_DESC";
        hiddenSelections[] = {"component01", "camo", "zbytek"};
        hiddenSelectionsTextures[] = {"DeutschZ_KotHZ/data/textures/AccesCard.paa", "DeutschZ_KotHZ/data/textures/AccesCard.paa", "DeutschZ_KotHZ/data/textures/AccesCard.paa"};
    };

    class DeutschZKotHZ_ResearchDocument: Paper
    {
        scope = 2;
        displayName = "$STR_DZKOTHZ_DZKOTHZ_RESEARCHDOCUMENT_NAME";
        descriptionShort = "$STR_DZKOTHZ_DZKOTHZ_RESEARCHDOCUMENT_DESC";
        weight = 10;
        itemSize[] = {1,1};
    };

    class DeutschZKotHZ_CommanderInsignia: GPSReceiver
    {
        scope = 2;
        displayName = "$STR_DZKOTHZ_DZKOTHZ_COMMANDERINSIGNIA_NAME";
        descriptionShort = "$STR_DZKOTHZ_DZKOTHZ_COMMANDERINSIGNIA_DESC";
        hiddenSelections[] = {"gpsreceiver"};
        hiddenSelectionsTextures[] = {"DeutschZ_KotHZ/data/textures/CardReader.paa"};
        itemSize[] = {1, 1};
        weight = 35;
    };

    class DZ_KotHZ_SiegeToken: PunchedCard
    {
        scope = 2;
        displayName = "$STR_DZKOTHZ_DZ_KOTHZ_SIEGETOKEN_NAME";
        descriptionShort = "$STR_DZKOTHZ_DZ_KOTHZ_SIEGETOKEN_DESC";
        hiddenSelections[] = {"component01", "camo", "zbytek"};
        hiddenSelectionsTextures[] = {"DeutschZ_KotHZ/data/textures/AccesCard.paa", "DeutschZ_KotHZ/data/textures/AccesCard.paa", "DeutschZ_KotHZ/data/textures/AccesCard.paa"};
        itemSize[] = {1, 1};
        weight = 20;
    };

    class DZ_KotHZ_InfectedSample: GPSReceiver
    {
        scope = 2;
        displayName = "$STR_DZKOTHZ_DZ_KOTHZ_INFECTEDSAMPLE_NAME";
        descriptionShort = "$STR_DZKOTHZ_DZ_KOTHZ_INFECTEDSAMPLE_DESC";
        hiddenSelections[] = {"gpsreceiver"};
        hiddenSelectionsTextures[] = {"DeutschZ_KotHZ/data/textures/CardReader.paa"};
        itemSize[] = {1, 2};
        weight = 250;
    };

    class DZ_KotHZ_BossTrophy: GPSReceiver
    {
        scope = 2;
        displayName = "$STR_DZKOTHZ_DZ_KOTHZ_BOSSTROPHY_NAME";
        descriptionShort = "$STR_DZKOTHZ_DZ_KOTHZ_BOSSTROPHY_DESC";
        hiddenSelections[] = {"gpsreceiver"};
        hiddenSelectionsTextures[] = {"DeutschZ_KotHZ/data/textures/CardReader.paa"};
        itemSize[] = {2, 2};
        weight = 650;
    };

    class DZ_KotHZ_ControlChip: GPSReceiver
    {
        scope = 2;
        displayName = "$STR_DZKOTHZ_DZ_KOTHZ_CONTROLCHIP_NAME";
        descriptionShort = "$STR_DZKOTHZ_DZ_KOTHZ_CONTROLCHIP_DESC";
        hiddenSelections[] = {"gpsreceiver"};
        hiddenSelectionsTextures[] = {"DeutschZ_KotHZ/data/textures/CardReader.paa"};
        itemSize[] = {1, 1};
        weight = 80;
    };

    class DZ_KotHZ_BloodyZBadge: PunchedCard
    {
        scope = 2;
        displayName = "$STR_DZKOTHZ_DZ_KOTHZ_BLOODYZBADGE_NAME";
        descriptionShort = "$STR_DZKOTHZ_DZ_KOTHZ_BLOODYZBADGE_DESC";
        hiddenSelections[] = {"component01", "camo", "zbytek"};
        hiddenSelectionsTextures[] = {"DeutschZ_KotHZ/data/textures/AccesCard.paa", "DeutschZ_KotHZ/data/textures/AccesCard.paa", "DeutschZ_KotHZ/data/textures/AccesCard.paa"};
        itemSize[] = {1, 1};
        weight = 35;
    };
};
