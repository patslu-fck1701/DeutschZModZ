# GitHub Commit Changelog - FIX25 Event Visual Stability

Suggested commit:

```bash
git add mods/DeutschZ_GroundZero
git commit -m "fix(groundzero): dedupe signal marker and add stage progress hud"
```

## Changed
- Reworked GroundZero marker bridge handling so map and 3D marker variants no longer create parallel visible IDs.
- Added legacy marker cleanup for `GroundZero_3D_*`, `Signalstation_*` and `Sendestation_*`.
- Added client HUD RPC/state/layout for GroundZero stage progress.
- Broadcasts status/progress every second while a stage is active and hides HUD after stage campaign completion.

## Verification checklist
- Signalstation/Sendestation should show one marker per active stage.
- Signalstation should show a visible GroundZero progress/statusbar.
- Event threat spawns remain staggered by WaveDelaySeconds and SpawnBatchDelaySeconds.
