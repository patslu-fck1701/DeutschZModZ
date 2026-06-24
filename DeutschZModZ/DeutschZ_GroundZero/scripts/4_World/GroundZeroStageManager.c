/*
    DeutschZ_GroundZero
    Owner: Patrick Sluzalek / fck1701
    Module: 4_World / GroundZeroStageManager
    Purpose: Five-stage campaign state machine with server-authoritative stage transitions.
    Dependencies: DayZ scripts; optional CF/Expansion APIs only through adapter methods.
    Compliance: Original DeutschZ implementation. No copied foreign mod code, assets, configs or stubs.
*/

class GroundZeroStageManager
{
    protected GroundZeroConfig m_Config;
    protected GroundZeroPersistentState m_State;
    protected GroundZeroItemManager m_Items;
    protected GroundZeroZombieManager m_Zombies;
    protected GroundZeroAIBridge m_AI;
    protected GroundZeroNotificationManager m_Notifications;
    protected GroundZeroCheckpointManager m_Checkpoints;
    protected GroundZeroMarkerManager m_Markers;
    protected float m_LastProgressBroadcast;
    protected float m_LastHUDBroadcast;

    void GroundZeroStageManager(GroundZeroConfig cfg, GroundZeroPersistentState state, GroundZeroItemManager items, GroundZeroZombieManager zombies, GroundZeroAIBridge ai, GroundZeroNotificationManager notifications, GroundZeroCheckpointManager checkpoints, GroundZeroMarkerManager markers)
    {
        m_Config = cfg;
        m_State = state;
        m_Items = items;
        m_Zombies = zombies;
        m_AI = ai;
        m_Notifications = notifications;
        m_Checkpoints = checkpoints;
        m_Markers = markers;
    }

    void BuildStages()
    {
        m_State.Stages.Clear();
        for (int i = 0; i < m_Config.Stages.Count(); i++)
        {
            GroundZeroStageConfig cfg = m_Config.Stages.Get(i);
            GroundZeroStageRuntime runtime = new GroundZeroStageRuntime();
            runtime.StageId = cfg.StageId;
            int posIndex = i % m_Config.PossibleStagePositions.Count();
            runtime.Position = m_Config.PossibleStagePositions.Get(posIndex);
            runtime.ObjectiveKillCount = 0;
            runtime.ObjectiveKillRequired = m_Config.GetStageRequiredKills();
            m_State.Stages.Insert(runtime);
        }
    }

    void EnterStage(int id)
    {
        GroundZeroStageRuntime runtime = GetStage(id);
        GroundZeroStageConfig cfg = m_Config.GetStageConfig(id);
        if (!runtime || !cfg) return;

        runtime.State = GroundZeroStageState.GZ_STAGE_OBJECTIVE_ACTIVE;
        runtime.StartedAt = GetGame().GetTime() * 0.001;
        runtime.ObjectiveStartedAt = runtime.StartedAt;
        runtime.ObjectiveKillCount = 0;
        runtime.ObjectiveKillRequired = m_Config.GetStageRequiredKills();
        m_State.CurrentStageId = id;

        m_Markers.UpdateStageMarker(runtime.Position, cfg.StageName, cfg.StageRadius);
        m_Notifications.Broadcast(cfg.StageName + ": " + cfg.ObjectiveText);
        m_LastProgressBroadcast = 0;
        m_LastHUDBroadcast = 0;
        SendStageHUD(runtime, cfg, "Signalstation aktiv - Gegner sichern und Fortschritt halten");

        int delayMs = m_Config.WaveDelaySeconds * 1000;
        if (delayMs < 1000) delayMs = 1000;
        GetGame().GetCallQueue(CALL_CATEGORY_SYSTEM).CallLater(SpawnStageThreats, delayMs, false, runtime.Position, cfg.ZombieThreatLevel, cfg.ZombieCount, cfg.StageRadius, cfg.MilitaryAICount, cfg.RogueAICount);

        GroundZeroLogging.Info("Stage", "Entered stage=" + id.ToString() + " pos=" + runtime.Position.ToString());
    }

    protected void SpawnStageThreats(vector position, int zombieThreat, int zombieCount, float radius, int militaryCount, int rogueCount)
    {
        GroundZeroStageRuntime runtime = GetStage(m_State.CurrentStageId);
        if (!runtime || runtime.State != GroundZeroStageState.GZ_STAGE_OBJECTIVE_ACTIVE) return;

        if (m_Zombies) m_Zombies.SpawnWave(position, zombieThreat, zombieCount, radius);
        if (m_AI) m_AI.SpawnMilitaryPatrol(position, militaryCount);
        if (m_AI) m_AI.SpawnRoguePatrol(position, rogueCount);
        GroundZeroLogging.Info("Stage", "Delayed threats spawned stage=" + runtime.StageId.ToString());
    }

