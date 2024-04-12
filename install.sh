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

# prompt to choose your build type
type=""
while true; do
    echo "Choose your build type"
    echo "Release [1]"
    echo "Debug [2]"
    echo "Exit script [3]"
    read -p "" option

    case $option in
        1 | 2 | 3) break ;;
        *) echo -e "Invalid option \n" && sleep 1 ;;
    esac
done

if [ $option = 1 ]; then
    type="Release"
elif [ $option = 2 ]; then
    type="Debug"
else
    exit
fi

cmake . -DCMAKE_BUILD_TYPE=$type
make -j4

echo
echo "Creating temporary folder"
mkdir tmp/external/lib/axolote -p
mkdir tmp/external/include -p
mkdir tmp/resources/shaders -p

echo "Moving content to temp folder"
cp lib/* tmp/external/lib/axolote/
cp external/assimp/* tmp/external/lib/axolote
cp -r include/axolote tmp/external/include/
cp -r resources/shaders tmp/resources/shaders

echo "Checking existence of $path"
if [ -d "$path" ]; then
    echo "Creating target path"
    mkdir $path -p
fi

echo "Moving to target path: $path"
cp tmp/external -r $path

echo "Cleaning temp folder"
rm -rf tmp
exit 0
