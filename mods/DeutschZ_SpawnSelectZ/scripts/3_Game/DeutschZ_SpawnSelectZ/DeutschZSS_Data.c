
class DeutschZSS_LoadoutItem
{
    string ClassName;
    int Quantity;
    float HealthPercent;
    ref array<string> Attachments;
    void DeutschZSS_LoadoutItem()
    {
        ClassName = "";
        Quantity = 1;
        HealthPercent = 100.0;
        Attachments = new array<string>;
    }
}

class DeutschZSS_SpawnPoint
{
    string Id;
    string Name;
    string Description;
    vector Position;
    vector Orientation;
    int Enabled;
    int PremiumOnly;
    int GroupOnly;
    int RequireWhitelist;
    int CooldownSeconds;
    int UseSafeRadius;
    float SafeRadius;
    ref array<string> AllowedSteamIds;
    ref array<string> RequiredBattlepassTasks;
    ref array<string> RequiredBattlepassLevels;
    ref array<ref DeutschZSS_LoadoutItem> StarterLoadout;
    void DeutschZSS_SpawnPoint()
    {
        Id = "spawn";
        Name = "Spawn";
        Description = "";
        Position = "0 0 0";
        Orientation = "0 0 0";
        Enabled = 1;
        PremiumOnly = 0;
        GroupOnly = 0;
        RequireWhitelist = 0;
        CooldownSeconds = 0;
        UseSafeRadius = 1;
        SafeRadius = 25.0;
        AllowedSteamIds = new array<string>;
        RequiredBattlepassTasks = new array<string>;
        RequiredBattlepassLevels = new array<string>;
        StarterLoadout = new array<ref DeutschZSS_LoadoutItem>;
    }
}

class DeutschZSS_Config
{
    int ConfigVersion;
    int Enabled;
    string MenuTitle;
    int OpenOnFreshSpawn;
    int AllowRespawnMenu;
    int PreventSpawnInCombat;
    int CombatBlockSeconds;
    int GlobalCooldownSeconds;
    int EnableBattlepassBridge;
    int EnableGroupBridge;
    int EnablePremiumBridge;
    int DebugLogging;
    ref array<ref DeutschZSS_SpawnPoint> SpawnPoints;
    void DeutschZSS_Config()
    {
        ConfigVersion = 1;
        Enabled = 1;
        MenuTitle = "DeutschZ SpawnSelect";
        OpenOnFreshSpawn = 1;
        AllowRespawnMenu = 1;
        PreventSpawnInCombat = 1;
        CombatBlockSeconds = 300;
        GlobalCooldownSeconds = 600;
        EnableBattlepassBridge = 1;
        EnableGroupBridge = 1;
        EnablePremiumBridge = 1;
        DebugLogging = 0;
        SpawnPoints = new array<ref DeutschZSS_SpawnPoint>;
    }
}

class DeutschZSS_PlayerData
{
    string PlayerId;
    string LastSpawnId;
    int LastSpawnTime;
    ref map<string, int> SpawnCooldowns;
    void DeutschZSS_PlayerData()
    {
        PlayerId = "";
        LastSpawnId = "";
        LastSpawnTime = 0;
        SpawnCooldowns = new map<string, int>;
    }
}
