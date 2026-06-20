# CHANGELOG

## 0.4.1-source-audit

- Renamed `$PREFIX$` to `$PBOPREFIX$`.
- Added root compliance files required by the DeutschZ source standard.
- Added source `mod.cpp` with only existing/no-missing asset references.
- Moved retry and abort RPC handling from `MissionServer.OnRPC` to `PlayerBase.OnRPC`.
