#include <iostream>

#include <glad/glad.h>
#include <GL/gl.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

#include <axolote/window.hpp>
#include <axolote/camera.hpp>
#include <axolote/structs.hpp>

#define INITIAL_SIZE 800

namespace axolote
{

static void framebuffer_size_callback(GLFWwindow *window, int width, int height)
{
    glViewport(0, 0, width, height);
}

static void error_callback(int error, const char *description)
{
    std::cerr << "Error: " << description << std::endl;
}

Window::Window()
{
    init();
}

Window::~Window()
{
    glfwDestroyWindow(window);
    glfwTerminate();
}

void Window::init()
{
    _title = "Axolote Engine";
    window = NULL;
    _color.r = 0x00;
    _color.g = 0x00;
    _color.b = 0x00;
    camera = Camera(glm::vec3(0.0f, 0.0f, 3.0f));

    if (!glfwInit())
    {
        std::cerr << "Error initializing glfw" << std::endl;
        return;
    }

    glfwWindowHint(GLFW_DOUBLEBUFFER, GLFW_FALSE);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
    window = glfwCreateWindow(INITIAL_SIZE, INITIAL_SIZE, _title.c_str(), NULL, NULL);
    if (!window)
    {
        std::cerr << "Error initialing window" << std::endl;
        glfwTerminate();
        return;
    }

    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    glfwSetErrorCallback(error_callback);

    glfwMakeContextCurrent(window);
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cerr << "Failed to initialize GLAD" << std::endl;
        return;
    }

    glfwSwapInterval(0);

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

void Window::process_input()
{
    minimal_process_input();

    // More keybinds
    if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
        camera.upward();
    if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
        camera.downward();
    if (glfwGetKey(window, GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS)
        camera.speed = 0.5f;
    if (glfwGetKey(window, GLFW_KEY_LEFT_CONTROL) == GLFW_RELEASE)
        camera.speed = 0.1f;
    if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_RIGHT) == GLFW_PRESS)
    {
        glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);

        if (camera.first_click)
            glfwSetCursorPos(window, (double)width() / 2, (double)height() / 2);

        double mouse_x, mouse_y;
        glfwGetCursorPos(window, &mouse_x, &mouse_y);
        camera.move_vision((float)mouse_x, (float)mouse_y, (float)width(), (float)height());
        glfwSetCursorPos(window, (double)width() / 2, (double)height() / 2);
    }
    if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_RIGHT) == GLFW_RELEASE)
    {
        glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
        camera.first_click = true;
    }
}

void Window::minimal_process_input()
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        camera.forward();
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        camera.backward();
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        camera.leftward();
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        camera.rightward();
}

bool Window::should_close()
{
    return glfwWindowShouldClose(window);
}

// GETTERS AND SETTERS

std::string Window::title()
{
    return _title;
}

void Window::set_title(std::string new_title)
{
    glfwSetWindowTitle(window, new_title.c_str());
    _title = new_title;
}

int Window::width()
{
    int width, height;
    glfwGetWindowSize(window, &width, &height);
    return width;
}

void Window::set_width(int new_width)
{
    glfwSetWindowSize(window, new_width, height());
}

int Window::height()
{
    int width, height;
    glfwGetWindowSize(window, &width, &height);
    return height;
}

void Window::set_height(int new_height)
{
    glfwSetWindowSize(window, width(), new_height);
}

Color Window::color()
{
    return _color;
}

void Window::set_color(Color color)
{
    _color = color;
}

void Window::set_color(uint8_t r, uint8_t g, uint8_t b, float opacity)
{
    _color = {(float)r / 255, (float)g / 255, (float)b / 255, opacity};
}

} // namespace axolote
