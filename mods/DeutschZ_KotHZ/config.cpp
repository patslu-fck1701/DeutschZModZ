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
        units[] = {"DeutschZKotHZ_RuntimeFlagpole", "DeutschZKotHZ_EventFlagpole", "DeutschZKotHZ_RuntimeFogEmitter", "DeutschZKotHZ_RewardCrate", "DeutschZKotHZ_DropCrate", "DeutschZKotHZ_Flag", "DeutschZKotHZ_Alt_One_Flag", "DeutschZKotHZ_Alt_Two_Flag", "DeutschZKotHZ_Alt_Three_Flag", "DeutschZKotHZ_DeutschZ_KotHZ_Flag", "DeutschZKotHZ_NWAF_Flag", "DeutschZKotHZ_Tisy_Flag", "DeutschZKotHZ_LOPA_Flag", "DeutschZKotHZ_YRAP_Flag", "DeutschZKotHZ_Basebuild_Flag", "DeutschZKotHZ_BiohazardReader", "DeutschZKotHZ_AccessCard", "DeutschZKotHZ_ResearchDocument", "DeutschZKotHZ_CommanderInsignia", "DeutschZKotHZ_MummyHeart", "DeutschZKotHZ_RedMistCore", "DeutschZKotHZ_BunkerOverrideKey", "DeutschZKotHZ_ContaminatedDogtag", "DZ_KotHZ_SiegeToken", "DZ_KotHZ_InfectedSample", "DZ_KotHZ_BossTrophy", "DZ_KotHZ_ControlChip", "DZ_KotHZ_BloodyZBadge", "DeutschZKotHZ_MummyBoss", "DeutschZKotHZ_CivilInfected", "DeutschZKotHZ_HunterInfected", "DeutschZKotHZ_MilitaryInfected"};
        weapons[] = {};
        requiredVersion = 0.1;
        requiredAddons[] = {"DZ_Data", "DZ_Scripts", "DZ_Sounds_Effects", "DZ_Gear_Camping", "DZ_Gear_Containers", "DZ_Gear_Navigation", "DZ_Gear_Consumables", "DZ_Characters_Zombies", "JM_CF_Scripts", "DeutschZ_Core", "DeutschZ_ExpansionBridge"};
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
        version = "2.3.6-fix46-boss-music-items";
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
    class ZmbM_Mummy;
    class ZmbM_CitizenASkinny_Brown;
    class ZmbM_HunterOld_Autumn;
    class ZmbM_usSoldier_Officer_Desert;

    class DeutschZKotHZ_CivilInfected: ZmbM_CitizenASkinny_Brown
    {
        scope = 2;
        displayName = "DeutschZ KotHZ Civil Infected";
        class DamageSystem: DamageSystem
        {
            class GlobalHealth: GlobalHealth
            {
                class Health: Health { hitpoints = 1400; };
            };
        };
    };

    class DeutschZKotHZ_HunterInfected: ZmbM_HunterOld_Autumn
    {
        scope = 2;
        displayName = "DeutschZ KotHZ Hunter Infected";
        class DamageSystem: DamageSystem
        {
            class GlobalHealth: GlobalHealth
            {
                class Health: Health { hitpoints = 1800; };
            };
        };
    };

    class DeutschZKotHZ_MilitaryInfected: ZmbM_usSoldier_Officer_Desert
    {
        scope = 2;
        displayName = "DeutschZ KotHZ Military Infected";
        class DamageSystem: DamageSystem
        {
            class GlobalHealth: GlobalHealth
            {
                class Health: Health { hitpoints = 2500; };
            };
        };
    };

    class DeutschZKotHZ_MummyBoss: ZmbM_Mummy
    {
        scope = 2;
        displayName = "DeutschZ KotHZ Mummy Boss";
        class DamageSystem: DamageSystem
        {
            class GlobalHealth: GlobalHealth
            {
                class Health: Health { hitpoints = 7500; };
            };
            class DamageZones: DamageZones
            {
                class Head: Head { class Health: Health { hitpoints = 3750; }; };
                class Torso: Torso { class Health: Health { hitpoints = 7500; }; };
                class LeftArm: LeftArm { class Health: Health { hitpoints = 7500; }; };
                class RightArm: RightArm { class Health: Health { hitpoints = 7500; }; };
                class LeftLeg: LeftLeg { class Health: Health { hitpoints = 7500; }; };
                class RightLeg: RightLeg { class Health: Health { hitpoints = 7500; }; };
                class LeftFoot: LeftFoot { class Health: Health { hitpoints = 7500; }; };
                class RightFoot: RightFoot { class Health: Health { hitpoints = 7500; }; };
            };
        };
    };

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
        hiddenSelectionsTextures[] = {"\DeutschZ_KotHZ\data\textures\Seachest.paa"};
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
        hiddenSelectionsTextures[] = {"\DeutschZ_KotHZ\data\flags\DeutschZ_KotHZ_Flag.paa"};
        inventorySlot[] = {"Material_FPole_Flag"};
    };

    class DeutschZKotHZ_DeutschZ_KotHZ_Flag: DeutschZKotHZ_Flag { scope = 2; hiddenSelectionsTextures[] = {"\DeutschZ_KotHZ\data\flags\DeutschZ_KotHZ_Flag.paa"}; };
    class DeutschZKotHZ_NWAF_Flag: DeutschZKotHZ_Flag { scope = 2; hiddenSelectionsTextures[] = {"\DeutschZ_KotHZ\data\flags\DeutschZ_KotH_NWAF.paa"}; };
    class DeutschZKotHZ_Tisy_Flag: DeutschZKotHZ_Flag { scope = 2; hiddenSelectionsTextures[] = {"\DeutschZ_KotHZ\data\flags\DeutschZ_KotH_Tisy.paa"}; };
    class DeutschZKotHZ_LOPA_Flag: DeutschZKotHZ_Flag { scope = 2; hiddenSelectionsTextures[] = {"\DeutschZ_KotHZ\data\flags\DeutschZ_KotH_LOPA.paa"}; };
    class DeutschZKotHZ_YRAP_Flag: DeutschZKotHZ_Flag { scope = 2; hiddenSelectionsTextures[] = {"\DeutschZ_KotHZ\data\flags\DeutschZ_KotH_YRAP.paa"}; };
    class DeutschZKotHZ_Basebuild_Flag: DeutschZKotHZ_Flag { scope = 2; hiddenSelectionsTextures[] = {"\DeutschZ_KotHZ\data\flags\DeutschZ_KotH_Basebuild.paa"}; };
    class DeutschZKotHZ_Alt_One_Flag: DeutschZKotHZ_Flag { scope = 2; hiddenSelectionsTextures[] = {"\DeutschZ_KotHZ\data\flags\DeutschZ_Alt_One_Flag.paa"}; };
    class DeutschZKotHZ_Alt_Two_Flag: DeutschZKotHZ_Flag { scope = 2; hiddenSelectionsTextures[] = {"\DeutschZ_KotHZ\data\flags\DeutschZ_Alt_Two_Flag.paa"}; };
    class DeutschZKotHZ_Alt_Three_Flag: DeutschZKotHZ_Flag { scope = 2; hiddenSelectionsTextures[] = {"\DeutschZ_KotHZ\data\flags\DeutschZ_Alt_Three_Flag.paa"}; };

    class DeutschZKotHZ_BiohazardReader: GPSReceiver
    {
        scope = 2;
        displayName = "DeutschZ KotHZ Biohazard Reader";
        descriptionShort = "Versiegelter Biohazard-Reader aus einer KotHZ-Zone. Sichtbares DeutschZ Eventmodell statt normaler GPS-Optik.";
        model = "\DeutschZ_KotHZ\data\items\protector_case.p3d";
        hiddenSelections[] = {"camo"};
        hiddenSelectionsTextures[] = {"\DeutschZ_KotHZ\data\textures\CardReader.paa"};
        itemSize[] = {2, 2};
        weight = 420;
    };

    class DeutschZKotHZ_AccessCard: PunchedCard
    {
        scope = 2;
        displayName = "DeutschZ KotHZ Access Card";
        descriptionShort = "Rote DeutschZ Access-Card im eigenen Eventcase. Hebt sich klar von der normalen PunchedCard ab.";
        model = "\DeutschZ_KotHZ\data\items\protector_case.p3d";
        hiddenSelections[] = {"camo"};
        hiddenSelectionsTextures[] = {"\DeutschZ_KotHZ\data\textures\AccesCard.paa"};
        itemSize[] = {2, 2};
        weight = 180;
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
        descriptionShort = "Rangabzeichen aus der Bossphase. Eigenes rotes DeutschZ Case, nicht mehr die normale Karten-/GPS-Optik.";
        model = "\DeutschZ_KotHZ\data\items\protector_case.p3d";
        hiddenSelections[] = {"camo"};
        hiddenSelectionsTextures[] = {"\DeutschZ_KotHZ\data\items\CommanderInsignia.paa"};
        itemSize[] = {2, 2};
        weight = 240;
    };

    class DeutschZKotHZ_MummyHeart: Inventory_Base
    {
        scope = 2;
        displayName = "DeutschZ KotHZ Mummy-Herz";
        descriptionShort = "Seltenes Boss-Artefakt aus der KotHZ Mummy-Phase. Fuer Trader, Folgequests oder Admin-Rewards nutzbar.";
        model = "\DeutschZ_KotHZ\data\items\protector_case.p3d";
        hiddenSelections[] = {"camo"};
        hiddenSelectionsTextures[] = {"\DeutschZ_KotHZ\data\items\CommanderInsignia.paa"};
        itemSize[] = {2, 2};
        weight = 650;
    };

    class DeutschZKotHZ_RedMistCore: Inventory_Base
    {
        scope = 2;
        displayName = "DeutschZ KotHZ Red-Mist Core";
        descriptionShort = "Instabiler Signalkern aus rotem KotHZ-Nebel. Seltener Technik-Reward fuer High-End-Handel.";
        model = "\DeutschZ_KotHZ\data\items\protector_case.p3d";
        hiddenSelections[] = {"camo"};
        hiddenSelectionsTextures[] = {"\DeutschZ_KotHZ\data\textures\CardReader.paa"};
        itemSize[] = {2, 2};
        weight = 520;
    };

    class DeutschZKotHZ_BunkerOverrideKey: Inventory_Base
    {
        scope = 2;
        displayName = "DeutschZ KotHZ Bunker-Override";
        descriptionShort = "Verschluesselter Override-Key aus einer gesicherten KotHZ-Zone. Premium-Reward fuer spaetere Bunker- oder Traderlogik.";
        model = "\DeutschZ_KotHZ\data\items\protector_case.p3d";
        hiddenSelections[] = {"camo"};
        hiddenSelectionsTextures[] = {"\DeutschZ_KotHZ\data\textures\AccesCard.paa"};
        itemSize[] = {2, 2};
        weight = 310;
    };

    class DeutschZKotHZ_ContaminatedDogtag: Inventory_Base
    {
        scope = 2;
        displayName = "DeutschZ KotHZ Kontaminierte Erkennungsmarke";
        descriptionShort = "Blutige Erkennungsmarke eines gefallenen KotHZ Commanders. Seltener Sammler- und Questgegenstand.";
        model = "\DeutschZ_KotHZ\data\items\protector_case.p3d";
        hiddenSelections[] = {"camo"};
        hiddenSelectionsTextures[] = {"\DeutschZ_KotHZ\data\textures\AccesCard.paa"};
        itemSize[] = {2, 1};
        weight = 120;
    };

    class DZ_KotHZ_SiegeToken: PunchedCard
    {
        scope = 2;
        displayName = "DeutschZ KotHZ Siege-Token";
        descriptionShort = "Event-only Nachweis fuer eine abgeschlossene KotHZ-Belagerung. Fuer Rewards, Adminspawn oder Trader nutzbar; kein normaler Mapspawn.";
        model = "\DeutschZ_KotHZ\data\items\protector_case.p3d";
        hiddenSelections[] = {"camo"};
        hiddenSelectionsTextures[] = {"\DeutschZ_KotHZ\data\textures\AccesCard.paa"};
        itemSize[] = {1, 1};
        weight = 20;
    };

    class DZ_KotHZ_InfectedSample: GPSReceiver
    {
        scope = 2;
        displayName = "DeutschZ KotHZ Infiziertenprobe";
        descriptionShort = "Versiegelte Probe aus einer KotHZ-Zone. Trigger- oder Questitem fuer Infected-Siege-Logik.";
        model = "\DeutschZ_KotHZ\data\items\protector_case.p3d";
        hiddenSelections[] = {"camo"};
        hiddenSelectionsTextures[] = {"\DeutschZ_KotHZ\data\textures\CardReader.paa"};
        itemSize[] = {1, 2};
        weight = 250;
    };

    class DZ_KotHZ_BossTrophy: GPSReceiver
    {
        scope = 2;
        displayName = "DeutschZ KotHZ Boss-Trophaee";
        descriptionShort = "Seltene Trophaee aus der Bossphase. Rewarditem fuer erfolgreiche KotHZ-Abschluesse.";
        model = "\DeutschZ_KotHZ\data\items\protector_case.p3d";
        hiddenSelections[] = {"camo"};
        hiddenSelectionsTextures[] = {"\DeutschZ_KotHZ\data\items\CommanderInsignia.paa"};
        itemSize[] = {2, 2};
        weight = 650;
    };

    class DZ_KotHZ_ControlChip: GPSReceiver
    {
        scope = 2;
        displayName = "DeutschZ KotHZ Kontrollchip";
        descriptionShort = "Technischer Kontrollchip fuer KotHZ-Eventsignale und spaetere Quest-/Adminlogik.";
        model = "\DeutschZ_KotHZ\data\items\protector_case.p3d";
        hiddenSelections[] = {"camo"};
        hiddenSelectionsTextures[] = {"\DeutschZ_KotHZ\data\textures\CardReader.paa"};
        itemSize[] = {1, 1};
        weight = 80;
    };

    class DZ_KotHZ_BloodyZBadge: PunchedCard
    {
        scope = 2;
        displayName = "DeutschZ KotHZ Blutiges Z-Abzeichen";
        descriptionShort = "Blutiges rotes DeutschZ-Abzeichen aus einer KotHZ-Zone. Event-only Sammler- und Rewarditem.";
        model = "\DeutschZ_KotHZ\data\items\protector_case.p3d";
        hiddenSelections[] = {"camo"};
        hiddenSelectionsTextures[] = {"\DeutschZ_KotHZ\data\textures\AccesCard.paa"};
        itemSize[] = {1, 1};
        weight = 35;
    };
};
