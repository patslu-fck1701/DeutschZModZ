/*
DeutschZ ModZ
Eigenstaendige Implementierung fuer DeutschZ.
Autor/Eigentuemer: Patrick Sluzalek / fck1701.
Projekt: DeutschZ.
Modul: DeutschZ_ConvoyZ.
Zweck der Datei: Serverseitige ConvoyZ-Eventlogik, Ablauf, Status und Sicherheitspruefung.
Quellen-/Konzeptnachweis: Eigene DeutschZ-Implementierung; DayZ/CF/Expansion werden nur als Laufzeit-Abhaengigkeit/API genutzt.
Keine direkte Codeuebernahme aus Drittquellen.
*/

class DeutschZConvoyZAIManager
{
    void StartWaves(DeutschZConvoyZConfig cfg, DeutschZConvoyZRuntimeState state)
    {
        if (!cfg || !state || cfg.Settings.EnableAiWaves == 0) return;
        state.CurrentWaveIndex = 0;
        state.NextWaveAt = GetGame().GetTime();
        Tick(cfg, state);
    }

    void Tick(DeutschZConvoyZConfig cfg, DeutschZConvoyZRuntimeState state)
    {
        ScanDeadAI(state);
        if (!cfg || !state || !cfg.EventData.AIWaves) return;
        if (state.CurrentWaveIndex >= cfg.EventData.AIWaves.Count()) return;
        if (GetGame().GetTime() < state.NextWaveAt) return;
        SpawnWave(cfg.EventData.AIWaves.Get(state.CurrentWaveIndex), cfg, state);
        state.CurrentWaveIndex++;
        state.NextWaveAt = GetGame().GetTime() + cfg.Settings.WaveDelaySeconds * 1000;
    }

    void SpawnWave(DeutschZConvoyZAIWaveDef wave, DeutschZConvoyZConfig cfg, DeutschZConvoyZRuntimeState state)
    {
        if (!wave || !state) return;
        bool usedBridge = false;
        if (wave.DeutschZAIProfileId != "") usedBridge = DeutschZConvoyZ_AIProviderSpawnForConvoy(state.EventId, cfg.EventData.EventIdPrefix, cfg.EventData.EventIdPrefix, wave.DeutschZAIProfileId);
        if (usedBridge)
        {
            DeutschZConvoyZLogger.Log("EventAISpawnStarted", state.EventId, DeutschZConvoyZ_StateName(state.CurrentState), "", cfg.EventData.EventCenter, "OK", "DeutschZ AI provider " + wave.WaveId);
            return;
        }
        if (!wave.SpawnPoints || wave.SpawnPoints.Count() == 0) return;
        for (int i = 0; i < wave.Count; i++)
        {
            DeutschZConvoyZSpawnPoint sp = wave.SpawnPoints.Get(i % wave.SpawnPoints.Count());
            vector p = sp.Position;
            float offsetX = Math.RandomFloat(-5, 5);
            float offsetZ = Math.RandomFloat(-5, 5);
            p[0] = p[0] + offsetX;
            p[2] = p[2] + offsetZ;
            p[1] = GetGame().SurfaceY(p[0], p[2]);
            string aiClass = NormalizeAIClassName(wave.AIClassName);
            if (!GetGame().ConfigIsExisting("CfgVehicles " + aiClass))
            {
                DeutschZConvoyZLogger.Log("AIClassFallback", state.EventId, DeutschZConvoyZ_StateName(state.CurrentState), "", p, "WARN", aiClass + " missing, using vanilla infected fallback");
                aiClass = "ZmbM_usSoldier_Officer_Desert";
            }
            Object ai = GetGame().CreateObjectEx(aiClass, p, ECE_SETUP | ECE_CREATEPHYSICS | ECE_UPDATEPATHGRAPH);
            if (ai)
            {
                ai.SetOrientation(sp.Orientation);
                ApplyPoliceLoadout(ai, wave);
                state.SpawnedAI.Insert(ai);
                DeutschZConvoyZLogger.Log("AIRegistered", state.EventId, DeutschZConvoyZ_StateName(state.CurrentState), "", p, "OK", aiClass);
            }
        }
    }



