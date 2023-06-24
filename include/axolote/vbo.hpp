#pragma once

#include <GL/gl.h>

namespace axolote
{
    class VBO
    {
    public:
        GLuint id;
        VBO(GLfloat *vertices, GLsizeiptr size);

        void bind();
        void unbind();
        void destroy();
    };
}
