DeutschZ_ConvoyZ Static Crash Event v1

Config/Profile path:
Profiles/DeutschZ/ConvoyZ
Server runtime path:
$profile:DeutschZ/ConvoyZ/

Event flow:
SPAWNING -> SECURE_AREA -> BLACKBOX_READY -> HACKING -> REWARD_UNLOCKED -> CLEANUP
FAILED is used for critical errors.

Smoke:
Red = secure area
Yellow = blackbox ready / hacking
Green = reward unlocked
White = failed

Important objects:
Land_HACKEDCRATE = hackable blackbox terminal
DZCV_ProtectedCase = reward/intel case using Case.paa

Notes:
- The fallback AI spawns via AIClassName if the DeutschZ AI provider bridge returns false.
- The neutral DeutschZ AI provider boundary is in DeutschZConvoyZManager.c.
- Custom UI/statusbar can replace DeutschZConvoyZ_ShowStatus.
- Individual red Z letters need a real widget; chat fallback is plain text.
