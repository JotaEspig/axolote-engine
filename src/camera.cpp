#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <axolote/camera.hpp>

using namespace axolote;

Camera::Camera()
{
    pos.x = 0.0f;
    pos.y = 0.0f;
    pos.z = 3.0f;
    front.x = 0.0f;
    front.y = 0.0f;
    front.z = -1.0f;
    up.x = 0.0f;
    up.y = 1.0f;
    up.z = 0.0f;
}

// IT's not working fuck merda que bosta 2 da manhã e nada

void Camera::forward()
{
    glm::vec3 vec_pos = glm::vec3(pos.x, pos.y, pos.z);
    glm::vec3 vec_front = glm::vec3(front.x, front.y, front.z);
    vec_pos += speed * vec_front;
    pos.x = vec_pos.x;
    pos.y = vec_pos.y;
    pos.z = vec_pos.z;
}

void Camera::backwards()
{
    glm::vec3 vec_pos = glm::vec3(pos.x, pos.y, pos.z);
    glm::vec3 vec_front = glm::vec3(front.x, front.y, front.z);
    vec_pos -= speed * vec_front;
    pos.x = vec_pos.x;
    pos.y = vec_pos.y;
    pos.z = vec_pos.z;
}

void Camera::left()
{
    glm::vec3 vec_pos = glm::vec3(pos.x, pos.y, pos.z);
    glm::vec3 vec_front = glm::vec3(front.x, front.y, front.z);
    glm::vec3 vec_up = glm::vec3(up.x, up.y, up.z);
    vec_pos -= speed * glm::normalize(glm::cross(vec_front, vec_up));
    pos.x = vec_pos.x;
    pos.y = vec_pos.y;
    pos.z = vec_pos.z;
}

void Camera::right()
{
    glm::vec3 vec_pos = glm::vec3(pos.x, pos.y, pos.z);
    glm::vec3 vec_front = glm::vec3(front.x, front.y, front.z);
    glm::vec3 vec_up = glm::vec3(up.x, up.y, up.z);
    vec_pos += speed * glm::normalize(glm::cross(vec_front, vec_up));
    pos.x = vec_pos.x;
    pos.y = vec_pos.y;
    pos.z = vec_pos.z;
}
