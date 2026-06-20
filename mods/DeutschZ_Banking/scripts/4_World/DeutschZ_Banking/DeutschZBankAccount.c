class DeutschZBankAccount
{
    string SteamID;
    string PlayerName;
    int Balance;
    bool StartingBalanceGranted;
    int CreatedAtServerTime;
    int UpdatedAtServerTime;

    static void EnsureFolders()
    {
        DeutschZBankingCurrency.EnsureFolders();
        if (!FileExist(DeutschZBankingConstants.DATA_FOLDER)) {
            MakeDirectory(DeutschZBankingConstants.DATA_FOLDER);
        }
        if (!FileExist(DeutschZBankingConstants.PLAYER_FOLDER)) {
            MakeDirectory(DeutschZBankingConstants.PLAYER_FOLDER);
        }
    }

    static string GetAccountPath(string steamId)
    {
        return DeutschZBankingConstants.PLAYER_FOLDER + steamId + ".json";
    }

    static DeutschZBankAccount CreateDefault(PlayerIdentity identity)
    {
        DeutschZBankAccount account = new DeutschZBankAccount();
        account.SteamID = identity.GetPlainId();
        account.PlayerName = identity.GetName();
        account.Balance = 0;
        account.CreatedAtServerTime = GetGame().GetTime();
        account.UpdatedAtServerTime = account.CreatedAtServerTime;

        DeutschZBankingConfig config = DeutschZBankingConfig.Get();
        if (config && config.GrantStartingBalanceOnNewAccount && config.StartingBalance > 0) {
            account.Balance = config.StartingBalance;
            account.StartingBalanceGranted = true;
        }

        return account;
    }

    static DeutschZBankAccount Load(PlayerIdentity identity)
    {
        if (!identity) {
            return null;
        }

        EnsureFolders();

        string path = GetAccountPath(identity.GetPlainId());
        DeutschZBankAccount account;
        if (FileExist(path)) {
            JsonFileLoader<DeutschZBankAccount>.JsonLoadFile(path, account);
        }

        if (!account) {
            account = CreateDefault(identity);
            account.Save();
            if (account.StartingBalanceGranted && account.Balance > 0) {
                DeutschZ_Banking.WriteLog("StartingBalance", identity, account.Balance, account.Balance);
            }
        }

        account.PlayerName = identity.GetName();
        account.UpdatedAtServerTime = GetGame().GetTime();
        return account;
    }

    void Save()
    {
        EnsureFolders();
        UpdatedAtServerTime = GetGame().GetTime();
        JsonFileLoader<DeutschZBankAccount>.JsonSaveFile(GetAccountPath(SteamID), this);
    }

    bool AddBalance(int amount)
    {
        if (amount <= 0) {
            return false;
        }

        DeutschZBankingConfig config = DeutschZBankingConfig.Get();
        if (config && config.MaxAccountMoney > 0) {
            if (Balance >= config.MaxAccountMoney) {
                return false;
            }
            amount = Math.Min(amount, config.MaxAccountMoney - Balance);
        }

        if (amount <= 0) {
            return false;
        }

        Balance += amount;
        Save();
        return true;
    }

    bool RemoveBalance(int amount)
    {
        if (amount <= 0 || Balance < amount) {
            return false;
        }

        Balance -= amount;
        Save();
        return true;
    }
}

class DeutschZ_Banking
{
    protected static void EnsureTransactionLogFile()
    {
        DeutschZBankingCurrency.EnsureFolders();
    }

