
DeutschZ System Manager v0.4.1 MEMORY-COMMIT-PACKAGE
==============================================================

Start:
- Start_DZSM_v0_4_1_MEMORY_COMMIT_PACKAGE.bat doppelklicken.

Wichtigste Entscheidung:
- P:\Root ist DayZ Tools WorkDrive/Vanilla-Arbeitsbereich und Legacy-Mischbereich.
- P:\Root wird nicht gelöscht, nicht verschoben, nicht pauschal gesichert und nicht nach GitHub exportiert.
- Sauberer Projektstand ist:
  P:\GitHub_DeutschZModZ\DeutschZModZ
- ReadyMods ist Build-/PBO-Ausgabe, nicht GitHub-Quelle.

Standardstruktur:
- D:\DeutschZ_System_Manager\backups
- D:\DeutschZ_System_Manager\app
- D:\DeutschZ_System_Manager\docs
- D:\DeutschZ_System_Manager\DZSM_v0_1
- D:\DeutschZ_System_Manager\reports
- D:\DeutschZ_System_Manager\scripts
- D:\DeutschZ_System_Manager\Arbeitsstand aktuell.txt

Falls D:\ fehlt:
- dieselbe Struktur unter C:\DeutschZ_System_Manager

Reports:
- 00_ZUSAMMENFASSUNG.txt
- 17_SAFE_AUTO_BACKUP_LOG.txt
- 19_GITHUB_EXPORT_LOG.txt
- 21_GITHUB_SAFETY_DOCS_LOG.txt
- 22_P_ROOT_WORKDRIVE_NOTES.txt


Neu in v0.4.1 MEMORY-COMMIT-PACKAGE:
- LM Studio wird nur noch als optional/experimentell behandelt.
- C:\Users\patsl\.lmstudio wird NICHT automatisch gesichert.
- Lokale GGUF-Modelle werden NICHT nach GitHub exportiert.
- Bekannter Testpfad Qwen2.5-Coder-14B-Instruct-Q3_K_L.gguf wird nur dokumentiert, nicht kopiert.
- Neuer Bericht:
  23_LMSTUDIO_MODEL_POLICY.txt


Neu in v0.4.1 MEMORY-COMMIT-PACKAGE:
- Archiv-Fix:
  Alte DZSM-BAT/PS1/README/Config/ZIP/Restdateien im Arbeitsordner werden zuverlässiger erkannt.
  Sie werden nach DZSM_v0_1\_archive_old_versions verschoben, nicht gelöscht.
- Desktop-Verknüpfungen:
  Erstellt aktuelle Verknüpfung zur BAT:
  DeutschZ System Manager - Start.lnk
  Erstellt aktuelle Verknüpfung zur PS1:
  DeutschZ System Manager - Script PS1.lnk
  Entfernt alte DZSM-.lnk-Verknüpfungen vom Desktop.
  Echte Dateien werden nicht gelöscht.
- Neuer Bericht:
  24_DESKTOP_SHORTCUTS_LOG.txt


Neu in v0.4.1 MEMORY-COMMIT-PACKAGE:
- Desktop-Verknüpfungs-Fix:
  Die Benutzer-Verknüpfung
  DeutschZ_System_Manager - Verknüpfung.lnk
  wird geschützt und nicht gelöscht.
- Keine Wildcard-Löschung von Desktop-Links mehr.
- Es werden nur exakt bekannte DZSM-Auto-Verknüpfungen ersetzt:
  DeutschZ System Manager - Start.lnk
  DeutschZ System Manager - Script PS1.lnk
  DZSM - Start.lnk
  DZSM - Script PS1.lnk
- BugReport-Arbeitsordner:
  D:\DeutschZ_System_Manager\bugreports
  oder auf Fallback-PCs:
  C:\DeutschZ_System_Manager\bugreports
