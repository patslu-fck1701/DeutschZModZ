/*
    DeutschZ_GroundZero
    Owner: Patrick Sluzalek / fck1701
    Module: 4_World / GroundZeroItems
    Purpose: Campaign item classes and storage restrictions.
    Dependencies: DayZ scripts; optional CF/Expansion APIs only through adapter methods.
    Compliance: Original DeutschZ implementation. No copied foreign mod code, assets, configs or stubs.
*/

class GroundZero_ComponentBase extends Inventory_Base
{
    override bool CanPutInCargo(EntityAI parent)
    {
        if (!super.CanPutInCargo(parent)) return false;
        if (!parent) return true;

        string parentType = parent.GetType();
        parentType.ToLower();

        // ASSUMPTION: Generic storage blocking by class-name pattern until exact DeutschZ Banking/Garage APIs are exposed.
        if (parentType.Contains("bank") || parentType.Contains("garage") || parentType.Contains("safe") || parentType.Contains("crate")) return false;
        return true;
    }

    override bool CanBeSplit()
    {
        return false;
    }
}

class GroundZero_AlphaDataModule extends GroundZero_ComponentBase {}
class GroundZero_EnergyCell extends GroundZero_ComponentBase {}
class GroundZero_BioSample extends GroundZero_ComponentBase {}
class GroundZero_AuthChip extends GroundZero_ComponentBase {}
class GroundZero_ContainmentKey extends GroundZero_ComponentBase {}
class GroundZero_ResearchCore extends GroundZero_ComponentBase {}
