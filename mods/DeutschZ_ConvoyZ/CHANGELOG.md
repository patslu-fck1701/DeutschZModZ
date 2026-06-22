## FIX39 - Full DeutschZ Baseline / Changelog Refresh (2026-06-22)
- Included in the full DeutschZ source replacement package after KotHZ live-test regression fixes.
- No ConvoyZ code changes in this pass.
- Staggered event start and smoke no-op compatibility remain active.

## FIX37 - Repo Clean / Changelog Baseline (2026-06-22)
- Repository-Basis auf aktuellen ConvoyZ-FIX36-Stand abgeglichen.
- Behaelt naeheren Eventstart, 3D-Marker-Request ueber Core/Bridge, zweite kleine Wave und Smoke-No-Op-Kompatibilitaet bei.
- Physische Smoke-/Crashobjekt-Risikopfade bleiben deaktiviert.
- Changelog fuer kuenftige Full-Source-Pakete aktualisiert.

## FIX36 - Event Ausbau Stage 1 / closer staged starts
- Adjusted staged test-start order: KotHZ 1 min, ConvoyZ 3 min, GroundZero 5 min, CourierZ 7 min.
- Keeps crash-risk features off: KotHZ music, physical smoke/fog cannons and heavy marker fallback objects remain disabled.
- Re-enables/keeps stable gameplay additions only: visible flags, Expansion markers, HUD/progress, infected/waves, rewards and reduced no-spam status messages.
- ConvoyZ now routes its 3D marker request through Core/ExpansionBridge when enabled.

# DeutschZ_ConvoyZ Changelog

## 0.1.1-fix33-compile-chain - 2026-06-22

- Fixed World compile chain error: `DeutschZConvoyZSpawnManager.RefreshSmoke` is present again.
- `RefreshSmoke(...)` is intentionally a no-op compatibility method while physical smoke is disabled.
- ConvoyZ visibility remains routed through DeutschZ_ExpansionBridge real Expansion marker requests.
- No physical smoke grenade fallback objects are spawned during crash isolation.


## FIX31 - KotHZ Crash/Marker/Flag Regression (2026-06-22)
- KotHZ crash isolation: music hard-disabled and risky RuntimeFlagpole attachment path removed from active use.
- KOTH flag now uses a safe visible Flag_Base-derived DeutschZ flag object.
- ExpansionBridge now creates real DayZ Expansion server markers via ExpansionMarkerModule/CreateServerMarker.
- ConvoyZ physical smoke and failing wreck classes reduced for crash isolation.

# CHANGELOG

## 2026-06-20 - Core/Bridge/Event Integration

- Core-/ExpansionBridge-Basis fuer die drei Event-Module vorbereitet.
- Sichere Provider- und Pfadstruktur ergaenzt.
- Keine Fremdmod-Dateien oder kopierten Fremdklassen hinzugefuegt.

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

## FIX33 - 2026-06-22 - ConvoyZ compile chain fix
- Restored `DeutschZConvoyZSpawnManager.RefreshSmoke(...)` as a safe no-op compatibility method.
- Physical smoke refresh remains disabled during crash isolation.
- ConvoyZ visibility stays routed through DeutschZ_ExpansionBridge / Expansion markers.
- Replaced remaining problematic `ZmbM_SoldierNormal_Beige` fallback with `ZmbM_usSoldier_Officer_Desert`.

