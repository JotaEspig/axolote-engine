#pragma once

#include <GL/gl.h>

#include <axolote/shader.hpp>

using namespace axolote;

namespace axolote
{
    class Texture
    {
    public:
        GLuint id;
        const char *type;
        GLuint unit;
        bool loaded;
        Texture();
        Texture(const char *texture_filename, const char *tex_type, GLuint _unit);

        void activate();
        void bind();
        void unbind();
        void destroy();
    };
}
