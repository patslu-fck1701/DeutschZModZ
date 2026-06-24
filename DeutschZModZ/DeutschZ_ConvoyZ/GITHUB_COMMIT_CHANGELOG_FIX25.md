# GitHub Commit Changelog - FIX25 Convoy Smoke Activation

Suggested commit:

```bash
git add mods/DeutschZ_ConvoyZ
git commit -m "fix(convoyz): activate and throttle event smoke"
```

## Changed
- Replaced smoke no-op with controlled smoke spawn/activation/cleanup.
- Activates vanilla smoke through `SmokeGrenadeBase.Unpin()`; fallback uses EnergyManager when available.
- Repairs blank smoke class names in Events.json during config normalization.
- Throttles smoke refresh by `Smoke.RefreshSeconds` to avoid per-tick object churn.

## Verification checklist
- Convoy smoke grenades should visibly smoke after event start/state changes.
- No smoke object pile-up: previous smoke objects are cleaned before forced state changes and refreshes.
