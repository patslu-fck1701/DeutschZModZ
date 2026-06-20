modded class MissionGameplay
{
    protected ref DeutschZTools_AdminMenu m_DeutschZTools_Menu;

    override void OnUpdate(float timeslice)
    {
        super.OnUpdate(timeslice);

        UAInput input = GetUApi().GetInputByName("UADeutschZToolsMenu");
        if (input && input.LocalPress())
        {
            DeutschZTools_ToggleMenu();
        }

        UAInput backInput = GetUApi().GetInputByName("UAUIBack");
        if (backInput && backInput.LocalPress())
        {
            DeutschZTools_CloseMenuIfOpen();
        }

        DeutschZTools_PollClientInbox();
    }

    void DeutschZTools_ToggleMenu()
    {
        UIScriptedMenu currentMenu = GetGame().GetUIManager().GetMenu();

        if (currentMenu && currentMenu == m_DeutschZTools_Menu)
        {
            GetGame().GetUIManager().HideScriptedMenu(m_DeutschZTools_Menu);
            m_DeutschZTools_Menu = null;
            return;
        }

        if (currentMenu)
            return;

        m_DeutschZTools_Menu = new DeutschZTools_AdminMenu();
        UIScriptedMenu shownMenu = GetGame().GetUIManager().ShowScriptedMenu(m_DeutschZTools_Menu, null);
        if (!shownMenu)
        {
            m_DeutschZTools_Menu = null;
            return;
        }

        DeutschZTools_Client.SendAction(DeutschZTools_Action.REQUEST_MENU_ACCESS);
    }

    void DeutschZTools_CloseMenuIfOpen()
    {
        DeutschZTools_AdminMenu menu = DeutschZTools_AdminMenu.Cast(GetGame().GetUIManager().GetMenu());
        if (!menu)
            return;

        GetGame().GetUIManager().HideScriptedMenu(menu);
        if (menu == m_DeutschZTools_Menu)
            m_DeutschZTools_Menu = null;
    }

    void DeutschZTools_PollClientInbox()
    {
        DeutschZTools_AdminMenu menu = DeutschZTools_AdminMenu.Cast(GetGame().GetUIManager().GetMenu());
        if (!menu)
            return;

        bool success;
        string message;
        if (DeutschZTools_ClientInbox.ConsumeStatus(success, message))
        {
            menu.SetStatus(message);
            DeutschZTools_Client.DisplayMessage(message);
        }

        string listText;
        int count;
        if (DeutschZTools_ClientInbox.ConsumePlayerList(listText, count))
        {
            menu.SetPlayerList(listText);
            menu.SetStatus("Player list updated.");
        }

        string garageTitle;
        string garageRows;
        if (DeutschZTools_ClientInbox.ConsumeGarageList(garageTitle, garageRows))
        {
            menu.SetGarageList(garageTitle, garageRows);
            menu.SetStatus(garageTitle);
        }

        string bankingTitle;
        string bankingRows;
        if (DeutschZTools_ClientInbox.ConsumeBankingList(bankingTitle, bankingRows))
        {
            menu.SetBankingList(bankingTitle, bankingRows);
            menu.SetStatus(bankingTitle);
        }

        string groupsTitle;
        string groupsRows;
        if (DeutschZTools_ClientInbox.ConsumeGroupsList(groupsTitle, groupsRows))
        {
            menu.SetGroupsList(groupsTitle, groupsRows);
            menu.SetStatus(groupsTitle);
        }

        string traderZTitle;
        string traderZRows;
        if (DeutschZTools_ClientInbox.ConsumeTraderZList(traderZTitle, traderZRows))
        {
            menu.SetTraderZList(traderZTitle, traderZRows);
            menu.SetStatus(traderZTitle);
        }
    }
}
