modded class MissionServer
{
    override void OnInit()
    {
        super.OnInit();
        DeutschZGarageConfig.Load();
        DeutschZGaragePlayer.EnsureFolders();
        DeutschZGarageVehicleRules.Load();
        DeutschZGarageStations.Load();
        DeutschZGarageImpoundConfig.Load();
        DeutschZGarageStations.Get().SpawnConfiguredStations();
        GetDayZGame().Event_OnRPC.Insert(DeutschZGarage_OnRPC);
    }

    void DeutschZGarage_OnRPC(PlayerIdentity sender, Object target, int rpcType, ParamsReadContext ctx)
    {
        if (!sender || rpcType <= DeutschZGarageRPCs.DEUTSCHZ_GARAGE_RPC_START || rpcType >= DeutschZGarageRPCs.DEUTSCHZ_GARAGE_RPC_END) {
            return;
        }

        PlayerBase player = DeutschZGaragePlayerLookup.GetPlayerByIdentity(sender);
        if (!player) {
            return;
        }

        if (rpcType == DeutschZGarageRPCs.DEUTSCHZ_GARAGE_STORE) {
            DeutschZGarageService.StoreNearestVehicle(player, target);
        } else if (rpcType == DeutschZGarageRPCs.DEUTSCHZ_GARAGE_RESTORE) {
            Param1<int> restoreParam;
            if (ctx.Read(restoreParam)) {
                DeutschZGarageService.RestoreVehicle(player, target, restoreParam.param1);
            }
        }

        DeutschZGarage_SendState(player, target);
    }

    void DeutschZGarage_SendState(PlayerBase player, Object station)
    {
        if (!player || !player.GetIdentity()) {
            return;
        }

        DeutschZGaragePlayer playerGarage = DeutschZGaragePlayer.Load(player.GetIdentity());
        ScriptRPC rpc = new ScriptRPC();
        int count = 0;
        if (playerGarage && playerGarage.Vehicles) {
            count = playerGarage.Vehicles.Count();
        }
        rpc.Write(count);
        for (int i = 0; i < count; i++) {
            DeutschZGarageVehicle vehicle = playerGarage.Vehicles.Get(i);
            rpc.Write(vehicle.ClassName);
            rpc.Write(vehicle.DisplayName);
        }
        rpc.Send(station, DeutschZGarageRPCs.DEUTSCHZ_GARAGE_SYNC, true, player.GetIdentity());
    }
}
