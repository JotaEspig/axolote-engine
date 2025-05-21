#include <iostream>
#include <memory>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/norm.hpp>
#include <glm/gtx/string_cast.hpp>
#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>

#include <axolote/engine.hpp>

std::string myget_path(const std::string &path) {
    return std::string(PROJECT_ROOT_FOLDER) + "/" + path;
}

class MirrorDrawable : public axolote::Drawable {
public:
    double absolute_time = 0.0;
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
    std::shared_ptr<axolote::gl::Texture> eder_tex;
    std::shared_ptr<axolote::Object3D> quad;
    std::shared_ptr<axolote::GMesh> eder_quad;
    std::shared_ptr<axolote::gl::Shader> screen_shader
        = axolote::gl::Shader::create(
            myget_path("/resources/shaders/gmesh_base_vertex_shader.glsl"),
            myget_path("/tests/shaders/screen_frag.glsl")
        );
    std::shared_ptr<axolote::gl::Shader> gmesh_shader
        = axolote::gl::Shader::create(
            myget_path("/resources/shaders/gmesh_base_vertex_shader.glsl"),
            myget_path("/resources/shaders/gmesh_base_fragment_shader.glsl")
        );

    MirrorDrawable();

    void init(std::shared_ptr<axolote::gl::Framebuffer> fbo);
    void bind_shader(std::shared_ptr<axolote::gl::Shader> shader) override;
    std::vector<std::shared_ptr<axolote::gl::Shader>>
    get_shaders() const override;
    void update(double absolute_time, double delta_time) override;
    void draw() override;
    void draw(const glm::mat4 &mat) override;
};

MirrorDrawable::MirrorDrawable() {
}

void MirrorDrawable::init(std::shared_ptr<axolote::gl::Framebuffer> fbo) {
    quad = std::make_shared<axolote::Object3D>(
        quad_vec, quad_indices,
        std::vector<std::shared_ptr<axolote::gl::Texture>>{fbo->texture()},
        glm::mat4{1.0f}
    );
    quad->bind_shader(screen_shader);

    eder_tex = axolote::gl::Texture::create(
        myget_path("resources/textures/eder.jpg"), "diffuse", (GLuint)0
    );
    eder_quad = std::make_shared<axolote::GMesh>(
        eder_quad_vec, quad_indices,
        std::vector<std::shared_ptr<axolote::gl::Texture>>{eder_tex}
    );
    eder_quad->bind_shader(gmesh_shader);
}

void MirrorDrawable::bind_shader(std::shared_ptr<axolote::gl::Shader> shader) {
    quad->bind_shader(shader);
    eder_quad->bind_shader(shader);
}

std::vector<std::shared_ptr<axolote::gl::Shader>>
MirrorDrawable::get_shaders() const {
    return {screen_shader, gmesh_shader};
}

void MirrorDrawable::update(double absolute_time, double delta_time) {
    (void)absolute_time;

    MirrorDrawable::absolute_time += delta_time;
    if (absolute_time > M_PI * 2.0) {
        absolute_time -= M_PI * 2.0;
    }
}

void MirrorDrawable::draw() {
    glm::mat4 model = glm::mat4{1.0f};
    // make the model orbit around the the center using radius 10
    model = glm::rotate(
        model, (float)absolute_time * 0.1f, glm::vec3{0.0f, 1.0f, 0.0f}
    );
    model = glm::translate(model, glm::vec3{10.0f, 0.0f, 0.0f});
    // rotate so it points to the center
    model
        = glm::rotate(model, glm::radians(-90.0f), glm::vec3{0.0f, 1.0f, 0.0f});
    glDisable(GL_CULL_FACE);
    quad->set_matrix(model);
    quad->draw();

    model = glm::translate(model, glm::vec3{0.0f, 0.0f, -0.01f});
    model = glm::scale(model, glm::vec3{1.1f, 1.1f, 1.1f});
    eder_quad->draw(model);
    glEnable(GL_CULL_FACE);
}

void MirrorDrawable::draw(const glm::mat4 &mat) {
    (void)mat;
    draw();
}

class Mirror : public axolote::CameraRenderer {
public:
    bool should_render = true;
    std::shared_ptr<MirrorDrawable> mirror_drawable
        = std::make_shared<MirrorDrawable>();

    Mirror(double width, double height);

    void update(double absolute_time, double delta_time) override;
};

Mirror::Mirror(double width, double height) {
    fbo = axolote::gl::Framebuffer::create();
    fbo->init(width, height);
    mirror_drawable->init(fbo);
}

