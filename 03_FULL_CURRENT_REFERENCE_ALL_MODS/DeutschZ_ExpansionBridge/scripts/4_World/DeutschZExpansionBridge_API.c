/*
    DeutschZ ModZ
    Autor/Eigentuemer: Patrick Sluzalek / fck1701
    Projekt: DeutschZ
    Zweck: Eigene DeutschZ-Implementierung fuer Core, ExpansionBridge und Event-Module.
    Quellen-/Konzeptnachweis: Eigenentwickelte Struktur; DayZ, CF und Expansion nur als Laufzeit-API/Abhaengigkeit.
    No-Copy-Bestaetigung: Kein Code, keine Assets und keine Configs aus fremden Mods kopiert.

    FIX31:
    - MarkerProvider nutzt die vorhandene DayZ Expansion Navigation Marker API.
    - Event-Mods rufen weiterhin nur DeutschZ Core/Bridge auf.
    - Keine physischen Marker-Fallbackobjekte.
*/

class DeutschZExpansionBridge_MarkerProvider: DeutschZCore_MarkerProviderAPI
{
    protected ref map<string, vector> m_Markers;
    protected ref map<string, int> m_MarkerIs3D;
    protected ref map<string, string> m_MarkerLabels;
    protected ref map<string, int> m_MarkerColors;

    void DeutschZExpansionBridge_MarkerProvider()
    {
        m_Markers = new map<string, vector>;
        m_MarkerIs3D = new map<string, int>;
        m_MarkerLabels = new map<string, string>;
        m_MarkerColors = new map<string, int>;
    }

    protected ExpansionMarkerModule GetExpansionMarkerModuleSafe()
    {
        return ExpansionMarkerModule.GetModuleInstance();
    }

    protected string GetIconName(string id)
    {
        // FIX44: event-specific marker symbols. Keep conservative names and fall back to Territory.
        if (id.IndexOf("KotHZ_") == 0) return "Territory";
        if (id.IndexOf("ConvoyZ_") == 0) return "Vehicle";
        if (id.IndexOf("GroundZero_") == 0) return "ContaminatedArea";
        if (id.IndexOf("CourierZ_") == 0) return "Deliver";
        return "Territory";
    }

    protected bool CreateOrReplaceExpansionMarker(string id, string label, vector position, int colorARGB, bool marker3D)
    {
        if (!GetGame() || !GetGame().IsClient() && !GetGame().IsServer())
            return false;

        ExpansionMarkerModule module = GetExpansionMarkerModuleSafe();
        if (!module)
        {
            DeutschZCore_Log.Warn("ExpansionBridge", "ExpansionMarkerModule unavailable for id=" + id);
            return false;
        }

        module.RemoveServerMarker(id);
        ExpansionMarkerData marker = module.CreateServerMarker(label, GetIconName(id), position, colorARGB, marker3D, id);
        if (!marker)
        {
            DeutschZCore_Log.Warn("ExpansionBridge", "Expansion server marker create failed id=" + id + " label=" + label);
            return false;
        }

        DeutschZCore_Log.Info("ExpansionBridge", "Expansion server marker created id=" + id + " label=" + label + " 3d=" + marker3D.ToString() + " pos=" + position.ToString());
        return true;
    }

    override bool CreateMarker(string id, string label, vector position, int colorARGB)
    {
        if (id == "")
            return false;

        m_Markers.Set(id, position);
        m_MarkerIs3D.Set(id, 0);
        m_MarkerLabels.Set(id, label);
        m_MarkerColors.Set(id, colorARGB);
        return CreateOrReplaceExpansionMarker(id, label, position, colorARGB, false);
    }

    override bool Create3DMarker(string id, string label, vector position, int colorARGB)
    {
        if (id == "")
            return false;

        m_Markers.Set(id, position);
        m_MarkerIs3D.Set(id, 1);
        m_MarkerLabels.Set(id, label);
        m_MarkerColors.Set(id, colorARGB);
        return CreateOrReplaceExpansionMarker(id, label, position, colorARGB, true);
    }

