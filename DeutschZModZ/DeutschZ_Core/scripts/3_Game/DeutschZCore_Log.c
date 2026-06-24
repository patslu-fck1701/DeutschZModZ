/*
    DeutschZ ModZ
    Autor/Eigentuemer: Patrick Sluzalek / fck1701
    Projekt: DeutschZ
    Zweck: Eigene DeutschZ-Implementierung fuer Core, ExpansionBridge und Event-Module.
    Quellen-/Konzeptnachweis: Eigenentwickelte Struktur; DayZ, CF und Expansion nur als Laufzeit-API/Abhaengigkeit.
    No-Copy-Bestaetigung: Kein Code, keine Assets und keine Configs aus fremden Mods kopiert.
*/

class DeutschZCore_Log
{
    static void EnsureFolders()
    {
        MakeDirectory(DeutschZCore_Constants.ROOT_PROFILE);
        MakeDirectory(DeutschZCore_Constants.LOG_PROFILE);
    }

    static void Info(string scopeName, string message)
    {
        Print("[DeutschZ][" + scopeName + "] " + message);
    }

    static void Warn(string scopeName, string message)
    {
        Print("[DeutschZ][WARN][" + scopeName + "] " + message);
    }

    static void Error(string scopeName, string message)
    {
        Print("[DeutschZ][ERROR][" + scopeName + "] " + message);
    }
}
