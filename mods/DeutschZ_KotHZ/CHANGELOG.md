## FIX36 - Event Ausbau Stage 1 / closer staged starts
- Adjusted staged test-start order: KotHZ 1 min, ConvoyZ 3 min, GroundZero 5 min, CourierZ 7 min.
- Keeps crash-risk features off: KotHZ music, physical smoke/fog cannons and heavy marker fallback objects remain disabled.
- Re-enables/keeps stable gameplay additions only: visible flags, Expansion markers, HUD/progress, infected/waves, rewards and reduced no-spam status messages.
- ConvoyZ now routes its 3D marker request through Core/ExpansionBridge when enabled.

## FIX34 - KotHZ Compile/Lifecycle Audit (2026-06-22)
- Restored missing `HasEnoughPlayers`, `CountPlayersInZone`, `FindSingleHolderInZone`, `FinishEvent`, `StopEvent`, `SpawnZoneDecorations`, `GiveRewardsDirect` and `GetRemainingZombieSlots` methods after the crash-isolation cleanup.
- Physical smoke object/particle smoke path stays disabled; visible state is routed through safe flag object + Expansion markers.
- Military infected fallback list uses `ZmbM_usSoldier_Officer_Desert` to avoid the previously problematic beige soldier fallback class.
- Keeps KotHZ music disabled and keeps the risky RuntimeFlagpole attachment path out of active use.


## FIX31 - KotHZ Crash/Marker/Flag Regression (2026-06-22)
- KotHZ crash isolation: music hard-disabled and risky RuntimeFlagpole attachment path removed from active use.
- KOTH flag now uses a safe visible Flag_Base-derived DeutschZ flag object.
- ExpansionBridge now creates real DayZ Expansion server markers via ExpansionMarkerModule/CreateServerMarker.
- ConvoyZ physical smoke and failing wreck classes reduced for crash isolation.

# CHANGELOG

## 2026-06-20 - Core/Bridge/Event Integration

- Core-/ExpansionBridge-Basis fuer die drei Event-Module vorbereitet.
- Sichere Provider- und Pfadstruktur ergaenzt.
- Keine Fremdmod-Dateien oder kopierten Fremdklassen hinzugefuegt.

# DeutschZ_KotHZ Changelog

## 2.2.7 - FIX20 Sound Path Aligned
- OGG-Dateiname und `CfgSoundShaders`-Pfad sauber aufeinander abgeglichen.
- Aktive OGG-Datei: `data/sounds/DeutschZ_KotHZ_RoterRauch.ogg`.
- Aktiver SoundShader-Pfad: `\DeutschZ_KotHZ\data\sounds\DeutschZ_KotHZ_RoterRauch` ohne Dateiendung, wie fuer DayZ-Soundshader ueblich.
- Alte interne OGG-Zieldatei `data/sounds/koth-laut-timer.ogg` entfernt, damit keine Namens-/Pfadverwechslung bleibt.
- SoundSet-Name bleibt `DeutschZ_KotHZ_EventMusic_SoundSet`, damit vorhandene Configs/Scripts weiter funktionieren.

# Changelog – DeutschZ_KotHZ

## FIX20 – Custom Event Music OGG

- Event-Musikdatei ersetzt.
- Neue Benutzerdatei `KotHZ im roten Rauch.ogg` wurde als `data/sounds/DeutschZ_KotHZ_RoterRauch.ogg` eingebunden.
- `CfgSoundShaders` und SoundSet-Namen bleiben unveraendert, damit keine Config-/Script-Umstellung noetig ist.
- Mod-Version auf `2.2.7 Infected Siege FIX20 Sound Path Aligned` gesetzt.
- FIX18 Compliance-/No-Copy-Dokumentation bleibt erhalten.

## FIX18 – Compliance Audit / No-Copy Cleanup

- Compliance-Dokumentation hinzugefuegt.
- Standard-Kopfkommentar in Code-Dateien eingefuegt.
- MarkerBackend-Begriffe durch eigene `MarkerMode`-Benennung ersetzt.
- ExpansionAI-/EventAI-Reste entfernt bzw. in deaktivierte eigene DeutschZ-NPC-Reserve umbenannt.
- Alte `DeutschZ_KOTH`, `DeutschZ_KOTHZ`, `DeutschZKOTH`, `DZKOTH` Textreste bereinigt.
- Alter falscher Profilpfad in Beispieldateien korrigiert.
- COT-Verweis aus EditHint entfernt.
- Doppelte inaktive Beispielasset-Ordner entfernt.
- Root/Prefix bleibt `DeutschZ_KotHZ`.
- Configpfad bleibt `$profile:DeutschZ/KotHZ/Config/`.

## FIX17 – Proper Test Loot

- Schnellstart-Testversion.
- High-Value-Testloot aus serverseitigen Classname-Referenzen.
- Ready-copy Configs beigelegt.

## FIX15/FIX14 – Safe Recheck

- Statusbar 500m.
- Duplicate Notify Schutz.
- Safe-Check auf Scriptmodule und alte Pfade.

## 0.2.5-fix35-koth-flow-visual - 2026-06-22

- Fixed KotHZ visual flow after live test feedback.
- Restored a visible mast using a vanilla TerritoryFlag-first path with attached DeutschZ flag.
- Removed the folded/loose flag as the primary visual path.
- Removed duplicate KotHZ map/3D marker ids by using one Expansion server marker.
- Aligned capture detection, HUD distance and marker position to the visible mast/flag position.
- Removed the confusing post-capture boss/statusbar block; capture completion now ends KotHZ directly.
- Kept music, smoke objects and particle/net-sync smoke disabled for crash isolation.
