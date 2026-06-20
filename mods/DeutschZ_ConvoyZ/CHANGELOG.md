# CHANGELOG.md

## FIX24_COMPLIANCE_AUDITED - 2026-06-18

- Compliance-Dokumente hinzugefuegt.
- DeutschZ-Kopfkommentar auf Code-/Config-Dateien gesetzt.
- Active-Source-Scan auf verbotene Fremd-/Stub-Begriffe ausgefuehrt.
- Asset-Pfade fuer DeutschZ-Rewarditems auf `DeutschZ_ConvoyZ\Assets\Case\...` normalisiert.
- Testversion aus FIX23 bleibt aktiv: schneller Start, kurze Hackzeit, M249 entfernt, KobraOptic als Ersatz.

## FIX25_LOCKONSPAWN_COMPILE - 2026-06-19

- Compilefehler in `DeutschZConvoyZSpawnManager.c` behoben.
- Ungueltiger Zugriff auf `veh.obsolete vehicle lock field` entfernt.
- Grund: `DeutschZConvoyZVehicleDef` besitzt kein Feld `obsolete vehicle lock field`.
- Entscheidung: Entfernen statt Feld hinzufuegen, weil `Vehicles` in dieser Version leer bleibt und keine fahrbaren Event-Trucks verwendet werden.

## FIX26_STATIC_ONLY_HARDENED - 2026-06-19

- Static-only ConvoyZ hardening.
- Active fahrbare Vehicle-Spawnlogik aus dem SpawnManager entfernt.
- `vehicle preparation routine`, `real drivable vehicle script type`, Vehicle-Health-Prepare und Vehicle-Lock-/Inventory-Prepare entfernt.
- Runtime-State `separate runtime vehicle list` entfernt; Cleanup nutzt nur noch SpawnedObjects, SpawnedAI, SpawnedRewards und SmokeObjects.
- Alte `Vehicles`-Eintraege werden beim Config-Load in statische `CrashObjects` umgewandelt und danach geleert.
- `Vehicles` bleibt nur als leeres Kompatibilitaetsfeld fuer alte Configs erhalten.
- Default-Config bleibt statisch: `Vehicles: []`, Crash-Deko ueber `CrashObjects`.
