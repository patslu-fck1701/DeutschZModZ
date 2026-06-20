class DeutschZTools_SpawnService
{
    static bool SpawnInFrontOfPlayer(PlayerBase admin, DeutschZTools_SpawnRequest request, out string message)
    {
        if (!admin)
        {
            message = "Admin player not found.";
            return false;
        }

        if (!request || request.ClassName == "")
        {
            message = "Classname missing.";
            return false;
        }

        if (!ClassExistsForSpawn(request.ClassName))
        {
            message = "Class not found: " + request.ClassName;
            return false;
        }

        PlayerBase spawnOwner = admin;
        if (request.SpawnMode == 1 && request.TargetSteam64 != "")
        {
            PlayerBase targetPlayer = DeutschZTools_PlayerService.GetPlayerBySteam64(request.TargetSteam64);
            if (!targetPlayer)
            {
                message = "Zielspieler nicht gefunden: " + request.TargetSteam64;
                return false;
            }
            spawnOwner = targetPlayer;
        }

        vector dir = spawnOwner.GetDirection();
        float spawnDistance = DeutschZTools_SettingsService.Get().SpawnObjectDistance;
        if (spawnDistance < 1.0)
            spawnDistance = 1.0;

        vector spawnOffset = dir * spawnDistance;
        vector pos = spawnOwner.GetPosition() + spawnOffset;
        pos[1] = GetGame().SurfaceY(pos[0], pos[2]) + 0.05;

        int flags = ECE_PLACE_ON_SURFACE | ECE_SETUP | ECE_UPDATEPATHGRAPH;
        Object obj = GetGame().CreateObjectEx(request.ClassName, pos, flags);
        if (!obj)
        {
            message = "CreateObjectEx failed: " + request.ClassName;
            return false;
        }

        EntityAI ent = EntityAI.Cast(obj);
        int attachmentCount = 0;

        if (ent && request.Attachments)
        {
            foreach (string att : request.Attachments)
            {
                if (att == "")
                    continue;

                if (!ClassExistsForSpawn(att))
                    continue;

                EntityAI createdAtt = ent.GetInventory().CreateAttachment(att);
                if (!createdAtt)
                    createdAtt = ent.GetInventory().CreateInInventory(att);

                if (createdAtt)
                    attachmentCount++;
            }
        }

        obj.SetOrientation(spawnOwner.GetOrientation());

        if (ent)
            ent.SetSynchDirty();

        if (attachmentCount > 0)
            message = "Gespawned: " + request.ClassName + " mit Anbauteilen: " + attachmentCount;
        else
            message = "Gespawned: " + request.ClassName;

        return true;
    }

    protected static bool ClassExistsForSpawn(string className)
    {
        if (GetGame().ConfigIsExisting("CfgVehicles " + className))
            return true;
        if (GetGame().ConfigIsExisting("CfgWeapons " + className))
            return true;
        if (GetGame().ConfigIsExisting("CfgMagazines " + className))
            return true;
        return false;
    }
}
