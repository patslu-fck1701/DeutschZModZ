/*
    DeutschZ_GroundZero
    Owner: Patrick Sluzalek / fck1701
    Module: 1_Core / GroundZeroEnums
    Purpose: Stable enum values used by persistent state and managers.
    Dependencies: DayZ scripts; optional CF/Expansion APIs only through adapter methods.
    Compliance: Original DeutschZ implementation. No copied foreign mod code, assets, configs or stubs.
*/

enum GroundZeroEventState
{
    GZ_IDLE = 0,
    GZ_STARTING = 1,
    GZ_STAGE_ACTIVE = 2,
    GZ_FINAL_READY = 3,
    GZ_FINAL_ACTIVE = 4,
    GZ_EXTRACTION_ACTIVE = 5,
    GZ_COMPLETED = 6,
    GZ_FAILED = 7,
    GZ_CLEANUP = 8
}

enum GroundZeroStageState
{
    GZ_STAGE_LOCKED = 0,
    GZ_STAGE_ENTERED = 1,
    GZ_STAGE_OBJECTIVE_ACTIVE = 2,
    GZ_STAGE_COMPLETED = 3,
    GZ_STAGE_FAILED = 4
}

enum GroundZeroBossState
{
    GZ_BOSS_NONE = 0,
    GZ_BOSS_SPAWNED = 1,
    GZ_BOSS_PHASE_ONE = 2,
    GZ_BOSS_PHASE_TWO = 3,
    GZ_BOSS_PHASE_THREE = 4,
    GZ_BOSS_DEAD = 5
}

enum GroundZeroMarkerType
{
    GZ_MARKER_NONE = 0,
    GZ_MARKER_SEARCH_LARGE = 1,
    GZ_MARKER_SEARCH_SMALL = 2,
    GZ_MARKER_EXACT = 3
}

enum GroundZeroDeathReason
{
    GZ_DEATH_UNKNOWN = 0,
    GZ_DEATH_PVE = 1,
    GZ_DEATH_PVP = 2
}
