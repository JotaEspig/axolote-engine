# INSTALLATION

Clone the repository:
```bash
git clone https://github.com/JotaEspig/axolote-engine
cd axolote-engine
```
Compile the project:
```bash
cmake .
make -j4
```
Now you should copy the .so file from `lib/` and header files from `include/` to your project folder. Assuming that you have a folder called `external` (or something similar) in your project folder, you should do this:
```bash
mkdir <your-project-dir>/external/include -p
mkdir <your-project-dir>/external/lib -p
cp -r include/axolote <your-project-dir>/external/include/axolote
cp lib/* <your-project-dir>/external/lib/
```

And then, when compiling your project, you should link them cerrectly

See an example: [solar system 3D](https://github.com/JotaEspig/solar-system-3d).
