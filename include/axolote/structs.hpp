#pragma once

#include <glm/glm.hpp>

namespace axolote
{

struct Vertex
{
    glm::vec3 position;
    glm::vec3 color;
    glm::vec2 tex_UV;
    glm::vec3 normal;
};

struct Color
{
    float r;
    float g;
    float b;
    float opacity;
};

} // namespace axolote
