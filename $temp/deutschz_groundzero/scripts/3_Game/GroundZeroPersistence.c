/*
    DeutschZ_GroundZero
    Owner: Patrick Sluzalek / fck1701
    Module: 3_Game / GroundZeroPersistence
    Purpose: Restart-safe state loading, repair, backup and reset helpers.
    Dependencies: DayZ scripts; optional CF/Expansion APIs only through adapter methods.
    Compliance: Original DeutschZ implementation. No copied foreign mod code, assets, configs or stubs.
*/

class GroundZeroPersistence
{
    static void EnsureProfileDirs()
    {
        if (!FileExist(GroundZeroConstants.PROFILE_ROOT)) MakeDirectory(GroundZeroConstants.PROFILE_ROOT);
        if (!FileExist(GroundZeroConstants.PROFILE_DIR)) MakeDirectory(GroundZeroConstants.PROFILE_DIR);
        if (!FileExist(GroundZeroConstants.LOG_DIR)) MakeDirectory(GroundZeroConstants.LOG_DIR);
    }

    static GroundZeroPersistentState LoadState()
    {
        EnsureProfileDirs();

        GroundZeroPersistentState state = new GroundZeroPersistentState();
        if (!FileExist(GroundZeroConstants.STATE_PATH))
        {
            SaveState(state);
            GroundZeroLogging.Info("Persistence", "Created default persistent state");
            return state;
        }

        JsonFileLoader<GroundZeroPersistentState>.JsonLoadFile(GroundZeroConstants.STATE_PATH, state);
        RepairState(state);
        GroundZeroLogging.Info("Persistence", "Loaded persistent state eventState=" + state.EventState.ToString());
        return state;
    }

    static void RepairState(GroundZeroPersistentState state)
    {
        if (!state) return;

        if (!state.Stages) state.Stages = new array<ref GroundZeroStageRuntime>();
        if (!state.Carriers) state.Carriers = new array<ref GroundZeroCarrierRuntime>();
        if (!state.Checkpoints) state.Checkpoints = new array<ref GroundZeroCheckpointRuntime>();
        if (!state.DroppedItems) state.DroppedItems = new array<ref GroundZeroDroppedItemRuntime>();
        if (state.StateVersion < 2) state.StateVersion = 2;

        if (state.EventState < GroundZeroEventState.GZ_IDLE || state.EventState > GroundZeroEventState.GZ_CLEANUP)
            state.EventState = GroundZeroEventState.GZ_IDLE;
    }

    static void BackupState(GroundZeroPersistentState state)
    {
        if (!state) return;
        EnsureProfileDirs();
        JsonFileLoader<GroundZeroPersistentState>.JsonSaveFile(GroundZeroConstants.STATE_BACKUP_PATH, state);
    }

    static void SaveState(GroundZeroPersistentState state)
    {
        if (!state) return;
        EnsureProfileDirs();
        BackupState(state);
        JsonFileLoader<GroundZeroPersistentState>.JsonSaveFile(GroundZeroConstants.STATE_PATH, state);
    }

    static void ResetState()
    {
        GroundZeroPersistentState state = new GroundZeroPersistentState();
        SaveState(state);
        GroundZeroLogging.Info("Persistence", "State reset to idle");
    }
}
