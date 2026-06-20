
static ref DeutschZSS_Manager g_DeutschZSS_Manager;
DeutschZSS_Manager DeutschZSS_GetManager()
{
    if (!g_DeutschZSS_Manager) g_DeutschZSS_Manager = new DeutschZSS_Manager();
    return g_DeutschZSS_Manager;
}

class DeutschZSS_Manager
{
    ref DeutschZSS_Config m_Config;
    ref map<string, ref DeutschZSS_PlayerData> m_PlayerData;

    void DeutschZSS_Manager()
    {
        m_PlayerData = new map<string, ref DeutschZSS_PlayerData>;
    }

    void Init()
    {
        EnsureFolders();
        LoadConfig();
    }

    void EnsureFolders()
    {
        MakeDirectory("$profile:DeutschZ");
        MakeDirectory("$profile:DeutschZ/Spawnselect");
        MakeDirectory(DeutschZSS_Constants.CONFIG_DIR);
        MakeDirectory(DeutschZSS_Constants.DATA_DIR);
    }

    void LoadConfig()
    {
        m_Config = new DeutschZSS_Config();
        if (FileExist(DeutschZSS_Constants.CONFIG_FILE))
        {
            JsonFileLoader<DeutschZSS_Config>.JsonLoadFile(DeutschZSS_Constants.CONFIG_FILE, m_Config);
        }
        else
        {
            CreateDefaultConfig();
            SaveConfig();
        }
        if (!m_Config.SpawnPoints) m_Config.SpawnPoints = new array<ref DeutschZSS_SpawnPoint>;
    }

    void SaveConfig()
    {
        JsonFileLoader<DeutschZSS_Config>.JsonSaveFile(DeutschZSS_Constants.CONFIG_FILE, m_Config);
    }

    void CreateDefaultConfig()
    {
        m_Config = new DeutschZSS_Config();
        DeutschZSS_SpawnPoint coast = new DeutschZSS_SpawnPoint();
        coast.Id = "coast_balota";
        coast.Name = "Coast - Balota";
        coast.Description = "Starter coast spawn.";
        coast.Position = "4520 0 2440";
        coast.Orientation = "0 0 0";
        m_Config.SpawnPoints.Insert(coast);

        DeutschZSS_SpawnPoint inland = new DeutschZSS_SpawnPoint();
        inland.Id = "inland_village";
        inland.Name = "Inland Village";
        inland.Description = "Safer inland start.";
        inland.Position = "7500 0 7500";
        inland.Orientation = "0 0 0";
        inland.CooldownSeconds = 1800;
        m_Config.SpawnPoints.Insert(inland);

        DeutschZSS_SpawnPoint premium = new DeutschZSS_SpawnPoint();
        premium.Id = "premium_safehouse";
        premium.Name = "Premium Safehouse";
        premium.Description = "Premium only example spawn.";
        premium.Position = "9500 0 3200";
        premium.Orientation = "0 0 0";
        premium.PremiumOnly = 1;
        premium.CooldownSeconds = 3600;
        m_Config.SpawnPoints.Insert(premium);
    }

    bool CanUseSpawn(PlayerBase player, string spawnId)
    {
        if (!m_Config || m_Config.Enabled == 0) return false;
        DeutschZSS_SpawnPoint sp = FindSpawn(spawnId);
        if (!sp || sp.Enabled == 0) return false;
        if (sp.PremiumOnly && m_Config.EnablePremiumBridge)
        {
            if (!DeutschZSS_HasPremium(player)) return false;
        }
        return true;
    }

    DeutschZSS_SpawnPoint FindSpawn(string spawnId)
    {
        if (!m_Config || !m_Config.SpawnPoints) return null;
        foreach (DeutschZSS_SpawnPoint sp: m_Config.SpawnPoints)
        {
            if (sp && sp.Id == spawnId) return sp;
        }
        return null;
    }

    void SelectSpawn(PlayerBase player, string spawnId)
    {
        if (!player) return;
        if (!CanUseSpawn(player, spawnId)) return;
        DeutschZSS_SpawnPoint sp = FindSpawn(spawnId);
        if (!sp) return;
        player.SetPosition(sp.Position);
        player.SetOrientation(sp.Orientation);
        ApplyLoadout(player, sp);
        DeutschZSS_AwardBattlepassXP(player, "spawnselect_used", 0);
    }

    void ApplyLoadout(PlayerBase player, DeutschZSS_SpawnPoint sp)
    {
        if (!player || !sp || !sp.StarterLoadout) return;
        foreach (DeutschZSS_LoadoutItem li: sp.StarterLoadout)
        {
            if (!li || li.ClassName == "") continue;
            EntityAI ent = player.GetInventory().CreateInInventory(li.ClassName);
            if (!ent) ent = player.SpawnEntityOnGroundPos(li.ClassName, player.GetPosition());
            if (ent && li.HealthPercent >= 0) ent.SetHealth01("", "", li.HealthPercent / 100.0);
        }
    }
}

bool DeutschZSS_HasPremium(PlayerBase player)
{
    // Bridge hook: Battlepass can override later. Default true for non-premium spawns only.
    if (!player) return false;
    return false;
}

void DeutschZSS_AwardBattlepassXP(PlayerBase player, string reason, int amount)
{
    // Bridge hook for DeutschZ_BattlepassZ. Kept empty to avoid hard dependency.
}
