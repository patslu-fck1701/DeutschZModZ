/*
    DeutschZ_GroundZero
    Owner: Patrick Sluzalek / fck1701
    Purpose: Original DeutschZ Ground Zero campaign event source.
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
        if (threat <= 1)
        {
            return "ZmbM_CitizenASkinny_Brown";
        }

        if (threat == 2)
        {
            return "ZmbM_SoldierNormal_Beige";
        }

        if (threat == 3)
        {
            return "ZmbM_HunterOld_Autumn";
        }

        if (threat == 4)
        {
            return "ZmbM_SoldierHeavy_Green";
        }

        return "ZmbM_usSoldier_Officer_Desert";
    }

    void SpawnWave(vector center, int threat, int count, float radius)
    {
        if(!m_Config.EnableZombies) return;
        string cls=ClassForThreat(threat);
        for(int i=0;i<count;i++){ vector p=center+Vector(Math.RandomFloat(-radius,radius),0,Math.RandomFloat(-radius,radius)); if(GroundZeroCoreBridge.SpawnInfected("zombies",cls,p)) continue; Object o=GetGame().CreateObjectEx(cls,p,ECE_PLACE_ON_SURFACE); if(o) m_Spawned.Insert(o); }
        GroundZeroLogging.Info("Zombies", "Spawned wave count=" + count.ToString());
    }
    void Cleanup(){ GroundZeroCoreBridge.CleanupAI("zombies"); foreach(Object o:m_Spawned){ if(o) GetGame().ObjectDelete(o); } m_Spawned.Clear(); }
}
