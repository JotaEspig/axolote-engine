#include <cmath>

#include <glm/glm.hpp>

#include <axolote/structs.hpp>
#include <axolote/utils/line.hpp>

namespace axolote
{

Line::Line(
    const glm::vec3 &point, const glm::vec3 &direction_vector, float length,
    float thickness, const glm::vec3 &color
) :
    a{point},
    dir_vec{glm::normalize(direction_vector)},
    length{length},
    thickness{thickness},
    color{color}
{
    build_mesh();
}

void Line::build_mesh()
{
    std::vector<Vertex> vs;
    std::vector<GLuint> es;

    // top base of the cylinder
    glm::vec3 center = a + glm::vec3{0.0f, length, 0.0f};
    float step = 2 * M_PI / 10;
    for (float i = 0; i < 2 * M_PI; i += step / 2)
    {
        glm::vec3 p1{};
    }

    meshes.push_back({vs, es, {}});
}

} // namespace axolote
