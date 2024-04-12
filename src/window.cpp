#include <iostream>
#include <memory>

#include <glad/glad.h>

#include <GL/gl.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

#include <axolote/scene.hpp>
#include <axolote/structs.hpp>
#include <axolote/window.hpp>

#define INITIAL_SIZE 800
#define __UNUSED(x) (void)(x)

namespace axolote
{

static void framebuffer_size_callback(GLFWwindow *window, int width, int height)
{
    __UNUSED(window);
    glViewport(0, 0, width, height);
}

static void error_callback(int error, const char *description)
{
    std::cerr << "Error: " << error << std::endl;
    std::cerr << "Description: " << description << std::endl;
}

Window::Window()
{
    init();
}

Window::Window(const Window &window) :
    _title{window._title},
    _color{window._color},
    current_scene{window.current_scene}
{
    Window::window = window.window;
}

Window::Window(Window &&window) :
    _title{std::move(window._title)},
    _color{std::move(window._color)},
    current_scene{std::move(window.current_scene)}
{
    Window::window = window.window;
    window.window = nullptr;
}

Window::~Window()
{
    glfwDestroyWindow(window);
    glfwTerminate();
}

void Window::init()
{
    glfwSetErrorCallback(error_callback);

    _title = "Axolote Engine";
    window = NULL;
    _color.r = 0x00;
    _color.g = 0x00;
    _color.b = 0x00;

    if (!glfwInit())
    {
        std::cerr << "Error initializing GLFW" << std::endl;
        return;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
    window = glfwCreateWindow(
        INITIAL_SIZE, INITIAL_SIZE, _title.c_str(), NULL, NULL
    );
    if (!window)
    {
        std::cerr << "Error initialing window" << std::endl;
        glfwTerminate();
        return;
    }

    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    glfwMakeContextCurrent(window);
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cerr << "Failed to initialize GLAD" << std::endl;
        return;
    }

    glfwSwapInterval(1);

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

void Window::process_input(float delta_t)
{
    minimal_process_input(delta_t);

    // More keybinds
    if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
        current_scene->camera.upward(delta_t);
    if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
        current_scene->camera.downward(delta_t);
    if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_RIGHT) == GLFW_PRESS)
    {
        glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);

        if (current_scene->camera.first_click)
            glfwSetCursorPos(window, (double)width() / 2, (double)height() / 2);

        double mouse_x, mouse_y;
        glfwGetCursorPos(window, &mouse_x, &mouse_y);
        current_scene->camera.move_vision(
            (float)mouse_x, (float)mouse_y, (float)width(), (float)height(),
            delta_t
        );
        glfwSetCursorPos(window, (double)width() / 2, (double)height() / 2);
    }
    if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_RIGHT) == GLFW_RELEASE)
    {
        glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
        current_scene->camera.first_click = true;
    }
}

void Window::minimal_process_input(float delta_t)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        current_scene->camera.forward(delta_t);
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        current_scene->camera.backward(delta_t);
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        current_scene->camera.leftward(delta_t);
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        current_scene->camera.rightward(delta_t);
}

bool Window::should_close()
{
    return glfwWindowShouldClose(window);
}

std::string Window::title() const
{
    return _title;
}

void Window::set_title(std::string new_title)
{
    glfwSetWindowTitle(window, new_title.c_str());
    _title = new_title;
}

int Window::width() const
{
    int width, height;
    glfwGetWindowSize(window, &width, &height);
    return width;
}

void Window::set_width(int new_width)
{
    glfwSetWindowSize(window, new_width, height());
}

int Window::height() const
{
    int width, height;
    glfwGetWindowSize(window, &width, &height);
    return height;
}

void Window::set_height(int new_height)
{
    glfwSetWindowSize(window, width(), new_height);
}

Color Window::color() const
{
    return _color;
}

void Window::set_color(const Color &color)
{
    _color = color;
}

void Window::set_color(uint8_t r, uint8_t g, uint8_t b, float opacity)
{
    _color = {(float)r / 255, (float)g / 255, (float)b / 255, opacity};
}

void Window::operator=(const Window &window)
{
    _title = window._title;
    _color = window._color;
    current_scene = window.current_scene;
    Window::window = window.window;
}

void Window::operator=(Window &&window)
{
    _title = std::move(window._title);
    _color = std::move(window._color);
    current_scene = std::move(window.current_scene);
    Window::window = window.window;
    window.window = nullptr;
}

} // namespace axolote
