#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/vector_angle.hpp>

#include "axolote/camera.hpp"

namespace axolote {

Camera::Camera() :
  pos{0.0f, 0.0f, 0.0f} {
}

Camera::Camera(const glm::vec3 &position) :
  pos{position} {
}

void Camera::forward(double delta_t) {
    pos += (float)delta_t * speed * orientation;
    has_moved = true;
}

void Camera::backward(double delta_t) {
    pos += (float)delta_t * speed * -orientation;
    has_moved = true;
}

void Camera::leftward(double delta_t) {
    pos += (float)delta_t * speed
           * -glm::normalize(glm::cross(orientation, up));
    has_moved = true;
}

void Camera::rightward(double delta_t) {
    pos += (float)delta_t * speed * glm::normalize(glm::cross(orientation, up));
    has_moved = true;
}

void Camera::upward(double delta_t) {
    pos += (float)delta_t * speed * up;
    has_moved = true;
}

void Camera::downward(double delta_t) {
    pos += (float)delta_t * speed * -up;
    has_moved = true;
}

void Camera::move_vision(
    float x, float y, float width, float height, double delta_t
) {
    if (first_click)
        first_click = false;

    double rot_x = delta_t * sensitivity * (y - (height / 2)) / height;
    double rot_y = delta_t * sensitivity * (x - (width / 2)) / width;
    glm::vec3 new_orientation = glm::rotate(
        orientation, (float)glm::radians(-rot_x),
        glm::normalize(glm::cross(orientation, up))
    );

    if (std::abs(glm::angle(new_orientation, up) - glm::radians(90.0f))
        <= glm::radians(85.0f)) {
        orientation = new_orientation;
    }

    orientation = glm::rotate(orientation, (float)glm::radians(-rot_y), up);
}

glm::vec3 Camera::get_ray(float x, float y, float width, float height) {
    glm::vec3 ray = glm::normalize(orientation);
    glm::vec3 right = glm::normalize(glm::cross(orientation, up));
    glm::vec3 up = glm::normalize(glm::cross(right, orientation));

    float aspect_ratio = width / height;
    float fov = glm::radians(45.0f);
    float tan_fov = std::tan(fov / 2.0f);

    float x_ndc = (2.0f * x / width - 1.0f) * tan_fov * aspect_ratio;
    float y_ndc = (1.0f - 2.0f * y / height) * tan_fov;

    glm::vec3 ray_dir
        = glm::normalize(x_ndc * right + y_ndc * up + orientation);

    return ray_dir;
}

} // namespace axolote
