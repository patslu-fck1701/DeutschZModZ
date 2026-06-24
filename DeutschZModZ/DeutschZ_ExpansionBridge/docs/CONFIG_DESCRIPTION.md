# DeutschZ ExpansionBridge Config-Beschreibung

Adapter-Grenze zwischen DeutschZ-Mods und optionalen Expansion-Funktionen. Events sprechen nicht direkt mit Expansion, sondern nur ueber Core-Provider.

## Abhaengigkeiten

Abhaengigkeiten: DeutschZ_Core. Optionale Expansion-Funktionen bleiben hinter Adapter/TODO, keine geratenen API-Aufrufe.

## Profilepfade

- `$profile:DeutschZ/`
- Event-spezifisch: `$profile:DeutschZ/ExpansionBridge/` beziehungsweise vorhandene Mod-Konfigpfade.

## Types.xml

Keine types.xml noetig, weil keine Spawn- oder Loot-Items enthalten sind.

## Teststatus

Fuer ersten Dedicated-Test vorbereitet. Kein PBO gebaut. Kein lokaler Server-Test durchgefuehrt.
