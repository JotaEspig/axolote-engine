#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/rotate_vector.hpp>
#include <glm/gtx/vector_angle.hpp>

#include <axolote/camera.hpp>

namespace axolote
{

Camera::Camera()
{
    pos = glm::vec3(0.0f, 0.0f, 0.0f);
}

Camera::Camera(glm::vec3 position)
{
    pos = position;
}

void Camera::forward(float delta_t)
{
    pos += delta_t * speed * orientation;
}

void Camera::backward(float delta_t)
{
    pos += delta_t * speed * -orientation;
}

void Camera::leftward(float delta_t)
{
    pos += delta_t * speed * -glm::normalize(glm::cross(orientation, up));
}

void Camera::rightward(float delta_t)
{
    pos += delta_t * speed * glm::normalize(glm::cross(orientation, up));
}

void Camera::upward(float delta_t)
{
    pos += delta_t * speed * up;
}

void Camera::downward(float delta_t)
{
    pos += delta_t * speed * -up;
}

void Camera::move_vision(float x, float y, float width, float height, double delta_t)
{
    if (first_click)
        first_click = false;

    float rot_x = delta_t * sensitivity * (y - (height / 2)) / height;
    float rot_y = delta_t * sensitivity * (x - (width / 2)) / width;
    glm::vec3 new_orientation = glm::rotate(orientation, glm::radians(-rot_x),
                                            glm::normalize(glm::cross(orientation, up)));

    if (std::abs(glm::angle(new_orientation, up) - glm::radians(90.0f)) <= glm::radians(85.0f))
    {
        orientation = new_orientation;
    }

    orientation = glm::rotate(orientation, glm::radians(-rot_y), up);
}

} // namespace axolote
