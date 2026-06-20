/*
    DeutschZ ModZ - DeutschZ_Core
    Autor/Eigentuemer: Patrick Sluzalek / fck1701
    Zweck: Basisklasse fuer DeutschZ-Module.
    Quellen-/Konzeptnachweis: Eigenentwickelte DeutschZ-Struktur, DayZ/CF/Expansion nur als API-Abhaengigkeit vorgesehen.
    No-Copy-Bestaetigung: Kein Code, keine Assets und keine Configs aus fremden Mods kopiert.
*/
class DeutschZCore_ModuleBase
{
    protected string m_ModuleName;
    void DeutschZCore_ModuleBase(string moduleName) { m_ModuleName = moduleName; }
    string GetModuleName() { return m_ModuleName; }
    void Init() {}
    void Shutdown() {}
}
