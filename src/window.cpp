#include <iostream>
#include <cmath>

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <stb/stb_image.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

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
    window = glfwCreateWindow(800, 700, _title.c_str(), NULL, NULL);
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
	// front
         0.5f,  0.5f, 0.5f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f,   // top right
         0.5f, -0.5f, 0.5f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f,   // bottom right
        -0.5f, -0.5f, 0.5f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f,   // bottom left
        -0.5f,  0.5f, 0.5f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f,   // top left
	// right
         0.5f, -0.5f, 0.5f,   0.0f, 1.0f, 0.0f,   0.0f, 0.0f,   // bottom right
         0.5f, -0.5f, -0.5f,  0.0f, 1.0f, 0.0f,   1.0f, 0.0f,   // back bottom right
         0.5f,  0.5f, -0.5f,  1.0f, 0.0f, 0.0f,   1.0f, 1.0f,   // back top right
         0.5f,  0.5f, 0.5f,   1.0f, 0.0f, 0.0f,   0.0f, 1.0f,   // top right
	// left
        -0.5f, -0.5f, -0.5f,  0.0f, 0.0f, 1.0f,   0.0f, 0.0f,   // back bottom left
        -0.5f, -0.5f, 0.5f,   0.0f, 0.0f, 1.0f,   1.0f, 0.0f,   // bottom left
        -0.5f,  0.5f, 0.5f,   1.0f, 1.0f, 0.0f,   1.0f, 1.0f,   // top left
        -0.5f,  0.5f, -0.5f,  1.0f, 1.0f, 0.0f,   0.0f, 1.0f,   // back top left
	// top
        -0.5f,  0.5f, 0.5f,   1.0f, 1.0f, 0.0f,   0.0f, 0.0f,   // top left
         0.5f,  0.5f, 0.5f,   1.0f, 0.0f, 0.0f,   1.0f, 0.0f,   // top right
         0.5f,  0.5f, -0.5f,  1.0f, 0.0f, 0.0f,   1.0f, 1.0f,   // back top right
        -0.5f,  0.5f, -0.5f,  1.0f, 1.0f, 0.0f,   0.0f, 1.0f,   // back top left
	// bottom
        -0.5f, -0.5f, -0.5f,  0.0f, 0.0f, 1.0f,   0.0f, 0.0f,   // back bottom left
         0.5f, -0.5f, -0.5f,  0.0f, 1.0f, 0.0f,   1.0f, 0.0f,   // back bottom right
         0.5f, -0.5f, 0.5f,   0.0f, 1.0f, 0.0f,   1.0f, 1.0f,   // bottom right
        -0.5f, -0.5f, 0.5f,   0.0f, 0.0f, 1.0f,   0.0f, 1.0f,   // bottom left
	// back
         0.5f, -0.5f, -0.5f,  0.0f, 1.0f, 0.0f,   0.0f, 0.0f,   // back bottom right
        -0.5f, -0.5f, -0.5f,  0.0f, 0.0f, 1.0f,   1.0f, 0.0f,   // back bottom left
        -0.5f,  0.5f, -0.5f,  1.0f, 1.0f, 0.0f,   1.0f, 1.0f,   // back top left
         0.5f,  0.5f, -0.5f,  1.0f, 0.0f, 0.0f,   0.0f, 1.0f,   // back top right
    };

    GLuint indices[] = {
        //front face
        0, 1, 2,
        0, 2, 3,
        // right face
        4, 5, 6,
        4, 6, 7,
        // left face
        8, 9, 10,
        8, 10, 11,
        // top face
        12, 13, 14,
        12, 14, 15,
        // bottom face
        16, 17, 18,
        16, 18, 19,
        // back face
        20, 21, 22,
        20, 22, 23
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

    VAO vao2;
    vao2.bind();
    VBO vbo2(vertices, sizeof(vertices));
    EBO ebo2(indices, sizeof(indices));

    vao2.link_attrib(vbo2, 0, 3, GL_FLOAT, 8 * sizeof(float), (void *)0);
    vao2.link_attrib(vbo2, 1, 3, GL_FLOAT, 8 * sizeof(float), (void *)(3 * sizeof(float)));
    vao2.link_attrib(vbo2, 2, 2, GL_FLOAT, 8 * sizeof(float), (void *)(6 * sizeof(float)));
    vao2.unbind();
    vbo2.unbind();
    ebo2.unbind();

    Texture tex0("./resources/textures/wall.jpg", GL_TEXTURE_2D, GL_TEXTURE0,
                 GL_RGB, GL_UNSIGNED_BYTE);
    if (!tex0.loaded)
        std::cerr << "Error when loading texture" << std::endl;

    shader_program.set_uniform_int("tex1", 0);

    Texture tex1("./resources/textures/mano.jpg", GL_TEXTURE_2D,
                 GL_TEXTURE1, GL_RGB, GL_UNSIGNED_BYTE);
    if (!tex1.loaded)
        std::cerr << "Error when loading texture" << std::endl;

    shader_program.set_uniform_int("tex2", 1);

    glEnable(GL_DEPTH_TEST);
    while (!glfwWindowShouldClose(window))
    {
        glClearColor(_color.r, _color.g, _color.b, _color.opacity);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        tex0.activate();
        tex0.bind();
        tex1.activate();
        tex1.bind();

        shader_program.activate();

        double now = glfwGetTime();
        glm::mat4 model = glm::mat4(1.0f);
        model = glm::translate(model, glm::vec3(0.0f, 0.0f, -1.0f));
        model = glm::rotate(model, (float)now, glm::vec3(0.5f, 1.0f, 0.0f));
        glm::mat4 view = glm::mat4(1.0f);
        view = glm::translate(view, glm::vec3(0.0f, 0.0f, -1.0f));
        glm::mat4 projection = glm::perspective(glm::radians(90.0f), (float)width() / height(), 0.1f, 100.0f);

        GLuint model_loc = glGetUniformLocation(shader_program.id, "model");
        GLuint view_loc = glGetUniformLocation(shader_program.id, "view");
        GLuint projection_loc = glGetUniformLocation(shader_program.id, "projection");

        glUniformMatrix4fv(model_loc, 1, GL_FALSE, glm::value_ptr(model));
        glUniformMatrix4fv(view_loc, 1, GL_FALSE, glm::value_ptr(view));
        glUniformMatrix4fv(projection_loc, 1, GL_FALSE, glm::value_ptr(projection));

        vao1.bind();
        glDrawElements(GL_TRIANGLES, sizeof(indices) / sizeof(int), GL_UNSIGNED_INT, 0);

        model = glm::mat4(1.0f);
        model = glm::scale(model, glm::vec3(0.3f, 0.3f, 0.3f));
        model = glm::translate(model, glm::vec3(8.0f * sin(now), 0.0f, -3.0f + 8.0f * cos(now)));
        glUniformMatrix4fv(model_loc, 1, GL_FALSE, glm::value_ptr(model));
        glDrawElements(GL_TRIANGLES, sizeof(indices) / sizeof(int), GL_UNSIGNED_INT, 0);
        vao1.unbind();

        glfwSwapBuffers(window);

        glfwPollEvents();
        process_input();
    }

    glDisable(GL_DEPTH_TEST);

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

void Window::set_color(uint8_t r, uint8_t g, uint8_t b, float opacity)
{
    _color = {(float)r / 255, (float)g / 255, (float)b / 255, opacity};
}
