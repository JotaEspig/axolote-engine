/**
 * \file camera.hpp
 * \brief camera operations
 * \author João Vitor Espig (JotaEspig)
 * \date October 04, 2023
 * \version November 06, 2023
 *
 * This file contains Camera class that handles operations like movement in 3D
 * and view movement
 **/
#pragma once

#include <glm/glm.hpp>

namespace axolote
{

/**
 * \brief class that represents a Camera in 2D/3D
 * \author João Vitor Espig (JotaEspig)
 * \date October 04, 2023
 * \version November 06, 2023
 **/
class Camera
{
public:
    /** movement speed **/
    float speed = 1.0f;
    /** view sensitivity **/
    float sensitivity = 1.0f;
    /** camera FOV **/
    float fov = 45.0f;
    /** first click in the window (used in view movement) **/
    bool first_click = true;
    /** camera position vector **/
    glm::vec3 pos;
    /** camera orientation vector **/
    glm::vec3 orientation = glm::vec3(0.0f, 0.0f, -1.0f);
    /** camera up vector **/
    glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f);

    /**
     * \brief Constructor
     * \author João Vitor Espig (JotaEspig)
     * \date October 04, 2023
     * \version October 08, 2023
     **/
    Camera();
    /**
     * \brief Copy constructor
     * \author João Vitor Espig (JotaEspig)
     * \date November 06, 2023
     * \version November 06, 2023
     * \param camera - Camera object
     **/
    Camera(const Camera &camera);
    /**
     * \brief Move constructor
     * \author João Vitor Espig (JotaEspig)
     * \date November 06, 2023
     * \version November 06, 2023
     * \param camera - Camera object
     **/
    Camera(Camera &&camera);
    /**
     * \brief Constructor
     * \author João Vitor Espig (JotaEspig)
     * \date October 04, 2023
     * \version October 08, 2023
     * \param position - Camera position vector
     **/
    Camera(const glm::vec3 &position);

    /**
     * \brief moves camera position forward
     * \author João Vitor Espig (JotaEspig)
     * \date October 04, 2023
     * \version October 04, 2023
     * \param delta_t - time difference from last frame
     **/
    void forward(float delta_t = 1.0f);
    /**
     * \brief moves camera position leftward
     * \author João Vitor Espig (JotaEspig)
     * \date October 04, 2023
     * \version October 04, 2023
     * \param delta_t - time difference from last frame
     **/
    void leftward(float delta_t = 1.0f);
    /**
     * \brief moves camera position rightward
     * \author João Vitor Espig (JotaEspig)
     * \date October 04, 2023
     * \version October 04, 2023
     * \param delta_t - time difference from last frame
     **/
    void rightward(float delta_t = 1.0f);
    /**
     * \brief moves camera position backward
     * \author João Vitor Espig (JotaEspig)
     * \date October 04, 2023
     * \version October 04, 2023
     * \param delta_t - time difference from last frame
     **/
    void backward(float delta_t = 1.0f);
    /**
     * \brief moves camera position upward
     * \author João Vitor Espig (JotaEspig)
     * \date October 04, 2023
     * \version October 04, 2023
     * \param delta_t - time difference from last frame
     **/
    void upward(float delta_t = 1.0f);
    /**
     * \brief moves camera position downward
     * \author João Vitor Espig (JotaEspig)
     * \date October 04, 2023
     * \version October 04, 2023
     * \param delta_t - time difference from last frame
     **/
    void downward(float delta_t = 1.0f);
    /**
     * \brief do view movement
     * \author João Vitor Espig (JotaEspig)
     * \date October 04, 2023
     * \version October 04, 2023
     * \param x - mouse click point x value
     * \param y - mouse click point y value
     * \param width - Window width
     * \param height - Window height
     * \param delta_t - time difference from last frame
     **/
    void move_vision(
        float x, float y, float width, float height, double delta_t = 1.0
    );
    /**
     * \brief operator = overload (copy)
     * \author João Vitor Espig (JotaEspig)
     * \date November 06, 2023
     * \version November 06, 2023
     * \param camera - Camera object
     **/
    void operator=(const Camera &camera);
    /**
     * \brief operator = overload (move)
     * \author João Vitor Espig (JotaEspig)
     * \date November 06, 2023
     * \version November 06, 2023
     * \param camera - Camera object
     **/
    void operator=(Camera &&camera);
};

} // namespace axolote
