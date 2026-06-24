# DeutschZ_ExpansionBridge Config Guide

## Pfad

Bridge nutzt die gemeinsamen Core-Pfade. Eigene Live-JSON ist normalerweise nicht erforderlich.

## Wofuer?

- optionale DayZ Expansion Marker
- optionale 3D Marker
- optionale Notifications
- optionale AI-/Infected-Bridge

## Aendern

Eventmods sollen keine direkten Expansion Calls bekommen. Anpassungen gehoeren in die Bridge oder in die Event-Config, nicht in Fremdmods.

## Nicht blind aendern

- Marker-ID-Prefixe
- DeleteMarker/CreateMarker-Routen
- direkte Expansion Calls in Eventmods einfuehren

## Livebetrieb

Nach Core laden, vor KotHZ/ConvoyZ/GroundZero/CourierZ.
