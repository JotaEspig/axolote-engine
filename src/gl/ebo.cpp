#include <vector>

#include <glad/glad.h>

#include <GL/gl.h>

#include <axolote/gl/ebo.hpp>

namespace axolote {

namespace gl {

EBO::EBO() {
}

EBO::EBO(const EBO &ebo) :
  id{ebo.id} {
}

EBO::EBO(EBO &&ebo) :
  id{std::move(ebo.id)} {
}

EBO::EBO(const std::vector<GLuint> &indices) {
    glGenBuffers(1, &id);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, id);
    glBufferData(
        GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(GLuint),
        indices.data(), GL_STATIC_DRAW
    );
}

void EBO::bind() {
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, id);
}

void EBO::unbind() {
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void EBO::destroy() {
    glDeleteBuffers(1, &id);
}

void EBO::operator=(const EBO &ebo) {
    id = ebo.id;
}

void EBO::operator=(EBO &&ebo) {
    id = std::move(ebo.id);
}

} // namespace gl

} // namespace axolote
