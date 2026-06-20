/*
    DeutschZ_GroundZero
    Owner: Patrick Sluzalek / fck1701
    Module: 4_World / GroundZeroEventManager
    Purpose: Authoritative lifecycle state machine, timeout handling and idempotent cleanup.
    Dependencies: DayZ scripts; optional CF/Expansion APIs only through adapter methods.
    Compliance: Original DeutschZ implementation. No copied foreign mod code, assets, configs or stubs.
*/

class GroundZeroEventManager
{
    protected GroundZeroConfig m_Config;
    protected GroundZeroPersistentState m_State;
    protected GroundZeroNotificationManager m_Notifications;
    protected bool m_CleanupRunning;

    ref GroundZeroStageManager Stages;
    ref GroundZeroCheckpointManager Checkpoints;
    ref GroundZeroCarrierManager Carriers;
    ref GroundZeroItemManager Items;
    ref GroundZeroMarkerManager Markers;
    ref GroundZeroZombieManager Zombies;
    ref GroundZeroAIBridge AI;
    ref GroundZeroBossManager Boss;
    ref GroundZeroExtractionManager Extraction;
    ref GroundZeroRewardManager Rewards;

    void GroundZeroEventManager(GroundZeroConfig cfg, GroundZeroPersistentState state, GroundZeroNotificationManager notifications)
    {
        m_Config = cfg;
        m_State = state;
        m_Notifications = notifications;
        m_CleanupRunning = false;

        Items = new GroundZeroItemManager(cfg, state);
        Markers = new GroundZeroMarkerManager(cfg, state);
        Checkpoints = new GroundZeroCheckpointManager(cfg, state);
        Carriers = new GroundZeroCarrierManager(cfg, state, Markers, notifications, Items, null);
        Zombies = new GroundZeroZombieManager(cfg);
        AI = new GroundZeroAIBridge(cfg);
        Carriers.SetAIBridge(AI);
        Boss = new GroundZeroBossManager(cfg, state, Zombies, AI, notifications);
        Extraction = new GroundZeroExtractionManager(cfg, state, notifications, Markers, Items);
        Rewards = new GroundZeroRewardManager(cfg, notifications);
        Stages = new GroundZeroStageManager(cfg, state, Items, Zombies, AI, notifications, Checkpoints, Markers);
    }

    void RestoreOrIdle()
    {
        if (!m_Config.EnableGroundZero)
        {
            GroundZeroLogging.Warn("Event", "GroundZero disabled by config");
            return;
        }

        if (m_State.EventState == GroundZeroEventState.GZ_COMPLETED || m_State.EventState == GroundZeroEventState.GZ_FAILED || m_State.EventState == GroundZeroEventState.GZ_CLEANUP)
        {
            Cleanup();
            return;
        }

        if (m_State.EventState == GroundZeroEventState.GZ_IDLE)
            ScheduleNextAutoStart();

        GroundZeroLogging.Info("Event", "Restored state=" + m_State.EventState.ToString() + " stage=" + m_State.CurrentStageId.ToString());
    }

    void ScheduleNextAutoStart()
    {
        if (!m_Config.AutoStartEnabled) return;
        if (!GetGame()) return;

        // Only schedule when no start time exists.
        // Do not push the start time forward when it is already due.
        if (m_State.NextAutoStartAt > 0)
            return;

        float now = GetGame().GetTime() * 0.001;
        m_State.NextAutoStartAt = now + Math.RandomInt(m_Config.AutoStartMinDelaySeconds, m_Config.AutoStartMaxDelaySeconds + 1);
        GroundZeroLogging.Info("Event", "Next autostart at gameTime=" + m_State.NextAutoStartAt.ToString());
        Save();
    }

    void StartEvent()
    {
        if (!GetGame() || !GetGame().IsServer()) return;
        if (!m_Config.EnableGroundZero) return;
        if (m_State.EventState != GroundZeroEventState.GZ_IDLE) return;

        float now = GetGame().GetTime() * 0.001;
        m_State.EventState = GroundZeroEventState.GZ_STARTING;
        m_State.EventStartedAt = now;
        m_State.EventEndsAt = now + Math.RandomInt(m_Config.EventMinDurationSeconds, m_Config.EventMaxDurationSeconds + 1);
        m_State.NextAutoStartAt = 0;
        m_State.CurrentStageId = 1;
        m_State.ExtractionStarted = false;
        m_State.ExtractionSuccess = false;
        m_State.ExtractionFailed = false;
        m_State.BossState = GroundZeroBossState.GZ_BOSS_NONE;
        m_State.FinalStartedAt = 0;
        m_State.ExtractionStartedAt = 0;
        m_State.FinalFacilityPosition = m_Config.PossibleFinalFacilityPositions.Get(Math.RandomInt(0, m_Config.PossibleFinalFacilityPositions.Count()));
        m_State.ExtractionPosition = m_Config.PossibleExtractionPositions.Get(Math.RandomInt(0, m_Config.PossibleExtractionPositions.Count()));

        Stages.BuildStages();
        Stages.EnterStage(1);
        m_State.EventState = GroundZeroEventState.GZ_STAGE_ACTIVE;
        m_Notifications.Broadcast("Ground Zero gestartet");
        Save();
    }