    override bool UpdateMarker(string id, vector position)
    {
        if (!m_Markers.Contains(id))
            return false;

        m_Markers.Set(id, position);
        int is3D = 0;
        m_MarkerIs3D.Find(id, is3D);
        string label = id;
        int color = 0xFFFF0000;
        if (m_MarkerLabels.Contains(id)) m_MarkerLabels.Find(id, label);
        if (m_MarkerColors.Contains(id)) m_MarkerColors.Find(id, color);
        return CreateOrReplaceExpansionMarker(id, label, position, color, is3D == 1);
    }

    override bool DeleteMarker(string id)
    {
        bool known = m_Markers.Contains(id);
        if (known)
            m_Markers.Remove(id);
        if (m_MarkerIs3D.Contains(id))
            m_MarkerIs3D.Remove(id);
        if (m_MarkerLabels.Contains(id))
            m_MarkerLabels.Remove(id);
        if (m_MarkerColors.Contains(id))
            m_MarkerColors.Remove(id);

        ExpansionMarkerModule module = GetExpansionMarkerModuleSafe();
        if (module)
            module.RemoveServerMarker(id);

        DeutschZCore_Log.Info("ExpansionBridge", "Expansion server marker delete request id=" + id);
        return known;
    }

    override void DeleteMarkersByPrefix(string prefix)
    {
        array<string> remove = new array<string>;
        foreach (string id, vector pos: m_Markers)
        {
            if (id.IndexOf(prefix) == 0)
                remove.Insert(id);
        }

        foreach (string removeId: remove)
        {
            DeleteMarker(removeId);
        }
    }
}

class DeutschZExpansionBridge_AIProvider: DeutschZCore_AIProviderAPI
{
    protected ref map<string, ref array<Object>> m_RuntimeObjects;

    void DeutschZExpansionBridge_AIProvider()
    {
        m_RuntimeObjects = new map<string, ref array<Object>>;
    }

    protected void Track(string eventId, Object obj)
    {
        if (!obj)
            return;

        array<Object> list;
        if (!m_RuntimeObjects.Find(eventId, list))
        {
            list = new array<Object>;
            m_RuntimeObjects.Insert(eventId, list);
        }

        list.Insert(obj);
    }

    override bool SpawnGuard(string eventId, string loadoutId, vector position)
    {
        if (!GetGame().IsServer())
            return false;

        string spawnClass = ResolveDeutschZGuardClassName();
        if (spawnClass == "")
        {
            DeutschZCore_Log.Warn("ExpansionBridge", "KotHZ guard AI spawn skipped: no Expansion AI class found in CfgVehicles.");
            return false;
        }

        vector p = position;
        p[1] = GetGame().SurfaceY(p[0], p[2]);

        Object obj = GetGame().CreateObjectEx(spawnClass, p, ECE_PLACE_ON_SURFACE | ECE_INITAI);
        if (!obj)
        {
            DeutschZCore_Log.Warn("ExpansionBridge", "KotHZ guard AI spawn failed class=" + spawnClass + " pos=" + p.ToString());
            return false;
        }

        EntityAI entity = EntityAI.Cast(obj);
        if (entity)
            ApplyDeutschZKotHZMilitaryLoadout(entity, loadoutId);

        Track(eventId, obj);
        DeutschZCore_Log.Info("ExpansionBridge", "spawned KotHZ guard AI event=" + eventId + " class=" + spawnClass + " loadout=" + loadoutId + " pos=" + p.ToString());
        return true;
    }

