#include <iostream>
#include <memory>
#include <sstream>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/string_cast.hpp>

#include <axolote/engine.hpp>

#define DT_MULTIPLIER 200000

class App : public axolote::Window {
public:
    void process_input(double dt);
    void main_loop();
};

void App::process_input(double dt) {
    axolote::Window::process_input(dt);

    KeyState v_key_state = get_key_state(Key::V);
    if (v_key_state == KeyState::PRESSED && !is_key_pressed(Key::V)) {
        set_key_pressed(Key::V, true);
    }
    else if (v_key_state == KeyState::RELEASED && is_key_pressed(Key::V)) {
        set_vsync(!vsync());
        set_key_pressed(Key::V, false);
    }
}

void App::main_loop() {
    std::string original_title = title();

    axolote::gl::Shader shader_program(
        "./resources/shaders/def_vertex_shader.glsl",
        "./resources/shaders/def_fragment_shader.glsl"
    );

    // Scene object
    std::shared_ptr<axolote::Scene> scene{new axolote::Scene{}};
    scene->camera.pos = {0.0f, 0.0f, 1.0f};
    scene->camera.speed = 1.0f;
    scene->camera.sensitivity = 10000.0f;

    auto saul = std::make_shared<axolote::Object3D>();
    saul->load_model("./resources/models/saul-goodman/model.obj");
    saul->model_mat
        = glm::translate(glm::mat4{1.0f}, glm::vec3{-2.0f, 0.0f, 0.0f});
    saul->bind_shader(shader_program);
    scene->add_drawable(saul);

    // x-axis line
    std::shared_ptr<axolote::Line> l_x{new axolote::Line{
        {0.0f, 0.0f, 0.0f}, {1.0f, 0.0f, 0.0f}, 1.0f, 0.01f, {1.0f, 0.0f, 0.0f}
    }};
    l_x->bind_shader(shader_program);
    scene->add_drawable(l_x);

    // y-axis line
    std::shared_ptr<axolote::Line> l_y{new axolote::Line{
        {0.0f, 0.0f, 0.0f}, {0.0f, 1.0f, 0.0f}, 1.0f, 0.01f, {0.0f, 1.0f, 0.0f}
    }};
    l_y->bind_shader(shader_program);
    scene->add_drawable(l_y);

    // z-axis line
    std::shared_ptr<axolote::Line> l_z{new axolote::Line{
        {0.0f, 0.0f, 0.0f}, {0.0f, 0.0f, 1.0f}, 1.0f, 0.01f, {0.0f, 0.0f, 1.0f}
    }};
    l_z->bind_shader(shader_program);
    scene->add_drawable(l_z);

    // xy-axis line
    std::shared_ptr<axolote::Line> l_xy{new axolote::Line{
        {0.0f, 0.0f, 0.0f}, {1.0f, 1.0f, 0.0f}, 0.3f, 0.01f, {1.0f, 1.0f, 0.0f}
    }};
    l_xy->bind_shader(shader_program);
    scene->add_drawable(l_xy);

    // xz-axis line
    std::shared_ptr<axolote::Line> l_xz{new axolote::Line{
        {0.0f, 0.0f, 0.0f}, {1.0f, 0.0f, 1.0f}, 0.3f, 0.01f, {1.0f, 0.0f, 1.0f}
    }};
    l_xz->bind_shader(shader_program);
    scene->add_drawable(l_xz);

    // yz-axis line
    std::shared_ptr<axolote::Line> l_yz{new axolote::Line{
        {0.0f, 0.0f, 0.0f}, {0.0f, 1.0f, 1.0f}, 0.3f, 0.01f, {0.0f, 1.0f, 1.0f}
    }};
    l_yz->bind_shader(shader_program);
    scene->add_drawable(l_yz);

    // xyz-axis line
    std::shared_ptr<axolote::Line> l_xyz{new axolote::Line{
        {0.0f, 0.0f, 0.0f}, {1.0f, 1.0f, 1.0f}, 0.3f, 0.01f, {1.0f, 1.0f, 1.0f}
    }};
    l_xyz->bind_shader(shader_program);
    scene->add_drawable(l_xyz);

    std::shared_ptr<axolote::Line> l_test{new axolote::Line{
        {-0.4f, 0.0f, 0.0f}, {1.0f, 0.0f, 1.0f}, 0.3f, 0.01f, {1.0f, 0.5f, 0.0f}
    }};
    l_test->bind_shader(shader_program);
    scene->add_drawable(l_test);

    auto sphere = std::make_shared<axolote::Object3D>(
        "./resources/models/sphere/sphere.obj", glm::vec3{1.0f, 1.0f, 1.0f},
        glm::mat4{1.0f}
    );
    sphere->bind_shader(shader_program);
    scene->add_drawable(sphere);

    set_scene(scene);
    double before = get_time();
    while (!should_close()) {
        clear();

        poll_events();

        double now = get_time();
        double dt = now - before;
        before = now;
        process_input(dt);

        std::stringstream sstr;
        sstr << original_title << " | " << (int)(1 / dt) << " fps";
        set_title(sstr.str());

        dt *= DT_MULTIPLIER;

        l_xyz->set_end(glm::vec3{
            std::cos((float)now) * .2f, std::sin((float)now) * .3f,
            std::cos((float)now * 0.2f) * .15f
        });

        update_camera((float)width() / height());
        update(dt);
        render();

        flush();
    }
}

int main() {
    std::cout << "Axolote Engine" << std::endl;
    App app{};
    app.set_title("Uepa");
    app.set_width(600);
    app.set_height(600);
    app.set_color(0x10, 0x10, 0x10);
    app.main_loop();
    return 0;
}