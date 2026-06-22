# DeutschZ FIX41 Validation

Date: 2026-06-22

## Inputs checked

- `C:\Users\Public\Pictures\crash_2026-06-22_03-45-17.log`
- `C:\Users\Public\Pictures\script_2026-06-22_03-45-17.log`
- `C:\Users\Public\Pictures\server_console.log`
- `C:\Users\Public\Pictures\DayZServer_x64_2026-06-22_03-45-06.RPT`
- `C:\Users\Public\Pictures\DayZServer_x64_2026-06-22_03-45-06.ADM`

## Result

- Crash stack confirms `Weapon.SaveCurrentFSMState` on exact vanilla `M249`.
- Local mission init was checked and does not spawn `M249`.
- Active DeutschZ source/default reward search found no exact vanilla `M249` reward source in the six active mods.
- `GCGN_M249` and `GCGN_M249_Mag` remain in KotHZ defaults and are intentionally allowed.
- DeutschZ now adds a shared unsafe-class guard and uses it in active reward/loadout paths.

## KotHZ FIX41 checks

- Event marker creation now removes old IDs before creating the active marker.
- Active visible marker ID is based on `KotHZ_<ZoneName>`.
- Marker, HUD distance and capture radius use the same event center: `FlagpolePosition` first, `Position` fallback.
- Capture is automatic in radius.
- No hidden action-menu interaction is required.
- Player messaging now says entry, leave, contested, active and completion states clearly.

## Runtime note

The provided crash log also shows Expansion/AI/entity storage activity around the M249 failure. If the server still crashes after these PBOs, the remaining M249 source is likely persisted server profile data or an external mod/loadout, not a DeutschZ reward entry.
