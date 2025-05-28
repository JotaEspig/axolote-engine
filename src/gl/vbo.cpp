#include "axolote/glad/glad.h"

#include "axolote/gl/vbo.hpp"
#include "axolote/utils.hpp"

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
    debug(DebugType::INFO, "VBO buffer data: %u, size: %zu bytes", _id, size);
}

void VBO::buffer_sub_data(
    std::size_t start_pos, std::size_t size, const void *data
) {
    bind();
    glBufferSubData(GL_ARRAY_BUFFER, start_pos, size, data);
}

void VBO::destroy() {
    GLuint id = _id;
    glDeleteBuffers(1, &_id);
    debug(DebugType::INFO, "VBO destroyed: %u", id);
}

VBO::VBO() {
    glGenBuffers(1, &_id);
    debug(DebugType::INFO, "VBO created: %u", _id);
}

void VBO::Deleter::operator()(VBO *vbo) {
    vbo->destroy();
    delete vbo;
}

} // namespace gl

} // namespace axolote
