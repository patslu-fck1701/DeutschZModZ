# Konfliktzone_SprinterSkins

Clean retexture addon for MBM Mercedes Sprinter.

## Vehicles

- `KZ_Sprinter_Admin_Cargo_KA01`
- `KZ_Sprinter_Admin_Cargo_KA02`

Both variants inherit from `MBM_Sprinter_BlackCargo` and use the original MBM red body texture by reference:

```cpp
MBM_MercedesSprinter\data\body_red.paa
```

Own Konfliktzone decal textures are used for the side/body and rear-window decal selections.

## Dependency

The verified MBM CfgPatches class is:

```cpp
MBM_Sprinter
```

No MBM P3D, scripts, sounds, RVMATs, textures or PBO contents are copied into this addon.

## Roof / Door Decals

The supplied roof and door decal PAA files are own assets, but the de-binarized MBM config reference did not confirm a separate roof decal selection or door decal selection for the relevant Cargo classes.

Therefore:

- roof decal textures are not assigned in `config.cpp`
- door decal textures are not assigned as fake second door textures
- KA/01 and KA/02 are separate classnames, but use the same confirmed texture layout until a real roof selection is verified

