# GITHUB COMMIT CHANGELOG - FIX43

Proposed commit:
fix(events): prepare FIX43 safe locations, Convoy crash isolation and GroundZero radius HUD

Base note:
- Built from the available FIX42/FIX41 source context in this ChatGPT workspace and cross-checked against the readable GitHub commit/search state.
- Direct GitHub push was not performed here because the GitHub write action returned HTTP 403 for content updates.

Changed mod:
- DeutschZ_ConvoyZ

Package rule:
- This package includes the complete source folder for this changed mod.

Changes:
- Moved ConvoyZ default event center away from CourierZ and away from Green Mountain.
- Updated crash objects, blackbox, reward and AI spawn positions.
- Added named military loadout handling for DZCV_MilitaryLight, DZCV_MilitaryRifleman and DZCV_MilitaryHeavy.
- Disabled physical smoke by default through `Smoke.Enabled = 0` to isolate reported possible Convoy crash.
- Kept unsafe M249 class guard usage.
