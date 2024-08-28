## Compiling

Clone the repository:
```bash
git clone https://github.com/JotaEspig/axolote-engine
cd axolote-engine
mkdir build
cd build
```

### Linux

Compile the project:
```bash
cmake ..
make -j4
```

### Windows

Compile the project (pay attention to the path of the vcpkg.cmake file,
you must change it to your path where you cloned the vcpkg repository):
```bash
cmake -G "Visual Studio 17 2022" -DCMAKE_TOOLCHAIN_FILE=C:/path/to/vcpkg/scripts/buildsystems/vcpkg.cmake ..
cmake --build . --config Release
```

### Compilation flags

 * `-DCMAKE_BUILD_TYPE=Release` to build the project in release mode. Default is `Release`. (Only for Linux)
 * `-DUSE_LOCAL_ASSIMP` to use the local assimp library. Default is `OFF`. (Only for Linux)
 * `-DDEBUG` to enable debug mode (It's displayed on the terminal the creation, deletion, resizing, etc of OpenGL objects). Default is `ON`.
 * `-DBUILD_TESTS=ON` to build the tests. Default is `ON`.

To set the flags, you must add it to the cmake command. For example:
```bash
cmake -DDEBUG=OFF ..
```
