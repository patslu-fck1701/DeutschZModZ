# DeutschZ Extension Plan

This document parks planned features behind config gates. The current online-test build keeps live orchestration disabled.

## Core

- VersionManifest.json, BuildInfo.json
- GlobalHealthCheck, ConfigValidator, RequiredAddonsValidator
- EventRegistry, RewardRegistry, ItemRegistry
- ServerProfileBootstrap, DebugLogLevel
- AntiDupeLock, EventCooldown, GlobalPlayerProgress APIs

## ExpansionBridge

- MarkerProvider, ThreeDMarkerProvider, NotificationProvider, MapProvider
- OptionalAIProvider, FallbackProvider, ProviderHealthCheck
- NoExpansionSafeMode

## Event Mods

- KotHZ: multi-zone rotation, boss variants, capture UI, reward crate, admin controls.
- ConvoyZ: routes, crash variants, hack terminal, orange marker, clue items.
- GroundZero: local radius HUD, contamination chains, samples, bunker/lab targets.
- CourierZ: routes, pickup/delivery radius, carrier marker, reputation, decoy cases.

## OperationDeutschZ

- Meta-progression, event chains, clues, keycards, threat level, VIP crate unlocks and finale logic.
- First online-test state remains safe: EnableOperationDeutschZ = 0 and SafeBootOnly = 1.