    protected string ResolveDeutschZGuardClassName()
    {
        ref array<string> candidates = new array<string>;
        candidates.Insert("eAI_SurvivorM_Boris");
        candidates.Insert("eAI_SurvivorM_Cyril");
        candidates.Insert("eAI_SurvivorM_Denis");
        candidates.Insert("eAI_SurvivorM_Elias");
        candidates.Insert("eAI_SurvivorM_Francis");
        candidates.Insert("eAI_SurvivorM_Guo");
        candidates.Insert("eAI_SurvivorM_Hassan");
        candidates.Insert("eAI_SurvivorM_Jose");
        candidates.Insert("eAI_SurvivorM_Kaito");
        candidates.Insert("eAI_SurvivorF_Eva");
        candidates.Insert("eAI_SurvivorF_Frida");

        foreach (string className : candidates)
        {
            if (className != "" && GetGame().ConfigIsExisting("CfgVehicles " + className))
                return className;
        }

        return "";
    }

    protected bool IsValidCfgVehicle(string className)
    {
        if (className == "")
            return false;
        return GetGame().ConfigIsExisting("CfgVehicles " + className);
    }

    protected EntityAI CreateBestAttachment(EntityAI owner, string slotName, array<string> candidates)
    {
        if (!owner || !candidates)
            return null;

        EntityAI existing = owner.FindAttachmentBySlotName(slotName);
        if (existing)
            GetGame().ObjectDelete(existing);

        foreach (string className : candidates)
        {
            if (!IsValidCfgVehicle(className))
                continue;

            EntityAI item = owner.GetInventory().CreateAttachment(className);
            if (item)
                return item;

            item = owner.GetInventory().CreateInInventory(className);
            if (item)
                return item;
        }

        return null;
    }

    protected EntityAI CreateCargoItem(EntityAI owner, array<string> candidates)
    {
        if (!owner || !candidates)
            return null;

        foreach (string className : candidates)
        {
            if (!IsValidCfgVehicle(className))
                continue;

            EntityAI item = owner.GetInventory().CreateInInventory(className);
            if (item)
                return item;
        }

        return null;
    }

    protected void CreateSimpleCargoItem(EntityAI owner, string className)
    {
        if (!owner || !IsValidCfgVehicle(className))
            return;
        owner.GetInventory().CreateInInventory(className);
    }

