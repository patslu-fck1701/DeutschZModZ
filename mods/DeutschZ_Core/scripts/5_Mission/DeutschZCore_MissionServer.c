/*
    DeutschZ ModZ
    Autor/Eigentuemer: Patrick Sluzalek / fck1701
    Projekt: DeutschZ
    Zweck: Serverseitiger Core-Bootstrap fuer Profile/Configs.
    No-Copy-Bestaetigung: Kein Code, keine Assets und keine Configs aus fremden Mods kopiert.
*/

static int g_DeutschZCore_Bootstrapped;

void DeutschZCore_RequestBootstrap(string source)
{
    if (!GetGame() || !GetGame().IsServer())
        return;

    if (g_DeutschZCore_Bootstrapped == 1)
        return;

    g_DeutschZCore_Bootstrapped = 1;

    Print("[DeutschZ_Core] Init start source=" + source);
    DeutschZCore_ServerProfile.EnsureRoot();
    DeutschZCore_Log.Info("Core", "MissionServer initialized source=" + source);
    Print("[DeutschZ_Core] Init done");
}

modded class MissionServer
{
    void MissionServer()
    {
        DeutschZCore_RequestBootstrap("MissionServer constructor");
    }

    override void OnInit()
    {
        super.OnInit();
        DeutschZCore_RequestBootstrap("MissionServer OnInit");
    }

    override void OnMissionStart()
    {
        super.OnMissionStart();
        DeutschZCore_RequestBootstrap("MissionServer OnMissionStart");
    }
}
