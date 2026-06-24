/* CourierZ runtime state DTOs. */

class CourierZState
{
    int State;
    string EventId;
    string CurrentCarrierID;
    string CurrentCarrierName;
    vector CasePosition;
    vector CarrierLastPosition;
    vector DeliveryPosition;
    float StartedAt;
    float EndsAt;
    float NextAutoStartAt;
    float CleanupAt;
    int EventsStartedThisRestart;
    int RequiredKills;
    int CurrentKills;

    void CourierZState()
    {
        Reset();
    }

    void Reset()
    {
        State = CourierZConstants.STATE_IDLE;
        EventId = "";
        CurrentCarrierID = "";
        CurrentCarrierName = "";
        CasePosition = "0 0 0";
        CarrierLastPosition = "0 0 0";
        DeliveryPosition = "0 0 0";
        StartedAt = 0;
        EndsAt = 0;
        NextAutoStartAt = 0;
        CleanupAt = 0;
        RequiredKills = 0;
        CurrentKills = 0;
    }
}
