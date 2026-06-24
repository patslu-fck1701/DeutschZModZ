
# ChatGPT Erinnerung / Projektstand fuer Patrick / DeutschZ / DZSM

Stand: 2026-06-24
Version: DZSM v0.4.1 MEMORY-COMMIT-PACKAGE

## WICHTIGER HINWEIS FUER CHATGPT

MEMORY_STATUS: AKTUALISIERT
MEMORY_ACTION_FOR_CHATGPT: NEU_SPEICHERN_WENN_DIESER_STAND_FEHLT_ODER_ABWEICHT
USER_INTENT: Patrick will eventuell alte Chats loeschen. Diese Datei dient als uebertragbarer Projekt-/Erinnerungsstand.
SENSIBLE_DATEN: Keine Passwoerter, keine Keys, keine Secrets speichern.

Wenn diese Datei nach einem Chat-Reset hochgeladen wird:
1. Diesen Stand lesen.
2. Mit vorhandener Erinnerung vergleichen.
3. Fehlende oder abweichende Projektregeln neu speichern.
4. Nichts als Rechtsberatung ausgeben.
5. Nicht automatisch Workshopdateien veraendern.

---

## Nutzer / Arbeitsweise

Nutzer: Patrick Sluzalek
Projekt: DeutschZ DayZ Server / DeutschZModZ / DeutschZ System Manager
Arbeitsstil: schnell, direkt, praezise, lieber gezielt nachfragen als falsch arbeiten.
Sprache: Deutsch.
Wichtig: Keine Geheimdaten ausgeben oder speichern.

---

## DeutschZ Grundregeln

DeutschZ ist ein eigenes DayZ-Mod-Oekosystem.
Kein kopierter Fremdmod-Code, keine fremden Klassen/Configs/UI/Assets uebernehmen.

Verbotene Altlasten:
- LBmaster
- LBAdvancedGroups
- LBAdminTool
- SFKOTH
- BasicMap
- VPPAdmin
- AdvancedGroups
- MarkerBridge
- MarkerBackend
- ExpansionEventAI-Stubs
- SurvivorM_Mirek-Fallbacks

Wenn gefunden:
- dokumentieren
- nicht blind loeschen
- nur nach Auftrag entfernen/ersetzen

---

## Aktive DeutschZ Mods / Reihenfolge

1. DeutschZ_Core
2. DeutschZ_ExpansionBridge
3. DeutschZ_KotHZ
4. DeutschZ_ConvoyZ
5. DeutschZ_GroundZero
6. DeutschZ_CourierZ
7. DeutschZ_OperationDeutschZ

Core ist Pflichtbasis.
ExpansionBridge ist die einzige direkte Expansion-Schicht.
Eventmods duerfen nicht direkt voneinander abhaengen.
OperationDeutschZ darf spaeter als Orchestrator von den Eventmods abhaengen.

---

## Event-Regeln

Alle Events muessen ohne Expansion crashfrei laufen.
Fallback:
- keine Expansion Marker
- keine Expansion AI
- lokale Eventlogik
- Logging
- Vanilla-kompatibles Verhalten

Keine direkten Expansion Calls ausserhalb DeutschZ_ExpansionBridge.

Signalstation/Sendestation ist strikt getrennt von KotHZ/KOTH.
Green Mountain ist Trader/SafeZone und keine Eventlocation.
ConvoyZ und CourierZ nutzen verschiedene Orte.
GroundZero HUD/Statusbar nur im Eventradius, nicht global.

---

## M249-Regel

Nur Vanilla M249 und Mag_M249_Box200Rnd blocken/entfernen.
GCGNM249/GCGN_M249 und Zubehoer erlaubt lassen.
Niemals pauschal alle Klassen mit M249 loeschen.

---

## Workshop-Regel

SteamWorkshop_Beschreibungen / Workshopdateien NICHT automatisch aendern.
Nur aendern, wenn Patrick das ausdruecklich beauftragt.
Workshoptexte nur Deutsch, English, Russisch.
Supportlink: https://discord.gg/WM5GkDbw7C

---

## DZSM Zielstruktur

Standardpfad Haupt-PC:

D:\DeutschZ_System_Manager

Unterordner:
- backups
- app
- docs
- DZSM_v0_1
- reports
- scripts
- bugreports
- memory
- reports\_UPLOAD_FUER_CHATGPT
- Arbeitsstand aktuell.txt

Fallback ohne D:\:
C:\DeutschZ_System_Manager

Backups liegen unter:
D:\DeutschZ_System_Manager\backups

Reports liegen unter:
D:\DeutschZ_System_Manager\reports

DZSM Arbeits-/Versionsordner:
D:\DeutschZ_System_Manager\DZSM_v0_1

Alte DZSM-Versionen:
D:\DeutschZ_System_Manager\DZSM_v0_1\_archive_old_versions

---

## P:\ Regeln

P:\ ist virtuelles Arbeitslaufwerk / DayZ Tools WorkDrive.
P:\ darf niemals Backup-Ziel sein.

P:\Root ist DayZ Tools WorkDrive / Vanilla-Arbeitsbereich + Legacy-Mischbereich.
Dort liegen z.B.:
- bin
- Core
- DZ
- graphics
- gui
- languagecore
- scripts
- system
- Worlds/DayZ Tools Dateien
- alte Legacy-/Fremdmod-Dateien

Diese Daten:
- nicht loeschen
- nicht verschieben
- nicht pauschal sichern
- nicht nach GitHub exportieren

Sauberer Projektstand:
P:\GitHub_DeutschZModZ\DeutschZModZ

