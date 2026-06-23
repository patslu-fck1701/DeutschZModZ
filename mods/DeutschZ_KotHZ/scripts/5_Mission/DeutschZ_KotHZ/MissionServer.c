/*
DeutschZ ModZ
Eigenstaendige Implementierung fuer DeutschZ.
Autor/Eigentuemer: Patrick Sluzalek / fck1701.
Keine direkte Codeuebernahme aus Drittquellen.
Oeffentliche Quellen werden nur zur Konzept- und API-Verifikation genutzt.
*/

modded class MissionServer
{
    protected ref DeutschZKotHZManager m_DeutschZKotHZManager;
    protected int m_DeutschZKotHZ_ConfigBootstrapped;

    void MissionServer()
    {
        DeutschZKotHZ_RequestConfigBootstrap("MissionServer constructor");
        DeutschZKotHZ_ScheduleDelayedConfigBootstrap();
    }

    protected void DeutschZKotHZ_RequestConfigBootstrap(string source)
    {
        if (!GetGame() || !GetGame().IsServer())
            return;

        if (m_DeutschZKotHZ_ConfigBootstrapped == 1)
            return;

        m_DeutschZKotHZ_ConfigBootstrapped = 1;
        Print("[DeutschZ_KotHZ] Config bootstrap requested source=" + source);
        DZKotHZ_ProfileFolders.Ensure();
        DeutschZKotHZConfigManager.Load();
        Print("[DeutschZ_KotHZ] Config bootstrap finished source=" + source);
    }

    protected void DeutschZKotHZ_DelayedConfigBootstrap()
    {
        DeutschZKotHZ_RequestConfigBootstrap("MissionServer delayed fallback");
    }

    protected void DeutschZKotHZ_ScheduleDelayedConfigBootstrap()
    {
        if (!GetGame())
            return;

        GetGame().GetCallQueue(CALL_CATEGORY_SYSTEM).CallLater(this.DeutschZKotHZ_DelayedConfigBootstrap, 1000, false);
        GetGame().GetCallQueue(CALL_CATEGORY_SYSTEM).CallLater(this.DeutschZKotHZ_DelayedConfigBootstrap, 5000, false);
    }

    override void OnMissionStart()
    {
        super.OnMissionStart();

        if (GetGame().IsServer())
        {
            DeutschZKotHZ_RequestConfigBootstrap("MissionServer OnMissionStart");
            DeutschZKotHZ_ScheduleDelayedConfigBootstrap();
        }
    }

    override void OnInit()
    {
        super.OnInit();

        if (GetGame().IsServer())
        {
            DeutschZKotHZ_RequestConfigBootstrap("MissionServer OnInit");
            DeutschZKotHZ_ScheduleDelayedConfigBootstrap();
            Print("[DeutschZ_KotHZ] OnInit config bootstrap done.");
            if (!m_DeutschZKotHZManager)
            {
                m_DeutschZKotHZManager = new DeutschZKotHZManager();
                m_DeutschZKotHZManager.StartScheduler();
                GetGame().GetCallQueue(CALL_CATEGORY_SYSTEM).CallLater(this.DeutschZKotHZ_ProcessAdminCommandBus, 500, true);
                GetGame().GetCallQueue(CALL_CATEGORY_SYSTEM).CallLater(this.DeutschZKotHZ_ProcessInfectedKillBus, 250, true);
            }
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
