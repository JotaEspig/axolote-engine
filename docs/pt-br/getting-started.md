## Compilando seu projeto com o Axolote Engine

Primeiramente, você deve instalá-lo na pasta do seu projeto. Veja [install.md](install.md).

É recomendado usar CMake para compilar seu projeto com o Axolote Engine.
Você pode ver um arquivo CMakeLists.txt mínimo que você pode usar em [examples/CMakeLists.txt](../../examples/CMakeLists.txt).

## Abrindo uma janela

Para abrir uma janela, você deve criar uma classe que herda de `axolote::Window` e implementar o método `main_loop`.

Observe que estamos processando a entrada do teclado e do mouse.
Veja os métodos `poll_events` e `process_input`. `poll_events` é uma chamada obrigatória para trabalhar com entrada.
E `process_input` é a implementação padrão para processar a entrada do usuário. Usando essa implementação, você tem:

- W, A, S, D, Left Shift e Space -> Mover-se
- Segurando o botão direito do mouse e arrastando -> Movimento da câmera
- ESC -> Sair

```cpp
#include <iostream>

#include <axolote/engine.hpp>

class App : public axolote::Window {
public:
    void main_loop();
};

void App::main_loop() {
    // You must set a scene for the engine to render it, otherwise it will give
    // you a segfault
    std::shared_ptr<axolote::Scene> scene{new axolote::Scene{}};
    set_scene(scene);

    float delta_t = 1.0f / 60.0f;
    while (!should_close()) {
        // Polling events and processing input
        poll_events();
        process_input();

        // Updating the camera and the scene objects
        update_camera((float)width() / height());
        update(delta_t);

        // Clearing the screen and rendering the scene
        clear();
        render();

        // Swapping the buffers MUST BE CALLED, otherwise bye bye PC :)
        flush();
    }
}

int main() {
    std::cout << "Axolote Engine" << std::endl;
    App app{};
    app.set_title("Window");
    app.set_width(600);
    app.set_height(600);
    app.set_color(0x01, 0x40, 0xff);
    app.main_loop();
    return 0;
}
```

## Carregamento de modelos e Shaders

Neste exemplo, um shader e um modelo 3D são carregados (Better Caul Saul!).
Carregar um modelo é bastante simples, crie um objeto `Object3D`, chame `load_model` e vincule o shader.
Você pode ver mais sobre shaders em [https://learnopengl.com/Getting-started/Shaders](https://learnopengl.com/Getting-started/Shaders).
Com esses shaders padrão, você pode fazer quase todas as coisas simples, mas esteja ciente de que, às vezes, alguns modelos podem não funcionar corretamente.
Se você deseja fazer coisas mais avançadas, é aconselhável aprender sobre shaders.

```cpp
#include <iostream>
#include <memory>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <axolote/engine.hpp>

class App : public axolote::Window {
public:
    void main_loop();
};

void App::main_loop() {
    // Loads the default shaders
    auto shader = axolote::gl::Shader::create(
        "./resources/shaders/object3d_base_vertex_shader.glsl",
        "./resources/shaders/object3d_base_fragment_shader.glsl"
    );

    auto saul_goodman = std::make_shared<axolote::Object3D>();
    saul_goodman->load_model("./resources/models/saul-goodman/model.obj");
    saul_goodman->set_matrix(
        glm::translate(glm::mat4{1.0f}, glm::vec3{0.0f, 0.0f, -2.0f})
    );
    saul_goodman->bind_shader(shader);

    // Creating a scene, configurating the camera and adding a drawable object
    std::shared_ptr<axolote::Scene> scene{new axolote::Scene{}};
    // Arbitrary value, you can change it for testing purposes
    scene->camera.sensitivity = 5000.0f;
    scene->add_drawable(saul_goodman);

    // You must set a scene for the engine to render it, otherwise it will give
    // you a segfault :)
    set_scene(scene);

    float delta_t = 1.0f / 60.0f;
    while (!should_close()) {
        // Polling events and processing input.
        // Now you can move arround the scene with WASD and move the camera
        // holding the right button on the mouse and dragging it.
        poll_events();
        process_input(delta_t);

        // Updating the camera and the scene objects
        update_camera((float)width() / height());
        update(delta_t);

        // Clearing the screen and rendering the scene
        clear();
        render();

        // Swapping the buffers MUST BE CALLED, otherwise bye bye PC :)
        flush();
    }
}

int main() {
    std::cout << "Axolote Engine" << std::endl;
    App app{};
    app.set_title("Window");
    app.set_width(600);
    app.set_height(600);
    app.set_color(0x01, 0x40, 0xff);
    app.main_loop();
    return 0;
}
```

## Outros Exemplos

Você pode ver alguns exemplos na pasta [examples](../../examples/).
Você também pode executá-los:

Linux
```bash
./bin/window-test
./bin/models-and-shaders-test
./bin/main-test
```

Windows
```bash
./bin/window-test.exe
./bin/models-and-shaders-test.exe
./bin/main-test.exe
```

## Documentação

Se você tiver Doxygen, pode ler a documentação usando:
```bash
git clone https://github.com/JotaEspig/axolote-engine
cd axolote-engine
mkdir build
cd build
cmake ..
make docs
```