    void Tick()
    {
        GroundZeroStageRuntime runtime = GetStage(m_State.CurrentStageId);
        GroundZeroStageConfig cfg = m_Config.GetStageConfig(m_State.CurrentStageId);
        if (!runtime || !cfg) return;

        float now = GetGame().GetTime() * 0.001;

        if (runtime.State == GroundZeroStageState.GZ_STAGE_OBJECTIVE_ACTIVE)
        {
            if (now - m_LastProgressBroadcast >= 10)
            {
                m_LastProgressBroadcast = now;
                int percent = 0;
                if (runtime.ObjectiveKillRequired > 0)
                    percent = (runtime.ObjectiveKillCount * 100) / runtime.ObjectiveKillRequired;
                if (percent > 100) percent = 100;
                m_Notifications.Broadcast(cfg.StageName + " Fortschritt: " + percent.ToString() + "% (" + runtime.ObjectiveKillCount.ToString() + "/" + runtime.ObjectiveKillRequired.ToString() + ")");
            }

            if (now - m_LastHUDBroadcast >= 1.0)
            {
                m_LastHUDBroadcast = now;
                SendStageHUD(runtime, cfg, cfg.StageName + " aktiv - Fortschritt laeuft");
            }

            bool timedFallbackAllowed = m_Config.AllowTimedObjectiveFallback && !cfg.RequireManualObjectiveCompletion;
            if (timedFallbackAllowed && cfg.CompletionHoldSeconds > 0 && now - runtime.ObjectiveStartedAt >= cfg.CompletionHoldSeconds)
            {
                // FIX23: Timed completion is only a fallback after real combat progress.
                // This prevents GroundZero from rushing through all stages while the player is only nearby.
                float nearRadius = cfg.StageRadius;
                if (nearRadius > 45.0)
                    nearRadius = 45.0;

                if (HasPlayerNear(runtime.Position, nearRadius) && runtime.ObjectiveKillCount >= runtime.ObjectiveKillRequired)
                    CompleteStage(runtime, cfg, null);
            }
        }
    }


    protected bool HasPlayerNear(vector position, float radius)
    {
        array<Man> players = new array<Man>();
        GetGame().GetPlayers(players);
        foreach (Man man : players)
        {
            PlayerBase player = PlayerBase.Cast(man);
            if (player && player.IsAlive() && vector.Distance(player.GetPosition(), position) <= radius)
                return true;
        }
        return false;
    }

    void OnEnemyKilled(Object victim, Object killer)
    {
        if (!GetGame() || !GetGame().IsServer()) return;
        GroundZeroStageRuntime runtime = GetStage(m_State.CurrentStageId);
        GroundZeroStageConfig cfg = m_Config.GetStageConfig(m_State.CurrentStageId);
        if (!runtime || !cfg) return;
        if (runtime.State != GroundZeroStageState.GZ_STAGE_OBJECTIVE_ACTIVE) return;
        if (!victim) return;

        float dist = vector.Distance(victim.GetPosition(), runtime.Position);
        if (dist > cfg.StageRadius + 80.0) return;

        runtime.ObjectiveKillCount++;
        m_Notifications.Broadcast(cfg.StageName + ": Gegner eliminiert " + runtime.ObjectiveKillCount.ToString() + "/" + runtime.ObjectiveKillRequired.ToString());
        GroundZeroLogging.Info("Stage", "Enemy kill progress stage=" + runtime.StageId.ToString() + " kills=" + runtime.ObjectiveKillCount.ToString() + "/" + runtime.ObjectiveKillRequired.ToString());

        if (runtime.ObjectiveKillCount >= runtime.ObjectiveKillRequired)
        {
            PlayerBase playerKiller = PlayerBase.Cast(killer);
            CompleteStage(runtime, cfg, playerKiller);
        }
        else
        {
            SendStageHUD(runtime, cfg, cfg.StageName + ": Gegner eliminiert");
        }
    }

    protected int CountPlayersNear(vector position, float radius)
    {
        int count = 0;
        array<Man> players = new array<Man>();
        GetGame().GetPlayers(players);
        foreach (Man man : players)
        {
            PlayerBase player = PlayerBase.Cast(man);
            if (player && player.IsAlive() && vector.Distance(player.GetPosition(), position) <= radius)
                count++;
        }
        return count;
    }

