# DeutschZModZ

Eigenes DayZ-Serverpack/Mod-Repository fuer DeutschZ.

Dieses Repository ist als saubere Source-Basis aufgebaut. Jede Mod liegt als eigenes Source-Modul unter `mods/`. Release-Ordner, PBOs, Keys und Signaturen werden nicht im Source-Baum vermischt.

## Module

1. DeutschZ_Core
2. DeutschZ_ExpansionBridge
3. DeutschZ_Banking
4. DeutschZ_Garage
5. DeutschZ_Groups
6. DeutschZ_TraderZ
7. DeutschZ_BattlepassZ
8. DeutschZ_SpawnSelectZ
9. DeutschZ_KotHZ
10. DeutschZ_ConvoyZ
11. DeutschZ_Tools

## Regeln

- Keine kopierten Fremdmod-Dateien.
- DayZ, CF und Expansion nur ueber eigene Adapter/API-Schichten verwenden.
- Server-autoritative Logik.
- Persistenz unter `$profile:DeutschZ/<System>/`.
- Configs validieren, reparieren und sicher speichern.


## Aktuell integrierte Source-Module

Die aktuellen Source-Dateien wurden unter `mods/` integriert. Details siehe `SOURCE_IMPORT_REPORT.md`.
