class CfgPatches
{
    class Konfliktzone_SprinterSkins
    {
        units[] =
        {
            "KZ_Sprinter_Admin_Cargo_KA01",
            "KZ_Sprinter_Admin_Cargo_KA02",
            "KZ_Sprinter_doors_driver_Admin",
            "KZ_Sprinter_doors_codriver_Admin",
            "KZ_Sprinter_doors_cargo1_Admin",
            "KZ_Sprinter_doors_cargo2_Admin",
            "KZ_Sprinter_doors_cargo3_Admin"
        };
        weapons[] = {};
        requiredVersion = 0.1;
        requiredAddons[] =
        {
            "DZ_Data",
            "DZ_Vehicles_Wheeled",
            "MBM_Sprinter"
        };
    };
};

class CfgMods
{
    class Konfliktzone_SprinterSkins
    {
        dir = "Konfliktzone_SprinterSkins";
        picture = "";
        action = "https://discord.gg/tRtSbWtrsm";
        hideName = 0;
        hidePicture = 0;
        name = "Konfliktzone Sprinter Skins";
        credits = "Retexture idea and permission: Einarvargr / Konfliktzone; technical execution: Patrick Sluzalek / fck1701 / DeutschZ";
        author = "Einarvargr / Konfliktzone; technical assistance by Patrick Sluzalek / fck1701";
        authorID = "";
        version = "0.1.0-admin-cargo";
        extra = 0;
        type = "mod";
        dependencies[] = {};
    };
};

class CfgVehicles
{
    class MBM_Sprinter_BlackCargo;
    class MBM_Sprinter_doors_driver_BlackCargo;
    class MBM_Sprinter_doors_codriver_BlackCargo;
    class MBM_Sprinter_doors_cargo1_BlackCargo;
    class MBM_Sprinter_doors_cargo2_BlackCargo;
    class MBM_Sprinter_doors_cargo3_BlackCargo;

    class KZ_Sprinter_doors_driver_Admin: MBM_Sprinter_doors_driver_BlackCargo
    {
        scope = 2;
        displayName = "Konfliktzone Admin Driver Door";
        hiddenSelections[] = {"camo"};
        hiddenSelectionsTextures[] =
        {
            "MBM_MercedesSprinter\data\body_red.paa"
        };
    };

    class KZ_Sprinter_doors_codriver_Admin: MBM_Sprinter_doors_codriver_BlackCargo
    {
        scope = 2;
        displayName = "Konfliktzone Admin Co-Driver Door";
        hiddenSelections[] = {"camo"};
        hiddenSelectionsTextures[] =
        {
            "MBM_MercedesSprinter\data\body_red.paa"
        };
    };

    class KZ_Sprinter_doors_cargo1_Admin: MBM_Sprinter_doors_cargo1_BlackCargo
    {
        scope = 2;
        displayName = "Konfliktzone Admin Cargo Door 1";
        hiddenSelections[] = {"camo", "camo_rear_glass"};
        hiddenSelectionsTextures[] =
        {
            "MBM_MercedesSprinter\data\body_red.paa",
            "MBM_MercedesSprinter\data\body_red.paa"
        };
    };

    class KZ_Sprinter_doors_cargo2_Admin: MBM_Sprinter_doors_cargo2_BlackCargo
    {
        scope = 2;
        displayName = "Konfliktzone Admin Cargo Door 2";
        hiddenSelections[] = {"camo", "camo_rear_glass"};
        hiddenSelectionsTextures[] =
        {
            "MBM_MercedesSprinter\data\body_red.paa",
            "MBM_MercedesSprinter\data\body_red.paa"
        };
    };

    class KZ_Sprinter_doors_cargo3_Admin: MBM_Sprinter_doors_cargo3_BlackCargo
    {
        scope = 2;
        displayName = "Konfliktzone Admin Cargo Door 3";
        hiddenSelections[] = {"camo", "camo_rear_glass"};
        hiddenSelectionsTextures[] =
        {
            "MBM_MercedesSprinter\data\body_red.paa",
            "MBM_MercedesSprinter\data\body_red.paa"
        };
    };

    class KZ_Sprinter_Admin_Cargo_KA01: MBM_Sprinter_BlackCargo
    {
        scope = 2;
        displayName = "Konfliktzone Admin Cargo KA/01";
        descriptionShort = "Konfliktzone Admin Response Car KA/01";

        hiddenSelections[] =
        {
            "light_1_1",
            "light_2_1",
            "light_brake_1_2",
            "light_brake_2_2",
            "light_reverse_1_2",
            "light_reverse_2_2",
            "light_1_2",
            "light_2_2",
            "light_dashboard",
            "light_dashboard2",
            "light_dashboard3",
            "light_taillight",
            "camo_body",
            "camo_rear_glass",
            "camo_decal_body",
            "camo_decal_windshield"
        };
        hiddenSelectionsTextures[] =
        {
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "MBM_MercedesSprinter\data\body_red.paa",
            "MBM_MercedesSprinter\data\body_red.paa",
            "Konfliktzone_SprinterSkins\data\kz_admin_decal_sides_lr.paa",
            "Konfliktzone_SprinterSkins\data\kz_admin_decal_rear_window.paa"
        };
    };

    class KZ_Sprinter_Admin_Cargo_KA02: KZ_Sprinter_Admin_Cargo_KA01
    {
        scope = 2;
        displayName = "Konfliktzone Admin Cargo KA/02";
        descriptionShort = "Konfliktzone Admin Response Car KA/02";
    };
};
