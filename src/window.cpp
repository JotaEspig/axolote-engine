#include <axolote/window.hpp>

#include <iostream>

#include <glad/glad.h>
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
        std::cout << "Error initialing window" << std::endl;
        glfwTerminate();
        return;
    }

    glfwMakeContextCurrent(window);
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return;
    }

    int width, height;
    glfwGetFramebufferSize(window, &width, &height);
    glViewport(0, 0, width, height);
    while (true);

    glfwTerminate();
}
