# GITHUB COMMIT CHANGELOG - FIX43

Proposed commit:
fix(events): prepare FIX43 safe locations, Convoy crash isolation and GroundZero radius HUD

Base note:
- Built from the available FIX42/FIX41 source context in this ChatGPT workspace and cross-checked against the readable GitHub commit/search state.
- Direct GitHub push was not performed here because the GitHub write action returned HTTP 403 for content updates.

Changed mod:
- DeutschZ_CourierZ

Package rule:
- This package includes the complete source folder for this changed mod.

Changes:
- Moved CourierZ pickup and delivery route away from ConvoyZ shared test location.
- Updated code defaults and ready-copy profile config.
- Kept CourierZ self-contained with no dependency on ConvoyZ.
