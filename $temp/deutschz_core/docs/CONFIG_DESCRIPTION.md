# DeutschZ Core Config-Beschreibung

Basis-Modul fuer alle modernen DeutschZ-Systeme. Stellt gemeinsame Profilepfade, Logging, RateLimiter, Provider-APIs und Event-State-Grundlagen bereit.

## Abhaengigkeiten

Abhaengigkeiten: DayZ. Muss vor DeutschZ_ExpansionBridge und den Event-Mods geladen werden.

## Profilepfade

- `$profile:DeutschZ/`
- Event-spezifisch: `$profile:DeutschZ/Core/` beziehungsweise vorhandene Mod-Konfigpfade.

## Types.xml

Keine types.xml noetig, weil keine Spawn- oder Loot-Items enthalten sind.

## Teststatus

Fuer ersten Dedicated-Test vorbereitet. Kein PBO gebaut. Kein lokaler Server-Test durchgefuehrt.
