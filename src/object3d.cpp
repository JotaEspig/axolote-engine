#include <string>

#include <GL/gl.h>
#include <glm/glm.hpp>

#include <axolote/object3d.hpp>
#include <axolote/model.hpp>

namespace axolote
{

Object3D::Object3D()
{
    pos = glm::mat4(1.0f);
}

Object3D::Object3D(const glm::mat4 &mat)
{
    pos = mat;
}

Object3D Object3D::from_model_file(const glm::mat4 &mat, std::string path,
                                   const glm::vec3 &color)
{
    Object3D o(mat);
    o.load_model(path, color);
    return o;
}

void Object3D::load_model(std::string path, const glm::vec3 &color)
{
    Object3D::color = color;
    Model::load_model(path);
}

void Object3D::draw(Shader &shader)
{
    Model::draw(shader, pos);
}

} // namespace axolote
