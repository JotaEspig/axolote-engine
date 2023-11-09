#include <string>

#include <GL/gl.h>
#include <glm/glm.hpp>

#include <axolote/object3d.hpp>
#include <axolote/model.hpp>

#define UNUSED(x) (void)(x)

namespace axolote
{

Object3D::Object3D() :
    model_mat{1.0f}
{
}

Object3D::Object3D(const Object3D &obj) :
    Model{obj},
    model_mat{obj.model_mat}
{
}

Object3D::Object3D(Object3D &&obj) :
    Model{obj},
    model_mat{obj.model_mat}
{
    obj.model_mat = glm::mat4(0.0f);
}

Object3D::Object3D(const glm::mat4 &mat) :
    model_mat{mat}
{
}

Object3D::Object3D(const std::vector<Vertex> &vertices,
                   const std::vector<GLuint> &indices,
                   const std::vector<Texture> &textures, const glm::mat4 &mat) :
    Model{vertices, indices, textures},
    model_mat{mat}
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

glm::mat4 Object3D::get_matrix() const
{
    return model_mat;
}

void Object3D::draw()
{
    Model::draw(model_mat);
}

void Object3D::draw(const glm::mat4 &mat)
{
    UNUSED(mat);
    draw();
}

void Object3D::operator=(const Object3D &obj)
{
    Model::operator=(obj);
    model_mat = obj.model_mat;
}

void Object3D::operator=(Object3D &&obj)
{
    Model::operator=(obj);
    model_mat = obj.model_mat;
    obj.model_mat = glm::mat4(0.0f);
}

} // namespace axolote
