class DeutschZ_Garage_Kit: ItemBase
{
    override void SetActions()
    {
        super.SetActions();
        AddAction(ActionTogglePlaceObject);
        AddAction(ActionDeployObject);
    }

    override bool IsDeployable()
    {
        return true;
    }

    string GetPlacementItemName()
    {
        return "DeutschZ_Garage_Kit_Placing";
    }

    string GetPlacedItemName()
    {
        return "DeutschZ_ParkingStation";
    }

    override void OnPlacementComplete(Man player, vector position = "0 0 0", vector orientation = "0 0 0")
    {
        super.OnPlacementComplete(player, position, orientation);

        if (!GetGame().IsServer()) {
            return;
        }

        Object station = GetGame().CreateObjectEx("DeutschZ_ParkingStation", position, ECE_PLACE_ON_SURFACE | ECE_UPDATEPATHGRAPH);
        if (station) {
            station.SetOrientation(orientation);
            station.SetPosition(position);
        }

        GetGame().ObjectDelete(this);
    }
}
