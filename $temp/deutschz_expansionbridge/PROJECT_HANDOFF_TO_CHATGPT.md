# PROJECT_HANDOFF_TO_CHATGPT

DeutschZ_ExpansionBridge is the only intended direct boundary for future DayZ Expansion integration.

Current scope:

- Registers marker and AI providers into `DeutschZCore_ServiceLocator`.
- Marker provider currently stores marker intent and logs requests.
- AI provider can spawn vanilla infected by classname and clean them by event id.
- Real Expansion AI and marker calls remain TODO until exact target APIs are verified from the installed Expansion version.

No PBO was packed, no server test was run and no release files were generated.
