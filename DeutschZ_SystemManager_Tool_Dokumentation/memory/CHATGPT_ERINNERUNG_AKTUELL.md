# ChatGPT Erinnerung / Projektstand fuer Patrick / DeutschZ / DZSM

Stand: 2026-06-24
Version: DZSM v0.4.4 GIT-MERGE-DIAGNOSTICS

MEMORY_STATUS: AKTUALISIERT
MEMORY_ACTION_FOR_CHATGPT: NEU_SPEICHERN_WENN_DIESER_STAND_FEHLT_ODER_ABWEICHT
USER_INTENT: Patrick will eventuell alte Chats loeschen. Diese Datei dient als uebertragbarer Projekt-/Erinnerungsstand.
SENSIBLE_DATEN: Keine Passwoerter, keine Keys, keine Secrets speichern.

## Wichtigste Regeln

- Sprache: Deutsch.
- Patrick will schnelle, direkte, praezise Arbeit.
- DeutschZ ist ein eigenes DayZ-Mod-Oekosystem.
- Keine fremden Mod-Codes, Klassen, Configs, UI oder Assets kopieren.
- Workshopdateien/SteamWorkshop_Beschreibungen nicht automatisch aendern.
- P:\Root ist DayZ Tools WorkDrive/Vanilla-Arbeitsbereich + Legacy-Mischbereich.
- Sauberer Projektstand: P:\GitHub_DeutschZModZ\DeutschZModZ
- ReadyMods ist Build-/PBO-Ausgabe, nicht GitHub-Quelle.
- P:\ niemals Backup-Ziel.
- LM Studio/.lmstudio/GGUF-Modelle nicht automatisch sichern/exportieren.
- Benutzer-Verknuepfung DeutschZ_System_Manager - Verknuepfung.lnk nicht loeschen.
- Nur exakt bekannte DZSM-Auto-Verknuepfungen ersetzen.
- Core Pflicht, ExpansionBridge einzige direkte Expansion-Schicht.
- Aktive Mods/Reihenfolge:
  1. DeutschZ_Core
  2. DeutschZ_ExpansionBridge
  3. DeutschZ_KotHZ
  4. DeutschZ_ConvoyZ
  5. DeutschZ_GroundZero
  6. DeutschZ_CourierZ
  7. DeutschZ_OperationDeutschZ
- Eventmods duerfen untereinander nicht abhaengen; OperationDeutschZ darf spaeter orchestrieren.
- Alle Events muessen ohne Expansion crashfrei laufen.
- Signalstation/Sendestation strikt von KotHZ trennen.
- Green Mountain ist Trader/SafeZone und keine Eventlocation.
- M249-Regel: nur Vanilla M249 und Mag_M249_Box200Rnd blocken; GCGNM249/GCGN_M249 erlauben.
- DZSM Standardstruktur:
  D:\DeutschZ_System_Manager\backups
  D:\DeutschZ_System_Manager\app
  D:\DeutschZ_System_Manager\docs
  D:\DeutschZ_System_Manager\DZSM_v0_1
  D:\DeutschZ_System_Manager\reports
  D:\DeutschZ_System_Manager\scripts
  D:\DeutschZ_System_Manager\bugreports
  D:\DeutschZ_System_Manager\memory
  D:\DeutschZ_System_Manager\reports\_UPLOAD_FUER_CHATGPT
- Build Wrapper:
  P:\GitHub_DeutschZModZ\DeutschZModZ\tools\build_wrapper
  Standard: CheckOnly, echter Build gesperrt bis allow_real_build bewusst true ist.
- Git Commit Helper:
  P:\GitHub_DeutschZModZ\DeutschZModZ\tools\git_commit_helper
  Kein automatischer Push.

