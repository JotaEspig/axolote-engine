#include <cmath>

#include <glm/glm.hpp>

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

} // namespace axolote
