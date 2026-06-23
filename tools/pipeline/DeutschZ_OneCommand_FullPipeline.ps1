param(
    [ValidateSet("Full", "Validate", "Build", "Test", "Package")]
    [string]$Mode = "Full",
    [int]$Rounds = 3,
    [int]$TestSeconds = 90,
    [string]$RepoRoot = "P:\GitHub_DeutschZModZ\DeutschZModZ",
    [string]$ServerRoot = "F:\Programme\steamapps\common\DayZServer",
    [string]$DeployRoot = "P:\ReadyMods",
    [string]$KeyName = "DeutschZLocal"
)

$pipeline = Join-Path $PSScriptRoot "DeutschZ_Full_Build_Test_OnlinePrep.ps1"
& $pipeline -Mode $Mode -Rounds $Rounds -TestSeconds $TestSeconds -RepoRoot $RepoRoot -ServerRoot $ServerRoot -DeployRoot $DeployRoot -KeyName $KeyName
