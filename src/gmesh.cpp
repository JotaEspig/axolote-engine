#include <cstddef>
#include <memory>
#include <string>
#include <vector>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "axolote/gl/ebo.hpp"
#include "axolote/gl/shader.hpp"
#include "axolote/gl/texture.hpp"
#include "axolote/gl/vbo.hpp"
#include "axolote/gmesh.hpp"
#include "axolote/mesh.hpp"
#include "axolote/structs.hpp"

#define UNUSED(x) (void)(x)

namespace axolote {

GMesh::GMesh() {
}

GMesh::GMesh(const Mesh &mesh) :
  GMesh{mesh.vertices, mesh.indices, mesh.textures} {
}

GMesh::GMesh(
    const std::vector<Vertex> &vertices, const std::vector<GLuint> &indices,
    const std::vector<std::shared_ptr<gl::Texture>> &textures
) :
  Mesh(vertices, indices, textures) {
    _vao = gl::VAO::create();
    _vao->bind();
    _vbo = gl::VBO::create(vertices);
    _vbo->bind();
    _ebo = gl::EBO::create(indices);
    _ebo->bind();

    _vao->link_attrib(
        _vbo, 0, 3, GL_FLOAT, sizeof(Vertex), (void *)(offsetof(Vertex, pos))
    );
    _vao->link_attrib(
        _vbo, 1, 4, GL_FLOAT, sizeof(Vertex), (void *)(offsetof(Vertex, color))
    );
    _vao->link_attrib(
        _vbo, 2, 2, GL_FLOAT, sizeof(Vertex), (void *)(offsetof(Vertex, tex_UV))
    );
    _vao->link_attrib(
        _vbo, 3, 3, GL_FLOAT, sizeof(Vertex), (void *)(offsetof(Vertex, normal))
    );
    _vao->unbind();
    _vbo->unbind();
    _ebo->unbind();
}

std::shared_ptr<gl::VAO> GMesh::vao() const {
    return _vao;
}

std::shared_ptr<gl::VBO> GMesh::vbo() const {
    return _vbo;
}

std::shared_ptr<gl::EBO> GMesh::ebo() const {
    return _ebo;
}

void GMesh::bind_shader(std::shared_ptr<gl::Shader> shader_program) {
    _shader = shader_program;
}

std::vector<std::shared_ptr<gl::Shader>> GMesh::get_shaders() const {
    return {_shader};
}

void GMesh::update(double dt) {
    UNUSED(dt);
}

void GMesh::default_draw_binds(const glm::mat4 &mat) {
    _shader->activate();
    _vao->bind();

    _shader->set_uniform_int("axolote_is_specular_map_set", 0);
    if (textures.size() > 0)
        _shader->set_uniform_int("axolote_is_tex_set", 1);
    else
        _shader->set_uniform_int("axolote_is_tex_set", 0);

    unsigned int num_diffuse = 0;
    unsigned int num_specular = 0;
    // set default invalid values to textures to prevent a Mesh
    // to use a texture from another Mesh
    // TODO search if there's a better solution than this
    // i.e. set to 99 (a unused texture id)
    _shader->set_uniform_int("axolote_diffuse0", 99);
    _shader->set_uniform_int("axolote_specular0", 99);

    for (std::shared_ptr<gl::Texture> t : textures) {
        std::string num;
        std::string type = t->type();
        if (type == "diffuse")
            num = std::to_string(num_diffuse++);
        else if (type == "specular") {
            num = std::to_string(num_specular++);
            _shader->set_uniform_int("axolote_is_specular_map_set", 1);
        }
        else {
            num = std::to_string(num_diffuse++);
            type = "diffuse";
        }

        t->bind();
        t->activate();
        _shader->set_uniform_int(("axolote_" + type + num).c_str(), t->unit());
    }

    _shader->set_uniform_matrix4("axolote_model", mat);
}

void GMesh::default_draw_unbinds() {
    _vao->unbind();
    for (std::shared_ptr<gl::Texture> t : textures) {
        t->unbind();
    }
    _shader->set_uniform_int("axolote_diffuse0", 99);
    _shader->set_uniform_int("axolote_specular0", 99);
}

void GMesh::draw() {
    draw(glm::mat4(1.0f));
}

void GMesh::draw(const glm::mat4 &mat) {
    default_draw_binds(mat);
    _vao->bind();
    glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
    _vao->unbind();
    default_draw_unbinds();
}

} // namespace axolote
