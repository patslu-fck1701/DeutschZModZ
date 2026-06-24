param([switch]$Build,[switch]$Force)
$RepoRoot = "P:\GitHub_DeutschZModZ\DeutschZModZ"
$ActiveMods = @("DeutschZ_Core","DeutschZ_ExpansionBridge","DeutschZ_KotHZ","DeutschZ_ConvoyZ","DeutschZ_GroundZero","DeutschZ_CourierZ","DeutschZ_OperationDeutschZ")
function TP($p){ try { Test-Path $p } catch { $false } }
function CountMods($root){ $c=0; foreach($m in $ActiveMods){ if(TP (Join-Path $root $m)){ $c++ } }; $c }
$candidates = @((Join-Path $RepoRoot "mods"),(Join-Path $RepoRoot "DeutschZModZ\mods"),(Join-Path $RepoRoot "03_FULL_CURRENT_REFERENCE_ALL_MODS"))
$best=$null;$score=-1
foreach($c in $candidates){ $s= if(TP $c){ CountMods $c } else {0}; Write-Host "Candidate $c => $s"; if($s -gt $score){$score=$s;$best=$c}}
Write-Host "ResolvedModsRoot: $best"
if(-not (TP (Join-Path $RepoRoot "mods"))){ Write-Host "ABBRUCH: Ziel mods fehlt. Erst Repo-Struktur reparieren."; pause; exit 3}
foreach($m in $ActiveMods){ $p=Join-Path (Join-Path $RepoRoot "mods") $m; if(TP $p){Write-Host "OK Mod: $m"} else {Write-Host "FEHLT Mod: $m"}}
Write-Host "CheckOnly: Kein Build ausgefuehrt."
pause
