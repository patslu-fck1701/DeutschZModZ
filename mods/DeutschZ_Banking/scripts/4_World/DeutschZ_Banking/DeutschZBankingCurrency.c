class DeutschZBankingCurrency
{
    protected static ref array<ref DeutschZCurrencyEntry> m_Currencies;

    static void EnsureFolders()
    {
        if (!FileExist(DeutschZBankingConstants.ROOT_FOLDER)) {
            MakeDirectory(DeutschZBankingConstants.ROOT_FOLDER);
        }
        if (!FileExist(DeutschZBankingConstants.BANKING_FOLDER)) {
            MakeDirectory(DeutschZBankingConstants.BANKING_FOLDER);
        }
        if (!FileExist(DeutschZBankingConstants.CONFIG_FOLDER)) {
            MakeDirectory(DeutschZBankingConstants.CONFIG_FOLDER);
        }
        if (!FileExist(DeutschZBankingConstants.DATA_FOLDER)) {
            MakeDirectory(DeutschZBankingConstants.DATA_FOLDER);
        }
        if (!FileExist(DeutschZBankingConstants.LOG_FOLDER)) {
            MakeDirectory(DeutschZBankingConstants.LOG_FOLDER);
        }
    }

    static ref array<ref DeutschZCurrencyEntry> Get()
    {
        if (!m_Currencies) {
            Load();
        }

        if (!m_Currencies) {
            m_Currencies = new array<ref DeutschZCurrencyEntry>();
            EnsureHardcodedDefaults();
        }

        return m_Currencies;
    }

    static void EnsureDefaultCurrency(string className, int value)
    {
        if (!m_Currencies) {
            m_Currencies = new array<ref DeutschZCurrencyEntry>();
        }

        foreach (DeutschZCurrencyEntry entry : m_Currencies) {
            if (entry && entry.ClassName == className) {
                entry.Value = value;
                return;
            }
        }

        m_Currencies.Insert(new DeutschZCurrencyEntry(className, value));
    }

    static void EnsureHardcodedDefaults()
    {
        EnsureDefaultCurrency("DZ_MarkZ_1", 1);
        EnsureDefaultCurrency("DZ_MarkZ_2", 2);
        EnsureDefaultCurrency("DZ_MarkZ_5", 5);
        EnsureDefaultCurrency("DZ_MarkZ_10", 10);
        EnsureDefaultCurrency("DZ_MarkZ_20", 20);
        EnsureDefaultCurrency("DZ_MarkZ_50", 50);
        EnsureDefaultCurrency("DZ_MarkZ_100", 100);
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

    static void Load()
    {
        EnsureFolders();
        m_Currencies = new array<ref DeutschZCurrencyEntry>();

        if (FileExist(DeutschZBankingConstants.CURRENCY_CONFIG)) {
            JsonFileLoader<array<ref DeutschZCurrencyEntry>>.JsonLoadFile(DeutschZBankingConstants.CURRENCY_CONFIG, m_Currencies);
        }

        if (!m_Currencies) {
            m_Currencies = new array<ref DeutschZCurrencyEntry>();
        }

        // Keep all DeutschZ MarkZ defaults even when an old or broken Currencies.json already exists.
        EnsureHardcodedDefaults();
        Save();
    }

    static void Save()
    {
        EnsureFolders();
        JsonFileLoader<array<ref DeutschZCurrencyEntry>>.JsonSaveFile(DeutschZBankingConstants.CURRENCY_CONFIG, Get());
    }

    static bool IsDeutschZMarkZClass(string className)
    {
        return className == "DZ_MarkZ_1" || className == "DZ_MarkZ_2" || className == "DZ_MarkZ_5" || className == "DZ_MarkZ_10" || className == "DZ_MarkZ_20" || className == "DZ_MarkZ_50" || className == "DZ_MarkZ_100";
    }

    static int GetCurrencyValue(string className)
    {
        if (className == "") {
            return 0;
        }

        // Hard fallback first: ATM must keep working even when Currencies.json is old, empty, malformed or partly NULL.
        int fallbackValue = GetHardcodedMarkZValue(className);
        if (fallbackValue > 0) {
            return fallbackValue;
        }

        ref array<ref DeutschZCurrencyEntry> currencies = Get();
        if (!currencies) {
            return 0;
        }

        foreach (DeutschZCurrencyEntry entry : currencies) {
            if (!entry || entry.Value <= 0 || entry.ClassName == "") {
                continue;
            }

            if (entry.ClassName == className) {
                return entry.Value;
            }
        }
        return 0;
    }

    static int GetCurrencyValueFromItem(EntityAI item)
    {
        if (!item) {
            return 0;
        }

        string itemType = item.GetType();
        int directValue = GetCurrencyValue(itemType);
        if (directValue > 0) {
            return directValue;
        }

        // Fallback: allow Currencies.json entries to point at a base class as well.
        ref array<ref DeutschZCurrencyEntry> currencies = Get();
        if (!currencies) {
            return 0;
        }

        foreach (DeutschZCurrencyEntry entry : currencies) {
            if (!entry || entry.Value <= 0 || entry.ClassName == "") {
                continue;
            }

            if (item.IsKindOf(entry.ClassName)) {
                return entry.Value;
            }
        }

        return 0;
    }

    static int GetSafeQuantity(EntityAI item)
    {
        if (!item) {
            return 0;
        }

        int quantity = Math.Round(item.GetQuantity());
        if (quantity <= 0) {
            quantity = 1;
        }
        return quantity;
    }

    static void CollectInventoryItems(EntityAI inventoryOwner, array<EntityAI> items)
    {
        if (!inventoryOwner || !items || !inventoryOwner.GetInventory()) {
            return;
        }

        inventoryOwner.GetInventory().EnumerateInventory(InventoryTraversalType.PREORDER, items);

        PlayerBase player = PlayerBase.Cast(inventoryOwner);
        if (player && player.GetHumanInventory()) {
            EntityAI hands = player.GetHumanInventory().GetEntityInHands();
            if (hands && items.Find(hands) == -1) {
                items.Insert(hands);
            }
        }
    }

    static int GetInventoryMoney(EntityAI inventoryOwner)
    {
        ref array<EntityAI> items = new array<EntityAI>();
        CollectInventoryItems(inventoryOwner, items);

        int total = 0;
        foreach (EntityAI item : items) {
            int value = GetCurrencyValueFromItem(item);
            if (value > 0) {
                total += GetSafeQuantity(item) * value;
            }
        }
        return total;
    }

    static int RemoveMoneyFromItem(EntityAI item, int removeQuantity)
    {
        if (!item || removeQuantity <= 0) {
            return 0;
        }

        int quantity = GetSafeQuantity(item);
        if (removeQuantity >= quantity) {
            GetGame().ObjectDelete(item);
            return quantity;
        }

        item.SetQuantity(quantity - removeQuantity);
        return removeQuantity;
    }

    static int RemoveInventoryMoney(PlayerBase player, int requestedAmount)
    {
        if (!player || requestedAmount <= 0) {
            return 0;
        }

        ref array<EntityAI> items = new array<EntityAI>();
        CollectInventoryItems(player, items);

        int removedValue = 0;

        // Remove only values that fit into requestedAmount. No overpaying bill deletion.
        for (int denominationPass = 1000000; denominationPass >= 1; denominationPass = denominationPass / 10) {
            foreach (EntityAI item : items) {
                if (!item || removedValue >= requestedAmount) {
                    continue;
                }

                int value = GetCurrencyValueFromItem(item);
                if (value <= 0 || value > denominationPass || value <= denominationPass / 10) {
                    continue;
                }

                int remaining = requestedAmount - removedValue;
                int quantity = GetSafeQuantity(item);
                int removeQuantity = Math.Min(quantity, remaining / value);
                if (removeQuantity <= 0) {
                    continue;
                }

                int actuallyRemoved = RemoveMoneyFromItem(item, removeQuantity);
                removedValue += actuallyRemoved * value;
            }
        }

        return removedValue;
    }

    static int RemoveInventoryMoneyExactAvailable(PlayerBase player, int requestedAmount)
    {
        int available = GetInventoryMoney(player);
        int amount = Math.Min(requestedAmount, available);
        return RemoveInventoryMoney(player, amount);
    }

    static bool CreateCurrencyItemInInventory(PlayerBase player, string className)
    {
        if (!player || !player.GetInventory() || className == "") {
            return false;
        }

        EntityAI created = player.GetInventory().CreateInInventory(className);
        if (!created) {
            return false;
        }

        return true;
    }

    static int AddInventoryMoney(PlayerBase player, int requestedAmount)
    {
        if (!player || !player.GetInventory() || requestedAmount <= 0) {
            return 0;
        }

        int remaining = requestedAmount;
        int added = 0;

        // Fixed MarkZ payout order. Creates real bill items one by one instead of risky quantity stacks.
        added += AddDenomination(player, "DZ_MarkZ_100", 100, remaining);
        remaining = requestedAmount - added;
        added += AddDenomination(player, "DZ_MarkZ_50", 50, remaining);
        remaining = requestedAmount - added;
        added += AddDenomination(player, "DZ_MarkZ_20", 20, remaining);
        remaining = requestedAmount - added;
        added += AddDenomination(player, "DZ_MarkZ_10", 10, remaining);
        remaining = requestedAmount - added;
        added += AddDenomination(player, "DZ_MarkZ_5", 5, remaining);
        remaining = requestedAmount - added;
        added += AddDenomination(player, "DZ_MarkZ_2", 2, remaining);
        remaining = requestedAmount - added;
        added += AddDenomination(player, "DZ_MarkZ_1", 1, remaining);

        return added;
    }

    static int AddDenomination(PlayerBase player, string className, int value, int amount)
    {
        if (!player || className == "" || value <= 0 || amount < value) {
            return 0;
        }

        int added = 0;
        while (amount - added >= value) {
            if (!CreateCurrencyItemInInventory(player, className)) {
                return added;
            }
            added += value;
        }

        return added;
    }
}
