# OPEN ASSUMPTIONS

- Stage-Ziele verwenden in v0.4.0 noch einen sicheren Timer-Fallback. Die Code-Schnittstelle `CompleteCurrentStageByPlayer` ist vorbereitet, damit Terminal-, Generator- und Containment-Objekte im nächsten Compile-Pass echte serverseitige Actions auslösen können.
- Expansion AI und Expansion Marker werden noch nicht direkt aufgerufen, weil die tatsächlichen Patchnamen und API-Funktionen der installierten Expansion-Version zuerst an der Zielkomponente geprüft werden müssen.
- Banking-, Garage- und Battlepass-Brücken sind bewusst nicht direkt verdrahtet. Sie werden später über eigene DeutschZ-Adapter ergänzt.
- Default-Positionen sind ChernarusPlus-Beispiele und müssen serverseitig in der JSON angepasst werden.
- Retry-UI ist als RPC-/API-Hook vorbereitet; echtes Layout/Widget folgt nach erstem erfolgreichen Compile-Test.
- Der AI-Bridge-Sicherheitsfallback nutzt Vanilla-Infizierte als Platzhalterdruck, bis Expansion AI sauber angebunden ist.
