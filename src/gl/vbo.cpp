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
}

void VBO::destroy() {
    debug("VBO destroyed: %u\n", _id);
    glDeleteBuffers(1, &_id);
}

VBO::VBO() {
    glGenBuffers(1, &_id);
    debug("VBO created: %u\n", _id);
}

void VBO::Deleter::operator()(VBO *vbo) {
    vbo->destroy();
    delete vbo;
}

} // namespace gl

} // namespace axolote
