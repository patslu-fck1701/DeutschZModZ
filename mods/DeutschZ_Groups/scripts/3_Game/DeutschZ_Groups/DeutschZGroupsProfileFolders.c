class DeutschZGroupsProfileFolders
{
    static void Ensure()
    {
        EnsureFolder(DeutschZGroupsConstants.PROFILE_ROOT);
        EnsureFolder(DeutschZGroupsConstants.PROFILE_GROUPZ_ROOT);
        EnsureFolder(DeutschZGroupsConstants.PROFILE_CONFIG_ROOT);
        EnsureFolder(DeutschZGroupsConstants.PROFILE_DATA_ROOT);
        EnsureFolder(DeutschZGroupsConstants.PROFILE_GROUP_DATA_ROOT);
        EnsureFolder(DeutschZGroupsConstants.PROFILE_PRIVATE_MARKER_ROOT);
        EnsureFolder(DeutschZGroupsConstants.PROFILE_INVITE_ROOT);
        EnsureFolder(DeutschZGroupsConstants.PROFILE_AUDIT_ROOT);
        EnsureFolder(DeutschZGroupsConstants.PROFILE_INTEGRATION_ROOT);
        EnsureFolder(DeutschZGroupsConstants.INTEGRATION_GARAGE_ROOT);
        EnsureFolder(DeutschZGroupsConstants.INTEGRATION_BANKING_ROOT);
    }

    protected static void EnsureFolder(string path)
    {
        if (!FileExist(path))
        {
            MakeDirectory(path);
        }
    }
}
