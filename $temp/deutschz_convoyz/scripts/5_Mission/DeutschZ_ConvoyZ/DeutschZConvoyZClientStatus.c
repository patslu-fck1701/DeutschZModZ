/*
DeutschZ ModZ
Eigenstaendige Implementierung fuer DeutschZ.
Autor/Eigentuemer: Patrick Sluzalek / fck1701.
Projekt: DeutschZ.
Modul: DeutschZ_ConvoyZ.
Zweck der Datei: Eigene DeutschZ-Datei fuer ConvoyZ.
Quellen-/Konzeptnachweis: Eigene DeutschZ-Implementierung; DayZ/CF/Expansion werden nur als Laufzeit-Abhaengigkeit/API genutzt.
Keine direkte Codeuebernahme aus Drittquellen.
*/

void DeutschZConvoyZ_ShowStatus(string text, int state, int kills, int hackSeconds)
{
    // Client UI bridge hook.
    // Kept override-free for compatibility with server Mission module.
    // Custom HUD/statusbar integration can call this function from a supported UI class later.
    if (GetGame())
    {
        PlayerBase player = PlayerBase.Cast(GetGame().GetPlayer());
        if (player)
        {
            GetGame().ChatPlayer(text);
        }
    }
}
