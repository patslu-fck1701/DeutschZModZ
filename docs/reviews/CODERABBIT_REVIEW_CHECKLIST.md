# CodeRabbit Review Checklist

- Check config.cpp requiredAddons for unverified patch names.
- Check that event mods do not depend on each other directly.
- Check MissionServer hooks for duplicate bootstraps and missing server guards.
- Check JSON load/save paths and default creation.
- Check null guards around optional providers and Expansion bridge calls.
- Check that no $temp, PBO, bisign, bikey, workshop image, or generated package file is committed unintentionally.
