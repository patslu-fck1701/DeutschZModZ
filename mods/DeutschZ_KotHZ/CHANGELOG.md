# CHANGELOG

## 2026-06-20 - 2.2.9 FIX23 TestReady

- Event music remains fully disabled to avoid server/native crash risk.
- Bridge notification routing enabled by default for visible popup/chat fallback.
- Flag texture paths normalized to reduce white-flag risk.
- Generated fast-test config defaults validated for marker/3D-marker/notify testing.


## 2026-06-20 - FIX21 NoMusic Marker Safe

- Disabled KOTH event music completely for hosted-server safe boot.
- Removed automatic sound trigger sync from the runtime flagpole.
- Forced KOTH flag texture assignment after flag attachment to avoid white flag visuals.
- Kept marker/3D marker requests active through DeutschZ Core/ExpansionBridge.


## 2026-06-20 - 0.2.4 Start-Ready Visible Test Build

- Generated/default config now enables fast test timings, map marker, 3D marker intent, vanilla popup and chat fallback.
- DeutschZEventSettings notification defaults changed to visible local testing: Expansion notify off by default, vanilla/chat on.
- ConfigManager no longer disables visible fallback notifications during generated config repair.
- Keeps Infected Siege gameplay, infected waves, capture flow and reward flow intact.
- No direct Expansion calls added; marker/notification route stays through Core/Bridge.

## 2026-06-20 - 0.2.3 Event Bridge Config Polish

- Routes configured Expansion-style notifications through the DeutschZ Core/ExpansionBridge provider.
- Creates matching Core 3D marker intents when `DeutschZEventSettings.Markers.Use3DMarker` is enabled.
- Reduces startup runtime-object cleanup spam to count-only logging.
- Adds visible `DeutschZEventSettings` fast-test block to READY_COPY configs.
- No foreign mod code, classes, configs, UI or assets added.

## 2026-06-20 - 0.2.2 KotHZ StoreLoad Compile Hotfix

- Fixed World-script compile crash in `DeutschZKotHZ_RuntimeFlagpole`: `SetPartsAfterStoreLoad` was marked as `override`, but the current DayZ base class has no matching method.
- Applied the same correction to `DeutschZKotHZ_RuntimeFogEmitter` to prevent the next compile stop.
- Keeps the 0.2.1 unified `DeutschZEventSettings` config standard and fast-test marker/notification setup intact.
- No gameplay feature changes.
- No foreign mod code, classes, configs, UI or assets added.

## 2026-06-20 - 0.2.1 EventSettings Standard Test

- Added unified `DeutschZEventSettings` config block with the same setting names as ConvoyZ and GroundZero.
- Syncs shared marker, 3D marker, notification, scheduling, cleanup, debug and fast-test values into legacy KotHZ keys.
- Keeps Expansion marker route through DeutschZ Core/Bridge; no direct Expansion calls added.
- Added override markers for runtime storage hooks and reduced RuntimeFlagpole config warnings.
- No foreign mod code, classes, configs, UI or assets added.

## 2026-06-20 - Core/Bridge/Event Integration

- Core-/ExpansionBridge-Basis fuer die drei Event-Module vorbereitet.
- Sichere Provider- und Pfadstruktur ergaenzt.
- Keine Fremdmod-Dateien oder kopierten Fremdklassen hinzugefuegt.

# DeutschZ_KotHZ Changelog

## 2.2.7 - FIX20 Sound Path Aligned
- OGG-Dateiname und `CfgSoundShaders`-Pfad sauber aufeinander abgeglichen.
- Aktive OGG-Datei: `data/sounds/DeutschZ_KotHZ_RoterRauch.ogg`.
- Aktiver SoundShader-Pfad: `\DeutschZ_KotHZ\data\sounds\DeutschZ_KotHZ_RoterRauch` ohne Dateiendung, wie fuer DayZ-Soundshader ueblich.
- Alte interne OGG-Zieldatei `data/sounds/koth-laut-timer.ogg` entfernt, damit keine Namens-/Pfadverwechslung bleibt.
- SoundSet-Name bleibt `DeutschZ_KotHZ_EventMusic_SoundSet`, damit vorhandene Configs/Scripts weiter funktionieren.

# Changelog – DeutschZ_KotHZ

## FIX20 – Custom Event Music OGG

- Event-Musikdatei ersetzt.
- Neue Benutzerdatei `KotHZ im roten Rauch.ogg` wurde als `data/sounds/DeutschZ_KotHZ_RoterRauch.ogg` eingebunden.
- `CfgSoundShaders` und SoundSet-Namen bleiben unveraendert, damit keine Config-/Script-Umstellung noetig ist.
- Mod-Version auf `2.2.7 Infected Siege FIX20 Sound Path Aligned` gesetzt.
- FIX18 Compliance-/No-Copy-Dokumentation bleibt erhalten.

## FIX18 – Compliance Audit / No-Copy Cleanup

- Compliance-Dokumentation hinzugefuegt.
- Standard-Kopfkommentar in Code-Dateien eingefuegt.
- MarkerBackend-Begriffe durch eigene `MarkerMode`-Benennung ersetzt.
- ExpansionAI-/EventAI-Reste entfernt bzw. in deaktivierte eigene DeutschZ-NPC-Reserve umbenannt.
- Alte `DeutschZ_KOTH`, `DeutschZ_KOTHZ`, `DeutschZKOTH`, `DZKOTH` Textreste bereinigt.
- Alter falscher Profilpfad in Beispieldateien korrigiert.
- COT-Verweis aus EditHint entfernt.
- Doppelte inaktive Beispielasset-Ordner entfernt.
- Root/Prefix bleibt `DeutschZ_KotHZ`.
- Configpfad bleibt `$profile:DeutschZ/KotHZ/Config/`.

## FIX17 – Proper Test Loot

- Schnellstart-Testversion.
- High-Value-Testloot aus serverseitigen Classname-Referenzen.
- Ready-copy Configs beigelegt.

## FIX15/FIX14 – Safe Recheck

- Statusbar 500m.
- Duplicate Notify Schutz.
- Safe-Check auf Scriptmodule und alte Pfade.
