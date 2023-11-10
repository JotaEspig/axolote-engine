#include <glad/glad.h>

#include <axolote/vao.hpp>
#include <axolote/vbo.hpp>

namespace axolote
{

VAO::VAO()
{
    glGenVertexArrays(1, &id);
}

VAO::VAO(const VAO &vao) :
    id{vao.id}
{
}

VAO::VAO(VAO &&vao) :
    id{std::move(vao.id)}
{
}

void VAO::link_attrib(VBO &vbo, GLuint layout, GLuint num_components,
                      GLenum type, GLsizeiptr size, void *offset)
{
    vbo.bind();
    glVertexAttribPointer(layout, num_components, type, GL_FALSE, size, offset);
    glEnableVertexAttribArray(layout);
    vbo.unbind();
}

void VAO::bind()
{
    glBindVertexArray(id);
}

void VAO::unbind()
{
    glBindVertexArray(0);
}

void VAO::destroy()
{
    glDeleteVertexArrays(1, &id);
}

void VAO::operator=(const VAO &vao)
{
    id = vao.id;
}

void VAO::operator=(VAO &&vao)
{
    id = std::move(vao.id);
}

} // namespace axolote
