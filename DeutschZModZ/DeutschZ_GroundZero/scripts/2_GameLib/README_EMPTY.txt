DeutschZ GroundZero GameLib module intentionally contains no runtime .c files.
Runtime helpers that use JsonFileLoader, FileIO or GetGame are loaded in scripts/3_Game to avoid GameLib compile errors.
