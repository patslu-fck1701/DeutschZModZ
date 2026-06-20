# CHANGELOG

## 2026-06-20 - 0.1.4-courierz-provider-api

- Added explicit Create3DMarker provider method for CourierZ and future events.
- Added DeutschZ_CourierZ placeholder references to documentation.

## 2026-06-20 - 0.1.6 FIX23 Provider API Validation

- Kept Core provider APIs stable for Marker, Notification and AI routing.
- Version aligned with FIX23 full replacement package.
- No gameplay dependency added to Core.


## 2026-06-20 - 0.1.5 Visible Provider Readiness

- Kept current safe-boot core state intact.
- Documented event-provider readiness for visible notifications through DeutschZ_ExpansionBridge.
- No gameplay logic moved into Core.
- No foreign mod code, classes, configs, UI or assets added.

## 2026-06-20 - 0.1.4 Notification Provider

- Added optional `DeutschZCore_NotificationProviderAPI` and ServiceLocator registration/getter.
- Keeps notification routing behind Core/Bridge, so event mods do not call Expansion directly.
- No gameplay feature changes.
- No foreign mod code, classes, configs, UI or assets added.

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
