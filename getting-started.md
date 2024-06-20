## Compiling your project with Axolote Engine

First of all you must install it at your project folder. See [install.md](install.md).

It's recommended to use CMake to compile your project with Axolote Engine.
You can see a minimal CMakeLists.txt file that you can use at [examples/CMakeLists.txt](examples/CMakeLists.txt).

## Opening a window

To open a window you must create a class that inherits from `axolote::Window` and implement the `main_loop` method.

```cpp
#include <iostream>

#include <axolote/engine.hpp>

class App : public axolote::Window {
public:
    void main_loop();
};

void App::main_loop() {
    // You must set a scene for the engine renders, otherwise it will give you a
    // segfault
    std::shared_ptr<axolote::Scene> scene{new axolote::Scene{}};
    set_scene(scene);

    float delta_t = 1.0f / 60.0f;
    while (!should_close()) {
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

## Model loading and Shaders

In this example, A shader and a 3D model is loaded (Better Caul Saul!).
To load a model it's quite easy, create a object3D object, call `load_model` and bind the shader.
You can see more about shaders at [https://learnopengl.com/Getting-started/Shaders](https://learnopengl.com/Getting-started/Shaders).
With this default shaders you can do almost all the simple things, but please be aware that sometimes, some models can break.
If want to do more advanced things it's advised to learn about shaders.

Please take note that we are processing input from the keyboard and mouse.
Look at the `poll_events` and `process_input` methods. `poll_events` it's a must call to work with input.
And `process_input` it's the default implementation to process user input, using this implementation you have:
 - W, A, S, D, Left Shift and Space -> Move around
 - Holding mouse right button and dragging it -> Camera movement
 - ESC -> Quit

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
    axolote::gl::Shader shader{
        "./resources/shaders/def_vertex_shader.glsl",
        "./resources/shaders/def_fragment_shader.glsl"
    };

    auto saul_goodman = std::make_shared<axolote::Object3D>();
    saul_goodman->load_model("./resources/models/saul-goodman/model.obj");
    saul_goodman->model_mat
        = glm::translate(glm::mat4{1.0f}, glm::vec3{0.0f, 0.0f, -2.0f});
    saul_goodman->bind_shader(shader);

    // Creating a scene, configurating the camera and adding a drawable object
    std::shared_ptr<axolote::Scene> scene{new axolote::Scene{}};
    // Arbitrary value, you can change it for testing purposes
    scene->camera.sensitivity = 5000.0f;
    scene->add_drawable(saul_goodman);

    // You must set a scene for the engine renders, otherwise it will give you a
    // segfault :)
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

## Other Examples

You can see some examples in the [examples](examples) folder.
You can run it as well:
```bash
./bin/window-test
./bin/models-and-shaders-test
./bin/main-test
```

## Documentation

If you have Doxygen, you can read the documentation using:
```bash
git clone https://github.com/JotaEspig/axolote-engine
cd axolote-engine
cmake .
make docs
```
