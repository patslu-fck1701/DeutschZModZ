# CHANGELOG

## 0.4.0-source
- AutoStart-Planung mit Mindestspielerzahl ergänzt.
- ConfigVersion 4 mit Retry-Minimal-Loadout, Stage-Manual-Objective-Schalter und AI-Safety-Fallback ergänzt.
- StageManager um serverseitige Objective-Completion-Schnittstelle erweitert.
- CarrierManager ruft ab 3 Komponenten AI-Suchtrupp-Intent auf.
- CheckpointManager speichert Pending-Death-Choice und Abort-Status und gibt optional Minimal-Loadout beim Retry.
- MarkerManager um Stage-Marker ergänzt.
- AIBridge mit gekapseltem Vanilla-Fallback erweitert, ohne Expansion-Code zu kopieren.
- BossManager mit klarerer Final-Defense-State-Machine verfeinert.
- ExtractionManager erzeugt Forschungskern und globale Extraktionsmarkierung über Manager-Schnittstellen.
- MissionHooks um Retry/Abort-RPC-Weiterleitung ergänzt.
- NEEDED_FROM_PATRICK.md ergänzt.

## 0.4.0-source
- Struktur an DayZ Leitfaden 2026 angepasst.
- `gameLibScriptModule` Schreibweise korrigiert.
- Config auf Load/Repair/Validate/Save erweitert.
- Persistence mit Backup/Repair/Reset ergänzt.
- Logging nach `$profile:DeutschZ/Logs/` verlegt.
- EventManager mit Timeout und idempotentem Cleanup verbessert.
- Carrier-, Item-, Marker-, Checkpoint- und Stage-Manager nach Server-Autorität verfeinert.
- Release-Checklist ergänzt.

## 0.2.1-source
- Erste packbare GroundZero Source-Struktur.
