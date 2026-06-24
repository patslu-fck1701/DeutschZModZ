# DeutschZ_KotHZ FIX35 - Flow / Marker / Flag Visual

## Ziel

Dieser Hotfix reagiert auf den Live-Test:

- Kein sichtbarer Mast.
- Flagge lag/war zusammengelegt.
- Doppelte Marker waren sichtbar.
- Signalstation/Marker war sichtbar, aber Capture lief nicht sinnvoll weiter.
- Nach KotH-Abschluss erschien/bleib ein zweiter Statusbalken bzw. eine Boss-/Nachphase.

## Fixes

- Sichtbarer Mast wird wieder gespawnt. Primär wird vanilla `TerritoryFlag` verwendet, mit DeutschZ-KotH-Flag als Attachment.
- Die alte lose/faltbare `Flag_Base`-Darstellung ist nur noch letzter Fallback.
- Capture-Logik, HUD-Reichweite und Markerposition verwenden jetzt dieselbe sichtbare Mast-/Flaggenposition.
- KotHZ erstellt nur noch einen Expansion-Servermarker. Wenn 3D aktiv ist, wird derselbe Marker als 3D-Marker erzeugt, statt zusätzlich einen zweiten Marker mit anderem Prefix zu erzeugen.
- Der Boss-Block nach 100 Prozent Capture wurde deaktiviert. KotH endet jetzt nach erfolgreicher Capture-Zeit direkt.
- Der HUD-/Statusbalken wird beim Abschluss sofort ausgeblendet.

## Weiterhin bewusst deaktiviert

- Eventmusik
- physische Smoke-Grenades
- Particle-Smoke auf dem Mast
- alte RuntimeFlagpole-Attachment-Kette als Hauptpfad

Grund: Crash-Isolation bleibt wichtiger als Optik-Spielerei.

## Erwarteter Ablauf

1. KotHZ startet.
2. Ein Marker zeigt auf die echte Mast-/Flaggenposition.
3. Am Mast ist eine sichtbare Flagge angebracht.
4. Ein einzelner Spieler im Radius startet Capture.
5. Bei mehreren Spielern ist die Zone contested und der Capture pausiert.
6. Bei 100 Prozent endet KotHZ direkt.
7. Reward wird erzeugt/ausgegeben.
8. HUD verschwindet, Marker und Eventobjekte werden bereinigt.