void Mirror::update(double absolute_time, double delta_time) {
    auto camera_original = scene_context->camera;
    glm::vec3 mirror_pos = mirror_drawable->quad->get_matrix()[3];
    glm::vec3 mirror_normal = glm::normalize(
        glm::mat3{mirror_drawable->quad->get_normal_matrix()}
        * mirror_drawable->quad_normal
    );
    glm::vec3 vec_camera_mirror_pos
        = glm::normalize(mirror_pos - scene_context->camera.get_pos());
    bool mirror_dir_comes_towards_camera
        = glm::length2(vec_camera_mirror_pos + mirror_normal)
          <= 2.0; // Pitagoras :) MATH IS SICK

    if (should_render && mirror_dir_comes_towards_camera) {
        glm::mat4 reflection_matrix{1.0f};
        float A = mirror_normal.x;
        float B = mirror_normal.y;
        float C = mirror_normal.z;
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
              * glm::vec4{mirror_pos - scene_context->camera.get_pos(), 1.0f};

        // first pass
        // Setting the camera to the mirror position and orientation
        Mirror::camera.set_pos(mirror_pos);
        Mirror::camera.set_orientation(reflection);
        Mirror::camera.set_up(glm::vec3{0.0f, 1.0f, 0.0f});
        Mirror::camera.should_calculate_matrix = true;
        scene_context->camera = Mirror::camera;
        scene_context->update_camera(1.0f);

        fbo->bind();
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        scene_context->render();

        // second pass
        fbo->unbind();
    }
    // restore the camera
    scene_context->camera = camera_original;
}

class App : public axolote::Window {
public:
    std::shared_ptr<axolote::SpotLight> flashlight;
    std::shared_ptr<Mirror> mirror;
    std::shared_ptr<axolote::gl::Shader> shader_post_process;
    std::shared_ptr<axolote::gl::Shader> crazy_post_process_shader;
    int shader_num = 0;

    void process_input();
    void main_loop();
    void imgui_frames() override;

    bool should_process_mouse_input() const override {
        return !_io->WantCaptureMouse;
    }
};

class MyDirLight : public axolote::DirectionalLight {
public:
    std::shared_ptr<axolote::AudioEngine> ae = axolote::AudioEngine::create();
    double abs_time = 0.0;
    MyDirLight(const glm::vec3 &color, bool is_set, const glm::vec3 &dir) :
      axolote::DirectionalLight{color, is_set, dir} {
        ae->load_mp3("bleep", myget_path("/resources/audio/bleep.mp3"));
    }

    void update(double absolute_time, double delta_time) override {
        abs_time += delta_time / 10;
        dir = glm::vec3{
            glm::cos((float)abs_time), 0.0f, glm::sin((float)abs_time)
        };

        if (abs_time > M_PI * 2.0) {
            abs_time -= M_PI * 2.0;
            ae->enqueue("bleep");
        }
    }
};

class SpotLightAttachedToCamera : public axolote::SpotLight {
public:
    App *app;

    SpotLightAttachedToCamera(
        const glm::vec3 &color, bool is_set, const glm::vec3 &pos,
        const glm::vec3 &dir, float cut_off, float outer_cut_off, App *app
    ) :
      axolote::SpotLight{color, is_set, pos, dir, cut_off, outer_cut_off},
      app{app} {
    }

    void update(double absolute_time, double delta_time) override {
        pos = app->current_scene()->context->camera.get_pos();
        dir = app->current_scene()->context->camera.get_orientation();
    }
};

// custom resize framebuffer callback
void framebuffer_size_callback(GLFWwindow *window, int width, int height) {
    axolote::Window::default_framebuffer_size_callback(window, width, height);
    auto app = static_cast<App *>(glfwGetWindowUserPointer(window));
    // check if the app is not null
    if (app && app->mirror->fbo)
        app->mirror->fbo->resize(width, height);
}

