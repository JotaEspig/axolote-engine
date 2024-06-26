#include <string>

#include <glm/glm.hpp>

#include "axolote/gl/shader.hpp"
#include "axolote/gmesh.hpp"
#include "axolote/gmodel.hpp"
#include "axolote/model.hpp"

#define UNUSED(x) (void)(x)

namespace axolote {

GModel::GModel() {
}

GModel::GModel(std::string path, const glm::vec3 &color) {
    load_model(path, color);
}

void GModel::bind_shader(const gl::Shader &shader) {
    for (GMesh &e : meshes)
        e.bind_shader(shader);
};

gl::Shader GModel::get_shader() const {
    for (const GMesh &e : meshes) {
        return e.get_shader();
    }
    return gl::Shader();
}

void GModel::update(double dt) {
    UNUSED(dt);
}

void GModel::draw() {
    draw(glm::mat4(1.0f));
}

void GModel::draw(const glm::mat4 &mat) {
    for (GMesh e : meshes)
        e.draw(mat);
}

void GModel::load_model(std::string path, const glm::vec3 &color) {
    meshes.clear();
    Model m{path, color};
    for (const Mesh &mesh : m.meshes) {
        meshes.push_back(mesh);
    }
}

} // namespace axolote
