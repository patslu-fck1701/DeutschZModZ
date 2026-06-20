/*
    DeutschZ_GroundZero
    Owner: Patrick Sluzalek / fck1701
    Module: 2_GameLib / GroundZeroLogging
    Purpose: Central structured logging under $profile:DeutschZ/Logs/.
    Dependencies: DayZ scripts; optional CF/Expansion APIs only through adapter methods.
    Compliance: Original DeutschZ implementation. No copied foreign mod code, assets, configs or stubs.
*/

class GroundZeroLogging
{
    protected static bool s_Debug = true;

    static void SetDebug(bool enabled)
    {
        s_Debug = enabled;
    }

    static void Info(string moduleName, string message)
    {
        Write("INFO", moduleName, message);
    }

    static void Warn(string moduleName, string message)
    {
        Write("WARN", moduleName, message);
    }

    static void Error(string moduleName, string message)
    {
        Write("ERROR", moduleName, message);
    }

    static void Debug(string moduleName, string message)
    {
        if (s_Debug) Write("DEBUG", moduleName, message);
    }

    protected static void Write(string level, string moduleName, string message)
    {
        GroundZeroPersistence.EnsureProfileDirs();

        string tick = "0";
        if (GetGame()) tick = GetGame().GetTime().ToString();

        string line = string.Format("[%1][%2][%3] %4", tick, level, moduleName, message);
        Print("[DeutschZ_GroundZero] " + line);

        FileHandle handle = OpenFile(GroundZeroConstants.LOG_PATH, FileMode.APPEND);
        if (handle != 0)
        {
            FPrintln(handle, line);
            CloseFile(handle);
        }
    }
}