void App::process_input() {
    axolote::Window::process_input();

    KeyState p_key_state = get_key_state(Key::P);
    if (p_key_state == KeyState::PRESSED && !is_key_pressed(Key::P)) {
        current_scene()->pause = !current_scene()->pause;
        set_key_pressed(Key::P, true);
    }
    else if (p_key_state == KeyState::RELEASED && is_key_pressed(Key::P)) {
        set_key_pressed(Key::P, false);
    }

    KeyState v_key_state = get_key_state(Key::V);
    if (v_key_state == KeyState::PRESSED && !is_key_pressed(Key::V)) {
        set_key_pressed(Key::V, true);
    }
    else if (v_key_state == KeyState::RELEASED && is_key_pressed(Key::V)) {
        set_vsync(!vsync());
        set_key_pressed(Key::V, false);
    }

    KeyState x_state = get_key_state(Key::X);
    if (x_state == KeyState::PRESSED && !is_key_pressed(Key::X)) {
        set_key_pressed(Key::X, true);
    }
    else if (x_state == KeyState::RELEASED && is_key_pressed(Key::X)) {
        if (shader_num == 0) {
            current_scene()->renderer.setup_shader(crazy_post_process_shader);
            shader_num = 1;
        }
        else {
            current_scene()->renderer.setup_shader(shader_post_process);
            shader_num = 0;
        }
        set_key_pressed(Key::X, false);
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
        mirror->should_render = !mirror->should_render;
        set_key_pressed(Key::M, false);
    }

    // Test camera get_ray
    if (get_mouse_key_state(MouseKey::LEFT) == MouseKeyState::PRESSED) {
        double mx, my;
        get_cursor_position(&mx, &my);
        glm::vec3 ray = current_scene()->context->camera.get_ray(
            mx, my, width(), height()
        );
        axolote::debug(
            axolote::DebugType::INFO2, "Ray: %s", glm::to_string(ray).c_str()
        );
    }
}

void App::imgui_frames() {
    // Small guide for using it
    ImGui::Begin("Tests using ImGui");
    ImGui::Text("Press 'P' to toggle scene pause rule");
    ImGui::Text("Press 'X' to toggle crazy post processing shader");
    ImGui::Text("Press 'V' to toggle vsync");
    ImGui::Text("Press 'L' to toggle flashlight");
    ImGui::Text("Press 'M' to toggle mirror");
    ImGui::End();

    // Gamma setter
    ImGui::SetNextWindowSize(ImVec2(200, 100), ImGuiCond_FirstUseEver);
    ImGui::SetNextWindowPos(
        ImVec2(width() / 2.0, height() / 2.0 + height() / 4.0),
        ImGuiCond_FirstUseEver
    );
    ImGui::Begin("Settings", nullptr, ImGuiWindowFlags_AlwaysAutoResize);
    static float gamma = current_scene()->gamma;
    ImGui::SliderFloat("Gamma", &gamma, 0.3f, 1.8f);
    current_scene()->gamma = gamma;
    ImGui::End();

    Window::imgui_frames();
}

