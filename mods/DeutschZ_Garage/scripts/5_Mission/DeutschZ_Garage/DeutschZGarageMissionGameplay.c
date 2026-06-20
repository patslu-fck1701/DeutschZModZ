modded class MissionGameplay
{
    override void OnInit()
    {
        super.OnInit();
        GetDayZGame().Event_OnRPC.Insert(DeutschZGarage_ClientRPC);
    }

    override void OnMissionFinish()
    {
        if (GetDayZGame()) {
            GetDayZGame().Event_OnRPC.Remove(DeutschZGarage_ClientRPC);
        }
        super.OnMissionFinish();
    }

    void DeutschZGarage_ClientRPC(PlayerIdentity sender, Object target, int rpcType, ParamsReadContext ctx)
    {
        if (rpcType != DeutschZGarageRPCs.DEUTSCHZ_GARAGE_SYNC) {
            return;
        }

        if (!DeutschZGarageMenu.Current) {
            DeutschZGarageMenu.OpenLocal(target);
        }

        if (DeutschZGarageMenu.Current) {
            DeutschZGarageMenu.Current.ReadState(ctx);
        }
    }
}
