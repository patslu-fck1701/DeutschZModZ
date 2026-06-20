class DeutschZBattlepassManager
{
    protected ref DeutschZBattlepassConfigManager m_ConfigManager;
    protected ref map<string, ref DeutschZBattlepassPlayerData> m_PlayerCache;
    protected ref DeutschZBattlepassRewardLog m_RewardLog;
    protected int m_LastSync;
    protected int m_LastPlaytimeTick;
    protected int m_LastExpiryCheck;

    void DeutschZBattlepassManager()
    {
        m_ConfigManager = new DeutschZBattlepassConfigManager();
        m_PlayerCache = new map<string, ref DeutschZBattlepassPlayerData>();
        m_RewardLog = new DeutschZBattlepassRewardLog();
        m_LastSync = 0;
        m_LastPlaytimeTick = 0;
        m_LastExpiryCheck = 0;
    }

    void Init()
    {
        DeutschZBattlepassProfileFolders.Ensure();
        m_ConfigManager.Load();
        LoadRewardLog();
        Print("[DeutschZ_BattlepassZ] Initialized version " + DeutschZBattlepassConstants.VERSION);
    }

    void Tick()
    {
        int now = GetGame().GetTime();
        if (now - m_LastPlaytimeTick > 60000)
        {
            GrantPlaytimeXP();
            m_LastPlaytimeTick = now;
        }

        int expiryMs = GetPremiumConfig().ExpiryCheckIntervalSeconds * 1000;
        if (expiryMs < 10000)
        {
            expiryMs = 10000;
        }
        if (now - m_LastExpiryCheck > expiryMs)
        {
            CheckPremiumExpiry();
            m_LastExpiryCheck = now;
        }

        int syncMs = GetFreeConfig().SyncIntervalSeconds * 1000;
        if (syncMs < 5000)
        {
            syncMs = 5000;
        }
        if (now - m_LastSync > syncMs)
        {
            SendSyncToAllOnline();
            m_LastSync = now;
        }
    }

    DeutschZBattlepassFreeConfig GetFreeConfig()
    {
        return m_ConfigManager.FreeConfig;
    }

    DeutschZBattlepassPremiumConfig GetPremiumConfig()
    {
        return m_ConfigManager.PremiumConfig;
    }

    protected string GetPlayerFile(string steam64)
    {
        return DeutschZBattlepassConstants.PLAYER_ROOT + steam64 + ".json";
    }

    DeutschZBattlepassPlayerData GetPlayerData(string steam64, string playerName)
    {
        if (steam64 == "")
        {
            return null;
        }

        if (m_PlayerCache.Contains(steam64))
        {
            DeutschZBattlepassPlayerData cached = m_PlayerCache.Get(steam64);
            if (cached)
            {
                if (playerName != "")
                {
                    cached.PlayerName = playerName;
                }
                return cached;
            }
        }

        ref DeutschZBattlepassPlayerData data = new DeutschZBattlepassPlayerData();
        string file = GetPlayerFile(steam64);
        if (FileExist(file))
        {
            JsonFileLoader<DeutschZBattlepassPlayerData>.JsonLoadFile(file, data);
        }
        data.Steam64 = steam64;
        if (playerName != "")
        {
            data.PlayerName = playerName;
        }
        data.SeasonId = GetFreeConfig().SeasonId;
        NormalizePlayer(data);
        m_PlayerCache.Set(steam64, data);
        return data;
    }

    protected void NormalizePlayer(DeutschZBattlepassPlayerData data)
    {
        if (!data)
        {
            return;
        }
        if (!data.ClaimedFreeRewards)
        {
            data.ClaimedFreeRewards = new array<string>();
        }
        if (!data.ClaimedPremiumRewards)
        {
            data.ClaimedPremiumRewards = new array<string>();
        }
        if (!data.TaskProgress)
        {
            data.TaskProgress = new array<ref DeutschZBattlepassTaskProgressData>();
        }
        if (data.Level < 1)
        {
            data.Level = 1;
        }
        if (IsManualPremium(data.Steam64))
        {
            data.Premium = 1;
            data.PremiumExpiresAt = 0;
        }
        else
        {
            if (GetPremiumConfig().RevokePremiumOnExpiry == 1 && data.Premium == 1 && data.PremiumExpiresAt > 0)
            {
                if (NowSeconds() >= data.PremiumExpiresAt)
                {
                    data.Premium = 0;
                    data.PremiumExpiresAt = 0;
                }
            }
        }
        data.Level = CalculateLevel(data.XP);
    }

    void SavePlayer(DeutschZBattlepassPlayerData data)
    {
        if (!data || data.Steam64 == "")
        {
            return;
        }
        NormalizePlayer(data);
        JsonFileLoader<DeutschZBattlepassPlayerData>.JsonSaveFile(GetPlayerFile(data.Steam64), data);
    }

    int CalculateLevel(int xp)
    {
        int xpPerLevel = GetFreeConfig().XpPerLevel;
        if (xpPerLevel <= 0)
        {
            xpPerLevel = DeutschZBattlepassConstants.DEFAULT_XP_PER_LEVEL;
        }
        int level = (xp / xpPerLevel) + 1;
        if (level < 1)
        {
            level = 1;
        }
        if (level > GetFreeConfig().MaxLevel)
        {
            level = GetFreeConfig().MaxLevel;
        }
        return level;
    }

    void AddXP(string steam64, string playerName, int amount, string reason)
    {
        if (amount <= 0)
        {
            return;
        }
        DeutschZBattlepassPlayerData data = GetPlayerData(steam64, playerName);
        if (!data)
        {
            return;
        }
        data.XP = data.XP + amount;
        data.Level = CalculateLevel(data.XP);
        data.LastSeenAt = GetGame().GetTime();
        SavePlayer(data);
    }

    void SetPremium(string steam64, int premium)
    {
        DeutschZBattlepassPlayerData data = GetPlayerData(steam64, "");
        if (!data)
        {
            return;
        }
        data.Premium = 0;
        data.PremiumExpiresAt = 0;
        data.PremiumActivatedAt = 0;
        data.PremiumSourceItem = "admin";
        data.PremiumDaysGranted = 0;
        if (premium == 1)
        {
            data.Premium = 1;
        }
        SavePlayer(data);
    }

    int NowSeconds()
    {
        return GetGame().GetTime() / 1000;
    }

    bool IsAdmin(string steam64)
    {
        if (steam64 == "")
        {
            return false;
        }
        if (!GetPremiumConfig().Admins)
        {
            return false;
        }
        if (GetPremiumConfig().Admins.Find(steam64) >= 0)
        {
            return true;
        }
        return false;
    }

    bool IsManualPremium(string steam64)
    {
        if (steam64 == "")
        {
            return false;
        }
        if (!GetPremiumConfig().PremiumPlayers)
        {
            return false;
        }
        if (GetPremiumConfig().PremiumPlayers.Find(steam64) >= 0)
        {
            return true;
        }
        return false;
    }

    DeutschZBattlepassPremiumItemConfig FindPremiumItemConfig(string classname)
    {
        if (classname == "")
        {
            return null;
        }
        if (!GetPremiumConfig().PremiumItems)
        {
            return null;
        }
        int i;
        for (i = 0; i < GetPremiumConfig().PremiumItems.Count(); i++)
        {
            DeutschZBattlepassPremiumItemConfig itemConfig = GetPremiumConfig().PremiumItems.Get(i);
            if (itemConfig && itemConfig.ClassName == classname)
            {
                return itemConfig;
            }
        }
        return null;
    }

    bool IsPremiumItemClass(string classname)
    {
        if (FindPremiumItemConfig(classname))
        {
            return true;
        }
        return false;
    }

    string GetPremiumItemActionText()
    {
        if (GetPremiumConfig().ActivateActionText != "")
        {
            return GetPremiumConfig().ActivateActionText;
        }
        return "Activate Premium";
    }

    bool ActivatePremiumItem(PlayerBase player, ItemBase item)
    {
        if (!player || !item)
        {
            return false;
        }
        if (GetPremiumConfig().PremiumEnabled != 1)
        {
            SendPlayerMessage(player, GetPremiumConfig().PremiumDisabledMessage);
            return false;
        }
        if (GetPremiumConfig().PremiumItemActivationEnabled != 1)
        {
            SendPlayerMessage(player, GetPremiumConfig().DisabledMessage);
            return false;
        }
        string itemClass = item.GetType();
        DeutschZBattlepassPremiumItemConfig itemConfig = FindPremiumItemConfig(itemClass);
        if (!itemConfig)
        {
            SendPlayerMessage(player, GetPremiumConfig().InvalidItemMessage);
            return false;
        }
        PlayerIdentity identity = player.GetIdentity();
        if (!identity)
        {
            return false;
        }
        string steam64 = identity.GetPlainId();
        string name = identity.GetName();
        DeutschZBattlepassPlayerData data = GetPlayerData(steam64, name);
        if (!data)
        {
            return false;
        }

        int now = NowSeconds();
        int days = itemConfig.Days;
        if (days <= 0)
        {
            days = 30;
        }
        int addSeconds = days * 86400;
        int newExpiry = now + addSeconds;
        string messagePrefix = GetPremiumConfig().ActivatedMessagePrefix;
        if (GetPremiumConfig().ExtendExistingPremium == 1 && data.Premium == 1 && data.PremiumExpiresAt > now)
        {
            newExpiry = data.PremiumExpiresAt + addSeconds;
            messagePrefix = GetPremiumConfig().ExtendedMessagePrefix;
        }

        data.Premium = 1;
        data.PremiumActivatedAt = now;
        data.PremiumExpiresAt = newExpiry;
        data.PremiumSourceItem = itemClass;
        data.PremiumDaysGranted = days;
        SavePlayer(data);

        if (itemConfig.ConsumeOnUse == 1)
        {
            GetGame().ObjectDelete(item);
        }

        SendPlayerMessage(player, messagePrefix + " " + days.ToString() + " days.");
        SendSyncToPlayer(player);
        return true;
    }

    protected void SendPlayerMessage(PlayerBase player, string message)
    {
        if (!player || message == "")
        {
            return;
        }
        player.MessageStatus(message);
    }

    protected void CheckPremiumExpiry()
    {
        if (GetPremiumConfig().RevokePremiumOnExpiry != 1)
        {
            return;
        }
        int now = NowSeconds();
        ref array<Man> players = new array<Man>();
        GetGame().GetPlayers(players);
        int i;
        for (i = 0; i < players.Count(); i++)
        {
            PlayerBase player = PlayerBase.Cast(players.Get(i));
            if (player && player.GetIdentity())
            {
                string steam64 = player.GetIdentity().GetPlainId();
                DeutschZBattlepassPlayerData data = GetPlayerData(steam64, player.GetIdentity().GetName());
                if (data && data.Premium == 1 && data.PremiumExpiresAt > 0 && now >= data.PremiumExpiresAt)
                {
                    data.Premium = 0;
                    data.PremiumExpiresAt = 0;
                    SavePlayer(data);
                    SendPlayerMessage(player, GetPremiumConfig().ExpiredMessage);
                    SendSyncToPlayer(player);
                }
            }
        }
    }

    protected DeutschZBattlepassRewardData FindReward(string rewardId, int premium)
    {
        int i;
        if (premium == 1)
        {
            for (i = 0; i < GetPremiumConfig().PremiumRewards.Count(); i++)
            {
                DeutschZBattlepassRewardData pr = GetPremiumConfig().PremiumRewards.Get(i);
                if (pr && pr.RewardId == rewardId)
                {
                    return pr;
                }
            }
        }
        else
        {
            for (i = 0; i < GetFreeConfig().FreeRewards.Count(); i++)
            {
                DeutschZBattlepassRewardData fr = GetFreeConfig().FreeRewards.Get(i);
                if (fr && fr.RewardId == rewardId)
                {
                    return fr;
                }
            }
        }
        return null;
    }

    bool ClaimReward(PlayerBase player, string rewardId, int premium)
    {
        if (!player || rewardId == "")
        {
            return false;
        }
        PlayerIdentity identity = player.GetIdentity();
        if (!identity)
        {
            return false;
        }
        string steam64 = identity.GetPlainId();
        string name = identity.GetName();
        DeutschZBattlepassPlayerData data = GetPlayerData(steam64, name);
        if (!data)
        {
            return false;
        }
        if (premium == 1 && data.Premium != 1)
        {
            return false;
        }
        DeutschZBattlepassRewardData reward = FindReward(rewardId, premium);
        if (!reward)
        {
            return false;
        }
        if (data.Level < reward.Level)
        {
            return false;
        }
        if (data.HasClaimed(rewardId, premium))
        {
            return false;
        }

        GrantReward(player, data, reward, premium);
        data.AddClaimed(rewardId, premium);
        SavePlayer(data);
        AddRewardLog(data, reward, premium);
        return true;
    }

    protected void GrantReward(PlayerBase player, DeutschZBattlepassPlayerData data, DeutschZBattlepassRewardData reward, int premium)
    {
        if (!player || !data || !reward)
        {
            return;
        }
        if (reward.RewardType == DeutschZBattlepassRewardType.ITEM)
        {
            GrantItem(player, reward);
            return;
        }
        if (reward.RewardType == DeutschZBattlepassRewardType.XP)
        {
            if (reward.XpAmount > 0)
            {
                data.XP = data.XP + reward.XpAmount;
                data.Level = CalculateLevel(data.XP);
            }
            return;
        }
        if (reward.RewardType == DeutschZBattlepassRewardType.MONEY)
        {
            Print("[DeutschZ_BattlepassZ] Money reward reserved for BankingZ bridge: " + reward.MoneyAmount.ToString());
            return;
        }
        if (reward.RewardType == DeutschZBattlepassRewardType.COMMAND)
        {
            Print("[DeutschZ_BattlepassZ] Command reward reserved for admin bridge: " + reward.Command);
            return;
        }
    }

    protected void GrantItem(PlayerBase player, DeutschZBattlepassRewardData reward)
    {
        if (!player || !reward || reward.ItemClass == "")
        {
            return;
        }
        int count = reward.Quantity;
        if (count <= 0)
        {
            count = 1;
        }
        int i;
        for (i = 0; i < count; i++)
        {
            EntityAI item = player.GetInventory().CreateInInventory(reward.ItemClass);
            if (!item)
            {
                item = EntityAI.Cast(GetGame().CreateObject(reward.ItemClass, player.GetPosition()));
            }
            if (item && reward.StackQuantity > 0)
            {
                ItemBase itemBase = ItemBase.Cast(item);
                if (itemBase)
                {
                    itemBase.SetQuantity(reward.StackQuantity);
                }
            }
            if (item && reward.AttachmentCSV != "")
            {
                AddAttachments(item, reward.AttachmentCSV);
            }
        }
    }

    protected void AddAttachments(EntityAI parent, string csv)
    {
        if (!parent || csv == "")
        {
            return;
        }
        ref TStringArray parts = new TStringArray;
        csv.Split(",", parts);
        int i;
        for (i = 0; i < parts.Count(); i++)
        {
            string classname = parts.Get(i);
            classname.TrimInPlace();
            if (classname != "")
            {
                parent.GetInventory().CreateAttachment(classname);
            }
        }
    }

    void AddTaskProgress(string steam64, string playerName, string taskId, int amount)
    {
        if (amount <= 0)
        {
            amount = 1;
        }
        DeutschZBattlepassTaskData task = FindTask(taskId);
        if (!task || task.Active != 1)
        {
            return;
        }
        DeutschZBattlepassPlayerData data = GetPlayerData(steam64, playerName);
        if (!data)
        {
            return;
        }
        DeutschZBattlepassTaskProgressData progress = data.GetProgress(taskId);
        if (!progress)
        {
            return;
        }
        if (progress.Completed == 1)
        {
            return;
        }
        progress.Count = progress.Count + amount;
        if (progress.Count >= task.TargetCount)
        {
            progress.Count = task.TargetCount;
            progress.Completed = 1;
            if (progress.ClaimedXp != 1)
            {
                data.XP = data.XP + task.XpReward;
                data.Level = CalculateLevel(data.XP);
                progress.ClaimedXp = 1;
            }
        }
        SavePlayer(data);
    }

    protected DeutschZBattlepassTaskData FindTask(string taskId)
    {
        int i;
        for (i = 0; i < GetFreeConfig().Tasks.Count(); i++)
        {
            DeutschZBattlepassTaskData task = GetFreeConfig().Tasks.Get(i);
            if (task && task.TaskId == taskId)
            {
                return task;
            }
        }
        return null;
    }

    protected void GrantPlaytimeXP()
    {
        ref array<Man> players = new array<Man>();
        GetGame().GetPlayers(players);
        int i;
        for (i = 0; i < players.Count(); i++)
        {
            PlayerBase player = PlayerBase.Cast(players.Get(i));
            if (player && player.GetIdentity())
            {
                string steam64 = player.GetIdentity().GetPlainId();
                string name = player.GetIdentity().GetName();
                DeutschZBattlepassPlayerData data = GetPlayerData(steam64, name);
                if (data)
                {
                    data.TotalPlaytimeMinutes = data.TotalPlaytimeMinutes + 1;
                    data.SessionSeconds = data.SessionSeconds + 60;
                    if (GetFreeConfig().PlaytimeXpPerMinute > 0)
                    {
                        data.XP = data.XP + GetFreeConfig().PlaytimeXpPerMinute;
                        data.Level = CalculateLevel(data.XP);
                    }
                    SavePlayer(data);
                    AddTaskProgress(steam64, name, "play_30_minutes", 1);
                }
            }
        }
    }

    DeutschZBattlepassSyncPacket BuildSyncPacket(PlayerBase player)
    {
        ref DeutschZBattlepassSyncPacket packet = new DeutschZBattlepassSyncPacket();
        packet.FreeConfig = GetFreeConfig();
        packet.PremiumConfig = GetPremiumConfig();
        packet.StatusMessage = "DeutschZ BattlepassZ ready";
        if (player && player.GetIdentity())
        {
            packet.Player = GetPlayerData(player.GetIdentity().GetPlainId(), player.GetIdentity().GetName());
        }
        return packet;
    }

    void SendSyncToPlayer(PlayerBase player)
    {
        if (!player)
        {
            return;
        }
        ref DeutschZBattlepassSyncPacket packet = BuildSyncPacket(player);
        GetGame().RPCSingleParam(player, DeutschZBattlepassRPC.SYNC, new Param1<DeutschZBattlepassSyncPacket>(packet), true, player.GetIdentity());
    }

    void SendSyncToAllOnline()
    {
        ref array<Man> players = new array<Man>();
        GetGame().GetPlayers(players);
        int i;
        for (i = 0; i < players.Count(); i++)
        {
            PlayerBase player = PlayerBase.Cast(players.Get(i));
            if (player)
            {
                SendSyncToPlayer(player);
            }
        }
    }

    protected void LoadRewardLog()
    {
        if (FileExist(DeutschZBattlepassConstants.REWARD_LOG_FILE))
        {
            JsonFileLoader<DeutschZBattlepassRewardLog>.JsonLoadFile(DeutschZBattlepassConstants.REWARD_LOG_FILE, m_RewardLog);
        }
        if (!m_RewardLog)
        {
            m_RewardLog = new DeutschZBattlepassRewardLog();
        }
        if (!m_RewardLog.Entries)
        {
            m_RewardLog.Entries = new array<ref DeutschZBattlepassRewardLogEntry>();
        }
    }

    protected void SaveRewardLog()
    {
        JsonFileLoader<DeutschZBattlepassRewardLog>.JsonSaveFile(DeutschZBattlepassConstants.REWARD_LOG_FILE, m_RewardLog);
    }

    protected void AddRewardLog(DeutschZBattlepassPlayerData data, DeutschZBattlepassRewardData reward, int premium)
    {
        if (!m_RewardLog)
        {
            m_RewardLog = new DeutschZBattlepassRewardLog();
        }
        ref DeutschZBattlepassRewardLogEntry entry = new DeutschZBattlepassRewardLogEntry();
        entry.Steam64 = data.Steam64;
        entry.PlayerName = data.PlayerName;
        entry.RewardId = reward.RewardId;
        entry.RewardName = reward.DisplayName;
        entry.Premium = premium;
        entry.Time = GetGame().GetTime();
        m_RewardLog.Entries.Insert(entry);
        SaveRewardLog();
    }
}
