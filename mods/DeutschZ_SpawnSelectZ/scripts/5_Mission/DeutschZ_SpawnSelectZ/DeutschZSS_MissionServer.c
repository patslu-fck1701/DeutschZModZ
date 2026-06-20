
modded class MissionServer
{
    override void OnInit()
    {
        super.OnInit();
        DeutschZSS_GetManager().Init();
    }

    override void InvokeOnConnect(PlayerBase player, PlayerIdentity identity)
    {
        super.InvokeOnConnect(player, identity);
    }
}