    protected void SendStageHUD(GroundZeroStageRuntime runtime, GroundZeroStageConfig cfg, string stateText)
    {
        if (!runtime || !cfg)
            return;

        int percent = 0;
        if (runtime.ObjectiveKillRequired > 0)
            percent = (runtime.ObjectiveKillCount * 100) / runtime.ObjectiveKillRequired;
        percent = Math.Clamp(percent, 0, 100);

        float hudRadius = GetStageHUDRadius(cfg);
        int playersNear = CountPlayersNear(runtime.Position, hudRadius);
        array<Man> players = new array<Man>();
        GetGame().GetPlayers(players);
        foreach (Man man : players)
        {
            PlayerBase player = PlayerBase.Cast(man);
            if (!player || !player.GetIdentity())
                continue;

            bool visible = vector.Distance(player.GetPosition(), runtime.Position) <= hudRadius;
            string title = "";
            string text = "";
            int current = 0;
            int required = 0;
            int shownPercent = 0;
            int shownPlayers = 0;

            if (visible)
            {
                title = cfg.StageName;
                text = stateText;
                current = runtime.ObjectiveKillCount;
                required = runtime.ObjectiveKillRequired;
                shownPercent = percent;
                shownPlayers = playersNear;
            }

            Param8<string, bool, string, int, int, int, int, string> data = new Param8<string, bool, string, int, int, int, int, string>(GroundZeroRPC.TOKEN, visible, title, shownPercent, current, required, shownPlayers, text);
            GetGame().RPCSingleParam(player, GroundZeroConstants.RPC_SYNC_HUD, data, true, player.GetIdentity());
        }
    }

    protected float GetStageHUDRadius(GroundZeroStageConfig cfg)
    {
        if (!cfg)
            return 150.0;

        float radius = cfg.StageRadius + 50.0;
        if (radius < 75.0)
            radius = 75.0;
        if (radius > 250.0)
            radius = 250.0;
        return radius;
    }

    protected void HideStageHUDToAll()
    {
        array<Man> players = new array<Man>();
        GetGame().GetPlayers(players);
        foreach (Man man : players)
        {
            PlayerBase player = PlayerBase.Cast(man);
            if (!player || !player.GetIdentity())
                continue;

            Param8<string, bool, string, int, int, int, int, string> data = new Param8<string, bool, string, int, int, int, int, string>(GroundZeroRPC.TOKEN, false, "", 0, 0, 0, 0, "");
            GetGame().RPCSingleParam(player, GroundZeroConstants.RPC_SYNC_HUD, data, true, player.GetIdentity());
        }
    }

    bool CompleteCurrentStageByPlayer(PlayerBase player)
    {
        if (!GetGame() || !GetGame().IsServer()) return false;
        GroundZeroStageRuntime runtime = GetStage(m_State.CurrentStageId);
        GroundZeroStageConfig cfg = m_Config.GetStageConfig(m_State.CurrentStageId);
        if (!runtime || !cfg || !player) return false;
        if (vector.Distance(player.GetPosition(), runtime.Position) > cfg.StageRadius) return false;
        CompleteStage(runtime, cfg, player);
        return true;
    }

    void CompleteStage(GroundZeroStageRuntime runtime, GroundZeroStageConfig cfg, PlayerBase completedBy)
    {
        if (!runtime || !cfg) return;
        if (runtime.State == GroundZeroStageState.GZ_STAGE_COMPLETED) return;

        runtime.State = GroundZeroStageState.GZ_STAGE_COMPLETED;
        runtime.CompletedAt = GetGame().GetTime() * 0.001;
        if (completedBy && completedBy.GetIdentity()) runtime.CompletedByPlayerId = completedBy.GetIdentity().GetPlainId();

        vector rewardPos = runtime.Position + Vector(1, 0, 1);
        m_Items.SpawnCampaignItem(cfg.RewardItemClass, rewardPos);
        runtime.RewardSpawned = true;
        m_Notifications.Broadcast(GroundZeroConstants.MSG_COMPONENT_DISCOVERED);

        array<Man> players = new array<Man>();
        GetGame().GetPlayers(players);
        foreach (Man man : players)
        {
            PlayerBase player = PlayerBase.Cast(man);
            if (player && vector.Distance(player.GetPosition(), runtime.Position) <= cfg.StageRadius + 50)
                m_Checkpoints.SaveCheckpoint(player, runtime.Position, runtime.StageId);
        }

        SendStageHUD(runtime, cfg, cfg.StageName + " abgeschlossen");
        GroundZeroLogging.Info("Stage", "Completed stage=" + runtime.StageId.ToString());

        if (m_Zombies) m_Zombies.Cleanup();
        if (m_AI) m_AI.Cleanup();

        int nextId = runtime.StageId + 1;
        if (nextId <= 5)
            EnterStage(nextId);
        else
            HideStageHUDToAll();
    }

    bool AllStagesComplete()
    {
        if (m_State.Stages.Count() < 5) return false;
        foreach (GroundZeroStageRuntime runtime : m_State.Stages)
        {
            if (!runtime || runtime.State != GroundZeroStageState.GZ_STAGE_COMPLETED) return false;
        }
        return true;
    }

    GroundZeroStageRuntime GetStage(int id)
    {
        foreach (GroundZeroStageRuntime runtime : m_State.Stages)
        {
            if (runtime && runtime.StageId == id) return runtime;
        }
        return null;
    }
}
