/*
DeutschZ ModZ
Eigenstaendige Implementierung fuer DeutschZ.
Autor/Eigentuemer: Patrick Sluzalek / fck1701.
Modul: DeutschZ_Core LanguageCore.
Zweck: Zentrale, sichere Stringtable-Key-Hilfe mit englischem Fallback.
Keine direkte Codeuebernahme aus Drittquellen.
*/

class DeutschZCore_LanguageCore
{
    static string HashKey(string key)
    {
        if (key == "") return "";
        if (key.IndexOf("#") == 0) return key;
        return "#" + key;
    }

    static string ConfigKey(string key)
    {
        if (key == "") return "";
        if (key.IndexOf("$") == 0) return key;
        return "$" + key;
    }

    static string Text(string key, string englishFallback = "")
    {
        if (key == "") return englishFallback;

        string lookup = HashKey(key);
        string translated = Widget.TranslateString(lookup);

        if (translated == "") return englishFallback;
        if (translated == lookup) return englishFallback;
        if (translated == key) return englishFallback;

        return translated;
    }

    static string TextHash(string keyWithHash, string englishFallback = "")
    {
        return Text(keyWithHash, englishFallback);
    }
}
