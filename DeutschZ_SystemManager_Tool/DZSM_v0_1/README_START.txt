DeutschZ System Manager
=======================
Aktuelle Version:
v0.7.9 FIX36 OUTPUT ARCHIVE WEBHOOK CHOICE REPAIR

Start:
DZSM_v_0_7_9.bat

Regeln:
- Kurze Dateinamen, alte DZSM-Dateien werden archiviert.
- Desktop-Link Analyse Starten zeigt auf aktuelle BAT.
- Desktop Datei Ausgabe wird vor jedem Start als kategorisiertes ZIP archiviert.
- Neue Datei Ausgabe wird nach Kategorien erzeugt.
- Types- und Fahrzeugspawn-Auswahl wartet aktiv auf Tastendruck.
- Webhook wird lokal aus ServerToolSettings\webhooks.txt gelesen, gecheckt und Status wird gesendet.
- Webhooks/Passwoerter/Tokens werden nicht ins Uploadpaket geschrieben.
- Kein Git commit/push/reset/clean, kein Build, kein Live-Write.

Repo-Source aktuell/read-only: P:\GitHub_DeutschZModZ\DeutschZModZ\DeutschZModZ

FIX37: Auswahl jetzt per Read-Host + ENTER statt choice.exe. Unter DONE wird eine gruene Zusammenfassung angezeigt. Webhook wird aus ToolDir oder Desktop-Kopie gelesen.
