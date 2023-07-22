#include <iostream>
#include <string>
#include <vector>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/quaternion.hpp>

#include <axolote/mesh.hpp>
#include <axolote/vao.hpp>
#include <axolote/vbo.hpp>
#include <axolote/ebo.hpp>
#include <axolote/structs.hpp>

using namespace axolote;

Mesh::Mesh(std::vector<Vertex> _vertices, std::vector<GLuint> _indices,
     std::vector<Texture> _textures)
{
    vertices = _vertices;
    indices = _indices;
    textures = _textures;

    vao.bind();
    vbo = VBO(vertices);
    ebo = EBO(indices);

    vao.link_attrib(vbo, 0, 3, GL_FLOAT, sizeof(Vertex), (void *)0);
    vao.link_attrib(vbo, 1, 3, GL_FLOAT, sizeof(Vertex), (void *)(3 * sizeof(float)));
    vao.link_attrib(vbo, 2, 2, GL_FLOAT, sizeof(Vertex), (void *)(6 * sizeof(float)));
    vao.link_attrib(vbo, 3, 3, GL_FLOAT, sizeof(Vertex), (void *)(8 * sizeof(float)));
    vao.unbind();
    vbo.unbind();
    ebo.unbind();
}

Mesh::~Mesh()
{
    destroy();
}

void Mesh::draw(Shader &shader, glm::mat4 matrix, glm::vec3 translation,
                glm::quat rotation, glm::vec3 scale)
{
    shader.activate();

    shader.set_uniform_int("is_simple_mesh", is_simple_mesh);

    if (textures.size() > 0)
        shader.set_uniform_int("is_tex_set", 1);
    else
        shader.set_uniform_int("is_tex_set", 0);

    unsigned int num_diffuse = 0;
    unsigned int num_specular = 0;

    for (size_t i = 0; i < textures.size(); i++)
    {
        std::string num;
        std::string type = textures[i].type;
        if (type == "diffuse")
            num = std::to_string(num_diffuse++);
        else if (type == "specular")
            num = std::to_string(num_specular++);

        shader.set_uniform_int((type + num).c_str(), textures[i].unit);
        textures[i].activate();
        textures[i].bind();
    }

    glm::mat4 trans = glm::mat4(1.0f);
    glm::mat4 rot = glm::mat4(1.0f);
    glm::mat4 sca = glm::mat4(1.0f);
    trans = glm::translate(trans, translation);
    rot = glm::mat4_cast(rotation);
    sca = glm::scale(sca, scale);
    shader.set_uniform_matrix4("translation", trans);
    shader.set_uniform_matrix4("rotation", rot);
    shader.set_uniform_matrix4("scale", sca);
    shader.set_uniform_matrix4("model", matrix);

    vao.bind();
    vbo.bind();
    ebo.bind();
    glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);

    vao.unbind();
}

void Mesh::destroy()
{
    vao.destroy();
    vbo.destroy();
    ebo.destroy();
}
