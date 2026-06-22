/*
DeutschZ ModZ
Eigenstaendige Implementierung fuer DeutschZ.
Autor/Eigentuemer: Patrick Sluzalek / fck1701.
Projekt: DeutschZ.
Modul: DeutschZ_ConvoyZ.
Zweck der Datei: Eigene DeutschZ-Datei fuer ConvoyZ.
Quellen-/Konzeptnachweis: Eigene DeutschZ-Implementierung; DayZ/CF/Expansion werden nur als Laufzeit-Abhaengigkeit/API genutzt.
Keine direkte Codeuebernahme aus Drittquellen.
*/

static int g_DeutschZConvoyZ_Bootstrapped;

void DeutschZConvoyZ_Bootstrap(string source)
{
    if (!GetGame() || !GetGame().IsServer()) return;
    if (g_DeutschZConvoyZ_Bootstrapped == 1) return;

    g_DeutschZConvoyZ_Bootstrapped = 1;

    DeutschZConvoyZManager mgr = DeutschZConvoyZ_GetManager();
    if (mgr) mgr.Init();

    Print("[DeutschZ_ConvoyZ] Bootstrap from " + source + " finished");
}

modded class MissionServer
{
    void MissionServer()
    {
        DeutschZConvoyZ_Bootstrap("MissionServer constructor");
    }

    override void OnInit()
    {
        super.OnInit();
        DeutschZConvoyZ_Bootstrap("MissionServer OnInit");
    }

    override void OnMissionStart()
    {
        super.OnMissionStart();
        DeutschZConvoyZ_Bootstrap("MissionServer OnMissionStart");
    }

    override void OnMissionFinish()
    {
        if (GetGame() && GetGame().IsServer()) DeutschZConvoyZ_GetManager().Cleanup("mission finish");
        super.OnMissionFinish();
    }
}
