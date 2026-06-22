# Aktuelles Workshop-Changelog

Stand: FIX43 / 22.06.2026

- Aktueller Stand: FIX43.
- FIX43: KotHZ Musik bleibt vorbereitet, aber wieder sicher deaktiviert. Defaults und Ready-Copy-Config setzen EnableEventMusic/PlayOnStart/PlayOnCaptured auf 0.
- FIX42: World-Compilefehler in DeutschZKotHZFlagpole.c behoben: SetObjectTexture wird nicht mehr auf generic Object aufgerufen.
- FIX41 EventFlow bleibt enthalten: Capture-Wellen, Bossphase, Boss-HP-Statusbar und Reward nach Bossphase.
- KotHZ bleibt radiusbasiert: KotHZ-Zone betreten, Bereich halten, keine versteckte Interaktion noetig.
- Mummy-Boss mit hoher HP-Zahl vorbereitet; Statusbar zeigt in der Bossphase verbleibende HP.
- M249-Blocker bleibt aktiv; GCGN_M249 bleibt erlaubt.
- Musik, Smoke und Fog bleiben weiterhin vorsichtig bzw. config-gated und standardmaessig aus, bis der Eventflow stabil getestet ist.