    protected void ApplyDeutschZKotHZMilitaryLoadout(EntityAI entity, string loadoutId)
    {
        if (!entity)
            return;

        // DeutschZ KotHZ v0.9.3: self-contained military/SNAFU-style AI loadout.
        // SNAFU classnames are attempted first when present; vanilla military classes keep the loadout safe on test servers.
        ref array<string> body = new array<string>;
        body.Insert("USMCJacket_Desert");
        body.Insert("USMCJacket_Woodland");
        body.Insert("BDUJacket");
        body.Insert("TTsKOJacket_Camo");
        EntityAI bodyItem = CreateBestAttachment(entity, "Body", body);

        ref array<string> legs = new array<string>;
        legs.Insert("USMCPants_Desert");
        legs.Insert("USMCPants_Woodland");
        legs.Insert("BDUPants");
        legs.Insert("TTSKOPants");
        CreateBestAttachment(entity, "Legs", legs);

        ref array<string> feet = new array<string>;
        feet.Insert("CombatBoots_Beige");
        feet.Insert("CombatBoots_Black");
        feet.Insert("CombatBoots_Brown");
        feet.Insert("CombatBoots_Green");
        CreateBestAttachment(entity, "Feet", feet);

        ref array<string> vest = new array<string>;
        vest.Insert("PlateCarrierVest");
        vest.Insert("HighCapacityVest_Olive");
        EntityAI vestItem = CreateBestAttachment(entity, "Vest", vest);
        if (vestItem)
        {
            ref array<string> pouches = new array<string>;
            pouches.Insert("PlateCarrierPouches");
            pouches.Insert("PlateCarrierHolster");
            CreateCargoItem(vestItem, pouches);
            CreateSimpleCargoItem(vestItem, "PlateCarrierPouches");
            CreateSimpleCargoItem(vestItem, "PlateCarrierHolster");
        }

        ref array<string> head = new array<string>;
        head.Insert("BallisticHelmet_Black");
        head.Insert("BallisticHelmet_Green");
        head.Insert("Mich2001Helmet");
        CreateBestAttachment(entity, "Headgear", head);

        ref array<string> back = new array<string>;
        back.Insert("CoyoteBag_Green");
        back.Insert("CoyoteBag_Brown");
        back.Insert("AssaultBag_Green");
        EntityAI bagItem = CreateBestAttachment(entity, "Back", back);

        ref array<string> gloves = new array<string>;
        gloves.Insert("TacticalGloves_Black");
        gloves.Insert("TacticalGloves_Green");
        gloves.Insert("TacticalGloves_Beige");
        CreateBestAttachment(entity, "Gloves", gloves);

        ref array<string> belt = new array<string>;
        belt.Insert("MilitaryBelt");
        CreateBestAttachment(entity, "Hips", belt);

        ref array<string> weapon = new array<string>;
        weapon.Insert("SNAFU_MK18_Black");
        weapon.Insert("SNAFU_HK416_Black");
        weapon.Insert("SNAFU_M4A1_Black");
        weapon.Insert("SNAFU_SCARH_Black");
        weapon.Insert("M4A1");
        weapon.Insert("M16A2");
        weapon.Insert("Aug");
        weapon.Insert("FAMAS");
        EntityAI weaponItem = CreateCargoItem(entity, weapon);
        if (weaponItem && bodyItem)
            bodyItem.GetInventory().CreateInInventory(weaponItem.GetType());

        EntityAI ammoTarget = entity;
        if (bagItem)
            ammoTarget = bagItem;

        CreateSimpleCargoItem(ammoTarget, "Mag_STANAG_60Rnd");
        CreateSimpleCargoItem(ammoTarget, "Mag_STANAG_30Rnd");
        CreateSimpleCargoItem(ammoTarget, "Mag_CMAG_40Rnd");
        CreateSimpleCargoItem(ammoTarget, "Mag_CMAG_30Rnd");
        CreateSimpleCargoItem(ammoTarget, "BandageDressing");
        CreateSimpleCargoItem(ammoTarget, "BandageDressing");
        CreateSimpleCargoItem(ammoTarget, "Battery9V");
        CreateSimpleCargoItem(ammoTarget, "NVGoggles");

        if (weaponItem)
        {
            ref array<string> optics = new array<string>;
            optics.Insert("ACOGOptic_6x");
            optics.Insert("ACOGOptic");
            optics.Insert("M68Optic");
            optics.Insert("ReflexOptic");
            CreateCargoItem(weaponItem, optics);
        }
    }

    override bool SpawnInfected(string eventId, string className, vector position)
    {
        if (!GetGame().IsServer() || className == "")
            return false;

        string spawnClass = className;
        if (!GetGame().ConfigIsExisting("CfgVehicles " + spawnClass))
            spawnClass = "ZmbM_usSoldier_Officer_Desert";

        vector p = position;
        p[1] = GetGame().SurfaceY(p[0], p[2]);

        Object obj = GetGame().CreateObjectEx(spawnClass, p, ECE_PLACE_ON_SURFACE | ECE_INITAI);
        if (!obj)
        {
            DeutschZCore_Log.Warn("ExpansionBridge", "infected spawn failed class=" + spawnClass + " pos=" + p.ToString());
            return false;
        }

        Track(eventId, obj);
        DeutschZCore_Log.Info("ExpansionBridge", "spawned fallback enemy event=" + eventId + " class=" + spawnClass + " pos=" + p.ToString());
        return true;
    }

    override bool CleanupEventAI(string eventId)
    {
        array<Object> list;
        if (!m_RuntimeObjects.Find(eventId, list))
            return false;

        foreach (Object obj: list)
        {
            if (obj)
                GetGame().ObjectDelete(obj);
        }

        m_RuntimeObjects.Remove(eventId);
        DeutschZCore_Log.Info("ExpansionBridge", "cleaned fallback enemies event=" + eventId);
        return true;
    }
}
