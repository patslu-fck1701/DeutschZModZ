# DeutschZ_GroundZero Release Checklist

- config.cpp lädt ohne Fehler.
- `$PBOPREFIX$` enthält exakt `DeutschZ_GroundZero`.
- `gameLibScriptModule` ist mit großem Lib geschrieben.
- Keine leeren Scriptmodul-Pfade.
- Keine Fremdmod-Reste: LBmaster, LBAdvancedGroups, MarkerBridge, MarkerBackend, SFKOTH, ExpansionEventAI.
- Keine direkten Expansion-Klassen im Kernsystem.
- Serverentscheidungen bleiben serverautoritär.
- Retry/Abort-RPCs verändern keinen kritischen Zustand ohne Serverprüfung.
- Cleanup ist mehrfach aufrufbar.
- Config Load/Repair/Validate/Save funktioniert.
- State Save/Backup/Repair/Reset funktioniert.
- FilePatching-Test bestanden.
- `-packonly` Build bestanden.
- Finaler AddonBuilder-Build bestanden.
- PBO signiert.
- BISIGN passt exakt zur PBO.
- Linux-Pfadprüfung bestanden.
- Test mit eigener Mod, CF, CF+Expansion, kompletter Ziel-Modliste bestanden.
