#include <iostream>

#include <glm/glm.hpp>
#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>

#include "axolote/glad/glad.h"
#include "axolote/structs.hpp"
#include "axolote/window.hpp"

#define INITIAL_SIZE 800
#define UNUSED(x) (void)(x)

namespace axolote {

Window::Window() {
    init();
}

Window::Window(bool vsync) :
  _vsync{vsync} {
    init();
}

Window::~Window() {
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
    glfwDestroyWindow(_window);
    glfwTerminate();
}

void Window::default_framebuffer_size_callback(
    GLFWwindow *window, int width, int height
) {
    UNUSED(window);
    glViewport(0, 0, width, height);
    auto w = static_cast<Window *>(glfwGetWindowUserPointer(window));
    if (w->_current_scene) {
        w->_current_scene->renderer.fbo->resize(width, height);
        w->_current_scene->context->camera.should_calculate_matrix = true;
        w->update_camera((float)width / height);
    }
}

void Window::default_error_callback(int error, const char *description) {
    std::cerr << "Error: " << error << std::endl;
    std::cerr << "Description: " << description << std::endl;
}

void Window::init() {
    glfwSetErrorCallback(default_error_callback);

    _title = "Axolote Engine";
    _window = NULL;
    _color.r = 0x00;
    _color.g = 0x00;
    _color.b = 0x00;

    if (!glfwInit()) {
        std::cerr << "Error initializing GLFW" << std::endl;
        return;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    _window = glfwCreateWindow(
        INITIAL_SIZE, INITIAL_SIZE, _title.c_str(), NULL, NULL
    );
    if (!_window) {
        std::cerr << "Error initialing window" << std::endl;
        glfwTerminate();
        return;
    }

    glfwSetFramebufferSizeCallback(_window, default_framebuffer_size_callback);

    glfwSetWindowUserPointer(_window, this);

    glfwMakeContextCurrent(_window);
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cerr << "Failed to initialize GLAD" << std::endl;
        return;
    }

    glfwSwapInterval(_vsync);

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
    glEnable(GL_FRAMEBUFFER_SRGB);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO &io = ImGui::GetIO();
    io.IniFilename = NULL;
    io.LogFilename = NULL;
    _io = std::make_shared<ImGuiIO>(io);
    ImGui::StyleColorsDark();
    ImGui_ImplGlfw_InitForOpenGL(_window, true);
    ImGui_ImplOpenGL3_Init("#version 330");

    _absolute_time = get_time();
}

void Window::poll_events() {
    glfwPollEvents();
}

Window::KeyState Window::get_key_state(Window::Key key) {
    int key_int = static_cast<int>(key);
    return static_cast<KeyState>(glfwGetKey(_window, key_int));
}

Window::MouseKeyState Window::get_mouse_key_state(Window::MouseKey key) {
    int key_int = static_cast<int>(key);
    return static_cast<MouseKeyState>(glfwGetMouseButton(_window, key_int));
}

bool Window::is_key_pressed(Window::Key key) const {
    int key_int = static_cast<int>(key);
    auto found = _keys_pressed.find(key_int);
    if (found == _keys_pressed.end())
        return false;
    return found->second;
}

void Window::set_key_pressed(Window::Key key, bool pressed) {
    int key_int = static_cast<int>(key);
    _keys_pressed[key_int] = pressed;
}

void Window::set_cursor_mode(CursorMode mode) {
    int mode_int = static_cast<int>(mode);
    glfwSetInputMode(_window, GLFW_CURSOR, mode_int);
}

void Window::get_cursor_position(double *x, double *y) {
    glfwGetCursorPos(_window, x, y);
}

void Window::set_cursor_position(double x, double y) {
    glfwSetCursorPos(_window, x, y);
}

void Window::process_input() {
    minimal_process_input();

    // More keybinds
    if (get_key_state(Key::SPACE) == KeyState::PRESSED)
        _current_scene->context->camera.upward(_delta_time);
    if (get_key_state(Key::LEFT_SHIFT) == KeyState::PRESSED)
        _current_scene->context->camera.downward(_delta_time);
    if (get_mouse_key_state(MouseKey::RIGHT) == MouseKeyState::PRESSED) {
        set_cursor_mode(CursorMode::DISABLED);

        double mouse_x, mouse_y;
        get_cursor_position(&mouse_x, &mouse_y);

        static bool was_right_mouse_pressed = false;
        static double last_mouse_x = 0.0, last_mouse_y = 0.0;

        if (!_current_scene->context->camera.first_click
            && was_right_mouse_pressed) {
            double delta_x = mouse_x - last_mouse_x;
            double delta_y = mouse_y - last_mouse_y;

            _current_scene->context->camera.move_vision(
                (float)delta_x, (float)delta_y, _delta_time
            );
        }

        last_mouse_x = mouse_x;
        last_mouse_y = mouse_y;
        was_right_mouse_pressed = true;
        _current_scene->context->camera.first_click = false;
    }
    else if (get_mouse_key_state(MouseKey::RIGHT) == MouseKeyState::RELEASED) {
        set_cursor_mode(CursorMode::NORMAL);
        _current_scene->context->camera.first_click = true;

        // Reset state
        static bool was_right_mouse_pressed = false;
        was_right_mouse_pressed = false;
    }
}

void Window::minimal_process_input() {
    if (get_key_state(Key::ESCAPE) == KeyState::PRESSED)
        set_should_close(true);
    if (get_key_state(Key::W) == KeyState::PRESSED)
        _current_scene->context->camera.forward(_delta_time);
    if (get_key_state(Key::S) == KeyState::PRESSED)
        _current_scene->context->camera.backward(_delta_time);
    if (get_key_state(Key::A) == KeyState::PRESSED)
        _current_scene->context->camera.leftward(_delta_time);
    if (get_key_state(Key::D) == KeyState::PRESSED)
        _current_scene->context->camera.rightward(_delta_time);
}

bool Window::should_close() const {
    return glfwWindowShouldClose(_window);
}

void Window::set_should_close(bool should_close) {
    glfwSetWindowShouldClose(_window, should_close);
}

void Window::tick() {
    double now = get_time();
    _delta_time = now - _absolute_time;
    _absolute_time = now;
}

void Window::init_frame() {
    clear();
    poll_events();
    tick();

    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();
}

void Window::clear() {
    glClearColor(_color.r, _color.g, _color.b, _color.opacity);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Window::finish_frame() {
    ImGui::EndFrame();
    glfwSwapBuffers(_window);
}

void Window::update_camera(float aspect_ratio) {
    _current_scene->update_camera(aspect_ratio);
}

void Window::update() {
    _current_scene->update(_absolute_time, _delta_time);
    clear();
}

void Window::render() {
    _current_scene->render();

    GLboolean is_srgb_enabled;
    glGetBooleanv(GL_FRAMEBUFFER_SRGB, &is_srgb_enabled);
    glDisable(GL_FRAMEBUFFER_SRGB);
    imgui_frames();
    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
    if (is_srgb_enabled)
        glEnable(GL_FRAMEBUFFER_SRGB);
}

void Window::imgui_frames() {
    // FPS
    ImGui::SetNextWindowPos(ImVec2(0, 0), ImGuiCond_Always); // Top Left

    ImGui::SetNextWindowBgAlpha(0.35f); // 35% opacity

    ImGuiWindowFlags flags
        = ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize
          | ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_NoMove
          | ImGuiWindowFlags_NoSavedSettings
          | ImGuiWindowFlags_NoFocusOnAppearing | ImGuiWindowFlags_NoNav;

    // Begin the ImGui window
    if (ImGui::Begin("FPS Overlay", nullptr, flags)) {
        // Set text color to green
        ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(0.0f, 1.0f, 0.0f, 1.0f));
        ImGui::Text("FPS: %.1f", ImGui::GetIO().Framerate);
        ImGui::PopStyleColor();
    }
    ImGui::End();

}

std::shared_ptr<Scene> Window::current_scene() const {
    return _current_scene;
}

void Window::set_scene(std::shared_ptr<Scene> scene) {
    _current_scene = scene;
}

bool Window::vsync() const {
    return _vsync;
}

void Window::set_vsync(bool vsync) {
    _vsync = vsync;
    glfwSwapInterval(vsync);
}

void Window::set_maximized() {
    glfwMaximizeWindow(_window);
}

std::string Window::title() const {
    return _title;
}

void Window::set_title(std::string new_title) {
    glfwSetWindowTitle(_window, new_title.c_str());
    _title = new_title;
}

int Window::width() const {
    int width, height;
    glfwGetWindowSize(_window, &width, &height);
    return width;
}

int Window::height() const {
    int width, height;
    glfwGetWindowSize(_window, &width, &height);
    return height;
}

void Window::set_window_size(int new_width, int new_height) {
    glfwSetWindowSize(_window, new_width, new_height);
}

Color Window::color() const {
    return _color;
}

void Window::set_color(const Color &color) {
    _color = color;
}

void Window::set_color(uint8_t r, uint8_t g, uint8_t b, float opacity) {
    _color = {(float)r / 255, (float)g / 255, (float)b / 255, opacity};
}

double Window::get_time() const {
    return glfwGetTime();
}

bool Window::should_process_mouse_input() const {
    return true;
}

bool Window::should_process_keyboard_input() const {
    return true;
}

GLFWwindow *Window::window() const {
    return _window;
}

} // namespace axolote
