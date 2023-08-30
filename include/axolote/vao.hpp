#pragma once

#include <GL/gl.h>

#include <axolote/vbo.hpp>

namespace axolote
{

class VAO
{
public:
    GLuint id;

    VAO();

    void link_attrib(VBO &vbo, GLuint layout, GLuint num_components,
                     GLenum type, GLsizeiptr stribe, void *offset);
    void bind();
    void unbind();
    void destroy();
};

} // namespace axolote
