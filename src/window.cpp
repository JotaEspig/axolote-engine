#include <iostream>
#include <cmath>

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <stb/stb_image.h>

#include <axolote/window.hpp>
#include <axolote/structs.hpp>
#include <axolote/shader.hpp>
#include <axolote/texture.hpp>
#include <axolote/vao.hpp>
#include <axolote/vbo.hpp>
#include <axolote/ebo.hpp>

using namespace axolote;

Window::Window()
{
    init();
}

Window::~Window()
{
    glfwDestroyWindow(window);
    glfwTerminate();
}

static void framebuffer_size_callback(GLFWwindow *window, int width, int height)
{
    glViewport(0, 0, width, height);
}

static void error_callback(int error, const char *description)
{
    std::cerr << "Error: " << description << std::endl;
}

void Window::init()
{
    _title = "Axolote Engine";
    _width = 800;
    _height = 600;
    window = NULL;
    _color.r = 0x00;
    _color.g = 0x00;
    _color.b = 0x00;

    if (!glfwInit())
    {
        std::cerr << "Error initializing glfw" << std::endl;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
    window = glfwCreateWindow(_width, _height, _title.c_str(), NULL, NULL);
    if (!window)
    {
        std::cerr << "Error initialing window" << std::endl;
        glfwTerminate();
        return;
    }
}

void Window::process_input()
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}

void Window::main_loop()
{
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    glfwSetErrorCallback(error_callback);

    glfwMakeContextCurrent(window);
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cerr << "Failed to initialize GLAD" << std::endl;
        return;
    }

    glfwSwapInterval(1);

    GLfloat vertices[] = {
        // positions          // colors           // texture coords
         0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f,   // top right
         0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f,   // bottom right
        -0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f,   // bottom left
        -0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f    // top left
    };

    GLuint indices[] = {
        0, 1, 3,
        1, 2, 3
    };

    Shader shader_program("./resources/shaders/vertex_shader.txt",
                          "./resources/shaders/fragment_shader.txt");

    VAO vao1;
    vao1.bind();
    VBO vbo1(vertices, sizeof(vertices));
    EBO ebo1(indices, sizeof(indices));

    vao1.link_attrib(vbo1, 0, 3, GL_FLOAT, 8 * sizeof(float), (void *)0);
    vao1.link_attrib(vbo1, 1, 3, GL_FLOAT, 8 * sizeof(float), (void *)(3 * sizeof(float)));
    vao1.link_attrib(vbo1, 2, 2, GL_FLOAT, 8 * sizeof(float), (void *)(6 * sizeof(float)));
    vao1.unbind();
    vbo1.unbind();
    ebo1.unbind();

    Texture tex0("./resources/textures/wall.jpg", GL_TEXTURE_2D, GL_TEXTURE0,
                 GL_RGB, GL_UNSIGNED_BYTE);
    if (!tex0.loaded)
        std::cerr << "Error when loading texture" << std::endl;

    tex0.set_tex_unit_uniform(shader_program, "tex1", 0);

    Texture tex1("./resources/textures/pedro.png", GL_TEXTURE_2D,
                 GL_TEXTURE1, GL_RGBA, GL_UNSIGNED_BYTE);
    if (!tex1.loaded)
        std::cerr << "Error when loading texture" << std::endl;

    tex1.set_tex_unit_uniform(shader_program, "tex2", 1);

    while (!glfwWindowShouldClose(window))
    {
        glClearColor(_color.r, _color.g, _color.b, _color.opacity);
        glClear(GL_COLOR_BUFFER_BIT);

        tex0.activate();
        tex0.bind();
        tex1.activate();
        tex1.bind();

        shader_program.activate();
        vao1.bind();

        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

        glfwSwapBuffers(window);

        glfwPollEvents();
        process_input();
    }

    vao1.destroy();
    vbo1.destroy();
    shader_program.destroy();
    tex0.destroy();
    tex1.destroy();
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

uint16_t Window::width()
{
    return _width;
}

void Window::set_width(uint16_t new_width)
{
    glfwSetWindowSize(window, new_width, _height);
    _width = new_width;
}

uint16_t Window::height()
{
    return _height;
}

void Window::set_height(uint16_t new_height)
{
    glfwSetWindowSize(window, _width, new_height);
    _height = new_height;
}

Color Window::color()
{
    return _color;
}

void Window::set_color(uint8_t r, uint8_t g, uint8_t b, float opacity)
{
    _color = {(float)r / 255, (float)g / 255, (float)b / 255, opacity};
}
