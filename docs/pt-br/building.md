## Compilação

Clone o repositório:
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

### Flags de compilação

 * `-DCMAKE_BUILD_TYPE=Release` para compilar o projeto em modo release. O padrão é `Release`. (Apenas para Linux)
 * `-DUSE_LOCAL_ASSIMP` para usar a biblioteca assimp local. O padrão é `OFF`. (Apenas para Linux)
 * `-DDEBUG` para habilitar o modo de depuração (É exibido no terminal a criação, exclusão, redimensionamento, etc de objetos OpenGL). O padrão é `ON`.
 * `-DBUILD_TESTS=ON` para compilar os testes. O padrão é `ON`.

Para definir as flags, você deve adicioná-las ao comando cmake. Por exemplo:
```bash
cmake -DDEBUG=OFF ..
```