    void Tick()
    {
        if (!m_Config.EnableGroundZero) return;

        if (m_State.EventState == GroundZeroEventState.GZ_IDLE)
        {
            if (m_Config.AutoStartEnabled)
            {
                if (m_State.NextAutoStartAt <= 0)
                    ScheduleNextAutoStart();

                if (CanAutoStartNow())
                    StartEvent();
            }
            return;
        }

        if (IsTimedOut())
        {
            GroundZeroLogging.Warn("Event", "Event timed out");
            Fail();
            return;
        }

        if (m_State.EventState == GroundZeroEventState.GZ_STAGE_ACTIVE)
        {
            Stages.Tick();
            Carriers.Tick();
            Markers.TickDroppedItems();

            if (Stages.AllStagesComplete())
            {
                m_State.EventState = GroundZeroEventState.GZ_FINAL_READY;
                Markers.UpdateFinalMarker(m_State.FinalFacilityPosition);
                m_Notifications.Broadcast(GroundZeroConstants.MSG_FINAL_AVAILABLE);
                Save();
            }
        }
        else if (m_State.EventState == GroundZeroEventState.GZ_FINAL_READY)
        {
            Boss.StartFinalIfNeeded();
            m_State.EventState = GroundZeroEventState.GZ_FINAL_ACTIVE;
            Save();
        }
        else if (m_State.EventState == GroundZeroEventState.GZ_FINAL_ACTIVE)
        {
            Boss.Tick();
            Carriers.Tick();
            Markers.TickDroppedItems();

            if (Boss.IsDead())
            {
                Extraction.StartExtraction();
                m_State.EventState = GroundZeroEventState.GZ_EXTRACTION_ACTIVE;
                Save();
            }
        }
        else if (m_State.EventState == GroundZeroEventState.GZ_EXTRACTION_ACTIVE)
        {
            Extraction.Tick();
            Carriers.Tick();
            Markers.TickDroppedItems();

            if (Extraction.IsSuccess())
            {
                Rewards.GrantSuccess();
                Complete();
            }
            else if (Extraction.IsFailed())
            {
                Rewards.GrantFailure();
                Fail();
            }
        }
    }

    bool CanAutoStartNow()
    {
        if (!GetGame()) return false;
        if (m_State.NextAutoStartAt <= 0) return false;
        if ((GetGame().GetTime() * 0.001) < m_State.NextAutoStartAt) return false;
        array<Man> players = new array<Man>();
        GetGame().GetPlayers(players);
        return players.Count() >= m_Config.MinOnlinePlayersToAutoStart;
    }

    bool IsTimedOut()
    {
        if (!GetGame()) return false;
        if (m_State.EventEndsAt <= 0) return false;
        return (GetGame().GetTime() * 0.001) >= m_State.EventEndsAt;
    }

    void OnPlayerKilled(PlayerBase player, Object killer)
    {
        if (!player) return;

        int droppedCount = Items.DropCampaignItemsFromPlayer(player);
        Carriers.RefreshPlayer(player);
        Checkpoints.FlagDeath(player, IsPvPKill(player, killer));

        if (droppedCount > 0)
            m_Notifications.Broadcast(GroundZeroConstants.MSG_COMPONENT_LOST);

        Save();
    }

    bool IsPvPKill(PlayerBase victim, Object killer)
    {
        if (!victim || !killer) return false;
        PlayerBase killerPlayer = PlayerBase.Cast(killer);
        if (killerPlayer && killerPlayer != victim) return true;
        return false;
    }

    void RequestRetry(PlayerBase player)
    {
        if (!GetGame() || !GetGame().IsServer()) return;
        if (Checkpoints.TryRetry(player)) Save();
    }

    void RequestAbort(PlayerBase player)
    {
        if (!GetGame() || !GetGame().IsServer()) return;
        Checkpoints.Abort(player);
        Save();
    }

    void Complete()
    {
        m_State.EventState = GroundZeroEventState.GZ_COMPLETED;
        GroundZeroLogging.Info("Event", "Event completed");
        Cleanup();
    }

    void Fail()
    {
        m_State.EventState = GroundZeroEventState.GZ_FAILED;
        GroundZeroLogging.Warn("Event", "Event failed");
        Cleanup();
    }

    void Cleanup()
    {
        if (m_CleanupRunning) return;
        m_CleanupRunning = true;

        GroundZeroLogging.Info("Event", "Cleanup started");
        if (AI) AI.Cleanup();
        if (Zombies) Zombies.Cleanup();
        if (Markers) Markers.Cleanup();
        if (Boss) Boss.Cleanup();
        if (Extraction) Extraction.Cleanup();

        m_State.EventState = GroundZeroEventState.GZ_IDLE;
        m_State.CurrentStageId = 0;
        GroundZeroPersistence.ResetState();
        m_CleanupRunning = false;
    }

    void Save()
    {
        GroundZeroPersistence.SaveState(m_State);
    }
}
