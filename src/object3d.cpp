#include <string>

#include <GL/gl.h>
#include <glm/glm.hpp>

#include <axolote/object3d.hpp>
#include <axolote/model.hpp>

namespace axolote
{

Object3D::Object3D()
{
}

Object3D::Object3D(glm::mat4 mat)
{
    pos = mat;
}

void Object3D::load_model(std::string path, glm::vec3 color)
{
    Object3D::color = color;
    Model::load_model(path);
}

void Object3D::draw(Shader &shader)
{
    Model::draw(shader, pos);
}

} // namespace axolote
