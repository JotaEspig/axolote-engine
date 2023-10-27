#include <iostream>
#include <sstream>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <axolote/engine.hpp>

class MineCubes : public axolote::Entity
{
public:
    void update(double time) override;
};

void MineCubes::update(double time)
{
    for (int i = 0; i < 30; ++i)
    {
        for (int j = 0; j < 30; ++j)
        {
            glm::mat4 mat = glm::mat4(1.0f);
            mat = glm::translate(mat, glm::vec3(i, sin(time + .2f * (i + j)) * 3, j));
            set_matrix(30 * i + j, mat);
        }
    }
}

class App : public axolote::Window
{
public:
    void main_loop();
};

void App::main_loop()
{
    camera.speed = 0.3f;
    camera.sensitivity = 10000.0f;

    // TODO Fix the indices order (error when culling face)
    std::vector<axolote::Vertex> vertices =
    {
        // front
        axolote::Vertex{glm::vec3(0.5f,  0.5f, 0.5f), glm::vec3(1.0f, 0.0f, 0.0f), glm::vec2(1.0f, 1.0f), glm::vec3(0.0f, 0.0f, 1.0f)},   // top right
        axolote::Vertex{glm::vec3(0.5f, -0.5f, 0.5f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec2(1.0f, 0.0f), glm::vec3(0.0f, 0.0f, 1.0f)},   // bottom right
        axolote::Vertex{glm::vec3(-0.5f, -0.5f, 0.5f), glm::vec3(0.0f, 0.0f, 1.0f), glm::vec2(0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 1.0f)}, // bottom left
        axolote::Vertex{glm::vec3(-0.5f,  0.5f, 0.5f), glm::vec3(1.0f, 1.0f, 0.0f), glm::vec2(0.0f, 1.0f), glm::vec3(0.0f, 0.0f, 1.0f)}, // top left
        // right
        axolote::Vertex{glm::vec3(0.5f, -0.5f, 0.5f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec2(0.0f, 0.0f), glm::vec3(1.0f, 0.0f, 0.0f)},   // bottom right
        axolote::Vertex{glm::vec3(0.5f, -0.5f, -0.5f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec2(1.0f, 0.0f), glm::vec3(1.0f, 0.0f, 0.0f)},  // back bottom right
        axolote::Vertex{glm::vec3(0.5f,  0.5f, -0.5f), glm::vec3(1.0f, 0.0f, 0.0f), glm::vec2(1.0f, 1.0f), glm::vec3(1.0f, 0.0f, 0.0f)},  // back top right
        axolote::Vertex{glm::vec3(0.5f,  0.5f, 0.5f), glm::vec3(1.0f, 0.0f, 0.0f), glm::vec2(0.0f, 1.0f), glm::vec3(1.0f, 0.0f, 0.0f)},   // top right
        // left
        axolote::Vertex{glm::vec3(-0.5f, -0.5f, -0.5f), glm::vec3(0.0f, 0.0f, 1.0f), glm::vec2(0.0f, 0.0f), glm::vec3(-1.0f, 0.0f, 0.0f)}, // back bottom left
        axolote::Vertex{glm::vec3(-0.5f, -0.5f, 0.5f), glm::vec3(0.0f, 0.0f, 1.0f), glm::vec2(1.0f, 0.0f), glm::vec3(-1.0f, 0.0f, 0.0f)},  // bottom left
        axolote::Vertex{glm::vec3(-0.5f,  0.5f, 0.5f), glm::vec3(1.0f, 1.0f, 0.0f), glm::vec2(1.0f, 1.0f), glm::vec3(-1.0f, 0.0f, 0.0f)},  // top left
        axolote::Vertex{glm::vec3(-0.5f,  0.5f, -0.5f), glm::vec3(1.0f, 1.0f, 0.0f), glm::vec2(0.0f, 1.0f), glm::vec3(-1.0f, 0.0f, 0.0f)}, // back top left
        // top
        axolote::Vertex{glm::vec3(-0.5f,  0.5f, 0.5f), glm::vec3(1.0f, 1.0f, 0.0f), glm::vec2(0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f)},  // top left
        axolote::Vertex{glm::vec3(0.5f,  0.5f, 0.5f), glm::vec3(1.0f, 0.0f, 0.0f), glm::vec2(1.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f)},   // top right
        axolote::Vertex{glm::vec3(0.5f,  0.5f, -0.5f), glm::vec3(1.0f, 0.0f, 0.0f), glm::vec2(1.0f, 1.0f), glm::vec3(0.0f, 1.0f, 0.0f)},  // back top right
        axolote::Vertex{glm::vec3(-0.5f,  0.5f, -0.5f), glm::vec3(1.0f, 1.0f, 0.0f), glm::vec2(0.0f, 1.0f), glm::vec3(0.0f, 1.0f, 0.0f)}, // back top left
        // bottom
        axolote::Vertex{glm::vec3(-0.5f, -0.5f, -0.5f), glm::vec3(0.0f, 0.0f, 1.0f), glm::vec2(0.0f, 0.0f), glm::vec3(0.0f, -1.0f, 0.0f)}, // back bottom left
        axolote::Vertex{glm::vec3(0.5f, -0.5f, -0.5f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec2(1.0f, 0.0f), glm::vec3(0.0f, -1.0f, 0.0f)},  // back bottom right
        axolote::Vertex{glm::vec3(0.5f, -0.5f, 0.5f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec2(1.0f, 1.0f), glm::vec3(0.0f, -1.0f, 0.0f)},   // bottom right
        axolote::Vertex{glm::vec3(-0.5f, -0.5f, 0.5f), glm::vec3(0.0f, 0.0f, 1.0f), glm::vec2(0.0f, 1.0f), glm::vec3(0.0f, -1.0f, 0.0f)},  // bottom left
        // back
        axolote::Vertex{glm::vec3(0.5f, -0.5f, -0.5f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec2(0.0f, 0.0f), glm::vec3(0.0f, 0.0f, -1.0f)},  // back bottom right
        axolote::Vertex{glm::vec3(-0.5f, -0.5f, -0.5f), glm::vec3(0.0f, 0.0f, 1.0f), glm::vec2(1.0f, 0.0f), glm::vec3(0.0f, 0.0f, -1.0f)}, // back bottom left
        axolote::Vertex{glm::vec3(-0.5f,  0.5f, -0.5f), glm::vec3(1.0f, 1.0f, 0.0f), glm::vec2(1.0f, 1.0f), glm::vec3(0.0f, 0.0f, -1.0f)}, // back top left
        axolote::Vertex{glm::vec3(0.5f,  0.5f, -0.5f), glm::vec3(1.0f, 0.0f, 0.0f), glm::vec2(0.0f, 1.0f), glm::vec3(0.0f, 0.0f, -1.0f)}   // back top right
    };

    std::vector<GLuint> indices = {
        //front face
        0, 2, 1,
        0, 3, 2,
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

    std::vector<axolote::Vertex> mine_vertices =
    {
        // front
        axolote::Vertex{glm::vec3(0.5f,  0.5f, 0.5f), glm::vec3(1.0f, 0.0f, 0.0f), glm::vec2(0.5f, 2.0f / 3), glm::vec3(0.0f, 0.0f, 1.0f)},   // top right
        axolote::Vertex{glm::vec3(0.5f, -0.5f, 0.5f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec2(0.5f, 1.0f / 3), glm::vec3(0.0f, 0.0f, 1.0f)},   // bottom right
        axolote::Vertex{glm::vec3(-0.5f, -0.5f, 0.5f), glm::vec3(0.0f, 0.0f, 1.0f), glm::vec2(0.25f, 1.0f / 3), glm::vec3(0.0f, 0.0f, 1.0f)}, // bottom left
        axolote::Vertex{glm::vec3(-0.5f,  0.5f, 0.5f), glm::vec3(1.0f, 1.0f, 0.0f), glm::vec2(0.25f, 2.0f / 3), glm::vec3(0.0f, 0.0f, 1.0f)}, // top left
        // right
        axolote::Vertex{glm::vec3(0.5f, -0.5f, 0.5f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec2(0.5f, 1.0f / 3), glm::vec3(1.0f, 0.0f, 0.0f)},   // bottom right
        axolote::Vertex{glm::vec3(0.5f, -0.5f, -0.5f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec2(0.75f, 1.0f / 3), glm::vec3(1.0f, 0.0f, 0.0f)},  // back bottom right
        axolote::Vertex{glm::vec3(0.5f,  0.5f, -0.5f), glm::vec3(1.0f, 0.0f, 0.0f), glm::vec2(0.75f, 2.0f / 3), glm::vec3(1.0f, 0.0f, 0.0f)},  // back top right
        axolote::Vertex{glm::vec3(0.5f,  0.5f, 0.5f), glm::vec3(1.0f, 0.0f, 0.0f), glm::vec2(0.5f, 2.0f / 3), glm::vec3(1.0f, 0.0f, 0.0f)},   // top right
        // left
        axolote::Vertex{glm::vec3(-0.5f, -0.5f, -0.5f), glm::vec3(0.0f, 0.0f, 1.0f), glm::vec2(0.0f, 1.0f / 3), glm::vec3(-1.0f, 0.0f, 0.0f)}, // back bottom left
        axolote::Vertex{glm::vec3(-0.5f, -0.5f, 0.5f), glm::vec3(0.0f, 0.0f, 1.0f), glm::vec2(0.25f, 1.0f / 3), glm::vec3(-1.0f, 0.0f, 0.0f)},  // bottom left
        axolote::Vertex{glm::vec3(-0.5f,  0.5f, 0.5f), glm::vec3(1.0f, 1.0f, 0.0f), glm::vec2(0.25f, 2.0f / 3), glm::vec3(-1.0f, 0.0f, 0.0f)},  // top left
        axolote::Vertex{glm::vec3(-0.5f,  0.5f, -0.5f), glm::vec3(1.0f, 1.0f, 0.0f), glm::vec2(0.0f, 2.0f / 3), glm::vec3(-1.0f, 0.0f, 0.0f)}, // back top left
        // top
        axolote::Vertex{glm::vec3(-0.5f,  0.5f, 0.5f), glm::vec3(1.0f, 1.0f, 0.0f), glm::vec2(0.5f, 2.0f / 3), glm::vec3(0.0f, 1.0f, 0.0f)},  // top left
        axolote::Vertex{glm::vec3(0.5f,  0.5f, 0.5f), glm::vec3(1.0f, 0.0f, 0.0f), glm::vec2(0.25f, 2.0f / 3), glm::vec3(0.0f, 1.0f, 0.0f)},   // top right
        axolote::Vertex{glm::vec3(0.5f,  0.5f, -0.5f), glm::vec3(1.0f, 0.0f, 0.0f), glm::vec2(0.25f, 1.0f), glm::vec3(0.0f, 1.0f, 0.0f)},  // back top right
        axolote::Vertex{glm::vec3(-0.5f,  0.5f, -0.5f), glm::vec3(1.0f, 1.0f, 0.0f), glm::vec2(0.5f, 1.0f), glm::vec3(0.0f, 1.0f, 0.0f)}, // back top left
        // bottom
        axolote::Vertex{glm::vec3(-0.5f, -0.5f, -0.5f), glm::vec3(0.0f, 0.0f, 1.0f), glm::vec2(0.25f, 0.0f), glm::vec3(0.0f, -1.0f, 0.0f)}, // back bottom left
        axolote::Vertex{glm::vec3(0.5f, -0.5f, -0.5f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec2(0.5f, 0.0f), glm::vec3(0.0f, -1.0f, 0.0f)},  // back bottom right
        axolote::Vertex{glm::vec3(0.5f, -0.5f, 0.5f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec2(0.5f, 1.0f / 3), glm::vec3(0.0f, -1.0f, 0.0f)},   // bottom right
        axolote::Vertex{glm::vec3(-0.5f, -0.5f, 0.5f), glm::vec3(0.0f, 0.0f, 1.0f), glm::vec2(0.25f, 1.0f / 3), glm::vec3(0.0f, -1.0f, 0.0f)},  // bottom left
        // back
        axolote::Vertex{glm::vec3(0.5f, -0.5f, -0.5f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec2(0.75f, 1.0f / 3), glm::vec3(0.0f, 0.0f, -1.0f)},  // back bottom right
        axolote::Vertex{glm::vec3(-0.5f, -0.5f, -0.5f), glm::vec3(0.0f, 0.0f, 1.0f), glm::vec2(1.0f, 1.0f / 3), glm::vec3(0.0f, 0.0f, -1.0f)}, // back bottom left
        axolote::Vertex{glm::vec3(-0.5f,  0.5f, -0.5f), glm::vec3(1.0f, 1.0f, 0.0f), glm::vec2(1.0f, 2.0f / 3), glm::vec3(0.0f, 0.0f, -1.0f)}, // back top left
        axolote::Vertex{glm::vec3(0.5f,  0.5f, -0.5f), glm::vec3(1.0f, 0.0f, 0.0f), glm::vec2(0.75f, 2.0f / 3), glm::vec3(0.0f, 0.0f, -1.0f)}   // back top right
    };

    std::vector<axolote::Vertex> floor_v = {
        axolote::Vertex{glm::vec3(-1.0f, 0.0f, 1.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec2(0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f)},
        axolote::Vertex{glm::vec3(1.0f, 0.0f, 1.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec2(0.0f, 1.0f), glm::vec3(0.0f, 1.0f, 0.0f)},
        axolote::Vertex{glm::vec3(-1.0f, 0.0f, -1.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec2(1.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f)},
        axolote::Vertex{glm::vec3(1.0f, 0.0f, -1.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec2(1.0f, 1.0f), glm::vec3(0.0f, 1.0f, 0.0f)},
    };

    std::vector<GLuint> floor_indices = {
        2, 0, 1,
        2, 1, 3
    };

    std::vector<axolote::Vertex> light_vertices =
    {
        // front
        axolote::Vertex{glm::vec3(0.5f,  0.5f, 0.5f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec2(1.0f, 1.0f)},   // top right
        axolote::Vertex{glm::vec3(0.5f, -0.5f, 0.5f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec2(1.0f, 0.0f)},   // bottom right
        axolote::Vertex{glm::vec3(-0.5f, -0.5f, 0.5f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec2(0.0f, 0.0f)},  // bottom left
        axolote::Vertex{glm::vec3(-0.5f,  0.5f, 0.5f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec2(0.0f, 1.0f)},  // top left
        // right
        axolote::Vertex{glm::vec3(0.5f, -0.5f, 0.5f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec2(0.0f, 0.0f)},   // bottom right
        axolote::Vertex{glm::vec3(0.5f, -0.5f, -0.5f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec2(1.0f, 0.0f)},  // back bottom right
        axolote::Vertex{glm::vec3(0.5f,  0.5f, -0.5f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec2(1.0f, 1.0f)},  // back top right
        axolote::Vertex{glm::vec3(0.5f,  0.5f, 0.5f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec2(0.0f, 1.0f)},   // top right
        // left
        axolote::Vertex{glm::vec3(-0.5f, -0.5f, -0.5f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec2(0.0f, 0.0f)}, // back bottom left
        axolote::Vertex{glm::vec3(-0.5f, -0.5f, 0.5f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec2(1.0f, 0.0f)},  // bottom left
        axolote::Vertex{glm::vec3(-0.5f,  0.5f, 0.5f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec2(1.0f, 1.0f)},  // top left
        axolote::Vertex{glm::vec3(-0.5f,  0.5f, -0.5f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec2(0.0f, 1.0f)}, // back top left
        // top
        axolote::Vertex{glm::vec3(-0.5f,  0.5f, 0.5f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec2(0.0f, 0.0f)},  // top left
        axolote::Vertex{glm::vec3(0.5f,  0.5f, 0.5f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec2(1.0f, 0.0f)},   // top right
        axolote::Vertex{glm::vec3(0.5f,  0.5f, -0.5f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec2(1.0f, 1.0f)},  // back top right
        axolote::Vertex{glm::vec3(-0.5f,  0.5f, -0.5f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec2(0.0f, 1.0f)}, // back top left
        // bottom
        axolote::Vertex{glm::vec3(-0.5f, -0.5f, -0.5f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec2(0.0f, 0.0f)}, // back bottom left
        axolote::Vertex{glm::vec3(0.5f, -0.5f, -0.5f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec2(1.0f, 0.0f)},  // back bottom right
        axolote::Vertex{glm::vec3(0.5f, -0.5f, 0.5f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec2(1.0f, 1.0f)},   // bottom right
        axolote::Vertex{glm::vec3(-0.5f, -0.5f, 0.5f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec2(0.0f, 1.0f)},  // bottom left
        // back
        axolote::Vertex{glm::vec3(0.5f, -0.5f, -0.5f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec2(0.0f, 0.0f)},  // back bottom right
        axolote::Vertex{glm::vec3(-0.5f, -0.5f, -0.5f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec2(1.0f, 0.0f)}, // back bottom left
        axolote::Vertex{glm::vec3(-0.5f,  0.5f, -0.5f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec2(1.0f, 1.0f)}, // back top left
        axolote::Vertex{glm::vec3(0.5f,  0.5f, -0.5f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec2(0.0f, 1.0f)}   // back top right
    };

    axolote::Texture tex0("./resources/textures/pedro.png", "diffuse", 0);
    if (!tex0.loaded)
        std::cerr << "Error when loading texture" << std::endl;

    axolote::Texture tex1("./resources/textures/planks.png", "diffuse", 1);
    if (!tex1.loaded)
        std::cerr << "Error when loading texture" << std::endl;

    axolote::Texture tex2("./resources/textures/grass.png", "diffuse", 2);
    if (!tex2.loaded)
        std::cerr << "Error when loading texture" << std::endl;

    axolote::Texture floor_spec("./resources/textures/planksSpec.png", "specular", 3);
    if (!floor_spec.loaded)
        std::cerr << "Error when loading texture" << std::endl;

    axolote::Object3D body{vertices, indices, {tex0},
                           glm::translate(glm::mat4{1.0f},
                                          glm::vec3{5.0f, 1.0f, 0.0f})};
    axolote::Object3D sun{light_vertices, indices, {}, glm::mat4{1.0f}};

    glm::mat4 floor_m = glm::scale(glm::mat4{1.0f}, glm::vec3{3.0f, 3.0f, 3.0f});
    floor_m = glm::translate(floor_m, glm::vec3(-2.0f, -2.0f, 0.0f));
    axolote::Object3D floor{floor_v, floor_indices, {tex1, floor_spec}, floor_m};

    MineCubes mine_cubes;
    for (int i = 0; i < 30; ++i)
    {
        for (int j = 0; j < 30; ++j)
        {
            axolote::Object3D c{mine_vertices, indices, {tex2}, glm::mat4{1.0f}};
            mine_cubes.add_object(c, glm::mat4{1.0f});
        }
    }

    glm::mat4 mat = glm::translate(glm::mat4(1.0f), glm::vec3(15.0f, 0.5f, 15.0f));
    axolote::Object3D dino{mat};
    dino.load_model("./resources/models/dino/Triceratops.obj");

    axolote::Object3D m26{glm::translate(glm::mat4(1.0f), glm::vec3(-7.0f, 0.0f, 0.0f))};
    m26.load_model("./resources/models/m26/m26pershing_coh.obj");

    axolote::Shader shader_program("./resources/shaders/def_vertex_shader.glsl",
                                   "./resources/shaders/def_fragment_shader.glsl");

    shader_program.activate();
    shader_program.set_uniform_float("ambient", 0.05f);
    shader_program.set_uniform_float4("light_color", 1.0f, 1.0f, 1.0f, 1.0f);
    shader_program.set_uniform_float3("light_pos", 0.0f, 0.0f, 0.0f);

    body.bind_shader(shader_program);
    sun.bind_shader(shader_program);
    floor.bind_shader(shader_program);
    for (int i = 0; i < 30; ++i)
        for (int j = 0; j < 30; ++j)
            mine_cubes.bind_shader_at(30 * i + j, shader_program);
    dino.bind_shader(shader_program);
    m26.bind_shader(shader_program);

    axolote::Scene ctx{};
    ctx.add_drawable(sun);
    ctx.add_drawable(body);
    ctx.add_drawable(floor);
    ctx.add_drawable(&mine_cubes);
    ctx.add_drawable(dino);
    ctx.add_drawable(m26);
    std::string original_title = _title;
    double before = glfwGetTime();
    while (!should_close())
    {
        glfwPollEvents();

        double now = glfwGetTime();
        double dt = now - before;
        before = now;
        process_input(dt);

        glClearColor(_color.r, _color.g, _color.b, _color.opacity);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        ctx.camera = camera;
        ctx.update_camera((float)width() / height());
        ctx.update(now);

        std::stringstream sstr;
        sstr << original_title << " | " << (int)(1 / dt) << " fps";
        set_title(sstr.str());

        /*
        model = glm::mat4(1.0f);
        model = glm::scale(model, glm::vec3(0.3f, 0.3f, 0.3f));
        model = glm::translate(model, glm::vec3(8.0f * sin(now / 3), 0.0f, -3.0f + 8.0f * cos(now / 3)));
        model = glm::rotate(model, glm::radians(23.5f), glm::vec3(0.0f, 0.0f, 1.0f));
        model = glm::rotate(model, (float)now / 2, glm::vec3(0.0f, 1.0f, 0.0f));

        // enable light normals for light receivers
        shader_program.set_uniform_int("is_light_color_set", 1);

        body.set_matrix(0, model);
        body.draw(shader_program);

        model = glm::mat4(1.0f);
        model = glm::translate(model, glm::vec3(0.0f, -0.5f, 0.0f));

        shader_program.set_uniform_int("is_light_color_set", 1);

        floor.set_matrix(0, model);
        floor.draw(shader_program);
        shader_program.set_uniform_int("is_light_color_set", 0);

        */

        /*
        glDisable(GL_BLEND);
        dino.draw(shader_program);
        // cubes.draw(shader_program);
        glEnable(GL_BLEND);
        */
        shader_program.set_uniform_int("is_light_color_set", 1);

        //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
        // glDisable(GL_CULL_FACE);
        //
        // disable light normals for the light emissor
        shader_program.set_uniform_int("is_light_color_set", 0);
        ctx.render();

        // glEnable(GL_CULL_FACE);
        //glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

        glfwSwapBuffers(window);
    }

    shader_program.destroy();
    tex0.destroy();
    tex1.destroy();
    tex2.destroy();
    floor_spec.destroy();
}

int main(int argc, char **argv)
{
    std::cout << "hello world axolote engine!" << std::endl;
    auto w = App();
    w.set_title("Axolote Engine Test");
    w.set_width(600);
    w.set_height(600);
    w.set_color(0x10, 0x10, 0x10);
    w.main_loop();
    return 0;
}
