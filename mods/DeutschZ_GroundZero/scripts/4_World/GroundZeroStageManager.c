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
            runtime.Position = m_Config.PossibleStagePositions.Get(Math.RandomInt(0, m_Config.PossibleStagePositions.Count()));
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
        m_State.CurrentStageId = id;

        m_Markers.UpdateStageMarker(runtime.Position, cfg.StageName, cfg.StageRadius);
        m_Zombies.SpawnWave(runtime.Position, cfg.ZombieThreatLevel, cfg.ZombieCount, cfg.StageRadius);
        m_AI.SpawnMilitaryPatrol(runtime.Position, cfg.MilitaryAICount);
        m_AI.SpawnRoguePatrol(runtime.Position, cfg.RogueAICount);
        m_Notifications.Broadcast(cfg.StageName + ": " + cfg.ObjectiveText);

        GroundZeroLogging.Info("Stage", "Entered stage=" + id.ToString() + " pos=" + runtime.Position.ToString());
    }

    void Tick()
    {
        GroundZeroStageRuntime runtime = GetStage(m_State.CurrentStageId);
        GroundZeroStageConfig cfg = m_Config.GetStageConfig(m_State.CurrentStageId);
        if (!runtime || !cfg) return;

        float now = GetGame().GetTime() * 0.001;

        if (runtime.State == GroundZeroStageState.GZ_STAGE_OBJECTIVE_ACTIVE)
        {
            bool timedFallbackAllowed = m_Config.AllowTimedObjectiveFallback && !cfg.RequireManualObjectiveCompletion;
            if (timedFallbackAllowed && now - runtime.ObjectiveStartedAt >= cfg.CompletionHoldSeconds)
                CompleteStage(runtime, cfg, null);
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

        GroundZeroLogging.Info("Stage", "Completed stage=" + runtime.StageId.ToString());

        int nextId = runtime.StageId + 1;
        if (nextId <= 5)
            EnterStage(nextId);
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
