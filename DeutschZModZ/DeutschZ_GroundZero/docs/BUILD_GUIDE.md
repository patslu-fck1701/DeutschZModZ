# DeutschZ_GroundZero Build Guide v0.4.0

Diese Source ist nach dem DayZ Mod Struktur-, Architektur-, Compile- und Release-Leitfaden 2026 verfeinert.

Pflichtablauf:

1. Source nach `P:\DeutschZ_GroundZero` legen.
2. Mit FilePatching gegen eigene Mod alleine testen.
3. Dann mit CF testen.
4. Dann mit CF + Expansion testen, falls Expansion-AI/Marker-Adapter aktiviert werden.
5. Erst danach mit kompletter Server-Modliste testen.
6. AddonBuilder zuerst mit `-packonly` nutzen.
7. Danach final binarisieren und signieren.
8. Jede PBO braucht eine passende BISIGN.
9. Keine alten PBO/BISIGN-Reste in `@DeutschZ_GroundZero/Addons` lassen.
10. Linux-Pfade und Prefix exakt prüfen.

Hinweis: v0.4.0 ist weiterhin eine Source-/Implementierungsbasis. Expansion-AI- und Expansion-Marker-Aufrufe sind absichtlich als Adapter/Fallback gekapselt, bis die tatsächlichen Ziel-Patchnamen und API-Funktionen der installierten Expansion-Version direkt geprüft wurden.
