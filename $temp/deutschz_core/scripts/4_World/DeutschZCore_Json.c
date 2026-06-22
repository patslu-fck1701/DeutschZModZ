/*
    DeutschZ ModZ
    Autor/Eigentuemer: Patrick Sluzalek / fck1701
    Projekt: DeutschZ
    Zweck: Eigene DeutschZ-Implementierung fuer Core, ExpansionBridge und Event-Module.
    Quellen-/Konzeptnachweis: Eigenentwickelte Struktur; DayZ, CF und Expansion nur als Laufzeit-API/Abhaengigkeit.
    No-Copy-Bestaetigung: Kein Code, keine Assets und keine Configs aus fremden Mods kopiert.
*/

class DeutschZCore_Json
{
    static bool Save(string path, Class data)
    {
        if (!data || path == string.Empty)
            return false;
        JsonFileLoader<Class>.JsonSaveFile(path, data);
        return true;
    }

    static bool Load(string path, Class data)
    {
        if (!data || path == string.Empty || !FileExist(path))
            return false;
        JsonFileLoader<Class>.JsonLoadFile(path, data);
        return true;
    }
}
