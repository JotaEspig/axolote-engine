if [ "$#" -ne 1 ]; then
    echo
    echo "This script copies the shared library needed to use Axolote Engine"
    echo "and paste into a path of your choice. It creates the folder called"
    echo "'external' that has subfolders 'lib' and 'include'. You should then"
    echo "link the libraries and the header files when compiling"
    echo
    echo "Usage: ./install.sh <path-to-install>"
    exit
fi

path=$1
cmake .
make -j4

echo
echo "Creating temporary folder"
mkdir tmp/external/lib/axolote -p
mkdir tmp/external/include -p

echo "Moving content to temp folder"
cp lib/* tmp/external/lib/axolote/
cp external/assimp/* tmp/external/lib/
cp -r include/axolote tmp/external/include/

echo "Checking existence of $path"
if [ -d "$path" ]; then
    echo "Creating target path"
    mkdir $path -p
fi

echo "Moving to target path: $path"
cp tmp/external -r $path

echo "Cleaning temp folder"
rm -rf tmp
