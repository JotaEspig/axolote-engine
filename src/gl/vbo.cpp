#include "axolote/gl/vbo.hpp"
#include "axolote/glad/glad.h"

namespace axolote {

namespace gl {

GLuint VBO::id() const {
    return _id;
}

void VBO::bind() {
    glBindBuffer(GL_ARRAY_BUFFER, _id);
}

void VBO::unbind() {
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void VBO::buffer_data(std::size_t size, const void *data, GLenum usage) {
    bind();
    glBufferData(GL_ARRAY_BUFFER, size, data, usage);
}

VBO::VBO() {
    glGenBuffers(1, &_id);
}

void VBO::destroy() {
    glDeleteBuffers(1, &_id);
}

} // namespace gl

} // namespace axolote
