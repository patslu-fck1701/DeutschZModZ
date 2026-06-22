# GitHub Commit Changelog - FIX25 KotHZ Music RPC

Suggested commit:

```bash
git add mods/DeutschZ_KotHZ
git commit -m "fix(kothz): restore event music through client rpc"
```

## Changed
- Removed hard-disable from KotHZ music config repair.
- Default config now enables event music on Start and Captured phases.
- Added `PLAY_MUSIC` RPC and client-side `SEffectManager.PlaySound` trigger for nearby players.
- Ready-copy configs and config guide updated to match active music defaults.

## Verification checklist
- KotHZ should play configured music for nearby players at event start.
- Music should also trigger when the boss/reward completion path finishes.
- Smoke/fog remains disabled to avoid mixing crash-prone visual paths with the music fix.
