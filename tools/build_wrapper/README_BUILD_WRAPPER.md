# DeutschZ Build Wrapper

Pfad:

`	ext
P:\GitHub_DeutschZModZ\DeutschZModZ\tools\build_wrapper
`

## Zweck

Der Build Wrapper ist die zentrale, sichere Build-Vorbereitung fuer DeutschZModZ.

Er prueft:

- P:\ readiness
- DayZ Tools / Vanilla WorkDrive Elemente
- AddonBuilder-Erkennung
- sauberen Repo-Pfad
- aktive Mod-Reihenfolge
- ReadyMods als Build-/PBO-Ausgabe
- Schutz vor Workshop-Datei-Aenderungen
- Schutz vor P:\Root-Aufraeumfehlern

## Standardmodus

Standard ist **CheckOnly**.

`	ext
DeutschZ_Build_Wrapper_CheckOnly.bat
`

Dieser Modus baut keine PBOs.

## Echter Build

Echter Build ist absichtlich gesperrt, bis BUILD_CONFIG.json bewusst angepasst wird:

`json
"allow_real_build": true
`

Danach muss der echte Build gezielt mit -Build gestartet werden.

## Sicherheitsregeln

- Keine Workshopdateien aendern.
- P:\Root nicht loeschen.
- P:\Root nicht verschieben.
- Keine Legacy-Dateien automatisch entfernen.
- ReadyMods nicht blind ueberschreiben.
- Keine Eventmod-Abhaengigkeiten untereinander.
- ExpansionBridge bleibt einzige direkte Expansion-Schicht.

## Aktive Reihenfolge

1. DeutschZ_Core
2. DeutschZ_ExpansionBridge
3. DeutschZ_KotHZ
4. DeutschZ_ConvoyZ
5. DeutschZ_GroundZero
6. DeutschZ_CourierZ
7. DeutschZ_OperationDeutschZ
