/*
    DeutschZ_GroundZero
    Owner: Patrick Sluzalek / fck1701
    Module: 4_World / GroundZeroCarrierManager
    Purpose: Carrier tracking, organic PvP marker pressure and AI search escalation.
    Dependencies: DayZ scripts; optional CF/Expansion APIs only through adapter methods.
    Compliance: Original DeutschZ implementation. No copied foreign mod code, assets, configs or stubs.
*/

class GroundZeroCarrierManager
{
    protected GroundZeroConfig m_Config;
    protected GroundZeroPersistentState m_State;
    protected GroundZeroMarkerManager m_Markers;
    protected GroundZeroNotificationManager m_Notifications;
    protected GroundZeroItemManager m_Items;
    protected GroundZeroAIBridge m_AI;

    void GroundZeroCarrierManager(GroundZeroConfig cfg, GroundZeroPersistentState state, GroundZeroMarkerManager markers, GroundZeroNotificationManager notifications, GroundZeroItemManager items, GroundZeroAIBridge ai)
    {
        m_Config = cfg;
        m_State = state;
        m_Markers = markers;
        m_Notifications = notifications;
        m_Items = items;
        m_AI = ai;
    }

    void SetAIBridge(GroundZeroAIBridge ai)
    {
        m_AI = ai;
    }

    void Tick()
    {
        array<Man> players = new array<Man>();
        GetGame().GetPlayers(players);

        foreach (Man man : players)
        {
            PlayerBase player = PlayerBase.Cast(man);
            if (player) RefreshPlayer(player);
        }
    }

    void RefreshPlayer(PlayerBase player)
    {
        string id = GetPlayerId(player);
        if (id == "") return;

        int count = m_Items.CountCampaignItems(player);
        GroundZeroCarrierRuntime runtime = GetOrCreate(id, GetPlayerName(player));
        bool changed = runtime.ItemCount != count;

        runtime.ItemCount = count;
        runtime.LastKnownPosition = player.GetPosition();

        float now = GetGame().GetTime() * 0.001;
        float radius = m_Config.GetCarrierRadius(count);
        if (radius >= 0 && now - runtime.LastMarkerUpdate >= m_Config.CarrierMarkerUpdateSeconds)
        {
            m_Markers.UpdateCarrierMarker(id, runtime.LastKnownPosition, radius);
            runtime.LastMarkerUpdate = now;
        }

        if (changed && count >= 2)
            m_Notifications.Broadcast(GroundZeroConstants.MSG_COMPONENTS_MERGED);

        if (changed && count >= 3)
            m_Notifications.Broadcast(GroundZeroConstants.MSG_CARRIER_LOCATED);

        if (m_AI && m_Config.EnableCarrierAISearchTeams && count >= m_Config.CarrierAISearchTeamsMinItems)
        {
            if (now - runtime.LastAISearchSpawnedAt >= m_Config.CarrierAISearchTeamCooldownSeconds)
            {
                m_AI.SpawnCarrierSearchTeam(runtime.LastKnownPosition, m_Config.CarrierAISearchTeamSize);
                runtime.LastAISearchSpawnedAt = now;
            }
        }
    }

    GroundZeroCarrierRuntime GetOrCreate(string id, string name)
    {
        foreach (GroundZeroCarrierRuntime carrier : m_State.Carriers)
        {
            if (carrier && carrier.PlayerId == id) return carrier;
        }

        GroundZeroCarrierRuntime runtime = new GroundZeroCarrierRuntime();
        runtime.PlayerId = id;
        runtime.PlayerName = name;
        m_State.Carriers.Insert(runtime);
        return runtime;
    }

    string GetPlayerId(PlayerBase player)
    {
        if (!player || !player.GetIdentity()) return "";
        return player.GetIdentity().GetPlainId();
    }

    string GetPlayerName(PlayerBase player)
    {
        if (!player || !player.GetIdentity()) return "unknown";
        return player.GetIdentity().GetName();
    }
}
