/*
    DeutschZ ModZ
    Autor/Eigentuemer: Patrick Sluzalek / fck1701
    Projekt: DeutschZ
    Zweck: Serverseitiger Core-Bootstrap fuer Profile/Configs.
    No-Copy-Bestaetigung: Kein Code, keine Assets und keine Configs aus fremden Mods kopiert.
*/

modded class MissionServer
{
    protected int m_DeutschZCore_Bootstrapped;

    void MissionServer()
    {
        DeutschZCore_RequestBootstrap("MissionServer constructor");
        DeutschZCore_ScheduleDelayedBootstrap();
    }

    protected void DeutschZCore_RequestBootstrap(string source)
    {
        if (!GetGame() || !GetGame().IsServer())
            return;

        if (m_DeutschZCore_Bootstrapped == 1)
            return;

        m_DeutschZCore_Bootstrapped = 1;

        Print("[DeutschZ_Core] Init start source=" + source);
        DeutschZCore_ServerProfile.EnsureRoot();
        DeutschZCore_Log.Info("Core", "MissionServer initialized source=" + source);
        Print("[DeutschZ_Core] Init done");
    }

    protected void DeutschZCore_DelayedBootstrap()
    {
        DeutschZCore_RequestBootstrap("MissionServer delayed fallback");
    }

    protected void DeutschZCore_ScheduleDelayedBootstrap()
    {
        if (!GetGame())
            return;

        GetGame().GetCallQueue(CALL_CATEGORY_SYSTEM).CallLater(this.DeutschZCore_DelayedBootstrap, 1000, false);
        GetGame().GetCallQueue(CALL_CATEGORY_SYSTEM).CallLater(this.DeutschZCore_DelayedBootstrap, 5000, false);
    }

    override void OnInit()
    {
        super.OnInit();
        DeutschZCore_RequestBootstrap("MissionServer OnInit");
        DeutschZCore_ScheduleDelayedBootstrap();
    }

    override void OnMissionStart()
    {
        super.OnMissionStart();
        DeutschZCore_RequestBootstrap("MissionServer OnMissionStart");
        DeutschZCore_ScheduleDelayedBootstrap();
    }
}
