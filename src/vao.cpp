#include <glad/glad.h>

#include <axolote/vao.hpp>
#include <axolote/vbo.hpp>

namespace axolote
{

VAO::VAO()
{
    glGenVertexArrays(1, &id);
}

void VAO::link_attrib(VBO &vbo, GLuint layout, GLuint num_components,
                      GLenum type, GLsizeiptr stribe, void *offset)
{
    vbo.bind();
    glVertexAttribPointer(layout, num_components, type, GL_FALSE, stribe, offset);
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

} // namespace axolote
