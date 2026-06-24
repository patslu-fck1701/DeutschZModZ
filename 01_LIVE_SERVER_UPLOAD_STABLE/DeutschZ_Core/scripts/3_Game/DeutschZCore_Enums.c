/*
    DeutschZ ModZ
    Autor/Eigentuemer: Patrick Sluzalek / fck1701
    Projekt: DeutschZ
    Zweck: Eigene DeutschZ-Implementierung fuer Core, ExpansionBridge und Event-Module.
    Quellen-/Konzeptnachweis: Eigenentwickelte Struktur; DayZ, CF und Expansion nur als Laufzeit-API/Abhaengigkeit.
    No-Copy-Bestaetigung: Kein Code, keine Assets und keine Configs aus fremden Mods kopiert.
*/

enum DeutschZCore_EventState
{
    DEUTSCHZ_EVENT_IDLE = 0,
    DEUTSCHZ_EVENT_STARTING = 1,
    DEUTSCHZ_EVENT_ACTIVE = 2,
    DEUTSCHZ_EVENT_COMPLETING = 3,
    DEUTSCHZ_EVENT_CLEANUP = 4,
    DEUTSCHZ_EVENT_FAILED = 5
}
