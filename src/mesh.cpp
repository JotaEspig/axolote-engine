#include <string>

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
    vao.unbind();
    vbo.unbind();
    ebo.unbind();
}

Mesh::~Mesh()
{
    destroy();
}

void Mesh::draw(Shader &shader)
{
    shader.activate();
    vao.bind();

    if (textures.size() > 0)
        shader.set_uniform_int("is_tex_set", 1);
    else
        shader.set_uniform_int("is_tex_set", 0);

    size_t i = 0;
    for (auto e : textures)
    {
        int slot = e.slot - GL_TEXTURE0;
        std::string tex_uniform = "tex" + std::to_string(i);
        shader.set_uniform_int(tex_uniform.c_str(), slot);
        e.activate();
        e.bind();
        ++i;
    }

    glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);

    vao.unbind();
}

void Mesh::destroy()
{
    vao.destroy();
    vbo.destroy();
    ebo.destroy();
}
