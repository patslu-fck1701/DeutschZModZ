/*
    DeutschZ ModZ
    Autor/Eigentuemer: Patrick Sluzalek / fck1701
    Projekt: DeutschZ
    Zweck: Eigene DeutschZ-Implementierung fuer Core, ExpansionBridge und Event-Module.
    Quellen-/Konzeptnachweis: Eigenentwickelte Struktur; DayZ, CF und Expansion nur als Laufzeit-API/Abhaengigkeit.
    No-Copy-Bestaetigung: Kein Code, keine Assets und keine Configs aus fremden Mods kopiert.
*/

class DeutschZCore_ServerProfile
{
    static void EnsureRoot()
    {
        MakeDirectory(DeutschZCore_Constants.ROOT_PROFILE);
        MakeDirectory(DeutschZCore_Constants.LOG_PROFILE);
    }

    static string SystemPath(string systemName)
    {
        EnsureRoot();
        string path = DeutschZCore_Constants.ROOT_PROFILE + systemName + "/";
        MakeDirectory(path);
        return path;
    }

    static string ConfigPath(string systemName)
    {
        string path = SystemPath(systemName) + DeutschZCore_Constants.CONFIG_FOLDER;
        MakeDirectory(path);
        return path;
    }

    static string StatePath(string systemName)
    {
        string path = SystemPath(systemName) + DeutschZCore_Constants.STATE_FOLDER;
        MakeDirectory(path);
        return path;
    }

    static string BackupPath(string systemName)
    {
        string path = SystemPath(systemName) + DeutschZCore_Constants.BACKUP_FOLDER;
        MakeDirectory(path);
        return path;
    }
}
