/*
DeutschZ ModZ
Eigenstaendige Implementierung fuer DeutschZ.
Autor/Eigentuemer: Patrick Sluzalek / fck1701.
Projekt: DeutschZ.
Modul: DeutschZ_ConvoyZ.
Zweck der Datei: Eigene DeutschZ-Datei fuer ConvoyZ.
Quellen-/Konzeptnachweis: Eigene DeutschZ-Implementierung; DayZ/CF/Expansion werden nur als Laufzeit-Abhaengigkeit/API genutzt.
Keine direkte Codeuebernahme aus Drittquellen.
*/

class DeutschZConvoyZConstants
{
    static const string PROFILE_ROOT = "$profile:DeutschZ/ConvoyZ/";
    static const string SETTINGS_FILE = "$profile:DeutschZ/ConvoyZ/Settings.json";
    static const string EVENTS_FILE = "$profile:DeutschZ/ConvoyZ/Events.json";
    static const string DATA_DIR = "$profile:DeutschZ/ConvoyZ/Data/";
    static const string LOG_DIR = "$profile:DeutschZ/ConvoyZ/Logs/";
    static const string CLAIMS_FILE = "$profile:DeutschZ/ConvoyZ/Data/RewardClaims.json";

    static const int RPC_REQUEST_STATUS = 7822001;
    static const int RPC_HACK_START = 7822002;
    static const int RPC_HACK_STOP = 7822003;
    static const int RPC_STATUS_SYNC = 7822004;

    static const int STATE_NONE = 0;
    static const int STATE_SPAWNING = 1;
    static const int STATE_SECURE_AREA = 2;
    static const int STATE_BLACKBOX_READY = 3;
    static const int STATE_HACKING = 4;
    static const int STATE_REWARD_UNLOCKED = 5;
    static const int STATE_CLEANUP = 6;
    static const int STATE_FAILED = 7;

    static const string SMOKE_RED = "RED";
    static const string SMOKE_YELLOW = "YELLOW";
    static const string SMOKE_GREEN = "GREEN";
    static const string SMOKE_WHITE = "WHITE";

    static const string DEFAULT_EXPANSION_AI_CLASS = "ZmbM_usSoldier_Officer_Desert";
}

string DeutschZConvoyZ_StateName(int state)
{
    if (state == DeutschZConvoyZConstants.STATE_SPAWNING) return "SPAWNING";
    if (state == DeutschZConvoyZConstants.STATE_SECURE_AREA) return "SECURE_AREA";
    if (state == DeutschZConvoyZConstants.STATE_BLACKBOX_READY) return "BLACKBOX_READY";
    if (state == DeutschZConvoyZConstants.STATE_HACKING) return "HACKING";
    if (state == DeutschZConvoyZConstants.STATE_REWARD_UNLOCKED) return "REWARD_UNLOCKED";
    if (state == DeutschZConvoyZConstants.STATE_CLEANUP) return "CLEANUP";
    if (state == DeutschZConvoyZConstants.STATE_FAILED) return "FAILED";
    return "NONE";
}
