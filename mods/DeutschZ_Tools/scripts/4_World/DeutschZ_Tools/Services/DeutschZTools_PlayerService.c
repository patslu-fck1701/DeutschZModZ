class DeutschZTools_PlayerService
{
    static PlayerBase GetPlayerByIdentity(PlayerIdentity identity)
    {
        if (!identity)
            return null;

        return GetPlayerBySteam64(identity.GetPlainId());
    }

    static PlayerBase GetPlayerBySteam64(string steam64)
    {
        if (steam64 == "")
            return null;

        ref array<Man> players = new array<Man>;
        GetGame().GetPlayers(players);

        foreach (Man man : players)
        {
            PlayerBase player = PlayerBase.Cast(man);
            if (!player || !player.GetIdentity())
                continue;

            if (player.GetIdentity().GetPlainId() == steam64)
                return player;
        }

        return null;
    }

    static bool Heal(PlayerBase player, out string message)
    {
        if (!player)
        {
            message = "Player not found.";
            return false;
        }

        player.DeutschZTools_HealFull();
        message = "Player healed.";
        return true;
    }

    static bool Teleport(PlayerBase player, vector targetPos, out string message)
    {
        if (!player)
        {
            message = "Player not found.";
            return false;
        }

        float surfaceY = GetGame().SurfaceY(targetPos[0], targetPos[2]);
        if (surfaceY < -1000.0 || surfaceY > 2000.0)
        {
            vector currentPos = player.GetPosition();
            surfaceY = currentPos[1];
        }

        targetPos[1] = surfaceY + 0.10;
        player.SetPosition(targetPos);
        player.SetOrientation(player.GetOrientation());
        player.SetSynchDirty();

        message = "Teleported to " + targetPos.ToString();
        return true;
    }

    static bool TeleportToPlayer(PlayerBase adminPlayer, string targetSteam64, out string message)
    {
        if (!adminPlayer)
        {
            message = "Admin player not found.";
            return false;
        }

        PlayerBase targetPlayer = GetPlayerBySteam64(targetSteam64);
        if (!targetPlayer)
        {
            message = "Target player not found: " + targetSteam64;
            return false;
        }

        vector pos = targetPlayer.GetPosition();
        pos[0] = pos[0] + 1.0;
        return Teleport(adminPlayer, pos, message);
    }

    static bool BringPlayer(PlayerBase adminPlayer, string targetSteam64, out string message)
    {
        if (!adminPlayer)
        {
            message = "Admin player not found.";
            return false;
        }

        PlayerBase targetPlayer = GetPlayerBySteam64(targetSteam64);
        if (!targetPlayer)
        {
            message = "Target player not found: " + targetSteam64;
            return false;
        }

        vector pos = adminPlayer.GetPosition();
        pos[0] = pos[0] + 1.0;
        return Teleport(targetPlayer, pos, message);
    }

    static bool HealBySteam64(string targetSteam64, out string message)
    {
        PlayerBase targetPlayer = GetPlayerBySteam64(targetSteam64);
        if (!targetPlayer)
        {
            message = "Target player not found: " + targetSteam64;
            return false;
        }

        return Heal(targetPlayer, message);
    }

    static void BuildPlayerList(array<ref DeutschZTools_PlayerSnapshot> snapshots)
    {
        if (!snapshots)
            return;

        snapshots.Clear();

        ref array<Man> players = new array<Man>;
        GetGame().GetPlayers(players);

        foreach (Man man : players)
        {
            PlayerBase player = PlayerBase.Cast(man);
            if (!player)
                continue;

            DeutschZTools_PlayerSnapshot snap = new DeutschZTools_PlayerSnapshot();
            snap.Position = player.GetPosition();
            snap.IsAlive = player.IsAlive();

            if (player.GetIdentity())
            {
                snap.Steam64 = player.GetIdentity().GetPlainId();
                snap.Name = player.GetIdentity().GetName();
            }

            snap.Health01 = player.GetHealth01("", "Health");
            snap.Blood01 = player.GetHealth01("GlobalHealth", "Blood");
            snap.Shock01 = player.GetHealth01("GlobalHealth", "Shock");
            snapshots.Insert(snap);
        }
    }
}
