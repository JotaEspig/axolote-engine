#include <memory>
#include <string>

#include <GL/gl.h>
#include <glm/glm.hpp>

#include "axolote/gmodel.hpp"
#include "axolote/object3d.hpp"

#define UNUSED(x) (void)(x)

namespace axolote {

Object3D::Object3D() :
  model_mat{1.0f} {
}

Object3D::Object3D(const glm::mat4 &mat) :
  model_mat{mat} {
}

Object3D::Object3D(
    const std::vector<Vertex> &vertices, const std::vector<GLuint> &indices,
    const std::vector<gl::Texture> &textures, const glm::mat4 &mat
) :
  gmodel{std::make_shared<GModel>()},
  model_mat{mat} {
    gmodel->meshes.push_back(GMesh{vertices, indices, textures});
}

Object3D::Object3D(
    std::string path, const glm::vec3 &color, const glm::mat4 &mat
) :
  model_mat{mat} {
    load_model(path, color);
}

void Object3D::load_model(std::string path, const glm::vec3 &color) {
    gmodel->load_model(path, color);
}

glm::mat4 Object3D::get_matrix() const {
    return model_mat;
}

void Object3D::bind_shader(const gl::Shader &shader_program) {
    gmodel->bind_shader(shader_program);
}

gl::Shader Object3D::get_shader() const {
    return gmodel->get_shader();
}

void Object3D::update(double dt) {
    UNUSED(dt);
}

void Object3D::draw() {
    gmodel->draw(model_mat);
}

void Object3D::draw(const glm::mat4 &mat) {
    UNUSED(mat);
    draw();
}

} // namespace axolote
