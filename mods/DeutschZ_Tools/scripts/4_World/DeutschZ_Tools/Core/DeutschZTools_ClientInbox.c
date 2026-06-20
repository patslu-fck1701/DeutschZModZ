class DeutschZTools_ClientInbox
{
    protected static bool s_HasStatus;
    protected static string s_StatusMessage;
    protected static bool s_StatusSuccess;

    protected static bool s_HasPlayerList;
    protected static string s_PlayerListText;
    protected static int s_PlayerListCount;

    protected static bool s_HasGarageList;
    protected static string s_GarageTitle;
    protected static string s_GarageRowsText;

    protected static bool s_HasBankingList;
    protected static string s_BankingTitle;
    protected static string s_BankingRowsText;

    protected static bool s_HasGroupsList;
    protected static string s_GroupsTitle;
    protected static string s_GroupsRowsText;

    protected static bool s_HasTraderZList;
    protected static string s_TraderZTitle;
    protected static string s_TraderZRowsText;

    static void HandleResultRPC(ParamsReadContext ctx)
    {
        bool success;
        string message;

        if (!ctx.Read(success))
            return;

        if (!ctx.Read(message))
            return;

        s_StatusSuccess = success;
        s_StatusMessage = message;
        s_HasStatus = true;

        if (success)
            Print(DeutschZTools_Constants.LOG_PREFIX + "OK: " + message);
        else
            Print(DeutschZTools_Constants.LOG_PREFIX + "FAILED: " + message);
    }

    static void HandlePlayerListRPC(ParamsReadContext ctx)
    {
        int count;
        if (!ctx.Read(count))
            return;

        string listText = "Online players: " + count + "\n";

        for (int i = 0; i < count; i++)
        {
            string name;
            string steam64;
            vector pos;
            float health01;
            float blood01;
            float shock01;
            bool alive;

            if (!ctx.Read(name)) return;
            if (!ctx.Read(steam64)) return;
            if (!ctx.Read(pos)) return;
            if (!ctx.Read(health01)) return;
            if (!ctx.Read(blood01)) return;
            if (!ctx.Read(shock01)) return;
            if (!ctx.Read(alive)) return;

            string state = "dead";
            if (alive)
                state = "alive";

            listText = listText + name + " | " + steam64 + " | " + state + " | " + pos.ToString() + "\n";
        }

        s_PlayerListText = listText;
        s_PlayerListCount = count;
        s_HasPlayerList = true;
        Print(DeutschZTools_Constants.LOG_PREFIX + "Player list received: " + count);
    }

    static void HandleGarageListRPC(ParamsReadContext ctx)
    {
        string title;
        int count;
        if (!ctx.Read(title))
            return;
        if (!ctx.Read(count))
            return;

        string rowsText = "";
        for (int i = 0; i < count; i++)
        {
            string row;
            if (!ctx.Read(row))
                return;
            rowsText = rowsText + row + "\n";
        }

        s_GarageTitle = title;
        s_GarageRowsText = rowsText;
        s_HasGarageList = true;
        Print(DeutschZTools_Constants.LOG_PREFIX + "Garage list received: " + count);
    }

    static void HandleBankingListRPC(ParamsReadContext ctx)
    {
        string title;
        int count;
        if (!ctx.Read(title))
            return;
        if (!ctx.Read(count))
            return;

        string rowsText = "";
        for (int i = 0; i < count; i++)
        {
            string row;
            if (!ctx.Read(row))
                return;
            rowsText = rowsText + row + "\n";
        }

        s_BankingTitle = title;
        s_BankingRowsText = rowsText;
        s_HasBankingList = true;
        Print(DeutschZTools_Constants.LOG_PREFIX + "Banking list received: " + count);
    }

    static void HandleGroupsListRPC(ParamsReadContext ctx)
    {
        string title;
        int count;
        if (!ctx.Read(title))
            return;
        if (!ctx.Read(count))
            return;

        string rowsText = "";
        for (int i = 0; i < count; i++)
        {
            string row;
            if (!ctx.Read(row))
                return;
            rowsText = rowsText + row + "\n";
        }

        s_GroupsTitle = title;
        s_GroupsRowsText = rowsText;
        s_HasGroupsList = true;
        Print(DeutschZTools_Constants.LOG_PREFIX + "Groups list received: " + count);
    }

    static void HandleTraderZListRPC(ParamsReadContext ctx)
    {
        string title;
        int count;
        if (!ctx.Read(title))
            return;
        if (!ctx.Read(count))
            return;

        string rowsText = "";
        for (int i = 0; i < count; i++)
        {
            string row;
            if (!ctx.Read(row))
                return;
            rowsText = rowsText + row + "\n";
        }

        s_TraderZTitle = title;
        s_TraderZRowsText = rowsText;
        s_HasTraderZList = true;
        Print(DeutschZTools_Constants.LOG_PREFIX + "TraderZ list received: " + count);
    }

    static bool ConsumeStatus(out bool success, out string message)
    {
        if (!s_HasStatus)
            return false;

        success = s_StatusSuccess;
        message = s_StatusMessage;
        s_HasStatus = false;
        return true;
    }

    static bool ConsumePlayerList(out string listText, out int count)
    {
        if (!s_HasPlayerList)
            return false;

        listText = s_PlayerListText;
        count = s_PlayerListCount;
        s_HasPlayerList = false;
        return true;
    }

    static bool ConsumeGarageList(out string title, out string rowsText)
    {
        if (!s_HasGarageList)
            return false;

        title = s_GarageTitle;
        rowsText = s_GarageRowsText;
        s_HasGarageList = false;
        return true;
    }

    static bool ConsumeBankingList(out string title, out string rowsText)
    {
        if (!s_HasBankingList)
            return false;

        title = s_BankingTitle;
        rowsText = s_BankingRowsText;
        s_HasBankingList = false;
        return true;
    }

    static bool ConsumeGroupsList(out string title, out string rowsText)
    {
        if (!s_HasGroupsList)
            return false;

        title = s_GroupsTitle;
        rowsText = s_GroupsRowsText;
        s_HasGroupsList = false;
        return true;
    }

    static bool ConsumeTraderZList(out string title, out string rowsText)
    {
        if (!s_HasTraderZList)
            return false;

        title = s_TraderZTitle;
        rowsText = s_TraderZRowsText;
        s_HasTraderZList = false;
        return true;
    }
}
