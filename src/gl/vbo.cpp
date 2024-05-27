#include "axolote/gl/vbo.hpp"
#include "axolote/glad/glad.h"

namespace axolote {

namespace gl {

VBO::VBO() {
}

void VBO::bind() {
    glBindBuffer(GL_ARRAY_BUFFER, id);
}

void VBO::unbind() {
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void VBO::destroy() {
    glDeleteBuffers(1, &id);
}

} // namespace gl

} // namespace axolote
