class DeutschZGroupsAdminAPI
{
    protected static void FindGroupFiles(notnull array<string> outFiles)
    {
        outFiles.Clear();
        FindFileHandle handle;
        string fileName;
        int fileAttr;

        handle = FindFile(DeutschZGroupsConstants.PROFILE_GROUP_DATA_ROOT + "/*.json", fileName, fileAttr, 0);
        if (handle)
        {
            bool found = true;
            while (found)
            {
                outFiles.Insert(fileName);
                found = FindNextFile(handle, fileName, fileAttr);
            }
            CloseFindFile(handle);
        }
    }

    protected static DeutschZGroupData LoadGroupFile(string fileName)
    {
        if (fileName == "")
            return null;

        ref DeutschZGroupData group = new DeutschZGroupData();
        string fullPath = DeutschZGroupsConstants.PROFILE_GROUP_DATA_ROOT + "/" + fileName;
        JsonFileLoader<DeutschZGroupData>.JsonLoadFile(fullPath, group);
        if (!group || group.GroupId == "")
            return null;
        group.EnsureArrays();
        return group;
    }

    static bool GetStatus(out string message)
    {
        DeutschZGroupsProfileFolders.Ensure();
        ref array<string> files = new array<string>;
        FindGroupFiles(files);

        int memberCount = 0;
        int markerCount = 0;
        foreach (string fileName : files)
        {
            DeutschZGroupData group = LoadGroupFile(fileName);
            if (!group)
                continue;
            if (group.Members)
                memberCount += group.Members.Count();
            if (group.Markers)
                markerCount += group.Markers.Count();
        }

        message = "DeutschZ_Groups OK. Groups=" + files.Count().ToString() + " Members=" + memberCount.ToString() + " Markers=" + markerCount.ToString();
        return true;
    }

    static bool ReloadAll(out string message)
    {
        DeutschZGroupsProfileFolders.Ensure();
        DeutschZGroupsManager manager = DeutschZGroupsRuntime.GetManager();
        if (manager)
        {
            manager.LoadGroups();
            manager.SaveAllGroups();
            message = "DeutschZ_Groups reloaded via manager.";
            return true;
        }

        message = "DeutschZ_Groups manager not ready. File API is available but runtime reload skipped.";
        return false;
    }

    static bool BuildGroupRows(array<string> rows, int limit, out string message)
    {
        if (!rows)
        {
            message = "Rows array missing.";
            return false;
        }

        rows.Clear();
        if (limit <= 0)
            limit = 12;

        DeutschZGroupsProfileFolders.Ensure();
        ref array<string> files = new array<string>;
        FindGroupFiles(files);

        int added = 0;
        foreach (string fileName : files)
        {
            if (added >= limit)
                break;

            DeutschZGroupData group = LoadGroupFile(fileName);
            if (!group)
                continue;

            int members = 0;
            int markers = 0;
            if (group.Members)
                members = group.Members.Count();
            if (group.Markers)
                markers = group.Markers.Count();

            rows.Insert(group.Name + "|" + group.Tag + "|" + members.ToString() + "|" + markers.ToString() + "|" + group.OwnerSteam64);
            added++;
        }

        message = "DeutschZ_Groups rows: " + added.ToString() + " / files=" + files.Count().ToString();
        return true;
    }

    static bool BuildPlayerGroupRows(string steam64, array<string> rows, out string message)
    {
        if (!rows)
        {
            message = "Rows array missing.";
            return false;
        }

        rows.Clear();
        steam64.Trim();
        if (steam64 == "")
        {
            message = "Steam64 missing.";
            return false;
        }

        DeutschZGroupsProfileFolders.Ensure();
        ref array<string> files = new array<string>;
        FindGroupFiles(files);

        foreach (string fileName : files)
        {
            DeutschZGroupData group = LoadGroupFile(fileName);
            if (!group || !group.Members)
                continue;

            DeutschZGroupMemberData member = group.FindMember(steam64);
            if (!member)
                continue;

            int markers = 0;
            if (group.Markers)
                markers = group.Markers.Count();

            rows.Insert(group.Name + "|" + group.Tag + "|" + member.Rank + "|" + markers.ToString() + "|" + group.OwnerSteam64);
            message = "Player is in group " + group.Tag + ".";
            return true;
        }

        rows.Insert(steam64 + "|No Group|0|0|No owner");
        message = "Player is not in a group.";
        return true;
    }
}
