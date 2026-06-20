class DeutschZTraderZ_Menu extends UIScriptedMenu
{
    protected TextWidget m_Title;
    protected TextWidget m_Status;
    protected MultilineTextWidget m_CategoryText;
    protected MultilineTextWidget m_ItemText;
    protected EditBoxWidget m_CategoryBox;
    protected EditBoxWidget m_ClassBox;
    protected EditBoxWidget m_AmountBox;
    protected ButtonWidget m_ButtonLoadCategory;
    protected ButtonWidget m_ButtonBuy;
    protected ButtonWidget m_ButtonSell;
    protected ButtonWidget m_ButtonClose;

    protected string m_TraderName;
    protected int m_TraderIndex;
    protected ref TStringArray m_Categories;
    protected ref array<ref DeutschZTraderZ_MarketItem> m_Items;

    void DeutschZTraderZ_Menu()
    {
        m_TraderName = "TraderZ";
        m_TraderIndex = -1;
        m_Categories = new TStringArray;
        m_Items = new array<ref DeutschZTraderZ_MarketItem>;
    }

    void SetInitialData(string traderName, int traderIndex, array<string> categories, array<ref DeutschZTraderZ_MarketItem> items)
    {
        m_TraderName = traderName;
        m_TraderIndex = traderIndex;
        m_Categories = new TStringArray;
        if (categories)
        {
            foreach (string cat : categories)
                m_Categories.Insert(cat);
        }
        m_Items = items;
        if (!m_Items)
            m_Items = new array<ref DeutschZTraderZ_MarketItem>;
        RefreshTexts();
    }

    override Widget Init()
    {
        layoutRoot = GetGame().GetWorkspace().CreateWidgets("DeutschZ_TraderZ/gui/layouts/deutschz_traderz_menu.layout");
        m_Title = TextWidget.Cast(layoutRoot.FindAnyWidget("TraderZTitle"));
        m_Status = TextWidget.Cast(layoutRoot.FindAnyWidget("TraderZStatus"));
        m_CategoryText = MultilineTextWidget.Cast(layoutRoot.FindAnyWidget("TraderZCategoryText"));
        m_ItemText = MultilineTextWidget.Cast(layoutRoot.FindAnyWidget("TraderZItemText"));
        m_CategoryBox = EditBoxWidget.Cast(layoutRoot.FindAnyWidget("TraderZCategoryBox"));
        m_ClassBox = EditBoxWidget.Cast(layoutRoot.FindAnyWidget("TraderZClassBox"));
        m_AmountBox = EditBoxWidget.Cast(layoutRoot.FindAnyWidget("TraderZAmountBox"));
        m_ButtonLoadCategory = ButtonWidget.Cast(layoutRoot.FindAnyWidget("TraderZButtonLoadCategory"));
        m_ButtonBuy = ButtonWidget.Cast(layoutRoot.FindAnyWidget("TraderZButtonBuy"));
        m_ButtonSell = ButtonWidget.Cast(layoutRoot.FindAnyWidget("TraderZButtonSell"));
        m_ButtonClose = ButtonWidget.Cast(layoutRoot.FindAnyWidget("TraderZButtonClose"));
        RefreshTexts();
        return layoutRoot;
    }

    void RefreshTexts()
    {
        if (m_Title)
            m_Title.SetText(m_TraderName);
        if (m_Status)
            m_Status.SetText("Ready");
        if (m_CategoryText)
        {
            string cats = "Categories:\n";
            foreach (string cat : m_Categories)
                cats = cats + "- " + cat + "\n";
            m_CategoryText.SetText(cats);
        }
        if (m_CategoryBox && m_Categories && m_Categories.Count() > 0 && m_CategoryBox.GetText() == "")
            m_CategoryBox.SetText(m_Categories.Get(0));
        if (m_AmountBox && m_AmountBox.GetText() == "")
            m_AmountBox.SetText("1");
        RefreshItems();
    }

    void SetItems(string category, array<ref DeutschZTraderZ_MarketItem> items)
    {
        m_Items = items;
        if (!m_Items)
            m_Items = new array<ref DeutschZTraderZ_MarketItem>;
        if (m_CategoryBox && category != "")
            m_CategoryBox.SetText(category);
        RefreshItems();
    }

    void RefreshItems()
    {
        if (!m_ItemText)
            return;
        string text = "Classname | Buy | Sell\n";
        text = text + "--------------------------------\n";
        foreach (DeutschZTraderZ_MarketItem item : m_Items)
        {
            if (!item)
                continue;
            text = text + item.ClassName + " | " + item.BuyPrice.ToString() + " | " + item.SellPrice.ToString() + "\n";
        }
        m_ItemText.SetText(text);
    }

    void SetStatus(string status)
    {
        if (m_Status)
            m_Status.SetText(status);
    }

    int GetAmount()
    {
        if (!m_AmountBox)
            return 1;
        string amountText = m_AmountBox.GetText();
        int amount = amountText.ToInt();
        if (amount < 1)
            amount = 1;
        return amount;
    }

    override bool OnClick(Widget w, int x, int y, int button)
    {
        if (w == m_ButtonClose)
        {
            Close();
            return true;
        }
        if (w == m_ButtonLoadCategory)
        {
            if (m_CategoryBox)
                GetRPCManager().SendRPC(DeutschZTraderZ_Constants.RPC_MOD, DeutschZTraderZ_Constants.RPC_REQUEST_CATEGORY, new Param1<string>(m_CategoryBox.GetText()), true, null);
            return true;
        }
        if (w == m_ButtonBuy)
        {
            if (m_ClassBox)
                GetRPCManager().SendRPC(DeutschZTraderZ_Constants.RPC_MOD, DeutschZTraderZ_Constants.RPC_BUY, new Param2<string, int>(m_ClassBox.GetText(), GetAmount()), true, null);
            return true;
        }
        if (w == m_ButtonSell)
        {
            if (m_ClassBox)
                GetRPCManager().SendRPC(DeutschZTraderZ_Constants.RPC_MOD, DeutschZTraderZ_Constants.RPC_SELL, new Param2<string, int>(m_ClassBox.GetText(), GetAmount()), true, null);
            return true;
        }
        return super.OnClick(w, x, y, button);
    }

    override void OnHide()
    {
        super.OnHide();
        Mission mission = GetGame().GetMission();
        if (mission)
        {
            mission.PlayerControlEnable(true);
            if (mission.GetHud())
                mission.GetHud().Show(true);
        }
    }
}
