# Public Source Register

Projekt: DeutschZ_KotHZ – Infected Siege  
Autor/Eigentuemer: Patrick Sluzalek / fck1701

## Genutzte oeffentliche Quellen / Konzepte

| Bereich | Nutzung | Status | Hinweis |
|---|---|---|---|
| DayZ Enforce Script | Script-Sprache, Mission/Game/World-Modultrennung, Vanilla-Klassen | Plattform/API | Keine direkte Codeuebernahme. |
| DayZ Vanilla Classes | Classname-Referenzen wie SeaChest, GPSReceiver, PunchedCard, Paper, ZmbM_Mummy, Vanilla-Zombies | API-/Config-Nutzung | Keine Vanilla-Scriptdateien kopiert. |
| CF | Addon-/Script-Abhaengigkeit fuer serverseitige Modumgebung | API-Nutzung | Kein CF-Quellcode kopiert. |
| DayZ Expansion public scripts/wiki | API-, CfgPatches-, requiredAddons-, Klassen- und Signaturpruefung fuer Marker/Notifications/AI | API-/Referenznutzung | Kein Expansion-Code, keine Layouts, keine Assets, keine Kommentare und keine Lizenztexte kopiert. |
| User-Datei All-classes-and-their-attachments.json | Classname-Auswahl fuer Test-Loot-Konfiguration | User-supplied config reference | Nur Classname-Referenzen, keine Assets oder Scripts. |

## Nicht genutzt / entfernt

- LBmaster
- LBAdvancedGroups
- LBAdminTool
- SFKOTH
- BasicMap
- VPPAdmin
- COT
- AdvancedGroups
- MarkerBridge
- MarkerBackend
- Fremde ExpansionEventAI-Stubs

## Offene Punkte

Custom-PAA- und OGG-Dateien wurden als vom Projekt/Benutzer bereitgestellte oder im Projektverlauf erzeugte Assets behandelt. Herkunft bleibt in `OPEN_ASSUMPTIONS.md` dokumentiert.

## Expansion-Sonderregel

Oeffentliche DayZ-Expansion-Sources duerfen fuer API- und Kompatibilitaetspruefung gelesen werden. Sie sind keine Freigabe zum Kopieren von Code, Assets, Layouts, Kommentaren, Headern oder Lizenztexten. Expansion-Integration bleibt eigene DeutschZ-Implementierung und wird perspektivisch ueber `DeutschZ_ExpansionBridge` gekapselt.
