modded class PlayerBase
{
    override void OnRPC(PlayerIdentity sender, int rpc_type, ParamsReadContext ctx)
    {
        super.OnRPC(sender, rpc_type, ctx);

        if (!GetGame())
            return;

        if (GetGame().IsServer())
        {
            if (rpc_type != DeutschZTools_RPC.CLIENT_REQUEST)
                return;

            int action;
            if (!ctx.Read(action))
                return;

            DeutschZTools_Server.HandleAction(sender, action, ctx);
            return;
        }

        if (rpc_type == DeutschZTools_RPC.SERVER_RESULT)
        {
            DeutschZTools_ClientInbox.HandleResultRPC(ctx);
            return;
        }

        if (rpc_type == DeutschZTools_RPC.SERVER_PLAYER_LIST)
        {
            DeutschZTools_ClientInbox.HandlePlayerListRPC(ctx);
            return;
        }

        if (rpc_type == DeutschZTools_RPC.SERVER_GARAGE_LIST)
        {
            DeutschZTools_ClientInbox.HandleGarageListRPC(ctx);
            return;
        }

        if (rpc_type == DeutschZTools_RPC.SERVER_BANKING_LIST)
        {
            DeutschZTools_ClientInbox.HandleBankingListRPC(ctx);
            return;
        }

        if (rpc_type == DeutschZTools_RPC.SERVER_GROUPS_LIST)
        {
            DeutschZTools_ClientInbox.HandleGroupsListRPC(ctx);
            return;
        }

        if (rpc_type == DeutschZTools_RPC.SERVER_TRADERZ_LIST)
        {
            DeutschZTools_ClientInbox.HandleTraderZListRPC(ctx);
            return;
        }
    }

    void DeutschZTools_HealFull()
    {
        SetHealth("", "Health", GetMaxHealth("", "Health"));
        SetHealth("GlobalHealth", "Health", GetMaxHealth("GlobalHealth", "Health"));
        SetHealth("GlobalHealth", "Blood", GetMaxHealth("GlobalHealth", "Blood"));
        SetHealth("GlobalHealth", "Shock", GetMaxHealth("GlobalHealth", "Shock"));

        if (GetStatWater())
            GetStatWater().Set(5000);

        if (GetStatEnergy())
            GetStatEnergy().Set(5000);

        if (GetBleedingManagerServer())
            GetBleedingManagerServer().RemoveAllSources();

        SetSynchDirty();
    }
}
