# EVENTS_CORE_BRIDGE_STATUS

Stand: 2026-06-20

## Bearbeitete Module

- DeutschZ_Core
- DeutschZ_ExpansionBridge
- DeutschZ_KotHZ
- DeutschZ_ConvoyZ
- DeutschZ_GroundZero

## Durchgefuehrt

- Aktuelle `mods.zip` entpackt und Source-Struktur statisch geprueft.
- Fehlendes `DeutschZ_ExpansionBridge/scripts/3_Game` Modul mit eigenem sicheren Platzhalter ergaenzt, damit der in `config.cpp` deklarierte Scriptpfad existiert.
- `DeutschZ_ExpansionBridge` von geratenen direkten Expansion-CfgPatches entkoppelt. Aktuell wird nur `DeutschZ_Core` hart vorausgesetzt; echte Expansion-API-Aufrufe bleiben bewusst hinter Provider/TODO, bis die Zielversion geprueft ist.
- `mod.cpp` Overviews/Versionen fuer Core, Bridge und Events aktualisiert.
- SteamWorkshop-Beschreibungen fuer alle 5 Module erstellt.
- Config-Beschreibungen je Mod erstellt.
- `types.xml` Templates erstellt:
  - Core/Bridge: keine Economy-Spawns noetig.
  - KotHZ/ConvoyZ/GroundZero: Event-Items mit `nominal=0`, damit sie nicht zufaellig auf der Map spawnen.
- ReadyMods/files-Textdateien als Vorlagen erzeugt.

## Statischer Compliance-Check

Aktive Source-Dateien wurden auf alte Fremdmod-Reste geprueft. Treffer befinden sich nur in Dokumentations-/Audittexten als Negativliste oder Historie, nicht als aktive Bridge-/Fremdmod-Implementierung.

Gesuchte Begriffe:
LBmaster, LBAdvancedGroups, LBAdminTool, SFKOTH, BasicMap, VPPAdmin, COT, AdvancedGroups, MarkerBridge, MarkerBackend, ExpansionEventAI, SurvivorM_Mirek.

## Types.xml Entscheidung

- Core: keine types.xml erforderlich.
- ExpansionBridge: keine types.xml erforderlich.
- KotHZ: types.xml nur optionales Event-/Trader-Template, `nominal=0`.
- ConvoyZ: types.xml nur optionales Event-/Trader-Template, `nominal=0`.
- GroundZero: types.xml nur optionales Event-/Trader-Template, `nominal=0`.

Empfehlung: Diese types.xml-Dateien NICHT blind in die Economy aktivieren, ausser du willst die Event-Items bewusst fuer Trader/Admin/Economy registrieren. Fuer normalen Mapspawn bleiben sie auf `nominal=0`.

## Teststatus

Testbereit fuer den ersten manuellen Dedicated-Server-Compile-/Starttest: BEDINGT JA.

Nicht live-bestaetigt:
- Kein PBO gebaut.
- Kein AddonBuilder gestartet.
- Kein lokaler Dedicated-Server-Test durchgefuehrt.
- Keine echte Expansion-AI-/Marker-API aktiviert, weil keine Ziel-API geraten werden soll.

## Vor dem Test laden

Empfohlene Reihenfolge:
1. DeutschZ_Core
2. DeutschZ_ExpansionBridge
3. DeutschZ_KotHZ
4. DeutschZ_ConvoyZ
5. DeutschZ_GroundZero

## Beim ersten Test pruefen

- Script-Compile auf Serverstart.
- RPT auf `Unknown type`, `Cannot compile`, `requiredAddons` und Pfadfehler.
- Werden `$profile:DeutschZ/` und Unterordner erzeugt?
- Werden Event-Configs erzeugt/geladen?
- Startet jedes Event einzeln ohne die anderen Events?
- Cleanup nach Eventende/Abbruch.
- Restart nach erzeugten Event-Objekten.
