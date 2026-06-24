/*
    DeutschZ ModZ
    Autor/Eigentuemer: Patrick Sluzalek / fck1701
    Projekt: DeutschZ
    Zweck: Serverprofile, Config-Root und sichere Default-Config-Erzeugung.
    No-Copy-Bestaetigung: Kein Code, keine Assets und keine Configs aus fremden Mods kopiert.
*/

class DeutschZCore_ServerProfile
{
    static const string CORE_PROFILE = "$profile:DeutschZ/Core/";
    static const string CORE_CONFIG_PROFILE = "$profile:DeutschZ/Core/Config/";
    static const string EVENTS_PROFILE = "$profile:DeutschZ/Events/";
    static const string CORE_CONFIG = "$profile:DeutschZ/Core/Config/CoreConfig.json";
    static const string CORE_LEGACY_CONFIG = "$profile:DeutschZ/Core/CoreConfig.json";

    static void EnsureRoot()
    {
        MakeDirectory(DeutschZCore_Constants.ROOT_PROFILE);
        MakeDirectory(DeutschZCore_Constants.LOG_PROFILE);
        MakeDirectory(CORE_PROFILE);
        MakeDirectory(CORE_CONFIG_PROFILE);
        MakeDirectory(EVENTS_PROFILE);
        EnsureCoreConfig();
    }

    static void EnsureCoreConfig()
    {
        if (FileExist(CORE_CONFIG))
            return;

        // FIX CONFIG-AUTOGEN: Always create the canonical Config folder file on server boot.
        // Existing legacy files in $profile:DeutschZ/Core/CoreConfig.json are left untouched for manual comparison.
        FileHandle file = OpenFile(CORE_CONFIG, FileMode.WRITE);
        if (file)
        {
            FPrintln(file, "{");
            FPrintln(file, "    \"ConfigVersion\": 1,");
            FPrintln(file, "    \"ProfileRoot\": \"$profile:DeutschZ/\",");
            FPrintln(file, "    \"EnableDebugLogs\": 1,");
            FPrintln(file, "    \"EnableUnsafeClassGuard\": 1,");
            FPrintln(file, "    \"BlockedClasses\": [\"M249\", \"Mag_M249_Box200Rnd\"],");
            FPrintln(file, "    \"AllowedM249Prefixes\": [\"GCGN_M249\", \"GCGNM249\"]");
            FPrintln(file, "}");
            CloseFile(file);
            Print("[DeutschZ_Core] Config created: " + CORE_CONFIG);
        }
        else
        {
            Print("[DeutschZ_Core][ERROR] Could not create config: " + CORE_CONFIG);
        }
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
        EnsureRoot();
        string systemPath = DeutschZCore_Constants.ROOT_PROFILE + systemName + "/";
        MakeDirectory(systemPath);

        string path = systemPath + DeutschZCore_Constants.CONFIG_FOLDER;
        MakeDirectory(path);
        return path;
    }

    static string StatePath(string systemName)
    {
        EnsureRoot();
        string systemPath = DeutschZCore_Constants.ROOT_PROFILE + systemName + "/";
        MakeDirectory(systemPath);

        string path = systemPath + DeutschZCore_Constants.STATE_FOLDER;
        MakeDirectory(path);
        return path;
    }

    static string BackupPath(string systemName)
    {
        EnsureRoot();
        string systemPath = DeutschZCore_Constants.ROOT_PROFILE + systemName + "/";
        MakeDirectory(systemPath);

        string path = systemPath + DeutschZCore_Constants.BACKUP_FOLDER;
        MakeDirectory(path);
        return path;
    }
}
