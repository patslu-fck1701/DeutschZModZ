class DeutschZTools_Result
{
    bool Success;
    string Message;

    void DeutschZTools_Result()
    {
        Success = false;
        Message = "";
    }

    void Set(bool success, string message)
    {
        Success = success;
        Message = message;
    }
}

class DeutschZTools_PlayerSnapshot
{
    string Steam64;
    string Name;
    vector Position;
    float Health01;
    float Blood01;
    float Shock01;
    bool IsAlive;

    void DeutschZTools_PlayerSnapshot()
    {
        Steam64 = "";
        Name = "";
        Position = "0 0 0";
        Health01 = 0.0;
        Blood01 = 0.0;
        Shock01 = 0.0;
        IsAlive = false;
    }
}

class DeutschZTools_SpawnRequest
{
    string ClassName;
    vector Position;
    ref TStringArray Attachments;
    bool PlaceOnSurface;
    string TargetSteam64;
    int SpawnMode;

    void DeutschZTools_SpawnRequest()
    {
        ClassName = "";
        Position = "0 0 0";
        Attachments = new TStringArray;
        PlaceOnSurface = true;
        TargetSteam64 = "";
        SpawnMode = 0;
    }
}
