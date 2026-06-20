class DeutschZBankingConfig
{
    static const int CURRENT_VERSION = 2;

    int ConfigVersion = CURRENT_VERSION;

    bool PersonalAccountEnabled = true;
    bool GrantStartingBalanceOnNewAccount = true;
    int StartingBalance = 10000;
    int MaxAccountMoney = 100000000;
    bool AllowDeposits = true;
    bool AllowWithdrawals = true;
    int MaxDepositPerAction = -1;
    int MaxWithdrawPerAction = -1;
    int TransactionDelayMS = 0;

    bool EnablePaycheck = false;
    int PaycheckAmount = 0;
    int PaycheckIntervalMinutes = 30;

    bool AutoSpawnATMsFromConfig = false;
    bool WriteTransactionLog = true;

    protected static ref DeutschZBankingConfig m_Instance;

    static DeutschZBankingConfig Get()
    {
        if (!m_Instance) {
            Load();
        }
        return m_Instance;
    }

    void SetDefaults()
    {
        ConfigVersion = CURRENT_VERSION;
        PersonalAccountEnabled = true;
        GrantStartingBalanceOnNewAccount = true;
        StartingBalance = 10000;
        MaxAccountMoney = 100000000;
        AllowDeposits = true;
        AllowWithdrawals = true;
        MaxDepositPerAction = -1;
        MaxWithdrawPerAction = -1;
        TransactionDelayMS = 0;
        EnablePaycheck = false;
        PaycheckAmount = 0;
        PaycheckIntervalMinutes = 30;
        AutoSpawnATMsFromConfig = false;
        WriteTransactionLog = true;
    }

    void Update()
    {
        if (ConfigVersion < 2) {
            if (MaxAccountMoney <= 0) {
                MaxAccountMoney = 100000000;
            }
            PersonalAccountEnabled = true;
            WriteTransactionLog = true;
        }
        ConfigVersion = CURRENT_VERSION;
    }

    static void Load()
    {
        DeutschZBankingCurrency.EnsureFolders();
        if (FileExist(DeutschZBankingConstants.BANKING_CONFIG)) {
            JsonFileLoader<DeutschZBankingConfig>.JsonLoadFile(DeutschZBankingConstants.BANKING_CONFIG, m_Instance);
        }

        if (!m_Instance) {
            m_Instance = new DeutschZBankingConfig();
            m_Instance.SetDefaults();
        }

        m_Instance.Update();
        m_Instance.Save();
    }

    void Save()
    {
        DeutschZBankingCurrency.EnsureFolders();
        JsonFileLoader<DeutschZBankingConfig>.JsonSaveFile(DeutschZBankingConstants.BANKING_CONFIG, this);
    }
}

class DeutschZBankingATMPositions
{
    ref array<ref DeutschZBankingATMPosition> ATMs = new array<ref DeutschZBankingATMPosition>();

    protected static ref DeutschZBankingATMPositions m_Instance;

    static DeutschZBankingATMPositions Get()
    {
        if (!m_Instance) {
            Load();
        }
        return m_Instance;
    }

    static void Load()
    {
        DeutschZBankingCurrency.EnsureFolders();

        if (FileExist(DeutschZBankingConstants.ATM_POSITIONS_CONFIG)) {
            JsonFileLoader<DeutschZBankingATMPositions>.JsonLoadFile(DeutschZBankingConstants.ATM_POSITIONS_CONFIG, m_Instance);
        }

        if (!m_Instance) {
            m_Instance = new DeutschZBankingATMPositions();
            m_Instance.LoadDefault();
        }

        if (!m_Instance.ATMs) {
            m_Instance.ATMs = new array<ref DeutschZBankingATMPosition>();
        }

        m_Instance.Save();
    }

    void LoadDefault()
    {
        ATMs.Clear();
        ATMs.Insert(new DeutschZBankingATMPosition("DeutschZ_ATM", "0 0 0", "0 0 0", "Example ATM - disabled", false));
    }

    void Save()
    {
        DeutschZBankingCurrency.EnsureFolders();
        JsonFileLoader<DeutschZBankingATMPositions>.JsonSaveFile(DeutschZBankingConstants.ATM_POSITIONS_CONFIG, this);
    }

    void SpawnConfiguredATMs()
    {
        if (!GetGame().IsServer()) {
            return;
        }

        if (!DeutschZBankingConfig.Get().AutoSpawnATMsFromConfig) {
            return;
        }

        foreach (DeutschZBankingATMPosition entry : ATMs) {
            if (!entry || !entry.Enabled || entry.ClassName == "" || entry.Position == vector.Zero) {
                continue;
            }

            Object atm = GetGame().CreateObjectEx(entry.ClassName, entry.Position, ECE_PLACE_ON_SURFACE | ECE_UPDATEPATHGRAPH);
            if (atm) {
                atm.SetOrientation(entry.Orientation);
                atm.SetPosition(entry.Position);
            }
        }
    }
}

class DeutschZBankingAdmins
{
    ref array<ref DeutschZBankingAdminEntry> Admins = new array<ref DeutschZBankingAdminEntry>();

    protected static ref DeutschZBankingAdmins m_Instance;

    static DeutschZBankingAdmins Get()
    {
        if (!m_Instance) {
            Load();
        }
        return m_Instance;
    }

    static void Load()
    {
        DeutschZBankingCurrency.EnsureFolders();

        if (FileExist(DeutschZBankingConstants.ADMIN_CONFIG)) {
            JsonFileLoader<DeutschZBankingAdmins>.JsonLoadFile(DeutschZBankingConstants.ADMIN_CONFIG, m_Instance);
        }

        if (!m_Instance) {
            m_Instance = new DeutschZBankingAdmins();
            m_Instance.LoadDefault();
        }

        if (!m_Instance.Admins) {
            m_Instance.Admins = new array<ref DeutschZBankingAdminEntry>();
        }

        m_Instance.Save();
    }

    void LoadDefault()
    {
        Admins.Clear();
        DeutschZBankingAdminEntry owner = new DeutschZBankingAdminEntry("PUT_STEAM64_HERE", "Owner");
        owner.NoLimits = true;
        owner.CanReloadConfig = true;
        owner.CanAddMoney = true;
        owner.CanRemoveMoney = true;
        Admins.Insert(owner);
    }

    void Save()
    {
        DeutschZBankingCurrency.EnsureFolders();
        JsonFileLoader<DeutschZBankingAdmins>.JsonSaveFile(DeutschZBankingConstants.ADMIN_CONFIG, this);
    }

    bool IsAdmin(PlayerIdentity identity)
    {
        if (!identity) {
            return false;
        }

        string steamId = identity.GetPlainId();
        foreach (DeutschZBankingAdminEntry entry : Admins) {
            if (entry && entry.SteamID == steamId) {
                return true;
            }
        }
        return false;
    }
}
