class DeutschZTools_Logger
{
    static void Info(string message)
    {
        Print(DeutschZTools_Constants.LOG_PREFIX + message);
    }

    static void Warn(string message)
    {
        Print(DeutschZTools_Constants.LOG_PREFIX + "WARNING: " + message);
    }

    static void Error(string message)
    {
        Print(DeutschZTools_Constants.LOG_PREFIX + "ERROR: " + message);
    }

    static void Admin(PlayerIdentity identity, string action)
    {
        string adminName = "unknown";
        string adminId = "unknown";

        if (identity)
        {
            adminName = identity.GetName();
            adminId = identity.GetPlainId();
        }

        Print(DeutschZTools_Constants.LOG_PREFIX + "ADMIN " + adminName + " (" + adminId + "): " + action);
    }
}
