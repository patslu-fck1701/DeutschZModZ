/* DeutschZ KotHZ local class guard. Keeps GCGN/SNAFU variants allowed; blocks only vanilla unsafe M249 classes. */
class DeutschZKotHZClassGuard
{
    static bool IsBlockedClass(string className)
    {
        if (className == "") return false;
        if (className == "M249") return true;
        if (className == "Mag_M249_Box200Rnd") return true;
        return false;
    }
}
