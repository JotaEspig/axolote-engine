#include <vector>

#include "axolote/glad/glad.h"

#include "axolote/gl/ebo.hpp"

#include "axolote/utils.hpp"

namespace axolote {

namespace gl {

GLuint EBO::id() const {
    return _id;
}

std::size_t EBO::size() const {
    return _size;
}

void EBO::bind() {
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _id);
}

void EBO::unbind() {
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void EBO::buffer_data(std::size_t size, const void *data, GLenum usage) {
    bind();
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, data, usage);
    _size = size;
}

void EBO::destroy() {
    debug("EBO destroyed: %u", _id);
    glDeleteBuffers(1, &_id);
}

EBO::EBO() {
    glGenBuffers(1, &_id);
    debug("EBO created: %u", _id);
}

EBO::EBO(const std::vector<GLuint> &indices) :
  EBO{} {
    bind();
    buffer_data(
        indices.size() * sizeof(GLuint), indices.data(), GL_STATIC_DRAW
    );
}

void EBO::Deleter::operator()(EBO *ebo) {
    ebo->destroy();
    delete ebo;
}

} // namespace gl

} // namespace axolote
