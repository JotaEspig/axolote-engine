#pragma once

#include <vector>

#include <GL/gl.h>
#include <glm/glm.hpp>

#include <axolote/structs.hpp>

namespace axolote
{

class VBO
{
public:
    GLuint id;

    VBO() = default;
    VBO(std::vector<Vertex> vertices);

    void bind();
    void unbind();
    void destroy();
};

} // namespace axolote
