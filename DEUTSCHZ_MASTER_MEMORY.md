# DEUTSCHZ MASTER MEMORY (JUNI 2026)

## Eigentümer

Projekt:
DeutschZ

Eigentümer:
Patrick Sluzalek (fck1701)

Server:
DeutschZ DayZ Server

GitHub:
https://github.com/patslu-fck1701/DeutschZModZ

---

# GRUNDSATZ

DeutschZ wird als vollständiges eigenes Mod-Ökosystem entwickelt.

Ziel:

* eigene Systeme
* eigene Architektur
* eigene Klassen
* eigene Configs
* eigene Persistenz
* eigene APIs

Keine Abhängigkeit von fremden Gameplay-Mods.

Erlaubt:

* DayZ
* Community Framework
* DayZ Expansion APIs

Nicht erlaubt:

* kopierter Code
* kopierte Klassen
* kopierte Config-Strukturen
* kopierte UI
* kopierte Assets

---

# VERBOTENE ALTLASTEN

Diese Namen dürfen nicht mehr im Projekt auftauchen:

LBmaster

LBAdvancedGroups

LBAdminTool

SFKOTH

BasicMap

VPPAdmin

AdvancedGroups

MarkerBridge

MarkerBackend

ExpansionEventAI Stubs

SurvivorM_Mirek Fallbacks

Wenn gefunden:

prüfen
dokumentieren
entfernen oder ersetzen

---

# DEUTSCHZ MOD REIHENFOLGE

1 DeutschZ_Core

2 DeutschZ_ExpansionBridge

3 DeutschZ_Banking

4 DeutschZ_Garage

5 DeutschZ_Groups

6 DeutschZ_TraderZ

7 DeutschZ_BattlepassZ

8 DeutschZ_SpawnSelectZ

9 DeutschZ_KotHZ

10 DeutschZ_ConvoyZ

11 DeutschZ_GroundZero

12 DeutschZ_Tools

---

# AKTUELLE PRIORITÄT

Aktuell aktiv:

DeutschZ_Core

DeutschZ_ExpansionBridge

DeutschZ_KotHZ

DeutschZ_ConvoyZ

DeutschZ_GroundZero

Alles andere hat aktuell niedrigere Priorität.

---

# CORE

DeutschZ_Core ist Pflicht.

Aufgaben:

* Logging
* JSON
* Save
* Backup
* Recovery
* EventBus
* ServiceLocator
* ProviderRegistry
* RateLimiter
* ConfigValidation
* ProfilePaths

Pfad:

$profile:DeutschZ/

---

# EXPANSION BRIDGE

DeutschZ_ExpansionBridge ist die einzige direkte Expansion-Schicht.

Verantwortlich für:

* Marker
* AI
* Notifications
* Map

Alle anderen Mods sprechen nur die Core APIs an.

Keine direkten Expansion Calls in Event Mods.

---

# EVENT REGEL

Alle Events müssen später OHNE Expansion lauffähig sein.

Pflicht:

DeutschZ_Core

Optional:

DeutschZ_ExpansionBridge

Optional:

DayZ Expansion

Wenn Expansion fehlt:

Event darf nicht crashen.

Fallback:

* keine Expansion Marker
* keine Expansion AI
* lokale Eventlogik
* Logging
* Vanilla-kompatibles Verhalten

---

# AKTUELLE EVENTS

## DeutschZ_KotHZ

Infected Siege

Features:

* Capture System
* Infected Waves
* Rewards
* Marker über Bridge
* Logging
* Cleanup

Workshop:

https://steamcommunity.com/sharedfiles/filedetails/?id=3746385283

---

## DeutschZ_ConvoyZ

Features:

* Convoy Event
* Spawn System
* Wave System
* Rewards
* Cleanup

Workshop:

https://steamcommunity.com/sharedfiles/filedetails/?id=3745946832

---

## DeutschZ_GroundZero

Aktueller Neubau.

Status:

Frühe Testphase.

Aktuelle bekannte Baustelle:

Scriptmodul-Trennung.

Workshop:

https://steamcommunity.com/sharedfiles/filedetails/?id=3748422786

---

# CORE WORKSHOP

https://steamcommunity.com/sharedfiles/filedetails/?id=3748421029

---

# EXPANSION BRIDGE WORKSHOP

https://steamcommunity.com/sharedfiles/filedetails/?id=3748421850

---

# REPOSITORY STRUKTUR

Source:

P:\GitHub_DeutschZModZ\DeutschZModZ\mods

Repository:

P:\GitHub_DeutschZModZ\DeutschZModZ

ReadyMods:

P:\ReadyMods

Workshopbeschreibungen:

P:\SteamWorkshop_Beschreibungen

---

# MOD.CPP REGEL

Jede Änderung prüft:

mod.cpp

Workshop Beschreibung

Upload Files

Changelog

Alles muss denselben Stand besitzen.

---

# TYPES.XML REGEL

Events spawnen nicht automatisch.

Standard:

nominal="0"

Verwendung:

* Event Loot
* Trader
* Admin Spawn

Kein normales Mapspawn.

---

# COMPLIANCE DATEIEN

Jede Mod enthält:

README.md

CHANGELOG.md

NO_COPY_AUDIT.md

SOURCE_PROVENANCE.md

PUBLIC_SOURCE_REGISTER.md

OPEN_ASSUMPTIONS.md

README_COMPLIANCE.md

---

# SAFE BOOT STANDARD

Vor jedem Release prüfen:

Modname

PBOPREFIX

config.cpp

CfgMods

CfgPatches

requiredAddons

Scriptmodule

Save

Load

RPC Sicherheit

Logging

Restart

Storage

Keine neuen Features bevor Safe Boot bestanden wurde.

---

# CODEx REGELN

Arbeitsordner:

P:\GitHub_DeutschZModZ\DeutschZModZ\mods

Darf:

* Dateien ändern
* Source erweitern
* Changelogs schreiben
* Workshopbeschreibungen aktualisieren
* mod.cpp aktualisieren
* ReadyMods aktualisieren
* Addon Builder nutzen
* PBOs bauen

Darf NICHT:

* fremden Code kopieren
* Fremdmod-Reste einbauen
* APIs raten
* geheime Daten speichern

---

# WORKSHOP BILDER

DeutschZ Stil:

* Schwarz
* Dunkelgrau
* Rot
* Militärisch
* Postapokalyptisch
* DeutschZ Logo
* Großes rotes Z
* GitHub Link
* Workshop Abhängigkeiten
* Technische Feature Darstellung

---

# SERVER PHILOSOPHIE

Einfacher Einstieg.

Starkes Endgame.

Große Events.

Serverautoritär.

Persistenz.

Keine Dupe Exploits.

Keine Client Autorität.

Saubere Architektur.

---

# AKTUELLER STATUS

DeutschZ_Core:
Testphase

DeutschZ_ExpansionBridge:
Testphase

DeutschZ_KotHZ:
Erste Testphase

DeutschZ_ConvoyZ:
Erste Testphase

DeutschZ_GroundZero:
Aktive Fehlerbehebung

Status Gesamt:

Projekt befindet sich aktuell in der technischen Test- und Stabilisierungsphase.

Ablageort Master Memory: P:\GitHub_DeutschZModZ\DeutschZModZ