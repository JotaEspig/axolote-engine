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
        GLuint unit;
        bool loaded;
        Texture(const char *image, GLenum _type, GLuint _unit, GLenum format,
                GLenum pixel_type);

        void activate();
        void bind();
        void unbind();
        void destroy();
    };
}
