#include <cmath>
#include <iostream>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <axolote/structs.hpp>
#include <axolote/utils/line.hpp>

namespace axolote
{

Line::Line(
    const glm::vec3 &point, const glm::vec3 &direction_vector, float length,
    float thickness, const glm::vec3 &color, float line_quality
) :
    a{point},
    dir_vec{glm::normalize(direction_vector)},
    length{length},
    thickness{thickness},
    color{color},
    line_quality{line_quality}
{
    build_mesh();
}

void Line::build_mesh()
{
    std::vector<Vertex> vs;
    std::vector<GLuint> es;

    float step = 2 * M_PI / 20;

    glm::vec3 bottom_base_center = a;
    glm::vec3 top_base_center = a + (glm::vec3{0.0f, 1.0f, 0.0f} * length);
    int counter = 0;
    for (float i = 0; i < 2 * M_PI; i += step / 2)
    {
        // bottom base face
        glm::vec3 bottom_p1{
            std::cos(i) * thickness, bottom_base_center.y,
            std::sin(i) * thickness};
        glm::vec3 bottom_p2{
            std::cos(i + step / 2) * thickness, bottom_base_center.y,
            std::sin(i + step / 2) * thickness};
        vs.push_back(Vertex{bottom_base_center, color, {}, {}});
        vs.push_back(Vertex{bottom_p1, color, {}, {}});
        vs.push_back(Vertex{bottom_p2, color, {}, {}});
        es.push_back(3 * counter + 0);
        es.push_back(3 * counter + 1);
        es.push_back(3 * counter + 2);
        ++counter;

        // top base face
        glm::vec3 top_p1{
            std::cos(i) * thickness, top_base_center.y,
            std::sin(i) * thickness};
        glm::vec3 top_p2{
            std::cos(i + step / 2) * thickness, top_base_center.y,
            std::sin(i + step / 2) * thickness};
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

    meshes.push_back({vs, es, {}});
}

void Line::draw()
{
    set_matrix();
    Object3D::draw();
}

void Line::set_matrix()
{
    glm::mat4 mat{1.0f};
    float x_rot = get_x_rotation();
    float z_rot = get_z_rotation();
    mat = glm::rotate(mat, x_rot, {1.0f, 0.0f, 0.0f});
    mat = glm::rotate(mat, z_rot, {0.0f, 0.0f, 1.0f});
    mat = glm::translate(mat, a);
    model_mat = mat;
}

float Line::get_x_rotation() const
{
    glm::vec3 orig_v = original_dir_vec;
    orig_v.x = 0.0f;
    glm::vec3 v = dir_vec;
    v.x = 0.0f;

    float x = glm::length(v) * glm::length(orig_v);
    if (x == 0)
        return 0;
    return -std::acos(glm::dot(v, orig_v) / (x));
}

float Line::get_z_rotation() const
{
    glm::vec3 orig_v = original_dir_vec;
    orig_v.z = 0.0f;
    glm::vec3 v = dir_vec;
    v.z = 0.0f;

    float x = glm::length(v) * glm::length(orig_v);
    if (x == 0)
        return 0;
    return -std::acos(glm::dot(v, orig_v) / (x));
}

} // namespace axolote
