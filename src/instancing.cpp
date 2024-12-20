#include "axolote/instancing.hpp"

namespace axolote {

Instancing::Instancing() {
}

Instancing::Instancing(const GMesh &mesh) :
  mesh(mesh) {
}

void Instancing::add_instanced_mat4_array(
    const std::uint8_t location, const std::vector<glm::mat4> &data
) {
    if (data.size() == 0) {
        return;
    }

    assert(data.size() == element_count);

    auto vao = mesh.vao();
    vao->bind();

    auto vbo = gl::VBO::create();
    vbo->bind();
    vbo->buffer_data(
        data.size() * sizeof(glm::mat4), data.data(), GL_DYNAMIC_DRAW
    );
    vao->link_attrib(vbo, location, 4, GL_FLOAT, sizeof(glm::mat4), (void *)0);
    vao->link_attrib(
        vbo, location + 1, 4, GL_FLOAT, sizeof(glm::mat4),
        (void *)(sizeof(glm::vec4))
    );
    vao->link_attrib(
        vbo, location + 2, 4, GL_FLOAT, sizeof(glm::mat4),
        (void *)(2 * sizeof(glm::vec4))
    );
    vao->link_attrib(
        vbo, location + 3, 4, GL_FLOAT, sizeof(glm::mat4),
        (void *)(3 * sizeof(glm::vec4))
    );
    vao->attrib_divisor(vbo, location, 1);
    vao->attrib_divisor(vbo, location + 1, 1);
    vao->attrib_divisor(vbo, location + 2, 1);
    vao->attrib_divisor(vbo, location + 3, 1);

    _instanced_array_vbos[location] = vbo;
    vao->unbind();
    vbo->unbind();
}

void Instancing::update_instanced_mat4_array(
    const std::uint8_t location, const std::vector<glm::mat4> &data
) {
    if (data.size() == 0) {
        return;
    }

    assert(data.size() == element_count);

    auto vbo = _instanced_array_vbos[location];
    vbo->bind();
    glBufferSubData(
        GL_ARRAY_BUFFER, 0, data.size() * sizeof(glm::mat4), data.data()
    );
    vbo->unbind();
}

void Instancing::bind_shader(std::shared_ptr<gl::Shader> shader) {
    mesh.bind_shader(shader);
}

std::vector<std::shared_ptr<gl::Shader>> Instancing::get_shaders() const {
    return mesh.get_shaders();
}

void Instancing::update(double dt) {
}

void Instancing::draw() {
    get_shaders()[0]->use();
    mesh.vao()->bind();
    glDrawElementsInstanced(
        GL_TRIANGLES, mesh.indices.size(), GL_UNSIGNED_INT, 0, element_count
    );
    mesh.vao()->unbind();
}

void Instancing::draw(const glm::mat4 &mat) {
    (void)mat;
    draw();
}

} // namespace axolote
