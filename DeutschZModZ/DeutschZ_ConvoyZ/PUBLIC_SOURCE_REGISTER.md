# PUBLIC_SOURCE_REGISTER.md

| Quelle/API | Nutzung | Code kopiert? | Status |
|---|---|---:|---|
| DayZ Script/API | Basisklassen, JSON, Inventar, Spawns, Serverfunktionen | Nein | erlaubte API-Nutzung |
| Community Framework | Laufzeitumgebung, falls geladen | Nein | Dependency, keine Source-Uebernahme |
| DayZ Expansion public scripts/wiki | CfgPatches-, requiredAddons-, Klassen-, Signatur- und API-Pruefung fuer Navigation, Notifications und AI | Nein | API-/Referenznutzung; kein Code, keine Layouts, keine Assets, keine Kommentare und keine Lizenztexte kopiert |

## Eigene DeutschZ-Klassen

- Land_HACKEDCRATE
- DZCV_ProtectedCase
- DZCV_AccessCard
- DZCV_CardReader
- DZCV_BlackboxCore
- DZCV_EncryptedDataDrive
- DZCV_ClassifiedIntel
- DZCV_SealedRewardChest

Die hochgeladene Klassenliste wurde nur zur Auswahl existierender Loot-Classnames verwendet, nicht als Codequelle.

## Expansion-Sonderregel

Oeffentliche DayZ-Expansion-Sources duerfen fuer API- und Kompatibilitaetspruefung gelesen werden. Sie sind keine Freigabe zum Kopieren von Code, Assets, Layouts, Kommentaren, Headern oder Lizenztexten. Direkte Expansion-Nutzung in diesem Modul ist als Uebergangsstand dokumentiert und soll in `DeutschZ_ExpansionBridge` gekapselt werden.
