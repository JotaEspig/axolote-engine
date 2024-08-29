# Axolote Engine

Engine gráfica feita em C++ utilizando OpenGL

## Descrição

README in english: [README.md](README.md)

Engine gráfica feita em C++ utilizando OpenGL versão 3.3+. A ideia do projeto surgiu do fato de que eu (João Vitor Espig) queria aprender OpenGL no início de 2023 e me divertir fazendo alguns jogos e simulações, e então decidi criar uma pequena engine utilizando OpenGL. Uma das minhas motivações para aprender OpenGL veio do Minecraft (ele usa OpenGL para renderizar seus gráficos) e da curiosidade que eu tinha sobre como os jogos 3D são feitos.
## Dependências

* CMake 2.8.5+
* OpenGL 3.3+
* GLFW3
* GLM
* Doxygen (Opcional)

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

Baixe o instalador do CMake em [https://cmake.org/download/](https://cmake.org/download/)
e instale-o.

As outras dependências serão instaladas via vcpkg.
Instale o vcpkg:
```bash
git clone https://github.com/microsoft/vcpkg.git
cd vcpkg
bootstrap-vcpkg.bat
vcpkg.exe integrate install
```

Instale as dependências:
```bash
vcpkg.exe install glm
vcpkg.exe install glfw3
vcpkg.exe install assimp
```

## Compilação

Clone o repositório e vá para a pasta build:
```bash
git clone https://github.com/JotaEspig/axolote-engine
cd axolote-engine
mkdir build
cd build
```

### Linux

Compile o projeto:
```bash
cmake ..
make -j4
```

### Windows

Compile o projeto (preste atenção no caminho do arquivo vcpkg.cmake,
você deve alterá-lo para o seu caminho onde você clonou o repositório do vcpkg):
```bash
cmake -G "Visual Studio 17 2022" -DCMAKE_TOOLCHAIN_FILE=C:/caminho/para/vcpkg/scripts/buildsystems/vcpkg.cmake ..
cmake --build . --config Release
```


Para mais detalhes sobre a compilação do projeto, veja [building.md](docs/pt-br/building.md).

## Instalação

veja [install.md](docs/pt-br/install.md).

## Getting Started

veja [getting-started.md](docs/pt-br/getting-started.md).

## Executing some tests

After compiling the project, go back to the root directory of the project and
run the following commands:

Após compilar o projeto, volte para o diretório raiz do projeto e execute os seguintes comandos:

Para Linux
```bash
./bin/window-test
./bin/models-and-shaders-test
./bin/main-test
```

Para Windows
```bash
.\bin\Release\window-test.exe
.\bin\Release\models-and-shaders-test.exe
.\bin\Release\main-test.exe
```

## Documentação

Se você tiver o Doxygen, você pode ler a documentação usando:
```bash
git clone https://github.com/JotaEspig/axolote-engine
cd axolote-engine
mkdir build
cd build
cmake ..
make docs
```

## Ajuda

Você pode criar uma Issue ou contatar os mantenedores (autores)

## Autores

 * João Vitor Espig ([JotaEspig](https://github.com/JotaEspig))
 * Mickael Reichert ([mickaelrei](https://github.com/mickaelrei))
 * Gustavo Tramontin Pedro ([gustatramontin](https://github.com/gustatramontin))

## Historico de versões

veja [CHANGELOG.md](CHANGELOG.md)

## Licença

O projeto é licenciado sob a Licença MIT - veja o arquivo [LICENSE](LICENSE) para mais detalhes

## Agradecimentos

* [Learn OpenGL](https://github.com/JoeyDeVries/LearnOpenGL)
* [OpenGL course](https://www.youtube.com/watch?v=45MIykWJ-C4&ab_channel=freeCodeCamp.org) - Por freeCodeCamp
* [README-Template.md](https://gist.github.com/DomPizzie/7a5ff55ffa9081f2de27c315f5018afc)
