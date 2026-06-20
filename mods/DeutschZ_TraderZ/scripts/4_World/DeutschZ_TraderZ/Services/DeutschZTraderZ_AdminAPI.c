class DeutschZTraderZAdminAPI
{
    static bool ReloadAll(out string message)
    {
        DeutschZTraderZ_TraderService.ReloadAll();
        message = "TraderZ configs, market and NPCs reloaded.";
        return true;
    }

    static bool ReloadSettings(out string message)
    {
        DeutschZTraderZ_ConfigManager.LoadSettings();
        message = "TraderZ settings reloaded.";
        return true;
    }

    static bool ReloadTraders(out string message)
    {
        DeutschZTraderZ_TraderService.DeleteSpawnedTraders();
        DeutschZTraderZ_ConfigManager.LoadTraders();
        if (DeutschZTraderZ_ConfigManager.GetSettings().SpawnTradersOnServerStart)
            DeutschZTraderZ_TraderService.SpawnTraders();
        message = "TraderZ traders reloaded and NPCs refreshed.";
        return true;
    }

    static bool ReloadMarket(out string message)
    {
        DeutschZTraderZ_ConfigManager.EnsureDefaultMarketFiles();
        DeutschZTraderZ_ConfigManager.LoadMarketFiles();
        message = "TraderZ market files reloaded.";
        return true;
    }

    static bool ReloadCurrency(out string message)
    {
        DeutschZTraderZ_ConfigManager.LoadCurrency();
        message = "TraderZ MarkZ currency config reloaded.";
        return true;
    }

    static bool ReloadSafezones(out string message)
    {
        DeutschZTraderZ_ConfigManager.LoadSafezones();
        message = "TraderZ safezones reloaded.";
        return true;
    }

    static bool GetStatus(out string message)
    {
        DeutschZTraderZ_ConfigManager.LoadAll();
        array<ref DeutschZTraderZ_Trader> traders = DeutschZTraderZ_ConfigManager.GetTraders();
        array<string> categories = DeutschZTraderZ_ConfigManager.GetAllConfiguredCategories();
        array<ref DeutschZTraderZ_CurrencyEntry> currency = DeutschZTraderZ_ConfigManager.GetCurrencies();
        DeutschZTraderZ_Settings settings = DeutschZTraderZ_ConfigManager.GetSettings();

        string enabledText = "disabled";
        if (settings && settings.Enabled)
            enabledText = "active";

        string payMode = "MarkZ cash";
        if (settings && settings.EnableBankingBridge && settings.UseBankingBalanceIfInventoryMoneyMissing)
            payMode = "MarkZ cash + Banking fallback";

        message = "TraderZ " + enabledText + ". Traders " + traders.Count().ToString() + ", categories " + categories.Count().ToString() + ", currency entries " + currency.Count().ToString() + ", payment " + payMode + ".";
        return true;
    }

    static bool BuildTraderRows(array<string> rows, out string message)
    {
        if (!rows)
        {
            message = "Rows buffer missing.";
            return false;
        }

        rows.Clear();
        array<ref DeutschZTraderZ_Trader> traders = DeutschZTraderZ_ConfigManager.GetTraders();
        foreach (DeutschZTraderZ_Trader trader : traders)
        {
            if (!trader)
                continue;

            string state = "disabled";
            if (trader.Enabled)
                state = "active";

            rows.Insert("Trader|" + trader.DisplayName + "|" + state + "|" + trader.TraderID + " @ " + trader.Position.ToString());
        }

        message = "TraderZ trader rows built: " + rows.Count().ToString();
        return true;
    }

    static bool BuildCategoryRows(array<string> rows, out string message)
    {
        if (!rows)
        {
            message = "Rows buffer missing.";
            return false;
        }

        rows.Clear();
        array<string> categories = DeutschZTraderZ_ConfigManager.GetAllConfiguredCategories();
        foreach (string category : categories)
        {
            ref TStringArray single = new TStringArray;
            single.Insert(category);
            array<ref DeutschZTraderZ_MarketItem> items = DeutschZTraderZ_ConfigManager.GetItemsForCategories(single);
            rows.Insert("Category|" + category + "|Items " + items.Count().ToString() + "|profiles/DeutschZ/TraderZ/Market/" + category + ".json");
        }

        message = "TraderZ category rows built: " + rows.Count().ToString();
        return true;
    }

    static bool BuildMarketRows(string category, array<string> rows, out string message)
    {
        if (!rows)
        {
            message = "Rows buffer missing.";
            return false;
        }

        rows.Clear();
        category.Trim();
        if (category == "")
            category = "Food";

        ref TStringArray categories = new TStringArray;
        categories.Insert(category);
        array<ref DeutschZTraderZ_MarketItem> items = DeutschZTraderZ_ConfigManager.GetItemsForCategories(categories);

        foreach (DeutschZTraderZ_MarketItem item : items)
        {
            if (!item)
                continue;

            string flags = "";
            if (item.CanBuy)
                flags = flags + "B";
            if (item.CanSell)
                flags = flags + "S";
            if (flags == "")
                flags = "locked";

            rows.Insert(category + "|" + item.ClassName + "|Buy " + item.BuyPrice.ToString() + " / Sell " + item.SellPrice.ToString() + "|" + flags);
        }

        message = "TraderZ market rows built for " + category + ": " + rows.Count().ToString();
        return true;
    }

    static bool BuildCurrencyRows(array<string> rows, out string message)
    {
        if (!rows)
        {
            message = "Rows buffer missing.";
            return false;
        }

        rows.Clear();
        array<ref DeutschZTraderZ_CurrencyEntry> currency = DeutschZTraderZ_ConfigManager.GetCurrencies();
        foreach (DeutschZTraderZ_CurrencyEntry entry : currency)
        {
            if (!entry)
                continue;
            rows.Insert("Currency|" + entry.ClassName + "|Value " + entry.Value.ToString() + "|MarkZ");
        }

        message = "TraderZ currency rows built: " + rows.Count().ToString();
        return true;
    }
}
