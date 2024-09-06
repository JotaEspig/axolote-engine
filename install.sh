if [ "$#" -ne 1 ]; then echo
    echo "This script copies the shared library needed to use Axolote Engine"
    echo "and paste into a path of your choice. It creates the folder"
    echo "'resources' containing ONLY the shaders and creates the folder"
    echo "'external' that has subfolders 'lib' and 'include'."
    echo
    echo "Usage: ./install.sh <path-to-install>"
    exit 1
fi

path=$1
if [ ! -d "$path" ]; then
    echo "target path not found"
    exit 1
fi


# prompt to choose your build type
type=""
while true; do
    echo "Choose your build type"
    echo "Release [1]"
    echo "Debug [2]"
    echo "Exit script [3]"
    read -p "Your choice: " option

    case $option in
        1 | 2 | 3) break ;;
        *) echo -e "Invalid option\n" && sleep 1 ;;
    esac
done

if [ $option = 1 ]; then
    type="Release"
elif [ $option = 2 ]; then
    type="Debug"
else
    exit
fi

use_local_assimp=""
while true; do
    echo "Do you want to use the local assimp library or the one installed"
    echo "on your machine (via your package manager)?"
    echo "Local [1]"
    echo "Installed [2]"
    echo "Exit script [3]"
    read -p "Your choice: " option

    case $option in
        1 | 2 | 3) break ;;
        *) echo -e "Invalid option\n" && sleep 1 ;;
    esac
done

if [ $option = 1 ]; then
    use_local_assimp="On"
elif [ $option = 2 ]; then
    use_local_assimp="Off"
else
    exit
fi

if [ ! -d "build" ]; then
    mkdir build
fi
cd build
cmake .. -DCMAKE_BUILD_TYPE=$type -DUSE_LOCAL_ASSIMP=$use_local_assimp
make -j4
cd ..

echo
echo "Creating temporary folder"
mkdir tmp/external/lib/axolote -p
mkdir tmp/external/include -p
mkdir tmp/external/imgui -p
mkdir tmp/resources/shaders -p

echo "Copying content to temp folder"
cp lib/* tmp/external/lib/axolote/
cp external/lib/assimp/* tmp/external/lib/axolote/
cp -r external/imgui/* tmp/external/imgui/
cp -r include/axolote tmp/external/include/
cp -r resources/shaders/* tmp/resources/shaders

echo "Moving to target path: $path"
cp tmp/* -r $path

echo "Cleaning temp folder"
rm -rf tmp
exit 0
