# CHANGELOG

## 2026-06-20 - 0.1.3 ServerProfile Hotfix

- Fixed `DeutschZCore_ServerProfile` World-script compile crash by removing internal `SystemPath()` helper calls from `ConfigPath`, `StatePath` and `BackupPath`.
- Profile folder creation remains under `$profile:DeutschZ/`.
- Includes previous 0.1.2 EventState compile fix.
- No gameplay feature changes.
- No foreign mod code, classes, configs, UI or assets added.

## 2026-06-20 - 0.1.2 EventState Hotfix

- Fixed `DeutschZCore_EventBase` compile crash by resolving event-state enum values through `DeutschZCore_EventState.*` instead of bare identifiers.
- No gameplay feature changes.
- No foreign mod code, classes, configs, UI or assets added.

## 2026-06-20 - Core/Bridge/Event Integration

- Core-/ExpansionBridge-Basis fuer die drei Event-Module vorbereitet.
- Sichere Provider- und Pfadstruktur ergaenzt.
- Keine Fremdmod-Dateien oder kopierten Fremdklassen hinzugefuegt.

# Changelog

## 0.1.0

- Initiale Source-Struktur angelegt.
