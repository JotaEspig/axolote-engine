#include <axolote/window.hpp>

#include <iostream>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

using namespace axolote;

Window::Window()
{
    init();
}

Window::~Window()
{
    glfwTerminate();
}

void Window::init()
{
    title = "default";
    width = 800;
    height = 600;
    window = NULL;

    if (!glfwInit())
    {
        std::cout << "Error initializing glfw" << std::endl;
    }

    window = glfwCreateWindow(width, height, title.c_str(), NULL, NULL);
    if (!window)
    {
        std::cout << "Error initialing window" << std::endl;
        glfwTerminate();
        return;
    }
}

static void framebuffer_size_callback(GLFWwindow *window, int width, int height)
{
    glViewport(0, 0, width, height);
}

void Window::process_input()
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}

void Window::main_loop()
{
    glfwMakeContextCurrent(window);
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return;
    }

    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    while (!glfwWindowShouldClose(window))
    {
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
}
