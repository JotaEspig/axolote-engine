#pragma once

#include <axolote/shader.hpp>
#include <glm/glm.hpp>

#include <axolote/mesh.hpp>

namespace axolote
{

class Object2D
{
    Mesh mesh;
    glm::mat4 pos = glm::mat4(1.0f);

public:
    Object2D();
    Object2D(Mesh _mesh, glm::mat4 mat = glm::mat4(1.0f));
    void draw(Shader &shader);
};

} // namespace axolote
