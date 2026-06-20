/*
    DeutschZ ModZ
    Autor/Eigentuemer: Patrick Sluzalek / fck1701
    Projekt: DeutschZ
    Zweck: Eigene DeutschZ-Implementierung fuer Core, ExpansionBridge und Event-Module.
    Quellen-/Konzeptnachweis: Eigenentwickelte Struktur; DayZ, CF und Expansion nur als Laufzeit-API/Abhaengigkeit.
    No-Copy-Bestaetigung: Kein Code, keine Assets und keine Configs aus fremden Mods kopiert.
*/

class DeutschZCore_ModuleBase
{
    protected string m_ModuleName;
    protected bool m_Initialized;

    void DeutschZCore_ModuleBase(string moduleName)
    {
        m_ModuleName = moduleName;
        m_Initialized = false;
    }

    string GetModuleName()
    {
        return m_ModuleName;
    }

    bool IsInitialized()
    {
        return m_Initialized;
    }

    void Init()
    {
        m_Initialized = true;
        DeutschZCore_Log.Info(m_ModuleName, "initialized");
    }

    void Shutdown()
    {
        m_Initialized = false;
        DeutschZCore_Log.Info(m_ModuleName, "shutdown");
    }
}
