/*
    DeutschZ_CourierZ kill hook for route checkpoint progress.
*/

modded class ZombieBase
{
    override void EEKilled(Object killer)
    {
        super.EEKilled(killer);

        if (!GetGame() || !GetGame().IsServer())
            return;

        CourierZ_GetCore().OnEnemyKilled(this);
    }
}
