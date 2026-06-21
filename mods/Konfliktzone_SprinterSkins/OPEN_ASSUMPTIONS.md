# OPEN_ASSUMPTIONS - Konfliktzone_SprinterSkins

- No separate roof decal selection was found in the provided MBM config reference.
- Roof decal PAA files are therefore not assigned in `config.cpp`.
- Door classes did not expose a separate decal selection. Door decal PAA is therefore not assigned as a fake second texture.
- KA/01 and KA/02 are separate classnames, but use the same confirmed texture mapping until a real roof/decal selection is verified.
- In-game spawn validation still needs to be done on a server with the current MBM Mercedes Sprinter mod loaded.

