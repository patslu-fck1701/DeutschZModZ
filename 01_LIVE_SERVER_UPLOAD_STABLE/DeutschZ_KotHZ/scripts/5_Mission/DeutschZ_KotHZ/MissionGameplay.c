/*
DeutschZ ModZ
Eigenstaendige Implementierung fuer DeutschZ.
Autor/Eigentuemer: Patrick Sluzalek / fck1701.
Keine direkte Codeuebernahme aus Drittquellen.
Oeffentliche Quellen werden nur zur Konzept- und API-Verifikation genutzt.
*/

modded class MissionGameplay
{
    protected ref DeutschZKotHZHUD m_DeutschZKotHZHUD;
    protected int m_DeutschZKotHZLastRenderedUpdateMs;

    void MissionGameplay()
    {
        m_DeutschZKotHZLastRenderedUpdateMs = -1;
    }

    override void OnInit()
    {
        super.OnInit();
        DeutschZKotHZ_EnsureHUD();
    }

    override void OnMissionStart()
    {
        super.OnMissionStart();
        DeutschZKotHZ_EnsureHUD();
    }

    override void OnUpdate(float timeslice)
    {
        super.OnUpdate(timeslice);
        DeutschZKotHZ_UpdateHUDFromClientState();
    }

    void DeutschZKotHZ_EnsureHUD()
    {
        if (!m_DeutschZKotHZHUD)
        {
            m_DeutschZKotHZHUD = new DeutschZKotHZHUD();
        }
    }

    void DeutschZKotHZ_UpdateHUDFromClientState()
    {
        DeutschZKotHZ_EnsureHUD();
        if (!m_DeutschZKotHZHUD)
        {
            return;
        }

        int lastUpdateMs = DeutschZKotHZClientHUDState.GetLastUpdateMs();
        if (lastUpdateMs == m_DeutschZKotHZLastRenderedUpdateMs)
        {
            return;
        }

        m_DeutschZKotHZLastRenderedUpdateMs = lastUpdateMs;

        bool active = DeutschZKotHZClientHUDState.IsActive();
        string zoneName = DeutschZKotHZClientHUDState.GetZoneName();
        int percent = DeutschZKotHZClientHUDState.GetPercent();
        int seconds = DeutschZKotHZClientHUDState.GetSeconds();
        int totalSeconds = DeutschZKotHZClientHUDState.GetTotalSeconds();
        int playersInZone = DeutschZKotHZClientHUDState.GetPlayersInZone();
        string state = DeutschZKotHZClientHUDState.GetState();

        m_DeutschZKotHZHUD.Update(active, zoneName, percent, seconds, totalSeconds, playersInZone, state);
    }
}
