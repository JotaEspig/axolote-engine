#include <iostream>
#include <sstream>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <axolote/engine.hpp>

class App : public axolote::Window
{
public:
    void main_loop();
};

void App::main_loop()
{
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

    axolote::Texture tex("./resources/textures/grass.png", "diffuse", 2);
    if (!tex.loaded)
        std::cerr << "Error when loading texture" << std::endl;

    axolote::Mesh c(mine_vertices, indices, {tex});
    axolote::Entity mine_cubes;
    for (int i = 0; i < 30; ++i)
    {
        for (int j = 0; j < 30; ++j)
        {
            glm::mat4 mat = glm::mat4(1.0f);
            mat = glm::translate(mat, glm::vec3(i, 0.0f, j));
            mine_cubes.add_mesh(c, mat);
        }
    }

    axolote::Model m("./resources/models/dino/Triceratops.obj");
    axolote::Entity dino;
    glm::mat4 mat = glm::translate(glm::mat4(1.0f), glm::vec3(15.0f, 0.5f, 15.0f));
    dino.add_model(m, mat);

    axolote::Shader shader_program("./resources/shaders/def_vertex_shader.glsl",
                                   "./resources/shaders/def_fragment_shader.glsl");

    std::string original_title = _title;
    double before = glfwGetTime();
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    while (!should_close())
    {
        glfwPollEvents();
        process_input();

        glClearColor(_color.r, _color.g, _color.b, _color.opacity);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        shader_program.set_uniform_float3("camera_pos", camera.pos.x, camera.pos.y, camera.pos.z);

        double now = glfwGetTime();
        double dt = now - before;
        before = now;

        std::stringstream sstr;
        sstr << original_title << " | " << (int)(1 / dt) << " fps";
        set_title(sstr.str());

        glm::mat4 view = glm::lookAt(camera.pos, camera.pos + camera.orientation, camera.up);
        glm::mat4 projection = glm::perspective(glm::radians(camera.fov), (float)width() / height(), 0.1f, 1000.0f);

        shader_program.set_uniform_matrix4("projection", projection);
        shader_program.set_uniform_matrix4("view",view);

        for (int i = 0; i < 30; ++i)
        {
            for (int j = 0; j < 30; ++j)
            {
                glm::mat4 mat = glm::mat4(1.0f);
                mat = glm::translate(mat, glm::vec3(i, sin(now + .2f * (i + j)) * 3, j));
                mine_cubes.set_matrix(30 * i + j, mat);
            }
        }

        mine_cubes.draw(shader_program);
        glDisable(GL_BLEND);
        dino.draw(shader_program);
        glEnable(GL_BLEND);

        glfwSwapBuffers(window);
    }

    shader_program.destroy();
    tex.destroy();
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

