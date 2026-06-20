class DeutschZTools_FileUtil
{
    static void EnsureProfileDirs()
    {
        if (!FileExist(DeutschZTools_Constants.PROFILE_BASE))
            MakeDirectory(DeutschZTools_Constants.PROFILE_BASE);

        if (!FileExist(DeutschZTools_Constants.PROFILE_ROOT))
            MakeDirectory(DeutschZTools_Constants.PROFILE_ROOT);

        if (!FileExist(DeutschZTools_Constants.PROFILE_CONFIG_DIR))
            MakeDirectory(DeutschZTools_Constants.PROFILE_CONFIG_DIR);
    }
}
