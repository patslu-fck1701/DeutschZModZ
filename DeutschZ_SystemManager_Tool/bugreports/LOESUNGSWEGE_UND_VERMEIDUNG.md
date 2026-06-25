# DZSM Loesungswege und Vermeidung

Dieses Dokument haelt fest, welche Fehler bereits passiert sind und wie sie kuenftig vermieden werden.

## Vermeidungsregeln

### Desktop-Verknuepfungen

Problem:
- Benutzerdefinierte Verknuepfungen duerfen nicht geloescht werden.

Regel:
- Keine Wildcard-Loeschung fuer Desktop-Links.
- Nur exakt bekannte DZSM-Auto-Verknuepfungen ersetzen.
- Die Verknuepfung DeutschZ_System_Manager - Verknuepfung.lnk bleibt immer erhalten.
- Echte Dateien werden niemals vom Desktop entfernt.

### Archivierung alter DZSM-Dateien

Problem:
- Alte Dateien koennen im Arbeitsordner liegen bleiben.

Regel:
- Alte DZSM-BAT/PS1/README/Config/ZIP/Restdateien werden archiviert.
- Ziel: DZSM_v0_1\_archive_old_versions
- Keine Loeschung.

### P:\Root

Problem:
- P:\Root enthaelt DayZ Tools WorkDrive/Vanilla-Daten und Legacy-Dateien.

Regel:
- P:\Root nicht loeschen.
- P:\Root nicht verschieben.
- P:\Root nicht pauschal sichern.
- P:\Root nicht nach GitHub exportieren.
- Sauberer Stand ist P:\GitHub_DeutschZModZ\DeutschZModZ.

### LM Studio

Problem:
- Lokales Modell laeuft noch nicht zuverlaessig.

Regel:
- .lmstudio und GGUF-Modelle nicht automatisch sichern/exportieren.
- Nur optional dokumentieren.

## Ziel

Jeder erkannte Fehler soll hier landen, damit zukuenftige DZSM-Versionen dieselben Fehler vermeiden.
