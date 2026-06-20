/*
    DeutschZ_GroundZero
    Owner: Patrick Sluzalek / fck1701
    Module: 4_World / GroundZeroMarkerManager
    Purpose: Marker intent layer for stages, carriers, drops, final facility and extraction.
    Dependencies: DayZ scripts; optional Expansion Marker API only through adapter methods.
    Compliance: Original DeutschZ implementation. No copied foreign mod code, assets, configs or stubs.
*/

class GroundZeroMarkerManager
{
    protected GroundZeroConfig m_Config;
    protected GroundZeroPersistentState m_State;

    void GroundZeroMarkerManager(GroundZeroConfig cfg, GroundZeroPersistentState state)
    {
        m_Config = cfg;
        m_State = state;
    }

    void UpdateStageMarker(vector position, string label, float radius)
    {
        if (!m_Config.EnableMapMarkers) return;
        GroundZeroLogging.Info("Markers", "Stage marker label=" + label + " radius=" + radius.ToString() + " pos=" + position.ToString());
        GroundZeroCoreBridge.CreateEventMarker("stage", label, position);
    }

    void UpdateCarrierMarker(string playerId, vector position, float radius)
    {
        if (!m_Config.EnableMapMarkers) return;

        if (radius <= 0)
            GroundZeroLogging.Info("Markers", "Carrier exact marker player=" + playerId + " pos=" + position.ToString());
        else
            GroundZeroLogging.Info("Markers", "Carrier search marker player=" + playerId + " radius=" + radius.ToString() + " pos=" + position.ToString());

        GroundZeroCoreBridge.CreateEventMarker("carrier_" + playerId, "GroundZero Carrier", position);
    }

    void UpdateFinalMarker(vector position)
    {
        if (!m_Config.EnableMapMarkers) return;
        GroundZeroLogging.Info("Markers", "Final facility marker pos=" + position.ToString());
        GroundZeroCoreBridge.CreateEventMarker("final", "GroundZero Final Facility", position);
    }

    void UpdateExtractionMarker(vector position)
    {
        if (!m_Config.EnableMapMarkers) return;
        GroundZeroLogging.Info("Markers", "Extraction marker pos=" + position.ToString());
        GroundZeroCoreBridge.CreateEventMarker("extraction", "GroundZero Extraction", position);
    }

    void UpdateDroppedItemMarker(GroundZeroDroppedItemRuntime drop)
    {
        if (!m_Config.EnableMapMarkers) return;
        if (!drop || drop.Resolved) return;

        float age = GetGame().GetTime() * 0.001 - drop.DroppedAt;
        if (age < m_Config.DroppedItemMarkerLargeSeconds)
            GroundZeroLogging.Debug("Markers", "Large dropped-item marker " + drop.ItemClass + " radius=" + m_Config.DroppedItemLargeRadius.ToString() + " pos=" + drop.Position.ToString());
        else if (age < m_Config.DroppedItemMarkerSmallSeconds)
            GroundZeroLogging.Debug("Markers", "Small dropped-item marker " + drop.ItemClass + " radius=" + m_Config.DroppedItemSmallRadius.ToString() + " pos=" + drop.Position.ToString());
        else
            GroundZeroLogging.Debug("Markers", "Exact dropped-item marker " + drop.ItemClass + " pos=" + drop.Position.ToString());
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
        GroundZeroLogging.Info("Markers", "Cleanup markers");
    }
}
