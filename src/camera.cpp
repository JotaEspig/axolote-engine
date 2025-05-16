#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/vector_angle.hpp>

#include "axolote/camera.hpp"

namespace axolote {

Camera::Camera() :
  _pos{0.0f, 0.0f, 0.0f} {
}

Camera::Camera(const glm::vec3 &position) :
  _pos{position} {
}

void Camera::forward(double delta_t) {
    _pos += (float)delta_t * speed * _orientation;
    _has_moved = true;
    should_calculate_matrix = true;
}

void Camera::backward(double delta_t) {
    _pos += (float)delta_t * speed * -_orientation;
    _has_moved = true;
    should_calculate_matrix = true;
}

void Camera::leftward(double delta_t) {
    _pos += (float)delta_t * speed
            * -glm::normalize(glm::cross(_orientation, _up));
    _has_moved = true;
    should_calculate_matrix = true;
}

void Camera::rightward(double delta_t) {
    _pos += (float)delta_t * speed
            * glm::normalize(glm::cross(_orientation, _up));
    _has_moved = true;
    should_calculate_matrix = true;
}

void Camera::upward(double delta_t) {
    _pos += (float)delta_t * speed * _up;
    _has_moved = true;
    should_calculate_matrix = true;
}

void Camera::downward(double delta_t) {
    _pos += (float)delta_t * speed * -_up;
    _has_moved = true;
    should_calculate_matrix = true;
}

void Camera::move_vision(float dx, float dy, double delta_t) {
    // Compute the rotation amounts based on delta, sensitivity, and delta time
    double rot_x = delta_t * sensitivity * dy;
    double rot_y = delta_t * sensitivity * dx;

    // Rotate around the right vector (pitch)
    glm::vec3 right = glm::normalize(glm::cross(_orientation, _up));
    glm::vec3 new_orientation
        = glm::rotate(_orientation, (float)glm::radians(-rot_x), right);

    // Clamp the pitch to prevent flipping
    if (std::abs(glm::angle(new_orientation, _up) - glm::radians(90.0f))
        <= glm::radians(85.0f)) {
        _orientation = new_orientation;
    }

    // Rotate around the global up vector (yaw)
    _orientation = glm::rotate(_orientation, (float)glm::radians(-rot_y), _up);

    should_calculate_matrix = true;
}

glm::vec3 Camera::get_ray(float x, float y, float width, float height) {
    glm::vec3 ray = glm::normalize(_orientation);
    glm::vec3 right = glm::normalize(glm::cross(_orientation, _up));
    glm::vec3 up = glm::normalize(glm::cross(right, _orientation));

    float aspect_ratio = width / height;
    float fov = glm::radians(45.0f);
    float tan_fov = std::tan(fov / 2.0f);

    float x_ndc = (2.0f * x / width - 1.0f) * tan_fov * aspect_ratio;
    float y_ndc = (1.0f - 2.0f * y / height) * tan_fov;

    glm::vec3 ray_dir
        = glm::normalize(x_ndc * right + y_ndc * up + _orientation);

    return ray_dir;
}

void Camera::update_matrix(float aspect_ratio) {
    if (should_calculate_matrix) {
        _view_matrix = glm::lookAt(_pos, _pos + _orientation, _up);
        _projection_matrix = glm::perspective(
            glm::radians(fov), aspect_ratio, min_dist, max_dist
        );
        _matrix = _projection_matrix * _view_matrix;
        should_calculate_matrix = false;
    }
}

glm::mat4 Camera::view_matrix() const {
    return _view_matrix;
}

glm::mat4 Camera::projection_matrix() const {
    return _projection_matrix;
}

glm::mat4 Camera::matrix() const {
    return _matrix;
}

bool Camera::has_moved() const {
    return _has_moved;
}

void Camera::set_pos(const glm::vec3 &pos) {
    _pos = pos;
    _has_moved = true;
    should_calculate_matrix = true;
}

glm::vec3 Camera::get_pos() const {
    return _pos;
}

void Camera::set_orientation(const glm::vec3 &orientation) {
    _orientation = orientation;
    should_calculate_matrix = true;
}

glm::vec3 Camera::get_orientation() const {
    return _orientation;
}

void Camera::set_up(const glm::vec3 &up) {
    _up = up;
    should_calculate_matrix = true;
}

glm::vec3 Camera::get_up() const {
    return _up;
}

} // namespace axolote
