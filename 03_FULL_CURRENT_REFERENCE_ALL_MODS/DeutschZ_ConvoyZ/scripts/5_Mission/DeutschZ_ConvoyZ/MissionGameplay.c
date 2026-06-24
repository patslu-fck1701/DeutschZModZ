/* DeutschZ ConvoyZ MissionGameplay HUD updater. */

modded class MissionGameplay
{
    protected ref DeutschZConvoyZHUD m_DeutschZConvoyZHUD;
    protected int m_DeutschZConvoyZLastRenderedUpdateMs;

    void MissionGameplay()
    {
        m_DeutschZConvoyZLastRenderedUpdateMs = -1;
    }

    override void OnInit()
    {
        super.OnInit();
        DeutschZConvoyZ_EnsureHUD();
    }

    override void OnMissionStart()
    {
        super.OnMissionStart();
        DeutschZConvoyZ_EnsureHUD();
    }

    override void OnUpdate(float timeslice)
    {
        super.OnUpdate(timeslice);
        DeutschZConvoyZ_UpdateHUDFromClientState();
    }

    void DeutschZConvoyZ_EnsureHUD()
    {
        if (!m_DeutschZConvoyZHUD)
            m_DeutschZConvoyZHUD = new DeutschZConvoyZHUD();
    }

    void DeutschZConvoyZ_UpdateHUDFromClientState()
    {
        DeutschZConvoyZ_EnsureHUD();
        if (!m_DeutschZConvoyZHUD) return;

        int lastUpdateMs = DeutschZConvoyZClientHUDState.GetLastUpdateMs();
        if (lastUpdateMs == m_DeutschZConvoyZLastRenderedUpdateMs) return;
        m_DeutschZConvoyZLastRenderedUpdateMs = lastUpdateMs;

        m_DeutschZConvoyZHUD.Update(DeutschZConvoyZClientHUDState.IsActive(), DeutschZConvoyZClientHUDState.GetTitle(), DeutschZConvoyZClientHUDState.GetStatus(), DeutschZConvoyZClientHUDState.GetPercent(), DeutschZConvoyZClientHUDState.GetDetail());
    }
}
