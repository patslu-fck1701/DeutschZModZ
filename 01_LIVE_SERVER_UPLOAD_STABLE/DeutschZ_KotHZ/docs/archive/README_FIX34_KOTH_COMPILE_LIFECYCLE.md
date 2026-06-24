# FIX34 - DeutschZ_KotHZ Compile/Lifecycle Audit

## Grund

Der Server stoppte im Mission-Script-Compile mit:

```txt
DeutschZ_KotHZ/scripts/5_Mission/deutschz_kothz/deutschzkothzmanager.c(192): Undefined function 'DeutschZKotHZManager.HasEnoughPlayers'
```

Beim erneuten Check wurden weitere Folgeaufrufe aus der KotHZ-Lifecycle-Kette abgesichert.

## Geändert

- `HasEnoughPlayers()` wiederhergestellt.
- `CountPlayersInZone()` wiederhergestellt.
- `FindSingleHolderInZone()` wiederhergestellt.
- `FinishEvent()` wiederhergestellt.
- `StopEvent()` wiederhergestellt.
- `SpawnZoneDecorations()` als sichere No-Op-Kompatibilitaetsmethode wiederhergestellt.
- `GiveRewardsDirect()` wiederhergestellt.
- `GetRemainingZombieSlots()` wiederhergestellt.
- Physische Smoke-/Particle-Smoke-Objekte bleiben deaktiviert.
- Militaer-Infected-Fallback auf `ZmbM_usSoldier_Officer_Desert` vereinheitlicht.

## Bewusst nicht reaktiviert

- KotHZ Musik.
- Riskante RuntimeFlagpole-Attachment-Kette.
- Physische Marker-Fallbackobjekte.
- Physische Smoke-Grenade-Statusanzeige.

## Test

Nur `DeutschZ_KotHZ` neu packen/signieren und Server starten.

Erwartung:

- Mission-Modul kompiliert weiter.
- KotHZ startet nach Zeitplan.
- Flagge bleibt sichtbar ueber den Safe-Flag-Pfad.
- Marker laufen ueber ExpansionBridge/ExpansionMarker.
- Kein Smoke-/Musik-Crashpfad aktiv.
