if ($args.Length -eq 0) {
    Write-Output "This script copies the shared library needed to use Axolote Engine"
    Write-Output "and paste into a path of your choice. It creates the folder"
    Write-Output "'resources' containing ONLY the shaders and creates the folder"
    Write-Output "'external' that has subfolders 'lib' and 'include'."
    Write-Output ""
    Write-Output "Usage: powershell -ExecutionPolicy Bypass -File .\install_windows.ps1 <path-to-install>"
    exit 1
}

$path = $args[0]
if (-not (Test-Path $path)) {
    Write-Output "target path not found"
    exit 1
}

# prompt to choose your build type
$type = ""
while ($true) {
    Write-Output "Choose your build type"
    Write-Output "Release [1]"
    Write-Output "Debug [2]"
    Write-Output "Exit script [3]"
    $option = Read-Host "Your choice"
    if ($option -ne "1" -and $option -ne "2" -and $option -ne "3") {
        Write-Output "Invalid option"
        Start-Sleep -Seconds 1
        Write-Output ""
    }
    else {
        break
    }
}

if ($option -eq "1") {
    $type = "Release"
}
elseif ($option -eq "2") {
    $type = "Debug"
}
elseif ($option -eq "3") {
    exit 1
}

$vcpkg_path = ""
while ($true) {
    $vcpkg_path = Read-Host "Enter the path to vcpkg.cmake"
    if (-not (Test-Path $vcpkg_path)) {
        Write-Output "File not found. Try again"
        Start-Sleep -Seconds 1
        Write-Output ""
    }
    else {
        break
    }
}

if (-not (Test-Path "build")) {
    New-Item -ItemType Directory -Name build
}
Set-Location build
cmake -G "Visual Studio 17 2022" -DCMAKE_TOOLCHAIN_FILE=$vcpkg_path ..
cmake --build . --config $type
Set-Location ..

Write-Output ""
Write-Output "Creating temporary folder"
New-Item -ItemType Directory -Path tmp/external/lib/axolote
New-Item -ItemType Directory -Path tmp/external/include
New-Item -ItemType Directory -Path tmp/external/imgui
New-Item -ItemType Directory -Path tmp/resources/shaders

Write-Output "Copying content to temporary folder"
Copy-Item -Path build/$type/* -Destination tmp/external/lib/axolote
Copy-Item -Recurse -Path include/axolote -Destination tmp/external/include
Copy-Item -Recurse -Path external/imgui/* -Destination tmp/external/imgui/
Copy-Item -Recurse -Path external/include/KHR -Destination tmp/external/include
Copy-Item -Recurse -Path resources/shaders/* -Destination tmp/resources/shaders

Write-Output "Moving to target path: $path"
Copy-Item -Recurse -Path tmp/* -Destination $path

Write-Output "Cleaning temp folder"
Remove-Item -Recurse -Force tmp
exit 0
