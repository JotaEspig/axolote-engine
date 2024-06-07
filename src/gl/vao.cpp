#include "axolote/gl/vao.hpp"
#include "axolote/gl/vbo.hpp"
#include "axolote/glad/glad.h"

namespace axolote {

namespace gl {

VAO::VAO() {
    glGenVertexArrays(1, &id);
}

void VAO::link_attrib(
    VBO &vbo, GLuint layout, GLuint num_components, GLenum type,
    GLsizeiptr size, void *offset
) {
    bind();
    vbo.bind();
    glVertexAttribPointer(layout, num_components, type, GL_FALSE, size, offset);
    glEnableVertexAttribArray(layout);
    vbo.unbind();
    unbind();
}

void VAO::attrib_divisor(VBO &vbo, GLuint index, GLuint divisor) {
    bind();
    vbo.bind();
    glVertexAttribDivisor(index, divisor);
    vbo.unbind();
    unbind();
}

void VAO::bind() {
    glBindVertexArray(id);
}

void VAO::unbind() {
    glBindVertexArray(0);
}

void VAO::destroy() {
    glDeleteVertexArrays(1, &id);
}

} // namespace gl

} // namespace axolote