void App::main_loop() {
    // Set the window user pointer to this object
    glfwSetWindowUserPointer(window(), this);

    auto audio_engine = axolote::AudioEngine::create();

    set_color(0xff, 0xff, 0xff);
    std::string original_title = title();

    auto shader_program = axolote::gl::Shader::create(
        myget_path("resources/shaders/object3d_base_vertex_shader.glsl"),
        myget_path("./resources/shaders/object3d_base_fragment_shader.glsl")
    );
    auto grid_shader = axolote::gl::Shader::create(
        myget_path("/resources/shaders/grid_base_vertex_shader.glsl"),
        myget_path("/resources/shaders/grid_base_fragment_shader.glsl")
    );
    shader_post_process = axolote::gl::Shader::create(
        myget_path("/resources/shaders/post_processing_base_vertex_shader.glsl"
        ),
        myget_path(
            "/resources/shaders/post_processing_base_fragment_shader.glsl"
        )
    );
    crazy_post_process_shader = axolote::gl::Shader::create(
        myget_path("/resources/shaders/post_processing_base_vertex_shader.glsl"
        ),
        myget_path("/tests/shaders/crazy_post_processing_frag.glsl")
    );

    auto instancing_shader = axolote::gl::Shader::create(
        myget_path("/tests/shaders/instancing_vert_shader.glsl"),
        myget_path("/resources/shaders/object3d_base_fragment_shader.glsl")
    );

    // Scene object
    std::shared_ptr<axolote::Scene> scene{new axolote::Scene{}};
    scene->renderer.init(width(), height());
    scene->renderer.setup_shader(shader_post_process);
    scene->context->camera.set_pos({0.0f, 0.0f, 12.35f});
    scene->context->camera.speed = 3.0f;
    scene->context->camera.sensitivity = 10.0f;
    scene->ambient_light_intensity = 0.1f;

    mirror = std::make_shared<Mirror>(width(), height());
    scene->add_camera_renderer(mirror);
    scene->add_drawable(mirror->mirror_drawable);

    auto dir_light = std::make_shared<MyDirLight>(
        glm::vec3{1.f, 1.f, 1.f}, true, glm::vec3{1.0f, 0.0f, 0.0f}
    );
    dir_light->intensity = 0.9f;
    scene->add_light(dir_light);

    auto flashlight = std::make_shared<SpotLightAttachedToCamera>(
        glm::vec3{1.0f}, true, glm::vec3{0.0f, 5.0f, 0.0f},
        glm::vec3{0.0f, -1.0f, 0.0f}, glm::cos(glm::radians(12.5f)),
        glm::cos(glm::radians(20.0f)), this
    );
    flashlight->should_overlap_scene_pause = true;
    flashlight->linear = 0.09f;
    flashlight->quadratic = 0.032f;
    scene->add_light(flashlight);
    App::flashlight = flashlight;

    auto earth = std::make_shared<axolote::Object3D>(
        myget_path("resources/models/sphere/sphere.obj"),
        glm::vec4{0.0f, 0.0f, 1.0f, 0.6f},
        glm::scale(glm::mat4{1.0f}, 6.0f * glm::vec3{1.0f, 1.0f, 1.0f})
    );
    earth->name = "earth";
    earth->is_transparent = true;
    earth->bind_shader(shader_program);
    scene->add_sorted_drawable(earth);

    auto moon = std::make_shared<axolote::Object3D>(
        myget_path("resources/models/sphere/sphere.obj"),
        glm::vec4{0.8f, 0.8f, 0.8f, 1.0f},
        glm::translate(glm::mat4{1.0f}, glm::vec3{15.f, 2.f, 0.f})
    );
    moon->bind_shader(shader_program);
    scene->add_drawable(moon);

    auto m26 = std::make_shared<axolote::Object3D>(
        myget_path("resources/models/m26/m26pershing_coh.obj"), glm::vec4{1.0f},
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

    auto red_ball = std::make_shared<axolote::Object3D>(
        myget_path("resources/models/sphere/sphere.obj"),
        glm::vec4{1.0f, 0.0f, 0.0f, 1.0f}, glm::mat4{0.0f}
    );
    red_ball->is_transparent = false;
    red_ball->is_affected_by_lights = true;
    auto instancing = std::make_shared<axolote::Instancing>(red_ball);
    std::vector<glm::mat4> matrices;
    // Model matrices
    for (int i = 0; i < 100; i++) {
        glm::mat4 model = glm::mat4{1.0f};
        model = glm::rotate(
            model, glm::radians((float)i * 10.0f), glm::vec3{0.0f, 1.0f, 0.0f}
        );
        model = glm::translate(model, glm::vec3{15.0f, -2.0f, 0.0f});
        model = glm::scale(model, glm::vec3{0.5f, 0.5f, 0.5f});
        matrices.push_back(model);
    }
    // Normal matrices
    std::vector<glm::mat4> normal_matrices;
    for (int i = 0; i < 100; i++) {
        glm::mat4 normal_matrix = glm::transpose(glm::inverse(matrices[i]));
        normal_matrices.push_back(normal_matrix);
    }

    instancing->element_count = matrices.size();
    instancing->add_instanced_mat4_array(4, matrices);
    instancing->add_instanced_mat4_array(8, normal_matrices);
    instancing->bind_shader(instancing_shader);
    scene->add_drawable(instancing);

    auto grid = std::make_shared<axolote::utils::Grid>(
        50, 5, true, glm::vec4{1.0f, 0.f, 0.f, 1.0f}
    );
    grid->fading_factor = 25.0f;
    grid->bind_shader(grid_shader);
    scene->set_grid(grid);

    auto skybox = std::make_shared<axolote::Skybox>(
        myget_path("resources/textures/skybox")
    );
    scene->set_skybox(skybox);

    // Funny things with fbo
    // Overwrite the default framebuffer size callback
    glfwSetFramebufferSizeCallback(window(), framebuffer_size_callback);

    axolote::debug(axolote::DebugType::INFO2, "Starting main loop");

    audio_engine->load_mp3("test", myget_path("resources/audio/breakout.mp3"));
    audio_engine->enqueue("test");
    // Test for debug message
    audio_engine->enqueue("debug test");

    set_scene(scene);
    double before = get_time();
    bool first = true;
    while (!should_close()) {
        init_frame();

        if (should_process_mouse_input()) {
            process_input();
        }

        update_camera((float)width() / height());
        update();
        render();

        finish_frame();
    }
}

int main() {
    axolote::debug(axolote::DebugType::INFO2, "Starting main test");
    App app{};
    app.set_title("Main test");
    app.set_maximized();
    app.main_loop();
    return 0;
}
