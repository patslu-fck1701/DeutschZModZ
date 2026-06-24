/*
    DeutschZ_GroundZero
    Owner: Patrick Sluzalek / fck1701
    Purpose: Original DeutschZ Ground Zero campaign infected spawning with staggered batches.
    Dependencies: DayZ scripts, optional CF/Expansion/Expansion AI/Expansion Marker as API only.
    Compliance: No foreign mod source, config, assets, class bodies or stubs copied.
*/

class GroundZeroZombieManager
{
    protected GroundZeroConfig m_Config;
    ref array<Object> m_Spawned;

    void GroundZeroZombieManager(GroundZeroConfig cfg)
    {
        m_Config = cfg;
        m_Spawned = new array<Object>();
    }

    string ClassForThreat(int threat)
    {
        return "ZmbM_usSoldier_Officer_Desert";
    }

    protected int CountAliveLocal()
    {
        int alive = 0;
        for (int i = m_Spawned.Count() - 1; i >= 0; i--)
        {
            Object o = m_Spawned.Get(i);
            if (!o)
            {
                m_Spawned.Remove(i);
                continue;
            }
            alive++;
        }
        return alive;
    }

    void SpawnWave(vector center, int threat, int count, float radius)
    {
        if (!m_Config.EnableZombies) return;
        if (count <= 0) return;

        int active = CountAliveLocal();
        int allowed = m_Config.MaxActiveInfected - active;
        if (allowed <= 0)
        {
            GroundZeroLogging.Info("Zombies", "Wave skipped activeLimit active=" + active.ToString() + " limit=" + m_Config.MaxActiveInfected.ToString());
            return;
        }

        int toSpawn = count;
        if (toSpawn > allowed) toSpawn = allowed;
        string cls = ClassForThreat(threat);
        GroundZeroLogging.Info("Zombies", "Wave queued count=" + toSpawn.ToString() + " batch=" + m_Config.MaxSpawnPerBatch.ToString() + " delay=" + m_Config.SpawnBatchDelaySeconds.ToString());
        SpawnBatch(cls, center, toSpawn, radius);
    }

    protected void SpawnBatch(string cls, vector center, int remaining, float radius)
    {
        if (remaining <= 0) return;
        if (!m_Config.EnableZombies) return;

        int active = CountAliveLocal();
        if (active >= m_Config.MaxActiveInfected)
        {
            GroundZeroLogging.Info("Zombies", "Batch stopped activeLimit active=" + active.ToString());
            return;
        }

        int batch = m_Config.MaxSpawnPerBatch;
        if (batch < 1) batch = 1;
        if (batch > remaining) batch = remaining;
        if (active + batch > m_Config.MaxActiveInfected) batch = m_Config.MaxActiveInfected - active;

        int spawned = 0;
        for (int i = 0; i < batch; i++)
        {
            vector p = center + Vector(Math.RandomFloat(-radius, radius), 0, Math.RandomFloat(-radius, radius));
            if (GroundZeroCoreBridge.SpawnInfected("zombies", cls, p))
            {
                spawned++;
                continue;
            }

            Object o = GetGame().CreateObjectEx(cls, p, ECE_PLACE_ON_SURFACE);
            if (o)
            {
                m_Spawned.Insert(o);
                spawned++;
            }
        }

        GroundZeroLogging.Info("Zombies", "Batch spawned=" + spawned.ToString() + " remaining=" + (remaining - batch).ToString() + " activeLocal=" + CountAliveLocal().ToString());

        int left = remaining - batch;
        if (left > 0)
            GetGame().GetCallQueue(CALL_CATEGORY_SYSTEM).CallLater(SpawnBatch, m_Config.SpawnBatchDelaySeconds * 1000, false, cls, center, left, radius);
    }

    void Cleanup()
    {
        GroundZeroCoreBridge.CleanupAI("zombies");
        foreach (Object o : m_Spawned)
        {
            if (o) GetGame().ObjectDelete(o);
        }
        m_Spawned.Clear();
        GroundZeroLogging.Info("Zombies", "Cleanup complete");
    }
}
