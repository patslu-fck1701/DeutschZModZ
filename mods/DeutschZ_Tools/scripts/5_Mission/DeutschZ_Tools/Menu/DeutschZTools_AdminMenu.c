class DeutschZTools_AdminMenu extends UIScriptedMenu
{
    protected ButtonWidget m_BtnTabDashboard;
    protected ButtonWidget m_BtnTabPlayers;
    protected ButtonWidget m_BtnTabMapTeleport;
    protected ButtonWidget m_BtnTabSpawn;
    protected ButtonWidget m_BtnTabVehicles;
    protected ButtonWidget m_BtnTabWeather;
    protected ButtonWidget m_BtnTabEvents;
    protected ButtonWidget m_BtnTabKothSettings;
    protected ButtonWidget m_BtnTabServer;
    protected ButtonWidget m_BtnTabDebug;
    protected ButtonWidget m_BtnTabGarage;
    protected ButtonWidget m_BtnTabBanking;
    protected ButtonWidget m_BtnTabGroups;
    protected ButtonWidget m_BtnTabPlayerFun;
    protected ButtonWidget m_BtnTabTraderZ;

    protected ButtonWidget m_BtnPing;
    protected ButtonWidget m_BtnPlayerList;
    protected ButtonWidget m_BtnReloadConfigs;
    protected ButtonWidget m_BtnHealSelf;
    protected ButtonWidget m_BtnHealTarget;
    protected ButtonWidget m_BtnTpToPlayer;
    protected ButtonWidget m_BtnBringPlayer;
    protected ButtonWidget m_BtnRepairVehicle;
    protected ButtonWidget m_BtnWeatherClear;
    protected ButtonWidget m_BtnWeatherRain;
    protected ButtonWidget m_BtnWeatherStorm;
    protected ButtonWidget m_BtnWeatherFog;
    protected ButtonWidget m_BtnKothStatus;
    protected ButtonWidget m_BtnKothForceStart;
    protected ButtonWidget m_BtnKothForceStop;
    protected ButtonWidget m_BtnKothReload;
    protected ButtonWidget m_BtnRestart;
    protected ButtonWidget m_BtnClose;
    protected ButtonWidget m_BtnMapLight;
    protected ButtonWidget m_BtnMapDark;
    protected ButtonWidget m_BtnTeleportCoords;
    protected ButtonWidget m_BtnSpawn;

    protected ButtonWidget m_BtnDashPlayerList;
    protected ButtonWidget m_BtnDashReloadConfigs;
    protected ButtonWidget m_BtnDashKothStatus;
    protected ButtonWidget m_BtnDashKothReload;
    protected ButtonWidget m_BtnDashWeatherClear;
    protected ButtonWidget m_BtnPlaceholderInventory;
    protected ButtonWidget m_BtnPlaceholderSpectate;
    protected ButtonWidget m_BtnPlaceholderKill;
    protected ButtonWidget m_BtnPlaceholderMapClick;
    protected ButtonWidget m_BtnSetAdminPosFields;
    protected ButtonWidget m_BtnSpawnGround;
    protected ButtonWidget m_BtnSpawnInventory;
    protected ButtonWidget m_BtnSpawnTarget;
    protected ButtonWidget m_BtnSpawnCatWeapons;
    protected ButtonWidget m_BtnSpawnCatVehicles;
    protected ButtonWidget m_BtnSpawnCatClothing;
    protected ButtonWidget m_BtnSpawnCatTools;
    protected ButtonWidget m_BtnSpawnCatBase;
    protected ButtonWidget m_BtnSpawnCatMedical;
    protected ButtonWidget m_BtnSpawnCatFood;
    protected ButtonWidget m_BtnSpawnCatMisc;
    protected ButtonWidget m_BtnSpawnPresetPrev;
    protected ButtonWidget m_BtnSpawnPresetNext;
    protected ButtonWidget m_BtnVehicleRefuel;
    protected ButtonWidget m_BtnVehicleFlip;
    protected ButtonWidget m_BtnVehicleTeleport;
    protected ButtonWidget m_BtnVehicleLock;
    protected ButtonWidget m_BtnVehicleDelete;
    protected ButtonWidget m_BtnWeatherApply;
    protected ButtonWidget m_BtnTimeApply;
    protected ButtonWidget m_BtnWeatherReset;
    protected ButtonWidget m_BtnServerReloadAdmins;
    protected ButtonWidget m_BtnServerMessage;
    protected ButtonWidget m_BtnDebugPrint;
    protected ButtonWidget m_BtnDebugReloadUI;
    protected ButtonWidget m_BtnGarageStatus;
    protected ButtonWidget m_BtnGarageReload;
    protected ButtonWidget m_BtnGarageVehicleList;
    protected ButtonWidget m_BtnGarageImpound;
    protected ButtonWidget m_BtnBankingStatus;
    protected ButtonWidget m_BtnBankingReload;
    protected ButtonWidget m_BtnBankingLookup;
    protected ButtonWidget m_BtnBankingAddMoney;
    protected ButtonWidget m_BtnBankingRemoveMoney;
    protected ButtonWidget m_BtnBankingAudit;
    protected ButtonWidget m_BtnGroupsStatus;
    protected ButtonWidget m_BtnGroupsReload;
    protected ButtonWidget m_BtnGroupsList;
    protected ButtonWidget m_BtnGroupsLookup;
    protected ButtonWidget m_BtnPlayerFunFreeze;
    protected ButtonWidget m_BtnPlayerFunUnfreeze;
    protected ButtonWidget m_BtnPlayerFunVomit;
    protected ButtonWidget m_BtnPlayerFunTiny;
    protected ButtonWidget m_BtnPlayerFunGiant;
    protected ButtonWidget m_BtnPlayerFunResetSize;
    protected ButtonWidget m_BtnPlayerFunSpin;
    protected ButtonWidget m_BtnPlayerFunPig;
    protected ButtonWidget m_BtnPlayerFunGoat;
    protected ButtonWidget m_BtnTraderZStatus;
    protected ButtonWidget m_BtnTraderZReloadAll;
    protected ButtonWidget m_BtnTraderZReloadSettings;
    protected ButtonWidget m_BtnTraderZReloadTraders;
    protected ButtonWidget m_BtnTraderZReloadMarket;
    protected ButtonWidget m_BtnTraderZReloadCurrency;
    protected ButtonWidget m_BtnTraderZReloadSafezones;
    protected ButtonWidget m_BtnTraderZListTraders;
    protected ButtonWidget m_BtnTraderZListCategory;
    protected ButtonWidget m_BtnTraderZListCategories;

    protected ButtonWidget m_BtnKothTabGeneral;
    protected ButtonWidget m_BtnKothTabSchedule;
    protected ButtonWidget m_BtnKothTabZones;
    protected ButtonWidget m_BtnKothTabCapture;
    protected ButtonWidget m_BtnKothTabRewards;
    protected ButtonWidget m_BtnKothTabAI;
    protected ButtonWidget m_BtnKothTabMarkers;
    protected ButtonWidget m_BtnKothTabEffects;
    protected ButtonWidget m_BtnKothTabSafety;
    protected ButtonWidget m_BtnKothSaveSettings;
    protected ButtonWidget m_BtnKothReloadSettings;
    protected ButtonWidget m_BtnKothReloadZones;
    protected ButtonWidget m_BtnKothReloadLoot;
    protected ButtonWidget m_BtnKothReloadAll;
    protected ButtonWidget m_BtnKothScheduleSave;
    protected ButtonWidget m_BtnKothCaptureSave;
    protected ButtonWidget m_BtnKothFullReload;

    protected EditBoxWidget m_SpawnClassname;
    protected EditBoxWidget m_SpawnAttachments;
    protected ItemPreviewWidget m_SpawnItemPreview;
    protected EntityAI m_SpawnPreviewEntity;
    protected EditBoxWidget m_TeleportX;
    protected EditBoxWidget m_TeleportZ;
    protected EditBoxWidget m_TargetSteam64;
    protected EditBoxWidget m_GarageSteam64;
    protected EditBoxWidget m_BankingSteam64;
    protected EditBoxWidget m_BankingAmount;
    protected EditBoxWidget m_TraderZCategory;
    protected MapWidget m_MapWidget;
    protected Widget m_MapFrame;
    protected Widget m_ContentHost;
    protected Widget m_CurrentFrame;
    protected ButtonWidget m_BtnMapClose;
    protected TextWidget m_StatusText;
    protected TextWidget m_HeaderStatusText;
    protected TextWidget m_SelectedTabText;
    protected TextWidget m_DashboardOnlineText;
    protected TextWidget m_AdminPositionText;
    protected MultilineTextWidget m_PlayerListText;
    protected MultilineTextWidget m_DebugText;
    protected TextWidget m_PlayerListSummary;
    protected ref array<ButtonWidget> m_PlayerRowButtons;
    protected ref array<TextWidget> m_PlayerRowNumberCells;
    protected ref array<TextWidget> m_PlayerRowNameCells;
    protected ref array<TextWidget> m_PlayerRowSteamCells;
    protected ref array<TextWidget> m_PlayerRowStateCells;
    protected ref array<TextWidget> m_PlayerRowPosCells;
    protected ref TStringArray m_PlayerRowSteam64;

    protected ref array<TextWidget> m_GarageRowNumberCells;
    protected ref array<TextWidget> m_GarageRowClassCells;
    protected ref array<TextWidget> m_GarageRowStateCells;
    protected ref array<TextWidget> m_GarageRowOwnerCells;
    protected ref array<TextWidget> m_GarageRowPosCells;

    protected ref array<TextWidget> m_BankingRowNumberCells;
    protected ref array<TextWidget> m_BankingRowPlayerCells;
    protected ref array<TextWidget> m_BankingRowBalanceCells;
    protected ref array<TextWidget> m_BankingRowTypeCells;
    protected ref array<TextWidget> m_BankingRowTimeCells;

    protected ref array<TextWidget> m_GroupsRowNumberCells;
    protected ref array<TextWidget> m_GroupsRowNameCells;
    protected ref array<TextWidget> m_GroupsRowTagCells;
    protected ref array<TextWidget> m_GroupsRowMembersCells;
    protected ref array<TextWidget> m_GroupsRowOwnerCells;

    protected ref array<TextWidget> m_TraderZRowNumberCells;
    protected ref array<TextWidget> m_TraderZRowTypeCells;
    protected ref array<TextWidget> m_TraderZRowNameCells;
    protected ref array<TextWidget> m_TraderZRowValueCells;
    protected ref array<TextWidget> m_TraderZRowInfoCells;

    protected Widget m_KothPanelGeneral;
    protected Widget m_KothPanelSchedule;
    protected Widget m_KothPanelZones;
    protected Widget m_KothPanelCapture;
    protected Widget m_KothPanelRewards;
    protected Widget m_KothPanelAI;
    protected Widget m_KothPanelMarkers;
    protected Widget m_KothPanelEffects;
    protected Widget m_KothPanelSafety;

    protected string m_SelectedTabKey;
    protected string m_SelectedTabName;
    protected string m_SelectedSteam64;
    protected string m_LastStatus;
    protected int m_LastPlayerCount;
    protected bool m_RequestPlayersOnShow;
    protected ref array<ButtonWidget> m_SpawnPresetButtons;
    protected ref TStringArray m_SpawnPresetClasses;
    protected string m_SpawnPresetCategory;
    protected int m_SpawnPresetPage;

    override Widget Init()
    {
        layoutRoot = GetGame().GetWorkspace().CreateWidgets("DeutschZ_Tools/gui/layouts/deutschztools_admin_menu.layout");
        if (!layoutRoot)
        {
            Print(DeutschZTools_Constants.LOG_PREFIX + "Failed to load admin menu layout.");
            return null;
        }

        layoutRoot.Show(true);
        DeutschZTools_BindMainWidgets();
        SetStatus("bereit");
        ShowPanel("Dashboard");
        return layoutRoot;
    }

    void DeutschZTools_BindMainWidgets()
    {
        m_BtnTabDashboard = ButtonWidget.Cast(layoutRoot.FindAnyWidget("BtnTabDashboard"));
        m_BtnTabPlayers = ButtonWidget.Cast(layoutRoot.FindAnyWidget("BtnTabPlayers"));
        m_BtnTabMapTeleport = ButtonWidget.Cast(layoutRoot.FindAnyWidget("BtnTabMapTeleport"));
        m_BtnTabSpawn = ButtonWidget.Cast(layoutRoot.FindAnyWidget("BtnTabSpawn"));
        m_BtnTabVehicles = ButtonWidget.Cast(layoutRoot.FindAnyWidget("BtnTabVehicles"));
        m_BtnTabWeather = ButtonWidget.Cast(layoutRoot.FindAnyWidget("BtnTabWeather"));
        m_BtnTabEvents = ButtonWidget.Cast(layoutRoot.FindAnyWidget("BtnTabEvents"));
        m_BtnTabKothSettings = ButtonWidget.Cast(layoutRoot.FindAnyWidget("BtnTabKothSettings"));
        m_BtnTabServer = ButtonWidget.Cast(layoutRoot.FindAnyWidget("BtnTabServer"));
        m_BtnTabDebug = ButtonWidget.Cast(layoutRoot.FindAnyWidget("BtnTabDebug"));
        m_BtnTabGarage = ButtonWidget.Cast(layoutRoot.FindAnyWidget("BtnTabGarage"));
        m_BtnTabBanking = ButtonWidget.Cast(layoutRoot.FindAnyWidget("BtnTabBanking"));
        m_BtnTabGroups = ButtonWidget.Cast(layoutRoot.FindAnyWidget("BtnTabGroups"));
        m_BtnTabPlayerFun = ButtonWidget.Cast(layoutRoot.FindAnyWidget("BtnTabPlayerFun"));
        m_BtnTabTraderZ = ButtonWidget.Cast(layoutRoot.FindAnyWidget("BtnTabTraderZ"));
        m_BtnClose = ButtonWidget.Cast(layoutRoot.FindAnyWidget("BtnClose"));
        m_ContentHost = layoutRoot.FindAnyWidget("ContentHost");
        m_StatusText = TextWidget.Cast(layoutRoot.FindAnyWidget("StatusText"));
        m_HeaderStatusText = TextWidget.Cast(layoutRoot.FindAnyWidget("HeaderStatusText"));
        m_SelectedTabText = TextWidget.Cast(layoutRoot.FindAnyWidget("SelectedTabText"));
        DeutschZTools_ApplyGermanButtonLabels();
    }

    void DeutschZTools_ClearDynamicRefs()
    {
        m_BtnPing = null;
        m_BtnPlayerList = null;
        m_BtnReloadConfigs = null;
        m_BtnHealSelf = null;
        m_BtnHealTarget = null;
        m_BtnTpToPlayer = null;
        m_BtnBringPlayer = null;
        m_BtnRepairVehicle = null;
        m_BtnWeatherClear = null;
        m_BtnWeatherRain = null;
        m_BtnWeatherStorm = null;
        m_BtnWeatherFog = null;
        m_BtnKothStatus = null;
        m_BtnKothForceStart = null;
        m_BtnKothForceStop = null;
        m_BtnKothReload = null;
        m_BtnRestart = null;
        m_BtnMapLight = null;
        m_BtnMapDark = null;
        m_BtnTeleportCoords = null;
        m_BtnSpawn = null;
        m_BtnDashPlayerList = null;
        m_BtnDashReloadConfigs = null;
        m_BtnDashKothStatus = null;
        m_BtnDashKothReload = null;
        m_BtnDashWeatherClear = null;
        m_BtnPlaceholderInventory = null;
        m_BtnPlaceholderSpectate = null;
        m_BtnPlaceholderKill = null;
        m_BtnPlaceholderMapClick = null;
        m_BtnSetAdminPosFields = null;
        m_BtnSpawnGround = null;
        m_BtnSpawnInventory = null;
        m_BtnSpawnTarget = null;
        m_BtnSpawnCatWeapons = null;
        m_BtnSpawnCatVehicles = null;
        m_BtnSpawnCatClothing = null;
        m_BtnSpawnCatTools = null;
        m_BtnSpawnCatBase = null;
        m_BtnSpawnCatMedical = null;
        m_BtnSpawnCatFood = null;
        m_BtnSpawnCatMisc = null;
        m_BtnSpawnPresetPrev = null;
        m_BtnSpawnPresetNext = null;
        m_BtnVehicleRefuel = null;
        m_BtnVehicleFlip = null;
        m_BtnVehicleTeleport = null;
        m_BtnVehicleLock = null;
        m_BtnVehicleDelete = null;
        m_BtnWeatherApply = null;
        m_BtnTimeApply = null;
        m_BtnWeatherReset = null;
        m_BtnServerReloadAdmins = null;
        m_BtnServerMessage = null;
        m_BtnDebugPrint = null;
        m_BtnDebugReloadUI = null;
        m_BtnGarageStatus = null;
        m_BtnGarageReload = null;
        m_BtnGarageVehicleList = null;
        m_BtnGarageImpound = null;
        m_BtnBankingStatus = null;
        m_BtnBankingReload = null;
        m_BtnBankingLookup = null;
        m_BtnBankingAddMoney = null;
        m_BtnBankingRemoveMoney = null;
        m_BtnBankingAudit = null;
        m_BtnGroupsStatus = null;
        m_BtnGroupsReload = null;
        m_BtnGroupsList = null;
        m_BtnGroupsLookup = null;
        m_BtnPlayerFunFreeze = null;
        m_BtnPlayerFunUnfreeze = null;
        m_BtnPlayerFunVomit = null;
        m_BtnPlayerFunTiny = null;
        m_BtnPlayerFunGiant = null;
        m_BtnPlayerFunResetSize = null;
        m_BtnPlayerFunSpin = null;
        m_BtnPlayerFunPig = null;
        m_BtnPlayerFunGoat = null;
        m_BtnTraderZStatus = null;
        m_BtnTraderZReloadAll = null;
        m_BtnTraderZReloadSettings = null;
        m_BtnTraderZReloadTraders = null;
        m_BtnTraderZReloadMarket = null;
        m_BtnTraderZReloadCurrency = null;
        m_BtnTraderZReloadSafezones = null;
        m_BtnTraderZListTraders = null;
        m_BtnTraderZListCategory = null;
        m_BtnTraderZListCategories = null;
        m_BtnKothTabGeneral = null;
        m_BtnKothTabSchedule = null;
        m_BtnKothTabZones = null;
        m_BtnKothTabCapture = null;
        m_BtnKothTabRewards = null;
        m_BtnKothTabAI = null;
        m_BtnKothTabMarkers = null;
        m_BtnKothTabEffects = null;
        m_BtnKothTabSafety = null;
        m_BtnKothSaveSettings = null;
        m_BtnKothReloadSettings = null;
        m_BtnKothReloadZones = null;
        m_BtnKothReloadLoot = null;
        m_BtnKothReloadAll = null;
        m_BtnKothScheduleSave = null;
        m_BtnKothCaptureSave = null;
        m_BtnKothFullReload = null;
        DeutschZTools_ClearSpawnPreview();
        m_SpawnClassname = null;
        m_SpawnAttachments = null;
        m_SpawnItemPreview = null;
        m_SpawnPresetButtons = null;
        m_SpawnPresetClasses = null;
        m_TeleportX = null;
        m_TeleportZ = null;
        m_TargetSteam64 = null;
        m_GarageSteam64 = null;
        m_BankingSteam64 = null;
        m_BankingAmount = null;
        m_TraderZCategory = null;
        m_MapWidget = null;
        m_MapFrame = null;
        m_BtnMapClose = null;
        m_DashboardOnlineText = null;
        m_AdminPositionText = null;
        m_PlayerListText = null;
        m_DebugText = null;
        m_PlayerListSummary = null;
        m_PlayerRowButtons = null;
        m_PlayerRowNumberCells = null;
        m_PlayerRowNameCells = null;
        m_PlayerRowSteamCells = null;
        m_PlayerRowStateCells = null;
        m_PlayerRowPosCells = null;
        m_PlayerRowSteam64 = null;
        m_GarageRowNumberCells = null;
        m_GarageRowClassCells = null;
        m_GarageRowStateCells = null;
        m_GarageRowOwnerCells = null;
        m_GarageRowPosCells = null;
        m_BankingRowNumberCells = null;
        m_BankingRowPlayerCells = null;
        m_BankingRowBalanceCells = null;
        m_BankingRowTypeCells = null;
        m_BankingRowTimeCells = null;
        m_GroupsRowNumberCells = null;
        m_GroupsRowNameCells = null;
        m_GroupsRowTagCells = null;
        m_GroupsRowMembersCells = null;
        m_GroupsRowOwnerCells = null;
        m_TraderZRowNumberCells = null;
        m_TraderZRowTypeCells = null;
        m_TraderZRowNameCells = null;
        m_TraderZRowValueCells = null;
        m_TraderZRowInfoCells = null;
        m_KothPanelGeneral = null;
        m_KothPanelSchedule = null;
        m_KothPanelZones = null;
        m_KothPanelCapture = null;
        m_KothPanelRewards = null;
        m_KothPanelAI = null;
        m_KothPanelMarkers = null;
        m_KothPanelEffects = null;
        m_KothPanelSafety = null;
    }

    Widget DeutschZTools_FrameFind(string name)
    {
        if (!m_CurrentFrame)
            return null;

        return m_CurrentFrame.FindAnyWidget(name);
    }

    void DeutschZTools_BindFrameWidgets()
    {
        DeutschZTools_ClearDynamicRefs();

        m_BtnPing = ButtonWidget.Cast(DeutschZTools_FrameFind("BtnPing"));
        m_BtnPlayerList = ButtonWidget.Cast(DeutschZTools_FrameFind("BtnPlayerList"));
        m_BtnReloadConfigs = ButtonWidget.Cast(DeutschZTools_FrameFind("BtnReloadConfigs"));
        m_BtnHealSelf = ButtonWidget.Cast(DeutschZTools_FrameFind("BtnHealSelf"));
        m_BtnHealTarget = ButtonWidget.Cast(DeutschZTools_FrameFind("BtnHealTarget"));
        m_BtnTpToPlayer = ButtonWidget.Cast(DeutschZTools_FrameFind("BtnTpToPlayer"));
        m_BtnBringPlayer = ButtonWidget.Cast(DeutschZTools_FrameFind("BtnBringPlayer"));
        m_BtnRepairVehicle = ButtonWidget.Cast(DeutschZTools_FrameFind("BtnRepairVehicle"));
        m_BtnWeatherClear = ButtonWidget.Cast(DeutschZTools_FrameFind("BtnWeatherClear"));
        m_BtnWeatherRain = ButtonWidget.Cast(DeutschZTools_FrameFind("BtnWeatherRain"));
        m_BtnWeatherStorm = ButtonWidget.Cast(DeutschZTools_FrameFind("BtnWeatherStorm"));
        m_BtnWeatherFog = ButtonWidget.Cast(DeutschZTools_FrameFind("BtnWeatherFog"));
        m_BtnKothStatus = ButtonWidget.Cast(DeutschZTools_FrameFind("BtnKothStatus"));
        m_BtnKothForceStart = ButtonWidget.Cast(DeutschZTools_FrameFind("BtnKothForceStart"));
        m_BtnKothForceStop = ButtonWidget.Cast(DeutschZTools_FrameFind("BtnKothForceStop"));
        m_BtnKothReload = ButtonWidget.Cast(DeutschZTools_FrameFind("BtnKothReload"));
        m_BtnRestart = ButtonWidget.Cast(DeutschZTools_FrameFind("BtnRestart"));
        m_BtnMapLight = ButtonWidget.Cast(DeutschZTools_FrameFind("BtnMapLight"));
        m_BtnMapDark = ButtonWidget.Cast(DeutschZTools_FrameFind("BtnMapDark"));
        m_BtnTeleportCoords = ButtonWidget.Cast(DeutschZTools_FrameFind("BtnTeleportCoords"));
        m_BtnSpawn = ButtonWidget.Cast(DeutschZTools_FrameFind("BtnSpawn"));
        m_BtnDashPlayerList = ButtonWidget.Cast(DeutschZTools_FrameFind("BtnDashPlayerList"));
        m_BtnDashReloadConfigs = ButtonWidget.Cast(DeutschZTools_FrameFind("BtnDashReloadConfigs"));
        m_BtnDashKothStatus = ButtonWidget.Cast(DeutschZTools_FrameFind("BtnDashKothStatus"));
        m_BtnDashKothReload = ButtonWidget.Cast(DeutschZTools_FrameFind("BtnDashKothReload"));
        m_BtnDashWeatherClear = ButtonWidget.Cast(DeutschZTools_FrameFind("BtnDashWeatherClear"));
        m_BtnPlaceholderInventory = ButtonWidget.Cast(DeutschZTools_FrameFind("BtnPlaceholderInventory"));
        m_BtnPlaceholderSpectate = ButtonWidget.Cast(DeutschZTools_FrameFind("BtnPlaceholderSpectate"));
        m_BtnPlaceholderKill = ButtonWidget.Cast(DeutschZTools_FrameFind("BtnPlaceholderKill"));
        m_BtnPlaceholderMapClick = ButtonWidget.Cast(DeutschZTools_FrameFind("BtnPlaceholderMapClick"));
        m_BtnSetAdminPosFields = ButtonWidget.Cast(DeutschZTools_FrameFind("BtnSetAdminPosFields"));
        m_BtnSpawnGround = ButtonWidget.Cast(DeutschZTools_FrameFind("BtnSpawnGround"));
        m_BtnSpawnInventory = ButtonWidget.Cast(DeutschZTools_FrameFind("BtnSpawnInventory"));
        m_BtnSpawnTarget = ButtonWidget.Cast(DeutschZTools_FrameFind("BtnSpawnTarget"));
        m_BtnSpawnCatWeapons = ButtonWidget.Cast(DeutschZTools_FrameFind("BtnSpawnCatWeapons"));
        m_BtnSpawnCatVehicles = ButtonWidget.Cast(DeutschZTools_FrameFind("BtnSpawnCatVehicles"));
        m_BtnSpawnCatClothing = ButtonWidget.Cast(DeutschZTools_FrameFind("BtnSpawnCatClothing"));
        m_BtnSpawnCatTools = ButtonWidget.Cast(DeutschZTools_FrameFind("BtnSpawnCatTools"));
        m_BtnSpawnCatBase = ButtonWidget.Cast(DeutschZTools_FrameFind("BtnSpawnCatBase"));
        m_BtnSpawnCatMedical = ButtonWidget.Cast(DeutschZTools_FrameFind("BtnSpawnCatMedical"));
        m_BtnSpawnCatFood = ButtonWidget.Cast(DeutschZTools_FrameFind("BtnSpawnCatFood"));
        m_BtnSpawnCatMisc = ButtonWidget.Cast(DeutschZTools_FrameFind("BtnSpawnCatMisc"));
        m_BtnSpawnPresetPrev = ButtonWidget.Cast(DeutschZTools_FrameFind("BtnSpawnPresetPrev"));
        m_BtnSpawnPresetNext = ButtonWidget.Cast(DeutschZTools_FrameFind("BtnSpawnPresetNext"));
        m_BtnVehicleRefuel = ButtonWidget.Cast(DeutschZTools_FrameFind("BtnVehicleRefuel"));
        m_BtnVehicleFlip = ButtonWidget.Cast(DeutschZTools_FrameFind("BtnVehicleFlip"));
        m_BtnVehicleTeleport = ButtonWidget.Cast(DeutschZTools_FrameFind("BtnVehicleTeleport"));
        m_BtnVehicleLock = ButtonWidget.Cast(DeutschZTools_FrameFind("BtnVehicleLock"));
        m_BtnVehicleDelete = ButtonWidget.Cast(DeutschZTools_FrameFind("BtnVehicleDelete"));
        m_BtnWeatherApply = ButtonWidget.Cast(DeutschZTools_FrameFind("BtnWeatherApply"));
        m_BtnTimeApply = ButtonWidget.Cast(DeutschZTools_FrameFind("BtnTimeApply"));
        m_BtnWeatherReset = ButtonWidget.Cast(DeutschZTools_FrameFind("BtnWeatherReset"));
        m_BtnServerReloadAdmins = ButtonWidget.Cast(DeutschZTools_FrameFind("BtnServerReloadAdmins"));
        m_BtnServerMessage = ButtonWidget.Cast(DeutschZTools_FrameFind("BtnServerMessage"));
        m_BtnDebugPrint = ButtonWidget.Cast(DeutschZTools_FrameFind("BtnDebugPrint"));
        m_BtnDebugReloadUI = ButtonWidget.Cast(DeutschZTools_FrameFind("BtnDebugReloadUI"));
        m_BtnGarageStatus = ButtonWidget.Cast(DeutschZTools_FrameFind("BtnGarageStatus"));
        m_BtnGarageReload = ButtonWidget.Cast(DeutschZTools_FrameFind("BtnGarageReload"));
        m_BtnGarageVehicleList = ButtonWidget.Cast(DeutschZTools_FrameFind("BtnGarageVehicleList"));
        m_BtnGarageImpound = ButtonWidget.Cast(DeutschZTools_FrameFind("BtnGarageImpound"));
        m_BtnBankingStatus = ButtonWidget.Cast(DeutschZTools_FrameFind("BtnBankingStatus"));
        m_BtnBankingReload = ButtonWidget.Cast(DeutschZTools_FrameFind("BtnBankingReload"));
        m_BtnBankingLookup = ButtonWidget.Cast(DeutschZTools_FrameFind("BtnBankingLookup"));
        m_BtnBankingAddMoney = ButtonWidget.Cast(DeutschZTools_FrameFind("BtnBankingAddMoney"));
        m_BtnBankingRemoveMoney = ButtonWidget.Cast(DeutschZTools_FrameFind("BtnBankingRemoveMoney"));
        m_BtnBankingAudit = ButtonWidget.Cast(DeutschZTools_FrameFind("BtnBankingAudit"));
        m_BtnGroupsStatus = ButtonWidget.Cast(DeutschZTools_FrameFind("BtnGroupsStatus"));
        m_BtnGroupsReload = ButtonWidget.Cast(DeutschZTools_FrameFind("BtnGroupsReload"));
        m_BtnGroupsList = ButtonWidget.Cast(DeutschZTools_FrameFind("BtnGroupsList"));
        m_BtnGroupsLookup = ButtonWidget.Cast(DeutschZTools_FrameFind("BtnGroupsLookup"));
        m_BtnPlayerFunFreeze = ButtonWidget.Cast(DeutschZTools_FrameFind("BtnPlayerFunFreeze"));
        m_BtnPlayerFunUnfreeze = ButtonWidget.Cast(DeutschZTools_FrameFind("BtnPlayerFunUnfreeze"));
        m_BtnPlayerFunVomit = ButtonWidget.Cast(DeutschZTools_FrameFind("BtnPlayerFunVomit"));
        m_BtnPlayerFunTiny = ButtonWidget.Cast(DeutschZTools_FrameFind("BtnPlayerFunTiny"));
        m_BtnPlayerFunGiant = ButtonWidget.Cast(DeutschZTools_FrameFind("BtnPlayerFunGiant"));
        m_BtnPlayerFunResetSize = ButtonWidget.Cast(DeutschZTools_FrameFind("BtnPlayerFunResetSize"));
        m_BtnPlayerFunSpin = ButtonWidget.Cast(DeutschZTools_FrameFind("BtnPlayerFunSpin"));
        m_BtnPlayerFunPig = ButtonWidget.Cast(DeutschZTools_FrameFind("BtnPlayerFunPig"));
        m_BtnPlayerFunGoat = ButtonWidget.Cast(DeutschZTools_FrameFind("BtnPlayerFunGoat"));
        m_BtnTraderZStatus = ButtonWidget.Cast(DeutschZTools_FrameFind("BtnTraderZStatus"));
        m_BtnTraderZReloadAll = ButtonWidget.Cast(DeutschZTools_FrameFind("BtnTraderZReloadAll"));
        m_BtnTraderZReloadSettings = ButtonWidget.Cast(DeutschZTools_FrameFind("BtnTraderZReloadSettings"));
        m_BtnTraderZReloadTraders = ButtonWidget.Cast(DeutschZTools_FrameFind("BtnTraderZReloadTraders"));
        m_BtnTraderZReloadMarket = ButtonWidget.Cast(DeutschZTools_FrameFind("BtnTraderZReloadMarket"));
        m_BtnTraderZReloadCurrency = ButtonWidget.Cast(DeutschZTools_FrameFind("BtnTraderZReloadCurrency"));
        m_BtnTraderZReloadSafezones = ButtonWidget.Cast(DeutschZTools_FrameFind("BtnTraderZReloadSafezones"));
        m_BtnTraderZListTraders = ButtonWidget.Cast(DeutschZTools_FrameFind("BtnTraderZListTraders"));
        m_BtnTraderZListCategory = ButtonWidget.Cast(DeutschZTools_FrameFind("BtnTraderZListCategory"));
        m_BtnTraderZListCategories = ButtonWidget.Cast(DeutschZTools_FrameFind("BtnTraderZListCategories"));
        m_BtnKothTabGeneral = ButtonWidget.Cast(DeutschZTools_FrameFind("BtnKothTabGeneral"));
        m_BtnKothTabSchedule = ButtonWidget.Cast(DeutschZTools_FrameFind("BtnKothTabSchedule"));
        m_BtnKothTabZones = ButtonWidget.Cast(DeutschZTools_FrameFind("BtnKothTabZones"));
        m_BtnKothTabCapture = ButtonWidget.Cast(DeutschZTools_FrameFind("BtnKothTabCapture"));
        m_BtnKothTabRewards = ButtonWidget.Cast(DeutschZTools_FrameFind("BtnKothTabRewards"));
        m_BtnKothTabAI = ButtonWidget.Cast(DeutschZTools_FrameFind("BtnKothTabAI"));
        m_BtnKothTabMarkers = ButtonWidget.Cast(DeutschZTools_FrameFind("BtnKothTabMarkers"));
        m_BtnKothTabEffects = ButtonWidget.Cast(DeutschZTools_FrameFind("BtnKothTabEffects"));
        m_BtnKothTabSafety = ButtonWidget.Cast(DeutschZTools_FrameFind("BtnKothTabSafety"));
        m_BtnKothSaveSettings = ButtonWidget.Cast(DeutschZTools_FrameFind("BtnKothSaveSettings"));
        m_BtnKothReloadSettings = ButtonWidget.Cast(DeutschZTools_FrameFind("BtnKothReloadSettings"));
        m_BtnKothReloadZones = ButtonWidget.Cast(DeutschZTools_FrameFind("BtnKothReloadZones"));
        m_BtnKothReloadLoot = ButtonWidget.Cast(DeutschZTools_FrameFind("BtnKothReloadLoot"));
        m_BtnKothReloadAll = ButtonWidget.Cast(DeutschZTools_FrameFind("BtnKothReloadAll"));
        m_BtnKothScheduleSave = ButtonWidget.Cast(DeutschZTools_FrameFind("BtnKothScheduleSave"));
        m_BtnKothCaptureSave = ButtonWidget.Cast(DeutschZTools_FrameFind("BtnKothCaptureSave"));
        m_BtnKothFullReload = ButtonWidget.Cast(DeutschZTools_FrameFind("BtnKothFullReload"));
        m_SpawnClassname = EditBoxWidget.Cast(DeutschZTools_FrameFind("SpawnClassname"));
        m_SpawnAttachments = EditBoxWidget.Cast(DeutschZTools_FrameFind("SpawnAttachments"));
        m_SpawnItemPreview = ItemPreviewWidget.Cast(DeutschZTools_FrameFind("SpawnItemPreview"));
        m_TeleportX = EditBoxWidget.Cast(DeutschZTools_FrameFind("TeleportX"));
        m_TeleportZ = EditBoxWidget.Cast(DeutschZTools_FrameFind("TeleportZ"));
        m_TargetSteam64 = EditBoxWidget.Cast(DeutschZTools_FrameFind("TargetSteam64"));
        m_GarageSteam64 = EditBoxWidget.Cast(DeutschZTools_FrameFind("GarageSteam64"));
        m_BankingSteam64 = EditBoxWidget.Cast(DeutschZTools_FrameFind("BankingSteam64"));
        m_BankingAmount = EditBoxWidget.Cast(DeutschZTools_FrameFind("BankingAmount"));
        m_TraderZCategory = EditBoxWidget.Cast(DeutschZTools_FrameFind("TraderZCategory"));
        m_MapWidget = MapWidget.Cast(DeutschZTools_FrameFind("MapNative"));
        m_MapFrame = DeutschZTools_FrameFind("MapFrame");
        m_BtnMapClose = ButtonWidget.Cast(DeutschZTools_FrameFind("BtnMapClose"));
        m_DashboardOnlineText = TextWidget.Cast(DeutschZTools_FrameFind("DashboardOnlineText"));
        m_AdminPositionText = TextWidget.Cast(DeutschZTools_FrameFind("AdminPositionText"));
        m_PlayerListText = MultilineTextWidget.Cast(DeutschZTools_FrameFind("PlayerListText"));
        m_DebugText = MultilineTextWidget.Cast(DeutschZTools_FrameFind("DebugText"));
        m_PlayerListSummary = TextWidget.Cast(DeutschZTools_FrameFind("PlayerListSummary"));
        DeutschZTools_InitPlayerRowBindings();
        DeutschZTools_InitGarageRowBindings();
        DeutschZTools_InitBankingRowBindings();
        DeutschZTools_InitGroupsRowBindings();
        DeutschZTools_InitTraderZRowBindings();
        DeutschZTools_InitSpawnPresetBindings();
        DeutschZTools_ApplyGermanButtonLabels();
        DeutschZTools_ApplySelectedSteam64ToFrame();
        m_KothPanelGeneral = DeutschZTools_FrameFind("KothPanelGeneral");
        m_KothPanelSchedule = DeutschZTools_FrameFind("KothPanelSchedule");
        m_KothPanelZones = DeutschZTools_FrameFind("KothPanelZones");
        m_KothPanelCapture = DeutschZTools_FrameFind("KothPanelCapture");
        m_KothPanelRewards = DeutschZTools_FrameFind("KothPanelRewards");
        m_KothPanelAI = DeutschZTools_FrameFind("KothPanelAI");
        m_KothPanelMarkers = DeutschZTools_FrameFind("KothPanelMarkers");
        m_KothPanelEffects = DeutschZTools_FrameFind("KothPanelEffects");
        m_KothPanelSafety = DeutschZTools_FrameFind("KothPanelSafety");

        if (m_DashboardOnlineText)
            m_DashboardOnlineText.SetText("Online players: " + m_LastPlayerCount);
        if (m_PlayerListText && m_LastPlayerCount == 0)
            m_PlayerListText.SetText("Online players: 0");
        if (m_MapFrame)
            HideNativeMap();
        if (m_DebugText)
            DeutschZTools_UpdateDebugText();
        if (m_KothPanelGeneral)
            DeutschZTools_ShowKothTab("General");
        DeutschZTools_UpdateAdminPosition();
    }

    override void OnShow()
    {
        super.OnShow();

        if (GetGame() && GetGame().GetInput())
            GetGame().GetInput().ChangeGameFocus(1);

        if (GetGame() && GetGame().GetUIManager())
            GetGame().GetUIManager().ShowUICursor(true);

        if (GetGame() && GetGame().GetMission())
            GetGame().GetMission().PlayerControlDisable(INPUT_EXCLUDE_ALL);

        if (layoutRoot)
            layoutRoot.Show(true);

        SetStatus("Menue geoeffnet");
        if (!m_RequestPlayersOnShow)
        {
            m_RequestPlayersOnShow = true;
            DeutschZTools_Client.SendAction(DeutschZTools_Action.REQUEST_PLAYER_LIST);
        }
    }

    override void OnHide()
    {
        super.OnHide();

        if (GetGame() && GetGame().GetInput())
            GetGame().GetInput().ResetGameFocus();

        if (GetGame() && GetGame().GetUIManager())
            GetGame().GetUIManager().ShowUICursor(false);

        if (GetGame() && GetGame().GetMission())
            GetGame().GetMission().PlayerControlEnable(true);
    }

    void SetStatus(string text)
    {
        m_LastStatus = text;

        if (m_StatusText)
            m_StatusText.SetText("Letzte Antwort: " + text);

        if (m_HeaderStatusText)
            m_HeaderStatusText.SetText("Status: " + text);

        DeutschZTools_UpdateDebugText();
    }

    void SetPlayerList(string text)
    {
        if (m_PlayerListText)
            m_PlayerListText.SetText(text);

        m_LastPlayerCount = DeutschZTools_CountPlayerLines(text);
        if (m_DashboardOnlineText)
            m_DashboardOnlineText.SetText("Spieler online: " + m_LastPlayerCount);

        DeutschZTools_PopulatePlayerRows(text);
        DeutschZTools_UpdateDebugText();
    }

    void DeutschZTools_SetButtonText(ButtonWidget button, string text)
    {
        if (button)
            button.SetText(text);
    }

    void DeutschZTools_ApplyGermanButtonLabels()
    {
        DeutschZTools_SetButtonText(m_BtnClose, "Schliessen");
        DeutschZTools_SetButtonText(m_BtnTabDashboard, "   Uebersicht");
        DeutschZTools_SetButtonText(m_BtnTabPlayers, "   Spieler");
        DeutschZTools_SetButtonText(m_BtnTabMapTeleport, "   Karte / Teleport");
        DeutschZTools_SetButtonText(m_BtnTabSpawn, "   Spawner");
        DeutschZTools_SetButtonText(m_BtnTabVehicles, "   Fahrzeuge");
        DeutschZTools_SetButtonText(m_BtnTabWeather, "   Wetter / Zeit");
        DeutschZTools_SetButtonText(m_BtnTabEvents, "   Ereignisse / KOTH");
        DeutschZTools_SetButtonText(m_BtnTabKothSettings, "   KOTH Optionen");
        DeutschZTools_SetButtonText(m_BtnTabServer, "   Server");
        DeutschZTools_SetButtonText(m_BtnTabDebug, "   Debug / Logs");
        DeutschZTools_SetButtonText(m_BtnTabGarage, "   Garage");
        DeutschZTools_SetButtonText(m_BtnTabBanking, "   Bank");
        DeutschZTools_SetButtonText(m_BtnTabGroups, "   Gruppen");
        DeutschZTools_SetButtonText(m_BtnTabTraderZ, "   TraderZ");
        DeutschZTools_SetButtonText(m_BtnTabPlayerFun, "   Spieler Spass");

        DeutschZTools_SetButtonText(m_BtnPing, "Verbindung testen");
        DeutschZTools_SetButtonText(m_BtnDashPlayerList, "Spieler laden");
        DeutschZTools_SetButtonText(m_BtnDashReloadConfigs, "Configs neu laden");
        DeutschZTools_SetButtonText(m_BtnDashKothStatus, "KOTH Status");
        DeutschZTools_SetButtonText(m_BtnDashKothReload, "KOTH neu laden");
        DeutschZTools_SetButtonText(m_BtnDashWeatherClear, "Wetter klar");
        DeutschZTools_SetButtonText(m_BtnPlaceholderInventory, "Inventar ansehen");
        DeutschZTools_SetButtonText(m_BtnPlaceholderSpectate, "Zuschauen");
        DeutschZTools_SetButtonText(m_BtnPlaceholderKill, "Aktion aus");
        DeutschZTools_SetButtonText(m_BtnPlaceholderMapClick, "Klick-Teleport");
        DeutschZTools_SetButtonText(m_BtnPlayerList, "Spieler laden");
        DeutschZTools_SetButtonText(m_BtnReloadConfigs, "Configs neu laden");
        DeutschZTools_SetButtonText(m_BtnHealSelf, "Mich heilen");
        DeutschZTools_SetButtonText(m_BtnHealTarget, "Ziel heilen");
        DeutschZTools_SetButtonText(m_BtnTpToPlayer, "Zum Spieler");
        DeutschZTools_SetButtonText(m_BtnBringPlayer, "Herholen");
        DeutschZTools_SetButtonText(m_BtnRepairVehicle, "Fahrzeug reparieren");
        DeutschZTools_SetButtonText(m_BtnMapLight, "Karte oeffnen");
        DeutschZTools_SetButtonText(m_BtnMapDark, "Karte neu oeffnen");
        DeutschZTools_SetButtonText(m_BtnMapClose, "Karte schliessen");
        DeutschZTools_SetButtonText(m_BtnTeleportCoords, "Zu X/Z teleportieren");
        DeutschZTools_SetButtonText(m_BtnSetAdminPosFields, "Admin Position nutzen");
        DeutschZTools_SetButtonText(m_BtnSpawn, "Vor mir spawnen");
        DeutschZTools_SetButtonText(m_BtnSpawnGround, "Auf Boden spawnen");
        DeutschZTools_SetButtonText(m_BtnSpawnInventory, "Ins Inventar");
        DeutschZTools_SetButtonText(m_BtnSpawnTarget, "Beim Ziel");
        DeutschZTools_SetButtonText(m_BtnSpawnCatWeapons, "Waffen");
        DeutschZTools_SetButtonText(m_BtnSpawnCatVehicles, "Fahrzeuge");
        DeutschZTools_SetButtonText(m_BtnSpawnCatClothing, "Kleidung");
        DeutschZTools_SetButtonText(m_BtnSpawnCatTools, "Werkzeug");
        DeutschZTools_SetButtonText(m_BtnSpawnCatBase, "Basebau");
        DeutschZTools_SetButtonText(m_BtnSpawnCatMedical, "Medizin");
        DeutschZTools_SetButtonText(m_BtnSpawnCatFood, "Nahrung");
        DeutschZTools_SetButtonText(m_BtnSpawnCatMisc, "Sonstiges");
        DeutschZTools_SetButtonText(m_BtnSpawnPresetPrev, "Zurueck");
        DeutschZTools_SetButtonText(m_BtnSpawnPresetNext, "Weiter");

        DeutschZTools_SetButtonText(m_BtnWeatherClear, "Klar");
        DeutschZTools_SetButtonText(m_BtnWeatherRain, "Regen");
        DeutschZTools_SetButtonText(m_BtnWeatherStorm, "Sturm");
        DeutschZTools_SetButtonText(m_BtnWeatherFog, "Nebel");
        DeutschZTools_SetButtonText(m_BtnWeatherApply, "Wetter setzen");
        DeutschZTools_SetButtonText(m_BtnTimeApply, "Zeit setzen");
        DeutschZTools_SetButtonText(m_BtnWeatherReset, "Wetter reset");
        DeutschZTools_SetButtonText(m_BtnKothStatus, "KOTH Status");
        DeutschZTools_SetButtonText(m_BtnKothForceStart, "KOTH starten");
        DeutschZTools_SetButtonText(m_BtnKothForceStop, "KOTH stoppen");
        DeutschZTools_SetButtonText(m_BtnKothReload, "KOTH neu laden");
        DeutschZTools_SetButtonText(m_BtnRestart, "Restart Countdown");
        DeutschZTools_SetButtonText(m_BtnServerReloadAdmins, "Admins neu laden");
        DeutschZTools_SetButtonText(m_BtnServerMessage, "Server Nachricht");
        DeutschZTools_SetButtonText(m_BtnDebugPrint, "Log schreiben");
        DeutschZTools_SetButtonText(m_BtnDebugReloadUI, "UI neu laden");

        DeutschZTools_SetButtonText(m_BtnVehicleRefuel, "Tanken");
        DeutschZTools_SetButtonText(m_BtnVehicleFlip, "Aufrichten");
        DeutschZTools_SetButtonText(m_BtnVehicleTeleport, "Zu mir holen");
        DeutschZTools_SetButtonText(m_BtnVehicleLock, "Schloss umschalten");
        DeutschZTools_SetButtonText(m_BtnVehicleDelete, "Fahrzeug loeschen");
        DeutschZTools_SetButtonText(m_BtnGarageStatus, "Garage Status");
        DeutschZTools_SetButtonText(m_BtnGarageReload, "Garage neu laden");
        DeutschZTools_SetButtonText(m_BtnGarageVehicleList, "Fahrzeuge laden");
        DeutschZTools_SetButtonText(m_BtnGarageImpound, "Naechstes einparken");
        DeutschZTools_SetButtonText(m_BtnBankingStatus, "Bank Status");
        DeutschZTools_SetButtonText(m_BtnBankingReload, "Bank neu laden");
        DeutschZTools_SetButtonText(m_BtnBankingLookup, "Konto suchen");
        DeutschZTools_SetButtonText(m_BtnBankingAddMoney, "Geld geben");
        DeutschZTools_SetButtonText(m_BtnBankingRemoveMoney, "Geld nehmen");
        DeutschZTools_SetButtonText(m_BtnBankingAudit, "Audit laden");
        DeutschZTools_SetButtonText(m_BtnGroupsStatus, "Gruppen Status");
        DeutschZTools_SetButtonText(m_BtnGroupsReload, "Gruppen neu laden");
        DeutschZTools_SetButtonText(m_BtnGroupsList, "Gruppen laden");
        DeutschZTools_SetButtonText(m_BtnGroupsLookup, "Gruppe suchen");

        DeutschZTools_SetButtonText(m_BtnPlayerFunFreeze, "Einfrieren");
        DeutschZTools_SetButtonText(m_BtnPlayerFunUnfreeze, "Freigeben");
        DeutschZTools_SetButtonText(m_BtnPlayerFunVomit, "Uebelkeit");
        DeutschZTools_SetButtonText(m_BtnPlayerFunTiny, "Klein");
        DeutschZTools_SetButtonText(m_BtnPlayerFunGiant, "Gross");
        DeutschZTools_SetButtonText(m_BtnPlayerFunResetSize, "Groesse reset");
        DeutschZTools_SetButtonText(m_BtnPlayerFunSpin, "Drehen");
        DeutschZTools_SetButtonText(m_BtnPlayerFunPig, "Schwein");
        DeutschZTools_SetButtonText(m_BtnPlayerFunGoat, "Ziege");

        DeutschZTools_SetButtonText(m_BtnTraderZStatus, "TraderZ Status");
        DeutschZTools_SetButtonText(m_BtnTraderZReloadAll, "Alles neu laden");
        DeutschZTools_SetButtonText(m_BtnTraderZReloadSettings, "Settings neu laden");
        DeutschZTools_SetButtonText(m_BtnTraderZReloadTraders, "Haendler neu laden");
        DeutschZTools_SetButtonText(m_BtnTraderZReloadMarket, "Markt neu laden");
        DeutschZTools_SetButtonText(m_BtnTraderZReloadCurrency, "Geld neu laden");
        DeutschZTools_SetButtonText(m_BtnTraderZReloadSafezones, "Safezones neu laden");
        DeutschZTools_SetButtonText(m_BtnTraderZListTraders, "Haendler anzeigen");
        DeutschZTools_SetButtonText(m_BtnTraderZListCategory, "Kategorie anzeigen");
        DeutschZTools_SetButtonText(m_BtnTraderZListCategories, "Kategorien anzeigen");

        DeutschZTools_SetButtonText(m_BtnKothTabGeneral, "Allgemein");
        DeutschZTools_SetButtonText(m_BtnKothTabSchedule, "Zeitplan");
        DeutschZTools_SetButtonText(m_BtnKothTabZones, "Zonen");
        DeutschZTools_SetButtonText(m_BtnKothTabCapture, "Eroberung");
        DeutschZTools_SetButtonText(m_BtnKothTabRewards, "Belohnung");
        DeutschZTools_SetButtonText(m_BtnKothTabAI, "Zombies");
        DeutschZTools_SetButtonText(m_BtnKothTabMarkers, "Marker");
        DeutschZTools_SetButtonText(m_BtnKothTabEffects, "Effekte");
        DeutschZTools_SetButtonText(m_BtnKothTabSafety, "Sicherheit");
        DeutschZTools_SetButtonText(m_BtnKothSaveSettings, "Settings speichern");
        DeutschZTools_SetButtonText(m_BtnKothReloadSettings, "Settings neu laden");
        DeutschZTools_SetButtonText(m_BtnKothReloadZones, "Zonen neu laden");
        DeutschZTools_SetButtonText(m_BtnKothReloadLoot, "Loot neu laden");
        DeutschZTools_SetButtonText(m_BtnKothReloadAll, "Alles neu laden");
        DeutschZTools_SetButtonText(m_BtnKothScheduleSave, "Zeitplan speichern");
        DeutschZTools_SetButtonText(m_BtnKothCaptureSave, "Eroberung speichern");
        DeutschZTools_SetButtonText(m_BtnKothFullReload, "Voll neu laden");
    }

    void SetGarageList(string title, string rowsText)
    {
        DeutschZTools_PopulateGarageRows(rowsText);
        if (m_DebugText)
            DeutschZTools_UpdateDebugText();
    }

    void SetBankingList(string title, string rowsText)
    {
        DeutschZTools_PopulateBankingRows(rowsText);
        if (m_DebugText)
            DeutschZTools_UpdateDebugText();
    }

    void SetGroupsList(string title, string rowsText)
    {
        DeutschZTools_PopulateGroupsRows(rowsText);
        if (m_DebugText)
            DeutschZTools_UpdateDebugText();
    }

    void SetTraderZList(string title, string rowsText)
    {
        DeutschZTools_PopulateTraderZRows(rowsText);
        if (m_DebugText)
            DeutschZTools_UpdateDebugText();
    }

    int DeutschZTools_CountPlayerLines(string text)
    {
        ref TStringArray lines = new TStringArray;
        text.Split("\n", lines);

        int count = 0;
        foreach (string line : lines)
        {
            if (line.Contains(" | "))
                count++;
        }

        return count;
    }

    void SetMapLight()
    {
        DeutschZTools_OpenNativeMap("native map opened");
    }

    void SetMapDark()
    {
        DeutschZTools_OpenNativeMap("native map reopened");
    }

    void DeutschZTools_OpenNativeMap(string statusText)
    {
        if (m_SelectedTabKey != "MapTeleport")
            ShowPanel("MapTeleport");

        if (m_MapFrame)
        {
            m_MapFrame.Show(true);
            m_MapFrame.Enable(true);
        }

        if (m_MapWidget)
        {
            m_MapWidget.Show(true);
            m_MapWidget.Enable(true);

            Object player = GetGame().GetPlayer();
            if (player)
            {
                vector playerPos = player.GetPosition();
                m_MapWidget.SetMapPos(playerPos);
                m_MapWidget.SetScale(0.25);
            }
        }

        SetStatus(statusText);
    }

    override bool OnClick(Widget w, int x, int y, int button)
    {
        if (DeutschZTools_HandleTabClick(w))
            return true;

        if (DeutschZTools_HandleKothTabClick(w))
            return true;

        if (DeutschZTools_HandlePlayerRowClick(w))
            return true;

        if (w == m_BtnPing)
        {
            DeutschZTools_Client.SendAction(DeutschZTools_Action.PING);
            SetStatus("Pruefung gesendet");
            return true;
        }

        if (w == m_BtnPlayerList || w == m_BtnDashPlayerList)
        {
            DeutschZTools_Client.SendAction(DeutschZTools_Action.REQUEST_PLAYER_LIST);
            SetStatus("Spielerliste angefordert");
            return true;
        }

        if (w == m_BtnReloadConfigs || w == m_BtnDashReloadConfigs)
        {
            DeutschZTools_Client.SendAction(DeutschZTools_Action.RELOAD_CONFIGS);
            SetStatus("Config Reload angefordert");
            return true;
        }

        if (w == m_BtnHealSelf)
        {
            DeutschZTools_Client.SendAction(DeutschZTools_Action.HEAL_SELF);
            SetStatus("Selbstheilung gesendet");
            return true;
        }

        if (w == m_BtnHealTarget)
        {
            DeutschZTools_Client.SendTargetAction(DeutschZTools_Action.HEAL_PLAYER, GetTargetSteam64());
            SetStatus("Zielheilung gesendet");
            return true;
        }

        if (w == m_BtnTpToPlayer)
        {
            DeutschZTools_Client.SendTargetAction(DeutschZTools_Action.TELEPORT_TO_PLAYER, GetTargetSteam64());
            SetStatus("Teleport zum Ziel gesendet");
            return true;
        }

        if (w == m_BtnBringPlayer)
        {
            DeutschZTools_Client.SendTargetAction(DeutschZTools_Action.TELEPORT_PLAYER_TO_ME, GetTargetSteam64());
            SetStatus("Ziel herholen gesendet");
            return true;
        }

        if (w == m_BtnRepairVehicle)
        {
            DeutschZTools_Client.SendAction(DeutschZTools_Action.REPAIR_NEAREST_VEHICLE);
            SetStatus("Reparatur gesendet");
            return true;
        }

        if (w == m_BtnWeatherClear || w == m_BtnDashWeatherClear)
        {
            DeutschZTools_Client.SendAction(DeutschZTools_Action.SET_WEATHER_CLEAR);
            SetStatus("Klares Wetter gesendet");
            return true;
        }

        if (w == m_BtnWeatherRain)
        {
            DeutschZTools_Client.SendAction(DeutschZTools_Action.SET_WEATHER_RAIN);
            SetStatus("Regen gesendet");
            return true;
        }

        if (w == m_BtnWeatherStorm)
        {
            DeutschZTools_Client.SendAction(DeutschZTools_Action.SET_WEATHER_STORM);
            SetStatus("Sturm gesendet");
            return true;
        }

        if (w == m_BtnWeatherFog)
        {
            DeutschZTools_Client.SendAction(DeutschZTools_Action.SET_WEATHER_FOG);
            SetStatus("Nebel gesendet");
            return true;
        }

        if (w == m_BtnKothStatus || w == m_BtnDashKothStatus)
        {
            DeutschZTools_Client.SendAction(DeutschZTools_Action.KOTH_STATUS);
            SetStatus("KOTH Status gesendet");
            return true;
        }

        if (w == m_BtnKothForceStart)
        {
            DeutschZTools_Client.SendAction(DeutschZTools_Action.KOTH_FORCE_START);
            SetStatus("KOTH Start gesendet");
            return true;
        }

        if (w == m_BtnKothForceStop)
        {
            DeutschZTools_Client.SendAction(DeutschZTools_Action.KOTH_FORCE_STOP);
            SetStatus("KOTH Stop gesendet");
            return true;
        }

        if (w == m_BtnKothReload || w == m_BtnDashKothReload)
        {
            DeutschZTools_Client.SendAction(DeutschZTools_Action.KOTH_RELOAD_CONFIGS);
            SetStatus("KOTH Reload gesendet");
            return true;
        }

        if (w == m_BtnKothSaveSettings)
        {
            DeutschZTools_Client.SendAction(DeutschZTools_Action.KOTH_SAVE_SETTINGS);
            SetStatus("KOTH Settings speichern vorbereitet");
            return true;
        }

        if (w == m_BtnKothReloadSettings)
        {
            DeutschZTools_Client.SendAction(DeutschZTools_Action.KOTH_RELOAD_SETTINGS);
            SetStatus("KOTH Settings Reload gesendet");
            return true;
        }

        if (w == m_BtnKothReloadZones)
        {
            DeutschZTools_Client.SendAction(DeutschZTools_Action.KOTH_RELOAD_ZONES);
            SetStatus("KOTH Zonen Reload gesendet");
            return true;
        }

        if (w == m_BtnKothReloadLoot)
        {
            DeutschZTools_Client.SendAction(DeutschZTools_Action.KOTH_RELOAD_LOOT);
            SetStatus("KOTH Loot Reload gesendet");
            return true;
        }

        if (w == m_BtnKothReloadAll || w == m_BtnKothFullReload)
        {
            DeutschZTools_Client.SendAction(DeutschZTools_Action.KOTH_RELOAD_ALL);
            SetStatus("KOTH Vollreload gesendet");
            return true;
        }

        if (w == m_BtnKothScheduleSave)
        {
            SetStatus("KOTH Zeitplan speichern vorbereitet");
            return true;
        }

        if (w == m_BtnKothCaptureSave)
        {
            SetStatus("KOTH Eroberung speichern vorbereitet");
            return true;
        }

        if (w == m_BtnRestart)
        {
            DeutschZTools_Client.SendAction(DeutschZTools_Action.SERVER_RESTART_COUNTDOWN);
            SetStatus("Restart Bridge gesendet");
            return true;
        }

        if (w == m_BtnMapLight)
        {
            SetMapLight();
            return true;
        }

        if (w == m_BtnMapDark)
        {
            SetMapDark();
            return true;
        }

        if (w == m_BtnMapClose)
        {
            HideNativeMap();
            SetStatus("Karte geschlossen");
            return true;
        }

        if (w == m_BtnTeleportCoords)
        {
            TeleportFromFields();
            return true;
        }

        if (w == m_BtnSetAdminPosFields)
        {
            DeutschZTools_SetAdminPositionFields();
            return true;
        }

        if (DeutschZTools_HandleSpawnPresetClick(w))
            return true;

        if (w == m_BtnSpawn || w == m_BtnSpawnGround)
        {
            SpawnFromFields(0);
            return true;
        }

        if (w == m_BtnVehicleFlip)
        {
            DeutschZTools_Client.SendAction(DeutschZTools_Action.FLIP_NEAREST_VEHICLE);
            SetStatus("Fahrzeug aufrichten gesendet");
            return true;
        }

        if (w == m_BtnVehicleTeleport)
        {
            DeutschZTools_Client.SendAction(DeutschZTools_Action.TELEPORT_NEAREST_VEHICLE_TO_ME);
            SetStatus("Fahrzeug teleportieren gesendet");
            return true;
        }

        if (w == m_BtnServerReloadAdmins)
        {
            DeutschZTools_Client.SendAction(DeutschZTools_Action.RELOAD_CONFIGS);
            SetStatus("Admin/Config Reload angefordert");
            return true;
        }

        if (w == m_BtnGarageStatus)
        {
            DeutschZTools_Client.SendAction(DeutschZTools_Action.GARAGE_STATUS);
            SetStatus("Garage Status angefordert");
            return true;
        }

        if (w == m_BtnGarageReload)
        {
            DeutschZTools_Client.SendAction(DeutschZTools_Action.GARAGE_RELOAD);
            SetStatus("Garage Bridge Reload angefordert");
            return true;
        }

        if (w == m_BtnGarageVehicleList)
        {
            DeutschZTools_Client.SendTargetAction(DeutschZTools_Action.GARAGE_LIST, GetGarageSteam64());
            SetStatus("Garage Fahrzeugliste angefordert");
            return true;
        }

        if (w == m_BtnGarageImpound)
        {
            DeutschZTools_Client.SendTargetAction(DeutschZTools_Action.GARAGE_IMPOUND_NEAREST, GetGarageSteam64());
            SetStatus("Naechstes Fahrzeug einparken gesendet");
            return true;
        }

        if (w == m_BtnBankingStatus)
        {
            DeutschZTools_Client.SendAction(DeutschZTools_Action.BANKING_STATUS);
            SetStatus("Bank Status angefordert");
            return true;
        }

        if (w == m_BtnBankingReload)
        {
            DeutschZTools_Client.SendAction(DeutschZTools_Action.BANKING_RELOAD);
            SetStatus("Bank Bridge Reload angefordert");
            return true;
        }

        if (w == m_BtnBankingLookup)
        {
            DeutschZTools_Client.SendTargetAction(DeutschZTools_Action.BANKING_LOOKUP, GetBankingSteam64());
            SetStatus("Konto Suche angefordert");
            return true;
        }

        if (w == m_BtnBankingAddMoney)
        {
            DeutschZTools_Client.SendTargetAmountAction(DeutschZTools_Action.BANKING_ADD_MONEY, GetBankingSteam64(), GetBankingAmount());
            SetStatus("Geld geben gesendet");
            return true;
        }

        if (w == m_BtnBankingRemoveMoney)
        {
            DeutschZTools_Client.SendTargetAmountAction(DeutschZTools_Action.BANKING_REMOVE_MONEY, GetBankingSteam64(), GetBankingAmount());
            SetStatus("Geld nehmen gesendet");
            return true;
        }

        if (w == m_BtnBankingAudit)
        {
            DeutschZTools_Client.SendTargetAction(DeutschZTools_Action.BANKING_AUDIT, GetBankingSteam64());
            SetStatus("Bank Audit angefordert");
            return true;
        }

        if (w == m_BtnGroupsStatus)
        {
            DeutschZTools_Client.SendAction(DeutschZTools_Action.GROUPS_STATUS);
            SetStatus("Gruppen Status angefordert");
            return true;
        }

        if (w == m_BtnGroupsReload)
        {
            DeutschZTools_Client.SendAction(DeutschZTools_Action.GROUPS_RELOAD);
            SetStatus("Gruppen Reload angefordert");
            return true;
        }

        if (w == m_BtnGroupsList)
        {
            DeutschZTools_Client.SendAction(DeutschZTools_Action.GROUPS_LIST);
            SetStatus("Gruppenliste angefordert");
            return true;
        }

        if (w == m_BtnGroupsLookup)
        {
            DeutschZTools_Client.SendTargetAction(DeutschZTools_Action.GROUPS_LOOKUP, GetTargetSteam64());
            SetStatus("Gruppen Suche angefordert");
            return true;
        }

        if (w == m_BtnTraderZStatus)
        {
            DeutschZTools_Client.SendAction(DeutschZTools_Action.TRADERZ_STATUS);
            SetStatus("TraderZ Status angefordert");
            return true;
        }

        if (w == m_BtnTraderZReloadAll)
        {
            DeutschZTools_Client.SendAction(DeutschZTools_Action.TRADERZ_RELOAD_ALL);
            SetStatus("TraderZ alles neu laden angefordert");
            return true;
        }

        if (w == m_BtnTraderZReloadSettings)
        {
            DeutschZTools_Client.SendAction(DeutschZTools_Action.TRADERZ_RELOAD_SETTINGS);
            SetStatus("TraderZ Settings Reload angefordert");
            return true;
        }

        if (w == m_BtnTraderZReloadTraders)
        {
            DeutschZTools_Client.SendAction(DeutschZTools_Action.TRADERZ_RELOAD_TRADERS);
            SetStatus("TraderZ Haendler Reload angefordert");
            return true;
        }

        if (w == m_BtnTraderZReloadMarket)
        {
            DeutschZTools_Client.SendAction(DeutschZTools_Action.TRADERZ_RELOAD_MARKET);
            SetStatus("TraderZ Markt Reload angefordert");
            return true;
        }

        if (w == m_BtnTraderZReloadCurrency)
        {
            DeutschZTools_Client.SendAction(DeutschZTools_Action.TRADERZ_RELOAD_CURRENCY);
            SetStatus("TraderZ Geld Reload angefordert");
            return true;
        }

        if (w == m_BtnTraderZReloadSafezones)
        {
            DeutschZTools_Client.SendAction(DeutschZTools_Action.TRADERZ_RELOAD_SAFEZONES);
            SetStatus("TraderZ Safezones Reload angefordert");
            return true;
        }

        if (w == m_BtnTraderZListTraders)
        {
            DeutschZTools_Client.SendAction(DeutschZTools_Action.TRADERZ_LIST_TRADERS);
            SetStatus("TraderZ Haendlerliste angefordert");
            return true;
        }

        if (w == m_BtnTraderZListCategories)
        {
            DeutschZTools_Client.SendAction(DeutschZTools_Action.TRADERZ_LIST_CATEGORIES);
            SetStatus("TraderZ Kategorien angefordert");
            return true;
        }

        if (w == m_BtnTraderZListCategory)
        {
            DeutschZTools_Client.SendTargetAction(DeutschZTools_Action.TRADERZ_LIST_CATEGORY, GetTraderZCategory());
            SetStatus("TraderZ Marktkategorie angefordert");
            return true;
        }

        if (w == m_BtnPlayerFunFreeze)
        {
            DeutschZTools_Client.SendTargetAction(DeutschZTools_Action.PLAYERFUN_FREEZE, GetTargetSteam64());
            SetStatus("Spieler einfrieren gesendet");
            return true;
        }

        if (w == m_BtnPlayerFunUnfreeze)
        {
            DeutschZTools_Client.SendTargetAction(DeutschZTools_Action.PLAYERFUN_UNFREEZE, GetTargetSteam64());
            SetStatus("Spieler freigeben gesendet");
            return true;
        }

        if (w == m_BtnPlayerFunVomit)
        {
            DeutschZTools_Client.SendTargetAction(DeutschZTools_Action.PLAYERFUN_VOMIT, GetTargetSteam64());
            SetStatus("Uebelkeit gesendet");
            return true;
        }

        if (w == m_BtnPlayerFunTiny)
        {
            DeutschZTools_Client.SendTargetAction(DeutschZTools_Action.PLAYERFUN_TINY, GetTargetSteam64());
            SetStatus("Klein gesendet");
            return true;
        }

        if (w == m_BtnPlayerFunGiant)
        {
            DeutschZTools_Client.SendTargetAction(DeutschZTools_Action.PLAYERFUN_GIANT, GetTargetSteam64());
            SetStatus("Gross gesendet");
            return true;
        }

        if (w == m_BtnPlayerFunResetSize)
        {
            DeutschZTools_Client.SendTargetAction(DeutschZTools_Action.PLAYERFUN_RESET_SIZE, GetTargetSteam64());
            SetStatus("Groesse reset gesendet");
            return true;
        }

        if (w == m_BtnPlayerFunSpin)
        {
            DeutschZTools_Client.SendTargetAction(DeutschZTools_Action.PLAYERFUN_SPIN, GetTargetSteam64());
            SetStatus("Drehen gesendet");
            return true;
        }

        if (w == m_BtnPlayerFunPig)
        {
            DeutschZTools_Client.SendTargetAction(DeutschZTools_Action.PLAYERFUN_PIG_PRANK, GetTargetSteam64());
            SetStatus("Schwein gesendet");
            return true;
        }

        if (w == m_BtnPlayerFunGoat)
        {
            DeutschZTools_Client.SendTargetAction(DeutschZTools_Action.PLAYERFUN_GOAT_PRANK, GetTargetSteam64());
            SetStatus("Ziege gesendet");
            return true;
        }

        if (DeutschZTools_HandlePlaceholderClick(w))
            return true;

        if (w == m_BtnDebugPrint)
        {
            Print(DeutschZTools_Constants.LOG_PREFIX + "Debug tab=" + m_SelectedTabName + " target=" + GetTargetSteam64() + " status=" + m_LastStatus);
            SetStatus("Debug ins Scriptlog geschrieben");
            return true;
        }

        if (w == m_BtnDebugReloadUI)
        {
            SetStatus("UI Reload vorbereitet. Mit F10 neu oeffnen.");
            return true;
        }

        if (w == m_BtnClose)
        {
            DeutschZTools_CloseMenu();
            return true;
        }

        return false;
    }

    bool DeutschZTools_HandleTabClick(Widget w)
    {
        if (w == m_BtnTabDashboard) { ShowPanel("Dashboard"); return true; }
        if (w == m_BtnTabPlayers) { ShowPanel("Players"); return true; }
        if (w == m_BtnTabMapTeleport) { ShowPanel("MapTeleport"); return true; }
        if (w == m_BtnTabSpawn) { ShowPanel("Spawn"); return true; }
        if (w == m_BtnTabVehicles) { ShowPanel("Vehicles"); return true; }
        if (w == m_BtnTabWeather) { ShowPanel("Weather"); return true; }
        if (w == m_BtnTabEvents) { ShowPanel("EventsKOTH"); return true; }
        if (w == m_BtnTabKothSettings) { ShowPanel("KOTHSettings"); return true; }
        if (w == m_BtnTabServer) { ShowPanel("Server"); return true; }
        if (w == m_BtnTabDebug) { ShowPanel("DebugLogs"); return true; }
        if (w == m_BtnTabGarage) { ShowPanel("Garage"); return true; }
        if (w == m_BtnTabBanking) { ShowPanel("Banking"); return true; }
        if (w == m_BtnTabGroups) { ShowPanel("Groups"); return true; }
        if (w == m_BtnTabTraderZ) { ShowPanel("TraderZ"); return true; }
        if (w == m_BtnTabPlayerFun) { ShowPanel("PlayerFun"); return true; }
        return false;
    }

    bool DeutschZTools_HandleKothTabClick(Widget w)
    {
        if (w == m_BtnKothTabGeneral) { DeutschZTools_ShowKothTab("General"); return true; }
        if (w == m_BtnKothTabSchedule) { DeutschZTools_ShowKothTab("Schedule"); return true; }
        if (w == m_BtnKothTabZones) { DeutschZTools_ShowKothTab("Zones"); return true; }
        if (w == m_BtnKothTabCapture) { DeutschZTools_ShowKothTab("Capture"); return true; }
        if (w == m_BtnKothTabRewards) { DeutschZTools_ShowKothTab("Rewards"); return true; }
        if (w == m_BtnKothTabAI) { DeutschZTools_ShowKothTab("AI"); return true; }
        if (w == m_BtnKothTabMarkers) { DeutschZTools_ShowKothTab("Markers"); return true; }
        if (w == m_BtnKothTabEffects) { DeutschZTools_ShowKothTab("Effects"); return true; }
        if (w == m_BtnKothTabSafety) { DeutschZTools_ShowKothTab("Safety"); return true; }
        return false;
    }

    bool DeutschZTools_HandlePlaceholderClick(Widget w)
    {
        if (w == m_BtnPlaceholderInventory) { SetStatus("Inventar Ansicht noch nicht aktiv"); return true; }
        if (w == m_BtnPlaceholderSpectate) { SetStatus("Zuschauen vorbereitet. Kamera noch nicht gebunden."); return true; }
        if (w == m_BtnPlaceholderKill) { SetStatus("Aktion bleibt aus bis Rechte und Servercode stehen."); return true; }
        if (w == m_BtnPlaceholderMapClick) { SetStatus("Klick-Teleport vorbereitet"); return true; }
        if (w == m_BtnSpawnInventory) { SetStatus("Inventar Spawn vorbereitet"); return true; }
        if (w == m_BtnSpawnTarget) { SpawnFromFields(1); return true; }
        if (w == m_BtnVehicleRefuel) { SetStatus("Tanken vorbereitet"); return true; }
        if (w == m_BtnVehicleLock) { SetStatus("Schloss umschalten vorbereitet"); return true; }
        if (w == m_BtnVehicleDelete) { SetStatus("Fahrzeug loeschen bleibt aus bis Servercode steht."); return true; }
        if (w == m_BtnWeatherApply) { SetStatus("Eigenes Wetter vorbereitet"); return true; }
        if (w == m_BtnTimeApply) { SetStatus("Zeit setzen vorbereitet"); return true; }
        if (w == m_BtnWeatherReset) { SetStatus("Wetter reset vorbereitet"); return true; }
        if (w == m_BtnServerMessage) { SetStatus("Server Nachricht vorbereitet"); return true; }
        return false;
    }



    void DeutschZTools_InitSpawnPresetBindings()
    {
        if (!m_CurrentFrame || !m_BtnSpawnCatWeapons)
            return;

        m_SpawnPresetButtons = new array<ButtonWidget>;
        for (int i = 0; i < 20; i++)
            m_SpawnPresetButtons.Insert(ButtonWidget.Cast(DeutschZTools_FrameFind("BtnSpawnPreset" + i.ToString())));

        m_SpawnPresetCategory = "Waffen";
        m_SpawnPresetPage = 0;
        DeutschZTools_LoadSpawnPresetCategory(m_SpawnPresetCategory);
    }

    bool DeutschZTools_HandleSpawnPresetClick(Widget w)
    {
        if (!m_SpawnPresetButtons)
            return false;

        if (w == m_BtnSpawnCatWeapons) { DeutschZTools_SelectSpawnCategory("Waffen"); return true; }
        if (w == m_BtnSpawnCatVehicles) { DeutschZTools_SelectSpawnCategory("Fahrzeuge"); return true; }
        if (w == m_BtnSpawnCatClothing) { DeutschZTools_SelectSpawnCategory("Kleidung"); return true; }
        if (w == m_BtnSpawnCatTools) { DeutschZTools_SelectSpawnCategory("Werkzeug"); return true; }
        if (w == m_BtnSpawnCatBase) { DeutschZTools_SelectSpawnCategory("Basebau"); return true; }
        if (w == m_BtnSpawnCatMedical) { DeutschZTools_SelectSpawnCategory("Medizin"); return true; }
        if (w == m_BtnSpawnCatFood) { DeutschZTools_SelectSpawnCategory("Nahrung"); return true; }
        if (w == m_BtnSpawnCatMisc) { DeutschZTools_SelectSpawnCategory("Sonstiges"); return true; }

        if (w == m_BtnSpawnPresetPrev)
        {
            if (m_SpawnPresetPage > 0)
                m_SpawnPresetPage--;
            DeutschZTools_UpdateSpawnPresetRows();
            return true;
        }

        if (w == m_BtnSpawnPresetNext)
        {
            int pageSize = m_SpawnPresetButtons.Count();
            if (m_SpawnPresetClasses && pageSize > 0 && ((m_SpawnPresetPage + 1) * pageSize) < m_SpawnPresetClasses.Count())
                m_SpawnPresetPage++;
            DeutschZTools_UpdateSpawnPresetRows();
            return true;
        }

        for (int i = 0; i < m_SpawnPresetButtons.Count(); i++)
        {
            if (w != m_SpawnPresetButtons.Get(i))
                continue;

            int presetIndex = (m_SpawnPresetPage * m_SpawnPresetButtons.Count()) + i;
            if (!m_SpawnPresetClasses || presetIndex < 0 || presetIndex >= m_SpawnPresetClasses.Count())
                return true;

            string className = m_SpawnPresetClasses.Get(presetIndex);
            if (m_SpawnClassname)
                m_SpawnClassname.SetText(className);
            DeutschZTools_UpdateSpawnPreview(className);
            SetStatus("Spawner Auswahl: " + className);
            return true;
        }

        return false;
    }

    void DeutschZTools_SelectSpawnCategory(string category)
    {
        m_SpawnPresetCategory = category;
        m_SpawnPresetPage = 0;
        DeutschZTools_LoadSpawnPresetCategory(category);
        SetStatus("Spawner Kategorie: " + category);
    }

    void DeutschZTools_LoadSpawnPresetCategory(string category)
    {
        m_SpawnPresetClasses = new TStringArray;

        if (category == "Waffen")
        {
            DeutschZTools_AddSpawnPreset("M4A1");
            DeutschZTools_AddSpawnPreset("AKM");
            DeutschZTools_AddSpawnPreset("AK74");
            DeutschZTools_AddSpawnPreset("Mosin9130");
            DeutschZTools_AddSpawnPreset("SKS");
            DeutschZTools_AddSpawnPreset("Winchester70");
            DeutschZTools_AddSpawnPreset("Glock19");
            DeutschZTools_AddSpawnPreset("Mag_STANAG_30Rnd");
            DeutschZTools_AddSpawnPreset("Ammo_556x45");
            DeutschZTools_AddSpawnPreset("Ammo_762x39");
            DeutschZTools_AddSpawnPreset("Ammo_308Win");
        }
        else if (category == "Fahrzeuge")
        {
            DeutschZTools_AddSpawnPreset("OffroadHatchback");
            DeutschZTools_AddSpawnPreset("CivilianSedan");
            DeutschZTools_AddSpawnPreset("Hatchback_02");
            DeutschZTools_AddSpawnPreset("Truck_01_Covered");
            DeutschZTools_AddSpawnPreset("TruckBattery");
            DeutschZTools_AddSpawnPreset("CarBattery");
            DeutschZTools_AddSpawnPreset("SparkPlug");
            DeutschZTools_AddSpawnPreset("TireRepairKit");
        }
        else if (category == "Kleidung")
        {
            DeutschZTools_AddSpawnPreset("PlateCarrierVest_Black");
            DeutschZTools_AddSpawnPreset("BallisticHelmet_Black");
            DeutschZTools_AddSpawnPreset("M65Jacket_Black");
            DeutschZTools_AddSpawnPreset("CargoPants_Black");
            DeutschZTools_AddSpawnPreset("MilitaryBoots_Black");
            DeutschZTools_AddSpawnPreset("TacticalGloves_Black");
            DeutschZTools_AddSpawnPreset("AliceBag_Black");
            DeutschZTools_AddSpawnPreset("NVGoggles");
        }
        else if (category == "Werkzeug")
        {
            DeutschZTools_AddSpawnPreset("Hatchet");
            DeutschZTools_AddSpawnPreset("Hammer");
            DeutschZTools_AddSpawnPreset("Shovel");
            DeutschZTools_AddSpawnPreset("Wrench");
            DeutschZTools_AddSpawnPreset("Pliers");
            DeutschZTools_AddSpawnPreset("Screwdriver");
            DeutschZTools_AddSpawnPreset("Lockpick");
            DeutschZTools_AddSpawnPreset("CanOpener");
        }
        else if (category == "Basebau")
        {
            DeutschZTools_AddSpawnPreset("SeaChest");
            DeutschZTools_AddSpawnPreset("WoodenCrate");
            DeutschZTools_AddSpawnPreset("Barrel_Green");
            DeutschZTools_AddSpawnPreset("NailBox");
            DeutschZTools_AddSpawnPreset("WoodenPlank");
            DeutschZTools_AddSpawnPreset("MetalPlate");
            DeutschZTools_AddSpawnPreset("FenceKit");
            DeutschZTools_AddSpawnPreset("WatchtowerKit");
        }
        else if (category == "Medizin")
        {
            DeutschZTools_AddSpawnPreset("BandageDressing");
            DeutschZTools_AddSpawnPreset("Morphine");
            DeutschZTools_AddSpawnPreset("Epinephrine");
            DeutschZTools_AddSpawnPreset("TetracyclineAntibiotics");
            DeutschZTools_AddSpawnPreset("SalineBagIV");
            DeutschZTools_AddSpawnPreset("BloodBagIV");
            DeutschZTools_AddSpawnPreset("CharcoalTablets");
            DeutschZTools_AddSpawnPreset("PainkillerTablets");
        }
        else if (category == "Nahrung")
        {
            DeutschZTools_AddSpawnPreset("BakedBeansCan");
            DeutschZTools_AddSpawnPreset("PeachesCan");
            DeutschZTools_AddSpawnPreset("SpaghettiCan");
            DeutschZTools_AddSpawnPreset("TacticalBaconCan");
            DeutschZTools_AddSpawnPreset("SodaCan_Cola");
            DeutschZTools_AddSpawnPreset("SodaCan_Pipsi");
            DeutschZTools_AddSpawnPreset("WaterBottle");
            DeutschZTools_AddSpawnPreset("Canteen");
        }
        else
        {
            DeutschZTools_AddSpawnPreset("PersonalRadio");
            DeutschZTools_AddSpawnPreset("GPSReceiver");
            DeutschZTools_AddSpawnPreset("Compass");
            DeutschZTools_AddSpawnPreset("ChernarusMap");
            DeutschZTools_AddSpawnPreset("Binoculars");
            DeutschZTools_AddSpawnPreset("Flashlight");
            DeutschZTools_AddSpawnPreset("Battery9V");
            DeutschZTools_AddSpawnPreset("FireworksLauncher");
        }

        DeutschZTools_UpdateSpawnPresetRows();
    }

    void DeutschZTools_AddSpawnPreset(string className)
    {
        if (!m_SpawnPresetClasses || className == "")
            return;
        if (!DeutschZTools_ClassExistsForSpawn(className))
            return;
        m_SpawnPresetClasses.Insert(className);
    }

    bool DeutschZTools_ClassExistsForSpawn(string className)
    {
        if (GetGame().ConfigIsExisting("CfgVehicles " + className))
            return true;
        if (GetGame().ConfigIsExisting("CfgWeapons " + className))
            return true;
        if (GetGame().ConfigIsExisting("CfgMagazines " + className))
            return true;
        return false;
    }

    void DeutschZTools_UpdateSpawnPresetRows()
    {
        if (!m_SpawnPresetButtons)
            return;

        for (int i = 0; i < m_SpawnPresetButtons.Count(); i++)
        {
            string label = "";
            int presetIndex = (m_SpawnPresetPage * m_SpawnPresetButtons.Count()) + i;
            if (m_SpawnPresetClasses && presetIndex >= 0 && presetIndex < m_SpawnPresetClasses.Count())
                label = m_SpawnPresetClasses.Get(presetIndex);

            ButtonWidget presetButton = m_SpawnPresetButtons.Get(i);
            DeutschZTools_SetButtonText(presetButton, label);
            if (presetButton)
            {
                presetButton.Show(label != "");
                presetButton.Enable(label != "");
            }
        }

        if (m_SpawnPresetClasses && m_SpawnPresetClasses.Count() > 0)
        {
            int firstIndex = m_SpawnPresetPage * m_SpawnPresetButtons.Count();
            if (firstIndex >= m_SpawnPresetClasses.Count())
                firstIndex = 0;
            string firstClass = m_SpawnPresetClasses.Get(firstIndex);
            if (m_SpawnClassname)
                m_SpawnClassname.SetText(firstClass);
            DeutschZTools_UpdateSpawnPreview(firstClass);
        }
        else
        {
            DeutschZTools_ClearSpawnPreview();
        }
    }

    void DeutschZTools_UpdateSpawnPreview(string className)
    {
        DeutschZTools_ClearSpawnPreview();
        if (!m_SpawnItemPreview || className == "")
            return;
        if (!DeutschZTools_ClassExistsForSpawn(className))
            return;

        vector previewPos = "0 0 0";
        m_SpawnPreviewEntity = EntityAI.Cast(GetGame().CreateObject(className, previewPos, true, false, false));
        if (m_SpawnPreviewEntity)
            m_SpawnItemPreview.SetItem(m_SpawnPreviewEntity);
    }

    void DeutschZTools_ClearSpawnPreview()
    {
        if (m_SpawnItemPreview)
            m_SpawnItemPreview.SetItem(null);
        if (m_SpawnPreviewEntity)
        {
            GetGame().ObjectDelete(m_SpawnPreviewEntity);
            m_SpawnPreviewEntity = null;
        }
    }

    void DeutschZTools_InitPlayerRowBindings()
    {
        if (!m_CurrentFrame)
            return;

        m_PlayerRowButtons = new array<ButtonWidget>;
        m_PlayerRowNumberCells = new array<TextWidget>;
        m_PlayerRowNameCells = new array<TextWidget>;
        m_PlayerRowSteamCells = new array<TextWidget>;
        m_PlayerRowStateCells = new array<TextWidget>;
        m_PlayerRowPosCells = new array<TextWidget>;
        m_PlayerRowSteam64 = new TStringArray;

        for (int i = 0; i < 12; i++)
        {
            string suffix = i.ToString();
            m_PlayerRowButtons.Insert(ButtonWidget.Cast(DeutschZTools_FrameFind("BtnPlayerRow" + suffix)));
            m_PlayerRowNumberCells.Insert(TextWidget.Cast(DeutschZTools_FrameFind("PlayerRowNo" + suffix)));
            m_PlayerRowNameCells.Insert(TextWidget.Cast(DeutschZTools_FrameFind("PlayerRowName" + suffix)));
            m_PlayerRowSteamCells.Insert(TextWidget.Cast(DeutschZTools_FrameFind("PlayerRowSteam" + suffix)));
            m_PlayerRowStateCells.Insert(TextWidget.Cast(DeutschZTools_FrameFind("PlayerRowState" + suffix)));
            m_PlayerRowPosCells.Insert(TextWidget.Cast(DeutschZTools_FrameFind("PlayerRowPos" + suffix)));
            m_PlayerRowSteam64.Insert("");
        }

        DeutschZTools_ClearPlayerRows();
    }

    void DeutschZTools_ClearPlayerRows()
    {
        if (!m_PlayerRowSteam64)
            return;

        for (int i = 0; i < m_PlayerRowSteam64.Count(); i++)
        {
            m_PlayerRowSteam64.Set(i, "");
            DeutschZTools_SetTextCell(m_PlayerRowNumberCells, i, "");
            DeutschZTools_SetTextCell(m_PlayerRowNameCells, i, "");
            DeutschZTools_SetTextCell(m_PlayerRowSteamCells, i, "");
            DeutschZTools_SetTextCell(m_PlayerRowStateCells, i, "");
            DeutschZTools_SetTextCell(m_PlayerRowPosCells, i, "");
        }

        if (m_PlayerListSummary)
            m_PlayerListSummary.SetText("Spieler laden, um die Tabelle zu fuellen.");
    }

    void DeutschZTools_SetTextCell(array<TextWidget> cells, int index, string value)
    {
        if (!cells)
            return;
        if (index < 0 || index >= cells.Count())
            return;

        TextWidget cell = cells.Get(index);
        if (cell)
            cell.SetText(value);
    }

    bool DeutschZTools_ParsePlayerLine(string line, out string name, out string steam64, out string state, out string posText)
    {
        name = "";
        steam64 = "";
        state = "";
        posText = "";

        ref TStringArray parts = new TStringArray;
        line.Split("|", parts);
        if (parts.Count() < 4)
            return false;

        name = parts.Get(0);
        steam64 = parts.Get(1);
        state = parts.Get(2);
        posText = parts.Get(3);
        name.Trim();
        steam64.Trim();
        state.Trim();
        posText.Trim();
        return true;
    }

    void DeutschZTools_PopulatePlayerRows(string text)
    {
        if (!m_PlayerRowSteam64)
            return;

        DeutschZTools_ClearPlayerRows();

        ref TStringArray lines = new TStringArray;
        text.Split("\n", lines);

        int row = 0;
        foreach (string line : lines)
        {
            if (!line.Contains(" | "))
                continue;
            if (row >= m_PlayerRowSteam64.Count())
                break;

            string name;
            string steam64;
            string state;
            string posText;
            if (!DeutschZTools_ParsePlayerLine(line, name, steam64, state, posText))
                continue;

            m_PlayerRowSteam64.Set(row, steam64);
            DeutschZTools_SetTextCell(m_PlayerRowNumberCells, row, (row + 1).ToString());
            DeutschZTools_SetTextCell(m_PlayerRowNameCells, row, name);
            DeutschZTools_SetTextCell(m_PlayerRowSteamCells, row, steam64);
            DeutschZTools_SetTextCell(m_PlayerRowStateCells, row, state);
            DeutschZTools_SetTextCell(m_PlayerRowPosCells, row, posText);
            row++;
        }

        if (m_PlayerListSummary)
            m_PlayerListSummary.SetText("Zeige " + row + " von " + m_LastPlayerCount + " Spielern. Zeile anklicken waehlt Steam64.");
    }

    bool DeutschZTools_HandlePlayerRowClick(Widget w)
    {
        if (!m_PlayerRowButtons || !m_PlayerRowSteam64)
            return false;

        for (int i = 0; i < m_PlayerRowButtons.Count(); i++)
        {
            if (w != m_PlayerRowButtons.Get(i))
                continue;

            string steam64 = m_PlayerRowSteam64.Get(i);
            if (steam64 == "")
            {
                SetStatus("Leere Spielerzeile");
                return true;
            }

            m_SelectedSteam64 = steam64;

            if (m_TargetSteam64)
                m_TargetSteam64.SetText(steam64);
            if (m_GarageSteam64)
                m_GarageSteam64.SetText(steam64);
            if (m_BankingSteam64)
                m_BankingSteam64.SetText(steam64);

            SetStatus("Spieler gewaehlt: " + steam64);
            return true;
        }

        return false;
    }

    string GetGarageSteam64()
    {
        if (m_GarageSteam64)
        {
            string value = m_GarageSteam64.GetText();
            value.Trim();
            if (value != "")
            {
                m_SelectedSteam64 = value;
                return value;
            }
        }

        return m_SelectedSteam64;
    }

    string GetBankingSteam64()
    {
        if (m_BankingSteam64)
        {
            string value = m_BankingSteam64.GetText();
            value.Trim();
            if (value != "")
            {
                m_SelectedSteam64 = value;
                return value;
            }
        }

        return m_SelectedSteam64;
    }

    string GetBankingAmount()
    {
        if (!m_BankingAmount)
            return "0";
        return m_BankingAmount.GetText();
    }

    void DeutschZTools_ApplySelectedSteam64ToFrame()
    {
        if (m_SelectedSteam64 == "")
            return;

        if (m_TargetSteam64)
            m_TargetSteam64.SetText(m_SelectedSteam64);
        if (m_GarageSteam64)
            m_GarageSteam64.SetText(m_SelectedSteam64);
        if (m_BankingSteam64)
            m_BankingSteam64.SetText(m_SelectedSteam64);
    }

    void DeutschZTools_InitGarageRowBindings()
    {
        if (!m_CurrentFrame)
            return;

        m_GarageRowNumberCells = new array<TextWidget>;
        m_GarageRowClassCells = new array<TextWidget>;
        m_GarageRowStateCells = new array<TextWidget>;
        m_GarageRowOwnerCells = new array<TextWidget>;
        m_GarageRowPosCells = new array<TextWidget>;

        for (int i = 0; i < 10; i++)
        {
            string suffix = i.ToString();
            m_GarageRowNumberCells.Insert(TextWidget.Cast(DeutschZTools_FrameFind("GarageRowNo" + suffix)));
            m_GarageRowClassCells.Insert(TextWidget.Cast(DeutschZTools_FrameFind("GarageRowClass" + suffix)));
            m_GarageRowStateCells.Insert(TextWidget.Cast(DeutschZTools_FrameFind("GarageRowState" + suffix)));
            m_GarageRowOwnerCells.Insert(TextWidget.Cast(DeutschZTools_FrameFind("GarageRowOwner" + suffix)));
            m_GarageRowPosCells.Insert(TextWidget.Cast(DeutschZTools_FrameFind("GarageRowPos" + suffix)));
        }

        DeutschZTools_ClearGarageRows();
    }

    void DeutschZTools_ClearGarageRows()
    {
        if (!m_GarageRowNumberCells)
            return;

        for (int i = 0; i < m_GarageRowNumberCells.Count(); i++)
        {
            DeutschZTools_SetTextCell(m_GarageRowNumberCells, i, "");
            DeutschZTools_SetTextCell(m_GarageRowClassCells, i, "");
            DeutschZTools_SetTextCell(m_GarageRowStateCells, i, "");
            DeutschZTools_SetTextCell(m_GarageRowOwnerCells, i, "");
            DeutschZTools_SetTextCell(m_GarageRowPosCells, i, "");
        }
    }

    void DeutschZTools_PopulateGarageRows(string rowsText)
    {
        if (!m_GarageRowNumberCells)
            return;

        DeutschZTools_ClearGarageRows();

        ref TStringArray lines = new TStringArray;
        rowsText.Split("\n", lines);

        int row = 0;
        foreach (string line : lines)
        {
            if (line == "")
                continue;
            if (row >= m_GarageRowNumberCells.Count())
                break;

            ref TStringArray parts = new TStringArray;
            line.Split("|", parts);
            if (parts.Count() < 4)
                continue;

            DeutschZTools_SetTextCell(m_GarageRowNumberCells, row, (row + 1).ToString());
            DeutschZTools_SetTextCell(m_GarageRowClassCells, row, parts.Get(0));
            DeutschZTools_SetTextCell(m_GarageRowStateCells, row, parts.Get(1));
            DeutschZTools_SetTextCell(m_GarageRowOwnerCells, row, parts.Get(2));
            DeutschZTools_SetTextCell(m_GarageRowPosCells, row, parts.Get(3));
            row++;
        }

        if (row == 0)
            DeutschZTools_SetTextCell(m_GarageRowClassCells, 0, "No garage rows returned.");
    }

    void DeutschZTools_InitBankingRowBindings()
    {
        if (!m_CurrentFrame)
            return;

        m_BankingRowNumberCells = new array<TextWidget>;
        m_BankingRowPlayerCells = new array<TextWidget>;
        m_BankingRowBalanceCells = new array<TextWidget>;
        m_BankingRowTypeCells = new array<TextWidget>;
        m_BankingRowTimeCells = new array<TextWidget>;

        for (int i = 0; i < 9; i++)
        {
            string suffix = i.ToString();
            m_BankingRowNumberCells.Insert(TextWidget.Cast(DeutschZTools_FrameFind("BankingRowNo" + suffix)));
            m_BankingRowPlayerCells.Insert(TextWidget.Cast(DeutschZTools_FrameFind("BankingRowPlayer" + suffix)));
            m_BankingRowBalanceCells.Insert(TextWidget.Cast(DeutschZTools_FrameFind("BankingRowBalance" + suffix)));
            m_BankingRowTypeCells.Insert(TextWidget.Cast(DeutschZTools_FrameFind("BankingRowType" + suffix)));
            m_BankingRowTimeCells.Insert(TextWidget.Cast(DeutschZTools_FrameFind("BankingRowTime" + suffix)));
        }

        DeutschZTools_ClearBankingRows();
    }

    void DeutschZTools_ClearBankingRows()
    {
        if (!m_BankingRowNumberCells)
            return;

        for (int i = 0; i < m_BankingRowNumberCells.Count(); i++)
        {
            DeutschZTools_SetTextCell(m_BankingRowNumberCells, i, "");
            DeutschZTools_SetTextCell(m_BankingRowPlayerCells, i, "");
            DeutschZTools_SetTextCell(m_BankingRowBalanceCells, i, "");
            DeutschZTools_SetTextCell(m_BankingRowTypeCells, i, "");
            DeutschZTools_SetTextCell(m_BankingRowTimeCells, i, "");
        }
    }

    void DeutschZTools_PopulateBankingRows(string rowsText)
    {
        if (!m_BankingRowNumberCells)
            return;

        DeutschZTools_ClearBankingRows();

        ref TStringArray lines = new TStringArray;
        rowsText.Split("\n", lines);

        int row = 0;
        foreach (string line : lines)
        {
            if (line == "")
                continue;
            if (row >= m_BankingRowNumberCells.Count())
                break;

            ref TStringArray parts = new TStringArray;
            line.Split("|", parts);
            if (parts.Count() < 5)
                continue;

            DeutschZTools_SetTextCell(m_BankingRowNumberCells, row, (row + 1).ToString());
            DeutschZTools_SetTextCell(m_BankingRowPlayerCells, row, parts.Get(0));
            DeutschZTools_SetTextCell(m_BankingRowBalanceCells, row, parts.Get(1));
            DeutschZTools_SetTextCell(m_BankingRowTypeCells, row, parts.Get(2));
            DeutschZTools_SetTextCell(m_BankingRowTimeCells, row, parts.Get(4));
            row++;
        }

        if (row == 0)
            DeutschZTools_SetTextCell(m_BankingRowPlayerCells, 0, "No banking rows returned.");
    }


    void DeutschZTools_InitGroupsRowBindings()
    {
        if (!m_CurrentFrame)
            return;

        m_GroupsRowNumberCells = new array<TextWidget>;
        m_GroupsRowNameCells = new array<TextWidget>;
        m_GroupsRowTagCells = new array<TextWidget>;
        m_GroupsRowMembersCells = new array<TextWidget>;
        m_GroupsRowOwnerCells = new array<TextWidget>;

        for (int i = 0; i < 12; i++)
        {
            string suffix = i.ToString();
            m_GroupsRowNumberCells.Insert(TextWidget.Cast(DeutschZTools_FrameFind("GroupsRowNo" + suffix)));
            m_GroupsRowNameCells.Insert(TextWidget.Cast(DeutschZTools_FrameFind("GroupsRowName" + suffix)));
            m_GroupsRowTagCells.Insert(TextWidget.Cast(DeutschZTools_FrameFind("GroupsRowTag" + suffix)));
            m_GroupsRowMembersCells.Insert(TextWidget.Cast(DeutschZTools_FrameFind("GroupsRowMembers" + suffix)));
            m_GroupsRowOwnerCells.Insert(TextWidget.Cast(DeutschZTools_FrameFind("GroupsRowOwner" + suffix)));
        }

        DeutschZTools_ClearGroupsRows();
    }

    void DeutschZTools_ClearGroupsRows()
    {
        if (!m_GroupsRowNumberCells)
            return;

        for (int i = 0; i < m_GroupsRowNumberCells.Count(); i++)
        {
            DeutschZTools_SetTextCell(m_GroupsRowNumberCells, i, "");
            DeutschZTools_SetTextCell(m_GroupsRowNameCells, i, "");
            DeutschZTools_SetTextCell(m_GroupsRowTagCells, i, "");
            DeutschZTools_SetTextCell(m_GroupsRowMembersCells, i, "");
            DeutschZTools_SetTextCell(m_GroupsRowOwnerCells, i, "");
        }
    }

    void DeutschZTools_PopulateGroupsRows(string rowsText)
    {
        if (!m_GroupsRowNumberCells)
            return;

        DeutschZTools_ClearGroupsRows();

        ref TStringArray lines = new TStringArray;
        rowsText.Split("\n", lines);

        int row = 0;
        foreach (string line : lines)
        {
            if (line == "")
                continue;
            if (row >= m_GroupsRowNumberCells.Count())
                break;

            ref TStringArray parts = new TStringArray;
            line.Split("|", parts);
            if (parts.Count() < 5)
                continue;

            DeutschZTools_SetTextCell(m_GroupsRowNumberCells, row, (row + 1).ToString());
            DeutschZTools_SetTextCell(m_GroupsRowNameCells, row, parts.Get(0));
            DeutschZTools_SetTextCell(m_GroupsRowTagCells, row, parts.Get(1));
            DeutschZTools_SetTextCell(m_GroupsRowMembersCells, row, parts.Get(2) + " / " + parts.Get(3));
            DeutschZTools_SetTextCell(m_GroupsRowOwnerCells, row, parts.Get(4));
            row++;
        }

        if (row == 0)
            DeutschZTools_SetTextCell(m_GroupsRowNameCells, 0, "No groups rows returned.");
    }

    string GetTraderZCategory()
    {
        if (!m_TraderZCategory)
            return "Food";
        string value = m_TraderZCategory.GetText();
        value.Trim();
        if (value == "")
            value = "Food";
        return value;
    }

    void DeutschZTools_InitTraderZRowBindings()
    {
        if (!m_CurrentFrame)
            return;

        m_TraderZRowNumberCells = new array<TextWidget>;
        m_TraderZRowTypeCells = new array<TextWidget>;
        m_TraderZRowNameCells = new array<TextWidget>;
        m_TraderZRowValueCells = new array<TextWidget>;
        m_TraderZRowInfoCells = new array<TextWidget>;

        for (int i = 0; i < 12; i++)
        {
            string suffix = i.ToString();
            m_TraderZRowNumberCells.Insert(TextWidget.Cast(DeutschZTools_FrameFind("TraderZRowNo" + suffix)));
            m_TraderZRowTypeCells.Insert(TextWidget.Cast(DeutschZTools_FrameFind("TraderZRowType" + suffix)));
            m_TraderZRowNameCells.Insert(TextWidget.Cast(DeutschZTools_FrameFind("TraderZRowName" + suffix)));
            m_TraderZRowValueCells.Insert(TextWidget.Cast(DeutschZTools_FrameFind("TraderZRowValue" + suffix)));
            m_TraderZRowInfoCells.Insert(TextWidget.Cast(DeutschZTools_FrameFind("TraderZRowInfo" + suffix)));
        }

        DeutschZTools_ClearTraderZRows();
    }

    void DeutschZTools_ClearTraderZRows()
    {
        if (!m_TraderZRowNumberCells)
            return;

        for (int i = 0; i < m_TraderZRowNumberCells.Count(); i++)
        {
            DeutschZTools_SetTextCell(m_TraderZRowNumberCells, i, "");
            DeutschZTools_SetTextCell(m_TraderZRowTypeCells, i, "");
            DeutschZTools_SetTextCell(m_TraderZRowNameCells, i, "");
            DeutschZTools_SetTextCell(m_TraderZRowValueCells, i, "");
            DeutschZTools_SetTextCell(m_TraderZRowInfoCells, i, "");
        }
    }

    void DeutschZTools_PopulateTraderZRows(string rowsText)
    {
        if (!m_TraderZRowNumberCells)
            return;

        DeutschZTools_ClearTraderZRows();

        ref TStringArray lines = new TStringArray;
        rowsText.Split("\n", lines);

        int row = 0;
        foreach (string line : lines)
        {
            if (line == "")
                continue;
            if (row >= m_TraderZRowNumberCells.Count())
                break;

            ref TStringArray parts = new TStringArray;
            line.Split("|", parts);
            if (parts.Count() < 4)
                continue;

            string col0 = parts.Get(0);
            string col1 = parts.Get(1);
            string col2 = parts.Get(2);
            string col3 = parts.Get(3);
            col0.Trim();
            col1.Trim();
            col2.Trim();
            col3.Trim();

            DeutschZTools_SetTextCell(m_TraderZRowNumberCells, row, (row + 1).ToString());
            DeutschZTools_SetTextCell(m_TraderZRowTypeCells, row, col0);
            DeutschZTools_SetTextCell(m_TraderZRowNameCells, row, col1);
            DeutschZTools_SetTextCell(m_TraderZRowValueCells, row, col2);
            DeutschZTools_SetTextCell(m_TraderZRowInfoCells, row, col3);
            row++;
        }

        if (row == 0)
            DeutschZTools_SetTextCell(m_TraderZRowNameCells, 0, "No TraderZ rows returned.");
    }

    void HideNativeMap()
    {
        if (m_MapWidget)
        {
            m_MapWidget.Show(false);
            m_MapWidget.Enable(false);
        }

        if (m_MapFrame)
        {
            m_MapFrame.Show(false);
            m_MapFrame.Enable(false);
        }
    }

    string GetPanelLabel(string panelName)
    {
        if (panelName == "Dashboard")
            return "Uebersicht";
        if (panelName == "Players")
            return "Spieler";
        if (panelName == "MapTeleport")
            return "Karte / Teleport";
        if (panelName == "Spawn")
            return "Spawner";
        if (panelName == "Vehicles")
            return "Fahrzeuge";
        if (panelName == "EventsKOTH")
            return "Ereignisse / KOTH";
        if (panelName == "KOTHSettings")
            return "KOTH Optionen";
        if (panelName == "DebugLogs")
            return "Debug / Logs";
        if (panelName == "Weather")
            return "Wetter / Zeit";
        if (panelName == "Server")
            return "Server";
        if (panelName == "Garage")
            return "Garage";
        if (panelName == "Banking")
            return "Bank";
        if (panelName == "Groups")
            return "Gruppen";
        if (panelName == "TraderZ")
            return "TraderZ";
        if (panelName == "PlayerFun")
            return "Spieler Spass";
        return panelName;
    }

    string GetPanelLayout(string panelName)
    {
        if (panelName == "Dashboard") return "DeutschZ_Tools/gui/layouts/toolz/dashboard.layout";
        if (panelName == "Players") return "DeutschZ_Tools/gui/layouts/toolz/players.layout";
        if (panelName == "MapTeleport") return "DeutschZ_Tools/gui/layouts/toolz/mapteleport.layout";
        if (panelName == "Spawn") return "DeutschZ_Tools/gui/layouts/toolz/spawn.layout";
        if (panelName == "Vehicles") return "DeutschZ_Tools/gui/layouts/toolz/vehicles.layout";
        if (panelName == "Weather") return "DeutschZ_Tools/gui/layouts/toolz/weather.layout";
        if (panelName == "EventsKOTH") return "DeutschZ_Tools/gui/layouts/toolz/events.layout";
        if (panelName == "KOTHSettings") return "DeutschZ_Tools/gui/layouts/toolz/kothsettings.layout";
        if (panelName == "Server") return "DeutschZ_Tools/gui/layouts/toolz/server.layout";
        if (panelName == "DebugLogs") return "DeutschZ_Tools/gui/layouts/toolz/debug.layout";
        if (panelName == "Garage") return "DeutschZ_Tools/gui/layouts/toolz/garage.layout";
        if (panelName == "Banking") return "DeutschZ_Tools/gui/layouts/toolz/banking.layout";
        if (panelName == "Groups") return "DeutschZ_Tools/gui/layouts/toolz/groups.layout";
        if (panelName == "TraderZ") return "DeutschZ_Tools/gui/layouts/toolz/traderz.layout";
        if (panelName == "PlayerFun") return "DeutschZ_Tools/gui/layouts/toolz/playerfun.layout";
        return "DeutschZ_Tools/gui/layouts/toolz/dashboard.layout";
    }

    void ClearCurrentFrame()
    {
        if (m_CurrentFrame)
        {
            m_CurrentFrame.Unlink();
            m_CurrentFrame = null;
        }
        DeutschZTools_ClearDynamicRefs();
    }

    void ShowPanel(string panelName)
    {
        if (!m_ContentHost)
        {
            SetStatus("Content Host fehlt");
            return;
        }

        ClearCurrentFrame();

        string layoutPath = GetPanelLayout(panelName);
        m_CurrentFrame = GetGame().GetWorkspace().CreateWidgets(layoutPath, m_ContentHost);
        if (!m_CurrentFrame)
        {
            SetStatus("Frame konnte nicht laden: " + panelName);
            Print(DeutschZTools_Constants.LOG_PREFIX + "Failed to load frame layout " + layoutPath);
            return;
        }

        m_CurrentFrame.Show(true);
        m_CurrentFrame.Enable(true);
        m_SelectedTabKey = panelName;
        m_SelectedTabName = GetPanelLabel(panelName);
        if (m_SelectedTabText)
            m_SelectedTabText.SetText("Aktiver Reiter: " + m_SelectedTabName);

        DeutschZTools_BindFrameWidgets();
        SetStatus("Aktiver Reiter: " + m_SelectedTabName);
        DeutschZTools_UpdateAdminPosition();
        DeutschZTools_UpdateDebugText();
    }

    void DeutschZTools_HideWidget(Widget widget)
    {
        if (!widget)
            return;
        widget.Show(false);
        widget.Enable(false);
    }

    void DeutschZTools_ShowWidget(Widget widget)
    {
        if (!widget)
            return;
        widget.Show(true);
        widget.Enable(true);
    }

    void DeutschZTools_ShowKothTab(string tabName)
    {
        DeutschZTools_HideWidget(m_KothPanelGeneral);
        DeutschZTools_HideWidget(m_KothPanelSchedule);
        DeutschZTools_HideWidget(m_KothPanelZones);
        DeutschZTools_HideWidget(m_KothPanelCapture);
        DeutschZTools_HideWidget(m_KothPanelRewards);
        DeutschZTools_HideWidget(m_KothPanelAI);
        DeutschZTools_HideWidget(m_KothPanelMarkers);
        DeutschZTools_HideWidget(m_KothPanelEffects);
        DeutschZTools_HideWidget(m_KothPanelSafety);

        if (tabName == "General") DeutschZTools_ShowWidget(m_KothPanelGeneral);
        else if (tabName == "Schedule") DeutschZTools_ShowWidget(m_KothPanelSchedule);
        else if (tabName == "Zones") DeutschZTools_ShowWidget(m_KothPanelZones);
        else if (tabName == "Capture") DeutschZTools_ShowWidget(m_KothPanelCapture);
        else if (tabName == "Rewards") DeutschZTools_ShowWidget(m_KothPanelRewards);
        else if (tabName == "AI") DeutschZTools_ShowWidget(m_KothPanelAI);
        else if (tabName == "Markers") DeutschZTools_ShowWidget(m_KothPanelMarkers);
        else if (tabName == "Effects") DeutschZTools_ShowWidget(m_KothPanelEffects);
        else if (tabName == "Safety") DeutschZTools_ShowWidget(m_KothPanelSafety);

        SetStatus("KOTH Optionen Reiter: " + tabName);
    }

    string GetTargetSteam64()
    {
        if (m_TargetSteam64)
        {
            string value = m_TargetSteam64.GetText();
            value.Trim();
            if (value != "")
            {
                m_SelectedSteam64 = value;
                return value;
            }
        }

        return m_SelectedSteam64;
    }

    void DeutschZTools_UpdateAdminPosition()
    {
        Object player = GetGame().GetPlayer();
        string posText = "Admin position: unknown";
        if (player)
            posText = "Admin position: " + player.GetPosition().ToString();

        if (m_AdminPositionText)
            m_AdminPositionText.SetText(posText);
    }

    void DeutschZTools_SetAdminPositionFields()
    {
        Object player = GetGame().GetPlayer();
        if (!player || !m_TeleportX || !m_TeleportZ)
        {
            SetStatus("Admin Position nicht verfuegbar");
            return;
        }

        vector pos = player.GetPosition();
        m_TeleportX.SetText(pos[0].ToString());
        m_TeleportZ.SetText(pos[2].ToString());
        DeutschZTools_UpdateAdminPosition();
        SetStatus("Admin Position in Felder kopiert");
    }

    override bool OnDoubleClick(Widget w, int x, int y, int button)
    {
        if (button == MouseState.LEFT && w == m_MapWidget && m_MapFrame && m_MapFrame.IsVisible())
        {
            DeutschZTools_TeleportToMapPointer(x, y);
            return true;
        }
        return super.OnDoubleClick(w, x, y, button);
    }

    vector DeutschZTools_ScreenToMapWorld(int x, int y)
    {
        if (!m_MapWidget)
            return "0 0 0";

        vector screenPos = Vector(x, y, 0);
        vector mapPos = m_MapWidget.ScreenToMap(screenPos);
        mapPos[1] = DeutschZTools_GetSafeSurfaceY(mapPos[0], mapPos[2], mapPos[1]) + 0.10;
        return mapPos;
    }

    float DeutschZTools_GetSafeSurfaceY(float x, float z, float fallbackY)
    {
        float surfaceY = GetGame().SurfaceY(x, z);
        if (surfaceY < -1000.0 || surfaceY > 2000.0)
            return fallbackY;
        return surfaceY;
    }

    void DeutschZTools_TeleportToMapPointer(int x, int y)
    {
        if (!m_MapWidget)
        {
            SetStatus("Karten Teleport fehlgeschlagen");
            return;
        }

        vector pos = DeutschZTools_ScreenToMapWorld(x, y);
        if (m_TeleportX) m_TeleportX.SetText(pos[0].ToString());
        if (m_TeleportZ) m_TeleportZ.SetText(pos[2].ToString());
        DeutschZTools_Client.SendTeleportSelfToPosition(pos);
        SetStatus("Teleport zur Kartenposition...");
    }

    void TeleportFromFields()
    {
        if (!m_TeleportX || !m_TeleportZ)
            return;

        float xCoord = m_TeleportX.GetText().ToFloat();
        float zCoord = m_TeleportZ.GetText().ToFloat();
        Object player = GetGame().GetPlayer();
        float fallbackY = 0.0;
        if (player)
        {
            vector playerPos = player.GetPosition();
            fallbackY = playerPos[1];
        }

        vector pos = Vector(xCoord, DeutschZTools_GetSafeSurfaceY(xCoord, zCoord, fallbackY) + 0.10, zCoord);
        DeutschZTools_Client.SendTeleportSelfToPosition(pos);
        SetStatus("Teleport gesendet");
    }

    void SpawnFromFields(int spawnMode)
    {
        string className = "";
        if (m_SpawnClassname)
            className = m_SpawnClassname.GetText();

        ref TStringArray attachments = new TStringArray;
        if (m_SpawnAttachments)
        {
            string csv = m_SpawnAttachments.GetText();
            if (csv != "")
            {
                ref TStringArray rawAttachments = new TStringArray;
                csv.Split(",", rawAttachments);
                foreach (string rawAtt : rawAttachments)
                {
                    rawAtt.Trim();
                    if (rawAtt != "")
                        attachments.Insert(rawAtt);
                }
            }
        }

        string targetSteam64 = "";
        if (spawnMode == 1)
            targetSteam64 = GetTargetSteam64();

        if (spawnMode == 1 && targetSteam64 == "")
        {
            SetStatus("Erst Spieler auswaehlen, dann Beim Ziel spawnen.");
            return;
        }

        DeutschZTools_Client.SendSpawnObject(className, attachments, targetSteam64, spawnMode);
        if (spawnMode == 1)
            SetStatus("Spawn beim Ziel gesendet");
        else
            SetStatus("Spawn vor Admin gesendet");
    }

    void DeutschZTools_UpdateDebugText()
    {
        if (!m_DebugText)
            return;

        string debugText = "Menu state: open\n";
        debugText = debugText + "Selected tab: " + m_SelectedTabName + "\n";
        debugText = debugText + "Selected target: " + GetTargetSteam64() + "\n";
        debugText = debugText + "Frame source: dynamic LBAdminTool-style content loader\n";
        debugText = debugText + "Last response: " + m_LastStatus + "\n";
        debugText = debugText + "Player count cache: " + m_LastPlayerCount + "\n";
        debugText = debugText + "Version: " + DeutschZTools_Constants.VERSION + "\n";
        m_DebugText.SetText(debugText);
    }

    void DeutschZTools_CloseMenu()
    {
        if (GetGame() && GetGame().GetUIManager())
            GetGame().GetUIManager().HideScriptedMenu(this);
    }
}
