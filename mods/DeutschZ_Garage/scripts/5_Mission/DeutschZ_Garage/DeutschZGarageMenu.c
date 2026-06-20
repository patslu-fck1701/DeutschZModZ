class DeutschZGarageMenu: UIScriptedMenu
{
    static ref DeutschZGarageMenu Current;

    protected Object m_Station;
    protected TextListboxWidget m_VehicleList;
    protected ButtonWidget m_StoreButton;
    protected ButtonWidget m_RestoreButton;
    protected ButtonWidget m_CloseButton;
    protected TextWidget m_CountText;

    static void Open(Object station)
    {
        if (Current) {
            return;
        }

        OpenLocal(station);
        GetGame().RPCSingleParam(station, DeutschZGarageRPCs.DEUTSCHZ_GARAGE_SYNC, new Param1<bool>(true), true);
    }

    static void OpenLocal(Object station)
    {
        if (Current) {
            return;
        }

        Current = new DeutschZGarageMenu();
        Current.m_Station = station;
        GetGame().GetUIManager().ShowScriptedMenu(Current, null);
    }

    override Widget Init()
    {
        layoutRoot = GetGame().GetWorkspace().CreateWidgets("DeutschZ_Garage/gui/layouts/deutschz_parking_station.layout", null);
        m_VehicleList = TextListboxWidget.Cast(layoutRoot.FindAnyWidget("VehicleList"));
        m_StoreButton = ButtonWidget.Cast(layoutRoot.FindAnyWidget("StoreButton"));
        m_RestoreButton = ButtonWidget.Cast(layoutRoot.FindAnyWidget("RestoreButton"));
        m_CloseButton = ButtonWidget.Cast(layoutRoot.FindAnyWidget("CloseButton"));
        m_CountText = TextWidget.Cast(layoutRoot.FindAnyWidget("CountText"));
        return layoutRoot;
    }

    void ~DeutschZGarageMenu()
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

    void ReadState(ParamsReadContext ctx)
    {
        int count;
        if (!ctx.Read(count)) {
            return;
        }

        if (m_VehicleList) {
            m_VehicleList.ClearItems();
        }

        for (int i = 0; i < count; i++) {
            string className;
            string displayName;
            ctx.Read(className);
            ctx.Read(displayName);
            if (displayName == "") {
                displayName = className;
            }
            if (m_VehicleList) {
                m_VehicleList.AddItem(displayName + " [" + className + "]", null, 0);
            }
        }

        if (m_CountText) {
            m_CountText.SetText("Eingelagert: " + count);
        }
    }

    int GetSelectedIndex()
    {
        if (!m_VehicleList) {
            return -1;
        }
        return m_VehicleList.GetSelectedRow();
    }

    override bool OnClick(Widget w, int x, int y, int button)
    {
        if (w == m_CloseButton) {
            Close();
            return true;
        }

        if (w == m_StoreButton) {
            GetGame().RPCSingleParam(m_Station, DeutschZGarageRPCs.DEUTSCHZ_GARAGE_STORE, new Param1<bool>(true), true);
            return true;
        }

        if (w == m_RestoreButton) {
            GetGame().RPCSingleParam(m_Station, DeutschZGarageRPCs.DEUTSCHZ_GARAGE_RESTORE, new Param1<int>(GetSelectedIndex()), true);
            return true;
        }

        return super.OnClick(w, x, y, button);
    }
}
