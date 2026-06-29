# DeutschZModZ

Official DeutschZ Mod Development Repository for DayZ.

This repository contains the original DeutschZ server-side mod sources, project documentation, changelogs, architecture notes, release notes and audit records. It is owned, designed and maintained by Patrick Sluzalek (`fck1701`) for the DeutschZ DayZ server project.

## Purpose

DeutschZModZ is the source and documentation repository for the custom DeutschZ DayZ systems.

Core goals:

- stable DayZ Enforce Script modules
- server-authoritative gameplay systems
- clean source/release separation
- no private keys or secrets in the repository
- no copied third-party PBO content
- reproducible changelogs and project state documentation
- public-facing information for Steam Workshop and Discord

## Current public modules / workshop links

- CourierZ: https://steamcommunity.com/sharedfiles/filedetails/?id=3754087534
- GroundZero: https://steamcommunity.com/sharedfiles/filedetails/?id=3754087391
- Operation Deutsch Z: https://steamcommunity.com/sharedfiles/filedetails/?id=3754087094
- ConvoyZ: https://steamcommunity.com/sharedfiles/filedetails/?id=3753962509
- KotHZ: https://steamcommunity.com/sharedfiles/filedetails/?id=3753961222

Community:

- Discord: https://discord.gg/WM5GkDbw7C
- Server/config repository: https://github.com/DeutschZModZ/DayZServer.git

## Repository rules

- Source files belong in source/module folders only.
- Built PBOs, signatures, release bundles and local server output do not belong in source folders.
- Private signing keys must never be committed.
- DayZ, CF and Expansion are referenced through clean APIs/adapters only.
- Do not decompile or copy third-party PBO content into this repository.
- Server authority first: client UI can request actions, but server code must validate.
- Configs must be validated, repaired safely and saved atomically where possible.
- Logs, profiles, local mission storage and generated backups are ignored by Git.

## Active DeutschZ systems

Currently tracked/project-relevant systems include:

1. DeutschZ_Core
2. DeutschZ_ExpansionBridge
3. DeutschZ_KotHZ
4. DeutschZ_ConvoyZ
5. DeutschZ_GroundZero
6. DeutschZ_CourierZ
7. DeutschZ_Banking
8. DeutschZ_Garage
9. DeutschZ_Groups
10. DeutschZ_TraderZ
11. DeutschZ_BattlepassZ
12. DeutschZ_SpawnSelectZ
13. DeutschZ_Tools

## Latest documented status

See:

- `docs/Projektstand_AKTUELL.md`
- `docs/CHANGELOG_2026-06-29.md`

Latest update focus:

- KotHZ server bootstrap/config stability
- GroundZero notification cooldowns
- NoxZ Phone ATM/marker/market cleanup
- Blackmarket AI patrol setup
- Expansion Object Map import documentation
- mapgrouppos merge documentation
- client-test checklist before live promotion

## Build / release policy

Keep a strict split between:

- Source: scripts, configs, documentation and project files
- Build output: PBOs, bisigns, release folders and generated artifacts
- Local server state: profiles, logs, persistence, backups and runtime files

Release artifacts should be generated deliberately and reviewed before upload.

## Security / safety

Never commit:

- `*.biprivatekey`
- API keys or webhooks
- RCON passwords
- database dumps with player data
- runtime profile folders
- local server logs
- generated release ZIPs unless intentionally published through a release workflow

## Status note

A local smoke test can verify compile/start/config loading, but it does not replace a real client join and visual/interaction test.
