/*
    DeutschZ_GroundZero
    Owner: Patrick Sluzalek / fck1701
    Module: 5_Mission / GroundZeroHUD
    Purpose: Client status/progress bar for Signalstation and stage objectives.
    Compliance: Original DeutschZ implementation. No copied foreign mod code, assets, configs or stubs.
*/

class GroundZeroHUD
{
    protected Widget m_Root;
    protected TextWidget m_Title;
    protected TextWidget m_Status;
    protected TextWidget m_PlayerCount;
    protected TextWidget m_ProgressText;
    protected ProgressBarWidget m_Progress;

    void GroundZeroHUD()
    {
        m_Root = GetGame().GetWorkspace().CreateWidgets("DeutschZ_GroundZero/gui/layouts/GroundZero_Progress.layout");
        if (!m_Root)
        {
            Print("[DeutschZ_GroundZero] Progress HUD layout could not be loaded: DeutschZ_GroundZero/gui/layouts/GroundZero_Progress.layout");
            return;
        }

        m_Title = TextWidget.Cast(m_Root.FindAnyWidget("TitleText"));
        m_Status = TextWidget.Cast(m_Root.FindAnyWidget("StatusMsg"));
        m_PlayerCount = TextWidget.Cast(m_Root.FindAnyWidget("PlayerCount"));
        m_ProgressText = TextWidget.Cast(m_Root.FindAnyWidget("ProgressText"));
        m_Progress = ProgressBarWidget.Cast(m_Root.FindAnyWidget("Progress"));
        Hide();
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

    void Update(bool active, string title, int percent, int current, int total, int playersNear, string state)
    {
        if (!m_Root)
            return;

        if (!active)
        {
            Hide();
            return;
        }

        Show();
        percent = Math.Clamp(percent, 0, 100);

        if (m_Title)
            m_Title.SetText("DeutschZ GroundZero - " + title);

        if (m_Status)
            m_Status.SetText(state);

        if (m_Progress)
            m_Progress.SetCurrent(percent);

        if (m_ProgressText)
            m_ProgressText.SetText(percent.ToString() + "%");

        if (m_PlayerCount)
            m_PlayerCount.SetText("Spieler im Bereich: " + playersNear.ToString() + " | Fortschritt: " + current.ToString() + " / " + total.ToString());
    }
}
