class DeutschZTools_VehicleService
{
    static Transport FindNearestVehicle(vector position, float radius)
    {
        ref array<Object> objects = new array<Object>;
        ref array<CargoBase> proxyCargos = new array<CargoBase>;
        GetGame().GetObjectsAtPosition3D(position, radius, objects, proxyCargos);

        Transport best;
        float bestDist = radius + 1.0;

        foreach (Object obj : objects)
        {
            Transport vehicle = Transport.Cast(obj);
            if (!vehicle)
                continue;

            float dist = vector.Distance(position, vehicle.GetPosition());
            if (dist < bestDist)
            {
                best = vehicle;
                bestDist = dist;
            }
        }

        return best;
    }

    static bool RepairVehicle(Transport vehicle, out string message)
    {
        if (!vehicle)
        {
            message = "No vehicle found nearby.";
            return false;
        }

        vehicle.SetHealth01("", "", 1.0);

        ref array<EntityAI> inventory = new array<EntityAI>;
        vehicle.GetInventory().EnumerateInventory(InventoryTraversalType.PREORDER, inventory);

        foreach (EntityAI item : inventory)
        {
            if (!item)
                continue;

            item.SetHealth01("", "", 1.0);
        }

        vehicle.SetSynchDirty();
        message = "Vehicle repaired.";
        return true;
    }


    static bool FlipVehicle(Transport vehicle, out string message)
    {
        if (!vehicle)
        {
            message = "No vehicle found nearby.";
            return false;
        }

        vector ori = vehicle.GetOrientation();
        ori[1] = 0.0;
        ori[2] = 0.0;
        vehicle.SetOrientation(ori);

        vector pos = vehicle.GetPosition();
        pos[1] = pos[1] + 0.35;
        vehicle.SetPosition(pos);
        vehicle.SetSynchDirty();
        message = "Vehicle flipped upright.";
        return true;
    }

    static bool TeleportVehicleToAdmin(Transport vehicle, PlayerBase admin, out string message)
    {
        if (!vehicle)
        {
            message = "No vehicle found nearby.";
            return false;
        }

        if (!admin)
        {
            message = "Admin player not found.";
            return false;
        }

        vector pos = admin.GetPosition() + (admin.GetDirection() * 5.0);
        pos[1] = GetGame().SurfaceY(pos[0], pos[2]) + 0.20;
        vehicle.SetPosition(pos);
        vehicle.SetOrientation(admin.GetOrientation());
        vehicle.SetSynchDirty();
        message = "Vehicle teleported to admin.";
        return true;
    }
}
