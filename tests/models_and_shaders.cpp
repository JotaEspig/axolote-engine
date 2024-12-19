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
    _root_path = PROJECT_ROOT_FOLDER;
    // Loads the default shaders
    auto shader = axolote::gl::Shader::create(
        get_path("resources/shaders/object3d_base_vertex_shader.glsl"),
        get_path("resources/shaders/object3d_base_fragment_shader.glsl")
    );

    auto saul_goodman = std::make_shared<axolote::Object3D>();
    saul_goodman->load_model(get_path("resources/models/saul-goodman/model.obj"));
    saul_goodman->set_matrix(
        glm::translate(glm::mat4{1.0f}, glm::vec3{0.0f, 0.0f, -2.0f})
    );
    saul_goodman->bind_shader(shader);

    // Creating a scene, configurating the camera and adding a drawable object
    std::shared_ptr<axolote::Scene> scene{new axolote::Scene{}};
    // Arbitrary value, you can change it for testing purposes
    scene->context->camera.sensitivity = 5000.0f;
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
    app.set_window_size(600, 600);
    app.set_color(0x01, 0x40, 0xff);
    app.main_loop();
    return 0;
}
