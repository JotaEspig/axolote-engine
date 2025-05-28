#include "axolote/glad/glad.h"

#include "axolote/gl/ubo.hpp"
#include "axolote/utils.hpp"

namespace axolote {
namespace gl {

GLuint UBO::id() const {
    return _id;
}

void UBO::bind() {
    glBindBuffer(GL_UNIFORM_BUFFER, _id);
}

void UBO::unbind() {
    glBindBuffer(GL_UNIFORM_BUFFER, 0);
}

void UBO::buffer_data(std::size_t size, const void *data, GLenum usage) {
    bind();
    glBufferData(GL_UNIFORM_BUFFER, size, data, usage);
    debug(DebugType::INFO, "UBO buffer data: %u, size: %zu bytes", _id, size);
}

void UBO::buffer_sub_data(
    std::size_t offset, std::size_t size, const void *data
) {
    bind();
    glBufferSubData(GL_UNIFORM_BUFFER, offset, size, data);
}

void UBO::destroy() {
    glDeleteBuffers(1, &_id);
    debug(DebugType::INFO, "UBO destroyed: %u", _id);
}

GLuint UBO::binding_point() const {
    return _binding_point;
}

void UBO::set_binding_point(GLuint binding_point) {
    _binding_point = binding_point;
    glBindBufferBase(GL_UNIFORM_BUFFER, binding_point, _id);
    debug(
        DebugType::INFO, "UBO binding point set: %u, id: %u", binding_point, _id
    );
}

UBO::UBO() {
    glGenBuffers(1, &_id);
    debug(DebugType::INFO, "UBO created: %u", _id);
}

void UBO::Deleter::operator()(UBO *ubo) {
    ubo->destroy();
    delete ubo;
}

} // namespace gl
} // namespace axolote
