class CfgPatches
{
    class DeutschZ_Core
    {
        units[] = {"DZ_EventToken", "DZ_BossDogtag", "DZ_RedZChip", "DZ_BrokenTransmitter", "DZ_BloodSample", "DZ_ContainmentSeal", "DZ_TacticalCase", "DZ_RewardKey", "DZ_SupplyVoucher", "DZ_HazardCanister", "DZ_MilitaryLedger", "DZ_SecureSSD", "DZ_FieldNote", "DZ_AccessFuse", "DZ_SignalBattery", "DZ_RadioCrystal", "DZ_EventCore", "DZ_RedSmokeBeacon"};
        weapons[] = {};
        requiredVersion = 0.1;
        requiredAddons[] = {"DZ_Data", "DZ_Scripts", "DZ_Gear_Containers", "DZ_Gear_Navigation", "DZ_Gear_Consumables", "DZ_Gear_Medical", "DZ_Gear_Tools", "DZ_Radio"};
    };
};

class CfgVehicles
{
    class Paper;
    class PunchedCard;
    class GPSReceiver;
    class SmallProtectorCase;
    class Battery9V;
    class BloodTestKit;
    class GasMask_Filter;
    class PersonalRadio;
    class ElectronicRepairKit;

    class DZ_EventToken: PunchedCard
    {
        scope = 2;
        displayName = "DeutschZ Event-Token";
        descriptionShort = "Globaler DeutschZ Event-Token fuer Rewards, Adminspawn und Trader. Event-only, kein normaler Mapspawn.";
        itemSize[] = {1, 1};
        weight = 20;
    };

    class DZ_BossDogtag: PunchedCard
    {
        scope = 2;
        displayName = "DeutschZ Boss-Erkennungsmarke";
        descriptionShort = "Trophy-Token fuer Bosskills und besondere Eventabschluesse.";
        itemSize[] = {1, 1};
        weight = 30;
    };

    class DZ_RedZChip: GPSReceiver
    {
        scope = 2;
        displayName = "DeutschZ Roter Z-Chip";
        descriptionShort = "Technischer DeutschZ-Chip fuer Trigger, Questketten und Eventsignale.";
        itemSize[] = {1, 1};
        weight = 60;
    };

    class DZ_BrokenTransmitter: PersonalRadio
    {
        scope = 2;
        displayName = "DeutschZ defekter Sender";
        descriptionShort = "Beschaedigter Funksender aus einer Eventzone. Als Signal-, Quest- oder Traderitem nutzbar.";
        itemSize[] = {2, 2};
        weight = 550;
    };

    class DZ_BloodSample: BloodTestKit
    {
        scope = 2;
        displayName = "DeutschZ Blutprobe";
        descriptionShort = "Gesicherte Probe aus einem DeutschZ-Event. Event-only und fuer medizinische Questlogik vorbereitet.";
        itemSize[] = {1, 1};
        weight = 120;
    };

    class DZ_ContainmentSeal: GasMask_Filter
    {
        scope = 2;
        displayName = "DeutschZ Containment-Siegel";
        descriptionShort = "Versiegeltes Kontaminationsbauteil fuer GroundZero-, NBC- oder Triggerlogik.";
        itemSize[] = {1, 2};
        weight = 180;
    };

    class DZ_TacticalCase: SmallProtectorCase
    {
        scope = 2;
        displayName = "DeutschZ taktischer Eventkoffer";
        descriptionShort = "Robuster Eventkoffer fuer sichere Belohnungen, Zielobjekte und Adminspawn.";
        itemSize[] = {4, 3};
        weight = 2600;
        canBeSplit = 0;
    };

    class DZ_RewardKey: PunchedCard
    {
        scope = 2;
        displayName = "DeutschZ Reward-Schluessel";
        descriptionShort = "Schluessel-/Tokenitem fuer Eventbelohnungen. Event-only, kein normaler Mapspawn.";
        itemSize[] = {1, 1};
        weight = 15;
    };

