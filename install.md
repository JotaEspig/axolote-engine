# INSTALLATION

## Linux

To install it in your project you can use the `install.sh` script
```bash
./install.sh <path-to-project>
```

It will create a folder called ´external´ and it will store the needed files there

And then, for compiling your project, you should link the libraries and header files correctly. See the
[CMakeLists.txt](examples/project_example/CMakeLists.txt) file in the `examples/project_example`
directory.

## Windows

For a better understanding, see the folder `examples/project_example`.

After compiling the project, you must manually copy the library files and the
headers files to your project.

Assuming you have a directory for your project called `project`, inside it you
should create a folder called `external` that has the subfolders `include` and `lib`.

See the structure below for a better understanding:
```
project/
│
└── external/
    │
    ├── include/
    │
    └── lib/
```

Then, you should copy the folder called `axolote` inside `axolote-engine/include`
and the folders `KHR` and `stb` inside `axolote-engine/external/include` to the
`project/external/include` folder.

Now you create a folder called `axolote` inside `project/external/lib` inside.
Then, you copy all the files inside
`axolote-engine/build/Release` to the `project/external/lib/axolote` folder.

Your project directory structure should look like this:
```
project/
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

And then, for compiling your project, you should link the libraries and header files correctly. See the
[CMakeLists.txt](examples/project_example/CMakeLists.txt) file in the `examples/project_example`
directory.
