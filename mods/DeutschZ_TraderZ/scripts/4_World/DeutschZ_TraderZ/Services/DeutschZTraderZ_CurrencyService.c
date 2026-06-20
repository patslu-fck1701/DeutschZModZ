class DeutschZTraderZ_CurrencyService
{
    static int GetPhysicalMoney(PlayerBase player)
    {
        if (!player)
            return 0;

        #ifdef DEUTSCHZ_BANKING
        return DeutschZBankingCurrency.GetInventoryMoney(player);
        #endif

        ref array<EntityAI> items = new array<EntityAI>;
        CollectItems(player, items);
        int total = 0;
        foreach (EntityAI item : items)
        {
            total += GetItemMoneyValue(item);
        }
        return total;
    }

    static int GetHardcodedMarkZValue(string className)
    {
        if (className == "DZ_MarkZ_1") return 1;
        if (className == "DZ_MarkZ_2") return 2;
        if (className == "DZ_MarkZ_5") return 5;
        if (className == "DZ_MarkZ_10") return 10;
        if (className == "DZ_MarkZ_20") return 20;
        if (className == "DZ_MarkZ_50") return 50;
        if (className == "DZ_MarkZ_100") return 100;
        return 0;
    }

    static int GetItemMoneyValue(EntityAI item)
    {
        if (!item)
            return 0;

        string itemType = item.GetType();
        int hardcodedValue = GetHardcodedMarkZValue(itemType);
        if (hardcodedValue > 0)
            return hardcodedValue;

        array<ref DeutschZTraderZ_CurrencyEntry> entries = DeutschZTraderZ_ConfigManager.GetCurrencies();
        foreach (DeutschZTraderZ_CurrencyEntry entry : entries)
        {
            if (!entry || entry.ClassName == "" || entry.Value <= 0)
                continue;
            if (entry.ClassName != itemType)
                continue;

            int quantity = 1;
            ItemBase ib = ItemBase.Cast(item);
            if (ib && ib.HasQuantity())
            {
                quantity = Math.Round(ib.GetQuantity());
                if (quantity < 1)
                    quantity = 1;
            }
            return entry.Value * quantity;
        }
        return 0;
    }

    static void CollectItems(EntityAI root, array<EntityAI> outItems)
    {
        if (!root || !outItems || !root.GetInventory())
            return;
        ref array<EntityAI> cargoItems = new array<EntityAI>;
        root.GetInventory().EnumerateInventory(InventoryTraversalType.PREORDER, cargoItems);
        foreach (EntityAI item : cargoItems)
        {
            if (item)
                outItems.Insert(item);
        }
    }

    static bool HasEnoughMoney(PlayerBase player, int amount)
    {
        if (amount <= 0)
            return true;
        if (!player)
            return false;

        DeutschZTraderZ_Settings settings = DeutschZTraderZ_ConfigManager.GetSettings();
        if (!settings)
            return false;

        if (settings.EnableBankingBridge && settings.PreferBankingBalance && HasEnoughBankMoney(player, amount))
            return true;

        if (settings.EnablePhysicalCurrency && GetPhysicalMoney(player) >= amount)
            return true;

        if (settings.EnableBankingBridge && settings.UseBankingBalanceIfInventoryMoneyMissing && HasEnoughBankMoney(player, amount))
            return true;

        return false;
    }

    static bool HasEnoughBankMoney(PlayerBase player, int amount)
    {
        #ifdef DEUTSCHZ_BANKING
        if (player && player.GetIdentity())
        {
            string playerName;
            int balance;
            int updatedAt;
            string message;
            if (DeutschZBankingAdminAPI.GetAccountInfo(player.GetIdentity().GetId(), playerName, balance, updatedAt, message))
                return balance >= amount;
        }
        #endif
        return false;
    }

    static bool RemoveMoney(PlayerBase player, int amount)
    {
        if (amount <= 0)
            return true;
        if (!player)
            return false;

        DeutschZTraderZ_Settings settings = DeutschZTraderZ_ConfigManager.GetSettings();
        if (!settings)
            return false;

        if (settings.EnableBankingBridge && settings.PreferBankingBalance && RemoveBankMoney(player, amount))
            return true;

        if (settings.EnablePhysicalCurrency && GetPhysicalMoney(player) >= amount)
            return RemovePhysicalMoney(player, amount);

        if (settings.EnableBankingBridge && settings.UseBankingBalanceIfInventoryMoneyMissing && RemoveBankMoney(player, amount))
            return true;

        return false;
    }

    static bool RemoveBankMoney(PlayerBase player, int amount)
    {
        #ifdef DEUTSCHZ_BANKING
        if (player && player.GetIdentity())
        {
            string removeMessage;
            return DeutschZBankingAdminAPI.RemoveMoneyBySteamID(player.GetIdentity().GetId(), amount, removeMessage);
        }
        #endif
        return false;
    }

    static bool AddMoney(PlayerBase player, int amount)
    {
        if (amount <= 0)
            return true;
        if (!player)
            return false;

        DeutschZTraderZ_Settings settings = DeutschZTraderZ_ConfigManager.GetSettings();
        if (!settings)
            return false;

        if (settings.EnableBankingBridge && settings.PreferBankingBalance && AddBankMoney(player, amount))
            return true;

        if (settings.EnablePhysicalCurrency && AddPhysicalMoney(player, amount))
            return true;

        if (settings.EnableBankingBridge && AddBankMoney(player, amount))
            return true;

        return false;
    }

    static bool AddBankMoney(PlayerBase player, int amount)
    {
        #ifdef DEUTSCHZ_BANKING
        if (player && player.GetIdentity())
        {
            string addMessage;
            return DeutschZBankingAdminAPI.AddMoneyBySteamID(player.GetIdentity().GetId(), amount, addMessage);
        }
        #endif
        return false;
    }

    static bool RemovePhysicalMoney(PlayerBase player, int amount)
    {
        if (!player || amount <= 0)
            return false;

        #ifdef DEUTSCHZ_BANKING
        return DeutschZBankingCurrency.RemoveInventoryMoneyExactAvailable(player, amount) == amount;
        #endif

        ref array<EntityAI> items = new array<EntityAI>;
        CollectItems(player, items);
        int paid = 0;

        for (int i = 0; i < items.Count(); i++)
        {
            EntityAI item = items.Get(i);
            int value = GetItemMoneyValue(item);
            if (value <= 0)
                continue;

            ItemBase ib = ItemBase.Cast(item);
            int unitValue = GetSingleUnitValue(item.GetType());
            if (ib && ib.HasQuantity() && unitValue > 0)
            {
                int quantity = Math.Round(ib.GetQuantity());
                if (quantity < 1)
                    quantity = 1;
                while (quantity > 0 && paid < amount)
                {
                    quantity--;
                    paid += unitValue;
                }
                if (quantity > 0)
                    ib.SetQuantity(quantity);
                else
                    GetGame().ObjectDelete(item);
            }
            else
            {
                paid += value;
                GetGame().ObjectDelete(item);
            }

            if (paid >= amount)
                break;
        }

        if (paid < amount)
            return false;

        int change = paid - amount;
        if (change > 0)
            return AddPhysicalMoney(player, change);

        return true;
    }

    static int GetSingleUnitValue(string className)
    {
        int hardcodedValue = GetHardcodedMarkZValue(className);
        if (hardcodedValue > 0)
            return hardcodedValue;

        array<ref DeutschZTraderZ_CurrencyEntry> entries = DeutschZTraderZ_ConfigManager.GetCurrencies();
        foreach (DeutschZTraderZ_CurrencyEntry entry : entries)
        {
            if (entry && entry.ClassName == className)
                return entry.Value;
        }
        return 0;
    }

    static bool AddPhysicalMoney(PlayerBase player, int amount)
    {
        if (!player || amount <= 0)
            return false;

        #ifdef DEUTSCHZ_BANKING
        return DeutschZBankingCurrency.AddInventoryMoney(player, amount) == amount;
        #endif

        array<ref DeutschZTraderZ_CurrencyEntry> entries = DeutschZTraderZ_ConfigManager.GetCurrencies();
        if (!entries || entries.Count() == 0)
            return false;

        ref array<ref DeutschZTraderZ_CurrencyEntry> sorted = new array<ref DeutschZTraderZ_CurrencyEntry>;
        foreach (DeutschZTraderZ_CurrencyEntry entry : entries)
        {
            if (entry && entry.Value > 0 && entry.ClassName != "")
                sorted.Insert(entry);
        }

        for (int a = 0; a < sorted.Count(); a++)
        {
            for (int b = a + 1; b < sorted.Count(); b++)
            {
                if (sorted.Get(b).Value > sorted.Get(a).Value)
                {
                    DeutschZTraderZ_CurrencyEntry tmp = sorted.Get(a);
                    sorted.Set(a, sorted.Get(b));
                    sorted.Set(b, tmp);
                }
            }
        }

        int remaining = amount;
        foreach (DeutschZTraderZ_CurrencyEntry cur : sorted)
        {
            while (remaining >= cur.Value)
            {
                EntityAI money = EntityAI.Cast(player.GetInventory().CreateInInventory(cur.ClassName));
                if (!money)
                    money = EntityAI.Cast(GetGame().CreateObjectEx(cur.ClassName, player.GetPosition(), ECE_PLACE_ON_SURFACE));
                if (!money)
                    return false;
                remaining -= cur.Value;
            }
        }

        return remaining == 0;
    }
}
