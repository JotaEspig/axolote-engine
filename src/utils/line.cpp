#define _USE_MATH_DEFINES
#include <cmath>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "axolote/structs.hpp"
#include "axolote/utils/line.hpp"

#define UNUSED(x) (void)(x)

#ifdef _WIN32
#define M_PIf 3.14159265358979323846f
#endif

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
  line_quality{line_quality} {
    is_affected_by_lights = false;
    build_mesh();
}

void Line::build_mesh() {
    std::vector<Vertex> vs;
    std::vector<GLuint> es;

    // Add top and bottom vertex
    vs.push_back(Vertex{
        glm::vec3{0.0f, 1.0f, 0.0f}, glm::vec4{color}, glm::vec2{0.5f, 1.0f},
        glm::vec3{0.0f, 1.0f, 0.0f}
    });
    vs.push_back(Vertex{
        glm::vec3{0.0f, 0.0f, 0.0f}, glm::vec4{color}, glm::vec2{0.5f, 0.0f},
        glm::vec3{0.0f, -1.0f, 0.0f}
    });

    // Add bottom vertices
    const size_t resolution = 30;
    float step = 1.0f / (float)resolution;
    for (size_t i = 0; i < resolution; ++i) {
        float tex_u;
        if (i <= resolution / 2) {
            tex_u = (float)i * step * 2.0f;
        }
        else {
            tex_u = 2.0f - (float)i * step * 2.0f;
        }
        float angle = (float)i * step * 2.0f * M_PIf;
        float c = std::cos(angle);
        float s = std::sin(angle);

        // Vertex for top face
        vs.push_back(Vertex{
            glm::vec3{c * 0.5f, 1.0f, s * 0.5f}, glm::vec4{color},
            glm::vec2{tex_u, 0.75f}, glm::vec3{0.0f, 1.0f, 0.0f}
        });

        // Vertex for bottom face
        vs.push_back(Vertex{
            glm::vec3{c * 0.5f, 0.0f, s * 0.5f}, glm::vec4{color},
            glm::vec2{tex_u, 0.25f}, glm::vec3{0.0f, -1.0f, 0.0f}
        });

        // Vertices for side face
        // Top
        vs.push_back(Vertex{
            glm::vec3{c * 0.5f, 1.0f, s * 0.5f}, glm::vec4{color},
            glm::vec2{tex_u, 0.75f}, glm::vec3{c, 0.0f, s}
        });
        // Bottom
        vs.push_back(Vertex{
            glm::vec3{c * 0.5f, 0.0f, s * 0.5f}, glm::vec4{color},
            glm::vec2{tex_u, 0.25f}, glm::vec3{c, 0.0f, s}
        });
    }

    // Add indices
    for (size_t i = 2; i < (resolution * 4); i += 4) {
        // Top face
        es.push_back(i);
        es.push_back(0);
        es.push_back(i == (resolution * 4 - 2) ? 2 : (i + 4));

        // Bottom face
        es.push_back(1);
        es.push_back(i + 1);
        es.push_back(i == (resolution * 4 - 2) ? 3 : (i + 5));

        // Side face 1
        es.push_back(i + 2);
        es.push_back(i == (resolution * 4 - 2) ? 5 : (i + 7));
        es.push_back(i + 3);

        // Side face 2
        es.push_back(i + 2);
        es.push_back(i == (resolution * 4 - 2) ? 4 : (i + 6));
        es.push_back(i == (resolution * 4 - 2) ? 5 : (i + 7));
    }

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

void Line::update(double absolute_time, double delta_time) {
    UNUSED(absolute_time);
    UNUSED(delta_time);

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
