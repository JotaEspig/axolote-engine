#include <memory>
#include <string>

#include <glm/glm.hpp>
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/norm.hpp>

#include "axolote/glad/glad.h"

#include "axolote/gmodel.hpp"
#include "axolote/object3d.hpp"

#define UNUSED(x) (void)(x)

namespace axolote {

Object3D::Object3D() {
    set_matrix(glm::mat4{1.0f});
}

Object3D::Object3D(const glm::mat4 &mat) {
    set_matrix(mat);
}

Object3D::Object3D(
    const std::vector<Vertex> &vertices, const std::vector<GLuint> &indices,
    const std::vector<std::shared_ptr<gl::Texture>> &textures,
    const glm::mat4 &mat
) :
  gmodel{std::make_shared<GModel>()} {
    set_matrix(mat);
    gmodel->meshes.push_back(GMesh{vertices, indices, textures});
}

Object3D::Object3D(
    std::string path, const glm::vec4 &color, const glm::mat4 &mat
) {
    set_matrix(mat);
    load_model(path, color);
}

void Object3D::load_model(std::string path, const glm::vec4 &color) {
    gmodel->load_model(path, color);
}

void Object3D::set_matrix(const glm::mat4 &mat) {
    _model_matrix = mat;
    _normal_matrix = glm::transpose(glm::inverse(mat));
}

glm::mat4 Object3D::get_matrix() const {
    return _model_matrix;
}

glm::mat4 Object3D::get_normal_matrix() const {
    return _normal_matrix;
}

void Object3D::bind_shader(std::shared_ptr<gl::Shader> shader_program) {
    gmodel->bind_shader(shader_program);
}

std::vector<std::shared_ptr<gl::Shader>> Object3D::get_shaders() const {
    return gmodel->get_shaders();
}

void Object3D::update(double dt) {
    UNUSED(dt);
}

void Object3D::draw() {
    auto shaders = get_shaders();
    for (auto &shader : shaders) {
        shader->set_uniform_int("axolote_is_affected_by_lights_set", 1);
        shader->set_uniform_int(
            "axolote_is_affected_by_lights", is_affected_by_lights
        );
        shader->set_uniform_matrix4("axolote_normal_matrix", _normal_matrix);
    }
    gmodel->draw(_model_matrix);
    for (auto &shader : shaders)
        shader->set_uniform_int("axolote_is_affected_by_lights_set", 0);
}

void Object3D::draw(const glm::mat4 &mat) {
    UNUSED(mat);
    draw();
}

} // namespace axolote
