# No-Copy Audit – DeutschZ_KotHZ FIX18

Pruefdatum: 2026-06-18  
Projekt: DeutschZ_KotHZ – Infected Siege  
Autor/Eigentuemer: Patrick Sluzalek / fck1701

## Audit-Ergebnis

Status: **Bereinigt mit dokumentierten Annahmen**

## Gefundene/verdaechtige Punkte und Massnahmen

| Datei/Bereich | Verdaechtiger Inhalt | Risiko | Massnahme |
|---|---|---|---|
| Config/JSON/Scripts | `MarkerBackendMode`, `GetMarkerBackendMode` | Klang nach alter generischer MarkerBackend-Struktur | Umbenannt in eigene DeutschZ-Bezeichnung `MarkerMode` / `GetMarkerMode`. |
| Config/Zone/Scripts | `EnableExpansionAI`, `KnownExpansionAIClassNames`, `SpawnExpansionAI`, `CleanupExpansionAI` | Koennte als fremder ExpansionEventAI-Stub missverstanden werden | Umbenannt/neutralisiert zu eigener deaktivierter DeutschZ-NPC-Reserve. Keine ExpansionAI-Spawnlogik aktiv. |
| config.cpp / Manager | alte `DeutschZKOTH_*` Klassen | Gemischte Altklasse/Prefix-Reste und Persistenzrisiko | Alte Klassen aus config.cpp entfernt; Runtime-Klassen nutzen `DeutschZKotHZ_*`. |
| Beispiele/README | alter Pfad `$profile:DeutschZ/KOTHZ/Config/` | falscher Profilpfad | Auf `$profile:DeutschZ/KotHZ/Config/` korrigiert. |
| LootPool EditHint | Text `JSON/COT` | COT-Fremdverweis | Ersetzt durch `DeutschZ JSON`. |
| Beispiele | doppelte inaktive CustomPAA-/CustomSound-Ordner | unnoetige Asset-Duplikate | Entfernt. Aktive Projektassets bleiben im eigentlichen Modpfad. |
| Code-Dateien | fehlender Standard-Kopfkommentar | Compliance-Dokumentation unvollstaendig | Standard-Kopfkommentar eingefuegt. |

## Suchbegriffe nach Bereinigung

Folgende Suchbegriffe wurden nach der Bereinigung ohne Treffer in Textdateien geprueft:

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
- ExpansionEventAI
- ExpansionAI
- DeutschZKOTH
- DZKOTH
- DeutschZ_KOTHZ
- DeutschZ_KOTH

## Hinweis zu Classnames

Reward-Classnames aus Waffenmods sind nur optionale serverseitige Config-Referenzen. Es werden keine fremden Modelle, Texturen, Scripts oder Config-Dateien dieser Mods kopiert.
