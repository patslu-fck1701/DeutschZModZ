/*
    DeutschZ ModZ
    Autor/Eigentuemer: Patrick Sluzalek / fck1701
    Projekt: DeutschZ
    Zweck: Eigene DeutschZ-Implementierung fuer Core, ExpansionBridge und Event-Module.
    Quellen-/Konzeptnachweis: Eigenentwickelte Struktur; DayZ, CF und Expansion nur als Laufzeit-API/Abhaengigkeit.
    No-Copy-Bestaetigung: Kein Code, keine Assets und keine Configs aus fremden Mods kopiert.
*/

class DeutschZCore_Constants
{
    static const string ROOT_PROFILE = "$profile:DeutschZ/";
    static const string LOG_PROFILE = "$profile:DeutschZ/Logs/";
    static const string BACKUP_FOLDER = "Backups/";
    static const string CONFIG_FOLDER = "Config/";
    static const string STATE_FOLDER = "State/";
    static const int RPC_BASE = 482000;
    static const int RPC_RATE_WINDOW_MS = 1000;
    static const int RPC_DEFAULT_LIMIT = 4;
}
