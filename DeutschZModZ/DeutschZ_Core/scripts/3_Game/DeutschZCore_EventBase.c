/*
    DeutschZ ModZ
    Autor/Eigentuemer: Patrick Sluzalek / fck1701
    Projekt: DeutschZ
    Zweck: Eigene DeutschZ-Implementierung fuer Core, ExpansionBridge und Event-Module.
    Quellen-/Konzeptnachweis: Eigenentwickelte Struktur; DayZ, CF und Expansion nur als Laufzeit-API/Abhaengigkeit.
    No-Copy-Bestaetigung: Kein Code, keine Assets und keine Configs aus fremden Mods kopiert.
*/

class DeutschZCore_EventBase: DeutschZCore_ModuleBase
{
    protected int m_State;
    protected string m_EventId;

    void DeutschZCore_EventBase(string moduleName)
    {
        m_State = DeutschZCore_EventState.DEUTSCHZ_EVENT_IDLE;
        m_EventId = moduleName;
    }

    int GetState()
    {
        return m_State;
    }

    string GetEventId()
    {
        return m_EventId;
    }

    bool CanStart()
    {
        return m_State == DeutschZCore_EventState.DEUTSCHZ_EVENT_IDLE || m_State == DeutschZCore_EventState.DEUTSCHZ_EVENT_FAILED;
    }

    void SetState(int state)
    {
        if (m_State == state)
            return;
        m_State = state;
        DeutschZCore_Log.Info(GetModuleName(), "state=" + state.ToString());
    }

    void StartEvent()
    {
        if (!CanStart())
            return;
        SetState(DeutschZCore_EventState.DEUTSCHZ_EVENT_STARTING);
    }

    void StopEvent()
    {
        SetState(DeutschZCore_EventState.DEUTSCHZ_EVENT_CLEANUP);
    }
}
