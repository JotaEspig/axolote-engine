#include <iostream>
#include <memory>
#include <sstream>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/string_cast.hpp>
#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>

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
    bool use_mirror = true;
    std::shared_ptr<axolote::SpotLight> flashlight;
    std::shared_ptr<axolote::gl::Framebuffer> mirror_fbo;

    void process_input(double dt);
    void main_loop();
};

// custom resize framebuffer callback
void framebuffer_size_callback(GLFWwindow *window, int width, int height) {
    axolote::Window::default_framebuffer_size_callback(window, width, height);
    auto app = static_cast<App *>(glfwGetWindowUserPointer(window));
    // check if the app is not null
    if (app && app->mirror_fbo)
        app->mirror_fbo->resize(width, height);
}

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

    KeyState m_key_state = get_key_state(Key::M);
    if (m_key_state == KeyState::PRESSED && !is_key_pressed(Key::M)) {
        set_key_pressed(Key::M, true);
    }
    else if (m_key_state == KeyState::RELEASED && is_key_pressed(Key::M)) {
        use_mirror = !use_mirror;
        set_key_pressed(Key::M, false);
    }

    // Test camera get_ray
    if (get_mouse_key_state(MouseKey::LEFT) == MouseKeyState::PRESSED) {
        double mx, my;
        get_cursor_position(&mx, &my);
        glm::vec3 ray
            = current_scene()->camera.get_ray(mx, my, width(), height());
        std::cout << "Ray: " << glm::to_string(ray) << std::endl;
    }
}

