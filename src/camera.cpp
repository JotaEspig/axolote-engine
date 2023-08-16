#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/rotate_vector.hpp>
#include <glm/gtx/vector_angle.hpp>

#include <axolote/camera.hpp>

using namespace axolote;

Camera::Camera()
{
    pos = glm::vec3(0.0f, 0.0f, 0.0f);
}

Camera::Camera(glm::vec3 position)
{
    pos = position;
}

void Camera::forward()
{
    pos += speed * orientation;
}

void Camera::backward()
{
    pos += speed * -orientation;
}

void Camera::leftward()
{
    pos += speed * -glm::normalize(glm::cross(orientation, up));
}

void Camera::rightward()
{
    pos += speed * glm::normalize(glm::cross(orientation, up));
}

void Camera::upward()
{
    pos += speed * up;
}

void Camera::downward()
{
    pos += speed * -up;
}

void Camera::move_vision(float x, float y, float width, float height)
{
    if (first_click)
        first_click = false;

    float rot_x = sensitivity * (y - (height / 2)) / height;
    float rot_y = sensitivity * (x - (width / 2)) / width;
    glm::vec3 new_orientation = glm::rotate(orientation, glm::radians(-rot_x),
                                            glm::normalize(glm::cross(orientation, up)));

    if (std::abs(glm::angle(new_orientation, up) - glm::radians(90.0f)) <= glm::radians(85.0f))
    {
        orientation = new_orientation;
    }

    orientation = glm::rotate(orientation, glm::radians(-rot_y), up);
}
