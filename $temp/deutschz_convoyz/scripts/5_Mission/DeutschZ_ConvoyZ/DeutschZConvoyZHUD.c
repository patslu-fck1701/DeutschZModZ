/* DeutschZ ConvoyZ client progress HUD. */

class DeutschZConvoyZHUD
{
    protected Widget m_Root;
    protected TextWidget m_Title;
    protected TextWidget m_Status;
    protected TextWidget m_ProgressText;
    protected TextWidget m_Detail;
    protected ProgressBarWidget m_Progress;

    void DeutschZConvoyZHUD()
    {
        m_Root = GetGame().GetWorkspace().CreateWidgets("DeutschZ_ConvoyZ/gui/layouts/DeutschZConvoyZ_Progress.layout");
        if (!m_Root)
        {
            Print("[DeutschZ_ConvoyZ] Progress HUD layout could not be loaded.");
            return;
        }

        m_Title = TextWidget.Cast(m_Root.FindAnyWidget("TitleText"));
        m_Status = TextWidget.Cast(m_Root.FindAnyWidget("StatusMsg"));
        m_ProgressText = TextWidget.Cast(m_Root.FindAnyWidget("ProgressText"));
        m_Detail = TextWidget.Cast(m_Root.FindAnyWidget("DetailText"));
        m_Progress = ProgressBarWidget.Cast(m_Root.FindAnyWidget("Progress"));
        Hide();
    }

    void Show()
    {
        if (m_Root) m_Root.Show(true);
    }

    void Hide()
    {
        if (m_Root) m_Root.Show(false);
    }

    void Update(bool active, string title, string status, int percent, string detail)
    {
        if (!m_Root) return;
        if (!active)
        {
            Hide();
            return;
        }

        Show();
        percent = Math.Clamp(percent, 0, 100);
        if (m_Title) m_Title.SetText(title);
        if (m_Status) m_Status.SetText(status);
        if (m_Progress) m_Progress.SetCurrent(percent);
        if (m_ProgressText) m_ProgressText.SetText(percent.ToString() + "%");
        if (m_Detail) m_Detail.SetText(detail);
    }
}
