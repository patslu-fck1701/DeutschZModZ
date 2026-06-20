modded class PlayerBase
{
    bool m_DeutschZTraderZ_IsTrader = false;
    bool m_DeutschZTraderZ_IsP2PTrader = false;
    bool m_DeutschZTraderZ_IsDeliveryTrader = false;
    bool m_DeutschZTraderZ_IsInSafezone = false;
    int m_DeutschZTraderZ_TraderIndex = -1;

    void PlayerBase()
    {
        RegisterNetSyncVariableBool("m_DeutschZTraderZ_IsTrader");
        RegisterNetSyncVariableBool("m_DeutschZTraderZ_IsP2PTrader");
        RegisterNetSyncVariableBool("m_DeutschZTraderZ_IsDeliveryTrader");
        RegisterNetSyncVariableBool("m_DeutschZTraderZ_IsInSafezone");
        RegisterNetSyncVariableInt("m_DeutschZTraderZ_TraderIndex", -1, 1000);
    }

    void DeutschZTraderZ_SetTrader(int traderIndex, bool p2p, bool delivery)
    {
        m_DeutschZTraderZ_IsTrader = true;
        m_DeutschZTraderZ_TraderIndex = traderIndex;
        m_DeutschZTraderZ_IsP2PTrader = p2p;
        m_DeutschZTraderZ_IsDeliveryTrader = delivery;
        SetSynchDirty();
    }

    bool DeutschZTraderZ_IsTrader()
    {
        return m_DeutschZTraderZ_IsTrader;
    }

    bool DeutschZTraderZ_IsP2PTrader()
    {
        return m_DeutschZTraderZ_IsP2PTrader;
    }

    bool DeutschZTraderZ_IsDeliveryTrader()
    {
        return m_DeutschZTraderZ_IsDeliveryTrader;
    }

    int DeutschZTraderZ_GetTraderIndex()
    {
        return m_DeutschZTraderZ_TraderIndex;
    }

    override bool CanBeTargetedByAI(EntityAI ai)
    {
        if (m_DeutschZTraderZ_IsTrader)
            return false;
        return super.CanBeTargetedByAI(ai);
    }

    override void SetActions(out TInputActionMap InputActionMap)
    {
        super.SetActions(InputActionMap);
        AddAction(DeutschZTraderZ_ActionOpenTrader, InputActionMap);
    }
}
