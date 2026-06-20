modded class MissionServer
{
    override void OnInit()
    {
        super.OnInit();

        GetRPCManager().AddRPC(DeutschZTraderZ_Constants.RPC_MOD, DeutschZTraderZ_Constants.RPC_BUY, this, SingleplayerExecutionType.Server);
        GetRPCManager().AddRPC(DeutschZTraderZ_Constants.RPC_MOD, DeutschZTraderZ_Constants.RPC_SELL, this, SingleplayerExecutionType.Server);
        GetRPCManager().AddRPC(DeutschZTraderZ_Constants.RPC_MOD, DeutschZTraderZ_Constants.RPC_REQUEST_CATEGORY, this, SingleplayerExecutionType.Server);
        GetRPCManager().AddRPC(DeutschZTraderZ_Constants.RPC_MOD, DeutschZTraderZ_Constants.RPC_ADMIN_STATUS, this, SingleplayerExecutionType.Server);
        GetRPCManager().AddRPC(DeutschZTraderZ_Constants.RPC_MOD, DeutschZTraderZ_Constants.RPC_ADMIN_RELOAD, this, SingleplayerExecutionType.Server);

        GetGame().GetCallQueue(CALL_CATEGORY_SYSTEM).CallLater(DeutschZTraderZ_TraderService.Init, 1000, false);
    }

    void RPC_Buy(CallType type, ParamsReadContext ctx, PlayerIdentity sender, Object target)
    {
        if (type != CallType.Server)
            return;

        Param2<string, int> pBuy;
        if (!ctx.Read(pBuy))
            return;

        HandleBuy(sender, pBuy.param1, pBuy.param2);
    }

    void RPC_Sell(CallType type, ParamsReadContext ctx, PlayerIdentity sender, Object target)
    {
        if (type != CallType.Server)
            return;

        Param2<string, int> pSell;
        if (!ctx.Read(pSell))
            return;

        HandleSell(sender, pSell.param1, pSell.param2);
    }

    void RPC_RequestCategory(CallType type, ParamsReadContext ctx, PlayerIdentity sender, Object target)
    {
        if (type != CallType.Server)
            return;

        Param1<string> pCat;
        if (!ctx.Read(pCat))
            return;

        HandleCategory(sender, pCat.param1);
    }

    void RPC_AdminStatus(CallType type, ParamsReadContext ctx, PlayerIdentity sender, Object target)
    {
        if (type != CallType.Server)
            return;

        HandleAdminStatus(sender);
    }

    void RPC_AdminReload(CallType type, ParamsReadContext ctx, PlayerIdentity sender, Object target)
    {
        if (type != CallType.Server)
            return;

        HandleAdminReload(sender);
    }

    // TraderZ uses CF RPCManager only.
    // Do not override MissionServer.OnRPC here: in the current DayZ server mission base this function is not available.

    void HandleBuy(PlayerIdentity sender, string className, int amount)
    {
        PlayerBase player = GetPlayerByIdentity(sender);
        if (!player)
            return;

        string buyMessage;
        bool buyOk = DeutschZTraderZ_TraderService.Buy(player, className, amount, buyMessage);
        SendTraderZNotify(player, buyOk, buyMessage);
    }

    void HandleSell(PlayerIdentity sender, string className, int amount)
    {
        PlayerBase player = GetPlayerByIdentity(sender);
        if (!player)
            return;

        string sellMessage;
        bool sellOk = DeutschZTraderZ_TraderService.Sell(player, className, amount, sellMessage);
        SendTraderZNotify(player, sellOk, sellMessage);
    }

    void HandleCategory(PlayerIdentity sender, string category)
    {
        PlayerBase player = GetPlayerByIdentity(sender);
        if (!player)
            return;

        DeutschZTraderZ_TraderService.SendCategory(player, category);
    }

    void HandleAdminStatus(PlayerIdentity sender)
    {
        PlayerBase player = GetPlayerByIdentity(sender);
        if (!player)
            return;

        string statusMessage;
        bool statusOk = DeutschZTraderZAdminAPI.GetStatus(statusMessage);
        SendTraderZNotify(player, statusOk, statusMessage);
    }

    void HandleAdminReload(PlayerIdentity sender)
    {
        PlayerBase player = GetPlayerByIdentity(sender);
        if (!player)
            return;

        string reloadMessage;
        bool reloadOk = DeutschZTraderZAdminAPI.ReloadAll(reloadMessage);
        SendTraderZNotify(player, reloadOk, reloadMessage);
    }

    PlayerBase GetPlayerByIdentity(PlayerIdentity identity)
    {
        if (!identity)
            return null;

        ref array<Man> players = new array<Man>;
        GetGame().GetPlayers(players);
        foreach (Man man : players)
        {
            PlayerBase player = PlayerBase.Cast(man);
            if (player && player.GetIdentity() && player.GetIdentity().GetId() == identity.GetId())
                return player;
        }

        return null;
    }

    void SendTraderZNotify(PlayerBase player, bool success, string message)
    {
        if (!player || !player.GetIdentity())
            return;

        GetRPCManager().SendRPC(DeutschZTraderZ_Constants.RPC_MOD, DeutschZTraderZ_Constants.RPC_NOTIFY, new Param2<bool, string>(success, message), true, player.GetIdentity());
    }
}
