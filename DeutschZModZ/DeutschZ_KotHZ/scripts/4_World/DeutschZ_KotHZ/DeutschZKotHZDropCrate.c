/*
DeutschZ ModZ
Eigenstaendige Implementierung fuer DeutschZ.
Autor/Eigentuemer: Patrick Sluzalek / fck1701.
Keine direkte Codeuebernahme aus Drittquellen.
Oeffentliche Quellen werden nur zur Konzept- und API-Verifikation genutzt.
*/

// DeutschZ KotHZ v1.0.30
// Unique SeaChest-based reward crate with 500 cargo slots in config.cpp.
class DeutschZKotHZ_RewardCrate extends SeaChest
{
    override bool CanPutInCargo(EntityAI parent)
    {
        return false;
    }

    override bool CanPutIntoHands(EntityAI parent)
    {
        return false;
    }
}

// Compatibility alias for existing configs/class references.
class DeutschZKotHZ_DropCrate extends DeutschZKotHZ_RewardCrate
{
}
