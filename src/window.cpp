#include <axolote/window.hpp>

#include <GLFW/glfw3.h>

using namespace axolote;

Window::Window(int argc, char **argv)
{
    init(argc, argv);
}

Window::~Window()
{
}

void Window::init(int argc, char **argv)
{
}

void Window::main_loop()
{
    if (!glfwInit())
    {
        // error
    }

    GLFWwindow* window = glfwCreateWindow(640, 480, "My Title", NULL, NULL);
    if (!window)
    {
        // Window or OpenGL context creation failed
    }

    glfwMakeContextCurrent(window);
    int width, height;
    glfwGetFramebufferSize(window, &width, &height);
    glViewport(0, 0, width, height);
    while (true);

    glfwTerminate();
}
