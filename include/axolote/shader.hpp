#pragma once

#include <GL/gl.h>

namespace axolote
{
    class Shader
    {
    public:
        GLuint id;
        Shader(const char *vertex_file, const char *fragment_file);

        void set_uniform_int(const char *uniform_name, int value);
        void activate();
        void destroy();
    };
}
