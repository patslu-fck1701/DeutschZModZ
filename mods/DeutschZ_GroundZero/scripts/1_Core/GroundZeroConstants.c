/*
    DeutschZ_GroundZero
    Owner: Patrick Sluzalek / fck1701
    Module: 1_Core / GroundZeroConstants
    Purpose: Shared constants, profile paths, RPC ids and fixed notification texts.
    Dependencies: DayZ scripts; optional CF/Expansion APIs only through adapter methods.
    Compliance: Original DeutschZ implementation. No copied foreign mod code, assets, configs or stubs.
*/

class GroundZeroConstants
{
    static const string MOD_NAME = "DeutschZ_GroundZero";
    static const string VERSION = "0.4.0-source";

    static const string PROFILE_ROOT = "$profile:DeutschZ/";
    static const string PROFILE_DIR = "$profile:DeutschZ/GroundZero/";
    static const string CONFIG_PATH = "$profile:DeutschZ/GroundZero/GroundZeroConfig.json";
    static const string STATE_PATH = "$profile:DeutschZ/GroundZero/GroundZeroState.json";
    static const string STATE_BACKUP_PATH = "$profile:DeutschZ/GroundZero/GroundZeroState.backup.json";
    static const string LOG_DIR = "$profile:DeutschZ/Logs/";
    static const string LOG_PATH = "$profile:DeutschZ/Logs/GroundZero.log";

    static const int RPC_RETRY_REQUEST = 7303101;
    static const int RPC_ABORT_REQUEST = 7303102;
    static const int RPC_DEATH_MENU = 7303103;
    static const int RPC_ADMIN_START_REQUEST = 7303104;

    static const string MSG_COMPONENT_DISCOVERED = "Kritische Komponente entdeckt";
    static const string MSG_COMPONENTS_MERGED = "Mehrere Komponenten wurden vereint";
    static const string MSG_CARRIER_LOCATED = "Carrier lokalisiert";
    static const string MSG_FINAL_AVAILABLE = "Finale Sequenz verfügbar";
    static const string MSG_COMPONENT_LOST = "Kritische Komponente verloren";

    static const string LOG_CAT_SECURITY = "Security";
    static const string LOG_CAT_EVENT = "Event";
    static const string LOG_CAT_STAGE = "Stage";
    static const string LOG_CAT_RETRY = "Retry";
}
