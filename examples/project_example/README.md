# Compiling the code

Create a directory for the build files and enter it.
```bash
mkdir build
cd build
```

## Linux

```bash
cmake ..
make -j4
```

## Windows

```bash
cmake -G "Visual Studio 17 2022" -DCMAKE_TOOLCHAIN_FILE=C:/path/to/vcpkg/scripts/buildsystems/vcpkg.cmake ..
cmake --build . --config Release
```

# Running the code

The executable will be in the `bin` directory. run it.

On Linux:
```bash
./bin/exe-test
```
On Windows:
```bash
.\bin\Release\exe-test.exe
```
