# DeutschZ_KotHZ – Compliance README

Projekt: DeutschZ_KotHZ – Infected Siege  
Autor/Eigentuemer: Patrick Sluzalek / fck1701  
Server/Projekt: DeutschZ

Diese Mod ist als eigenstaendige DeutschZ-Implementierung aufgebaut. Ziel ist ein server-autoritatives King-of-the-Hill-Event mit Vanilla-Infizierten-Wellen, ZmbM_Mummy-Boss, Reward-Crate und Expansion-Marker-Nutzung ueber oeffentlich nutzbare API-Schnittstellen.

## No-Copy-Grundsatz

In dieser Mod duerfen keine fremden Scriptdateien, Fremdmod-Klassen, UI-Dateien, Layouts, Config-Strukturen, JSON-Beispiele, Icons, Sounds, Texturen oder Modelle aus fremden Mods enthalten sein, sofern keine dokumentierte Freigabe vorliegt.

## Abhaengigkeiten

- DayZ / Enforce Script: Zielplattform und Vanilla-API.
- CF: technische Server-/Script-Abhaengigkeit.
- DayZ Expansion: nur fuer Marker/Notification-API vorgesehen; kein Expansion-Quellcode wird kopiert.

## Aktiver Build

FIX18 Compliance Audit:

- Fremdmod-/Altverweise gescannt.
- MarkerBackend-Begriffe entfernt und durch eigene MarkerMode-Bezeichnung ersetzt.
- ExpansionAI-/EventAI-Reste entfernt bzw. in eine deaktivierte eigene DeutschZ-NPC-Reserve umbenannt.
- Alte DeutschZ_KOTH-/DeutschZKOTH-Namensreste entfernt.
- Pflichtdokumentation hinzugefuegt.
- Standard-Kopfkommentar in Code-Dateien eingefuegt.

## Nutzung

Server duerfen die Mod nutzen und in ein Serverpack aufnehmen. Oeffnen, Bearbeiten, Reupload oder Veraendern des Quellcodes/der Mod ist ohne ausdrueckliche Freigabe nicht gestattet.
