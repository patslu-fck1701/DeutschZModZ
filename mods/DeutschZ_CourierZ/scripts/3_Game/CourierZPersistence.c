/* CourierZ profile and JSON persistence helpers. */

class CourierZPersistence
{
    static void EnsureProfileDirs()
    {
        MakeDirectory("$profile:DeutschZ");
        MakeDirectory(CourierZConstants.PROFILE_ROOT);
    }

    static CourierZState LoadState()
    {
        EnsureProfileDirs();

        ref CourierZState state = new CourierZState;
        if (!FileExist(CourierZConstants.STATE_PATH))
        {
            SaveState(state);
            return state;
        }

        JsonFileLoader<CourierZState>.JsonLoadFile(CourierZConstants.STATE_PATH, state);
        if (!state)
        {
            state = new CourierZState;
            SaveState(state);
        }

        return state;
    }

    static void SaveState(CourierZState state)
    {
        EnsureProfileDirs();

        if (!state)
        {
            ref CourierZState emptyState = new CourierZState;
            JsonFileLoader<CourierZState>.JsonSaveFile(CourierZConstants.STATE_PATH, emptyState);
            JsonFileLoader<CourierZState>.JsonSaveFile(CourierZConstants.BACKUP_PATH, emptyState);
            return;
        }

        JsonFileLoader<CourierZState>.JsonSaveFile(CourierZConstants.STATE_PATH, state);
        JsonFileLoader<CourierZState>.JsonSaveFile(CourierZConstants.BACKUP_PATH, state);
    }
}
