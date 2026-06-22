# DeutschZ_CourierZ - FIX32 Compile Audit

## Anlass

Server compile crash:

```txt
Can't compile "Game" script module!
DeutschZ_CourierZ/scripts/3_Game/courierzpersistence.c(31): Variable 'state' is not strong ref (missing 'ref'?) !
```

## Ursache

`SaveState(CourierZState state)` hat im Fehlerfall direkt `state = new CourierZState;` gesetzt.
In DayZ/Enforce Script ist dieser Funktionsparameter keine starke `ref`-Variable. Das fuehrt beim Zuweisen eines neuen Objekts zum Game-Script-Compilefehler.

## Fix

- `LoadState()` nutzt jetzt eine starke lokale `ref CourierZState state`.
- `SaveState()` weist dem schwachen Parameter kein neues Objekt mehr zu.
- Falls `SaveState()` ohne State aufgerufen wird, wird eine lokale starke `ref CourierZState emptyState` erzeugt und gespeichert.
- `CourierZConfig.Load()` nutzt jetzt ebenfalls eine starke lokale `ref CourierZConfig cfg`.

## Regression Check

Geprueft gegen unsere bisherige Fehlerliste:

- PlayerBase nur in `scripts/4_World`: OK
- MissionServer nur in `scripts/5_Mission`: OK
- keine direkten Expansion Calls in CourierZ: OK
- Marker/Notify laufen nur ueber DeutschZ_Core/DeutschZ_ExpansionBridge: OK
- keine verbotenen Legacy-Namen: OK
- Fallback-Gegnerklasse bleibt `ZmbM_usSoldier_Officer_Desert`: OK
- CourierZ Start bleibt zeitversetzt bei 1200 Sekunden: OK
- CourierZ Credits/Workshoplink bleiben unveraendert: OK

## Geaenderte Mod

Nur `DeutschZ_CourierZ` wurde geaendert.

## Build-Hinweis

Nur diese Mod neu packen/signieren:

```txt
@DeutschZ_CourierZ
```
