#include <cstddef>
#include <vector>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/string_cast.hpp>

#include "axolote/utils.hpp"
#include "axolote/utils/grid.hpp"

struct CustomVertex {
    glm::vec3 pos;
    glm::vec4 color;
};

namespace axolote {

namespace utils {

Grid::Grid() {
    build_mesh();
}

Grid::Grid(
    std::uint8_t size, std::uint8_t step, bool is_3d, const glm::vec4 &color
) :
  is_3d(is_3d),
  size{size},
  step{step},
  color{color} {
    build_mesh();
}

void Grid::build_mesh() {
    std::vector<CustomVertex> vertices;
    std::vector<GLuint> indices;

    if (is_3d) {
        for (int x = -size; x <= size; x += step) {
            for (int y = -size; y <= size; y += step) {
                for (int z = -size; z <= size; z += step) {
                    vertices.push_back({glm::vec3{x, y, -size}, color});
                    vertices.push_back({glm::vec3{x, y, size}, color});
                    vertices.push_back({glm::vec3{x, -size, z}, color});
                    vertices.push_back({glm::vec3{x, size, z}, color});
                    vertices.push_back({glm::vec3{-size, y, z}, color});
                    vertices.push_back({glm::vec3{size, y, z}, color});
                }
            }
        }

        for (std::size_t i = 0; i < vertices.size(); i++) {
            indices.push_back(i);
        }
    }
    else {
        debug("2D grid is not implemented yet");
    }

    _vao = gl::VAO::create();
    _vbo = gl::VBO::create(vertices);
    _ebo = gl::EBO::create(indices);

    _vao->bind();
    _vbo->bind();
    _ebo->bind();

    _vao->link_attrib(_vbo, 0, 3, GL_FLOAT, sizeof(CustomVertex), (void *)0);
    _vao->link_attrib(
        _vbo, 1, 4, GL_FLOAT, sizeof(CustomVertex),
        (void *)offsetof(CustomVertex, color)
    );

    _vao->unbind();
    _vbo->unbind();
    _ebo->unbind();
}

void Grid::bind_shader(std::shared_ptr<gl::Shader> shader_program) {
    _shader = shader_program;
}

std::vector<std::shared_ptr<gl::Shader>> Grid::get_shaders() const {
    return {_shader};
}

void Grid::update(double delta_t) {
    (void)delta_t;
    if (camera_pos.x > 0) {
        pos.x = (int)camera_pos.x - (int)camera_pos.x % step;
    }
    else {
        pos.x = (int)camera_pos.x - (int)camera_pos.x % step - step;
    }
    if (camera_pos.y > 0) {
        pos.y = (int)camera_pos.y - (int)camera_pos.y % step;
    }
    else {
        pos.y = (int)camera_pos.y - (int)camera_pos.y % step - step;
    }
    if (is_3d) {
        if (camera_pos.z > 0) {
            pos.z = (int)camera_pos.z - (int)camera_pos.z % step;
        }
        else {
            pos.z = (int)camera_pos.z - (int)camera_pos.z % step - step;
        }
    }
    model_mat = glm::translate(glm::mat4{1.0f}, pos);
}

void Grid::draw() {
    glLineWidth(2.0f);
    _shader->use();
    _vao->bind();
    _shader->set_uniform_matrix4("axolote_model", model_mat);
    _shader->set_uniform_int("axolote_grid_size", size);
    _shader->set_uniform_float("axolote_grid_fading_factor", fading_factor);
    glDrawElements(GL_LINES, _ebo->size(), GL_UNSIGNED_INT, 0);
    _vao->unbind();
    glLineWidth(1.0f);
}

void Grid::draw(const glm::mat4 &mat) {
    (void)mat;
    draw();
}

} // namespace utils

} // namespace axolote
