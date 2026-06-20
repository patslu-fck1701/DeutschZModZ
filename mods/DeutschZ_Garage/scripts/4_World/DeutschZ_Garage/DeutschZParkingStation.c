class DeutschZ_ParkingStation: Inventory_Base
{
    override bool CanPutIntoHands(EntityAI parent)
    {
        return false;
    }

    override bool CanPutInCargo(EntityAI parent)
    {
        return false;
    }

    string GetKitItemname()
    {
        return "DeutschZ_Garage_Kit";
    }
}

class DeutschZ_Garage_Sign: DeutschZ_ParkingStation
{
}
