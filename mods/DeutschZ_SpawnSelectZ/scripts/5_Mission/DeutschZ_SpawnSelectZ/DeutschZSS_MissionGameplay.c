
modded class MissionGameplay
{
    override void OnUpdate(float timeslice)
    {
        super.OnUpdate(timeslice);
        UAInput inp = GetUApi().GetInputByName("UADZSOpenSpawnSelect");
        if (inp && inp.LocalPress())
        {
            Print("[DeutschZ_SpawnSelectZ] SpawnSelect menu key pressed. UI shell pending.");
        }
    }
}