    void ApplyPoliceLoadout(Object aiObject, DeutschZConvoyZAIWaveDef wave)
    {
        if (!aiObject || !wave) return;

        string loadoutName = wave.LoadoutName;
        if (loadoutName == "") loadoutName = "PoliceLoadout";

        if (GetGame().IsKindOf(aiObject.GetType(), "ZombieBase") || GetGame().IsKindOf(aiObject.GetType(), "DayZInfected"))
        {
            DeutschZConvoyZLogger.Log("AILoadoutSkipped", "", "", "", aiObject.GetPosition(), "OK", "Infected fallback has no inventory loadout: " + aiObject.GetType());
            return;
        }

        EntityAI ai = EntityAI.Cast(aiObject);
        if (!ai || !ai.GetInventory())
        {
            DeutschZConvoyZLogger.Log("AILoadoutSkipped", "", "", "", aiObject.GetPosition(), "WARN", "No EntityAI inventory for " + aiObject.GetType());
            return;
        }

        ApplyDeutschZMilitaryLoadout(ai, loadoutName);
        DeutschZConvoyZLogger.Log("AILoadoutApplied", "", "", "", aiObject.GetPosition(), "OK", "DeutschZ loadout '" + loadoutName + "' applied where classes existed");
    }

    void ApplyDeutschZMilitaryLoadout(EntityAI ai, string loadoutName)
    {
        if (!ai) return;

        SpawnLoadoutItemOrFallback(ai, "USMCJacket_Woodland", "BDUJacket");
        SpawnLoadoutItemOrFallback(ai, "USMCPants_Woodland", "BDUPants");
        SpawnLoadoutItemOrFallback(ai, "CombatBoots_Green", "CombatBoots_Black");
        SpawnLoadoutItemOrFallback(ai, "PlateCarrierVest", "HighCapacityVest_Olive");
        SpawnLoadoutItem(ai, "PlateCarrierPouches");
        SpawnLoadoutItem(ai, "PlateCarrierHolster");
        SpawnLoadoutItemOrFallback(ai, "BallisticHelmet_Green", "Mich2001Helmet");
        SpawnLoadoutItemOrFallback(ai, "TacticalGloves_Green", "WorkingGloves_Black");
        SpawnLoadoutItem(ai, "BandageDressing");
        SpawnLoadoutItem(ai, "Morphine");

        if (loadoutName == "DZCV_SNAFU_Heavy" || loadoutName == "DZCV_MilitaryHeavy")
        {
            SpawnLoadoutItemOrFallback(ai, "Snafu_ScarH_Black_GUN", "M4A1");
            SpawnLoadoutItemOrFallback(ai, "SNAFU_ScarH_100RND_Mag_Black", "Mag_STANAG_60Rnd");
            SpawnLoadoutItemOrFallback(ai, "SNAFU_ScarH_100RND_Mag_Black", "Mag_STANAG_60Rnd");
            SpawnLoadoutItemOrFallback(ai, "SNAFU_HNightforce", "ACOGOptic");
            SpawnLoadoutItem(ai, "AmmoBox_308Win_20Rnd");
            return;
        }

        if (loadoutName == "DZCV_SNAFU_Assault" || loadoutName == "DZCV_MilitaryRifleman")
        {
            SpawnLoadoutItemOrFallback(ai, "SNAFU_HK416_Black", "M4A1");
            SpawnLoadoutItemOrFallback(ai, "SNAFU_HK416_Mag", "Mag_STANAG_30Rnd");
            SpawnLoadoutItemOrFallback(ai, "SNAFU_HK416_Mag", "Mag_STANAG_30Rnd");
            SpawnLoadoutItemOrFallback(ai, "SNAFU_EOTech_EXPS3", "M68Optic");
            SpawnLoadoutItem(ai, "AmmoBox_556x45_20Rnd");
            return;
        }

        // Default / light convoy guard.
        SpawnLoadoutItemOrFallback(ai, "SNAFU_MK18_Black", "AK74");
        SpawnLoadoutItemOrFallback(ai, "SNAFU_MK18_Mag", "Mag_AK74_30Rnd");
        SpawnLoadoutItemOrFallback(ai, "SNAFU_MK18_Mag", "Mag_AK74_30Rnd");
        SpawnLoadoutItemOrFallback(ai, "SNAFU_EOTech_EXPS3", "KobraOptic");
        SpawnLoadoutItem(ai, "Ammo_545x39");
    }

