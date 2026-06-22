/*
    DeutschZ_GroundZero
    Owner: Patrick Sluzalek / fck1701
    Module: 4_World / GroundZeroMarkerManager
    Purpose: Marker intent layer with stable one-marker-per-logical-target handling.
    Dependencies: DayZ scripts; optional Expansion Marker API only through DeutschZ Core/Bridge.
    Compliance: Original DeutschZ implementation. No copied foreign mod code, assets, configs or stubs.
*/

class GroundZeroMarkerManager
{
    protected GroundZeroConfig m_Config;
    protected GroundZeroPersistentState m_State;
    protected ref map<string, bool> m_KnownMarkers;
    protected ref map<string, float> m_LastMarkerUpdate;

    void GroundZeroMarkerManager(GroundZeroConfig cfg, GroundZeroPersistentState state)
    {
        m_Config = cfg;
        m_State = state;
        m_KnownMarkers = new map<string, bool>();
        m_LastMarkerUpdate = new map<string, float>();
    }

    protected void UpsertMarker(string markerId, string label, vector position)
    {
        if (!m_Config.MarkersEnabled()) return;
        if (markerId == "") return;

        float now = GetGame().GetTime() * 0.001;
        float last = 0;
        if (m_LastMarkerUpdate.Find(markerId, last) && now - last < m_Config.MarkerUpdateIntervalSeconds)
            return;

        bool prefer3D = m_Config.Use3DMarker();
        bool ok;
        if (m_KnownMarkers.Contains(markerId))
        {
            ok = GroundZeroCoreBridge.UpdateUnifiedEventMarker(markerId, position, prefer3D);
            if (!ok)
            {
                m_KnownMarkers.Remove(markerId);
                ok = GroundZeroCoreBridge.CreateUnifiedEventMarker(markerId, label, position, prefer3D);
                if (ok) m_KnownMarkers.Set(markerId, prefer3D);
                GroundZeroLogging.Info("Markers", "Marker recreate id=" + markerId + " label=" + label + " 3d=" + prefer3D.ToString() + " pos=" + position.ToString());
            }
            else
            {
                GroundZeroLogging.Debug("Markers", "Marker update id=" + markerId + " pos=" + position.ToString());
            }
        }
        else
        {
            ok = GroundZeroCoreBridge.CreateUnifiedEventMarker(markerId, label, position, prefer3D);
            if (ok) m_KnownMarkers.Set(markerId, prefer3D);
            GroundZeroLogging.Info("Markers", "Marker create id=" + markerId + " label=" + label + " 3d=" + prefer3D.ToString() + " pos=" + position.ToString());
        }

        m_LastMarkerUpdate.Set(markerId, now);
    }

    void UpdateStageMarker(vector position, string label, float radius)
    {
        // FIX25: one logical stage marker only. Remove old human-readable ids that could
        // remain visible after older Signalstation/Sendestation builds.
        GroundZeroCoreBridge.DeleteRawMarker("GroundZero_Signalstation");
        GroundZeroCoreBridge.DeleteRawMarker("GroundZero_Sendestation");
        GroundZeroCoreBridge.DeleteRawMarker("GroundZero_3D_Signalstation");
        GroundZeroCoreBridge.DeleteRawMarker("GroundZero_3D_Sendestation");
        GroundZeroCoreBridge.DeleteRawMarker("Signalstation_stage");
        GroundZeroCoreBridge.DeleteRawMarker("Sendestation_stage");
        UpsertMarker("stage", label, position);
    }

    void UpdateCarrierMarker(string playerId, vector position, float radius)
    {
        if (!m_Config.ShowCarrierMarker()) return;
        UpsertMarker("carrier_" + playerId, "GroundZero Carrier", position);
    }

    void UpdateFinalMarker(vector position)
    {
        if (!m_Config.ShowFinalMarker()) return;
        UpsertMarker("final", "GroundZero Final Facility", position);
    }

    void UpdateExtractionMarker(vector position)
    {
        if (!m_Config.ShowExtractionMarker()) return;
        UpsertMarker("extraction", "GroundZero Extraction", position);
    }

    void UpdateDroppedItemMarker(GroundZeroDroppedItemRuntime drop)
    {
        if (!m_Config.ShowDroppedItemMarker()) return;
        if (!drop || drop.Resolved) return;

        string markerId = "drop_" + drop.ItemClass + "_" + drop.DroppedAt.ToString();
        UpsertMarker(markerId, "GroundZero Drop", drop.Position);
    }

    void TickDroppedItems()
    {
        foreach (GroundZeroDroppedItemRuntime drop : m_State.DroppedItems)
        {
            UpdateDroppedItemMarker(drop);
        }
    }

    void Cleanup()
    {
        GroundZeroCoreBridge.CleanupMarkers();
        m_KnownMarkers.Clear();
        m_LastMarkerUpdate.Clear();
        GroundZeroLogging.Info("Markers", "Cleanup markers");
    }
}
