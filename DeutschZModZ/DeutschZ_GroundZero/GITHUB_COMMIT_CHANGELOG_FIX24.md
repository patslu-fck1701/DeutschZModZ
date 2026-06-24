# GitHub Commit Changelog - DeutschZ_GroundZero 0.4.7-fix24-marker-dedupe-staggered

Suggested commit message:

```txt
fix(GroundZero): dedupe markers and stagger Signalstation load
```

Changed files:

- `scripts/1_Core/GroundZeroConstants.c`
  - Version bumped to `0.4.7-fix24-marker-dedupe-staggered`.

- `scripts/3_Game/GroundZeroConfig.c`
  - Added runtime throttling/config values:
    - `MarkerUpdateIntervalSeconds`
    - `MaxActiveInfected`
    - `MaxSpawnPerBatch`
    - `SpawnBatchDelaySeconds`
    - `WaveDelaySeconds`

- `scripts/4_World/GroundZeroCoreBridge.c`
  - Added unified marker create/update methods.
  - Uses Core/ExpansionBridge provider only; no direct Expansion calls.

- `scripts/4_World/GroundZeroMarkerManager.c`
  - Reworked marker handling to one stable logical marker per target.
  - Keeps markers enabled by default.
  - Prevents duplicate map + 3D marker pair creation.
  - Uses create-once/update-after logic with fallback recreate if provider lost marker state.
  - Cleanup clears known marker registry.

- `scripts/4_World/GroundZeroStageManager.c`
  - Delays threat spawning after stage marker/notification.
  - Adds visible progress status messages for Signalstation and later stages.
  - Avoids stage start doing marker + infected + AI + notification all in one instant.

- `scripts/4_World/GroundZeroZombieManager.c`
  - Replaced one-frame infected mass spawn with capped staggered batches.
  - Adds active local infected limit and batch logging.

- `Profiles/DeutschZ/GroundZero/READY_COPY_CONFIGS/GroundZeroConfig.json`
  - Added matching default config values.

Smoke note:

- ConvoyZ physical smoke is currently still intentionally isolated/no-op in the uploaded source. I did not force unknown smoke activation calls into the source because that would risk a compile/runtime crash without confirming the exact DayZ smoke API available in your build. The reported smoke issue is documented for the next safe pass: use a confirmed smoke activation method or a DeutschZ-owned FX fallback, not just spawned smoke grenade loot.
