# EVENTS_CORE_BRIDGE_STATUS

Stand: 2026-06-20

Scope:

- DeutschZ_Core
- DeutschZ_ExpansionBridge
- DeutschZ_KotHZ
- DeutschZ_ConvoyZ
- DeutschZ_GroundZero

## Durchgefuehrt

- GitHub-Modpfad wurde zuerst mit dem neueren Stand aus `P:/Source Files` fuer die fuenf erlaubten Mods synchronisiert.
- Alte Ziel-only KotHZ-Reste `DeutschZKotHZ_MarkerBridge.c` und `DeutschZKotHZ_LBAdvancedGroups_Notes.c` wurden entfernt, weil sie in `P:/Source Files` nicht mehr existieren und gegen die No-Copy-/No-LB-Regel laufen.
- Alle fuenf Mods haben `config.cpp`, `$PBOPREFIX$`, `mod.cpp`, Compliance-Doku, Changelog, Assumptions, Provenance und Handoff.
- DeutschZ_Core stellt Profilepfade, Logging, RateLimiter, ProviderRegistry und Event-State-Basis bereit.
- DeutschZ_ExpansionBridge registriert Marker- und AI-Provider ueber `DeutschZCore_ServiceLocator`.
- KotHZ, ConvoyZ und GroundZero verwenden CoreBridge-Klassen fuer Marker-/AI-Provider-Zugriffe.
- Direkte Event-Script-Verweise auf `ExpansionMarkerModule`, `ExpansionMarkerData`, `ExpansionNotification`, `eAIBase`, `ExpansionHumanLoadout`, LB/SFKOTH/BasicMap/VPP/COT/MarkerBridge/MarkerBackend wurden aus aktiven Scripts entfernt.
- ConvoyZ AI-Spawn prueft Klassen vor Spawn und faellt ohne Expansion-Klasse auf Vanilla-Infected zurueck.
- GroundZero Marker, AI-Fallbacks und Zombie-Spawns versuchen zuerst den Core/Bridge-Provider und behalten lokale Safe-Boot-Fallbacks.

## Bewusst offen

- Echte Expansion-Marker- und Expansion-AI-Methoden sind nicht geraten. Sie bleiben in `DeutschZ_ExpansionBridge` als TODO/OPEN_ASSUMPTION, bis die installierte Zielversion direkt geprueft wurde.
- KotHZ enthaelt noch Legacy-Konfigfelder wie `EnableExpansionNotifications` und `EnableExpansionMarker`; sie sind keine direkten API-Aufrufe mehr.
- Kein Script-Compile und kein Dedicated-Server-Test wurde ausgefuehrt.

## Nicht getan

- Keine PBOs gebaut.
- Kein AddonBuilder gestartet.
- Kein lokaler Server-Test.
- Keine Release-Dateien erzeugt.
- Keine Fremddateien kopiert.
