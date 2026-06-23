/*
    DeutschZ_CourierZ - 3_Game constants.
    Original DeutschZ implementation. No copied foreign mod code.
*/

class CourierZConstants
{
    static const string PROFILE_ROOT = "$profile:DeutschZ/CourierZ/";
    static const string CONFIG_DIR = "$profile:DeutschZ/CourierZ/Config/";
    static const string DATA_DIR = "$profile:DeutschZ/CourierZ/Data/";
    static const string LOG_DIR = "$profile:DeutschZ/CourierZ/Logs/";
    static const string CONFIG_PATH = "$profile:DeutschZ/CourierZ/CourierZConfig.json";
    static const string STATE_PATH = "$profile:DeutschZ/CourierZ/CourierZState.json";
    static const string BACKUP_PATH = "$profile:DeutschZ/CourierZ/CourierZState.backup.json";
    static const string LOG_SCOPE = "CourierZ";

    static const int STATE_IDLE = 0;
    static const int STATE_SCHEDULED = 1;
    static const int STATE_WAITING_FOR_CARRIER = 2;
    static const int STATE_IN_TRANSIT = 3;
    static const int STATE_DELIVERED = 4;
    static const int STATE_FAILED = 5;
    static const int STATE_CLEANUP = 6;
}

string CourierZ_StateName(int state)
{
    if (state == CourierZConstants.STATE_SCHEDULED) return "SCHEDULED";
    if (state == CourierZConstants.STATE_WAITING_FOR_CARRIER) return "WAITING_FOR_CARRIER";
    if (state == CourierZConstants.STATE_IN_TRANSIT) return "IN_TRANSIT";
    if (state == CourierZConstants.STATE_DELIVERED) return "DELIVERED";
    if (state == CourierZConstants.STATE_FAILED) return "FAILED";
    if (state == CourierZConstants.STATE_CLEANUP) return "CLEANUP";
    return "IDLE";
}
