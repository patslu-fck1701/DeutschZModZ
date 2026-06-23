static int g_DeutschZOperationDeutschZ_Bootstrapped;

void DeutschZOperationDeutschZ_RequestSafeBoot(string source)
{
    if (!GetGame() || !GetGame().IsServer())
        return;

    if (g_DeutschZOperationDeutschZ_Bootstrapped == 1)
        return;

    g_DeutschZOperationDeutschZ_Bootstrapped = 1;
<<<<<<< Updated upstream
    DeutschZOperationDeutschZSafeBoot.Init();
=======
    Print("[DeutschZ_OperationDeutschZ] SafeBoot requested source=" + source);
    DeutschZOperationDeutschZSafeBoot.Init();
    Print("[DeutschZ_OperationDeutschZ] SafeBoot finished source=" + source);
}

void DeutschZOperationDeutschZ_DelayedSafeBoot()
{
    DeutschZOperationDeutschZ_RequestSafeBoot("MissionServer delayed fallback");
}

void DeutschZOperationDeutschZ_ScheduleDelayedSafeBoot()
{
    if (!GetGame())
        return;

    GetGame().GetCallQueue(CALL_CATEGORY_SYSTEM).CallLater(DeutschZOperationDeutschZ_DelayedSafeBoot, 1000, false);
    GetGame().GetCallQueue(CALL_CATEGORY_SYSTEM).CallLater(DeutschZOperationDeutschZ_DelayedSafeBoot, 5000, false);
>>>>>>> Stashed changes
}

modded class MissionServer
{
    void MissionServer()
    {
        DeutschZOperationDeutschZ_RequestSafeBoot("MissionServer constructor");
<<<<<<< Updated upstream
=======
        DeutschZOperationDeutschZ_ScheduleDelayedSafeBoot();
>>>>>>> Stashed changes
    }

    override void OnInit()
    {
        super.OnInit();
        DeutschZOperationDeutschZ_RequestSafeBoot("MissionServer OnInit");
<<<<<<< Updated upstream
=======
        DeutschZOperationDeutschZ_ScheduleDelayedSafeBoot();
>>>>>>> Stashed changes
    }

    override void OnMissionStart()
    {
        super.OnMissionStart();
        DeutschZOperationDeutschZ_RequestSafeBoot("MissionServer OnMissionStart");
<<<<<<< Updated upstream
=======
        DeutschZOperationDeutschZ_ScheduleDelayedSafeBoot();
>>>>>>> Stashed changes
    }
}
