# MBM Reference Check

Source reference used:

```text
reference/MBM_config.bin
```

The file was supplied in the Codex assignment package and de-binarized only for verification. It is not included in this addon source or PBO.

## Verified

- CfgPatches class: `MBM_Sprinter`
- Cargo base class: `MBM_Sprinter_BlackCargo`
- Driver door base: `MBM_Sprinter_doors_driver_BlackCargo`
- Co-driver door base: `MBM_Sprinter_doors_codriver_BlackCargo`
- Cargo door bases:
  - `MBM_Sprinter_doors_cargo1_BlackCargo`
  - `MBM_Sprinter_doors_cargo2_BlackCargo`
  - `MBM_Sprinter_doors_cargo3_BlackCargo`

## Cargo HiddenSelections

Confirmed relevant Cargo selections:

```cpp
"camo_body",
"camo_rear_glass",
"camo_decal_body",
"camo_decal_windshield"
```

The Cargo class also has 12 light selections before those four entries. The final config keeps those 12 texture slots empty and assigns the four confirmed body/decal texture slots in order.

## Roof

No separate roof decal selection was found. Roof PAA files are not assigned.

## Doors

Driver and co-driver BlackCargo doors expose only:

```cpp
"camo"
```

Cargo doors expose:

```cpp
"camo",
"camo_rear_glass"
```

No separate door decal selection was confirmed. Door decal PAA is not assigned.

