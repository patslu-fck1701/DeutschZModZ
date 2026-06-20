modded class MissionGameplay
{
    protected ref DeutschZTraderZ_Menu m_DeutschZTraderZ_Menu;

    override void OnInit()
    {
        super.OnInit();

        GetRPCManager().AddRPC(DeutschZTraderZ_Constants.RPC_MOD, DeutschZTraderZ_Constants.RPC_OPEN_MENU, this, SingleplayerExecutionType.Client);
        GetRPCManager().AddRPC(DeutschZTraderZ_Constants.RPC_MOD, DeutschZTraderZ_Constants.RPC_SYNC_ITEMS, this, SingleplayerExecutionType.Client);
        GetRPCManager().AddRPC(DeutschZTraderZ_Constants.RPC_MOD, DeutschZTraderZ_Constants.RPC_NOTIFY, this, SingleplayerExecutionType.Client);
    }

    void RPC_OpenMenu(CallType type, ParamsReadContext ctx, PlayerIdentity sender, Object target)
    {
        if (type != CallType.Client)
            return;

        Param4<string, int, ref TStringArray, ref array<ref DeutschZTraderZ_MarketItem>> data;
        if (!ctx.Read(data))
            return;

        OpenDeutschZTraderZMenu(data.param1, data.param2, data.param3, data.param4);
    }

    void RPC_SyncItems(CallType type, ParamsReadContext ctx, PlayerIdentity sender, Object target)
    {
        if (type != CallType.Client)
            return;

        Param2<string, ref array<ref DeutschZTraderZ_MarketItem>> itemData;
        if (!ctx.Read(itemData))
            return;

        if (m_DeutschZTraderZ_Menu)
            m_DeutschZTraderZ_Menu.SetItems(itemData.param1, itemData.param2);
    }

    void RPC_Notify(CallType type, ParamsReadContext ctx, PlayerIdentity sender, Object target)
    {
        if (type != CallType.Client)
            return;

        Param2<bool, string> notify;
        if (!ctx.Read(notify))
            return;

        if (m_DeutschZTraderZ_Menu)
            m_DeutschZTraderZ_Menu.SetStatus(notify.param2);
        else
            Print(DeutschZTraderZ_Constants.LOG_PREFIX + notify.param2);
    }

    void OpenDeutschZTraderZMenu(string traderName, int traderIndex, array<string> categories, array<ref DeutschZTraderZ_MarketItem> items)
    {
        if (!m_DeutschZTraderZ_Menu)
            m_DeutschZTraderZ_Menu = new DeutschZTraderZ_Menu();

        m_DeutschZTraderZ_Menu.SetInitialData(traderName, traderIndex, categories, items);
        GetGame().GetUIManager().ShowScriptedMenu(m_DeutschZTraderZ_Menu, null);
        GetGame().GetMission().PlayerControlDisable(INPUT_EXCLUDE_ALL);
        if (GetGame().GetMission().GetHud())
            GetGame().GetMission().GetHud().Show(false);
    }
}
