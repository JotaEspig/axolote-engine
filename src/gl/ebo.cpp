#include <vector>

#include "axolote/gl/ebo.hpp"
#include "axolote/glad/glad.h"

namespace axolote {

namespace gl {

GLuint EBO::id() const {
    return _id;
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
}

EBO::EBO() {
    glGenBuffers(1, &_id);
}

EBO::EBO(const std::vector<GLuint> &indices) :
  EBO{} {
    bind();
    buffer_data(
        indices.size() * sizeof(GLuint), indices.data(), GL_STATIC_DRAW
    );
}

void EBO::destroy() {
    glDeleteBuffers(1, &_id);
}

} // namespace gl

} // namespace axolote
