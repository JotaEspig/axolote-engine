#include <iostream>
#include <memory>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <axolote/engine.hpp>

std::string my_get_path(const std::string &path) {
    return std::string(PROJECT_ROOT_FOLDER) + "/" + path;
}

class App : public axolote::Window {
public:
    void main_loop();
};

void App::main_loop() {
    // Loads the default shaders
    auto shader = axolote::gl::Shader::create(
        my_get_path("resources/shaders/object3d_base_vertex_shader.glsl"),
        my_get_path("resources/shaders/object3d_base_fragment_shader.glsl")
    );
    auto post_processing_shader = axolote::gl::Shader::create(
        my_get_path("resources/shaders/post_processing_base_vertex_shader.glsl"
        ),
        my_get_path(
            "resources/shaders/post_processing_base_fragment_shader.glsl"
        )
    );

    auto saul_goodman = std::make_shared<axolote::Object3D>();
    saul_goodman->load_model(
        my_get_path("resources/models/saul-goodman/model.obj")
    );
    saul_goodman->set_matrix(
        glm::translate(glm::mat4{1.0f}, glm::vec3{0.0f, 0.0f, -2.0f})
    );
    saul_goodman->bind_shader(shader);

    // Creating a scene, configurating the camera and adding a drawable object
    std::shared_ptr<axolote::Scene> scene{new axolote::Scene{}};
    // Initializes the renderer for the scene
    scene->renderer.init(width(), height());
    // Setup the shader used for post processing (see:
    // https://learnopengl.com/Advanced-OpenGL/Framebuffers), this base shader
    // does nothing related to post processing, just draws the texture into the
    // screen
    scene->renderer.setup_shader(post_processing_shader);
    // Arbitrary value, you can change it for testing purposes
    // The context variable stores the camera and objects to be drawn
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

        // Swapping the buffers MUST BE CALLED
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
