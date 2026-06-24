/*
    DeutschZ ModZ
    Shared runtime class guard for known crash-prone vanilla classes.
*/

class DeutschZCore_UnsafeClassGuard
{
    static bool IsBlockedClass(string className)
    {
        if (className == "")
            return false;

        if (className == "GCGN_M249" || className == "GCGNM249" || className == "GCGN_M249_Mag")
            return false;

        if (className == "M249")
            return true;
        if (className == "Mag_M249_Box200Rnd")
            return true;

        return false;
    }
}
