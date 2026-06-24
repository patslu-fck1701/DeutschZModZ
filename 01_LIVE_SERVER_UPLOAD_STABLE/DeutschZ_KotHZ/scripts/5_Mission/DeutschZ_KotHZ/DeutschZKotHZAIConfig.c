class DeutschZKotHZAIConfig
{
    string EditHint;
    int EnableExpansionAI;
    // Main optional AI entity class. Leave empty for vanilla/CF-only servers.
    string AIClassName;

    // Optional spawn-class rotation. Leave empty for vanilla/CF-only servers.
    ref array<string> AIClassNames;

    // Vanilla survivor model classnames for future eAI model/appearance integration.
    ref array<string> AIModelClassNames;

    int AIAmount;
    float AISpawnRadius;
    int AISpawnHeightOffset;
    int AIDespawnOnEventEnd;
    int ValidateClassBeforeSpawn;
    ref array<string> AILoadoutClassNames;
    ref array<string> KnownExpansionAIClassNames;

    void DeutschZKotHZAIConfig()
    {
        EditHint = "AI config is parked for now. Keep disabled; KOTH currently uses zombie waves only.";
        EnableExpansionAI = 0;
        AIClassName = "";

        AIClassNames = new array<string>;

        AIModelClassNames = new array<string>;

        AIAmount = 0;
        AISpawnRadius = 25.0;
        AISpawnHeightOffset = 0;
        AIDespawnOnEventEnd = 1;
        ValidateClassBeforeSpawn = 1;

        AILoadoutClassNames = new array<string>;

        KnownExpansionAIClassNames = new array<string>;
    }
}
