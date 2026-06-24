/*
    DeutschZ_GroundZero
    Owner: Patrick Sluzalek / fck1701
    Module: 4_World / GroundZeroItemManager
    Purpose: Server-authoritative campaign item creation, counting and forced drop handling.
    Dependencies: DayZ scripts; optional CF/Expansion APIs only through adapter methods.
    Compliance: Original DeutschZ implementation. No copied foreign mod code, assets, configs or stubs.
*/

class GroundZeroItemManager
{
    protected GroundZeroConfig m_Config;
    protected GroundZeroPersistentState m_State;

    void GroundZeroItemManager(GroundZeroConfig cfg, GroundZeroPersistentState state)
    {
        m_Config = cfg;
        m_State = state;
    }

    EntityAI SpawnCampaignItem(string className, vector position)
    {
        if (!GetGame() || !GetGame().IsServer()) return null;
        if (DeutschZCore_UnsafeClassGuard.IsBlockedClass(className)) return null;
        if (!m_Config.IsCampaignItemClass(className) && className != m_Config.ItemFinalResearchCore) return null;

        EntityAI entity = EntityAI.Cast(GetGame().CreateObjectEx(className, position, ECE_PLACE_ON_SURFACE));
        if (entity)
        {
            entity.SetPosition(position);
            GroundZeroLogging.Info("Items", "Spawned " + className + " at " + position.ToString());
        }
        else
        {
            GroundZeroLogging.Error("Items", "Failed to spawn " + className);
        }

        return entity;
    }

    int DropCampaignItemsFromPlayer(PlayerBase player)
    {
        if (!player || !m_Config.RemoveCampaignItemsOnDeath) return 0;

        vector origin = player.GetPosition();
        array<EntityAI> found = new array<EntityAI>();
        CollectCampaignItems(player, found);

        foreach (EntityAI item : found)
        {
            if (!item) continue;

            string itemClass = item.GetType();
            player.ServerDropEntity(item);
            item.SetPosition(origin + Vector(Math.RandomFloat(-2, 2), 0, Math.RandomFloat(-2, 2)));

            GroundZeroDroppedItemRuntime drop = new GroundZeroDroppedItemRuntime();
            drop.ItemClass = itemClass;
            drop.Position = item.GetPosition();
            drop.DroppedAt = GetGame().GetTime() * 0.001;
            m_State.DroppedItems.Insert(drop);
        }

        if (found.Count() > 0)
        {
            GroundZeroLogging.Info("Items", "Dropped campaign items count=" + found.Count().ToString());
        }

        return found.Count();
    }

    void CollectCampaignItems(EntityAI root, array<EntityAI> outItems)
    {
        if (!root || !outItems || !root.GetInventory()) return;

        CargoBase cargo = root.GetInventory().GetCargo();
        if (!cargo) return;

        for (int i = 0; i < cargo.GetItemCount(); i++)
        {
            EntityAI item = cargo.GetItem(i);
            if (!item) continue;

            if (m_Config.IsCampaignItemClass(item.GetType())) outItems.Insert(item);
            CollectCampaignItems(item, outItems);
        }
    }

    int CountCampaignItems(PlayerBase player)
    {
        array<EntityAI> items = new array<EntityAI>();
        CollectCampaignItems(player, items);
        return items.Count();
    }
}
