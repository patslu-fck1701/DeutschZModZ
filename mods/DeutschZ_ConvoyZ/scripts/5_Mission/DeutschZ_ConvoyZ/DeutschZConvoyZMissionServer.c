/*
DeutschZ ModZ
Eigenstaendige Implementierung fuer DeutschZ.
Autor/Eigentuemer: Patrick Sluzalek / fck1701.
Projekt: DeutschZ.
Modul: DeutschZ_ConvoyZ.
Zweck der Datei: Robuster serverseitiger Bootstrap fuer Config/State-Erzeugung.
Keine direkte Codeuebernahme aus Drittquellen.
*/

static int g_DeutschZConvoyZ_Bootstrapped;

void DeutschZConvoyZ_Bootstrap(string source)
{
<<<<<<< Updated upstream
    if (!GetGame() || !GetGame().IsServer()) return;
    if (g_DeutschZConvoyZ_Bootstrapped == 1) return;

    g_DeutschZConvoyZ_Bootstrapped = 1;

    DeutschZConvoyZManager mgr = DeutschZConvoyZ_GetManager();
    if (mgr) mgr.Init();

    Print("[DeutschZ_ConvoyZ] Bootstrap from " + source + " finished");
=======
    if (!GetGame() || !GetGame().IsServer())
        return;

    if (g_DeutschZConvoyZ_Bootstrapped == 1)
        return;

    g_DeutschZConvoyZ_Bootstrapped = 1;

    Print("[DeutschZ_ConvoyZ] Bootstrap requested source=" + source);

    DeutschZConvoyZManager mgr = DeutschZConvoyZ_GetManager();
    if (mgr)
        mgr.Init();

    Print("[DeutschZ_ConvoyZ] Bootstrap from " + source + " finished");
}

void DeutschZConvoyZ_DelayedBootstrap()
{
    DeutschZConvoyZ_Bootstrap("MissionServer delayed fallback");
}

void DeutschZConvoyZ_ScheduleDelayedBootstrap()
{
    if (!GetGame())
        return;

    GetGame().GetCallQueue(CALL_CATEGORY_SYSTEM).CallLater(DeutschZConvoyZ_DelayedBootstrap, 1000, false);
    GetGame().GetCallQueue(CALL_CATEGORY_SYSTEM).CallLater(DeutschZConvoyZ_DelayedBootstrap, 5000, false);
>>>>>>> Stashed changes
}

modded class MissionServer
{
    void MissionServer()
    {
        DeutschZConvoyZ_Bootstrap("MissionServer constructor");
        DeutschZConvoyZ_ScheduleDelayedBootstrap();
    }

    override void OnInit()
    {
        super.OnInit();
        DeutschZConvoyZ_Bootstrap("MissionServer OnInit");
<<<<<<< Updated upstream
=======
        DeutschZConvoyZ_ScheduleDelayedBootstrap();
>>>>>>> Stashed changes
    }

    override void OnMissionStart()
    {
        super.OnMissionStart();
        DeutschZConvoyZ_Bootstrap("MissionServer OnMissionStart");
<<<<<<< Updated upstream
=======
        DeutschZConvoyZ_ScheduleDelayedBootstrap();
>>>>>>> Stashed changes
    }

    override void OnMissionFinish()
    {
        if (GetGame() && GetGame().IsServer())
            DeutschZConvoyZ_GetManager().Cleanup("mission finish");

        super.OnMissionFinish();
    }
}
