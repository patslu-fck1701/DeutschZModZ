/*
    DeutschZ_GroundZero
    Owner: Patrick Sluzalek / fck1701
    Module: 4_World / GroundZeroCheckpointManager
    Purpose: Retry checkpoints, retry limit and PvP-death restrictions.
    Dependencies: DayZ scripts; optional CF/Expansion APIs only through adapter methods.
    Compliance: Original DeutschZ implementation. No copied foreign mod code, assets, configs or stubs.
*/

class GroundZeroCheckpointManager
{
    protected GroundZeroConfig m_Config;
    protected GroundZeroPersistentState m_State;

    void GroundZeroCheckpointManager(GroundZeroConfig cfg, GroundZeroPersistentState state)
    {
        m_Config = cfg;
        m_State = state;
    }

    void SaveCheckpoint(PlayerBase player, vector position, int stageId)
    {
        string id = GetPlayerId(player);
        if (id == "") return;

        GroundZeroCheckpointRuntime checkpoint = GetOrCreate(id);
        checkpoint.Position = position;
        checkpoint.StageId = stageId;
        checkpoint.HasAbortedEvent = false;
        GroundZeroLogging.Info("Checkpoint", "Saved checkpoint player=" + id + " stage=" + stageId.ToString());
    }

    void FlagDeath(PlayerBase player, bool wasPvP)
    {
        string id = GetPlayerId(player);
        if (id == "") return;

        GroundZeroCheckpointRuntime checkpoint = GetOrCreate(id);
        checkpoint.LastDeathWasPvP = wasPvP;
        checkpoint.HasPendingDeathChoice = true;
        GroundZeroLogging.Info("Checkpoint", "Death flagged player=" + id + " pvp=" + wasPvP.ToString());
    }

    bool TryRetry(PlayerBase player)
    {
        if (!player) return false;

        GroundZeroCheckpointRuntime checkpoint = GetOrCreate(GetPlayerId(player));
        if (!checkpoint) return false;

        if (checkpoint.HasAbortedEvent)
        {
            GroundZeroLogging.Warn("Checkpoint", "Retry blocked: player aborted event");
            return false;
        }

        if (checkpoint.RetriesUsed >= m_Config.RetryLimitPerEvent)
        {
            GroundZeroLogging.Warn("Checkpoint", "Retry blocked: limit reached");
            return false;
        }

        if (checkpoint.LastDeathWasPvP && !m_Config.AllowRetryAfterPvPDeath)
        {
            GroundZeroLogging.Warn("Checkpoint", "Retry blocked: PvP death");
            return false;
        }

        checkpoint.RetriesUsed++;
        checkpoint.HasPendingDeathChoice = false;
        player.SetPosition(GetRetryPosition(checkpoint.Position));
        GiveRetryMinimalLoadout(player);
        GroundZeroLogging.Info("Checkpoint", "Retry used retries=" + checkpoint.RetriesUsed.ToString());
        return true;
    }

    void Abort(PlayerBase player)
    {
        string id = GetPlayerId(player);
        if (id == "") return;
        GroundZeroCheckpointRuntime checkpoint = GetOrCreate(id);
        checkpoint.HasPendingDeathChoice = false;
        checkpoint.HasAbortedEvent = true;
        GroundZeroLogging.Info("Checkpoint", "Player aborted retry flow player=" + id);
    }

    vector GetRetryPosition(vector checkpoint)
    {
        float dist = Math.RandomFloat(m_Config.RetrySpawnBackDistanceMin, m_Config.RetrySpawnBackDistanceMax);
        float side = Math.RandomFloat(-80, 80);
        return checkpoint + Vector(dist, 0, side);
    }

    void GiveRetryMinimalLoadout(PlayerBase player)
    {
        if (!player || !player.GetInventory()) return;
        foreach (string itemClass : m_Config.RetryMinimalLoadout)
        {
            if (itemClass != "" && !DeutschZCore_UnsafeClassGuard.IsBlockedClass(itemClass)) player.GetInventory().CreateInInventory(itemClass);
        }
    }

    GroundZeroCheckpointRuntime GetOrCreate(string id)
    {
        if (id == "") return null;

        foreach (GroundZeroCheckpointRuntime checkpoint : m_State.Checkpoints)
        {
            if (checkpoint && checkpoint.PlayerId == id) return checkpoint;
        }

        GroundZeroCheckpointRuntime created = new GroundZeroCheckpointRuntime();
        created.PlayerId = id;
        m_State.Checkpoints.Insert(created);
        return created;
    }

    string GetPlayerId(PlayerBase player)
    {
        if (!player || !player.GetIdentity()) return "";
        return player.GetIdentity().GetPlainId();
    }
}
