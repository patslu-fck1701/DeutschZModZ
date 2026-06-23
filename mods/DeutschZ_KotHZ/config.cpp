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
        version = "0.9.3-online-test";
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
        displayName = "DeutschZ KotHZ Infected Siege Reward Chest";
        descriptionShort = "DeutschZ KotHZ reward chest with custom SeaChest skin.";
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
        displayName = "DeutschZ KotHZ Drop Crate";
    };

    // Active KotHZ flags.
    class DeutschZKotHZ_Flag: Flag_Base
    {
        scope = 1;
        displayName = "DeutschZ KotHZ Flag";
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
        displayName = "DeutschZ KotHZ Biohazard Reader";
        descriptionShort = "GPSReceiver based KotHZ card reader.";
        hiddenSelections[] = {"gpsreceiver"};
        hiddenSelectionsTextures[] = {"DeutschZ_KotHZ/data/textures/CardReader.paa"};
    };

    class DeutschZKotHZ_AccessCard: PunchedCard
    {
        scope = 2;
        displayName = "DeutschZ KotHZ Access Card";
        descriptionShort = "PunchedCard based KotHZ access card.";
        hiddenSelections[] = {"component01", "camo", "zbytek"};
        hiddenSelectionsTextures[] = {"DeutschZ_KotHZ/data/textures/AccesCard.paa", "DeutschZ_KotHZ/data/textures/AccesCard.paa", "DeutschZ_KotHZ/data/textures/AccesCard.paa"};
    };

    class DeutschZKotHZ_ResearchDocument: Paper
    {
        scope = 2;
        displayName = "DeutschZ KotHZ Research Document";
        descriptionShort = "Classified research document from an Infected Siege zone.";
        weight = 10;
        itemSize[] = {1,1};
    };

    class DeutschZKotHZ_CommanderInsignia: GPSReceiver
    {
        scope = 2;
        displayName = "DeutschZ KotHZ Commander Insignia";
        descriptionShort = "Sichtbar ueberarbeitetes rotes DeutschZ Commander-Insignia fuer den Mummy-Boss und KotHZ Rewards. Nutzt bewusst nicht mehr die normale PunchedCard-Optik.";
        hiddenSelections[] = {"gpsreceiver"};
        hiddenSelectionsTextures[] = {"DeutschZ_KotHZ/data/textures/CardReader.paa"};
        itemSize[] = {1, 1};
        weight = 35;
    };

    class DZ_KotHZ_SiegeToken: PunchedCard
    {
        scope = 2;
        displayName = "DeutschZ KotHZ Siege-Token";
        descriptionShort = "Event-only Nachweis fuer eine abgeschlossene KotHZ-Belagerung. Fuer Rewards, Adminspawn oder Trader nutzbar; kein normaler Mapspawn.";
        hiddenSelections[] = {"component01", "camo", "zbytek"};
        hiddenSelectionsTextures[] = {"DeutschZ_KotHZ/data/textures/AccesCard.paa", "DeutschZ_KotHZ/data/textures/AccesCard.paa", "DeutschZ_KotHZ/data/textures/AccesCard.paa"};
        itemSize[] = {1, 1};
        weight = 20;
    };

    class DZ_KotHZ_InfectedSample: GPSReceiver
    {
        scope = 2;
        displayName = "DeutschZ KotHZ Infiziertenprobe";
        descriptionShort = "Versiegelte Probe aus einer KotHZ-Zone. Trigger- oder Questitem fuer Infected-Siege-Logik.";
        hiddenSelections[] = {"gpsreceiver"};
        hiddenSelectionsTextures[] = {"DeutschZ_KotHZ/data/textures/CardReader.paa"};
        itemSize[] = {1, 2};
        weight = 250;
    };

    class DZ_KotHZ_BossTrophy: GPSReceiver
    {
        scope = 2;
        displayName = "DeutschZ KotHZ Boss-Trophaee";
        descriptionShort = "Seltene Trophaee aus der Bossphase. Rewarditem fuer erfolgreiche KotHZ-Abschluesse.";
        hiddenSelections[] = {"gpsreceiver"};
        hiddenSelectionsTextures[] = {"DeutschZ_KotHZ/data/textures/CardReader.paa"};
        itemSize[] = {2, 2};
        weight = 650;
    };

    class DZ_KotHZ_ControlChip: GPSReceiver
    {
        scope = 2;
        displayName = "DeutschZ KotHZ Kontrollchip";
        descriptionShort = "Technischer Kontrollchip fuer KotHZ-Eventsignale und spaetere Quest-/Adminlogik.";
        hiddenSelections[] = {"gpsreceiver"};
        hiddenSelectionsTextures[] = {"DeutschZ_KotHZ/data/textures/CardReader.paa"};
        itemSize[] = {1, 1};
        weight = 80;
    };

    class DZ_KotHZ_BloodyZBadge: PunchedCard
    {
        scope = 2;
        displayName = "DeutschZ KotHZ Blutiges Z-Abzeichen";
        descriptionShort = "Blutiges rotes DeutschZ-Abzeichen aus einer KotHZ-Zone. Event-only Sammler- und Rewarditem.";
        hiddenSelections[] = {"component01", "camo", "zbytek"};
        hiddenSelectionsTextures[] = {"DeutschZ_KotHZ/data/textures/AccesCard.paa", "DeutschZ_KotHZ/data/textures/AccesCard.paa", "DeutschZ_KotHZ/data/textures/AccesCard.paa"};
        itemSize[] = {1, 1};
        weight = 35;
    };
};
