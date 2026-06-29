# Projektstand_AKTUELL

**Projekt:** DeutschZModZ  
**Stand:** 2026-06-29 15:20 Europe/Berlin  
**Status:** Local smoke test OK, client/in-game test still required

## Summary

DeutschZModZ was stabilized and documented for the current update cycle. The main work areas were KotHZ initialization/config bootstrap, GroundZero notification cooldowns, NoxZ Phone market/ATM/marker cleanup, Blackmarket AI, Expansion Object Map import and mapgrouppos merge tracking.

A local server smoke test verifies compile/start/config loading. It does not replace a real client join, visual marker checks, ATM interaction checks or gameplay balance testing.

## Completed / active changes

### KotHZ

- `DeutschZ_KotHZ` initializes earlier server-side.
- `MissionServer` safely calls the KotHZ manager in the constructor.
- `OnInit`, `OnMissionStart` and `ClientReady` remain fallback paths.
- `$profile:KotHZ/DZ_KotHZ_Config.json` was generated locally.
- `DebugMode` exists in the generated config.
- Test evidence included `Config geladen` and `Manager initialisiert`.
- `DeutschZ_KotHZ.pbo` was rebuilt, signed and deployed into ready/server bundles.

### GroundZero

- Notification spam reduced.
- Duplicate status/progress messages are cooldowned per message.
- Progress broadcasts now use the configured status interval instead of hard-coded 10 seconds.
- Event/HUD logic was not replaced by chat messages.
- Local server bootstrap loaded Config Version 6, persistence and core.
- `DeutschZ_GroundZero.pbo` was rebuilt, signed and deployed.

### NoxZ Phone / Market / ATM / Marker

- Invalid ServerShop base item `MBM_DodgeRam` removed.
- Valid DodgeRam variants remain active.
- NoxZ healthcheck after cleanup: `errors=0 | warnings=0 | OK`.
- Bitcoin Exchange disabled because `Bitcoin` is not a proven loaded class.
- `Exchange.json` currently has `Rates: []`.
- Three Phone ATMs were configured.
- Server markers were configured for ATMs, SchwarzHandel and AirCraft's.
- Phone server 3D markers were enabled.

### Expansion Objects / mapgrouppos

- 14 Expansion Object Map files were copied/updated.
- `mapgrouppos.xml` was merged with Desktop MapGroupPos XML content.
- Dedupe applied by group name/position/orientation.
- Before: 11680 groups.
- Added: 4602 groups.
- After: 16282 groups.
- XML validated after merge.
- `new_Zombis_territory.xml` was intentionally not imported because its root was `territory`, not MapGroupPos structure.

### Expansion AI / Blackmarket

- New patrol: `DeutschZ Blackmarket Guards`.
- 2 AI.
- Existing `BanditLoadout`.
- `Faction: West`.
- Moderate accuracy: `0.25-0.45`.
- Respawn: 1800 seconds to avoid instant farming.
- Waypoints sit roughly 100-150 m around the Blackmarket area.

## Open / not completed

### CE/types and Economy

- No full `types.xml` balancing pass completed in this iteration.
- SNAFU/MVS military loot distribution remains open.
- nominal-0 review remains open.
- Aircraft/Blackmarket price balancing was not rewritten.

### Bitcoin

- Bitcoin Exchange remains disabled.
- Re-enable only after a loaded PBO provides a real `CfgVehicles` class `Bitcoin` and NoxZ healthcheck accepts it.

### Rewardchest / DZCR

- Not implemented in this iteration.
- No fake SeaChest subclass introduced.
- No unverified logo/chest class introduced.

## Client test checklist before live promotion

- Verify all three Phone ATMs in-client.
- Verify Phone server markers in 2D and 3D.
- Verify Blackmarket Guards spawn exactly as intended and are fair.
- Verify GroundZero no longer spams the client chat/HUD.
- Verify KotHZ scheduling and no double-init after player connect.
- Spot-check Expansion Object Map areas for missing/colliding/static floating objects.
- Check final RPT/script logs after client testing.
