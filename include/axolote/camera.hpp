#pragma once

#include <glm/glm.hpp>

namespace axolote
{

class Camera
{
public:
    float speed = 0.1f;
    float sensitivity = 200.0f;
    float fov = 45.0f;
    bool first_click = true;
    glm::vec3 pos;
    glm::vec3 orientation = glm::vec3(0.0f, 0.0f, -1.0f);
    glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f);
    
    Camera();
    Camera(glm::vec3 position);

    void forward();
    void leftward();
    void rightward();
    void backward();
    void upward();
    void downward();
    void move_vision(float x, float y, float width, float height);
};

} // namespace axolote