void App::main_loop() {
    // Set the window user pointer to this object
    glfwSetWindowUserPointer(window(), this);
    // Set root path using definition from CMake
    _root_path = PROJECT_ROOT_FOLDER;

    set_color(0xff, 0xff, 0xff);
    std::string original_title = title();

    auto shader_program = axolote::gl::Shader::create(
        get_path("resources/shaders/object3d_base_vertex_shader.glsl"),
        get_path("./resources/shaders/object3d_base_fragment_shader.glsl")
    );
    auto gmesh_shader = axolote::gl::Shader::create(
        get_path("/resources/shaders/gmesh_base_vertex_shader.glsl"),
        get_path("/resources/shaders/gmesh_base_fragment_shader.glsl")
    );
    auto grid_shader = axolote::gl::Shader::create(
        get_path("/resources/shaders/grid_base_vertex_shader.glsl"),
        get_path("/resources/shaders/grid_base_fragment_shader.glsl")
    );
    auto screen_shader = axolote::gl::Shader::create(
        get_path("/resources/shaders/gmesh_base_vertex_shader.glsl"),
        get_path("/tests/shaders/screen_frag.glsl")
    );

    // Scene object
    std::shared_ptr<axolote::Scene> scene{new axolote::Scene{}};
    scene->camera.pos = {0.0f, 0.0f, 12.35f};
    scene->camera.speed = 3.0f;
    scene->camera.sensitivity = 10000.0f;
    scene->ambient_light_intensity = 0.15f;

    auto dir_light = std::make_shared<MyDirLight>(
        glm::vec3{1.f, 1.f, 1.f}, true, glm::vec3{1.0f, 0.0f, 0.0f}
    );
    dir_light->intensity = 0.9f;
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
        get_path("resources/models/sphere/sphere.obj"),
        glm::vec4{0.0f, 0.0f, 1.0f, 0.6f},
        glm::scale(glm::mat4{1.0f}, 6.0f * glm::vec3{1.0f, 1.0f, 1.0f})
    );
    earth->name = "earth";
    earth->is_transparent = true;
    earth->bind_shader(shader_program);
    scene->add_sorted_drawable(earth);

    auto moon = std::make_shared<axolote::Object3D>(
        get_path("resources/models/sphere/sphere.obj"),
        glm::vec4{0.8f, 0.8f, 0.8f, 1.0f},
        glm::translate(glm::mat4{1.0f}, glm::vec3{15.f, 2.f, 0.f})
    );
    moon->bind_shader(shader_program);
    scene->add_drawable(moon);

    auto m26 = std::make_shared<axolote::Object3D>(
        get_path("resources/models/m26/m26pershing_coh.obj"), glm::vec4{1.0f},
        glm::translate(glm::mat4{1.0f}, glm::vec3{0.f, -10.f, 0.f})
    );
    m26->name = "m26";
    m26->is_transparent = true;
    m26->bind_shader(shader_program);
    scene->add_sorted_drawable(m26);

    auto line = std::make_shared<axolote::utils::Line>(
        glm::vec3{10.0f, 10.0f, 0.0f}, glm::vec3{1.0f, 1.0f, 1.0f}, 5.0f, 1.0f,
        glm::vec4{0.0f, 1.0f, 0.0f, 1.0f}
    );
    line->is_affected_by_lights = true;
    line->bind_shader(shader_program);
    scene->add_drawable(line);

    auto grid = std::make_shared<axolote::utils::Grid>(
        70, 5, true, glm::vec4{1.0f, 0.f, 0.f, 1.0f}
    );
    grid->fading_factor = 70.0f;
    grid->bind_shader(grid_shader);
    scene->set_grid(grid);

    std::vector<axolote::Vertex> quad_vec{
        {{-1.0f, 1.0f, 0.0f}, {}, {1.0f, 1.0f}, {}},
        {{-1.0f, -1.0f, 0.0f}, {}, {1.0f, 0.0f}, {}},
        {{1.0f, -1.0f, 0.0f}, {}, {0.0f, 0.0f}, {}},
        {{1.0f, 1.0f, 0.0f}, {}, {0.0f, 1.0f}, {}}
    };
    std::vector<axolote::Vertex> eder_quad_vec{
        {{-1.0f, 1.0f, 0.0f}, {1.0f, 0.0f, 0.0f, 1.0f}, {0.0f, 1.0f}, {}},
        {{-1.0f, -1.0f, 0.0f}, {1.0f, 0.0f, 0.0f, 1.0f}, {0.0f, 0.0f}, {}},
        {{1.0f, -1.0f, 0.0f}, {1.0f, 0.0f, 0.0f, 1.0f}, {1.0f, 0.0f}, {}},
        {{1.0f, 1.0f, 0.0f}, {1.0f, 0.0f, 0.0f, 1.0f}, {1.0f, 1.0f}, {}}
    };
    std::vector<GLuint> quad_indices{0, 1, 2, 0, 2, 3};
    glm::vec3 quad_normal = glm::vec3{0.0f, 0.0f, 1.0f};

    // Funny things with fbo
    mirror_fbo = axolote::gl::Framebuffer::create();
    mirror_fbo->init(width(), height());
    // Overwrite the default framebuffer size callback
    glfwSetFramebufferSizeCallback(window(), framebuffer_size_callback);

    // TODO: check how to use the textute correctly when resizing the window
    auto quad = std::make_shared<axolote::Object3D>(
        quad_vec, quad_indices,
        std::vector<std::shared_ptr<axolote::gl::Texture>>{mirror_fbo->texture()
        },
        glm::mat4{1.0f}
    );
    quad->bind_shader(screen_shader);

    auto eder_tex = axolote::gl::Texture::create(
        get_path("resources/textures/eder.jpg"), "diffuse", (GLuint)0
    );
    auto eder_quad = std::make_shared<axolote::GMesh>(
        eder_quad_vec, quad_indices,
        std::vector<std::shared_ptr<axolote::gl::Texture>>{eder_tex}
    );
    eder_quad->bind_shader(gmesh_shader);

    std::cout << "Starting main loop" << std::endl;

    set_scene(scene);
    double before = get_time();
    while (!should_close()) {
        poll_events();

        double now = get_time();
        double dt = now - before;
        before = now;
        if (!_io->WantCaptureMouse) {
            process_input(dt);
        }

        std::stringstream sstr;
        sstr << original_title << " | " << (int)(1 / dt) << " fps";
        set_title(sstr.str());

        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        dt *= DT_MULTIPLIER;
        auto camera = current_scene()->camera;
        if (use_mirror) {
            glm::vec3 normal
                = glm::mat3{quad->get_normal_matrix()} * quad_normal;
            glm::vec3 pos = quad->get_matrix()[3];
            glm::mat4 reflection_matrix{1.0f};
            float A = normal.x;
            float B = normal.y;
            float C = normal.z;
            reflection_matrix[0][0] = 1 - 2 * A * A;
            reflection_matrix[0][1] = -2 * A * B;
            reflection_matrix[0][2] = -2 * A * C;

            reflection_matrix[1][0] = -2 * A * B;
            reflection_matrix[1][1] = 1 - 2 * B * B;
            reflection_matrix[1][2] = -2 * B * C;

            reflection_matrix[2][0] = -2 * A * C;
            reflection_matrix[2][1] = -2 * B * C;
            reflection_matrix[2][2] = 1 - 2 * C * C;
            glm::vec3 reflection
                = reflection_matrix
                  * glm::vec4{pos - current_scene()->camera.pos, 1.0f};

            // first pass
            // Setting the camera to the mirror position and orientation
            current_scene()->camera.pos = pos;
            current_scene()->camera.orientation = reflection;
            current_scene()->camera.up = glm::vec3{0.0f, 1.0f, 0.0f};
            update_camera(1.0f);

            mirror_fbo->bind();
            clear();
            render();

            // second pass
            mirror_fbo->unbind();
        }

        clear();
        // restore original camera
        current_scene()->camera = camera;
        glm::mat4 view = glm::lookAt(
            camera.pos, camera.pos + camera.orientation, camera.up
        );
        glm::mat4 projection = glm::perspective(
            glm::radians(camera.fov), (float)width() / height(),
            camera.min_dist, camera.max_dist
        );

        auto shaders = quad->get_shaders();
        for (auto &s : shaders) {
            s->activate();
            s->set_uniform_float3(
                "axolote_camera_pos", camera.pos.x, camera.pos.y, camera.pos.z
            );
            s->set_uniform_matrix4("axolote_projection", projection);
            s->set_uniform_matrix4("axolote_view", view);
        }

        glm::mat4 model = glm::mat4{1.0f};
        // make the model orbit around the the center using radius 10
        model = glm::rotate(
            model, (float)get_time() * 0.1f, glm::vec3{0.0f, 1.0f, 0.0f}
        );
        model = glm::translate(model, glm::vec3{10.0f, 0.0f, 0.0f});
        // rotate so it points to the center
        model = glm::rotate(
            model, glm::radians(-90.0f), glm::vec3{0.0f, 1.0f, 0.0f}
        );
        glDisable(GL_CULL_FACE);
        quad->set_matrix(model);
        quad->draw();

        shaders = eder_quad->get_shaders();
        for (auto &s : shaders) {
            s->activate();
            s->set_uniform_float3(
                "axolote_camera_pos", camera.pos.x, camera.pos.y, camera.pos.z
            );
            s->set_uniform_matrix4("axolote_projection", projection);
            s->set_uniform_matrix4("axolote_view", view);
        }

        model = glm::translate(model, glm::vec3{0.0f, 0.0f, -0.01f});
        model = glm::scale(model, glm::vec3{1.1f, 1.1f, 1.1f});
        eder_quad->draw(model);
        glEnable(GL_CULL_FACE);

        // Flashlight
        spot_light->pos = current_scene()->camera.pos;
        spot_light->dir = current_scene()->camera.orientation;

        update_camera((float)width() / height());
        update(dt);
        render();

        ImGui::Begin("Tests using ImGui");
        ImGui::Text("Press 'V' to toggle vsync");
        ImGui::Text("Press 'L' to toggle flashlight");
        ImGui::Text("Press 'M' to toggle mirror");
        ImGui::End();

        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        flush();
    }
}

int main() {
    std::cout << "Axolote Engine" << std::endl;
    App app{};
    app.set_title("Main test");
    app.set_maximized();
    app.main_loop();
    return 0;
}
