#include <iostream>
#include <cmath>
#include <vector>

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <stb/stb_image.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <axolote/window.hpp>
#include <axolote/camera.hpp>
#include <axolote/structs.hpp>
#include <axolote/shader.hpp>
#include <axolote/texture.hpp>
#include <axolote/entity.hpp>
#include <axolote/model.hpp>
#include <axolote/mesh.hpp>
#include <axolote/vbo.hpp>

using namespace axolote;

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

    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    glfwSetErrorCallback(error_callback);

    glfwMakeContextCurrent(window);
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cerr << "Failed to initialize GLAD" << std::endl;
        return;
    }

    glfwSwapInterval(1);

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
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
            glfwSetCursorPos(window, width() / 2, height() / 2);

        double mouse_x, mouse_y;
        glfwGetCursorPos(window, &mouse_x, &mouse_y);
        camera.move_vision((float)mouse_x, (float)mouse_y, (float)width(), (float)height());
        glfwSetCursorPos(window, width() / 2, height() / 2);
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

void Window::main_loop()
{
    /*
    std::vector<Vertex> vertices =
    {
        // front
        Vertex{glm::vec3(0.5f,  0.5f, 0.5f), glm::vec3(1.0f, 0.0f, 0.0f), glm::vec2(1.0f, 1.0f), glm::vec3(0.0f, 0.0f, 1.0f)},   // top right
        Vertex{glm::vec3(0.5f, -0.5f, 0.5f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec2(1.0f, 0.0f), glm::vec3(0.0f, 0.0f, 1.0f)},   // bottom right
        Vertex{glm::vec3(-0.5f, -0.5f, 0.5f), glm::vec3(0.0f, 0.0f, 1.0f), glm::vec2(0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 1.0f)}, // bottom left
        Vertex{glm::vec3(-0.5f,  0.5f, 0.5f), glm::vec3(1.0f, 1.0f, 0.0f), glm::vec2(0.0f, 1.0f), glm::vec3(0.0f, 0.0f, 1.0f)}, // top left
        // right
        Vertex{glm::vec3(0.5f, -0.5f, 0.5f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec2(0.0f, 0.0f), glm::vec3(1.0f, 0.0f, 0.0f)},   // bottom right
        Vertex{glm::vec3(0.5f, -0.5f, -0.5f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec2(1.0f, 0.0f), glm::vec3(1.0f, 0.0f, 0.0f)},  // back bottom right
        Vertex{glm::vec3(0.5f,  0.5f, -0.5f), glm::vec3(1.0f, 0.0f, 0.0f), glm::vec2(1.0f, 1.0f), glm::vec3(1.0f, 0.0f, 0.0f)},  // back top right
        Vertex{glm::vec3(0.5f,  0.5f, 0.5f), glm::vec3(1.0f, 0.0f, 0.0f), glm::vec2(0.0f, 1.0f), glm::vec3(1.0f, 0.0f, 0.0f)},   // top right
        // left
        Vertex{glm::vec3(-0.5f, -0.5f, -0.5f), glm::vec3(0.0f, 0.0f, 1.0f), glm::vec2(0.0f, 0.0f), glm::vec3(-1.0f, 0.0f, 0.0f)}, // back bottom left
        Vertex{glm::vec3(-0.5f, -0.5f, 0.5f), glm::vec3(0.0f, 0.0f, 1.0f), glm::vec2(1.0f, 0.0f), glm::vec3(-1.0f, 0.0f, 0.0f)},  // bottom left
        Vertex{glm::vec3(-0.5f,  0.5f, 0.5f), glm::vec3(1.0f, 1.0f, 0.0f), glm::vec2(1.0f, 1.0f), glm::vec3(-1.0f, 0.0f, 0.0f)},  // top left
        Vertex{glm::vec3(-0.5f,  0.5f, -0.5f), glm::vec3(1.0f, 1.0f, 0.0f), glm::vec2(0.0f, 1.0f), glm::vec3(-1.0f, 0.0f, 0.0f)}, // back top left
        // top
        Vertex{glm::vec3(-0.5f,  0.5f, 0.5f), glm::vec3(1.0f, 1.0f, 0.0f), glm::vec2(0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f)},  // top left
        Vertex{glm::vec3(0.5f,  0.5f, 0.5f), glm::vec3(1.0f, 0.0f, 0.0f), glm::vec2(1.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f)},   // top right
        Vertex{glm::vec3(0.5f,  0.5f, -0.5f), glm::vec3(1.0f, 0.0f, 0.0f), glm::vec2(1.0f, 1.0f), glm::vec3(0.0f, 1.0f, 0.0f)},  // back top right
        Vertex{glm::vec3(-0.5f,  0.5f, -0.5f), glm::vec3(1.0f, 1.0f, 0.0f), glm::vec2(0.0f, 1.0f), glm::vec3(0.0f, 1.0f, 0.0f)}, // back top left
        // bottom
        Vertex{glm::vec3(-0.5f, -0.5f, -0.5f), glm::vec3(0.0f, 0.0f, 1.0f), glm::vec2(0.0f, 0.0f), glm::vec3(0.0f, -1.0f, 0.0f)}, // back bottom left
        Vertex{glm::vec3(0.5f, -0.5f, -0.5f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec2(1.0f, 0.0f), glm::vec3(0.0f, -1.0f, 0.0f)},  // back bottom right
        Vertex{glm::vec3(0.5f, -0.5f, 0.5f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec2(1.0f, 1.0f), glm::vec3(0.0f, -1.0f, 0.0f)},   // bottom right
        Vertex{glm::vec3(-0.5f, -0.5f, 0.5f), glm::vec3(0.0f, 0.0f, 1.0f), glm::vec2(0.0f, 1.0f), glm::vec3(0.0f, -1.0f, 0.0f)},  // bottom left
        // back
        Vertex{glm::vec3(0.5f, -0.5f, -0.5f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec2(0.0f, 0.0f), glm::vec3(0.0f, 0.0f, -1.0f)},  // back bottom right
        Vertex{glm::vec3(-0.5f, -0.5f, -0.5f), glm::vec3(0.0f, 0.0f, 1.0f), glm::vec2(1.0f, 0.0f), glm::vec3(0.0f, 0.0f, -1.0f)}, // back bottom left
        Vertex{glm::vec3(-0.5f,  0.5f, -0.5f), glm::vec3(1.0f, 1.0f, 0.0f), glm::vec2(1.0f, 1.0f), glm::vec3(0.0f, 0.0f, -1.0f)}, // back top left
        Vertex{glm::vec3(0.5f,  0.5f, -0.5f), glm::vec3(1.0f, 0.0f, 0.0f), glm::vec2(0.0f, 1.0f), glm::vec3(0.0f, 0.0f, -1.0f)}   // back top right
    };

    std::vector<GLuint> indices = {
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

    std::vector<Vertex> floor_v = {
        Vertex{glm::vec3(-1.0f, 0.0f, 1.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec2(0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f)},
        Vertex{glm::vec3(1.0f, 0.0f, 1.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec2(0.0f, 1.0f), glm::vec3(0.0f, 1.0f, 0.0f)},
        Vertex{glm::vec3(-1.0f, 0.0f, -1.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec2(1.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f)},
        Vertex{glm::vec3(1.0f, 0.0f, -1.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec2(1.0f, 1.0f), glm::vec3(0.0f, 1.0f, 0.0f)},
    };

    std::vector<GLuint> floor_indices = {
        0, 1, 2,
        1, 2, 3
    };

    std::vector<Vertex> light_vertices =
    {
        // front
        Vertex{glm::vec3(0.5f,  0.5f, 0.5f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec2(1.0f, 1.0f)},   // top right
        Vertex{glm::vec3(0.5f, -0.5f, 0.5f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec2(1.0f, 0.0f)},   // bottom right
        Vertex{glm::vec3(-0.5f, -0.5f, 0.5f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec2(0.0f, 0.0f)},  // bottom left
        Vertex{glm::vec3(-0.5f,  0.5f, 0.5f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec2(0.0f, 1.0f)},  // top left
        // right
        Vertex{glm::vec3(0.5f, -0.5f, 0.5f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec2(0.0f, 0.0f)},   // bottom right
        Vertex{glm::vec3(0.5f, -0.5f, -0.5f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec2(1.0f, 0.0f)},  // back bottom right
        Vertex{glm::vec3(0.5f,  0.5f, -0.5f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec2(1.0f, 1.0f)},  // back top right
        Vertex{glm::vec3(0.5f,  0.5f, 0.5f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec2(0.0f, 1.0f)},   // top right
        // left
        Vertex{glm::vec3(-0.5f, -0.5f, -0.5f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec2(0.0f, 0.0f)}, // back bottom left
        Vertex{glm::vec3(-0.5f, -0.5f, 0.5f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec2(1.0f, 0.0f)},  // bottom left
        Vertex{glm::vec3(-0.5f,  0.5f, 0.5f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec2(1.0f, 1.0f)},  // top left
        Vertex{glm::vec3(-0.5f,  0.5f, -0.5f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec2(0.0f, 1.0f)}, // back top left
        // top
        Vertex{glm::vec3(-0.5f,  0.5f, 0.5f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec2(0.0f, 0.0f)},  // top left
        Vertex{glm::vec3(0.5f,  0.5f, 0.5f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec2(1.0f, 0.0f)},   // top right
        Vertex{glm::vec3(0.5f,  0.5f, -0.5f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec2(1.0f, 1.0f)},  // back top right
        Vertex{glm::vec3(-0.5f,  0.5f, -0.5f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec2(0.0f, 1.0f)}, // back top left
        // bottom
        Vertex{glm::vec3(-0.5f, -0.5f, -0.5f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec2(0.0f, 0.0f)}, // back bottom left
        Vertex{glm::vec3(0.5f, -0.5f, -0.5f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec2(1.0f, 0.0f)},  // back bottom right
        Vertex{glm::vec3(0.5f, -0.5f, 0.5f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec2(1.0f, 1.0f)},   // bottom right
        Vertex{glm::vec3(-0.5f, -0.5f, 0.5f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec2(0.0f, 1.0f)},  // bottom left
        // back
        Vertex{glm::vec3(0.5f, -0.5f, -0.5f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec2(0.0f, 0.0f)},  // back bottom right
        Vertex{glm::vec3(-0.5f, -0.5f, -0.5f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec2(1.0f, 0.0f)}, // back bottom left
        Vertex{glm::vec3(-0.5f,  0.5f, -0.5f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec2(1.0f, 1.0f)}, // back top left
        Vertex{glm::vec3(0.5f,  0.5f, -0.5f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec2(0.0f, 1.0f)}   // back top right
    };

    std::vector<GLuint> light_indices = {
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

    Texture tex0("./resources/textures/wall.jpg", "diffuse", 0);
    if (!tex0.loaded)
        std::cerr << "Error when loading texture" << std::endl;

    Texture tex1("./resources/textures/planks.png", "diffuse", 2);
    if (!tex1.loaded)
        std::cerr << "Error when loading texture" << std::endl;

    Texture floor_spec("./resources/textures/planksSpec.png", "specular", 3);
    if (!floor_spec.loaded)
        std::cerr << "Error when loading texture" << std::endl;

    Mesh body(vertices, indices, {tex0});
    Mesh sun(light_vertices, light_indices, {});
    Mesh floor(floor_v, floor_indices, {tex1, floor_spec});
    */

    Model m("./resources/models/dino/Triceratops.obj");
    Entity ent;
    ent.add_model(m);

    Shader shader_program("./resources/shaders/vertex_shader.txt",
                          "./resources/shaders/fragment_shader.txt");

    shader_program.activate();
    shader_program.set_uniform_float("ambient", 0.05f);
    shader_program.set_uniform_float4("light_color", 1.0f, 1.0f, 1.0f, 1.0f);
    shader_program.set_uniform_float3("light_pos", 0.0f, 0.0f, 0.0f);
    while (!should_close())
    {
        glfwPollEvents();
        process_input();

        glClearColor(_color.r, _color.g, _color.b, _color.opacity);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        shader_program.set_uniform_float3("camera_pos", camera.pos.x, camera.pos.y, camera.pos.z);

        double now = glfwGetTime();

        glm::mat4 view = glm::lookAt(camera.pos, camera.pos + camera.orientation, camera.up);
        glm::mat4 projection = glm::perspective(glm::radians(camera.fov), (float)width() / height(), 0.1f, 1000.0f);

        shader_program.set_uniform_matrix4("camera", projection * view);

        /*
        glm::mat4 model = glm::mat4(1.0f);
        model = glm::scale(model, glm::vec3(0.25f, 0.25f, 0.25f));

        // disable light normals for the light emissor
        shader_program.set_uniform_int("is_light_color_set", 0);

        sun.draw(shader_program, model);

        model = glm::mat4(1.0f);
        model = glm::scale(model, glm::vec3(0.3f, 0.3f, 0.3f));
        model = glm::translate(model, glm::vec3(8.0f * sin(now / 3), 0.0f, -3.0f + 8.0f * cos(now / 3)));
        model = glm::rotate(model, glm::radians(23.5f), glm::vec3(0.0f, 0.0f, 1.0f));
        model = glm::rotate(model, (float)now / 2, glm::vec3(0.0f, 1.0f, 0.0f));

        // enable light normals for light receivers
        shader_program.set_uniform_int("is_light_color_set", 1);

        body.draw(shader_program, model);

        model = glm::mat4(1.0f);
        model = glm::translate(model, glm::vec3(0.0f, -0.5f, 0.0f));

        shader_program.set_uniform_int("is_light_color_set", 1);

        floor.draw(shader_program, model);
        */

        ent.set_matrix(0, glm::rotate(glm::mat4(1.0f), (float)now * sinf(now), glm::vec3(0.0f, 1.0f, 0.0f)));
        ent.draw(shader_program);

        glfwSwapBuffers(window);
    }

    shader_program.destroy();
    // tex0.destroy();
    // tex1.destroy();
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
