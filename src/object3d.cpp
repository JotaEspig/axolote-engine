#include <string>

#include <GL/gl.h>
#include <glm/glm.hpp>

#include <axolote/object3d.hpp>
#include <axolote/model.hpp>

#define UNUSED(x) (void)(x)

namespace axolote
{

Object3D::Object3D() :
    pos{1.0f}
{
}

Object3D::Object3D(const glm::mat4 &mat) :
    pos{mat}
{
}

Object3D::Object3D(const std::vector<Vertex> &vertices,
                   const std::vector<GLuint> &indices,
                   const std::vector<Texture> &textures, const glm::mat4 &mat) :
    Model{vertices, indices, textures},
    pos{mat}
{
}

Object3D::Object3D(std::string path, const glm::vec3 &color, const glm::mat4 &mat) :
    Object3D{mat}
{
    load_model(path, color);
}

void Object3D::load_model(std::string path, const glm::vec3 &color)
{
    Model::color = color;
    Model::load_model(path);
}

void Object3D::draw()
{
    Model::draw(pos);
}

void Object3D::draw(const glm::mat4 &mat)
{
    UNUSED(mat);
    draw();
}

} // namespace axolote
