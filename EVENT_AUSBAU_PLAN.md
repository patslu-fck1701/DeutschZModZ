# EVENT_AUSBAU_PLAN

Stand: 2026-06-22

## Grundsatz

Der aktuelle Serverstart gilt als stabile Basis. Es werden keine riskanten Atmosphaere-Systeme hart aktiviert. Jede Rueckkehr von Musik, Smoke oder Fog bleibt config-gesteuert, einzeln testbar und standardmaessig aus.

## Stufe 0 - stabiler Fallback

Aktiv:
- gestaffelte Starts: KotHZ 60s, ConvoyZ 180s, GroundZero 300s, CourierZ 420s
- Marker ueber DeutschZ_Core / DeutschZ_ExpansionBridge
- KotHZ Signalstation, Fahne/Mast, Auto-Capture im Radius
- klare HUD-/Chat-Texte
- Zombies/Waves und Rewards je Event

Aus:
- KotHZ Musik
- physische Smoke-Grenades als Pflichtvisual
- Particle-Smoke
- Fog-Hazard
- Smoke-Cannons
- riskante RuntimeFlagpole-Attachment-Ketten
- physische Marker-Fallbackobjekte

## Stufe 1 - risikoarme Atmosphaere

Kann als naechstes getestet werden:
- bessere Eventtexte und Markerlabels
- klarere HUD-Zustaende
- statische Dekoobjekte nur mit bekannten stabilen Vanilla-Klassen
- keine dauerhaften Partikel
- keine Soundloops
- keine physischen Smoke-Grenades

## Stufe 2 - Musik vorsichtig vorbereiten

Nur fuer KotHZ spaeter pruefen:
- EnableEventMusic bleibt Standard 0
- nur bei Eventbeginn starten, nicht bei Tick/Markerupdate
- keine Dauerschleife ohne MaxRuntime/Cooldown
- Stop bei Eventende/Cleanup testen

Empfohlene fehlende Zusatzfelder fuer spaeter:
- MusicTestMode
- MusicMaxRuntimeSeconds
- MusicCooldownSeconds
- MusicStopOnEventEnd

## Stufe 3 - Smoke/Fog einzeln testen

Nur nach stabiler Stufe 1/2:
- EnableSmoke bleibt Standard 0
- UseObjectSmoke bleibt Standard 0
- UseParticleSmoke bleibt Standard 0
- EnableFogHazard bleibt Standard 0
- EnableSmokeCannons bleibt Standard 0
- Smoke/Fog nicht gleichzeitig mit Musik testen

Empfohlene fehlende Zusatzfelder fuer spaeter:
- VisualEffectMaxRuntimeSeconds
- VisualEffectCleanupRadius

## Eventmod-Status

### DeutschZ_KotHZ
Aktiv: ein Marker, Signalstation/Fahne, Auto-Capture, HUD/Chat, Zombies/Waves, Reward-Crate.
Aus: Musik, Object-Smoke, Particle-Smoke, Fog, Smoke-Cannons, riskante Flagpole-Attachment-Kette.
Stufe 1 sicher: Texte/Markerlabels/statische Deko nach Klassenpruefung.
Weiter aus lassen: Musik/Smoke/Fog bis Einzeltest.
Config-Schalter vorhanden: EnableEventMusic, EventMusicPlayOnReady/Start/Captured, Smoke.EnableSmoke, UseObjectSmoke, UseParticleSmoke, EnableFogHazard, EnableSmokeCannons.
Fehlt fuer spaeter: MusicTestMode, MusicMaxRuntimeSeconds, MusicCooldownSeconds, VisualEffectMaxRuntimeSeconds.
Crashrisiko: alte Profilconfigs koennen riskante Werte enthalten; Repair setzt FIX42-safe defaults wieder auf aus.

### DeutschZ_ConvoyZ
Aktiv: Crashsite/Blackbox, Hack-/Loot-/Wave-Flow, Rewards, Marker/3D-Marker via Bridge.
Aus: physische Smoke-Grenades; Smoke-Funktionen sind Kompatibilitaets-No-Op.
Stufe 1 sicher: bessere Status-/Hacktexte und Markerlabels.
Weiter aus lassen: physischer Smoke bis separater Test.
Config-Schalter vorhanden: UseEventMarker, UseEvent3DMarker, EnableAiWaves, StatusNotifications, Start-/Restart-Delays.
Fehlt fuer spaeter: eigener EnableVisualSmoke-Schalter, falls Smoke wiederkommen soll.
Crashrisiko: physische Crashobjekte/Klassen muessen pro Klasse stabil bleiben.

### DeutschZ_GroundZero
Aktiv: Kampagnenstufen, Objectives, Marker/Status, Zombies/Waves, Rewards.
Aus: kein Musik-/Smoke-/Fog-System aktiv.
Stufe 1 sicher: bessere Objective-/Stage-Texte und Markerlabels.
Weiter aus lassen: neue Fog-/Particle-Systeme.
Config-Schalter vorhanden: EnableGroundZero, AutoStart, Markers, Notifications, Zombies, Rewards, DebugLogs.
Fehlt fuer spaeter: Atmosphaere-spezifische Schalter nur noetig, wenn solche Features gebaut werden.
Crashrisiko: ExpansionAI/Faction-Optionen nur mit Zielmodliste testen.

### DeutschZ_CourierZ
Aktiv: Operation Aktenkoffer, Pickup/Delivery, Carrierstatus, Marker, Reward.
Aus: kein Musik-/Smoke-/Fog-System aktiv.
Stufe 1 sicher: bessere Carrier-/Delivery-Texte und Markerlabels.
Weiter aus lassen: neue Partikel/Soundloops.
Config-Schalter vorhanden: Event Enabled, Scheduling, Markers, Notifications, Courier PvP marker, Rewards, Cleanup.
Fehlt fuer spaeter: Atmosphaere-spezifische Schalter nur noetig, wenn solche Features gebaut werden.
Crashrisiko: Carrier-Marker kann PvP-Druck erzeugen, ist aber kein Crashrisiko.

## Empfehlung fuer den naechsten Test

Nur Stufe 0 plus Stufe-1-Texte testen. Keine Musik, kein Smoke, kein Fog. Speziell KotHZ pruefen: ein Marker, Signalstation sichtbar, Radius betreten startet Fortschritt, contested blockiert, Reward bei 100 Prozent, Cleanup nach Ende.
