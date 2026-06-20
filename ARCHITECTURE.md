# Architektur

DeutschZ_Core ist die gemeinsame Basis fuer Logging, Profilepfade, Settings, RPC-Grundlagen, Locks, Rate-Limits, Save/Load-Helfer und Modulregistrierung.

DeutschZ_ExpansionBridge ist die einzige Schicht, die direkt mit Expansion-APIs verbunden werden darf. Andere Module sprechen nur ueber DeutschZCore_AIProviderAPI und DeutschZCore_MarkerProviderAPI.

Alle Feature-Module bleiben eigenstaendig. Tools ist nur Admin-Menue und kein Core.
