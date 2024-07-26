#include <iostream>

#include <glm/glm.hpp>

#include "axolote/glad/glad.h"
#include "axolote/structs.hpp"
#include "axolote/window.hpp"

#define INITIAL_SIZE 800
#define UNUSED(x) (void)(x)

namespace axolote {

static void
framebuffer_size_callback(GLFWwindow *window, int width, int height) {
    UNUSED(window);
    glViewport(0, 0, width, height);
}

static void error_callback(int error, const char *description) {
    std::cerr << "Error: " << error << std::endl;
    std::cerr << "Description: " << description << std::endl;
}

Window::Window() {
    init();
}

Window::Window(bool vsync) :
  _vsync{vsync} {
    init();
}

Window::~Window() {
    glfwDestroyWindow(_window);
    glfwTerminate();
}

void Window::init() {
    glfwSetErrorCallback(error_callback);

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
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
    _window = glfwCreateWindow(
        INITIAL_SIZE, INITIAL_SIZE, _title.c_str(), NULL, NULL
    );
    if (!_window) {
        std::cerr << "Error initialing window" << std::endl;
        glfwTerminate();
        return;
    }

    glfwSetFramebufferSizeCallback(_window, framebuffer_size_callback);

    glfwMakeContextCurrent(_window);
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cerr << "Failed to initialize GLAD" << std::endl;
        return;
    }

    glfwSwapInterval(_vsync);

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
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

void Window::process_input(double delta_t) {
    minimal_process_input(delta_t);

    // More keybinds
    if (get_key_state(Key::SPACE) == KeyState::PRESSED)
        _current_scene->camera.upward(delta_t);
    if (get_key_state(Key::LEFT_SHIFT) == KeyState::PRESSED)
        _current_scene->camera.downward(delta_t);
    if (get_mouse_key_state(MouseKey::RIGHT) == MouseKeyState::PRESSED) {
        set_cursor_mode(CursorMode::DISABLED);

        if (_current_scene->camera.first_click)
            set_cursor_position((double)width() / 2, (double)height() / 2);

        double mouse_x, mouse_y;
        get_cursor_position(&mouse_x, &mouse_y);
        _current_scene->camera.move_vision(
            (float)mouse_x, (float)mouse_y, (float)width(), (float)height(),
            delta_t
        );
        set_cursor_position((double)width() / 2, (double)height() / 2);
    }
    if (get_mouse_key_state(MouseKey::RIGHT) == MouseKeyState::RELEASED) {
        set_cursor_mode(CursorMode::NORMAL);
        _current_scene->camera.first_click = true;
    }
}

void Window::minimal_process_input(double delta_t) {
    if (get_key_state(Key::ESCAPE) == KeyState::PRESSED)
        set_should_close(true);
    if (get_key_state(Key::W) == KeyState::PRESSED)
        _current_scene->camera.forward(delta_t);
    if (get_key_state(Key::S) == KeyState::PRESSED)
        _current_scene->camera.backward(delta_t);
    if (get_key_state(Key::A) == KeyState::PRESSED)
        _current_scene->camera.leftward(delta_t);
    if (get_key_state(Key::D) == KeyState::PRESSED)
        _current_scene->camera.rightward(delta_t);
}

bool Window::should_close() const {
    return glfwWindowShouldClose(_window);
}

void Window::set_should_close(bool should_close) {
    glfwSetWindowShouldClose(_window, should_close);
}

void Window::clear() {
    glClearColor(_color.r, _color.g, _color.b, _color.opacity);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Window::flush() {
    glfwSwapBuffers(_window);
}

void Window::update_camera(float aspect_ratio) {
    _current_scene->update_camera(aspect_ratio);
}

void Window::update(double delta_t) {
    _current_scene->update(delta_t);
}

void Window::render() {
    _current_scene->render();
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

void Window::set_width(int new_width) {
    glfwSetWindowSize(_window, new_width, height());
}

int Window::height() const {
    int width, height;
    glfwGetWindowSize(_window, &width, &height);
    return height;
}

void Window::set_height(int new_height) {
    glfwSetWindowSize(_window, width(), new_height);
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

} // namespace axolote
