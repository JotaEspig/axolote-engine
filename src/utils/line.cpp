#define _USE_MATH_DEFINES
#include <cmath>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "axolote/structs.hpp"
#include "axolote/utils/line.hpp"

#define UNUSED(x) (void)(x)

namespace axolote {

namespace utils {

Line::Line(
    const glm::vec3 &point, const glm::vec3 &direction_vector, float length,
    float thickness, const glm::vec4 &color, float line_quality
) :
  start{point},
  dir_vec{glm::normalize(direction_vector)},
  length{length},
  thickness{thickness},
  color{color},
  line_quality{line_quality}
{
    is_affected_by_lights = false;
    build_mesh();
}

void Line::build_mesh() {
    std::vector<Vertex> vs;
    std::vector<GLuint> es;

    float step = 2 * M_PI / line_quality;

    glm::vec3 bottom_base_center = glm::vec3{0.0f};
    glm::vec3 top_base_center = glm::vec3{0.0f, 1.0f, 0.0f};
    int counter = 0;
    for (float i = 0; i < 2 * M_PI; i += step / 2) {
        // bottom base face
        glm::vec3 bottom_p1{
            std::cos(i) * 0.5f, bottom_base_center.y,
            std::sin(i) * 0.5f
        };
        glm::vec3 bottom_p2{
            std::cos(i + step / 2) * 0.5f, bottom_base_center.y,
            std::sin(i + step / 2) * 0.5f
        };
        vs.push_back(Vertex{bottom_base_center, color, {}, {}});
        vs.push_back(Vertex{bottom_p1, color, {}, {}});
        vs.push_back(Vertex{bottom_p2, color, {}, {}});
        es.push_back(3 * counter + 0);
        es.push_back(3 * counter + 1);
        es.push_back(3 * counter + 2);
        ++counter;

        // top base face
        glm::vec3 top_p1{
            std::cos(i) * 0.5f, top_base_center.y, std::sin(i) * 0.5f
        };
        glm::vec3 top_p2{
            std::cos(i + step / 2) * 0.5f, top_base_center.y,
            std::sin(i + step / 2) * 0.5f
        };
        vs.push_back(Vertex{top_p1, color, {}, {}});
        vs.push_back(Vertex{top_base_center, color, {}, {}});
        vs.push_back(Vertex{top_p2, color, {}, {}});
        es.push_back(3 * counter + 0);
        es.push_back(3 * counter + 1);
        es.push_back(3 * counter + 2);
        ++counter;

        // lateral face
        vs.push_back(Vertex{top_p1, color, {}, {}});
        vs.push_back(Vertex{top_p2, color, {}, {}});
        vs.push_back(Vertex{bottom_p1, color, {}, {}});
        es.push_back(3 * counter + 0);
        es.push_back(3 * counter + 1);
        es.push_back(3 * counter + 2);
        ++counter;
        vs.push_back(Vertex{top_p2, color, {}, {}});
        vs.push_back(Vertex{bottom_p2, color, {}, {}});
        vs.push_back(Vertex{bottom_p1, color, {}, {}});
        es.push_back(3 * counter + 0);
        es.push_back(3 * counter + 1);
        es.push_back(3 * counter + 2);
        ++counter;
    }

    for (unsigned long i = 0; i < vs.size(); i += 3) {
        glm::vec3 normal
            = glm::cross(vs[i + 1].pos - vs[i].pos, vs[i + 2].pos - vs[i].pos);
        vs[i].normal += normal;
        vs[i + 1].normal += normal;
        vs[i + 2].normal += normal;
    }

    for (auto &v : vs)
        v.normal = glm::normalize(v.normal);

    gmodel->meshes.push_back({vs, es, {}});
}

void Line::set_end(const glm::vec3 &end) {
    // Calculate new direction
    glm::vec3 direction = end - start;
    float distance = glm::length(direction);
    assert((distance > 0.0f));

    // Set new direction and length
    dir_vec = glm::normalize(direction);
    length = distance;
}

glm::vec3 Line::get_end() {
    return start + dir_vec * length;
}

void Line::draw() {
    Object3D::draw();
}

void Line::update(double dt) {
    UNUSED(dt);
    glm::mat4 mat{1.0f};
    float x_rot = get_rotation_around_x();
    float y_rot = get_rotation_around_y();
    mat = glm::translate(mat, start);
    mat = glm::rotate(mat, y_rot, {0.0f, 1.0f, 0.0f});
    mat = glm::rotate(mat, x_rot, {1.0f, 0.0f, 0.0f});
    mat = glm::scale(mat, {thickness, length, thickness});
    set_matrix(mat);
}

float Line::get_rotation_around_x() const {
    return std::atan2(
        std::sqrt(dir_vec.z * dir_vec.z + dir_vec.x * dir_vec.x), dir_vec.y
    );
}

float Line::get_rotation_around_y() const {
    return std::atan2(dir_vec.x, dir_vec.z);
}

} // namespace utils

} // namespace axolote
