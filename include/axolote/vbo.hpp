#pragma once

#include <vector>

#include <GL/gl.h>
#include <glm/glm.hpp>

namespace axolote
{
    struct Vertex
    {
        glm::vec3 position;
        glm::vec3 color;
        glm::vec2 tex_UV;
    };

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
}
