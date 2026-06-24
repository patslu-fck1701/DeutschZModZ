DeutschZ Deployment Paket - CURRENT STABLE aus mods(13) - LIVE/TEST SPLIT V2
Datum: 2026-06-24

ZIEL
Dieses Paket trennt den aktuellen reparierten Stand in Live-Upload und Test-/Weiterentwicklung.
Es basiert auf DeutschZ_CURRENT_STABLE_mods13_REPAIRED.zip und enthaelt alle aktuellen DeutschZ-Mods.

WICHTIGER HINWEIS
Die Dateien wurden statisch geprueft und sauber getrennt. Ein echter DayZ-PBO-Packlauf und Serverstart kann hier nicht ausgefuehrt werden. Wenn beim Packen/Starten ein Fehler kommt, Pack-Log oder Crashlog schicken, nicht wieder blind Dateien mischen.

ORDNER
01_LIVE_SERVER_UPLOAD_STABLE
- Diese Mods auf den Live Server, wenn KotHZ und ConvoyZ dort laufen sollen.

02_TEST_BUILD_ONLY_DO_NOT_LIVE_UPLOAD
- Diese Mods separat neu packen und nur auf Testserver/Dev-Server verwenden.
- Positive Updates gehen spaeter einzeln auf Live.

03_FULL_CURRENT_REFERENCE_ALL_MODS
- Vollstaendige aktuelle Referenzkopie aller Mods aus diesem Paket.
- Nicht als Arbeitsordner fuer Live verwenden, nur als Sicherung/Quelle.

LIVE MODS / LOAD ORDER
1. DeutschZ_Core
2. DeutschZ_ExpansionBridge
3. DeutschZ_KotHZ
4. DeutschZ_ConvoyZ

LIVE SERVERMODLINE ZUSAETZLICH ZU EXTERNEN MODS
@DeutschZ_Core;@DeutschZ_ExpansionBridge;@DeutschZ_KotHZ;@DeutschZ_ConvoyZ

Externe Abhaengigkeiten bleiben wie bisher vor DeutschZ:
@CF;@Dabs Framework;@DayZ-Expansion-Licensed;@DayZ-Expansion-Bundle

TEST MODS / NICHT DIREKT LIVE
1. DeutschZ_GroundZero
2. DeutschZ_CourierZ
3. DeutschZ_OperationDeutschZ

TEST-REIHENFOLGE
Erst Live-Grundpaket testen:
Core -> ExpansionBridge -> KotHZ -> ConvoyZ
Dann Testmods einzeln dazu:
GroundZero -> CourierZ -> OperationDeutschZ

EINBAU LIVE
1. Alte @DeutschZ_Core, @DeutschZ_ExpansionBridge, @DeutschZ_KotHZ, @DeutschZ_ConvoyZ komplett entfernen.
2. Keine alten Addons/PBOs liegen lassen.
3. Live-Ordner aus 01_LIVE_SERVER_UPLOAD_STABLE einsetzen.
4. In der Reihenfolge Core, ExpansionBridge, KotHZ, ConvoyZ neu packen.
5. Alte kaputte Profile sichern/verschieben:
   profiles\DeutschZ\KotHZ\Config\
   profiles\DeutschZ\ConvoyZ\Config\
6. Server minimal starten, zuerst nur Core/Bridge/KotHZ/ConvoyZ.

ENTSCHEIDUNG
Live jetzt:
- DeutschZ_Core
- DeutschZ_ExpansionBridge
- DeutschZ_KotHZ
- DeutschZ_ConvoyZ

Test/Weiterbearbeitung:
- DeutschZ_GroundZero
- DeutschZ_CourierZ
- DeutschZ_OperationDeutschZ

NICHT MEHR MISCHEN
Keine Dateien aus FIX5-FIX10 oder alten Hybrid-Paketen in dieses Paket kopieren.
Keine Eventmods direkt an ExpansionMarkerModule anbinden.
Marker laufen ueber Core -> ExpansionBridge -> Expansion.

STATISCHER CHECK V2
- Aktive script-level direkte Expansion-Marker-API-Aufrufe in KotHZ/ConvoyZ: keine gefunden.
- Treffer in Changelogs/Audit-Dokumenten sind nur Dokumentation alter API-Begriffe und kein Pack-/Runtime-Code.
