class DeutschZTools_Client
{
    static Object GetRPCTarget()
    {
        return GetGame().GetPlayer();
    }

    static bool HasValidTarget(out Object target)
    {
        target = GetRPCTarget();
        if (!target)
        {
            Print(DeutschZTools_Constants.LOG_PREFIX + "RPC target missing.");
            return false;
        }

        return true;
    }

    static void SendAction(int action)
    {
        Object target;
        if (!HasValidTarget(target))
            return;

        ScriptRPC rpc = new ScriptRPC();
        rpc.Write(action);
        rpc.Send(target, DeutschZTools_RPC.CLIENT_REQUEST, true, null);
    }

    static void SendTargetAction(int action, string steam64)
    {
        Object target;
        if (!HasValidTarget(target))
            return;

        steam64.Trim();

        ScriptRPC rpc = new ScriptRPC();
        rpc.Write(action);
        rpc.Write(steam64);
        rpc.Send(target, DeutschZTools_RPC.CLIENT_REQUEST, true, null);
    }


    static void SendTargetAmountAction(int action, string steam64, string amountText)
    {
        Object target;
        if (!HasValidTarget(target))
            return;

        steam64.Trim();
        amountText.Trim();
        int amount = amountText.ToInt();

        ScriptRPC rpc = new ScriptRPC();
        rpc.Write(action);
        rpc.Write(steam64);
        rpc.Write(amount);
        rpc.Send(target, DeutschZTools_RPC.CLIENT_REQUEST, true, null);
    }

    static void SendSpawnObject(string className, TStringArray attachments, string targetSteam64, int spawnMode)
    {
        Object target;
        if (!HasValidTarget(target))
            return;

        className.Trim();
        targetSteam64.Trim();

        ScriptRPC rpc = new ScriptRPC();
        rpc.Write(DeutschZTools_Action.SPAWN_OBJECT);
        rpc.Write(className);

        int count = 0;
        if (attachments)
            count = attachments.Count();

        if (count > 25)
            count = 25;

        rpc.Write(count);

        for (int i = 0; i < count; i++)
        {
            rpc.Write(attachments.Get(i));
        }

        rpc.Write(targetSteam64);
        rpc.Write(spawnMode);

        rpc.Send(target, DeutschZTools_RPC.CLIENT_REQUEST, true, null);
    }

    static void SendTeleportSelfToPosition(vector position)
    {
        Object target;
        if (!HasValidTarget(target))
            return;

        ScriptRPC rpc = new ScriptRPC();
        rpc.Write(DeutschZTools_Action.TELEPORT_SELF_TO_POS);
        rpc.Write(position);
        rpc.Send(target, DeutschZTools_RPC.CLIENT_REQUEST, true, null);
    }

    static void DisplayMessage(string message)
    {
        if (!GetGame() || !GetGame().GetMission())
            return;

        GetGame().GetMission().OnEvent(ChatMessageEventTypeID, new ChatMessageEventParams(CCAdmin, "", "DeutschZ Tools: " + message, ""));
    }

    static void HandleResult(ParamsReadContext ctx)
    {
        bool success;
        string message;

        if (!ctx.Read(success))
            return;

        if (!ctx.Read(message))
            return;

        if (success)
            Print(DeutschZTools_Constants.LOG_PREFIX + "OK: " + message);
        else
            Print(DeutschZTools_Constants.LOG_PREFIX + "FAILED: " + message);

        DeutschZTools_AdminMenu menu = DeutschZTools_AdminMenu.Cast(GetGame().GetUIManager().GetMenu());
        if (menu)
            menu.SetStatus(message);

        DisplayMessage(message);
    }

    static void HandlePlayerList(ParamsReadContext ctx)
    {
        int count;
        if (!ctx.Read(count))
            return;

        string listText = "Online players: " + count + "\n";
        Print(DeutschZTools_Constants.LOG_PREFIX + "Player list received: " + count);

        for (int i = 0; i < count; i++)
        {
            string name;
            string steam64;
            vector pos;
            float health01;
            float blood01;
            float shock01;
            bool alive;

            if (!ctx.Read(name)) return;
            if (!ctx.Read(steam64)) return;
            if (!ctx.Read(pos)) return;
            if (!ctx.Read(health01)) return;
            if (!ctx.Read(blood01)) return;
            if (!ctx.Read(shock01)) return;
            if (!ctx.Read(alive)) return;

            string state = "dead";
            if (alive)
                state = "alive";

            listText = listText + name + " | " + steam64 + " | " + state + " | " + pos.ToString() + "\n";
            Print(DeutschZTools_Constants.LOG_PREFIX + "Player: " + name + " " + steam64 + " " + pos.ToString());
        }

        DeutschZTools_AdminMenu menu = DeutschZTools_AdminMenu.Cast(GetGame().GetUIManager().GetMenu());
        if (menu)
        {
            menu.SetPlayerList(listText);
            menu.SetStatus("Player list updated.");
        }
    }
}
