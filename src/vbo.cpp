#include <vector>

#include <glad/glad.h>

#include <axolote/vbo.hpp>
#include <axolote/structs.hpp>

namespace axolote
{

VBO::VBO()
{
}

VBO::VBO(const VBO &vbo) :
    id{vbo.id}
{
}

VBO::VBO(VBO &&vbo) :
    id{std::move(vbo.id)}
{
}

VBO::VBO(const std::vector<Vertex> &vertices)
{
    glGenBuffers(1, &id);
    glBindBuffer(GL_ARRAY_BUFFER, id);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), vertices.data(), GL_STATIC_DRAW);
}

void VBO::bind()
{
    glBindBuffer(GL_ARRAY_BUFFER, id);
}

void VBO::unbind()
{
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void VBO::destroy()
{
    glDeleteBuffers(1, &id);
}

void VBO::operator=(const VBO &vbo)
{
    id = vbo.id;
}

void VBO::operator=(VBO &&vbo)
{
    id = std::move(vbo.id);
}

} // namespace axolote
