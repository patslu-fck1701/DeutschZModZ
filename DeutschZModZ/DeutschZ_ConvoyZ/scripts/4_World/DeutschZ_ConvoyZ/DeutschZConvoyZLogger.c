/*
DeutschZ ModZ
Eigenstaendige Implementierung fuer DeutschZ.
Autor/Eigentuemer: Patrick Sluzalek / fck1701.
Projekt: DeutschZ.
Modul: DeutschZ_ConvoyZ.
Zweck der Datei: Eigene DeutschZ-Logging-Funktionen.
Quellen-/Konzeptnachweis: Eigene DeutschZ-Implementierung; DayZ/CF/Expansion werden nur als Laufzeit-Abhaengigkeit/API genutzt.
Keine direkte Codeuebernahme aus Drittquellen.
*/

class DeutschZConvoyZLogger
{
    static int s_Debug;

    static void SetDebug(int enabled)
    {
        s_Debug = enabled;
    }

    static void Log(string action, string eventId = "", string state = "", string playerId = "", vector pos = "0 0 0", string result = "", string reason = "")
    {
        if (s_Debug == 0 && result != "FAILED" && result != "BLOCKED") return;
        Print("[DeutschZ_ConvoyZ] Action=" + action + " EventId=" + eventId + " State=" + state + " PlayerId=" + playerId + " Pos=" + pos.ToString() + " Result=" + result + " Reason=" + reason);
    }
}
