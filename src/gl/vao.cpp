#include <glad/glad.h>

#include <axolote/gl/vao.hpp>
#include <axolote/gl/vbo.hpp>

namespace axolote
{

namespace gl
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

void VAO::link_attrib(
    VBO &vbo, GLuint layout, GLuint num_components, GLenum type,
    GLsizeiptr size, void *offset
)
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

} // namespace gl

} // namespace axolote
