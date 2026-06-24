/*
    DeutschZ_GroundZero
    Owner: Patrick Sluzalek / fck1701
    Purpose: Original DeutschZ Ground Zero campaign event source.
    Dependencies: DayZ scripts, optional CF/Expansion/Expansion AI/Expansion Marker as API only.
    Compliance: No foreign mod source, config, assets, class bodies or stubs copied.
*/

class GroundZeroRewardManager
{
    protected GroundZeroConfig m_Config; protected GroundZeroNotificationManager m_Notifications;
    void GroundZeroRewardManager(GroundZeroConfig cfg, GroundZeroNotificationManager n){ m_Config=cfg; m_Notifications=n; }
    void GrantSuccess(){ GroundZeroLogging.Info("Rewards", "Success reward money=" + m_Config.RewardMoneySuccess.ToString() + " xp=" + m_Config.RewardBattlepassXPSuccess.ToString()); m_Notifications.Broadcast("Ground Zero erfolgreich abgeschlossen"); }
    void GrantFailure(){ GroundZeroLogging.Info("Rewards", "Failure reward xp=" + m_Config.RewardBattlepassXPFail.ToString()); m_Notifications.Broadcast("Ground Zero fehlgeschlagen"); }
}
