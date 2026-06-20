/*
    DeutschZ_GroundZero
    Owner: Patrick Sluzalek / fck1701
    Module: 4_World / GroundZeroCore
    Purpose: Server entry point and module wiring. No large logic in 5_Mission.
    Dependencies: DayZ scripts; optional CF/Expansion APIs only through adapter methods.
    Compliance: Original DeutschZ implementation. No copied foreign mod code, assets, configs or stubs.
*/

class GroundZeroCore
{
    protected static ref GroundZeroCore s_Instance;
    protected bool m_Initialized;

    ref GroundZeroConfig Config;
    ref GroundZeroPersistentState State;
    ref GroundZeroNotificationManager Notifications;
    ref GroundZeroEventManager m_EventManager;

    static GroundZeroCore Get()
    {
        if (!s_Instance) s_Instance = new GroundZeroCore();
        return s_Instance;
    }

    void InitServer()
    {
        if (!GetGame() || !GetGame().IsServer()) return;
        if (m_Initialized) return;

        GroundZeroPersistence.EnsureProfileDirs();
        Config = GroundZeroConfig.Load();
        GroundZeroLogging.SetDebug(Config.EnableDebugLogs);
        State = GroundZeroPersistence.LoadState();
        Notifications = new GroundZeroNotificationManager(Config);
        m_EventManager = new GroundZeroEventManager(Config, State, Notifications);
        m_EventManager.RestoreOrIdle();
        m_Initialized = true;

        GroundZeroLogging.Info("Core", "Server initialized version=" + GroundZeroConstants.VERSION);
    }

    void Tick()
    {
        if (!m_Initialized) InitServer();
        if (m_EventManager) m_EventManager.Tick();
    }

    void StartEventAdmin()
    {
        if (m_EventManager) m_EventManager.StartEvent();
    }

    void OnPlayerKilled(PlayerBase player, Object killer)
    {
        if (m_EventManager && player) m_EventManager.OnPlayerKilled(player, killer);
    }

    void RequestRetry(PlayerBase player)
    {
        if (m_EventManager && player) m_EventManager.RequestRetry(player);
    }

    void RequestAbort(PlayerBase player)
    {
        if (m_EventManager && player) m_EventManager.RequestAbort(player);
    }

    void RequestRetryByIdentity(PlayerIdentity identity)
    {
        PlayerBase player = FindPlayerByIdentity(identity);
        if (player) RequestRetry(player);
        else GroundZeroLogging.Warn(GroundZeroConstants.LOG_CAT_SECURITY, "Retry request without live player");
    }

    void RequestAbortByIdentity(PlayerIdentity identity)
    {
        PlayerBase player = FindPlayerByIdentity(identity);
        if (player) RequestAbort(player);
        else GroundZeroLogging.Warn(GroundZeroConstants.LOG_CAT_SECURITY, "Abort request without live player");
    }

    PlayerBase FindPlayerByIdentity(PlayerIdentity identity)
    {
        if (!identity) return null;
        string wanted = identity.GetPlainId();
        array<Man> players = new array<Man>();
        GetGame().GetPlayers(players);
        foreach (Man man : players)
        {
            PlayerBase player = PlayerBase.Cast(man);
            if (player && player.GetIdentity() && player.GetIdentity().GetPlainId() == wanted)
                return player;
        }
        return null;
    }
}
