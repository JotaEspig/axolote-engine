if ($args.Length -eq 0) {
    echo "This script copies the shared library needed to use Axolote Engine"
    echo "and paste into a path of your choice. It creates the folder"
    echo "'resources' containing ONLY the shaders and creates the folder"
    echo "'external' that has subfolders 'lib' and 'include'."
    echo ""
    echo "Usage: powershell -ExecutionPolicy Bypass -File .\install_windows.ps1 <path-to-install>"
    exit 1
}

$path=$args[0]
if (-not (Test-Path $path)) {
    echo "target path not found"
    exit 1
}

# prompt to choose your build type
$type = ""
while ($true) {
    echo "Choose your build type"
    echo "Release [1]"
    echo "Debug [2]"
    echo "Exit script [3]"
    $option = Read-Host "Your choice"
    if ($option -ne "1" -and $option -ne "2" -and $option -ne "3") {
        echo "Invalid option"
        sleep 1
        echo ""
    } else {
        break
    }
}

if ($option -eq "1") {
    $type = "Release"
} elseif ($option -eq "2") {
    $type = "Debug"
} elseif ($option -eq "3") {
    exit 1
}

$vcpkg_path = ""
while ($true) {
    $vcpkg_path = Read-Host "Enter the path to vcpkg.cmake"
    if (-not (Test-Path $vcpkg_path)) {
        echo "File not found. Try again"
        sleep 1
        echo ""
    }
    else {
        break
    }
}

if (-not (Test-Path "build")) {
    mkdir build
}
cd build
cmake -G "Visual Studio 17 2022" -DCMAKE_TOOLCHAIN_FILE=$path_to_vcpkg ..
cmake --build . --config $type
cd ..

echo ""
echo "Creating temporary folder"
mkdir tmp/external/lib/axolote
mkdir tmp/external/include
mkdir tmp/resources/shaders

echo "Copying content to temporary folder"
cp build/$type/* tmp/external/lib/axolote
cp -r include/axolote tmp/external/include
cp -r external/include/KHR tmp/external/include
cp -r resources/shaders/* tmp/resources/shaders

echo "Moving to target path: $path"
cp -r tmp/* $path

echo "Cleaning temp folder"
Remove-Item -Recurse -Force tmp
exit 0
