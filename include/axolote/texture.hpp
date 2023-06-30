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
        GLenum type;
        GLenum slot;
        bool loaded;
        Texture(const char *image, GLenum _type, GLenum _slot, GLenum format,
                GLenum pixel_type);

        void activate();
        void bind();
        void unbind();
        void destroy();
    };
}
