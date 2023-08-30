#pragma once

#include <vector>

#include <GL/gl.h>

namespace axolote
{

class EBO
{
    public:
    GLuint id;

    EBO() = default;
    EBO(std::vector<GLuint> indices);

    void bind();
    void unbind();
    void destroy();
};

} // namespace axolote