- Enthält:
  BUGREPORT_AKTUELL.md
  LOESUNGSWEGE_UND_VERMEIDUNG.md
  KNOWN_ISSUES.md
  offen/
  geloest/
  notizen/
  logs/
- Neuer Bericht:
  25_BUGREPORT_WORKSPACE_LOG.txt


Neu in v0.4.1 MEMORY-COMMIT-PACKAGE:
- Erstellt eigenen Upload-Ordner für ChatGPT:
  D:\DeutschZ_System_Manager\reports\_UPLOAD_FUER_CHATGPT
- Kopiert dort nur die wichtigen Analyse-/Fehlerdateien hinein.
- Erstellt optional ein ZIP:
  DZSM_UPLOAD_PACKAGE.zip
- Erstellt Desktop-Verknüpfung:
  DeutschZ System Manager - Upload Reports.lnk
- Erstellt zusätzlich Desktop-Verknüpfung:
  DeutschZ System Manager - Reports.lnk
- Nutzt eigene DZSM-Icons aus dem Ordner:
  icons
- Die Benutzer-Verknüpfung
  DeutschZ_System_Manager - Verknüpfung.lnk
  bleibt weiterhin geschützt.
- Neuer Bericht:
  26_UPLOAD_PACKAGE_LOG.txt


Neu in v0.4.1 MEMORY-COMMIT-PACKAGE:
- Alte roten Icons ersetzt.
- Neue Optik:
  - elegant
  - dark / graphite
  - neon-green
  - kein Rot
- Keine PS1-Desktop-Verknüpfung mehr im Normalmodus.
- Desktop bekommt nur:
  - DeutschZ System Manager - Start.lnk
  - DeutschZ System Manager - Upload Reports.lnk
  - DeutschZ System Manager - Reports.lnk
- Icons liegen unter:
  icons
- Vorschau:
  icons\DZSM_Icon_Preview.png


Neu in v0.4.1 MEMORY-COMMIT-PACKAGE:
- Neue eindeutige NeonGreen-v040 Icons gegen Windows Icon-Cache:
  icons\DZSM_Start_NeonGreen_v040.ico
  icons\DZSM_Upload_NeonGreen_v040.ico
  icons\DZSM_Reports_NeonGreen_v040.ico
  icons\DZSM_Build_NeonGreen_v040.ico
- Icons sind dark/graphite/neon-green, kein Rot.
- Desktop bekommt zusätzlich:
  DeutschZ Build Wrapper - Check.lnk
- Erstellt Build Wrapper unter:
  P:\GitHub_DeutschZModZ\DeutschZModZ\tools\build_wrapper
- Build Wrapper ist standardmäßig CheckOnly.
- Echter Build ist gesperrt, bis BUILD_CONFIG.json bewusst freigegeben wird.
- Neuer Bericht:
  27_BUILD_WRAPPER_LOG.txt


Neu in v0.4.1 MEMORY-COMMIT-PACKAGE:
- Erstellt ChatGPT-Erinnerungsdatei:
  D:\DeutschZ_System_Manager\memory\CHATGPT_ERINNERUNG_AKTUELL.md
- Erstellt Statusdatei:
  D:\DeutschZ_System_Manager\memory\MEMORY_STATUS.json
- Kopiert beide automatisch ins Uploadpaket:
  D:\DeutschZ_System_Manager\reports\_UPLOAD_FUER_CHATGPT
- Kennzeichnung:
  MEMORY_STATUS: AKTUALISIERT
  MEMORY_ACTION_FOR_CHATGPT: NEU_SPEICHERN_WENN_DIESER_STAND_FEHLT_ODER_ABWEICHT
- Erstellt Git Commit Helper:
  P:\GitHub_DeutschZModZ\DeutschZModZ\tools\git_commit_helper
- Erstellt Commit Message:
  DZSM_GIT_COMMIT_MESSAGE.txt
- Neuer Bericht:
  28_MEMORY_PACKAGE_LOG.txt
  29_GIT_COMMIT_HELPER_LOG.txt
