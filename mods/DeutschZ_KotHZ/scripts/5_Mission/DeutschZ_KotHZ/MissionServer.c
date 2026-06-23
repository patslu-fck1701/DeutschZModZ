/*
DeutschZ ModZ
Eigenstaendige Implementierung fuer DeutschZ.
Autor/Eigentuemer: Patrick Sluzalek / fck1701.
Keine direkte Codeuebernahme aus Drittquellen.
Oeffentliche Quellen werden nur zur Konzept- und API-Verifikation genutzt.
*/

<<<<<<< Updated upstream
=======
static int g_DeutschZKotHZ_ConfigBootstrapped;

void DeutschZKotHZ_RequestConfigBootstrap(string source)
{
    if (!GetGame() || !GetGame().IsServer())
        return;

    if (g_DeutschZKotHZ_ConfigBootstrapped == 1)
        return;

    g_DeutschZKotHZ_ConfigBootstrapped = 1;

    Print("[DeutschZ_KotHZ] Config bootstrap requested source=" + source);
    DZKotHZ_ProfileFolders.Ensure();
    DeutschZKotHZConfigManager.Load();
    Print("[DeutschZ_KotHZ] Config bootstrap finished source=" + source);
}

void DeutschZKotHZ_DelayedConfigBootstrap()
{
    DeutschZKotHZ_RequestConfigBootstrap("MissionServer delayed fallback");
}

void DeutschZKotHZ_ScheduleDelayedConfigBootstrap()
{
    if (!GetGame())
        return;

    GetGame().GetCallQueue(CALL_CATEGORY_SYSTEM).CallLater(DeutschZKotHZ_DelayedConfigBootstrap, 1000, false);
    GetGame().GetCallQueue(CALL_CATEGORY_SYSTEM).CallLater(DeutschZKotHZ_DelayedConfigBootstrap, 5000, false);
}

>>>>>>> Stashed changes
modded class MissionServer
{
    protected ref DeutschZKotHZManager m_DeutschZKotHZManager;

    void MissionServer()
    {
<<<<<<< Updated upstream
        Print("[DeutschZ_KotHZ] MissionServer constructor - forcing profile config init.");
        DZKotHZ_ProfileFolders.Ensure();
        DeutschZKotHZConfigManager.Load();
=======
        DeutschZKotHZ_RequestConfigBootstrap("MissionServer constructor");
        DeutschZKotHZ_ScheduleDelayedConfigBootstrap();
>>>>>>> Stashed changes
    }

    override void OnMissionStart()
    {
        super.OnMissionStart();

        if (GetGame().IsServer())
        {
<<<<<<< Updated upstream
            Print("[DeutschZ_KotHZ] OnMissionStart - forcing profile config init.");
            DZKotHZ_ProfileFolders.Ensure();
            DeutschZKotHZConfigManager.Load();
=======
            DeutschZKotHZ_RequestConfigBootstrap("MissionServer OnMissionStart");
            DeutschZKotHZ_ScheduleDelayedConfigBootstrap();
>>>>>>> Stashed changes
        }
    }

    override void OnInit()
    {
        super.OnInit();

        if (GetGame().IsServer())
        {
<<<<<<< Updated upstream
            DZKotHZ_ProfileFolders.Ensure();
            DeutschZKotHZConfigManager.Load();
            Print("[DeutschZ_KotHZ] OnInit config bootstrap done.");
            m_DeutschZKotHZManager = new DeutschZKotHZManager();
            m_DeutschZKotHZManager.StartScheduler();
            GetGame().GetCallQueue(CALL_CATEGORY_SYSTEM).CallLater(DeutschZKotHZ_ProcessAdminCommandBus, 500, true);
            GetGame().GetCallQueue(CALL_CATEGORY_SYSTEM).CallLater(DeutschZKotHZ_ProcessInfectedKillBus, 250, true);
=======
            DeutschZKotHZ_RequestConfigBootstrap("MissionServer OnInit");
            DeutschZKotHZ_ScheduleDelayedConfigBootstrap();

            if (!m_DeutschZKotHZManager)
            {
                m_DeutschZKotHZManager = new DeutschZKotHZManager();
                m_DeutschZKotHZManager.StartScheduler();
                GetGame().GetCallQueue(CALL_CATEGORY_SYSTEM).CallLater(DeutschZKotHZ_ProcessAdminCommandBus, 500, true);
                GetGame().GetCallQueue(CALL_CATEGORY_SYSTEM).CallLater(DeutschZKotHZ_ProcessInfectedKillBus, 250, true);
            }

            Print("[DeutschZ_KotHZ] OnInit manager bootstrap done.");
>>>>>>> Stashed changes
        }
    }

    DeutschZKotHZManager DeutschZKotHZ_GetManager()
    {
        return m_DeutschZKotHZManager;
    }

    protected void DeutschZKotHZ_ProcessInfectedKillBus()
    {
        if (!m_DeutschZKotHZManager)
            return;

        Object infected;
        int processed = 0;
        while (processed < 100 && DeutschZKotHZInfectedKillBus.Pop(infected))
        {
            if (infected)
                m_DeutschZKotHZManager.DZKZ_OnInfectedKilled(infected);
            processed++;
        }
    }

    protected void DeutschZKotHZ_ProcessAdminCommandBus()
    {
        if (!m_DeutschZKotHZManager)
            return;

        string command;
        string adminSteam64;
        string adminName;
        while (DeutschZKotHZAdminCommandBus.Pop(command, adminSteam64, adminName))
        {
            string message;
            bool success = false;

            PlayerIdentity adminIdentity = null;
            ref array<Man> players = new array<Man>;
            GetGame().GetPlayers(players);
            foreach (Man man : players)
            {
                PlayerBase player = PlayerBase.Cast(man);
                if (player && player.GetIdentity() && player.GetIdentity().GetPlainId() == adminSteam64)
                {
                    adminIdentity = player.GetIdentity();
                    break;
                }
            }

            if (command == "status")
            {
                message = m_DeutschZKotHZManager.GetAdminStatusMessage();
                success = true;
            }
            else if (command == "start")
            {
                success = m_DeutschZKotHZManager.AdminForceStartEvent(adminIdentity, message);
            }
            else if (command == "stop")
            {
                success = m_DeutschZKotHZManager.AdminForceStopEvent(adminIdentity, message);
            }
            else if (command == "reload" || command == "reload_settings" || command == "reload_zones" || command == "reload_loot" || command == "reload_all")
            {
                success = m_DeutschZKotHZManager.ReloadJsonConfigs(adminIdentity, message);
            }
            else
            {
                message = "Unknown KOTH admin command: " + command;
                success = false;
            }

            if (success)
                DeutschZKotHZAdminCommandBus.SetLastResult("KOTH OK: " + message);
            else
                DeutschZKotHZAdminCommandBus.SetLastResult("KOTH failed: " + message);
        }
    }
}
