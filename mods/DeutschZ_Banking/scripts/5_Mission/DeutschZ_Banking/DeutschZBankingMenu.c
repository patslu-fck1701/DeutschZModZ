class DeutschZBankingMenu: UIScriptedMenu
{
    static ref DeutschZBankingMenu Current;

    protected TextWidget m_BalanceText;
    protected TextWidget m_InventoryText;
    protected EditBoxWidget m_AmountInput;
    protected ButtonWidget m_DepositButton;
    protected ButtonWidget m_WithdrawButton;
    protected ButtonWidget m_DepositAllButton;
    protected ButtonWidget m_CloseButton;

    static void Open()
    {
        if (Current) {
            return;
        }

        OpenLocal();
        GetGame().RPCSingleParam(null, DeutschZBankingRPCs.DEUTSCHZ_BANKING_SYNC, new Param1<bool>(true), true);
    }

    static void OpenLocal()
    {
        if (Current) {
            return;
        }

        Current = new DeutschZBankingMenu();
        GetGame().GetUIManager().ShowScriptedMenu(Current, null);
    }

    override Widget Init()
    {
        layoutRoot = GetGame().GetWorkspace().CreateWidgets("DeutschZ_Banking/gui/layouts/deutschz_atm.layout", null);
        m_BalanceText = TextWidget.Cast(layoutRoot.FindAnyWidget("BalanceText"));
        m_InventoryText = TextWidget.Cast(layoutRoot.FindAnyWidget("InventoryText"));
        m_AmountInput = EditBoxWidget.Cast(layoutRoot.FindAnyWidget("AmountInput"));
        m_DepositButton = ButtonWidget.Cast(layoutRoot.FindAnyWidget("DepositButton"));
        m_WithdrawButton = ButtonWidget.Cast(layoutRoot.FindAnyWidget("WithdrawButton"));
        m_DepositAllButton = ButtonWidget.Cast(layoutRoot.FindAnyWidget("DepositAllButton"));
        m_CloseButton = ButtonWidget.Cast(layoutRoot.FindAnyWidget("CloseButton"));
        return layoutRoot;
    }

    void ~DeutschZBankingMenu()
    {
        Current = null;
    }

    override void OnShow()
    {
        super.OnShow();
        GetGame().GetInput().ChangeGameFocus(1);
        GetGame().GetUIManager().ShowUICursor(true);
    }

    override void OnHide()
    {
        super.OnHide();
        GetGame().GetInput().ResetGameFocus();
        GetGame().GetUIManager().ShowUICursor(false);
    }

    void SetState(int balance, int inventoryMoney)
    {
        if (m_BalanceText) {
            m_BalanceText.SetText("Bank: " + balance + " MarkZ");
        }
        if (m_InventoryText) {
            m_InventoryText.SetText("Inventar: " + inventoryMoney + " MarkZ");
        }
    }

    int GetAmount()
    {
        if (!m_AmountInput) {
            return 0;
        }
        return m_AmountInput.GetText().ToInt();
    }

    override bool OnClick(Widget w, int x, int y, int button)
    {
        if (w == m_CloseButton) {
            Close();
            return true;
        }

        if (w == m_DepositButton) {
            GetGame().RPCSingleParam(null, DeutschZBankingRPCs.DEUTSCHZ_BANKING_DEPOSIT, new Param1<int>(GetAmount()), true);
            return true;
        }

        if (w == m_WithdrawButton) {
            GetGame().RPCSingleParam(null, DeutschZBankingRPCs.DEUTSCHZ_BANKING_WITHDRAW, new Param1<int>(GetAmount()), true);
            return true;
        }

        if (w == m_DepositAllButton) {
            GetGame().RPCSingleParam(null, DeutschZBankingRPCs.DEUTSCHZ_BANKING_DEPOSIT, new Param1<int>(2147483647), true);
            return true;
        }

        return super.OnClick(w, x, y, button);
    }
}