ReadyMods:
P:\ReadyMods
= Build-/PBO-Ausgabe, nicht GitHub-Quelle.

---

## DZSM GitHub Export

Tool-Export:
P:\GitHub_DeutschZModZ\DeutschZModZ\DeutschZ_SystemManager_Tool

Tool-Dokumentation:
P:\GitHub_DeutschZModZ\DeutschZModZ\DeutschZ_SystemManager_Tool_Dokumentation

Build Wrapper:
P:\GitHub_DeutschZModZ\DeutschZModZ\tools\build_wrapper

GitHub-Export ist Whitelist-basiert.
Nicht exportieren:
- backups
- reports
- private Daten
- LM Studio Modelle
- P:\Root
- ReadyMods/PBOs
- Logs blind
- Secrets/Keys

---

## LM Studio Regel

LM Studio ist optional/experimentell.
Aktueller Modellpfad:
C:\Users\patsl\.lmstudio\models\lmstudio-community\Qwen2.5-Coder-14B-Instruct-GGUF\Qwen2.5-Coder-14B-Instruct-Q3_K_L.gguf

Das Modell funktioniert noch nicht zuverlaessig.
.lmstudio und lokale GGUF-Modelle:
- nicht automatisch sichern
- nicht nach GitHub exportieren
- nur optional dokumentieren

---

## Desktop-Verknuepfungen

Benutzerdefinierte Verknuepfung schuetzen:
DeutschZ_System_Manager - Verknuepfung.lnk

Diese darf NICHT geloescht werden.

DZSM darf nur exakt eigene Auto-Links ersetzen:
- DeutschZ System Manager - Start.lnk
- DeutschZ System Manager - Upload Reports.lnk
- DeutschZ System Manager - Reports.lnk
- DeutschZ Build Wrapper - Check.lnk
- DZSM - Start.lnk
- DZSM - Script PS1.lnk
- DZSM - Upload Reports.lnk

Keine Wildcard-Loeschung.
Keine echten Desktop-Dateien loeschen.

---

## BugReport-Regel

DZSM erzeugt:
D:\DeutschZ_System_Manager\bugreports

Darin:
- BUGREPORT_AKTUELL.md
- LOESUNGSWEGE_UND_VERMEIDUNG.md
- KNOWN_ISSUES.md
- offen
- geloest
- notizen
- logs

Ziel:
Fehler, Loesungswege und Vermeidungsregeln dokumentieren, damit sie beim naechsten Lauf beruecksichtigt werden.

---

## Uploadpaket fuer ChatGPT

DZSM erzeugt:
D:\DeutschZ_System_Manager\reports\_UPLOAD_FUER_CHATGPT

Darin sollen immer die wichtigsten Dateien fuer ChatGPT liegen:
- 00_ZUSAMMENFASSUNG.txt
- 16_DZSM_SELF_CLEANUP.txt
- 17_SAFE_AUTO_BACKUP_LOG.txt
- 18_DZSM_STANDARD_STRUCTURE.txt
- 19_GITHUB_EXPORT_LOG.txt
- 21_GITHUB_SAFETY_DOCS_LOG.txt
- 22_P_ROOT_WORKDRIVE_NOTES.txt
- 23_LMSTUDIO_MODEL_POLICY.txt
- 24_DESKTOP_SHORTCUTS_LOG.txt
- 25_BUGREPORT_WORKSPACE_LOG.txt
- 26_UPLOAD_PACKAGE_LOG.txt
- 27_BUILD_WRAPPER_LOG.txt
- 28_MEMORY_PACKAGE_LOG.txt
- 29_GIT_COMMIT_HELPER_LOG.txt
- 11_DEUTSCHZ_STRUCTURE_CHECK.txt
- 99_NAECHSTE_SCHRITTE.txt
- CHATGPT_ERINNERUNG_AKTUELL.md
- MEMORY_STATUS.json
- DZSM_GIT_COMMIT_MESSAGE.txt

Wenn Patrick fragt "weiter", nach Uploadpaket fragen und diese Dateien auswerten.

---

## Build Wrapper Regeln

Build Wrapper Pfad:
P:\GitHub_DeutschZModZ\DeutschZModZ\tools\build_wrapper

Standardmodus:
CheckOnly

Echter Build ist gesperrt, bis BUILD_CONFIG.json bewusst freigegeben wird:
"allow_real_build": true

Wrapper soll pruefen:
- P:\ readiness
- DayZ Tools / Vanilla WorkDrive Elemente
- AddonBuilder
- sauberen Repo-Pfad
- aktive Mod-Reihenfolge
- ReadyMods Schutz
- Workshopdateien nicht anfassen
- keine P:\Root-Aufraeumaktion

---

## Git / Commit Regel

Patrick will GitHub Repo hochladen/committen.
DZSM soll Commit-Helfer erzeugen:
P:\GitHub_DeutschZModZ\DeutschZModZ\tools\git_commit_helper

Commit-Helfer darf:
- git status zeigen
- Commit-Text bereitstellen
- optional manuell committen

Nicht automatisch pushen ohne bewusste Aktion.

Empfohlene Commit Message:
chore(dzsm): add system manager, safety docs, upload package and build wrapper

---

## Aktuelle naechste Schritte

1. DZSM v0.4.1 laufen lassen.
2. Uploadpaket pruefen:
   D:\DeutschZ_System_Manager\reports\_UPLOAD_FUER_CHATGPT
3. GitHub-Commit-Helfer pruefen.
4. Repo committen.
5. Nach Chat-Loeschung Uploadpaket hochladen.
6. ChatGPT soll CHATGPT_ERINNERUNG_AKTUELL.md lesen und Memory neu speichern, falls noetig.

