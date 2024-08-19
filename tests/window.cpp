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
