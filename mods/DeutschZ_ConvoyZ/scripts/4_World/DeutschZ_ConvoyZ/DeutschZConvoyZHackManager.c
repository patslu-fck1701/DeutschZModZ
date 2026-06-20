/*
DeutschZ ModZ
Eigenstaendige Implementierung fuer DeutschZ.
Autor/Eigentuemer: Patrick Sluzalek / fck1701.
Projekt: DeutschZ.
Modul: DeutschZ_ConvoyZ.
Zweck der Datei: Serverseitige ConvoyZ-Eventlogik, Ablauf, Status und Sicherheitspruefung.
Quellen-/Konzeptnachweis: Eigene DeutschZ-Implementierung; DayZ/CF/Expansion werden nur als Laufzeit-Abhaengigkeit/API genutzt.
Keine direkte Codeuebernahme aus Drittquellen.
*/

class DeutschZConvoyZHackManager
{
    DeutschZConvoyZManager Manager;

    void DeutschZConvoyZHackManager(DeutschZConvoyZManager manager)
    {
        Manager = manager;
    }

    bool StartHack(PlayerBase player)
    {
        if (!Manager || !Manager.State || !Manager.Config || !player || !player.GetIdentity()) return false;
        DeutschZConvoyZRuntimeState state = Manager.State;
        string pid = player.GetIdentity().GetPlainId();
        if (state.CurrentState != DeutschZConvoyZConstants.STATE_BLACKBOX_READY) return Block(player, "not ready");
        if (state.HackProcessing == 1 && Manager.Config.Settings.RejectParallelHackRequests == 1) return Block(player, "parallel hack");
        if (!DeutschZConvoyZValidator.CanHack(player, state.BlackboxEntity, Manager.Config.Settings.BlackboxMaxHackDistance)) return Block(player, "validation failed");
        state.ActiveHackerPlayerId = pid;
        state.HackProcessing = 1;
        state.HackProgressSeconds = 0;
        Manager.ChangeState(DeutschZConvoyZConstants.STATE_HACKING, "hack started");
        Manager.SetSmoke(DeutschZConvoyZConstants.SMOKE_YELLOW);
        GetGame().GetCallQueue(CALL_CATEGORY_SYSTEM).Remove(this.Tick);
        GetGame().GetCallQueue(CALL_CATEGORY_SYSTEM).CallLater(this.Tick, 1000, true);
        DeutschZConvoyZLogger.Log("HackStarted", state.EventId, "HACKING", pid, player.GetPosition(), "OK", "hold action");
        Manager.SyncStatusNow();
        return true;
    }

    bool StopHack(PlayerBase player, string reason)
    {
        if (!Manager || !Manager.State) return false;
        string pid = "";
        if (player && player.GetIdentity()) pid = player.GetIdentity().GetPlainId();
        if (Manager.State.ActiveHackerPlayerId != "" && pid != "" && Manager.State.ActiveHackerPlayerId != pid) return false;
        Abort(reason);
        return true;
    }

    void Tick()
    {
        if (!Manager || !Manager.State || !Manager.Config) return;
        DeutschZConvoyZRuntimeState state = Manager.State;
        if (state.CurrentState != DeutschZConvoyZConstants.STATE_HACKING || state.ActiveHackerPlayerId == "")
        {
            StopTimer();
            return;
        }
        PlayerBase player = FindPlayer(state.ActiveHackerPlayerId);
        if (!DeutschZConvoyZValidator.CanHack(player, state.BlackboxEntity, Manager.Config.Settings.BlackboxMaxHackDistance))
        {
            Abort("invalid hacker state");
            return;
        }
        state.HackProgressSeconds++;
        Manager.SendStatusNotification(true);
        Manager.SyncStatusNow();
        DeutschZConvoyZLogger.Log("HackProgress", state.EventId, "HACKING", state.ActiveHackerPlayerId, player.GetPosition(), "OK", state.HackProgressSeconds.ToString() + "/" + Manager.GetHackDuration().ToString());
        if (state.HackProgressSeconds >= Manager.GetHackDuration()) Complete(player);
    }

    void Complete(PlayerBase player)
    {
        if (!Manager || !Manager.State) return;
        string pid = Manager.State.ActiveHackerPlayerId;
        StopTimer();
        Manager.State.ActiveHackerPlayerId = "";
        Manager.State.HackProcessing = 0;
        Manager.ChangeState(DeutschZConvoyZConstants.STATE_REWARD_UNLOCKED, "hack complete");
        Manager.SetSmoke(DeutschZConvoyZConstants.SMOKE_GREEN);
        Manager.UnlockReward();
        DeutschZConvoyZLogger.Log("HackCompleted", Manager.State.EventId, "REWARD_UNLOCKED", pid, player.GetPosition(), "OK", "");
        Manager.ScheduleCleanup();
        Manager.SyncStatusNow();
    }

    void Abort(string reason)
    {
        if (!Manager || !Manager.State) return;
        string pid = Manager.State.ActiveHackerPlayerId;
        StopTimer();
        Manager.State.ActiveHackerPlayerId = "";
        Manager.State.HackProcessing = 0;
        if (Manager.Config && Manager.Config.Settings.AllowHackProgressResetOnAbort == 1) Manager.State.HackProgressSeconds = 0;
        if (Manager.State.CurrentState == DeutschZConvoyZConstants.STATE_HACKING) Manager.ChangeState(DeutschZConvoyZConstants.STATE_BLACKBOX_READY, "hack aborted");
        DeutschZConvoyZLogger.Log("HackAborted", Manager.State.EventId, DeutschZConvoyZ_StateName(Manager.State.CurrentState), pid, "0 0 0", "OK", reason);
        Manager.SyncStatusNow();
    }

    void StopTimer()
    {
        GetGame().GetCallQueue(CALL_CATEGORY_SYSTEM).Remove(this.Tick);
    }

    PlayerBase FindPlayer(string plainId)
    {
        array<Man> players = new array<Man>;
        GetGame().GetPlayers(players);
        foreach (Man man: players)
        {
            PlayerBase pb = PlayerBase.Cast(man);
            if (pb && pb.GetIdentity() && pb.GetIdentity().GetPlainId() == plainId) return pb;
        }
        return null;
    }

    bool Block(PlayerBase player, string reason)
    {
        string pid = "";
        vector pos = "0 0 0";
        if (player)
        {
            pos = player.GetPosition();
            if (player.GetIdentity()) pid = player.GetIdentity().GetPlainId();
        }
        if (Manager && Manager.State) DeutschZConvoyZLogger.Log("HackBlocked", Manager.State.EventId, DeutschZConvoyZ_StateName(Manager.State.CurrentState), pid, pos, "BLOCKED", reason);
        return false;
    }
}
