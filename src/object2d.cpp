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
    glDisable(GL_CULL_FACE);
    mesh.draw(shader, pos);
    glEnable(GL_CULL_FACE);
}

} // namespace axolote
