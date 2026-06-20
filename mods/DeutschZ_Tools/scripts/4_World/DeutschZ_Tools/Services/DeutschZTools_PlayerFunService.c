class DeutschZTools_PlayerFunFreezeEntry
{
    string Steam64;
    vector Position;

    void DeutschZTools_PlayerFunFreezeEntry()
    {
        Steam64 = "";
        Position = "0 0 0";
    }
}

class DeutschZTools_PlayerFunService
{
    protected static ref array<ref DeutschZTools_PlayerFunFreezeEntry> s_FrozenPlayers;
    protected static bool s_FreezeTickRunning;

    protected static void EnsureState()
    {
        if (!s_FrozenPlayers)
            s_FrozenPlayers = new array<ref DeutschZTools_PlayerFunFreezeEntry>;
    }

    protected static DeutschZTools_PlayerFunFreezeEntry FindFreezeEntry(string steam64)
    {
        EnsureState();
        foreach (DeutschZTools_PlayerFunFreezeEntry entry : s_FrozenPlayers)
        {
            if (entry && entry.Steam64 == steam64)
                return entry;
        }
        return null;
    }

    protected static void StartFreezeTick()
    {
        if (s_FreezeTickRunning)
            return;
        s_FreezeTickRunning = true;
        int tickMs = DeutschZTools_SettingsService.Get().PlayerFunFreezeTickMs;
        if (tickMs < 100)
            tickMs = 100;
        GetGame().GetCallQueue(CALL_CATEGORY_SYSTEM).CallLater(FreezeTick, tickMs, true);
    }

    protected static void StopFreezeTickIfEmpty()
    {
        EnsureState();
        if (s_FrozenPlayers.Count() > 0)
            return;
        GetGame().GetCallQueue(CALL_CATEGORY_SYSTEM).Remove(FreezeTick);
        s_FreezeTickRunning = false;
    }

    static void FreezeTick()
    {
        EnsureState();
        if (s_FrozenPlayers.Count() == 0)
        {
            StopFreezeTickIfEmpty();
            return;
        }

        for (int i = s_FrozenPlayers.Count() - 1; i >= 0; i--)
        {
            DeutschZTools_PlayerFunFreezeEntry entry = s_FrozenPlayers.Get(i);
            if (!entry)
            {
                s_FrozenPlayers.Remove(i);
                continue;
            }

            PlayerBase player = DeutschZTools_PlayerService.GetPlayerBySteam64(entry.Steam64);
            if (!player || !player.IsAlive())
                continue;

            player.SetPosition(entry.Position);
            player.SetSynchDirty();
        }
    }

    static bool Freeze(string steam64, out string message)
    {
        PlayerBase player = DeutschZTools_PlayerService.GetPlayerBySteam64(steam64);
        if (!player)
        {
            message = "Target player not found: " + steam64;
            return false;
        }

        DeutschZTools_PlayerFunFreezeEntry entry = FindFreezeEntry(steam64);
        if (!entry)
        {
            entry = new DeutschZTools_PlayerFunFreezeEntry();
            entry.Steam64 = steam64;
            s_FrozenPlayers.Insert(entry);
        }

        entry.Position = player.GetPosition();
        StartFreezeTick();
        message = "Player frozen: " + steam64;
        return true;
    }

    static bool Unfreeze(string steam64, out string message)
    {
        EnsureState();
        for (int i = s_FrozenPlayers.Count() - 1; i >= 0; i--)
        {
            DeutschZTools_PlayerFunFreezeEntry entry = s_FrozenPlayers.Get(i);
            if (entry && entry.Steam64 == steam64)
            {
                s_FrozenPlayers.Remove(i);
                StopFreezeTickIfEmpty();
                message = "Player unfrozen: " + steam64;
                return true;
            }
        }

        message = "Player was not frozen: " + steam64;
        return false;
    }

    static bool Vomit(string steam64, out string message)
    {
        PlayerBase player = DeutschZTools_PlayerService.GetPlayerBySteam64(steam64);
        if (!player)
        {
            message = "Target player not found: " + steam64;
            return false;
        }

        if (player.GetSymptomManager())
        {
            player.GetSymptomManager().QueueUpPrimarySymptom(SymptomIDs.SYMPTOM_VOMIT);
            message = "Vomit symptom queued for: " + steam64;
            return true;
        }

        message = "Vomit failed: symptom manager missing.";
        return false;
    }

    static bool SetPlayerScale(string steam64, float scale, out string message)
    {
        PlayerBase player = DeutschZTools_PlayerService.GetPlayerBySteam64(steam64);
        if (!player)
        {
            message = "Target player not found: " + steam64;
            return false;
        }

        if (scale < 0.25)
            scale = 0.25;
        if (scale > 3.0)
            scale = 3.0;

        player.SetScale(scale);
        player.SetSynchDirty();
        message = "Player scale set to " + scale.ToString() + " for: " + steam64;
        return true;
    }

    static bool Tiny(string steam64, out string message)
    {
        float scale = DeutschZTools_SettingsService.Get().PlayerFunTinyScale;
        if (scale <= 0)
            scale = 0.65;
        return SetPlayerScale(steam64, scale, message);
    }

    static bool Giant(string steam64, out string message)
    {
        float scale = DeutschZTools_SettingsService.Get().PlayerFunGiantScale;
        if (scale <= 0)
            scale = 1.35;
        return SetPlayerScale(steam64, scale, message);
    }

    static bool ResetSize(string steam64, out string message)
    {
        return SetPlayerScale(steam64, 1.0, message);
    }

    static bool Spin(string steam64, out string message)
    {
        PlayerBase player = DeutschZTools_PlayerService.GetPlayerBySteam64(steam64);
        if (!player)
        {
            message = "Target player not found: " + steam64;
            return false;
        }

        vector ori = player.GetOrientation();
        ori[0] = ori[0] + 180.0;
        if (ori[0] > 360.0)
            ori[0] = ori[0] - 360.0;
        player.SetOrientation(ori);
        player.SetSynchDirty();
        message = "Player spun around: " + steam64;
        return true;
    }

    protected static bool SpawnAnimalAtPlayer(string steam64, string animalClass, out string message)
    {
        PlayerBase player = DeutschZTools_PlayerService.GetPlayerBySteam64(steam64);
        if (!player)
        {
            message = "Target player not found: " + steam64;
            return false;
        }

        vector pos = player.GetPosition();
        vector dir = player.GetDirection();
        pos = pos + (dir * 1.5);
        pos[1] = GetGame().SurfaceY(pos[0], pos[2]);

        Object animal = GetGame().CreateObjectEx(animalClass, pos, ECE_PLACE_ON_SURFACE);
        if (!animal)
        {
            message = "Animal spawn failed: " + animalClass;
            return false;
        }

        message = "PlayerFun animal prank spawned " + animalClass + " near " + steam64;
        return true;
    }

    static bool PigPrank(string steam64, out string message)
    {
        bool ok = SpawnAnimalAtPlayer(steam64, "Animal_SusDomesticus", message);
        if (ok)
            Tiny(steam64, message);
        return ok;
    }

    static bool GoatPrank(string steam64, out string message)
    {
        bool ok = SpawnAnimalAtPlayer(steam64, "Animal_CapraHircus", message);
        if (ok)
            Spin(steam64, message);
        return ok;
    }
}
