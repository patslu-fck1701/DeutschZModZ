# DeutschZ_GroundZero Config Guide

## Pfad

`$profile:DeutschZ/GroundZero/`

## Wichtige Bereiche

- EnableGroundZero
- AutoStartEnabled
- AutoStartMinDelaySeconds / MaxDelaySeconds
- Stages und Objectives
- Markers / Notifications
- Zombies / FinalWaves
- Rewards
- Cleanup

## Sichere Testwerte

- AutoStartMinDelaySeconds = 300
- AutoStartMaxDelaySeconds = 300
- Marker und Notifications aktiv
- FinalWaves klein halten
- DebugLogs nur fuer Tests aktiv lassen

## Empfohlene Livewerte

- Startdelay groesser setzen
- Stage-Ziele klar platzieren
- RewardItemClass nur aus vorhandenen GroundZero-Klassen waehlen
- ZombieCount langsam skalieren

## Nicht blind aktivieren

- ungetestete ExpansionAI/Faction-Optionen
- zu viele FinalWaves
- zu kurze Cleanup-Zeiten
