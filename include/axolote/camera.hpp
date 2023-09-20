#pragma once

#include <glm/glm.hpp>

namespace axolote
{

class Camera
{
public:
    float speed = 1.0f;
    float sensitivity = 1.0f;
    float fov = 45.0f;
    bool first_click = true;
    glm::vec3 pos;
    glm::vec3 orientation = glm::vec3(0.0f, 0.0f, -1.0f);
    glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f);
    
    Camera();
    Camera(glm::vec3 position);

    void forward(float delta_v = 1.0f);
    void leftward(float delta_v = 1.0f);
    void rightward(float delta_v = 1.0f);
    void backward(float delta_v = 1.0f);
    void upward(float delta_v = 1.0f);
    void downward(float delta_v = 1.0f);
    void move_vision(float x, float y, float width, float height, double delta_t = 1.0);
};

} // namespace axolote
