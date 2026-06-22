# VALIDATION_EVENT_AUSBAU

Stand: 2026-06-22

## Geprueft

- KotHZ Markerlogik: alte IDs werden vor Start/Cleanup entfernt, aktive ID ist `KotHZ_<ZoneName>`.
- KotHZ Signalstation: keine Action-Menue-Erwartung, Auto-Capture im Radius, Eintritt/Austritt/Contested/Abschluss-Texte vorhanden.
- KotHZ Safe Defaults: Musik aus, Object-Smoke aus, Particle-Smoke aus, Fog aus, Smoke-Cannons aus.
- ConvoyZ Smoke: physisches Smoke-Spawning bleibt No-Op; Marker/Bridge bleibt Sichtbarkeitspfad.
- GroundZero/CourierZ: keine Musik/Smoke/Fog-Systeme aktiv.
- Event-Reihenfolge bleibt: 60 / 180 / 300 / 420 Sekunden.

## Nicht aktiviert

- keine neuen Soundloops
- keine physische Smoke-Grenade-Pflicht
- keine persistenten Partikelobjekte
- keine Fog-Hazard-Aktivierung
- keine direkten Expansion Calls in Eventmods

## Testempfehlung

1. Server mit den sechs DeutschZ-Mods starten.
2. RPT und script log auf Compile-/Init-Fehler pruefen.
3. KotHZ nach 1 Minute pruefen: ein Marker, Signalstation sichtbar, keine Aktionstaste noetig.
4. ConvoyZ nach 3 Minuten pruefen: Marker, Crashsite, Hackflow, Reward.
5. GroundZero nach 5 Minuten pruefen: Stages/Marker/Status.
6. CourierZ nach 7 Minuten pruefen: Aktenkoffer, Carrierstatus, Delivery, Reward.

## Offen fuer spaeter

Musik und Smoke/Fog erst in getrennten Testlaeufen mit neuen MaxRuntime-/Cooldown-Dokumentationen pruefen.
