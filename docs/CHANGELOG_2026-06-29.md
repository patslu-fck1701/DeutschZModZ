# DeutschZModZ Changelog

**Stand:** 2026-06-29 15:20 Europe/Berlin

## KotHZ

- `DeutschZ_KotHZ` serverseitig frueher initialisiert.
- `MissionServer` ruft den KotHZ-Manager jetzt im Konstruktor sicher auf und behaelt `OnInit`, `OnMissionStart` und `ClientReady` als Fallbacks.
- Lokaler Server hat `$profile:KotHZ/DZ_KotHZ_Config.json` erzeugt.
- `DebugMode` ist in der erzeugten Config enthalten.
- Nachweis im Testlog: `[DeutschZ][KotHZ][INFO] Config geladen.` und `Manager initialisiert.`
- Default reward profile enthaelt aktuell:
  - `BandageDressing` x2
  - `TacticalBaconCan` x2
- Keine Reward-Economy-Erweiterung in dieser Iteration.

## GroundZero

- Notification-Spam gedrosselt.
- Doppelte Statusmeldungen werden pro Nachricht gecooldowned.
- Fortschritts-Broadcasts verwenden jetzt das konfigurierte Statusintervall statt hart alle 10 Sekunden.
- Event-/HUD-Logik wurde nicht ersetzt, nur Chat-/Notification-Spam begrenzt.
- Lokaler Server bootstrapped GroundZero sauber:
  - Config Version 6 geladen
  - Persistence geladen
  - Core initialisiert

## NoxZ Phone / ATM / Market / Marker

- Falscher Phone-Shop-Eintrag `MBM_DodgeRam` entfernt.
- Sichere DodgeRam-Varianten bleiben vorhanden und wurden vom NoxZ-Healthcheck als OK bestaetigt.
- Bitcoin-Exchange deaktiviert, weil kein geladener echter `Bitcoin`-CfgVehicles-Classname nachweisbar war.
- `Exchange.json` hat aktuell `Rates: []`.
- Bitcoin wurde aus den ATM-Waehrungen entfernt.
- Drei Phone-ATMs wurden an den angeforderten Positionen eingetragen.
- NoxZ ServerMarkers wurden fuer die drei ATMs, SchwarzHandel und AirCraft's eingetragen.
- Phone-Server-3D-Marker wurden aktiviert.
- Letzter NoxZ-Healthcheck: `errors=0 | warnings=0 | OK`.

## Expansion Objects / mapgrouppos

- Desktop-Ordner `C:\Users\patsl\Desktop\Expansion Objekt Maps` wurde lokal in die Servermission eingepflegt.
- 14 `.map` Dateien wurden nach `expansion\objects` kopiert/aktualisiert.
- `mapgrouppos.xml` wurde gesichert und erweitert.
- Vorher: 11680 Gruppen.
- Neu hinzugefuegt: 4602 deduplizierte Gruppen.
- Nachher: 16282 Gruppen.
- XML wurde nach dem Merge validiert.
- `new_Zombis_territory.xml` wurde bewusst nicht importiert, weil Root `territory` statt MapGroupPos-Struktur.

## Expansion AI

- Eine neue Patrol `DeutschZ Blackmarket Guards` wurde in `AIPatrolSettings.json` eingetragen.
- 2 AI, vorhandenes `BanditLoadout`, `Faction: West`, moderate Accuracy `0.25-0.45`.
- Respawn: 1800 Sekunden, um Instant-Farming zu vermeiden.
- Wegpunkte liegen ca. 100-150 m um den Blackmarket-Bereich.
- Kein High-End-Loadout und kein Massen-Spawn.

## Build / Deploy

- `DeutschZ_KotHZ.pbo` neu gepackt, signiert und in Ready-/Server-Bundle uebernommen.
- `DeutschZ_GroundZero.pbo` wurde nach dem Notification-Fix gepackt/signiert/deployed.
- Keine privaten Keys wurden in den Output kopiert.

## Nicht abgeschlossen

- Kein kompletter `types.xml` Balancing-Pass.
- Kein Aircraft-Preis-Rewrite.
- Rewardchest nicht implementiert.
- Bitcoin Exchange nicht reaktiviert.
- Client-/Ingame-Test steht noch aus.
