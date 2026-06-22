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

class DeutschZConvoyZValidator
{
    static bool IsVectorUsable(vector pos)
    {
        return pos != "0 0 0";
    }

    static bool IsClassNameUsable(string className)
    {
        return className != "";
    }

    static bool ValidateConfig(DeutschZConvoyZConfig cfg)
    {
        if (!cfg || !cfg.Settings || !cfg.EventData) return false;
        if (!IsVectorUsable(cfg.EventData.EventCenter)) return false;
        if ((!cfg.EventData.Vehicles || cfg.EventData.Vehicles.Count() == 0) && (!cfg.EventData.CrashObjects || cfg.EventData.CrashObjects.Count() == 0)) return false;
        if (!cfg.EventData.Blackbox || !IsClassNameUsable(cfg.EventData.Blackbox.ClassName)) return false;
        if (cfg.EventData.RequiredAiKills <= 0) return false;
        if (cfg.EventData.HackDurationSeconds <= 0) return false;
        if (cfg.Settings.MaxSimultaneousEvents < 1) return false;
        if (cfg.Settings.InitialStartDelayMaxSeconds < cfg.Settings.InitialStartDelayMinSeconds) return false;
        if (cfg.Settings.RestartDelayMaxSeconds < cfg.Settings.RestartDelayMinSeconds) return false;
        return true;
    }

    static bool CanHack(PlayerBase player, Object blackbox, float maxDistance)
    {
        if (!player || !player.GetIdentity()) return false;
        if (!player.IsAlive()) return false;
        if (player.IsUnconscious()) return false;
        if (!blackbox) return false;
        if (vector.Distance(player.GetPosition(), blackbox.GetPosition()) > maxDistance) return false;
        return true;
    }
}
