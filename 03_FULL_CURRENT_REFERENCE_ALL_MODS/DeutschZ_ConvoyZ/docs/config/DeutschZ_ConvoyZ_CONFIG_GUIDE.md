# DeutschZ_ConvoyZ Config Guide

## Pfad

`$profile:DeutschZ/ConvoyZ/Config/`

## Wichtige Bereiche

- EnableConvoyZEvent
- InitialStartDelayMinSeconds / MaxSeconds
- CrashObjects und Blackbox
- Hackdauer und Status
- AIWaves
- Rewards
- Marker / 3D Marker
- CleanupDelaySeconds

## Sichere Testwerte

- InitialStartDelayMinSeconds = 180
- InitialStartDelayMaxSeconds = 180
- UseEventMarker = 1
- UseEvent3DMarker = 1
- EnableAiWaves = 1 mit kleinen Wellen
- Smoke bleibt No-Op, nicht physisch aktivieren

## Empfohlene Livewerte

- Startdelay groesser setzen
- Hackzeit passend zur Serverpopulation setzen
- RewardClaimOnce aktiv lassen
- CleanupDelaySeconds nicht zu kurz setzen

## Nicht blind aktivieren

- physische Smoke-Grenades
- ungetestete Crashobjekt-Klassen
- sehr kurze Restart-Delays
