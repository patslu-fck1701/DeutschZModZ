/*
DeutschZ ModZ
Eigenstaendige Implementierung fuer DeutschZ.
Autor/Eigentuemer: Patrick Sluzalek / fck1701.
Keine direkte Codeuebernahme aus Drittquellen.
Oeffentliche Quellen werden nur zur Konzept- und API-Verifikation genutzt.
*/

class DeutschZKotHZSmokeConfig
{
    string EditHint;
    int EnableSmoke;
    int UseObjectSmoke;
    int UseParticleSmoke;
    int AutoActivateSmokeGrenade;
    int ForceSwitchOnSmokeGrenade;
    float SmokeHeightAboveFlagpole;
    float SmokeRefreshSeconds;
    float CompletedSmokeSeconds;

    int EnableFogHazard;
    string FogEditHint;
    float FogHazardChance;
    int FogStartOnReady;
    int FogStartOnProgress;
    int FogStartOnCompleted;
    int FogPulseSeconds;
    int FogEmitterCount;
    float FogRadius;
    float FogEmitterHeightOffset;
    string FogEmitterObjectType;
    int FogParticleType;
    int FogCleanupOnEventEnd;
    int EnableSmokeCannons;
    int SmokeCannonCount;
    float SmokeCannonRadius;
    ref array<string> SmokeCannonClassNames;

    // Current DeutschZ states: Green=ready, Yellow=in progress, Red=captured.
    string SmokeObjectClassNameWhite; // spawn compatibility
    string SmokeObjectClassNameBlack; // profile compatibility
    string SmokeObjectClassNameRed;
    string SmokeObjectClassNameYellow;
    int ParticleIdWhite; // spawn compatibility
    int ParticleIdBlack; // profile compatibility
    int ParticleIdRed;
    int ParticleIdYellow;

    // Profile compatibility fields. These remain so existing profile JSONs do not break loading.
    string SmokeObjectClassNameBlue;
    string SmokeObjectClassNameGreen;
    int ParticleIdBlue;
    int ParticleIdGreen;

    void DeutschZKotHZSmokeConfig()
    {
        EditHint = "Smoke config. DeutschZ states: green=ready, yellow=in progress, red=captured.";
        EnableSmoke = 0;
        UseObjectSmoke = 0;
        UseParticleSmoke = 0;
        AutoActivateSmokeGrenade = 1;
        ForceSwitchOnSmokeGrenade = 1;
        SmokeHeightAboveFlagpole = 13.0;
        SmokeRefreshSeconds = 85.0;
        CompletedSmokeSeconds = 180.0;

        EnableFogHazard = 0;
        FogEditHint = "KVM1 test fog enabled. ParticleType: 0=large gas, 1=tiny gas, 2=around gas, 3=ground fog.";
        FogHazardChance = 1.0;
        FogStartOnReady = 0;
        FogStartOnProgress = 0;
        FogStartOnCompleted = 0;
        FogPulseSeconds = 45;
        FogEmitterCount = 0;
        FogRadius = 85.0;
        FogEmitterHeightOffset = 0.0;
        FogEmitterObjectType = "DeutschZKotHZ_RuntimeFogEmitter";
        FogParticleType = 3;
        FogCleanupOnEventEnd = 1;
        EnableSmokeCannons = 0;
        SmokeCannonCount = 4;
        SmokeCannonRadius = 35.0;
        SmokeCannonClassNames = new array<string>;
        SmokeCannonClassNames.Insert("M18SmokeGrenade_Yellow");
        SmokeCannonClassNames.Insert("M18SmokeGrenade_Red");

        SmokeObjectClassNameWhite = "M18SmokeGrenade_Green";
        SmokeObjectClassNameBlack = "M18SmokeGrenade_Green";
        SmokeObjectClassNameRed = "M18SmokeGrenade_Red";
        SmokeObjectClassNameYellow = "M18SmokeGrenade_Yellow";

        ParticleIdWhite = 0;
        ParticleIdBlack = 0;
        ParticleIdRed = 0;
        ParticleIdYellow = 0;

        SmokeObjectClassNameBlue = "M18SmokeGrenade_Green";
        SmokeObjectClassNameGreen = "M18SmokeGrenade_Green";
        ParticleIdBlue = 0;
        ParticleIdGreen = 0;
    }
}
