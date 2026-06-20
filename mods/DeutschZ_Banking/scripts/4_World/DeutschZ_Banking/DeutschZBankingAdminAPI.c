class DeutschZBankingAdminAPI
{
    static PlayerBase FindOnlinePlayerBySteamID(string steamId)
    {
        if (steamId == "") {
            return null;
        }

        ref array<Man> players = new array<Man>();
        GetGame().GetPlayers(players);

        foreach (Man man : players) {
            PlayerBase player = PlayerBase.Cast(man);
            if (!player || !player.GetIdentity()) {
                continue;
            }

            if (player.GetIdentity().GetPlainId() == steamId) {
                return player;
            }
        }

        return null;
    }

    static string GetOnlineNameOrFallback(string steamId, string fallbackName = "")
    {
        PlayerBase player = FindOnlinePlayerBySteamID(steamId);
        if (player && player.GetIdentity()) {
            return player.GetIdentity().GetName();
        }

        if (fallbackName != "") {
            return fallbackName;
        }

        return steamId;
    }

    static DeutschZBankAccount LoadAccountBySteamID(string steamId, bool createIfMissing = false, string fallbackName = "")
    {
        steamId.Trim();
        if (steamId == "") {
            return null;
        }

        DeutschZBankAccount.EnsureFolders();

        PlayerBase onlinePlayer = FindOnlinePlayerBySteamID(steamId);
        if (onlinePlayer && onlinePlayer.GetIdentity()) {
            return DeutschZBankAccount.Load(onlinePlayer.GetIdentity());
        }

        string path = DeutschZBankAccount.GetAccountPath(steamId);
        DeutschZBankAccount account;
        if (FileExist(path)) {
            JsonFileLoader<DeutschZBankAccount>.JsonLoadFile(path, account);
        }

        if (!account && createIfMissing) {
            account = new DeutschZBankAccount();
            account.SteamID = steamId;
            account.PlayerName = GetOnlineNameOrFallback(steamId, fallbackName);
            account.Balance = 0;
            account.CreatedAtServerTime = GetGame().GetTime();
            account.UpdatedAtServerTime = account.CreatedAtServerTime;

            DeutschZBankingConfig config = DeutschZBankingConfig.Get();
            if (config && config.GrantStartingBalanceOnNewAccount && config.StartingBalance > 0) {
                account.Balance = config.StartingBalance;
                account.StartingBalanceGranted = true;
            }

            account.Save();
        }

        if (account) {
            string name = GetOnlineNameOrFallback(steamId, account.PlayerName);
            if (name != "") {
                account.PlayerName = name;
            }
            if (account.PlayerName == "") {
                account.PlayerName = steamId;
            }
        }

        return account;
    }

    static void WriteAdminLog(string action, string steamId, string playerName, int amount, int balanceAfter)
    {
        if (!DeutschZBankingConfig.Get().WriteTransactionLog) {
            return;
        }

        DeutschZBankingCurrency.EnsureFolders();

        ref array<ref DeutschZBankingLogEntry> entries;
        if (FileExist(DeutschZBankingConstants.TRANSACTION_LOG_FILE)) {
            JsonFileLoader<array<ref DeutschZBankingLogEntry>>.JsonLoadFile(DeutschZBankingConstants.TRANSACTION_LOG_FILE, entries);
        }
        if (!entries) {
            entries = new array<ref DeutschZBankingLogEntry>();
        }

        DeutschZBankingLogEntry entry = new DeutschZBankingLogEntry();
        entry.Action = action;
        entry.SteamID = steamId;
        entry.PlayerName = playerName;
        entry.Amount = amount;
        entry.BalanceAfter = balanceAfter;
        entry.ServerTime = GetGame().GetTime();
        entries.Insert(entry);

        JsonFileLoader<array<ref DeutschZBankingLogEntry>>.JsonSaveFile(DeutschZBankingConstants.TRANSACTION_LOG_FILE, entries);
    }

    static bool ReloadAll(out string message)
    {
        DeutschZBankingConfig.Load();
        DeutschZBankingCurrency.Load();
        DeutschZBankingAdmins.Load();
        DeutschZBankingATMPositions.Load();
        message = "DeutschZ_Banking configs reloaded.";
        return true;
    }

    static bool GetStatus(out string message)
    {
        DeutschZBankingConfig config = DeutschZBankingConfig.Get();
        if (!config) {
            message = "DeutschZ_Banking config not loaded.";
            return false;
        }

        string enabled = "off";
        if (config.PersonalAccountEnabled) {
            enabled = "on";
        }

        message = "DeutschZ_Banking connected. Accounts=" + enabled + " start=" + config.StartingBalance.ToString() + " max=" + config.MaxAccountMoney.ToString();
        return true;
    }

    static bool GetAccountInfo(string steamId, out string playerName, out int balance, out int updatedAt, out string message)
    {
        playerName = "";
        balance = 0;
        updatedAt = 0;
        message = "";

        DeutschZBankAccount account = LoadAccountBySteamID(steamId, false);
        if (!account) {
            message = "No Banking account found for " + steamId + ". Use Add Money to create one.";
            return false;
        }

        playerName = account.PlayerName;
        balance = account.Balance;
        updatedAt = account.UpdatedAtServerTime;
        message = "Banking account loaded for " + playerName + ". Balance " + balance.ToString() + " MarkZ.";
        return true;
    }

    static bool AddMoneyBySteamID(string steamId, int amount, out string message)
    {
        message = "";
        if (amount <= 0) {
            message = "Amount must be greater than 0.";
            return false;
        }

        if (!DeutschZBankingConfig.Get().PersonalAccountEnabled) {
            message = "Personal accounts are disabled in BankingConfig.json.";
            return false;
        }

        DeutschZBankAccount account = LoadAccountBySteamID(steamId, true);
        if (!account) {
            message = "Could not load or create Banking account for " + steamId + ".";
            return false;
        }

        if (!account.AddBalance(amount)) {
            message = "Could not add money. Account may be at max limit.";
            return false;
        }

        WriteAdminLog("ToolsAdminAdd", account.SteamID, account.PlayerName, amount, account.Balance);
        message = "Added " + amount.ToString() + " MarkZ to " + account.PlayerName + ". New balance " + account.Balance.ToString() + ".";
        return true;
    }

    static bool RemoveMoneyBySteamID(string steamId, int amount, out string message)
    {
        message = "";
        if (amount <= 0) {
            message = "Amount must be greater than 0.";
            return false;
        }

        if (!DeutschZBankingConfig.Get().PersonalAccountEnabled) {
            message = "Personal accounts are disabled in BankingConfig.json.";
            return false;
        }

        DeutschZBankAccount account = LoadAccountBySteamID(steamId, false);
        if (!account) {
            message = "No Banking account found for " + steamId + ".";
            return false;
        }

        if (!account.RemoveBalance(amount)) {
            message = "Could not remove money. Balance may be too low.";
            return false;
        }

        WriteAdminLog("ToolsAdminRemove", account.SteamID, account.PlayerName, amount, account.Balance);
        message = "Removed " + amount.ToString() + " MarkZ from " + account.PlayerName + ". New balance " + account.Balance.ToString() + ".";
        return true;
    }

    static bool BuildAccountRows(string steamId, array<string> rows, out string message)
    {
        if (!rows) {
            message = "Banking rows target missing.";
            return false;
        }

        rows.Clear();
        string playerName;
        int balance;
        int updatedAt;
        if (!GetAccountInfo(steamId, playerName, balance, updatedAt, message)) {
            rows.Insert(steamId + "|0|Missing|No account|0");
            return false;
        }

        rows.Insert(playerName + "|" + balance.ToString() + "|Account|Steam64 " + steamId + "|" + updatedAt.ToString());
        return true;
    }

    static bool BuildAuditRows(string steamId, array<string> rows, int maxRows, out string message)
    {
        if (!rows) {
            message = "Banking audit rows target missing.";
            return false;
        }

        rows.Clear();
        if (maxRows <= 0) {
            maxRows = 9;
        }

        ref array<ref DeutschZBankingLogEntry> entries;
        if (FileExist(DeutschZBankingConstants.TRANSACTION_LOG_FILE)) {
            JsonFileLoader<array<ref DeutschZBankingLogEntry>>.JsonLoadFile(DeutschZBankingConstants.TRANSACTION_LOG_FILE, entries);
        }
        if (!entries) {
            entries = new array<ref DeutschZBankingLogEntry>();
        }

        for (int i = entries.Count() - 1; i >= 0; i--) {
            if (rows.Count() >= maxRows) {
                break;
            }

            DeutschZBankingLogEntry entry = entries.Get(i);
            if (!entry) {
                continue;
            }

            if (steamId != "" && entry.SteamID != steamId) {
                continue;
            }

            rows.Insert(entry.PlayerName + "|" + entry.BalanceAfter.ToString() + "|" + entry.Action + "|" + entry.Amount.ToString() + "|" + entry.ServerTime.ToString());
        }

        message = "Banking audit loaded. Rows " + rows.Count().ToString() + ".";
        return true;
    }
}
