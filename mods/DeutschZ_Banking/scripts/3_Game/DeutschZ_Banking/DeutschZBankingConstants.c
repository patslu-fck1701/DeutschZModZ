class DeutschZCurrencyEntry
{
    string ClassName;
    int Value;

    void DeutschZCurrencyEntry(string className = "", int value = 0)
    {
        ClassName = className;
        Value = value;
    }
}

enum DeutschZBankingRPCs
{
    DEUTSCHZ_BANKING_RPC_START = 71382000,
    DEUTSCHZ_BANKING_OPEN,
    DEUTSCHZ_BANKING_DEPOSIT,
    DEUTSCHZ_BANKING_WITHDRAW,
    DEUTSCHZ_BANKING_SYNC,
    DEUTSCHZ_BANKING_RPC_END
}

class DeutschZBankingConstants
{
    static const string ROOT_FOLDER = "$profile:DeutschZ/";
    static const string BANKING_FOLDER = "$profile:DeutschZ/Banking/";
    static const string CONFIG_FOLDER = "$profile:DeutschZ/Banking/Config/";
    static const string DATA_FOLDER = "$profile:DeutschZ/Banking/Data/";
    static const string PLAYER_FOLDER = "$profile:DeutschZ/Banking/Data/Players/";
    static const string LOG_FOLDER = "$profile:DeutschZ/Banking/Data/Logs/";
    static const string BANKING_CONFIG = "$profile:DeutschZ/Banking/Config/BankingConfig.json";
    static const string CURRENCY_CONFIG = "$profile:DeutschZ/Banking/Config/Currencies.json";
    static const string ATM_POSITIONS_CONFIG = "$profile:DeutschZ/Banking/Config/ATMPositions.json";
    static const string ADMIN_CONFIG = "$profile:DeutschZ/Banking/Config/Admins.json";
    static const string TRANSACTION_LOG_FILE = "$profile:DeutschZ/Banking/Data/Logs/Transactions.json";

    static ref array<ref DeutschZCurrencyEntry> GetDefaultCurrencies()
    {
        ref array<ref DeutschZCurrencyEntry> entries = new array<ref DeutschZCurrencyEntry>();
        entries.Insert(new DeutschZCurrencyEntry("DZ_MarkZ_1", 1));
        entries.Insert(new DeutschZCurrencyEntry("DZ_MarkZ_2", 2));
        entries.Insert(new DeutschZCurrencyEntry("DZ_MarkZ_5", 5));
        entries.Insert(new DeutschZCurrencyEntry("DZ_MarkZ_10", 10));
        entries.Insert(new DeutschZCurrencyEntry("DZ_MarkZ_20", 20));
        entries.Insert(new DeutschZCurrencyEntry("DZ_MarkZ_50", 50));
        entries.Insert(new DeutschZCurrencyEntry("DZ_MarkZ_100", 100));
        return entries;
    }
}

class DeutschZBankingLogEntry
{
    string Action;
    string SteamID;
    string PlayerName;
    int Amount;
    int BalanceAfter;
    int ServerTime;
}

class DeutschZBankingATMPosition
{
    string ClassName;
    vector Position;
    vector Orientation;
    string Name;
    bool Enabled;

    void DeutschZBankingATMPosition(string className = "DeutschZ_ATM", vector position = "0 0 0", vector orientation = "0 0 0", string name = "Default ATM", bool enabled = false)
    {
        ClassName = className;
        Position = position;
        Orientation = orientation;
        Name = name;
        Enabled = enabled;
    }
}

class DeutschZBankingAdminEntry
{
    string SteamID;
    string Comment;
    bool NoLimits;
    bool CanReloadConfig;
    bool CanAddMoney;
    bool CanRemoveMoney;

    void DeutschZBankingAdminEntry(string steamId = "", string comment = "")
    {
        SteamID = steamId;
        Comment = comment;
        NoLimits = false;
        CanReloadConfig = false;
        CanAddMoney = false;
        CanRemoveMoney = false;
    }
}
