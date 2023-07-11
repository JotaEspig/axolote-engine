#pragma once

#include <GL/gl.h>
#include <glm/glm.hpp>

namespace axolote
{
    class Shader
    {
    public:
        GLuint id;
        Shader(const char *vertex_file, const char *fragment_file);

        void set_uniform_int(const char *uniform_name, int value);
        void set_uniform_matrix4(const char *uniform_name, glm::mat4 matrix);
        void activate();
        void destroy();
    };
}
