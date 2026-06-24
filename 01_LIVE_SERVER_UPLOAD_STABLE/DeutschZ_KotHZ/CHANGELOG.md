## 0.9.3-online-test - 2026-06-23
- Online-Testserver pack/test candidate; config.cpp/script module validation aligned.

## FIX42 - KotHZ Flag Texture Compile Hotfix (2026-06-22)
## 2.3.3-fix43-music-rpc - 2026-06-22
- KotHZ event music is no longer hard-disabled in config repair. Default: play on event start and completion, not on ready phase.
- Added client-side music RPC using `SEffectManager.PlaySound` so nearby players receive the configured `DeutschZ_KotHZ_EventMusic_SoundSet`.
- Updated ready configs and config guide to keep music enabled by default while leaving risky smoke/fog paths disabled.
- Updated mod.cpp/config.cpp version to `2.3.3-fix43-music-rpc`.

- Fixed World compile error in `DeutschZKotHZFlagpole.c`: `SetObjectTexture` was called on generic `Object`.
- Changed the DeutschZ flag texture safety path to accept/call `EntityAI` only.
- Keeps FIX41 EventFlow behavior intact: capture waves, boss phase, M249 block, one-marker target and safe audio/smoke defaults.
- No Core, Bridge, ConvoyZ, GroundZero or CourierZ source changes in this hotfix.

## FIX41 - EventFlow Bossphase, Signalstation, Flagge (2026-06-22)
- Capture bleibt radiusbasiert: Signalstation betreten, Bereich halten, keine versteckte Interaktion noetig.
- KotHZ endet nicht mehr direkt bei 100% Capture: Danach erscheint ein Spezial-Boss.
- Finaler Mummy-Boss spawnt nach Capture, wird visuell vergroessert und mit 5000 HP gesetzt.
- KotHZ-HUD nutzt in der Bossphase die Statusbar als verbleibende Boss-HP-Anzeige.
- Reward-Crate wird erst nach Bosskill freigegeben; bei Boss-Spawn-Fallback wird Reward sicher freigegeben.
- Drei Wellen bleiben nach Capture-Prozent: zivil, Hunter/Patrol, Military.
- DeutschZ Flagtextur wird auf dem angehaengten Flaggenobjekt zusaetzlich erzwungen, damit keine weisse Fahne angezeigt wird.
- Musik/Smoke/Fog bleiben weiter vorsichtig ausgeschaltet bzw. config-gated; keine riskanten Loops reaktiviert.

﻿## Publishing Cleanup + Stage-0 Atmosphere Defaults (2026-06-22)
- Workshop description refreshed to German, English and Russian only.
- Added `DeutschZ_KotHZ_types.xml` with event classes at `nominal=0` for adminspawn/trader/event rewards, not random mapspawn.
- Added admin-friendly config guide under `docs/config/`.
- Repair/migration now keeps risky atmosphere defaults off: music, object smoke, particle smoke, fog hazard and smoke cannons remain disabled until separate tests.
- KotHZ signalstation/marker documentation now matches the auto-capture flow.
## FIX41 - Signalstation Auto-Capture + Single Marker + M249 Guard (2026-06-22)
- KotHZ now communicates the intended flow clearly: go to the signal station, hold the radius, no action-menu interaction required.
- Added player entry/leave messages for the signal-station radius and a contested message when progress is blocked.
- Marker cleanup now removes legacy IDs (`KotHZ_*`, `KotHZ_3D_*`, `Signalstation_*`, `DeutschZ_KotHZ_*`) before creating one visible `KotHZ_<ZoneName>` marker.
- Marker/capture/HUD center continues to prefer `FlagpolePosition`, with `Position` as fallback.
- Reward and optional NPC loadout paths use the shared unsafe-class guard; vanilla `M249` and `Mag_M249_Box200Rnd` are blocked, `GCGN_M249` stays allowed.
- Risky music, smoke/fog, particle smoke and RuntimeFlagpole attachment paths remain disabled.

## FIX39 - KotHZ Reward Crash Guard + Flag Compile Fix (2026-06-22)
- Fixed World compile error in `DeutschZKotHZFlagpole.c`: `SetAnimationPhase` is no longer called on generic `Object`; the pole is cast to `EntityAI` first.
- Added/kept runtime reward crash guard for exact unsafe vanilla `M249` and `Mag_M249_Box200Rnd` entries even if old server profile loot configs still contain them.
- Default/example KotHZ loot pools keep `GCGN_M249` and `GCGN_M249_Mag` allowed, as requested.
- KotHZ music, particle smoke, heavy physical marker fallbacks and risky RuntimeFlagpole paths remain disabled for crash isolation.

## FIX37 - Repo Clean / Changelog Baseline (2026-06-22)
- Repository-Basis auf aktuellen KotHZ-FIX36-Stand abgeglichen.
- Behaelt sichtbaren Mast/Fahne, einen eindeutigen Marker, Capture-HUD, Zombies/Waves und Rewardflow bei.
- KotHZ-Musik, Smoke/Fog und riskante RuntimeFlagpole-Pfade bleiben deaktiviert.
- Changelog fuer kuenftige Full-Source-Pakete aktualisiert.

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

# Changelog â€“ DeutschZ_KotHZ

## FIX20 â€“ Custom Event Music OGG

- Event-Musikdatei ersetzt.
- Neue Benutzerdatei `KotHZ im roten Rauch.ogg` wurde als `data/sounds/DeutschZ_KotHZ_RoterRauch.ogg` eingebunden.
- `CfgSoundShaders` und SoundSet-Namen bleiben unveraendert, damit keine Config-/Script-Umstellung noetig ist.
- Mod-Version auf `2.2.7 Infected Siege FIX20 Sound Path Aligned` gesetzt.
- FIX18 Compliance-/No-Copy-Dokumentation bleibt erhalten.

## FIX18 â€“ Compliance Audit / No-Copy Cleanup

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

## FIX17 â€“ Proper Test Loot

- Schnellstart-Testversion.
- High-Value-Testloot aus serverseitigen Classname-Referenzen.
- Ready-copy Configs beigelegt.

## FIX15/FIX14 â€“ Safe Recheck

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