    class DZ_SupplyVoucher: Paper
    {
        scope = 2;
        displayName = "DeutschZ Versorgungsgutschein";
        descriptionShort = "Einloesbares Eventdokument fuer Versorgung, Trader oder Adminbelohnung.";
        itemSize[] = {1, 2};
        weight = 20;
    };

    class DZ_HazardCanister: GasMask_Filter
    {
        scope = 2;
        displayName = "DeutschZ Gefahrstoffkanister";
        descriptionShort = "Kleiner versiegelter Gefahrstoffbehaelter fuer kontaminierte Eventketten.";
        itemSize[] = {2, 2};
        weight = 900;
    };

    class DZ_MilitaryLedger: Paper
    {
        scope = 2;
        displayName = "DeutschZ Militaer-Ledger";
        descriptionShort = "Militaerisches Register mit Eventrouten, Ladungen und Zielcodes.";
        itemSize[] = {1, 2};
        weight = 35;
    };

    class DZ_SecureSSD: GPSReceiver
    {
        scope = 2;
        displayName = "DeutschZ Secure SSD";
        descriptionShort = "Verschluesselter Datentraeger fuer High-Value-Events und Missionsketten.";
        itemSize[] = {1, 1};
        weight = 80;
    };

    class DZ_FieldNote: Paper
    {
        scope = 2;
        displayName = "DeutschZ Feldnotiz";
        descriptionShort = "Kurze Feldnotiz aus einer Eventzone. Quest-, Lore- oder Traderitem.";
        itemSize[] = {1, 1};
        weight = 10;
    };

    class DZ_AccessFuse: ElectronicRepairKit
    {
        scope = 2;
        displayName = "DeutschZ Zugangssicherung";
        descriptionShort = "Elektronische Sicherung fuer Eventgeraete, Kisten und Triggerlogik.";
        itemSize[] = {1, 2};
        weight = 180;
    };

    class DZ_SignalBattery: Battery9V
    {
        scope = 2;
        displayName = "DeutschZ Signalbatterie";
        descriptionShort = "Spezielle Batterie fuer Signalstation, Beacons und Eventtechnik.";
        itemSize[] = {1, 1};
        weight = 70;
    };

    class DZ_RadioCrystal: GPSReceiver
    {
        scope = 2;
        displayName = "DeutschZ Funkkristall";
        descriptionShort = "Kalibrierter Kristall fuer Funk-, Signal- und Broadcast-Events.";
        itemSize[] = {1, 1};
        weight = 45;
    };

    class DZ_EventCore: GPSReceiver
    {
        scope = 2;
        displayName = "DeutschZ Event-Core";
        descriptionShort = "Zentrales technisches Kernmodul fuer hochwertige Eventketten.";
        itemSize[] = {2, 2};
        weight = 800;
    };

    class DZ_RedSmokeBeacon: PersonalRadio
    {
        scope = 2;
        displayName = "DeutschZ roter Smoke-Beacon";
        descriptionShort = "Event-only Signalgeraet fuer sichtbare, config-gated Eventmarkierung.";
        itemSize[] = {2, 2};
        weight = 650;
    };
};

class CfgMods
{
    class DeutschZ_Core
    {
        dir = "DeutschZ_Core";
        name = "DeutschZ Core";
        author = "Patrick Sluzalek / fck1701";
        type = "mod";
        dependencies[] = {"Game", "World", "Mission"};
        class defs
        {
            class gameScriptModule
            {
                value = "";
                files[] = {"DeutschZ_Core/scripts/3_Game"};
            };
            class worldScriptModule
            {
                value = "";
                files[] = {"DeutschZ_Core/scripts/4_World"};
            };
            class missionScriptModule
            {
                value = "";
                files[] = {"DeutschZ_Core/scripts/5_Mission"};
            };
        };
    };
};
