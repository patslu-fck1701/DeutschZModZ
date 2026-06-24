/*
    DeutschZ_GroundZero
    Owner: Patrick Sluzalek / fck1701
    Module: 3_Game / GroundZeroRPC
    Purpose: Shared client HUD RPC payload and client-side HUD state.
    Compliance: Original DeutschZ implementation. No copied foreign mod code, assets, configs or stubs.
*/

class GroundZeroRPC
{
    static const string TOKEN = "DeutschZ_GroundZero_RPC_V1";
}

class GroundZeroClientHUDState
{
    protected static bool s_Active;
    protected static string s_Title;
    protected static int s_Percent;
    protected static int s_Current;
    protected static int s_Total;
    protected static int s_PlayersNear;
    protected static string s_State;
    protected static int s_LastUpdateMs;

    static void Set(bool active, string title, int percent, int current, int total, int playersNear, string state)
    {
        s_Active = active;
        s_Title = title;
        s_Percent = percent;
        s_Current = current;
        s_Total = total;
        s_PlayersNear = playersNear;
        s_State = state;
        s_LastUpdateMs = GetGame().GetTime();
    }

    static bool IsActive() { return s_Active; }
    static string GetTitle() { return s_Title; }
    static int GetPercent() { return s_Percent; }
    static int GetCurrent() { return s_Current; }
    static int GetTotal() { return s_Total; }
    static int GetPlayersNear() { return s_PlayersNear; }
    static string GetState() { return s_State; }
    static int GetLastUpdateMs() { return s_LastUpdateMs; }
}
