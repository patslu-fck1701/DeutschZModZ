# DeutschZ FIX24 CourierZ Komplett-Ersatz

## Inhalt

- DeutschZ_Core
- DeutschZ_ExpansionBridge
- DeutschZ_KotHZ
- DeutschZ_ConvoyZ
- DeutschZ_GroundZero
- DeutschZ_CourierZ
- SteamWorkshop_Beschreibungen mit CourierZ Platzhalter-Link
- AUTO_GENERATED_TEST_CONFIGS_REFERENCE inklusive CourierZ

## Einbau

1. Server stoppen.
2. Mod-Ordner nach `P:\GitHub_DeutschZModZ\DeutschZModZ\mods\` kopieren und ersetzen.
3. Folgende Mods neu packen/signieren:
   - @DeutschZ_Core
   - @DeutschZ_ExpansionBridge
   - @DeutschZ_KotHZ(InfectedSiege)
   - @DeutschZ_ConvoyZ
   - @DeutschZ_GroundZero
   - @DeutschZ_CourierZ
4. Serverprofil `$profile:DeutschZ/` fuer Test neu erzeugen lassen oder nur CourierZ-Profil loeschen.
5. Modline um `@DeutschZ_CourierZ` nach `@DeutschZ_GroundZero` erweitern.

## Test-Erwartung CourierZ

- Nach ca. 60 Sekunden wird Operation Aktenkoffer geplant/gestartet.
- Ein sichtbarer Aktenkoffer-Abholpunkt wird erzeugt.
- Marker/3D-Marker Requests laufen ueber DeutschZ_ExpansionBridge.
- Chat/Popup Notify kommt ueber Bridge.
- Vanilla-Infected-Fallbacks spawnen am Abhol- und Zielpunkt.
- Ein Spieler nahe am Koffer wird Carrier.
- Am Zielmarker wird die Lieferung abgeschlossen und eine RewardChest erzeugt.

## Neuer Workshop-Link

Nach erstem Steam Upload diesen Platzhalter ersetzen:
`[WORKSHOP_LINK_DEUTSCHZ_COURIERZ_AFTER_FIRST_UPLOAD]`


## FIX24b Credit-Hinweis

CourierZ / Operation Aktenkoffer dokumentiert jetzt transparent den Ideen-/Konzeptanstoß:

- Idee / Konzeptanstoß: Chris / Einarvargr / Konfliktzone
- Entwicklung / Implementierung: Patrick Sluzalek / fck1701 / DeutschZ DayZ Server

Dieser Hinweis ist in README, SOURCE_PROVENANCE, PUBLIC_SOURCE_REGISTER, Compliance-Dateien, Workshopbeschreibung und Changelog eingetragen.
