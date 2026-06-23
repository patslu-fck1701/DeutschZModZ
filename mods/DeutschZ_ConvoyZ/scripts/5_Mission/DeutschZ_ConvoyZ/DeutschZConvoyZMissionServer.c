/*
DeutschZ ModZ
Eigenstaendige Implementierung fuer DeutschZ.
Autor/Eigentuemer: Patrick Sluzalek / fck1701.
Projekt: DeutschZ.
Modul: DeutschZ_ConvoyZ.
Zweck der Datei: Robuster serverseitiger Bootstrap fuer Config/State-Erzeugung.
*/

modded class MissionServer
{
    protected int m_DeutschZConvoyZ_Bootstrapped;

    void MissionServer()
    {
        DeutschZConvoyZ_Bootstrap("MissionServer constructor");
        DeutschZConvoyZ_ScheduleDelayedBootstrap();
    }

    protected void DeutschZConvoyZ_Bootstrap(string source)
    {
        if (!GetGame() || !GetGame().IsServer())
            return;

        if (m_DeutschZConvoyZ_Bootstrapped == 1)
            return;

        m_DeutschZConvoyZ_Bootstrapped = 1;
        Print("[DeutschZ_ConvoyZ] Bootstrap requested source=" + source);

        DeutschZConvoyZManager mgr = DeutschZConvoyZ_GetManager();
        if (mgr)
            mgr.Init();

        Print("[DeutschZ_ConvoyZ] Bootstrap from " + source + " finished");
    }

    protected void DeutschZConvoyZ_DelayedBootstrap()
    {
        DeutschZConvoyZ_Bootstrap("MissionServer delayed fallback");
    }

    protected void DeutschZConvoyZ_ScheduleDelayedBootstrap()
    {
        if (!GetGame())
            return;

        GetGame().GetCallQueue(CALL_CATEGORY_SYSTEM).CallLater(this.DeutschZConvoyZ_DelayedBootstrap, 1000, false);
        GetGame().GetCallQueue(CALL_CATEGORY_SYSTEM).CallLater(this.DeutschZConvoyZ_DelayedBootstrap, 5000, false);
    }

    override void OnInit()
    {
        super.OnInit();
        DeutschZConvoyZ_Bootstrap("MissionServer OnInit");
        DeutschZConvoyZ_ScheduleDelayedBootstrap();
    }

    override void OnMissionStart()
    {
        super.OnMissionStart();
        DeutschZConvoyZ_Bootstrap("MissionServer OnMissionStart");
        DeutschZConvoyZ_ScheduleDelayedBootstrap();
    }

    override void OnMissionFinish()
    {
        if (GetGame() && GetGame().IsServer())
            DeutschZConvoyZ_GetManager().Cleanup("mission finish");
        super.OnMissionFinish();
    }
}
