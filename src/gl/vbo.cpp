#include "axolote/gl/vbo.hpp"
#include "axolote/glad/glad.h"

namespace axolote {

namespace gl {

VBO::VBO() {
    glGenBuffers(1, &id);
}

void VBO::bind() {
    glBindBuffer(GL_ARRAY_BUFFER, id);
}

void VBO::unbind() {
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void VBO::buffer_data(std::size_t size, const void *data, GLenum usage) {
    bind();
    glBufferData(GL_ARRAY_BUFFER, size, data, usage);
}

void VBO::destroy() {
    glDeleteBuffers(1, &id);
}

} // namespace gl

} // namespace axolote
