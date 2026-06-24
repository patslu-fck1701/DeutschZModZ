/*
DeutschZ ModZ
Eigenstaendige Implementierung fuer DeutschZ.
Autor/Eigentuemer: Patrick Sluzalek / fck1701.
Keine direkte Codeuebernahme aus Drittquellen.
Oeffentliche Quellen werden nur zur Konzept- und API-Verifikation genutzt.
*/

// DeutschZ KotHZ profile bootstrap.
// Physical server path: <profiles>/DeutschZ/KotHZ/Config/
// DayZ script path: $profile:DeutschZ/KotHZ/Config/

class DZKotHZ_ProfileFolders
{
	static const string ROOT_FOLDER   = "$profile:DeutschZ";
	static const string KOTH_FOLDER   = "$profile:DeutschZ/KotHZ/";
	static const string CONFIG_FOLDER = "$profile:DeutschZ/KotHZ/Config/";

	static void Ensure()
	{
		// Same style as the working DeutschZ_ConvoyZ module: create unconditionally.
		MakeDirectory(ROOT_FOLDER);
		MakeDirectory(KOTH_FOLDER);
		MakeDirectory(CONFIG_FOLDER);
		Print("[DeutschZ_KotHZ] Profile folders ensured: " + CONFIG_FOLDER);
	}
}
