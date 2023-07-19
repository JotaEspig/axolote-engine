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
        void set_uniform_float(const char *uniform_name, float x);
        void set_uniform_float3(const char *uniform_name,
                                 float x, float y, float z);
        void set_uniform_float4(const char *uniform_name,
                                 float x, float y, float z, float w);
        void activate();
        void destroy();
    };
}
