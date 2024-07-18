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
    scene->camera.pos = {0.0f, 0.0f, 3.0f};
    scene->camera.speed = 3.0f;
    scene->camera.sensitivity = 10000.0f;

    float s = 20.0f;
    std::shared_ptr<axolote::PointLight> point_light{new axolote::PointLight{
        glm::vec3{1.0f, 1.0f, 0.0f}, true,
        glm::vec3{0.0f, 0.0f, s}, 1.0f
    }};
    scene->add_light(point_light);

    std::shared_ptr<axolote::PointLight> point_light1{new axolote::PointLight{
        glm::vec3{1.0f, 0.5f, 0.0f}, true,
        glm::vec3{0.0f, 0.0f, -s}, 1.0f
    }};
    scene->add_light(point_light1);

    std::shared_ptr<axolote::PointLight> point_light2{new axolote::PointLight{
        glm::vec3{0.0f, 0.5f, 1.0f}, true,
        glm::vec3{s, 0.0f, 0.0f}, 1.0f
    }};
    scene->add_light(point_light2);

    std::shared_ptr<axolote::PointLight> point_light3{new axolote::PointLight{
        glm::vec3{0.0f, 1.0f, 0.5f}, true,
        glm::vec3{-s, 0.0f, 0.0f}, 1.0f
    }};
    scene->add_light(point_light3);

    std::shared_ptr<axolote::PointLight> point_light4{new axolote::PointLight{
        glm::vec3{0.5f, 0.0f, 1.0f}, true,
        glm::vec3{0.0f, s, 0.0f}, 1.0f
    }};
    scene->add_light(point_light4);

    std::shared_ptr<axolote::PointLight> point_light5{new axolote::PointLight{
        glm::vec3{1.0f, 0.0f, 0.5f}, true,
        glm::vec3{0.0f, -s, 0.0f}, 1.0f
    }};
    scene->add_light(point_light5);

    auto sphere = std::make_shared<axolote::Object3D>(
        "./resources/models/sphere/sphere.obj", glm::vec3{1.0f, 1.0f, 1.0f},
        glm::translate(glm::mat4{1.0f}, glm::vec3{0.f, 0.f, 0.f})
    );
    sphere->bind_shader(shader_program);
    scene->add_drawable(sphere);

    auto m26 = std::make_shared<axolote::Object3D>(
        "./resources/models/m26/m26pershing_coh.obj", glm::vec3{1.0f, 1.0f, 1.0f},
        glm::translate(glm::mat4{1.0f}, glm::vec3{0.f, 0.f, 0.f})
    );
    m26->bind_shader(shader_program);
    scene->add_drawable(m26);

    // xyz-axis line
    std::shared_ptr<axolote::Line> l_xyz{new axolote::Line{
        {0.0f, 0.0f, 0.0f}, {1.0f, 1.0f, 1.0f}, 20.0f, 01.1f, {1.0f, 1.0f, 1.0f}
    }};
    l_xyz->bind_shader(shader_program);
    scene->add_drawable(l_xyz);

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

        m26->set_matrix(glm::rotate(
            glm::translate(glm::mat4{1.0f}, glm::vec3{0.0f, 2.5f, 0.0f}),
            (float)now, glm::vec3{0.0f, 1.0f, 0.0f}
        ));

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
