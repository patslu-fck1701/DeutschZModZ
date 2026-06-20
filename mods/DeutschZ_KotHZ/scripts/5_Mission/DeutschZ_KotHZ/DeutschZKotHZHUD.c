/*
DeutschZ ModZ
Eigenstaendige Implementierung fuer DeutschZ.
Autor/Eigentuemer: Patrick Sluzalek / fck1701.
Keine direkte Codeuebernahme aus Drittquellen.
Oeffentliche Quellen werden nur zur Konzept- und API-Verifikation genutzt.
*/

class DeutschZKotHZHUD
{
    protected Widget m_Root;
    protected TextWidget m_Title;
    protected TextWidget m_Status;
    protected TextWidget m_PlayerCount;
    protected TextWidget m_ProgressText;
    protected ProgressBarWidget m_Progress;

    void DeutschZKotHZHUD()
    {
        // v1.0.19: use the same bottom-right progress layout for the direct HUD path.
        // This makes the statusbar visible even if CF RPCManager/plugin registration does not fire on a client.
        m_Root = GetGame().GetWorkspace().CreateWidgets("DeutschZ_KotHZ/gui/layouts/DeutschZKotHZ_Progress.layout");
        if (!m_Root)
        {
            Print("[DeutschZ_KotHZ] Progress HUD layout could not be loaded: DeutschZ_KotHZ/gui/layouts/DeutschZKotHZ_Progress.layout");
            return;
        }

        m_Title = TextWidget.Cast(m_Root.FindAnyWidget("TitleText"));
        m_Status = TextWidget.Cast(m_Root.FindAnyWidget("StatusMsg"));
        m_PlayerCount = TextWidget.Cast(m_Root.FindAnyWidget("PlayerCount"));
        m_ProgressText = TextWidget.Cast(m_Root.FindAnyWidget("ProgressText"));
        m_Progress = ProgressBarWidget.Cast(m_Root.FindAnyWidget("Progress"));
        Hide();
        Print("[DeutschZ_KotHZ] Bottom-right progress HUD created via direct RPC path.");
    }

    void Show()
    {
        if (m_Root)
            m_Root.Show(true);
    }

    void Hide()
    {
        if (m_Root)
            m_Root.Show(false);
    }

    void Update(bool active, string zoneName, int percent, int seconds, int totalSeconds, int playersInZone, string state)
    {
        if (!m_Root)
            return;

        if (!active)
        {
            Hide();
            return;
        }

        Show();

        if (m_Title)
            m_Title.SetText("DeutschZ KotH - " + zoneName);

        if (m_Status)
            m_Status.SetText(state);

        if (m_Progress)
            m_Progress.SetCurrent(Math.Clamp(percent, 0, 100));

        if (m_ProgressText)
            m_ProgressText.SetText(Math.Clamp(percent, 0, 100).ToString() + "%");

        if (m_PlayerCount)
        {
            string timeText = FormatTime(seconds) + " / " + FormatTime(totalSeconds);
            m_PlayerCount.SetText("Spieler: " + playersInZone.ToString() + " | Zeit: " + timeText);
        }
    }

    protected string FormatTime(int totalSeconds)
    {
        int mins = totalSeconds / 60;
        int secs = totalSeconds % 60;
        string secText = secs.ToString();
        if (secs < 10)
            secText = "0" + secText;

        return mins.ToString() + ":" + secText;
    }
}
