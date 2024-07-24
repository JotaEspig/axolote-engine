#include <memory>

#include "axolote/gl/vao.hpp"
#include "axolote/gl/vbo.hpp"
#include "axolote/glad/glad.h"

namespace axolote {

namespace gl {

GLuint VAO::id() const {
    return _id;
}

void VAO::link_attrib(
    std::shared_ptr<VBO> vbo, GLuint layout, GLuint num_components, GLenum type,
    GLsizeiptr size, void *offset
) {
    bind();
    vbo->bind();
    glVertexAttribPointer(layout, num_components, type, GL_FALSE, size, offset);
    glEnableVertexAttribArray(layout);
}

void VAO::attrib_divisor(
    std::shared_ptr<VBO> vbo, GLuint index, GLuint divisor
) {
    bind();
    vbo->bind();
    glVertexAttribDivisor(index, divisor);
}

void VAO::bind() {
    glBindVertexArray(_id);
}

void VAO::unbind() {
    glBindVertexArray(0);
}

VAO::VAO() {
    glGenVertexArrays(1, &_id);
}

void VAO::destroy() {
    glDeleteVertexArrays(1, &_id);
}

} // namespace gl

} // namespace axolote
