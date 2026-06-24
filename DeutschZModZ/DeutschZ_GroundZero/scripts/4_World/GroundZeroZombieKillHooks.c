/*
    DeutschZ_GroundZero
    Owner: Patrick Sluzalek / fck1701
    Module: 4_World / GroundZeroZombieKillHooks
    Purpose: Count GroundZero test-stage enemy kills without direct Expansion AI dependencies.
    Compliance: Original DeutschZ implementation. No copied foreign mod code, assets, configs or stubs.
*/

modded class ZombieBase
{
    override void EEKilled(Object killer)
    {
        super.EEKilled(killer);

        if (GetGame() && GetGame().IsServer())
        {
            GroundZeroCore.Get().OnGroundZeroEnemyKilled(this, killer);
        }
    }
}
