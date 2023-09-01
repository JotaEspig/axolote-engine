#include <glm/glm.hpp>

#include <axolote/object2d.hpp>
#include <axolote/mesh.hpp>

namespace axolote
{

Object2D::Object2D()
{
}

Object2D::Object2D(Mesh _mesh, glm::mat4 mat)
{
    mesh = _mesh;
    pos = mat;
}

void Object2D::draw(Shader &shader)
{
    mesh.draw(shader, pos);
}

} // namespace axolote
