/*
    DeutschZ_GroundZero
    Owner: Patrick Sluzalek / fck1701
    Module: 4_World / GroundZeroExtractionManager
    Purpose: Research core spawn, extraction zone timer and success/failure state.
    Dependencies: DayZ scripts; optional marker API through GroundZeroMarkerManager only.
    Compliance: Original DeutschZ implementation. No copied foreign mod code, assets, configs or stubs.
*/

class GroundZeroExtractionManager
{
    protected GroundZeroConfig m_Config;
    protected GroundZeroPersistentState m_State;
    protected GroundZeroNotificationManager m_Notifications;
    protected GroundZeroMarkerManager m_Markers;
    protected GroundZeroItemManager m_Items;
    protected float m_Start;
    protected bool m_Active;
    protected bool m_Success;
    protected bool m_Failed;
    protected EntityAI m_ResearchCore;

    void GroundZeroExtractionManager(GroundZeroConfig cfg, GroundZeroPersistentState state, GroundZeroNotificationManager n, GroundZeroMarkerManager markers, GroundZeroItemManager items)
    {
        m_Config = cfg;
        m_State = state;
        m_Notifications = n;
        m_Markers = markers;
        m_Items = items;
    }

    void StartExtraction()
    {
        if (m_Active) return;
        m_Active = true;
        m_Success = false;
        m_Failed = false;
        m_Start = GetGame().GetTime() * 0.001;
        m_State.ExtractionStarted = true;
        m_State.ExtractionStartedAt = m_Start;

        if (m_State.ExtractionPosition == "0 0 0")
            m_State.ExtractionPosition = m_Config.PossibleExtractionPositions.Get(Math.RandomInt(0, m_Config.PossibleExtractionPositions.Count()));

        m_ResearchCore = m_Items.SpawnCampaignItem(m_Config.ItemFinalResearchCore, m_State.ExtractionPosition);
        m_Markers.UpdateExtractionMarker(m_State.ExtractionPosition);
        m_Notifications.Broadcast("Extraktion aktiv");
        GroundZeroLogging.Info("Extraction", "Started pos=" + m_State.ExtractionPosition.ToString());
    }

    void Tick()
    {
        if (!m_Active) return;

        float now = GetGame().GetTime() * 0.001;
        if (now - m_Start >= m_Config.ExtractionDurationSeconds)
        {
            m_Success = true;
            m_Active = false;
            m_State.ExtractionSuccess = true;
            GroundZeroLogging.Info("Extraction", "Extraction succeeded");
        }
    }

    bool IsSuccess()
    {
        return m_Success;
    }

    bool IsFailed()
    {
        return m_Failed;
    }

    void Cleanup()
    {
        if (m_ResearchCore)
        {
            GetGame().ObjectDelete(m_ResearchCore);
            m_ResearchCore = null;
        }
        m_Active = false;
    }
}
