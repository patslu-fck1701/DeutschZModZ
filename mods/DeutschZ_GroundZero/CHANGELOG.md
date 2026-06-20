## 2026-06-20 - GroundZero Hotfix v7

- Fixed Mission module compile error in `scripts/5_Mission/GroundZeroMissionHooks.c`: `Unknown type PlayerBase`.
- Moved PlayerBase RPC/death hooks from Mission module to `scripts/4_World/GroundZeroPlayerHooks.c`, because PlayerBase is a World type.
- Removed the non-essential connect-log hook from `GroundZeroMissionHooks.c` so 5_Mission no longer declares PlayerBase parameters.
- Moved `GroundZeroRetryUI` implementation from Mission module to `scripts/4_World/GroundZeroRetryUI.c`; left the Mission file as a placeholder to overwrite the old unsafe source during hotfix install.
- Updated GroundZero version markers to `0.4.4-mission-hooks-hotfix`.
- No gameplay feature changes. No foreign mod code or assets added.


## 2026-06-20 - GroundZero Hotfix v6

- Fixed World module compile error in `scripts/4_World/GroundZeroZombieManager.c`: `No return statement in function returning non-void`.
- Rewrote `ClassForThreat` from compressed one-line returns into explicit multi-line return branches with a final fallback return for DayZ script compiler compatibility.
- No gameplay feature changes. No foreign mod code or assets added.


## 2026-06-20 - GroundZero Hotfix v5

- Fixed World module compile error in `scripts/4_World/GroundZeroItems.c`: `Incompatible parameter 'parentType'`.
- Changed `parentType = parentType.ToLower();` to in-place lowercase conversion `parentType.ToLower();` for DayZ script compatibility.
- No gameplay feature changes. No foreign mod code or assets added.


## 2026-06-20 - GroundZero Hotfix v4

- Moved `GroundZeroCore.c`, `GroundZeroEventManager.c` and `GroundZeroNotificationManager.c` from `scripts/3_Game` to `scripts/4_World`.
- Fixed Game module compile error: `Unknown type PlayerBase` by keeping PlayerBase/Man runtime logic in World module.
- Kept `scripts/3_Game` limited to config, persistence and logging helpers.

# CHANGELOG

## 2026-06-20 - Core/Bridge/Event Integration

- Core-/ExpansionBridge-Basis fuer die drei Event-Module vorbereitet.
- Sichere Provider- und Pfadstruktur ergaenzt.
- Keine Fremdmod-Dateien oder kopierten Fremdklassen hinzugefuegt.

# CHANGELOG

## 0.4.1-source-audit

- Renamed `$PREFIX$` to `$PBOPREFIX$`.
- Added root compliance files required by the DeutschZ source standard.
- Added source `mod.cpp` with only existing/no-missing asset references.
- Moved retry and abort RPC handling from `MissionServer.OnRPC` to `PlayerBase.OnRPC`.
## 0.4.2-source-hotfix - 2026-06-20

- Fixed GameLib compile error by moving GroundZeroConfig, GroundZeroPersistence and GroundZeroLogging from scripts/2_GameLib to scripts/3_Game.
- Removed JsonFileLoader usage from GameLib load scope.
- Kept scripts/2_GameLib intentionally empty except for documentation placeholder.
- No PBO build and no local server test performed.
## 0.4.1-hotfix - 2026-06-20

- Fixed GameLib compile error by removing runtime helper duplicates from `scripts/2_GameLib`.
- `GroundZeroConfig`, `GroundZeroLogging` and `GroundZeroPersistence` now compile only from `scripts/3_Game`, where `JsonFileLoader`/`GetGame` are available.
- No PBO built and no local server test performed.
## 2026-06-20 - Hotfix v3

- Fixed Game module compile issue in `scripts/3_Game/GroundZeroCore.c`.
- Renamed member variable `EventManager` to `m_EventManager` to avoid collision with existing DayZ/global type name `EventManager`.
- No PBO built and no server test performed.
