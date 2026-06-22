/*
DeutschZ ModZ
Eigenstaendige Implementierung fuer DeutschZ.
Autor/Eigentuemer: Patrick Sluzalek / fck1701.
Keine direkte Codeuebernahme aus Drittquellen.
Oeffentliche Quellen werden nur zur Konzept- und API-Verifikation genutzt.
*/

class DeutschZKotHZRPC
{
    static const int SYNC_HUD = 789451;
    static const int PLAY_MUSIC = 789452;
    static const string TOKEN = "DeutschZ_KotHZ_RPC_V1";
}

class DeutschZKotHZProgress
{
    string ZoneName;
    string Status;
    int PlayerCount;
    float Progress;
    int Seconds;
    int TotalSeconds;

    void DeutschZKotHZProgress(string zoneName, string status, int playerCount, float progress, int seconds, int totalSeconds)
    {
        ZoneName = zoneName;
        Status = status;
        PlayerCount = playerCount;
        Progress = progress;
        Seconds = seconds;
        TotalSeconds = totalSeconds;
    }
}

class DeutschZKotHZClientHUDState
{
    protected static bool s_Active;
    protected static string s_ZoneName;
    protected static int s_Percent;
    protected static int s_Seconds;
    protected static int s_TotalSeconds;
    protected static int s_PlayersInZone;
    protected static string s_State;
    protected static int s_LastUpdateMs;

    static void Set(bool active, string zoneName, int percent, int seconds, int totalSeconds, int playersInZone, string state)
    {
        s_Active = active;
        s_ZoneName = zoneName;
        s_Percent = percent;
        s_Seconds = seconds;
        s_TotalSeconds = totalSeconds;
        s_PlayersInZone = playersInZone;
        s_State = state;
        s_LastUpdateMs = GetGame().GetTime();
    }

    static bool IsActive() { return s_Active; }
    static string GetZoneName() { return s_ZoneName; }
    static int GetPercent() { return s_Percent; }
    static int GetSeconds() { return s_Seconds; }
    static int GetTotalSeconds() { return s_TotalSeconds; }
    static int GetPlayersInZone() { return s_PlayersInZone; }
    static string GetState() { return s_State; }
    static int GetLastUpdateMs() { return s_LastUpdateMs; }
}


class DeutschZKotHZClientSound
{
    static void PlayEventMusic(string soundSetName, vector position)
    {
        if (soundSetName == "")
            return;

        EffectSound sound = SEffectManager.PlaySound(soundSetName, position, 0.2, 0.2, false);
        if (sound)
            sound.SetAutodestroy(true);
    }
}
