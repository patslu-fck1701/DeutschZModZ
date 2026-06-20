/*
    DeutschZ_GroundZero
    Owner: Patrick Sluzalek / fck1701
    Module: 4_World / GroundZeroAIBridge
    Purpose: Isolated adapter boundary for Expansion AI intent calls and safe vanilla fallback.
    Dependencies: DayZ scripts. Expansion AI integration must be added only after target patch/API names are verified.
    Compliance: Original DeutschZ implementation. No copied foreign mod code, assets, configs or stubs.
*/

class GroundZeroAIBridge
{
    protected GroundZeroConfig m_Config;
    protected ref array<Object> m_FallbackUnits;

    void GroundZeroAIBridge(GroundZeroConfig cfg)
    {
        m_Config = cfg;
        m_FallbackUnits = new array<Object>();
    }

    void SpawnMilitaryPatrol(vector center, int count)
    {
        if (count <= 0) return;
        if (!m_Config.EnableMilitaryFaction) return;
        GroundZeroLogging.Info("AI", "Military patrol requested count=" + count.ToString() + " pos=" + center.ToString());
        SpawnFallbackIfNeeded(center, count, "ZmbM_SoldierNormal_Beige", 90);
        // ASSUMPTION: Replace this adapter body with verified Expansion AI patrol/group calls for the installed Expansion version.
    }

    void SpawnRoguePatrol(vector center, int count)
    {
        if (count <= 0) return;
        if (!m_Config.EnableRogueFaction) return;
        GroundZeroLogging.Info("AI", "Rogue patrol requested count=" + count.ToString() + " pos=" + center.ToString());
        SpawnFallbackIfNeeded(center, count, "ZmbM_SoldierHeavy_Green", 90);
        // ASSUMPTION: Replace this adapter body with verified Expansion AI faction/group calls for the installed Expansion version.
    }

    void SpawnCarrierSearchTeam(vector target, int count)
    {
        if (count <= 0) return;
        if (!m_Config.EnableCarrierAISearchTeams) return;
        GroundZeroLogging.Info("AI", "Carrier search team requested count=" + count.ToString() + " target=" + target.ToString());
        SpawnFallbackIfNeeded(target, count, "ZmbM_usSoldier_Officer_Desert", 120);
    }

    void SpawnFallbackIfNeeded(vector center, int count, string className, float radius)
    {
        if (!m_Config.EnableVanillaAISafetyFallback) return;
        for (int i = 0; i < count; i++)
        {
            vector pos = center + Vector(Math.RandomFloat(-radius, radius), 0, Math.RandomFloat(-radius, radius));
            if (GroundZeroCoreBridge.SpawnInfected("ai_fallback", className, pos))
                continue;

            Object obj = GetGame().CreateObjectEx(className, pos, ECE_PLACE_ON_SURFACE);
            if (obj) m_FallbackUnits.Insert(obj);
        }
    }

    void Cleanup()
    {
        GroundZeroCoreBridge.CleanupAI("ai_fallback");
        foreach (Object obj : m_FallbackUnits)
        {
            if (obj) GetGame().ObjectDelete(obj);
        }
        m_FallbackUnits.Clear();
        GroundZeroLogging.Info("AI", "Cleanup AI bridge-owned units");
    }
}
