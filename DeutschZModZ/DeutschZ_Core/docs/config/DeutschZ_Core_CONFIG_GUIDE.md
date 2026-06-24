# DeutschZ_Core Config Guide

## Pfad

Core nutzt gemeinsame Profilpfade unter `$profile:DeutschZ/` und stellt Basisdienste bereit.

## Wofuer?

- gemeinsame Serverprofil-Pfade
- Logging
- Provider-APIs
- ServiceLocator fuer Marker, Nachrichten und AI-Bridges

## Aendern

Normalerweise keine Live-Config noetig. Core ist Fundament und sollte vor allen DeutschZ-Eventmods geladen werden.

## Nicht blind aendern

- Provider-/ServiceLocator-Struktur
- Profilpfade
- Logging-Klassen

## Livebetrieb

Core immer vor ExpansionBridge und Eventmods laden.
