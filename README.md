# 🦎 Axolote Engine

Graphics engine made in C++ using OpenGL

🇧🇷 README em português: [READMEpt.md](READMEpt.md)

## 📄 Description

Graphics engine made in C++ using OpenGL version 3.3+. The idea of the project came from the fact that I (João Vitor Espig) wanted to learn OpenGL at the start of 2023 and have some fun doing some games and simulations, and then I decided to create a small engine using OpenGL. One of my motivations for learning OpenGL came from Minecraft (it uses OpenGL to render its graphics) and from the curiosity that I had about how 3D games are made.

## 📦 Dependencies

* CMake 2.8.5+
* OpenGL 3.3+
* GLFW3
* GLM
* Doxygen (Optional)

### Linux

Ubuntu:
```bash
sudo apt-get install cmake
sudo apt-get install libglm-dev
sudo apt-get install libglfw3-dev libglfw3
sudo apt-get install libassimp-dev
```

Arch:
```bash
sudo pacman -S cmake
sudo pacman -S glm
sudo pamcan -S glfw
sudo pacman -S assimp
```

### Windows

Download the CMake installer in [https://cmake.org/download/](https://cmake.org/download/)
and install it.

The other dependencies will be installed via vcpkg.
Install the vcpkg:
```bash
git clone https://github.com/microsoft/vcpkg.git
cd vcpkg
bootstrap-vcpkg.bat
vcpkg.exe integrate install
```

Install the dependencies
```bash
vcpkg.exe install glm
vcpkg.exe install glfw3
vcpkg.exe install assimp
```

## 🔧 Compiling

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

For more details about building the project, see [building.md](docs/en/building.md).

## 🛠️ Installation

see [install.md](docs/en/install.md).

## 🚀 Getting Started

see [getting-started.md](docs/en/getting-started.md).

## 🧪 Executing some tests

After compiling the project, go back to the root directory of the project and
run the following commands:

For Linux
```bash
./bin/window-test
./bin/models-and-shaders-test
./bin/main-test
```

For Windows
```bash
.\bin\Release\window-test.exe
.\bin\Release\models-and-shaders-test.exe
.\bin\Release\main-test.exe
```

## 📚 Documentation

If you have Doxygen, you can read the documentation using:
```bash
git clone https://github.com/JotaEspig/axolote-engine
cd axolote-engine
mkdir build
cd build
cmake ..
make docs
```

## ❓ Help

You can create an Issue or contact the mantainers (authors)

## 👥 Authors

 * João Vitor Espig ([JotaEspig](https://github.com/JotaEspig))
 * Mickael Reichert ([mickaelrei](https://github.com/mickaelrei))
 * Gustavo Tramontin Pedro ([gustatramontin](https://github.com/gustatramontin))

## 🕒 Version History

see [CHANGELOG.md](CHANGELOG.md)

## 📜 License

This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details

## 🙏 Acknowledgments

* [Learn OpenGL](https://github.com/JoeyDeVries/LearnOpenGL)
* [OpenGL course](https://www.youtube.com/watch?v=45MIykWJ-C4&ab_channel=freeCodeCamp.org) - By freeCodeCamp
* [README-Template.md](https://gist.github.com/DomPizzie/7a5ff55ffa9081f2de27c315f5018afc)
