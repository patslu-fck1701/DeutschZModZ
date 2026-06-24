# GITHUB COMMIT CHANGELOG - FIX43

Proposed commit:
fix(events): prepare FIX43 safe locations, Convoy crash isolation and GroundZero radius HUD

Base note:
- Built from the available FIX42/FIX41 source context in this ChatGPT workspace and cross-checked against the readable GitHub commit/search state.
- Direct GitHub push was not performed here because the GitHub write action returned HTTP 403 for content updates.

Changed mod:
- DeutschZ_GroundZero

Package rule:
- This package includes the complete source folder for this changed mod.

Changes:
- Removed Green Mountain from default GroundZero stage positions.
- Made stage positions sequential/unique instead of random duplicate-prone selection.
- Updated final/extraction default locations to avoid overlap.
- Limited HUD/statusbar RPC to local stage radius and hides active HUD for players outside the radius.
