/*
DeutschZ ModZ
Eigenstaendige Implementierung fuer DeutschZ.
Autor/Eigentuemer: Patrick Sluzalek / fck1701.
Projekt: DeutschZ.
Modul: DeutschZ_ConvoyZ.
Zweck der Datei: Serverseitige ConvoyZ-Eventlogik, Ablauf, Status und Sicherheitspruefung.
Quellen-/Konzeptnachweis: Eigene DeutschZ-Implementierung; DayZ/CF/Expansion werden nur als Laufzeit-Abhaengigkeit/API genutzt.
Keine direkte Codeuebernahme aus Drittquellen.
*/

class DeutschZConvoyZRewardManager
{
    ref DeutschZConvoyZRewardClaims Claims;

    void DeutschZConvoyZRewardManager()
    {
        Claims = new DeutschZConvoyZRewardClaims();
    }

    void Load()
    {
        Claims = new DeutschZConvoyZRewardClaims();
        if (FileExist(DeutschZConvoyZConstants.CLAIMS_FILE)) JsonFileLoader<DeutschZConvoyZRewardClaims>.JsonLoadFile(DeutschZConvoyZConstants.CLAIMS_FILE, Claims);
        if (!Claims || !Claims.Claims) Claims = new DeutschZConvoyZRewardClaims();
    }

    void Save()
    {
        JsonFileLoader<DeutschZConvoyZRewardClaims>.JsonSaveFile(DeutschZConvoyZConstants.CLAIMS_FILE, Claims);
    }

    bool HasClaim(string eventId)
    {
        foreach (DeutschZConvoyZRewardClaim c: Claims.Claims)
        {
            if (c && c.EventId == eventId) return true;
        }
        return false;
    }

    bool Unlock(DeutschZConvoyZConfig cfg, DeutschZConvoyZRuntimeState state)
    {
        if (!cfg || !state || !cfg.EventData.Reward) return false;
        if (state.RewardProcessing == 1 || state.RewardUnlocked == 1) return false;
        if (cfg.Settings.RewardClaimOnce == 1 && HasClaim(state.EventId)) return false;
        state.RewardProcessing = 1;
        DeutschZConvoyZRewardDef reward = cfg.EventData.Reward;
        Object container = null;
        if (reward.RewardContainerClassName != "")
        {
            vector p = reward.RewardPosition;
            p[1] = GetGame().SurfaceY(p[0], p[2]) + 0.75;
            container = GetGame().CreateObjectEx(reward.RewardContainerClassName, p, ECE_SETUP | ECE_CREATEPHYSICS | ECE_UPDATEPATHGRAPH);
            if (container)
            {
                container.SetOrientation(reward.RewardOrientation);
                state.SpawnedRewards.Insert(container);
            }
        }
        SpawnItems(reward, container, state.EventId);
        state.RewardUnlocked = 1;
        state.RewardClaimed = 1;
        if (cfg.Settings.RewardClaimOnce == 1)
        {
            DeutschZConvoyZRewardClaim claim = new DeutschZConvoyZRewardClaim();
            claim.EventId = state.EventId;
            claim.ClaimedAt = GetGame().GetTime();
            Claims.Claims.Insert(claim);
            Save();
        }
        state.RewardProcessing = 0;
        DeutschZConvoyZLogger.Log("RewardUnlocked", state.EventId, "REWARD_UNLOCKED", "", reward.RewardPosition, "OK", "once");
        return true;
    }

    void SpawnItems(DeutschZConvoyZRewardDef reward, Object container, string eventId)
    {
        if (!reward || !reward.Items) return;
        EntityAI ent = EntityAI.Cast(container);
        foreach (DeutschZConvoyZRewardItemDef item: reward.Items)
        {
            if (!item || item.ClassName == "" || item.Quantity <= 0) continue;
            if (DeutschZCore_UnsafeClassGuard.IsBlockedClass(item.ClassName))
            {
                DeutschZConvoyZLogger.Log("RewardItemBlocked", eventId, "REWARD_UNLOCKED", "", reward.RewardPosition, "BLOCKED", item.ClassName);
                continue;
            }
            if (!DeutschZConvoyZValidator.IsConfiguredInventoryClass(item.ClassName))
            {
                DeutschZConvoyZLogger.Log("RewardItemClassMissing", eventId, "REWARD_UNLOCKED", "", reward.RewardPosition, "SKIPPED", item.ClassName);
                continue;
            }
            if (item.Chance < 1.0 && Math.RandomFloat01() > item.Chance) continue;
            for (int i = 0; i < item.Quantity; i++)
            {
                EntityAI created = null;
                if (ent) created = ent.GetInventory().CreateInInventory(item.ClassName);
                if (!created)
                {
                    vector p = reward.RewardPosition;
                    float rx = Math.RandomFloat(-1, 1);
                    float rz = Math.RandomFloat(-1, 1);
                    p[0] = p[0] + rx;
                    p[2] = p[2] + rz;
                    created = EntityAI.Cast(GetGame().CreateObjectEx(item.ClassName, p, ECE_SETUP | ECE_CREATEPHYSICS));
                }
                if (created) DeutschZConvoyZLogger.Log("RewardItemCreated", eventId, "REWARD_UNLOCKED", "", created.GetPosition(), "OK", item.ClassName);
            }
        }
    }
    void SpawnRewardItemSafe(EntityAI container, string className, int quantity, vector fallbackPos)
    {
        if (className == "") return;
        if (DeutschZCore_UnsafeClassGuard.IsBlockedClass(className)) return;
        if (!DeutschZConvoyZValidator.IsConfiguredInventoryClass(className)) return;
        if (quantity <= 0) quantity = 1;

        for (int i = 0; i < quantity; i++)
        {
            EntityAI item = null;

            if (container)
            {
                item = EntityAI.Cast(container.GetInventory().CreateInInventory(className));
            }

            if (!item)
            {
                float dx = Math.RandomFloat(-1.5, 1.5);
                float dz = Math.RandomFloat(-1.5, 1.5);
                vector p = fallbackPos;
                p[0] = p[0] + dx;
                p[2] = p[2] + dz;
                p[1] = GetGame().SurfaceY(p[0], p[2]) + 0.75;
                item = EntityAI.Cast(GetGame().CreateObjectEx(className, p, ECE_PLACE_ON_SURFACE | ECE_SETUP));
            }

            if (item) item.SetHealth01("", "", 1.0);
        }
    }


}
