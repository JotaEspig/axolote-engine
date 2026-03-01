#include <memory>

#include <axolote/engine.hpp>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#define GLM_ENABLE_EXPERIMENTAL
#include <axolote/utils.hpp>
#include <glm/gtx/norm.hpp>
#include <glm/gtx/string_cast.hpp>

int WIDTH;
int HEIGHT;

std::string myget_path(const std::string &path) {
    return std::string(PROJECT_ROOT_FOLDER) + "/" + path;
}

class Paint : public axolote::GMesh {
public:
    std::vector<std::vector<glm::vec3>> painted_points;

    Paint();
    Paint(
        const std::vector<axolote::Vertex> &vertices,
        const std::vector<GLuint> &indices,
        const std::vector<std::shared_ptr<axolote::gl::Texture>> &textures
    );

    void draw() override;
    void update_tex();
};

Paint::Paint() :
  GMesh() {
}

Paint::Paint(
    const std::vector<axolote::Vertex> &vertices,
    const std::vector<GLuint> &indices,
    const std::vector<std::shared_ptr<axolote::gl::Texture>> &textures
) :
  GMesh(vertices, indices, textures) {
}

void Paint::update_tex() {
    auto textureID = GMesh::textures.at(0)->id();
    glBindTexture(GL_TEXTURE_2D, textureID);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    auto width = WIDTH;
    auto height = HEIGHT;
    auto data = std::vector<float>(width * height * 3);
    for (int x = 0; x < width; x++) {
        for (int y = 0; y < height; y++) {
            auto color = this->painted_points[x][y];
            data[(y * width + x) * 3 + 0] = color.r;
            data[(y * width + x) * 3 + 1] = color.g;
            data[(y * width + x) * 3 + 2] = color.b;
        }
    }
    glTexImage2D(
        GL_TEXTURE_2D, 0, GL_RGB32F, width, height, 0, GL_RGB, GL_FLOAT,
        data.data()
    );

    glGenerateMipmap(GL_TEXTURE_2D);

    glBindTexture(GL_TEXTURE_2D, 0);
}

void Paint::draw() {
    update_tex();

    GMesh::draw();
}

class App : public axolote::Window {
public:
    int selection = 0; // 0 = RED, 1 = GREEN, 2 = BLUE
    std::shared_ptr<Paint> paint_mesh;

    App();

    void process_input();
    void main_loop();
    void imgui_frames() override;

private:
    glm::vec3 get_color_by_selection() const;
};

glm::vec3 App::get_color_by_selection() const {
    switch (selection) {
    case 0:
        return glm::vec3{1.0f, 0.0f, 0.0f}; // RED
    case 1:
        return glm::vec3{0.0f, 1.0f, 0.0f}; // GREEN
    case 2:
        return glm::vec3{0.0f, 0.0f, 1.0f}; // BLUE
    default:
        return glm::vec3{1.0f, 1.0f, 1.0f}; // WHITE
    }
}

App::App() :
  Window() {
    glfwMaximizeWindow(window());
    glfwGetWindowSize(window(), &WIDTH, &HEIGHT);
    axolote::debug(
        axolote::DebugType::Info, "Window size: %d x %d", WIDTH, HEIGHT
    );

    auto paint_shaders = axolote::gl::Shader::create(
        myget_path("/tests/shaders/paint_vert.glsl"),
        myget_path("/tests/shaders/paint_frag.glsl")
    );

    auto vertices = std::vector<axolote::Vertex>{
        {{-1.0f, 1.0f, 0.0f}, {}, {0.0f, 1.0f}, {}},
        {{-1.0f, -1.0f, 0.0f}, {}, {0.0f, 0.0f}, {}},
        {{1.0f, -1.0f, 0.0f}, {}, {1.0f, 0.0f}, {}},
        {{1.0f, 1.0f, 0.0f}, {}, {1.0f, 1.0f}, {}},
    };
    auto indices = std::vector<GLuint>{0, 1, 2, 0, 2, 3};
    auto tex = axolote::gl::Texture::create();
    auto textures = std::vector<std::shared_ptr<axolote::gl::Texture>>{tex};
    paint_mesh = std::make_shared<Paint>(vertices, indices, textures);
    paint_mesh->bind_shader(paint_shaders);

    paint_mesh->painted_points.resize(WIDTH);
    for (auto &column : paint_mesh->painted_points) {
        column.resize(HEIGHT, glm::vec3{1.0f, 1.0f, 1.0f});
    }

    set_vsync(false);
}

void App::process_input() {
    KeyState c_key_state = get_key_state(Key::C);
    if (c_key_state == KeyState::PRESSED && !is_key_pressed(Key::C)) {
        // clear paint
        paint_mesh->painted_points.clear();
        paint_mesh->painted_points.resize(WIDTH);
        for (auto &column : paint_mesh->painted_points) {
            column.resize(HEIGHT, glm::vec3{1.0f, 1.0f, 1.0f});
        }
        set_key_pressed(Key::C, true);
    }
    else if (c_key_state == KeyState::RELEASED && is_key_pressed(Key::C)) {
        set_key_pressed(Key::C, false);
    }

    if (get_mouse_key_state(MouseKey::LEFT) == MouseKeyState::PRESSED) {
        double mx, my;
        get_cursor_position(&mx, &my);
        axolote::debug(
            axolote::DebugType::Info2, "Mouse press: %.2lf, %.2lf", mx, my
        );

        int x = static_cast<int>(mx);
        int y = HEIGHT - static_cast<int>(my);
        auto size = 10;
        for (int i = -(size) / 2; i < size / 2; ++i) {
            for (int j = -(size) / 2; j < size / 2; ++j) {
                if (x + i < 0 || y + j < 0)
                    continue;
                paint_mesh->painted_points[x + i][y + j]
                    = get_color_by_selection();
            }
        }
    }
}

void App::imgui_frames() {
    ImGui::Begin("Paint");

    // Radiobutton for colors
    ImGui::Text("Paint brabo");
    ImGui::RadioButton("RED", &selection, 0);
    ImGui::SameLine();
    ImGui::RadioButton("GREEN", &selection, 1);
    ImGui::SameLine();
    ImGui::RadioButton("BLUE", &selection, 2);

    ImGui::End();

    Window::imgui_frames();
}

void App::main_loop() {
    glfwSetWindowUserPointer(window(), this);
    auto shader_post_process = axolote::gl::Shader::create(
        myget_path("/resources/shaders/post_processing_base_vertex_shader.glsl"
        ),
        myget_path(
            "/resources/shaders/post_processing_base_fragment_shader.glsl"
        )
    );

    auto scene = std::make_shared<axolote::Scene>();
    scene->renderer.init(width(), height());
    scene->renderer.setup_shader(shader_post_process);

    scene->add_drawable(paint_mesh);

    this->set_scene(scene);
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
    axolote::debug(axolote::DebugType::Info2, "Starting main test");
    App app{};
    app.set_title("Main test");
    app.set_maximized();
    app.main_loop();
    return 0;
}