static int g_DeutschZOperationDeutschZ_Bootstrapped;

void DeutschZOperationDeutschZ_RequestSafeBoot(string source)
{
    if (!GetGame() || !GetGame().IsServer())
        return;

    if (g_DeutschZOperationDeutschZ_Bootstrapped == 1)
        return;

    g_DeutschZOperationDeutschZ_Bootstrapped = 1;
    DeutschZOperationDeutschZSafeBoot.Init();
}

modded class MissionServer
{
    void MissionServer()
    {
        DeutschZOperationDeutschZ_RequestSafeBoot("MissionServer constructor");
    }

    override void OnInit()
    {
        super.OnInit();
        DeutschZOperationDeutschZ_RequestSafeBoot("MissionServer OnInit");
    }

    override void OnMissionStart()
    {
        super.OnMissionStart();
        DeutschZOperationDeutschZ_RequestSafeBoot("MissionServer OnMissionStart");
    }
}
