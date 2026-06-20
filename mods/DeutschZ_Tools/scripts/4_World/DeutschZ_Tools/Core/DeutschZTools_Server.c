class DeutschZTools_Server
{
    protected static bool s_Initialized;

    static void Init()
    {
        if (s_Initialized)
            return;

        s_Initialized = true;
        DeutschZTools_FileUtil.EnsureProfileDirs();
        DeutschZTools_SettingsService.Load();
        DeutschZTools_FeatureConfigService.Load();
        DeutschZTools_PermissionService.Load();
        DeutschZTools_Logger.Info("Server initialized. Version " + DeutschZTools_Constants.VERSION);
    }

    static void SendResult(PlayerIdentity identity, bool success, string message)
    {
        if (!identity)
            return;

        PlayerBase player = DeutschZTools_PlayerService.GetPlayerByIdentity(identity);
        if (!player)
            return;

        ScriptRPC rpc = new ScriptRPC();
        rpc.Write(success);
        rpc.Write(message);
        rpc.Send(player, DeutschZTools_RPC.SERVER_RESULT, true, identity);
    }

    static void SendPlayerList(PlayerIdentity identity)
    {
        if (!identity)
            return;

        PlayerBase player = DeutschZTools_PlayerService.GetPlayerByIdentity(identity);
        if (!player)
            return;

        ref array<ref DeutschZTools_PlayerSnapshot> list = new array<ref DeutschZTools_PlayerSnapshot>;
        DeutschZTools_PlayerService.BuildPlayerList(list);

        ScriptRPC rpc = new ScriptRPC();
        rpc.Write(list.Count());

        foreach (DeutschZTools_PlayerSnapshot snap : list)
        {
            rpc.Write(snap.Name);
            rpc.Write(snap.Steam64);
            rpc.Write(snap.Position);
            rpc.Write(snap.Health01);
            rpc.Write(snap.Blood01);
            rpc.Write(snap.Shock01);
            rpc.Write(snap.IsAlive);
        }

        rpc.Send(player, DeutschZTools_RPC.SERVER_PLAYER_LIST, true, identity);
    }


    static void SendGarageList(PlayerIdentity identity, string title, array<string> rows)
    {
        if (!identity)
            return;

        PlayerBase player = DeutschZTools_PlayerService.GetPlayerByIdentity(identity);
        if (!player)
            return;

        ScriptRPC rpc = new ScriptRPC();
        rpc.Write(title);

        int count = 0;
        if (rows)
            count = rows.Count();

        rpc.Write(count);
        for (int i = 0; i < count; i++)
        {
            rpc.Write(rows.Get(i));
        }

        rpc.Send(player, DeutschZTools_RPC.SERVER_GARAGE_LIST, true, identity);
    }

    static void SendBankingList(PlayerIdentity identity, string title, array<string> rows)
    {
        if (!identity)
            return;

        PlayerBase player = DeutschZTools_PlayerService.GetPlayerByIdentity(identity);
        if (!player)
            return;

        ScriptRPC rpc = new ScriptRPC();
        rpc.Write(title);

        int count = 0;
        if (rows)
            count = rows.Count();

        rpc.Write(count);
        for (int i = 0; i < count; i++)
        {
            rpc.Write(rows.Get(i));
        }

        rpc.Send(player, DeutschZTools_RPC.SERVER_BANKING_LIST, true, identity);
    }

    static void SendGroupsList(PlayerIdentity identity, string title, array<string> rows)
    {
        if (!identity)
            return;

        PlayerBase player = DeutschZTools_PlayerService.GetPlayerByIdentity(identity);
        if (!player)
            return;

        ScriptRPC rpc = new ScriptRPC();
        rpc.Write(title);

        int count = 0;
        if (rows)
            count = rows.Count();

        rpc.Write(count);
        for (int i = 0; i < count; i++)
        {
            rpc.Write(rows.Get(i));
        }

        rpc.Send(player, DeutschZTools_RPC.SERVER_GROUPS_LIST, true, identity);
    }


    static void SendTraderZList(PlayerIdentity identity, string title, array<string> rows)
    {
        if (!identity)
            return;

        PlayerBase player = DeutschZTools_PlayerService.GetPlayerByIdentity(identity);
        if (!player)
            return;

        ScriptRPC rpc = new ScriptRPC();
        rpc.Write(title);

        int count = 0;
        if (rows)
            count = rows.Count();

        rpc.Write(count);
        for (int i = 0; i < count; i++)
        {
            rpc.Write(rows.Get(i));
        }

        rpc.Send(player, DeutschZTools_RPC.SERVER_TRADERZ_LIST, true, identity);
    }

    static bool ReadIntSafe(ParamsReadContext ctx, out int value)
    {
        value = 0;
        if (!ctx)
            return false;

        if (!ctx.Read(value))
            return false;

        return true;
    }

    static bool ReadStringSafe(ParamsReadContext ctx, out string value)
    {
        value = "";
        if (!ctx)
            return false;

        if (!ctx.Read(value))
            return false;

        return true;
    }

    static void HandleAction(PlayerIdentity sender, int action, ParamsReadContext ctx)
    {
        Init();

        if (!sender)
            return;

        string message = "";
        bool success = false;
        string requiredPermission = GetRequiredPermission(action);

        if (requiredPermission != "" && !DeutschZTools_PermissionService.HasPermission(sender, requiredPermission))
        {
            SendResult(sender, false, DeutschZTools_PermissionService.GetMissingPermissionText(requiredPermission));
            return;
        }

        PlayerBase adminPlayer = DeutschZTools_PlayerService.GetPlayerByIdentity(sender);

        switch (action)
        {
            case DeutschZTools_Action.PING:
                success = true;
                message = "DeutschZ_Tools " + DeutschZTools_Constants.VERSION + " permission check OK.";
                break;

            case DeutschZTools_Action.REQUEST_MENU_ACCESS:
                success = true;
                message = "Menu access granted.";
                break;

            case DeutschZTools_Action.REQUEST_PLAYER_LIST:
                SendPlayerList(sender);
                success = true;
                message = "Player list requested.";
                break;

            case DeutschZTools_Action.HEAL_SELF:
                success = DeutschZTools_PlayerService.Heal(adminPlayer, message);
                break;

            case DeutschZTools_Action.HEAL_PLAYER:
                string healSteam64;
                if (!ReadStringSafe(ctx, healSteam64))
                {
                    success = false;
                    message = "Target Steam64 missing.";
                }
                else
                {
                    success = DeutschZTools_PlayerService.HealBySteam64(healSteam64, message);
                }
                break;

            case DeutschZTools_Action.TELEPORT_SELF_TO_POS:
                vector targetPos;
                if (!ctx.Read(targetPos))
                {
                    success = false;
                    message = "Teleport payload missing.";
                }
                else
                {
                    success = DeutschZTools_PlayerService.Teleport(adminPlayer, targetPos, message);
                }
                break;

            case DeutschZTools_Action.TELEPORT_TO_PLAYER:
                string tpTargetSteam64;
                if (!ReadStringSafe(ctx, tpTargetSteam64))
                {
                    success = false;
                    message = "Target Steam64 missing.";
                }
                else
                {
                    success = DeutschZTools_PlayerService.TeleportToPlayer(adminPlayer, tpTargetSteam64, message);
                }
                break;

            case DeutschZTools_Action.TELEPORT_PLAYER_TO_ME:
                string bringSteam64;
                if (!ReadStringSafe(ctx, bringSteam64))
                {
                    success = false;
                    message = "Target Steam64 missing.";
                }
                else
                {
                    success = DeutschZTools_PlayerService.BringPlayer(adminPlayer, bringSteam64, message);
                }
                break;

            case DeutschZTools_Action.REPAIR_NEAREST_VEHICLE:
                if (!adminPlayer)
                {
                    success = false;
                    message = "Admin player not found.";
                }
                else
                {
                    float repairRadius = DeutschZTools_SettingsService.Get().RepairVehicleRadius;
                    if (repairRadius < 1.0)
                        repairRadius = 1.0;

                    Transport vehicle = DeutschZTools_VehicleService.FindNearestVehicle(adminPlayer.GetPosition(), repairRadius);
                    success = DeutschZTools_VehicleService.RepairVehicle(vehicle, message);
                }
                break;


            case DeutschZTools_Action.FLIP_NEAREST_VEHICLE:
                if (!adminPlayer)
                {
                    success = false;
                    message = "Admin player not found.";
                }
                else
                {
                    float flipRadius = DeutschZTools_SettingsService.Get().VehicleActionRadius;
                    if (flipRadius < 1.0)
                        flipRadius = 1.0;

                    Transport flipVehicle = DeutschZTools_VehicleService.FindNearestVehicle(adminPlayer.GetPosition(), flipRadius);
                    success = DeutschZTools_VehicleService.FlipVehicle(flipVehicle, message);
                }
                break;

            case DeutschZTools_Action.TELEPORT_NEAREST_VEHICLE_TO_ME:
                if (!adminPlayer)
                {
                    success = false;
                    message = "Admin player not found.";
                }
                else
                {
                    float tpVehicleRadius = DeutschZTools_SettingsService.Get().VehicleActionRadius;
                    if (tpVehicleRadius < 1.0)
                        tpVehicleRadius = 1.0;

                    Transport tpVehicle = DeutschZTools_VehicleService.FindNearestVehicle(adminPlayer.GetPosition(), tpVehicleRadius);
                    success = DeutschZTools_VehicleService.TeleportVehicleToAdmin(tpVehicle, adminPlayer, message);
                }
                break;

            case DeutschZTools_Action.SPAWN_OBJECT:
                string className;
                if (!ctx.Read(className))
                    className = "";

                DeutschZTools_SpawnRequest request = new DeutschZTools_SpawnRequest();
                request.ClassName = className;

                int attCount;
                if (ctx.Read(attCount))
                {
                    if (attCount > 25)
                        attCount = 25;

                    for (int i = 0; i < attCount; i++)
                    {
                        string att;
                        if (ctx.Read(att) && att != "")
                            request.Attachments.Insert(att);
                    }
                }

                string spawnTargetSteam64;
                if (ctx.Read(spawnTargetSteam64))
                    request.TargetSteam64 = spawnTargetSteam64;

                int spawnMode;
                if (ctx.Read(spawnMode))
                    request.SpawnMode = spawnMode;

                success = DeutschZTools_SpawnService.SpawnInFrontOfPlayer(adminPlayer, request, message);
                break;

            case DeutschZTools_Action.SET_WEATHER_CLEAR:
                success = DeutschZTools_WeatherService.SetClear(message);
                break;

            case DeutschZTools_Action.SET_WEATHER_RAIN:
                success = DeutschZTools_WeatherService.SetRain(message);
                break;

            case DeutschZTools_Action.SET_WEATHER_STORM:
                success = DeutschZTools_WeatherService.SetStorm(message);
                break;

            case DeutschZTools_Action.SET_WEATHER_FOG:
                success = DeutschZTools_WeatherService.SetFog(message);
                break;

            case DeutschZTools_Action.RELOAD_CONFIGS:
                success = DeutschZTools_SettingsService.Reload();
                success = DeutschZTools_FeatureConfigService.Reload() && success;
                success = DeutschZTools_PermissionService.Reload() && success;
                if (success)
                    message = "DeutschZ_Tools configs reloaded.";
                else
                    message = "Config reload failed. Check server log.";
                break;

            case DeutschZTools_Action.KOTH_STATUS:
                success = DeutschZTools_EventBridge.KOTHStatus(sender, message);
                break;

            case DeutschZTools_Action.KOTH_FORCE_START:
                success = DeutschZTools_EventBridge.ForceStartKOTH(sender, message);
                break;

            case DeutschZTools_Action.KOTH_FORCE_STOP:
                success = DeutschZTools_EventBridge.ForceStopKOTH(sender, message);
                break;

            case DeutschZTools_Action.KOTH_RELOAD_CONFIGS:
                success = DeutschZTools_EventBridge.ReloadKOTHConfigs(sender, message);
                break;

            case DeutschZTools_Action.KOTH_SAVE_SETTINGS:
                success = DeutschZTools_EventBridge.SaveKOTHSettings(sender, message);
                break;

            case DeutschZTools_Action.KOTH_RELOAD_SETTINGS:
                success = DeutschZTools_EventBridge.ReloadKOTHSettings(sender, message);
                break;

            case DeutschZTools_Action.KOTH_RELOAD_ZONES:
                success = DeutschZTools_EventBridge.ReloadKOTHZones(sender, message);
                break;

            case DeutschZTools_Action.KOTH_RELOAD_LOOT:
                success = DeutschZTools_EventBridge.ReloadKOTHLoot(sender, message);
                break;

            case DeutschZTools_Action.KOTH_RELOAD_ALL:
                success = DeutschZTools_EventBridge.ReloadKOTHAll(sender, message);
                break;

            case DeutschZTools_Action.SERVER_RESTART_COUNTDOWN:
                success = false;
                if (DeutschZTools_SettingsService.Get().AllowScriptedRestart == 0)
                    message = "Scripted restart is disabled in DeutschZTools_Settings.json.";
                else
                    message = "Safe restart bridge is prepared but not bound yet.";
                break;

            case DeutschZTools_Action.GARAGE_STATUS:
                success = DeutschZTools_GarageBridge.GetStatus(message);
                break;

            case DeutschZTools_Action.GARAGE_RELOAD:
                success = DeutschZTools_GarageBridge.Reload(message);
                break;

            case DeutschZTools_Action.GARAGE_LIST:
                string garageSteam64;
                if (!ReadStringSafe(ctx, garageSteam64))
                {
                    success = false;
                    message = "Target Steam64 missing.";
                }
                else
                {
                    ref array<string> garageRows = new array<string>;
                    success = DeutschZTools_GarageBridge.BuildVehicleRows(garageSteam64, garageRows, message);
                    SendGarageList(sender, message, garageRows);
                }
                break;

            case DeutschZTools_Action.GARAGE_IMPOUND_NEAREST:
                string impoundSteam64;
                if (!ReadStringSafe(ctx, impoundSteam64))
                {
                    success = false;
                    message = "Target Steam64 missing.";
                }
                else
                {
                    success = DeutschZTools_GarageBridge.ImpoundNearest(adminPlayer, impoundSteam64, message);
                    string impoundResultMessage = message;
                    ref array<string> garageRowsAfterImpound = new array<string>;
                    string garageListMessage;
                    DeutschZTools_GarageBridge.BuildVehicleRows(impoundSteam64, garageRowsAfterImpound, garageListMessage);
                    SendGarageList(sender, garageListMessage, garageRowsAfterImpound);
                    message = impoundResultMessage;
                }
                break;

            case DeutschZTools_Action.BANKING_STATUS:
                success = DeutschZTools_BankingBridge.GetStatus(message);
                break;

            case DeutschZTools_Action.BANKING_RELOAD:
                success = DeutschZTools_BankingBridge.Reload(message);
                break;

            case DeutschZTools_Action.BANKING_LOOKUP:
                string lookupSteam64;
                if (!ReadStringSafe(ctx, lookupSteam64))
                {
                    success = false;
                    message = "Target Steam64 missing.";
                }
                else
                {
                    ref array<string> bankingRows = new array<string>;
                    success = DeutschZTools_BankingBridge.Lookup(lookupSteam64, bankingRows, message);
                    SendBankingList(sender, message, bankingRows);
                }
                break;

            case DeutschZTools_Action.BANKING_ADD_MONEY:
                string addSteam64;
                int addAmount;
                if (!ReadStringSafe(ctx, addSteam64) || !ReadIntSafe(ctx, addAmount))
                {
                    success = false;
                    message = "Banking add payload missing.";
                }
                else
                {
                    success = DeutschZTools_BankingBridge.AddMoney(addSteam64, addAmount, message);
                    string addResultMessage = message;
                    ref array<string> bankingRowsAfterAdd = new array<string>;
                    string addListMessage;
                    DeutschZTools_BankingBridge.Lookup(addSteam64, bankingRowsAfterAdd, addListMessage);
                    SendBankingList(sender, addListMessage, bankingRowsAfterAdd);
                    message = addResultMessage;
                }
                break;

            case DeutschZTools_Action.BANKING_REMOVE_MONEY:
                string removeSteam64;
                int removeAmount;
                if (!ReadStringSafe(ctx, removeSteam64) || !ReadIntSafe(ctx, removeAmount))
                {
                    success = false;
                    message = "Banking remove payload missing.";
                }
                else
                {
                    success = DeutschZTools_BankingBridge.RemoveMoney(removeSteam64, removeAmount, message);
                    string removeResultMessage = message;
                    ref array<string> bankingRowsAfterRemove = new array<string>;
                    string removeListMessage;
                    DeutschZTools_BankingBridge.Lookup(removeSteam64, bankingRowsAfterRemove, removeListMessage);
                    SendBankingList(sender, removeListMessage, bankingRowsAfterRemove);
                    message = removeResultMessage;
                }
                break;

            case DeutschZTools_Action.BANKING_AUDIT:
                string auditSteam64;
                if (!ReadStringSafe(ctx, auditSteam64))
                    auditSteam64 = "";

                ref array<string> auditRows = new array<string>;
                success = DeutschZTools_BankingBridge.Audit(auditSteam64, auditRows, message);
                SendBankingList(sender, message, auditRows);
                break;

            case DeutschZTools_Action.GROUPS_STATUS:
                success = DeutschZTools_GroupsBridge.GetStatus(message);
                break;

            case DeutschZTools_Action.GROUPS_RELOAD:
                success = DeutschZTools_GroupsBridge.Reload(message);
                break;

            case DeutschZTools_Action.GROUPS_LIST:
                ref array<string> groupRows = new array<string>;
                success = DeutschZTools_GroupsBridge.BuildGroupRows(groupRows, message);
                SendGroupsList(sender, message, groupRows);
                break;

            case DeutschZTools_Action.GROUPS_LOOKUP:
                string groupLookupSteam64;
                if (!ReadStringSafe(ctx, groupLookupSteam64))
                {
                    success = false;
                    message = "Target Steam64 missing.";
                }
                else
                {
                    ref array<string> groupLookupRows = new array<string>;
                    success = DeutschZTools_GroupsBridge.Lookup(groupLookupSteam64, groupLookupRows, message);
                    SendGroupsList(sender, message, groupLookupRows);
                }
                break;

            case DeutschZTools_Action.TRADERZ_STATUS:
                success = DeutschZTools_TraderZBridge.GetStatus(message);
                break;

            case DeutschZTools_Action.TRADERZ_RELOAD_ALL:
                success = DeutschZTools_TraderZBridge.ReloadAll(message);
                break;

            case DeutschZTools_Action.TRADERZ_RELOAD_SETTINGS:
                success = DeutschZTools_TraderZBridge.ReloadSettings(message);
                break;

            case DeutschZTools_Action.TRADERZ_RELOAD_TRADERS:
                success = DeutschZTools_TraderZBridge.ReloadTraders(message);
                break;

            case DeutschZTools_Action.TRADERZ_RELOAD_MARKET:
                success = DeutschZTools_TraderZBridge.ReloadMarket(message);
                break;

            case DeutschZTools_Action.TRADERZ_RELOAD_CURRENCY:
                success = DeutschZTools_TraderZBridge.ReloadCurrency(message);
                break;

            case DeutschZTools_Action.TRADERZ_RELOAD_SAFEZONES:
                success = DeutschZTools_TraderZBridge.ReloadSafezones(message);
                break;

            case DeutschZTools_Action.TRADERZ_LIST_TRADERS:
                ref array<string> traderRows = new array<string>;
                success = DeutschZTools_TraderZBridge.BuildTraderRows(traderRows, message);
                SendTraderZList(sender, message, traderRows);
                break;

            case DeutschZTools_Action.TRADERZ_LIST_CATEGORIES:
                ref array<string> traderCategoryRows = new array<string>;
                success = DeutschZTools_TraderZBridge.BuildCategoryRows(traderCategoryRows, message);
                SendTraderZList(sender, message, traderCategoryRows);
                break;

            case DeutschZTools_Action.TRADERZ_LIST_CATEGORY:
                string traderCategory;
                if (!ReadStringSafe(ctx, traderCategory))
                {
                    success = false;
                    message = "TraderZ category missing.";
                }
                else
                {
                    ref array<string> traderMarketRows = new array<string>;
                    success = DeutschZTools_TraderZBridge.BuildMarketRows(traderCategory, traderMarketRows, message);
                    SendTraderZList(sender, message, traderMarketRows);
                }
                break;

            case DeutschZTools_Action.PLAYERFUN_FREEZE:
                string funFreezeSteam64;
                if (!ReadStringSafe(ctx, funFreezeSteam64))
                {
                    success = false;
                    message = "Target Steam64 missing.";
                }
                else
                {
                    success = DeutschZTools_PlayerFunService.Freeze(funFreezeSteam64, message);
                }
                break;

            case DeutschZTools_Action.PLAYERFUN_UNFREEZE:
                string funUnfreezeSteam64;
                if (!ReadStringSafe(ctx, funUnfreezeSteam64))
                {
                    success = false;
                    message = "Target Steam64 missing.";
                }
                else
                {
                    success = DeutschZTools_PlayerFunService.Unfreeze(funUnfreezeSteam64, message);
                }
                break;

            case DeutschZTools_Action.PLAYERFUN_VOMIT:
                string funVomitSteam64;
                if (!ReadStringSafe(ctx, funVomitSteam64))
                {
                    success = false;
                    message = "Target Steam64 missing.";
                }
                else
                {
                    success = DeutschZTools_PlayerFunService.Vomit(funVomitSteam64, message);
                }
                break;

            case DeutschZTools_Action.PLAYERFUN_TINY:
                string funTinySteam64;
                if (!ReadStringSafe(ctx, funTinySteam64))
                {
                    success = false;
                    message = "Target Steam64 missing.";
                }
                else
                {
                    success = DeutschZTools_PlayerFunService.Tiny(funTinySteam64, message);
                }
                break;

            case DeutschZTools_Action.PLAYERFUN_GIANT:
                string funGiantSteam64;
                if (!ReadStringSafe(ctx, funGiantSteam64))
                {
                    success = false;
                    message = "Target Steam64 missing.";
                }
                else
                {
                    success = DeutschZTools_PlayerFunService.Giant(funGiantSteam64, message);
                }
                break;

            case DeutschZTools_Action.PLAYERFUN_RESET_SIZE:
                string funResetSteam64;
                if (!ReadStringSafe(ctx, funResetSteam64))
                {
                    success = false;
                    message = "Target Steam64 missing.";
                }
                else
                {
                    success = DeutschZTools_PlayerFunService.ResetSize(funResetSteam64, message);
                }
                break;

            case DeutschZTools_Action.PLAYERFUN_SPIN:
                string funSpinSteam64;
                if (!ReadStringSafe(ctx, funSpinSteam64))
                {
                    success = false;
                    message = "Target Steam64 missing.";
                }
                else
                {
                    success = DeutschZTools_PlayerFunService.Spin(funSpinSteam64, message);
                }
                break;

            case DeutschZTools_Action.PLAYERFUN_PIG_PRANK:
                string funPigSteam64;
                if (!ReadStringSafe(ctx, funPigSteam64))
                {
                    success = false;
                    message = "Target Steam64 missing.";
                }
                else
                {
                    success = DeutschZTools_PlayerFunService.PigPrank(funPigSteam64, message);
                }
                break;

            case DeutschZTools_Action.PLAYERFUN_GOAT_PRANK:
                string funGoatSteam64;
                if (!ReadStringSafe(ctx, funGoatSteam64))
                {
                    success = false;
                    message = "Target Steam64 missing.";
                }
                else
                {
                    success = DeutschZTools_PlayerFunService.GoatPrank(funGoatSteam64, message);
                }
                break;

            default:
                success = false;
                message = "Unknown action: " + action;
                break;
        }

        DeutschZTools_Logger.Admin(sender, "action=" + action + " success=" + success + " message=" + message);
        SendResult(sender, success, message);
    }

    static string GetRequiredPermission(int action)
    {
        switch (action)
        {
            case DeutschZTools_Action.PING:
            case DeutschZTools_Action.REQUEST_MENU_ACCESS:
                return DeutschZTools_Constants.PERM_MENU_OPEN;

            case DeutschZTools_Action.REQUEST_PLAYER_LIST:
                return DeutschZTools_Constants.PERM_PLAYER_LIST;

            case DeutschZTools_Action.HEAL_SELF:
            case DeutschZTools_Action.HEAL_PLAYER:
                return DeutschZTools_Constants.PERM_PLAYER_HEAL;

            case DeutschZTools_Action.TELEPORT_SELF_TO_POS:
                return DeutschZTools_Constants.PERM_MAP_TELEPORT;

            case DeutschZTools_Action.TELEPORT_TO_PLAYER:
            case DeutschZTools_Action.TELEPORT_PLAYER_TO_ME:
                return DeutschZTools_Constants.PERM_PLAYER_TELEPORT;

            case DeutschZTools_Action.REPAIR_NEAREST_VEHICLE:
                return DeutschZTools_Constants.PERM_VEHICLE_REPAIR;


            case DeutschZTools_Action.FLIP_NEAREST_VEHICLE:
                return DeutschZTools_Constants.PERM_VEHICLE_FLIP;

            case DeutschZTools_Action.TELEPORT_NEAREST_VEHICLE_TO_ME:
                return DeutschZTools_Constants.PERM_VEHICLE_TELEPORT;

            case DeutschZTools_Action.SPAWN_OBJECT:
                return DeutschZTools_Constants.PERM_SPAWN_OBJECT;

            case DeutschZTools_Action.SET_WEATHER_CLEAR:
            case DeutschZTools_Action.SET_WEATHER_RAIN:
            case DeutschZTools_Action.SET_WEATHER_STORM:
            case DeutschZTools_Action.SET_WEATHER_FOG:
                return DeutschZTools_Constants.PERM_WEATHER_SET;

            case DeutschZTools_Action.RELOAD_CONFIGS:
                return DeutschZTools_Constants.PERM_SERVER_CONFIG_RELOAD;

            case DeutschZTools_Action.KOTH_STATUS:
                return DeutschZTools_Constants.PERM_EVENT_STATUS;

            case DeutschZTools_Action.KOTH_FORCE_START:
                return DeutschZTools_Constants.PERM_EVENT_FORCE_START;

            case DeutschZTools_Action.KOTH_FORCE_STOP:
                return DeutschZTools_Constants.PERM_EVENT_FORCE_STOP;

            case DeutschZTools_Action.KOTH_RELOAD_CONFIGS:
            case DeutschZTools_Action.KOTH_SAVE_SETTINGS:
            case DeutschZTools_Action.KOTH_RELOAD_SETTINGS:
            case DeutschZTools_Action.KOTH_RELOAD_ZONES:
            case DeutschZTools_Action.KOTH_RELOAD_LOOT:
            case DeutschZTools_Action.KOTH_RELOAD_ALL:
                return DeutschZTools_Constants.PERM_EVENT_RELOAD;

            case DeutschZTools_Action.SERVER_RESTART_COUNTDOWN:
                return DeutschZTools_Constants.PERM_SERVER_RESTART;

            case DeutschZTools_Action.GARAGE_STATUS:
            case DeutschZTools_Action.GARAGE_RELOAD:
            case DeutschZTools_Action.GARAGE_LIST:
            case DeutschZTools_Action.GARAGE_IMPOUND_NEAREST:
                return DeutschZTools_Constants.PERM_GARAGE_ADMIN;

            case DeutschZTools_Action.BANKING_STATUS:
            case DeutschZTools_Action.BANKING_RELOAD:
            case DeutschZTools_Action.BANKING_LOOKUP:
            case DeutschZTools_Action.BANKING_ADD_MONEY:
            case DeutschZTools_Action.BANKING_REMOVE_MONEY:
            case DeutschZTools_Action.BANKING_AUDIT:
                return DeutschZTools_Constants.PERM_BANKING_ADMIN;

            case DeutschZTools_Action.GROUPS_STATUS:
            case DeutschZTools_Action.GROUPS_RELOAD:
            case DeutschZTools_Action.GROUPS_LIST:
            case DeutschZTools_Action.GROUPS_LOOKUP:
                return DeutschZTools_Constants.PERM_GROUPS_ADMIN;

            case DeutschZTools_Action.TRADERZ_STATUS:
            case DeutschZTools_Action.TRADERZ_RELOAD_ALL:
            case DeutschZTools_Action.TRADERZ_RELOAD_SETTINGS:
            case DeutschZTools_Action.TRADERZ_RELOAD_TRADERS:
            case DeutschZTools_Action.TRADERZ_RELOAD_MARKET:
            case DeutschZTools_Action.TRADERZ_RELOAD_CURRENCY:
            case DeutschZTools_Action.TRADERZ_RELOAD_SAFEZONES:
            case DeutschZTools_Action.TRADERZ_LIST_TRADERS:
            case DeutschZTools_Action.TRADERZ_LIST_CATEGORY:
            case DeutschZTools_Action.TRADERZ_LIST_CATEGORIES:
                return DeutschZTools_Constants.PERM_TRADERZ_ADMIN;

            case DeutschZTools_Action.PLAYERFUN_FREEZE:
            case DeutschZTools_Action.PLAYERFUN_UNFREEZE:
            case DeutschZTools_Action.PLAYERFUN_VOMIT:
            case DeutschZTools_Action.PLAYERFUN_TINY:
            case DeutschZTools_Action.PLAYERFUN_GIANT:
            case DeutschZTools_Action.PLAYERFUN_RESET_SIZE:
            case DeutschZTools_Action.PLAYERFUN_SPIN:
            case DeutschZTools_Action.PLAYERFUN_PIG_PRANK:
            case DeutschZTools_Action.PLAYERFUN_GOAT_PRANK:
                return DeutschZTools_Constants.PERM_PLAYER_FUN;
        }

        return DeutschZTools_Constants.PERM_MENU_OPEN;
    }
}
