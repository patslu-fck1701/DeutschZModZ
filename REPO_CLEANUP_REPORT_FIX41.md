# DeutschZ FIX41 Cleanup Report

Scope:
- DeutschZ_Core
- DeutschZ_ExpansionBridge
- DeutschZ_KotHZ
- DeutschZ_ConvoyZ
- DeutschZ_GroundZero
- DeutschZ_CourierZ

Excluded:
- Konfliktzone_Retexturen
- Konfliktzone_SprinterSkins
- unrelated dirty workspace files

Changes:
- Added shared exact-class M249 guard in Core.
- Routed active DeutschZ reward/loadout insertions through the guard.
- Reworked KotHZ Signalstation communication for radius-based auto-capture.
- Reworked KotHZ marker cleanup to remove legacy duplicate IDs before creating the one active marker.
- Kept disabled: KotHZ music, physical smoke, particle smoke, fog hazard, smoke cannons and risky RuntimeFlagpole attachment chain.

No source deletion or unrelated refactor was performed.
