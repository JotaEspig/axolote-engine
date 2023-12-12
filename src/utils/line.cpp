#include <glm/glm.hpp>

#include <axolote/utils/line.hpp>

namespace axolote
{

Line::Line(
    glm::vec3 point, glm::vec3 direction_vector, float length, float thickness
) :
    a{point},
    dir_vec{glm::normalize(direction_vector)},
    length{length},
    thickness{thickness}
{
}

} // namespace axolote
