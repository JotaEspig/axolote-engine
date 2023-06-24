#pragma once

#include <GL/gl.h>

namespace axolote
{
    class Shader
    {
    public:
        GLuint id;
        Shader(const char *vertex_file, const char *fragment_file);

        void activate();
        void destroy();
    };
}
