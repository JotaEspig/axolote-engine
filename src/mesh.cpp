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

void Mesh::draw(Shader &shader, glm::mat4 matrix)
{
    shader.activate();
    vao.bind();

    if (textures.size() > 0)
        shader.set_uniform_int("is_tex_set", 1);
    else
        shader.set_uniform_int("is_tex_set", 0);

    unsigned int num_diffuse = 0;
    unsigned int num_specular = 0;
    // set default invalid values to textures to prevent a Mesh
    // to use a texture from another Mesh
    // TODO search if there's a better solution than this
    // i.e. set to 99 (a unused texture id)
    shader.set_uniform_int("diffuse0", 99);
    shader.set_uniform_int("specular0", 99);

    for (Texture t : textures)
    {
        std::string num;
        std::string type = t.type;
        if (type == "diffuse")
            num = std::to_string(num_diffuse++);
        else if (type == "specular")
            num = std::to_string(num_specular++);

        shader.set_uniform_int((type + num).c_str(), t.unit);
        t.activate();
        t.bind();
    }

    shader.set_uniform_matrix4("model", matrix);

    vao.bind();
    glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);

    for (Texture t : textures)
    {
        t.unbind();
    }
    vao.unbind();
}

void Mesh::destroy()
{
    vao.destroy();
    vbo.destroy();
    ebo.destroy();
}
