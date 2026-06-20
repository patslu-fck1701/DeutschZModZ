# CHANGELOG

## 2026-06-20 - 0.1.3 Visible Marker/Notify Fallbacks

- Marker provider now keeps marker requests tracked and creates a visible vanilla fallback object for test visibility.
- Notification provider now sends visible server chat fallback messages to online players.
- AI provider now uses safe vanilla infected fallback spawning instead of a no-op guard path.
- Expansion API calls remain behind the Bridge boundary; no direct Expansion calls were added to event mods.
- No foreign mod code, classes, configs, UI or assets added.

## 2026-06-20 - 0.1.2 Notification Provider

- Registers a safe notification provider with DeutschZ Core.
- Provider records notification intent only; no unverified direct Expansion API calls were added.
- No gameplay feature changes.
- No foreign mod code, classes, configs, UI or assets added.

## 2026-06-20 - Core/Bridge/Event Integration

- Core-/ExpansionBridge-Basis fuer die drei Event-Module vorbereitet.
- Sichere Provider- und Pfadstruktur ergaenzt.
- Keine Fremdmod-Dateien oder kopierten Fremdklassen hinzugefuegt.

# Changelog

## 0.1.0

- Initiale Source-Struktur angelegt.
