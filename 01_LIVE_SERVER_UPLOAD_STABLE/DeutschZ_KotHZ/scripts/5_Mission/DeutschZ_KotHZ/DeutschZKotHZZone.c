/*
DeutschZ ModZ
Eigenstaendige Implementierung fuer DeutschZ.
Autor/Eigentuemer: Patrick Sluzalek / fck1701.
Keine direkte Codeuebernahme aus Drittquellen.
Oeffentliche Quellen werden nur zur Konzept- und API-Verifikation genutzt.
*/

class DeutschZKotHZZonesConfig
{
    ref array<ref DeutschZKotHZZone> Zones;

    void DeutschZKotHZZonesConfig()
    {
        Zones = new array<ref DeutschZKotHZZone>;

        DeutschZKotHZConfig defaults = new DeutschZKotHZConfig();
        if (defaults && defaults.Zones)
        {
            foreach (DeutschZKotHZZone zone : defaults.Zones)
            {
                if (zone)
                    Zones.Insert(zone);
            }
        }
    }
}
