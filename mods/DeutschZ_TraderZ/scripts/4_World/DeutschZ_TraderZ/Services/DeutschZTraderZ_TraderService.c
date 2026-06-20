class DeutschZTraderZ_TraderService
{
    protected static ref array<Object> m_SpawnedTraders;
    protected static bool m_Initialized;

    static void Init()
    {
        if (m_Initialized)
            return;
        m_Initialized = true;
        m_SpawnedTraders = new array<Object>;
        DeutschZTraderZ_ConfigManager.LoadAll();
        if (DeutschZTraderZ_ConfigManager.GetSettings().SpawnTradersOnServerStart)
            SpawnTraders();
    }

    static void ReloadAll()
    {
        DeleteSpawnedTraders();
        DeutschZTraderZ_ConfigManager.LoadAll();
        if (DeutschZTraderZ_ConfigManager.GetSettings().SpawnTradersOnServerStart)
            SpawnTraders();
    }

    static void DeleteSpawnedTraders()
    {
        if (!m_SpawnedTraders)
            m_SpawnedTraders = new array<Object>;
        foreach (Object obj : m_SpawnedTraders)
        {
            if (obj)
                GetGame().ObjectDelete(obj);
        }
        m_SpawnedTraders.Clear();
    }

    static void SpawnTraders()
    {
        array<ref DeutschZTraderZ_Trader> traders = DeutschZTraderZ_ConfigManager.GetTraders();
        if (!traders)
            return;
        if (!m_SpawnedTraders)
            m_SpawnedTraders = new array<Object>;

        for (int i = 0; i < traders.Count(); i++)
        {
            DeutschZTraderZ_Trader trader = traders.Get(i);
            if (!trader || !trader.Enabled || trader.ObjectClass == "")
                continue;

            Object obj = GetGame().CreateObject(trader.ObjectClass, trader.Position, false, true);
            if (!obj)
                continue;
            obj.SetPosition(trader.Position);
            obj.SetOrientation(trader.Orientation);
            m_SpawnedTraders.Insert(obj);

            PlayerBase npc = PlayerBase.Cast(obj);
            if (npc)
            {
                npc.DeutschZTraderZ_SetTrader(i, trader.IsP2PTrader, trader.IsDeliveryTrader);
                npc.SetAllowDamage(false);
                dBodyActive(npc, ActiveState.INACTIVE);
                npc.SetDynamicPhysicsLifeTime(-1);
                ApplyAppearance(npc, trader.Appearance);
                ApplyHandsItem(npc, trader.HandsItem, trader.HandsItemAttachments);
            }
        }
    }

    static void ApplyAppearance(PlayerBase npc, DeutschZTraderZ_Appearance appearance)
    {
        if (!npc || !appearance)
            return;
        EntityAI body;
        EntityAI pants;
        EntityAI shoes;
        EntityAI vest;
        EntityAI backpack;
        EntityAI gloves;
        EntityAI headgear;
        EntityAI mask;
        EntityAI glasses;
        EntityAI belt;

        if (appearance.Body != "") body = npc.GetInventory().CreateAttachment(appearance.Body);
        if (appearance.Pants != "") pants = npc.GetInventory().CreateAttachment(appearance.Pants);
        if (appearance.Shoes != "") shoes = npc.GetInventory().CreateAttachment(appearance.Shoes);
        if (appearance.Vest != "") vest = npc.GetInventory().CreateAttachment(appearance.Vest);
        if (appearance.Backpack != "") backpack = npc.GetInventory().CreateAttachment(appearance.Backpack);
        if (appearance.Gloves != "") gloves = npc.GetInventory().CreateAttachment(appearance.Gloves);
        if (appearance.Headgear != "") headgear = npc.GetInventory().CreateAttachment(appearance.Headgear);
        if (appearance.Mask != "") mask = npc.GetInventory().CreateAttachment(appearance.Mask);
        if (appearance.Glasses != "") glasses = npc.GetInventory().CreateAttachment(appearance.Glasses);
        if (appearance.Belt != "") belt = npc.GetInventory().CreateAttachment(appearance.Belt);

        ApplyAttachments(headgear, appearance.HeadgearAttachments);
        ApplyAttachments(vest, appearance.VestAttachments);
        ApplyAttachments(belt, appearance.BeltAttachments);
    }

    static void ApplyAttachments(EntityAI item, array<string> attachments)
    {
        if (!item || !attachments)
            return;
        foreach (string attachmentClass : attachments)
        {
            if (attachmentClass != "")
                item.GetInventory().CreateAttachment(attachmentClass);
        }
    }

    static void ApplyHandsItem(PlayerBase npc, string itemClass, array<string> attachments)
    {
        if (!npc || itemClass == "")
            return;
        EntityAI handsItem = npc.GetHumanInventory().CreateInHands(itemClass);
        ApplyAttachments(handsItem, attachments);
    }

    static void OpenTraderMenu(PlayerBase player, int traderIndex)
    {
        if (!player || !player.GetIdentity())
            return;
        array<ref DeutschZTraderZ_Trader> traders = DeutschZTraderZ_ConfigManager.GetTraders();
        if (!traders || traderIndex < 0 || traderIndex >= traders.Count())
            return;
        DeutschZTraderZ_Trader trader = traders.Get(traderIndex);
        if (!trader || !trader.Enabled)
            return;
        ref array<ref DeutschZTraderZ_MarketItem> items = DeutschZTraderZ_ConfigManager.GetItemsForCategories(trader.Categories);
        GetRPCManager().SendRPC(DeutschZTraderZ_Constants.RPC_MOD, DeutschZTraderZ_Constants.RPC_OPEN_MENU, new Param4<string, int, ref TStringArray, ref array<ref DeutschZTraderZ_MarketItem>>(trader.DisplayName, traderIndex, trader.Categories, items), true, player.GetIdentity());
    }

    static void SendCategory(PlayerBase player, string category)
    {
        if (!player || !player.GetIdentity())
            return;
        ref TStringArray categories = new TStringArray;
        categories.Insert(category);
        ref array<ref DeutschZTraderZ_MarketItem> items = DeutschZTraderZ_ConfigManager.GetItemsForCategories(categories);
        GetRPCManager().SendRPC(DeutschZTraderZ_Constants.RPC_MOD, DeutschZTraderZ_Constants.RPC_SYNC_ITEMS, new Param2<string, ref array<ref DeutschZTraderZ_MarketItem>>(category, items), true, player.GetIdentity());
    }

    static bool Buy(PlayerBase player, string className, int amount, out string message)
    {
        message = "";
        DeutschZTraderZ_Settings settings = DeutschZTraderZ_ConfigManager.GetSettings();
        if (!settings || !settings.Enabled)
        {
            message = "TraderZ disabled.";
            return false;
        }
        if (!player || className == "")
        {
            message = "Missing player or classname.";
            return false;
        }
        if (amount < 1) amount = 1;
        if (amount > settings.MaxBuyAmount) amount = settings.MaxBuyAmount;

        DeutschZTraderZ_MarketItem item = DeutschZTraderZ_ConfigManager.FindMarketItem(className);
        if (!item || !item.CanBuy || item.BuyPrice <= 0)
        {
            message = "Item cannot be bought.";
            return false;
        }
        int total = item.BuyPrice * amount;
        if (!DeutschZTraderZ_CurrencyService.HasEnoughMoney(player, total))
        {
            message = "Not enough money.";
            return false;
        }
        if (!DeutschZTraderZ_CurrencyService.RemoveMoney(player, total))
        {
            message = "Could not remove money.";
            return false;
        }

        vector spawnPos = GetSpawnPosition(player, item);
        vector spawnOri = player.GetOrientation();
        ref array<EntityAI> spawnedItems = new array<EntityAI>;
        for (int i = 0; i < amount; i++)
        {
            EntityAI bought = SpawnPurchasedItem(player, item, spawnPos, spawnOri);
            if (!bought)
            {
                DeleteSpawnedPurchaseItems(spawnedItems);
                DeutschZTraderZ_CurrencyService.AddMoney(player, total);
                message = "Could not spawn item. Money refunded.";
                break;
            }
            spawnedItems.Insert(bought);
        }
        if (message != "")
            return false;

        message = "Bought " + amount.ToString() + "x " + className + " for " + total.ToString() + ".";
        return true;
    }

    static void DeleteSpawnedPurchaseItems(array<EntityAI> items)
    {
        if (!items)
            return;
        foreach (EntityAI item : items)
        {
            if (item)
                GetGame().ObjectDelete(item);
        }
        items.Clear();
    }

    static EntityAI SpawnPurchasedItem(PlayerBase player, DeutschZTraderZ_MarketItem item, vector spawnPos, vector spawnOri)
    {
        if (!player || !item)
            return null;
        EntityAI entity;
        bool isVehicle = GetGame().IsKindOf(item.ClassName, "CarScript") || GetGame().IsKindOf(item.ClassName, "BoatScript");
        if (!isVehicle)
        {
            entity = EntityAI.Cast(player.GetInventory().CreateInInventory(item.ClassName));
            if (!entity && !player.GetHumanInventory().GetEntityInHands())
                entity = EntityAI.Cast(player.GetHumanInventory().CreateInHands(item.ClassName));
        }
        if (!entity)
            entity = EntityAI.Cast(GetGame().CreateObjectEx(item.ClassName, spawnPos, ECE_PLACE_ON_SURFACE));
        if (!entity)
            return null;
        entity.SetOrientation(spawnOri);
        ApplyBoughtAttachments(entity, item.SpawnAttachments);
        return entity;
    }

    static void ApplyBoughtAttachments(EntityAI entity, array<string> attachments)
    {
        if (!entity || !attachments)
            return;
        foreach (string attachment : attachments)
        {
            if (attachment != "")
                entity.GetInventory().CreateAttachment(attachment);
        }
    }

    static vector GetSpawnPosition(PlayerBase player, DeutschZTraderZ_MarketItem item)
    {
        vector pos = player.GetPosition() + (player.GetDirection() * 1.8);
        pos[1] = GetGame().SurfaceY(pos[0], pos[2]) + 0.05;
        if (!item || item.DeliveryGroup == "")
            return pos;
        array<ref DeutschZTraderZ_VehicleSpawnPoint> spawns = DeutschZTraderZ_ConfigManager.GetVehicleSpawns();
        foreach (DeutschZTraderZ_VehicleSpawnPoint sp : spawns)
        {
            if (sp && sp.GroupName == item.DeliveryGroup)
                return sp.Position;
        }
        return pos;
    }

    static bool Sell(PlayerBase player, string className, int amount, out string message)
    {
        message = "";
        DeutschZTraderZ_Settings settings = DeutschZTraderZ_ConfigManager.GetSettings();
        if (!settings || !settings.Enabled)
        {
            message = "TraderZ disabled.";
            return false;
        }
        if (!player || className == "")
        {
            message = "Missing player or classname.";
            return false;
        }
        if (amount < 1) amount = 1;
        if (amount > settings.MaxSellAmount) amount = settings.MaxSellAmount;

        DeutschZTraderZ_MarketItem item = DeutschZTraderZ_ConfigManager.FindMarketItem(className);
        if (!item || !item.CanSell || item.SellPrice <= 0)
        {
            message = "Item cannot be sold.";
            return false;
        }
        int removed = RemoveItemsFromPlayer(player, className, amount);
        if (removed <= 0)
        {
            message = "Item not found in inventory.";
            return false;
        }
        int payout = item.SellPrice * removed;
        DeutschZTraderZ_CurrencyService.AddMoney(player, payout);
        message = "Sold " + removed.ToString() + "x " + className + " for " + payout.ToString() + ".";
        return true;
    }

    static int RemoveItemsFromPlayer(PlayerBase player, string className, int amount)
    {
        ref array<EntityAI> items = new array<EntityAI>;
        DeutschZTraderZ_CurrencyService.CollectItems(player, items);
        int removed = 0;
        foreach (EntityAI entity : items)
        {
            if (!entity || entity.GetType() != className)
                continue;
            GetGame().ObjectDelete(entity);
            removed++;
            if (removed >= amount)
                break;
        }
        return removed;
    }
}
