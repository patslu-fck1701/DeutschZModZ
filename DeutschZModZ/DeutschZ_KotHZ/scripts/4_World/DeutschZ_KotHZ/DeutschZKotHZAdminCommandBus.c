/*
DeutschZ ModZ
Eigenstaendige Implementierung fuer DeutschZ.
Autor/Eigentuemer: Patrick Sluzalek / fck1701.
Keine direkte Codeuebernahme aus Drittquellen.
Oeffentliche Quellen werden nur zur Konzept- und API-Verifikation genutzt.
*/

class DeutschZKotHZAdminCommand
{
    string Command;
    string AdminSteam64;
    string AdminName;

    void DeutschZKotHZAdminCommand()
    {
        Command = "";
        AdminSteam64 = "";
        AdminName = "";
    }
}

class DeutschZKotHZAdminCommandBus
{
    protected static ref array<ref DeutschZKotHZAdminCommand> s_Queue;
    protected static string s_LastResult;

    protected static void Ensure()
    {
        if (!s_Queue)
            s_Queue = new array<ref DeutschZKotHZAdminCommand>;
        if (s_LastResult == "")
            s_LastResult = "KOTH command bus ready.";
    }

    static bool Enqueue(string command, string adminSteam64, string adminName)
    {
        Ensure();
        DeutschZKotHZAdminCommand item = new DeutschZKotHZAdminCommand();
        item.Command = command;
        item.AdminSteam64 = adminSteam64;
        item.AdminName = adminName;
        s_Queue.Insert(item);
        s_LastResult = "KOTH command queued: " + command;
        return true;
    }

    static bool Pop(out string command, out string adminSteam64, out string adminName)
    {
        Ensure();
        command = "";
        adminSteam64 = "";
        adminName = "";

        if (s_Queue.Count() == 0)
            return false;

        DeutschZKotHZAdminCommand item = s_Queue.Get(0);
        s_Queue.Remove(0);
        if (!item)
            return false;

        command = item.Command;
        adminSteam64 = item.AdminSteam64;
        adminName = item.AdminName;
        return true;
    }

    static void SetLastResult(string result)
    {
        s_LastResult = result;
    }

    static string GetLastResult()
    {
        Ensure();
        return s_LastResult;
    }
}