    bool IsLoadoutClassConfigured(string className)
    {
        if (className == "") return false;
        if (GetGame().ConfigIsExisting("CfgVehicles " + className)) return true;
        if (GetGame().ConfigIsExisting("CfgWeapons " + className)) return true;
        if (GetGame().ConfigIsExisting("CfgMagazines " + className)) return true;
        return false;
    }

    bool TrySpawnLoadoutItem(EntityAI ai, string className)
    {
        if (!ai || className == "") return false;
        if (DeutschZCore_UnsafeClassGuard.IsBlockedClass(className)) return false;
        if (!IsLoadoutClassConfigured(className)) return false;
        EntityAI item = ai.GetInventory().CreateInInventory(className);
        return item != null;
    }

    void SpawnLoadoutItem(EntityAI ai, string className)
    {
        TrySpawnLoadoutItem(ai, className);
    }

    void SpawnLoadoutItemOrFallback(EntityAI ai, string preferred, string fallback)
    {
        if (TrySpawnLoadoutItem(ai, preferred)) return;
        TrySpawnLoadoutItem(ai, fallback);
    }

    string NormalizeAIClassName(string className)
    {
        if (className == "") return DeutschZConvoyZConstants.DEFAULT_EXPANSION_AI_CLASS;
        if (className.IndexOf("eAI_") == 0) return className;
        if (className.IndexOf("SurvivorM_") == 0) return "eAI_" + className;
        if (className.IndexOf("SurvivorF_") == 0) return "eAI_" + className;
        return className;
    }

    void ScanDeadAI(DeutschZConvoyZRuntimeState state)
    {
        if (!state || !state.SpawnedAI) return;
        for (int i = state.SpawnedAI.Count() - 1; i >= 0; i--)
        {
            Object ai = state.SpawnedAI.Get(i);
            if (!ai)
            {
                state.SpawnedAI.Remove(i);
                state.CurrentKills++;
                DeutschZConvoyZLogger.Log("AIKilled", state.EventId, DeutschZConvoyZ_StateName(state.CurrentState), "", "0 0 0", "OK", state.CurrentKills.ToString() + "/" + state.RequiredKills.ToString());
                continue;
            }
            if (ai.IsDamageDestroyed())
            {
                vector pos = ai.GetPosition();
                state.SpawnedAI.Remove(i);
                state.CurrentKills++;
                DeutschZConvoyZLogger.Log("AIKilled", state.EventId, DeutschZConvoyZ_StateName(state.CurrentState), "", pos, "OK", state.CurrentKills.ToString() + "/" + state.RequiredKills.ToString());
            }
        }
    }

    void OnKilled(DeutschZConvoyZRuntimeState state, Object victim, PlayerBase killer)
    {
        if (!state || !victim || !state.SpawnedAI) return;
        int idx = state.SpawnedAI.Find(victim);
        if (idx < 0) return;
        state.SpawnedAI.Remove(idx);
        state.CurrentKills++;
        string pid = "";
        if (killer && killer.GetIdentity()) pid = killer.GetIdentity().GetPlainId();
        DeutschZConvoyZLogger.Log("AIKilled", state.EventId, DeutschZConvoyZ_StateName(state.CurrentState), pid, victim.GetPosition(), "OK", state.CurrentKills.ToString() + "/" + state.RequiredKills.ToString());
    }
}
