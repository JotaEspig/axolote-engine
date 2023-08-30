#pragma once

#include <string>

#include <GL/gl.h>

namespace axolote
{

class Texture
{
public:
    GLuint id;
    std::string type;
    GLuint unit;
    bool loaded;

    Texture();
    Texture(const char *texture_filename, std::string tex_type, GLuint _unit);

    void activate();
    void bind();
    void unbind();
    void destroy();
};

} // namespace axolote
