modded class MissionServer
{
    protected int m_DeutschZOperationDeutschZ_Bootstrapped;

    void MissionServer()
    {
        DeutschZOperationDeutschZ_RequestSafeBoot("MissionServer constructor");
        DeutschZOperationDeutschZ_ScheduleDelayedSafeBoot();
    }

    protected void DeutschZOperationDeutschZ_RequestSafeBoot(string source)
    {
        if (!GetGame() || !GetGame().IsServer())
            return;

        if (m_DeutschZOperationDeutschZ_Bootstrapped == 1)
            return;

        m_DeutschZOperationDeutschZ_Bootstrapped = 1;
        Print("[DeutschZ_OperationDeutschZ] SafeBoot requested source=" + source);
        DeutschZOperationDeutschZSafeBoot.Init();
        Print("[DeutschZ_OperationDeutschZ] SafeBoot finished source=" + source);
    }

    protected void DeutschZOperationDeutschZ_DelayedSafeBoot()
    {
        DeutschZOperationDeutschZ_RequestSafeBoot("MissionServer delayed fallback");
    }

    protected void DeutschZOperationDeutschZ_ScheduleDelayedSafeBoot()
    {
        if (!GetGame())
            return;

        GetGame().GetCallQueue(CALL_CATEGORY_SYSTEM).CallLater(this.DeutschZOperationDeutschZ_DelayedSafeBoot, 1000, false);
        GetGame().GetCallQueue(CALL_CATEGORY_SYSTEM).CallLater(this.DeutschZOperationDeutschZ_DelayedSafeBoot, 5000, false);
    }

    override void OnInit()
    {
        super.OnInit();
        DeutschZOperationDeutschZ_RequestSafeBoot("MissionServer OnInit");
        DeutschZOperationDeutschZ_ScheduleDelayedSafeBoot();
    }

    override void OnMissionStart()
    {
        super.OnMissionStart();
        DeutschZOperationDeutschZ_RequestSafeBoot("MissionServer OnMissionStart");
        DeutschZOperationDeutschZ_ScheduleDelayedSafeBoot();
    }
}
