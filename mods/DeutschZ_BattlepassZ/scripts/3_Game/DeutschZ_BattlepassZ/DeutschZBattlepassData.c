class DeutschZBattlepassTaskProgressData
{
    string TaskId;
    int Count;
    int Completed;
    int ClaimedXp;

    void DeutschZBattlepassTaskProgressData()
    {
        TaskId = "";
        Count = 0;
        Completed = 0;
        ClaimedXp = 0;
    }
}

class DeutschZBattlepassPlayerData
{
    string Steam64;
    string PlayerName;
    string SeasonId;
    int XP;
    int Level;
    int Premium;
    int PremiumExpiresAt;
    int PremiumActivatedAt;
    string PremiumSourceItem;
    int PremiumDaysGranted;
    int LastSeenAt;
    int TotalPlaytimeMinutes;
    int SessionSeconds;
    ref array<string> ClaimedFreeRewards;
    ref array<string> ClaimedPremiumRewards;
    ref array<ref DeutschZBattlepassTaskProgressData> TaskProgress;

    void DeutschZBattlepassPlayerData()
    {
        Steam64 = "";
        PlayerName = "";
        SeasonId = "";
        XP = 0;
        Level = 1;
        Premium = 0;
        PremiumExpiresAt = 0;
        PremiumActivatedAt = 0;
        PremiumSourceItem = "";
        PremiumDaysGranted = 0;
        LastSeenAt = 0;
        TotalPlaytimeMinutes = 0;
        SessionSeconds = 0;
        ClaimedFreeRewards = new array<string>();
        ClaimedPremiumRewards = new array<string>();
        TaskProgress = new array<ref DeutschZBattlepassTaskProgressData>();
    }

    bool HasClaimed(string rewardId, int premium)
    {
        if (premium == 1)
        {
            if (!ClaimedPremiumRewards)
            {
                ClaimedPremiumRewards = new array<string>();
            }
            if (ClaimedPremiumRewards.Find(rewardId) >= 0)
            {
                return true;
            }
        }
        else
        {
            if (!ClaimedFreeRewards)
            {
                ClaimedFreeRewards = new array<string>();
            }
            if (ClaimedFreeRewards.Find(rewardId) >= 0)
            {
                return true;
            }
        }
        return false;
    }

    void AddClaimed(string rewardId, int premium)
    {
        if (premium == 1)
        {
            if (!ClaimedPremiumRewards)
            {
                ClaimedPremiumRewards = new array<string>();
            }
            if (ClaimedPremiumRewards.Find(rewardId) < 0)
            {
                ClaimedPremiumRewards.Insert(rewardId);
            }
        }
        else
        {
            if (!ClaimedFreeRewards)
            {
                ClaimedFreeRewards = new array<string>();
            }
            if (ClaimedFreeRewards.Find(rewardId) < 0)
            {
                ClaimedFreeRewards.Insert(rewardId);
            }
        }
    }

    DeutschZBattlepassTaskProgressData GetProgress(string taskId)
    {
        if (!TaskProgress)
        {
            TaskProgress = new array<ref DeutschZBattlepassTaskProgressData>();
        }
        int i;
        for (i = 0; i < TaskProgress.Count(); i++)
        {
            DeutschZBattlepassTaskProgressData progress = TaskProgress.Get(i);
            if (progress && progress.TaskId == taskId)
            {
                return progress;
            }
        }
        ref DeutschZBattlepassTaskProgressData created = new DeutschZBattlepassTaskProgressData();
        created.TaskId = taskId;
        TaskProgress.Insert(created);
        return created;
    }
}

class DeutschZBattlepassClaimRequest
{
    string RewardId;
    int Premium;

    void DeutschZBattlepassClaimRequest()
    {
        RewardId = "";
        Premium = 0;
    }
}

class DeutschZBattlepassAdminXpRequest
{
    string Steam64;
    int XP;
    string Reason;

    void DeutschZBattlepassAdminXpRequest()
    {
        Steam64 = "";
        XP = 0;
        Reason = "admin";
    }
}

class DeutschZBattlepassPremiumRequest
{
    string Steam64;
    int Premium;

    void DeutschZBattlepassPremiumRequest()
    {
        Steam64 = "";
        Premium = 0;
    }
}

class DeutschZBattlepassTaskProgressRequest
{
    string TaskId;
    int Amount;

    void DeutschZBattlepassTaskProgressRequest()
    {
        TaskId = "";
        Amount = 1;
    }
}


class DeutschZBattlepassPremiumItemActivationRequest
{
    string ItemClass;

    void DeutschZBattlepassPremiumItemActivationRequest()
    {
        ItemClass = "";
    }
}

class DeutschZBattlepassSyncPacket
{
    ref DeutschZBattlepassFreeConfig FreeConfig;
    ref DeutschZBattlepassPremiumConfig PremiumConfig;
    ref DeutschZBattlepassPlayerData Player;
    string StatusMessage;

    void DeutschZBattlepassSyncPacket()
    {
        FreeConfig = new DeutschZBattlepassFreeConfig();
        PremiumConfig = new DeutschZBattlepassPremiumConfig();
        Player = new DeutschZBattlepassPlayerData();
        StatusMessage = "";
    }
}

class DeutschZBattlepassRewardLogEntry
{
    string Steam64;
    string PlayerName;
    string RewardId;
    string RewardName;
    int Premium;
    int Time;

    void DeutschZBattlepassRewardLogEntry()
    {
        Steam64 = "";
        PlayerName = "";
        RewardId = "";
        RewardName = "";
        Premium = 0;
        Time = 0;
    }
}

class DeutschZBattlepassRewardLog
{
    ref array<ref DeutschZBattlepassRewardLogEntry> Entries;

    void DeutschZBattlepassRewardLog()
    {
        Entries = new array<ref DeutschZBattlepassRewardLogEntry>();
    }
}
