/*
DeutschZ ModZ
Eigenstaendige Implementierung fuer DeutschZ.
Autor/Eigentuemer: Patrick Sluzalek / fck1701.
Keine direkte Codeuebernahme aus Drittquellen.
Oeffentliche Quellen werden nur zur Konzept- und API-Verifikation genutzt.
*/

class DeutschZKotHZNPCConfig
{
    string EditHint;
    int EnableOptionalNPC;
    // Reserved optional DeutschZ NPC entity class. Disabled in this build.
    string NPCClassName;

    // Reserved optional DeutschZ NPC class rotation. Disabled in this build.
    ref array<string> NPCClassNames;

    // Reserved vanilla survivor model classnames for a future own DeutschZ NPC layer.
    ref array<string> NPCModelClassNames;

    int NPCAmount;
    float NPCSpawnRadius;
    int NPCSpawnHeightOffset;
    int NPCDespawnOnEventEnd;
    int ValidateClassBeforeSpawn;
    ref array<string> NPCLoadoutClassNames;
    ref array<string> KnownOptionalNPCClassNames;

    void DeutschZKotHZNPCConfig()
    {
        EditHint = "NPC config is reserved and disabled. DeutschZ_KotHZ currently uses infected waves only.";
        EnableOptionalNPC = 0;
        NPCClassName = "";

        NPCClassNames = new array<string>;

        NPCModelClassNames = new array<string>;

        NPCAmount = 0;
        NPCSpawnRadius = 25.0;
        NPCSpawnHeightOffset = 0;
        NPCDespawnOnEventEnd = 1;
        ValidateClassBeforeSpawn = 1;

        NPCLoadoutClassNames = new array<string>;

        KnownOptionalNPCClassNames = new array<string>;
    }
}