    static void WriteLog(string action, PlayerIdentity identity, int amount, int balanceAfter)
    {
        if (!identity) {
            return;
        }

        if (!DeutschZBankingConfig.Get().WriteTransactionLog) {
            return;
        }

        ref array<ref DeutschZBankingLogEntry> entries;
        if (FileExist(DeutschZBankingConstants.TRANSACTION_LOG_FILE)) {
            JsonFileLoader<array<ref DeutschZBankingLogEntry>>.JsonLoadFile(DeutschZBankingConstants.TRANSACTION_LOG_FILE, entries);
        }
        if (!entries) {
            entries = new array<ref DeutschZBankingLogEntry>();
        }

        DeutschZBankingLogEntry entry = new DeutschZBankingLogEntry();
        entry.Action = action;
        entry.SteamID = identity.GetPlainId();
        entry.PlayerName = identity.GetName();
        entry.Amount = amount;
        entry.BalanceAfter = balanceAfter;
        entry.ServerTime = GetGame().GetTime();
        entries.Insert(entry);
        JsonFileLoader<array<ref DeutschZBankingLogEntry>>.JsonSaveFile(DeutschZBankingConstants.TRANSACTION_LOG_FILE, entries);
    }

    static bool AddMoney(PlayerIdentity identity, int amount)
    {
        if (!DeutschZBankingConfig.Get().PersonalAccountEnabled) {
            return false;
        }
        DeutschZBankAccount account = DeutschZBankAccount.Load(identity);
        if (!account) {
            return false;
        }
        if (account.AddBalance(amount)) {
            WriteLog("AdminOrScriptAdd", identity, amount, account.Balance);
            return true;
        }
        return false;
    }

    static bool RemoveMoney(PlayerIdentity identity, int amount)
    {
        if (!DeutschZBankingConfig.Get().PersonalAccountEnabled) {
            return false;
        }
        DeutschZBankAccount account = DeutschZBankAccount.Load(identity);
        if (!account) {
            return false;
        }
        if (account.RemoveBalance(amount)) {
            WriteLog("AdminOrScriptRemove", identity, amount, account.Balance);
            return true;
        }
        return false;
    }

    static int GetBalance(PlayerIdentity identity)
    {
        if (!DeutschZBankingConfig.Get().PersonalAccountEnabled) {
            return 0;
        }
        DeutschZBankAccount account = DeutschZBankAccount.Load(identity);
        if (!account) {
            return 0;
        }
        return account.Balance;
    }

    static int DepositCash(PlayerBase player, int amount)
    {
        if (!player || !player.GetIdentity() || amount <= 0) {
            return 0;
        }

        DeutschZBankingConfig config = DeutschZBankingConfig.Get();
        if (!config || !config.PersonalAccountEnabled || !config.AllowDeposits) {
            return 0;
        }
        int inventoryMoney = DeutschZBankingCurrency.GetInventoryMoney(player);
        if (inventoryMoney <= 0) {
            return 0;
        }

        amount = Math.Min(amount, inventoryMoney);
        if (config.MaxDepositPerAction > 0) {
            amount = Math.Min(amount, config.MaxDepositPerAction);
        }

        int removed = DeutschZBankingCurrency.RemoveInventoryMoney(player, amount);
        if (removed <= 0) {
            return 0;
        }

        DeutschZBankAccount account = DeutschZBankAccount.Load(player.GetIdentity());
        if (account) {
            account.AddBalance(removed);
            WriteLog("DepositCash", player.GetIdentity(), removed, account.Balance);
        }
        return removed;
    }

    static int WithdrawCash(PlayerBase player, int amount)
    {
        if (!player || !player.GetIdentity() || amount <= 0) {
            return 0;
        }

        DeutschZBankingConfig config = DeutschZBankingConfig.Get();
        if (!config || !config.PersonalAccountEnabled || !config.AllowWithdrawals) {
            return 0;
        }
        if (config.MaxWithdrawPerAction > 0) {
            amount = Math.Min(amount, config.MaxWithdrawPerAction);
        }

        DeutschZBankAccount account = DeutschZBankAccount.Load(player.GetIdentity());
        if (!account || account.Balance <= 0) {
            return 0;
        }

        int payable = Math.Min(amount, account.Balance);
        int added = DeutschZBankingCurrency.AddInventoryMoney(player, payable);
        if (added > 0) {
            account.RemoveBalance(added);
            WriteLog("WithdrawCash", player.GetIdentity(), added, account.Balance);
        }
        return added;
    }
}
