/*
    DeutschZ ModZ
    Autor/Eigentuemer: Patrick Sluzalek / fck1701
    Projekt: DeutschZ
    Zweck: Eigene DeutschZ-Implementierung fuer Core, ExpansionBridge und Event-Module.
    Quellen-/Konzeptnachweis: Eigenentwickelte Struktur; DayZ, CF und Expansion nur als Laufzeit-API/Abhaengigkeit.
    No-Copy-Bestaetigung: Kein Code, keine Assets und keine Configs aus fremden Mods kopiert.
*/

class DeutschZCore_RateBucket
{
    int WindowStart;
    int Count;
}

class DeutschZCore_RateLimiter
{
    protected ref map<string, ref DeutschZCore_RateBucket> m_Buckets;

    void DeutschZCore_RateLimiter()
    {
        m_Buckets = new map<string, ref DeutschZCore_RateBucket>;
    }

    bool Allow(string key, int maxPerWindow, int windowMs)
    {
        int now = GetGame().GetTime();
        DeutschZCore_RateBucket bucket;
        if (!m_Buckets.Find(key, bucket))
        {
            bucket = new DeutschZCore_RateBucket;
            bucket.WindowStart = now;
            bucket.Count = 0;
            m_Buckets.Insert(key, bucket);
        }

        if (now - bucket.WindowStart > windowMs)
        {
            bucket.WindowStart = now;
            bucket.Count = 0;
        }

        if (bucket.Count >= maxPerWindow)
            return false;

        bucket.Count++;
        return true;
    }
}
