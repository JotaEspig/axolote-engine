#include <string>

#include <axolote/mesh.hpp>
#include <axolote/vao.hpp>
#include <axolote/vbo.hpp>
#include <axolote/ebo.hpp>
#include <axolote/structs.hpp>

using namespace axolote;

Mesh::Mesh(std::vector<Vertex> _vertices, std::vector<GLuint> _indices,
     Texture _texture, Texture _specular_map)
{
    vertices = _vertices;
    indices = _indices;
    texture = _texture;
    specular_map = _specular_map;


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

void Mesh::draw(Shader &shader)
{
    shader.activate();
    vao.bind();

    if (texture.loaded)
    {
        shader.set_uniform_int("is_tex_set", 1);
        shader.set_uniform_int("tex", texture.unit);
    }
    else
        shader.set_uniform_int("is_tex_set", 0);

    if (specular_map.loaded)
    {
        shader.set_uniform_int("is_specular_map_set", 1);
        shader.set_uniform_int("tex_specular_map", specular_map.unit);
    }
    else
        shader.set_uniform_int("is_specular_map_set", 0);

    texture.activate();
    texture.bind();
    specular_map.activate();
    specular_map.bind();

    glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);

    vao.unbind();
}

void Mesh::destroy()
{
    vao.destroy();
    vbo.destroy();
    ebo.destroy();
}
