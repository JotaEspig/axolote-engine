#include <iostream>

#include <axolote/engine.hpp>

std::string my_get_path(const std::string &path) {
    return std::string(PROJECT_ROOT_FOLDER) + "/" + path;
}

class App : public axolote::Window {
public:
    void main_loop();
};

void App::main_loop() {
    auto post_processing_shader = axolote::gl::Shader::create(
        my_get_path(
            "./resources/shaders/post_processing_base_vertex_shader.glsl"
        ),
        my_get_path(
            "./resources/shaders/post_processing_base_fragment_shader.glsl"
        )
    );
    // You must set a scene for the engine to render it, otherwise it will give
    // you a segfault
    std::shared_ptr<axolote::Scene> scene{new axolote::Scene{}};
    // Initializes the renderer for the scene
    scene->renderer.init(width(), height());
    // Setup the shader used for post processing (see:
    // https://learnopengl.com/Advanced-OpenGL/Framebuffers), this base shader
    // does nothing related to post processing, just draws the texture into the
    // screen
    scene->renderer.setup_shader(post_processing_shader);
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

        // Swapping the buffers
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
