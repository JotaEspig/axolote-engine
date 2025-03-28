#include <string>

#include <glm/glm.hpp>

#include "axolote/gl/shader.hpp"
#include "axolote/gmodel.hpp"
#include "axolote/model.hpp"

#define UNUSED(x) (void)(x)

namespace axolote {

GModel::GModel() {
}

GModel::GModel(std::string path, const glm::vec4 &color) {
    load_model(path, color);
}

void GModel::load_model(std::string path, const glm::vec4 &color) {
    meshes.clear();
    Model m{path, color};
    for (const Mesh &mesh : m.meshes) {
        meshes.push_back(mesh);
    }
}

void GModel::bind_shader(std::shared_ptr<gl::Shader> shader) {
    for (GMesh &e : meshes)
        e.bind_shader(shader);
};

std::vector<std::shared_ptr<gl::Shader>> GModel::get_shaders() const {
    std::vector<std::shared_ptr<gl::Shader>> v;
    for (GMesh e : meshes) {
        auto x = e.get_shaders();
        v.insert(v.end(), x.begin(), x.end());
    }
    return v;
}

void GModel::update(double absolute_time, double delta_time) {
    UNUSED(absolute_time);
    UNUSED(delta_time);
}

void GModel::draw() {
    draw(glm::mat4(1.0f));
}

void GModel::draw(const glm::mat4 &mat) {
    for (GMesh e : meshes)
        e.draw(mat);
}

} // namespace axolote
