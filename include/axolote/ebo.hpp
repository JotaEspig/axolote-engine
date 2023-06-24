#pragma once

#include <GL/gl.h>

namespace axolote
{
    class EBO
    {
    public:
        GLuint id;
        EBO(GLuint *indices, GLsizeiptr size);

        void bind();
        void unbind();
        void destroy();
    };
}
