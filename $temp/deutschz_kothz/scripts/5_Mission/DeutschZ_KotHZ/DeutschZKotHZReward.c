/*
DeutschZ ModZ
Eigenstaendige Implementierung fuer DeutschZ.
Autor/Eigentuemer: Patrick Sluzalek / fck1701.
Keine direkte Codeuebernahme aus Drittquellen.
Oeffentliche Quellen werden nur zur Konzept- und API-Verifikation genutzt.
*/

class DeutschZKotHZReward
{
    string EditHint;
    string ClassName;
    int Quantity;
    float SpawnChance;
    int MaxSpawnable;
    string MagazineClassName;
    ref array<string> AlternativeClassNames;
    ref array<ref DeutschZKotHZReward> AttachmentItems;
    ref array<ref DeutschZKotHZReward> CargoItems;
    ref array<ref DeutschZKotHZReward> ExtraRewardItems;

    void DeutschZKotHZReward()
    {
        EditHint = "Reward item. Quantity -1 means normal item spawn. SpawnChance is percent. AttachmentItems/CargoItems/ExtraRewardItems are optional nested reward entries.";
        ClassName = "NailBox";
        Quantity = 1;
        SpawnChance = 100.0;
        MaxSpawnable = -1;
        MagazineClassName = "";
        AlternativeClassNames = new array<string>;
        AttachmentItems = new array<ref DeutschZKotHZReward>;
        CargoItems = new array<ref DeutschZKotHZReward>;
        ExtraRewardItems = new array<ref DeutschZKotHZReward>;
    }
}
