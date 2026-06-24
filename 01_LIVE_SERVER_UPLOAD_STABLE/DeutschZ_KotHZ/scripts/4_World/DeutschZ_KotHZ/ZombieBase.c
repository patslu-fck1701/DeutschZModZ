/*
DeutschZ ModZ
Eigenstaendige Implementierung fuer DeutschZ.
Autor/Eigentuemer: Patrick Sluzalek / fck1701.
Keine direkte Codeuebernahme aus Drittquellen.
Oeffentliche Quellen werden nur zur Konzept- und API-Verifikation genutzt.
*/

modded class ZombieBase
{
    override void EEKilled(Object killer)
    {
        super.EEKilled(killer);

        if (!GetGame() || !GetGame().IsServer())
            return;

        // Do not reference MissionServer here. 4_World compiles before 5_Mission.
        // The MissionServer drains this queue and forwards kills to DeutschZKotHZManager.
        DeutschZKotHZInfectedKillBus.Enqueue(this);
    }
}
