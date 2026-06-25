# DZSM v0.7.9 FIX37 - INPUT DISCORD DONE SUMMARY

- Tastenauswahl umgestellt: keine choice.exe mehr, sondern Read-Host mit Buchstabe + ENTER.
- Keine Auto-Auswahl mehr, ausser ENTER wird bewusst gedrueckt und ein Fallback ist vorgesehen.
- Types-, Fahrzeugspawn- und GitHub-Menue nutzen dieselbe robuste Eingabe.
- Unter dem DONE/FAIL-Endbild erscheint eine normale gruene/rote Kurzliste der Aenderungen im Lauf.
- Webhook wird aus ToolDir\ServerToolSettings\webhooks.txt oder Desktop DZSM_webhooks.txt gelesen.
- Desktop-Webhooks werden nicht mehr blind mit leerem Template ueberschrieben.
- Rohe Discord-Webhook-URL in eigener Zeile wird akzeptiert, nicht nur DiscordStatusWebhook=.
- Webhook bleibt secret: nicht im Uploadpaket, nicht in GitHub-Plan, Reports redacted.
- Dateinamen bleiben kurz: DZSM_v_0_7_9.bat / DZSM_v_0_7_9.ps1.
