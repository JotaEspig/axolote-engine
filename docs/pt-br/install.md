# INSTALAÇÃO

## Linux

Para instalar no seu projeto você pode usar o script `install.sh`
```bash
./install.sh <caminho-para-o-projeto>
```

Isso irá criar uma pasta chamada `external` e outra chamada `resources` e irá
armazenar os arquivos necessários lá.

E então, para compilar seu projeto, você deve linkar as bibliotecas e os arquivos
de cabeçalho corretamente. Veja o arquivo [CMakeLists.txt](../../examples/project_example/CMakeLists.txt)

## Windows

### Script

A instalação no Windows é um pouco mais complicada, pois o script `install_windows.ps1`
ainda não está totalmente funcional. Aviso: O script pode não funcionar e pode lançar
alguns erros, mas você pode tentar.

Para instalar no seu projeto você pode usar o script `install_windows.ps1`
```bash
powershell -ExecutionPolicy Bypass -File .\install_windows.ps1 <caminho-para-o-projeto>
```

Isso irá criar uma pasta chamada `external` e outra chamada `resources` e irá
armazenar os arquivos necessários lá.

E então, para compilar seu projeto, você deve linkar as bibliotecas e os arquivos
de cabeçalho corretamente. Veja o arquivo [CMakeLists.txt](../../examples/project_example/CMakeLists.txt)

### Manualmente

Para uma melhor compreensão, veja a pasta `examples/project_example`.

Depois de compilar o projeto, você deve copiar manualmente os arquivos de biblioteca
e os arquivos de cabeçalho para o seu projeto.

Assumindo que você tenha um diretório para o seu projeto chamado `project`, dentro dele
você deve criar uma pasta chamada `external` que tenha as subpastas `include` e `lib`.

Veja a estrutura abaixo para uma melhor compreensão:
```
projeto/
│
└── external/
    │
    ├── include/
    │
    └── lib/
```

Agora, você deve copiar a pasta chamada `axolote` dentro de `axolote-engine/include`
e as pastas `KHR` e `stb` dentro de `axolote-engine/external/include` para a pasta
`project/external/include`.

Então, você deve criar uma pasta chamada `axolote` dentro de `project/external/lib`.
Depois, você copia todos os arquivos dentro de `axolote-engine/build/Release` para
a pasta `project/external/lib/axolote`.

A estrutura do diretório do seu projeto deve parecer com isso:
```
projeto/
│
└── external/
    │
    ├── include/
    │   │
    │   ├── axolote/
    │   │   │
    │   │   └── ...
    │   ├── KHR/
    │   │   │
    │   │   └── ...
    │   └── stb/
    │       │
    │       └── ...
    │
    └── lib/
        │
        └── axolote/
            │
            ├── axolote.dll
            ├── axolote.lib
            ├── glfw3.dll
            └── ...
```

E então, para compilar seu projeto, você deve linkar as bibliotecas e os arquivos
de cabeçalho corretamente. Veja o arquivo [CMakeLists.txt](../../examples/project_example/CMakeLists.txt)
