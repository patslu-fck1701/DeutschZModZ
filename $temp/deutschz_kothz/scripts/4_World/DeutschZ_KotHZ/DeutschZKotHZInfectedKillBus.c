/*
DeutschZ ModZ
Eigenstaendige Implementierung fuer DeutschZ.
Autor/Eigentuemer: Patrick Sluzalek / fck1701.
Keine direkte Codeuebernahme aus Drittquellen.
Oeffentliche Quellen werden nur zur Konzept- und API-Verifikation genutzt.
*/

// DeutschZ KotHZ - World-to-Mission kill bridge.
// 4_World must not reference MissionServer or other 5_Mission classes.
// ZombieBase only enqueues killed infected here; MissionServer drains the queue.
class DeutschZKotHZInfectedKillBus
{
    protected static ref array<Object> s_KilledInfectedQueue;

    protected static void Ensure()
    {
        if (!s_KilledInfectedQueue)
            s_KilledInfectedQueue = new array<Object>;
    }

    static void Enqueue(Object infected)
    {
        if (!infected)
            return;

        Ensure();
        s_KilledInfectedQueue.Insert(infected);
    }

    static bool Pop(out Object infected)
    {
        Ensure();
        infected = null;

        if (s_KilledInfectedQueue.Count() <= 0)
            return false;

        infected = s_KilledInfectedQueue.Get(0);
        s_KilledInfectedQueue.Remove(0);
        return infected != null;
    }

    static void Clear()
    {
        Ensure();
        s_KilledInfectedQueue.Clear();
    }

    static int Count()
    {
        Ensure();
        return s_KilledInfectedQueue.Count();
    }
}
