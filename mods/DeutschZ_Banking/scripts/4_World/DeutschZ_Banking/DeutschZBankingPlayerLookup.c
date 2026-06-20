class DeutschZBankingPlayerLookup
{
    static PlayerBase GetPlayerByIdentity(PlayerIdentity identity)
    {
        if (!identity) {
            return null;
        }

        ref array<Man> players = new array<Man>();
        GetGame().GetPlayers(players);

        foreach (Man man : players) {
            PlayerBase player = PlayerBase.Cast(man);
            if (!player || !player.GetIdentity()) {
                continue;
            }

            if (player.GetIdentity().GetPlainId() == identity.GetPlainId()) {
                return player;
            }
        }

        return null;
    }
}
