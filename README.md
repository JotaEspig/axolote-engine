# Axolote Engine

Graphics engine made in C++ using OpenGL

## Description

Graphics engine made in C++ using OpenGL version 3.3+. The idea of the project came from the fact that I (João Vitor Espig) wanted to learn OpenGL at the start of 2023 and have some fun doing some games and simulations, and then I decided to create a small engine using OpenGL. One of my motivations for learning OpenGL came from Minecraft (it uses OpenGL to render its graphics) and from the curiosity that I had about how 3D games are made.

## Getting Started

### Dependencies

* CMake 2.8.5+
* OpenGL 3.3+
* GLFW3
* GLM
* Doxygen (Optional)

### Documentation

If you have Doxygen, you can read the documentation using:
```bash
git clone https://github.com/JotaEspig/axolote-engine
cd axolote-engine
cmake .
make docs
```

### Compiling

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

### Executing some tests

After compiling the project:
```bash
./tests/bin/tests
```

### Installation

see [install.md](install.md).

## Help

You can create an Issue or contact the mantainers (authors)

## Authors

 * João Vitor Espig ([JotaEspig](https://github.com/JotaEspig))
 * Mickael Reichert ([mickaelrei](https://github.com/mickaelrei))
 * Gustavo Tramontin Pedro ([gustatramontin](https://github.com/gustatramontin))

## Version History

see [CHANGELOG.md](CHANGELOG.md)

## License

This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details

## Acknowledgments

* [Learn OpenGL](https://github.com/JoeyDeVries/LearnOpenGL)
* [OpenGL course](https://www.youtube.com/watch?v=45MIykWJ-C4&ab_channel=freeCodeCamp.org) - By freeCodeCamp
* [README-Template.md](https://gist.github.com/DomPizzie/7a5ff55ffa9081f2de27c315f5018afc)

## TODO

See [TODO.md](TODO.md)
