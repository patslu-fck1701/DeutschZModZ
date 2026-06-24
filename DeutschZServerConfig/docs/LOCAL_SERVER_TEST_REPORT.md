# Local Server Test Report

Stand: 2026-06-23 11:38 Europe/Berlin

## Source/build validation

- `DeutschZ_Core/config.cpp` had unresolved merge markers in the OperationDeutschZ item block. Fixed locally by keeping the OperationDeutschZ-specific display names/descriptions and the newer additional special items.
- Final source validation passed:
  - `P:\GitHub_DeutschZModZ\DeutschZModZ\local_test_results\2026-06-23_11-35-26`
- Final build/deploy for all DeutschZ mods, including `@DeutschZ_OperationDeutschZ`, passed:
  - `P:\GitHub_DeutschZModZ\DeutschZModZ\local_test_results\2026-06-23_11-35-35`

## Full modline smoke test

Run folder:

```text
P:\GitHub_DeutschZModZ\DeutschZModZ\local_test_results\codex_full_modline_postfix_2026-06-23_11-36-25
```

Result:

- Server started with the requested full mod stack using local server-root paths for installed `@` mods and Workshop cache paths for missing server-root mods.
- Missing mod paths: none.
- `DayZServer_x64.exe` was still alive after 70 seconds.
- No `SCRIPT ERROR`, `requires addon`, `Can't compile`, `Undefined function`, `Unknown type`, `Can't open file`, signature, wrong-signature, or access violation matches were found.
- OperationDeutschZ safe-boot print lines were not observed in this full-modline run.

## OperationDeutschZ relative-modline check

Run folder:

```text
P:\GitHub_DeutschZModZ\DeutschZModZ\local_test_results\codex_operation_relative_2026-06-23_11-32-46
```

Result:

- Started with relative server-root modline including `@DeutschZ_OperationDeutschZ`.
- No script/addon/compile/signature pattern was logged before shutdown.
- The process was no longer alive after 65 seconds and produced a DayZ minidump in `profiles_codex_operationtest`.
- RPT stopped very early, so this remains an open local engine/minidump issue rather than a confirmed script compile issue.

## Notes

- Existing `F:\Programme\steamapps\common\DayZServer\start.bat` was not modified and still lacks `@DeutschZ_OperationDeutschZ` and several requested Workshop mods.
- The test used isolated profiles:
  - `F:\Programme\steamapps\common\DayZServer\profiles_codex_fulltest`
  - `F:\Programme\steamapps\common\DayZServer\profiles_codex_operationtest`
