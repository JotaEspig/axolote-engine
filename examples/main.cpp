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

class MyDirLight : public axolote::DirectionalLight {
public:
    float absolute_time = 0.0;

    MyDirLight(const glm::vec3 &color, bool is_set, const glm::vec3 &dir) :
      axolote::DirectionalLight{color, is_set, dir} {
    }

    void update(double dt) override {
        absolute_time += dt / (DT_MULTIPLIER * 10);
        dir = glm::vec3{
            glm::cos((float)absolute_time), 0.0f, glm::sin((float)absolute_time)
        };
    }
};

class App : public axolote::Window {
public:
    std::shared_ptr<axolote::SpotLight> flashlight;

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

    KeyState l_key_state = get_key_state(Key::L);
    if (l_key_state == KeyState::PRESSED && !is_key_pressed(Key::L)) {
        set_key_pressed(Key::L, true);
    }
    else if (l_key_state == KeyState::RELEASED && is_key_pressed(Key::L)) {
        flashlight->is_set = !flashlight->is_set;
        set_key_pressed(Key::L, false);
    }
}

void App::main_loop() {
    set_color(0xff, 0xff, 0xff);
    std::string original_title = title();

    auto shader_program = axolote::gl::Shader::create(
        "./resources/shaders/object3d_base_vertex_shader.glsl",
        "./resources/shaders/object3d_base_fragment_shader.glsl"
    );
    auto grid_shader = axolote::gl::Shader::create(
        "./resources/shaders/grid_base_vertex_shader.glsl",
        "./resources/shaders/grid_base_fragment_shader.glsl"
    );

    // Scene object
    std::shared_ptr<axolote::Scene> scene{new axolote::Scene{}};
    scene->camera.pos = {0.0f, 0.0f, 3.0f};
    scene->camera.speed = 3.0f;
    scene->camera.sensitivity = 10000.0f;

    auto dir_light = std::make_shared<MyDirLight>(
        glm::vec3{1.f, 1.f, 1.f}, true, glm::vec3{1.0f, 0.0f, 0.0f}
    );
    scene->add_light(dir_light);

    auto spot_light = std::make_shared<axolote::SpotLight>(
        glm::vec3{1.0f}, true, glm::vec3{0.0f, 5.0f, 0.0f},
        glm::vec3{0.0f, -1.0f, 0.0f}, glm::cos(glm::radians(12.5f)),
        glm::cos(glm::radians(20.0f))
    );
    spot_light->linear = 0.09f;
    spot_light->quadratic = 0.032f;
    scene->add_light(spot_light);
    App::flashlight = spot_light;

    auto earth = std::make_shared<axolote::Object3D>(
        "./resources/models/sphere/sphere.obj",
        glm::vec4{0.0f, 0.0f, 1.0f, 0.6f},
        glm::scale(glm::mat4{1.0f}, 6.0f * glm::vec3{1.0f, 1.0f, 1.0f})
    );
    earth->bind_shader(shader_program);
    scene->add_sorted_drawable(earth);

    auto moon = std::make_shared<axolote::Object3D>(
        "./resources/models/sphere/sphere.obj",
        glm::vec4{0.9f, 0.9f, 0.9f, 1.0f},
        glm::translate(glm::mat4{1.0f}, glm::vec3{15.f, 2.f, 0.f})
    );
    moon->bind_shader(shader_program);
    scene->add_drawable(moon);

    auto m26 = std::make_shared<axolote::Object3D>(
        "./resources/models/m26/m26pershing_coh.obj", glm::vec4{1.0f},
        glm::translate(glm::mat4{1.0f}, glm::vec3{0.f, -7.f, 0.f})
    );
    m26->is_transparent = true;
    m26->bind_shader(shader_program);
    scene->add_sorted_drawable(m26);

    auto line = std::make_shared<axolote::utils::Line>(
        glm::vec3{10.0f, 10.0f, 0.0f}, glm::vec3{1.0f, 1.0f, 1.0f}, 5.0f, 1.0f,
        glm::vec4{0.0f, 1.0f, 0.0f, 1.0f}, 5
    );
    line->bind_shader(shader_program);
    scene->add_drawable(line);

    auto grid = std::make_shared<axolote::utils::Grid>(
        70, 5, true, glm::vec4{1.0f, 0.f, 0.f, 1.0f}
    );
    grid->fading_factor = 70.0f;
    grid->bind_shader(grid_shader);
    scene->set_grid(grid);

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

        // Flashlight
        spot_light->pos = current_scene()->camera.pos;
        spot_light->dir = current_scene()->camera.orientation;

        update_camera((float)width() / height());
        update(dt);
        render();

        grid->camera_pos = current_scene()->camera.pos;

        flush();
    }
}

int main() {
    std::cout << "Axolote Engine" << std::endl;
    App app{};
    app.set_title("Main test");
    app.set_window_size(600, 600);
    app.main_loop();
    return 0;
}
