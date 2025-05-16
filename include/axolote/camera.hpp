/**
 * @file camera.hpp
 * @brief camera operations
 * @author João Vitor Espig (jotaespig@gmail.com)
 *
 * This file contains Camera class that handles operations like movement in 3D
 * and view movement
 **/
#pragma once

#include <glm/glm.hpp>

namespace axolote {

/**
 * @brief struct that represents a Camera in 2D/3D
 * @author João Vitor Espig (jotaespig@gmail.com)
 **/
class Camera {
public:
    /** max view distance **/
    float max_dist = 1000.0f;
    /** min view distance **/
    float min_dist = 0.1f;
    /** movement speed **/
    float speed = 1.0f;
    /** view sensitivity **/
    float sensitivity = 1.0f;
    /** camera FOV **/
    float fov = 45.0f;
    /** first click in the window (used in view movement) **/
    bool first_click = true;
    /** check if camera orientation has moved, so the matrix should be
     * recalculated **/
    bool should_calculate_matrix = true;

    /**
     * @brief Constructor
     * @author João Vitor Espig (jotaespig@gmail.com)
     **/
    Camera();
    /**
     * @brief Constructor
     * @author João Vitor Espig (jotaespig@gmail.com)
     * @param position Camera position vector
     **/
    Camera(const glm::vec3 &position);

    /**
     * @brief moves camera position forward
     * @author João Vitor Espig (jotaespig@gmail.com)
     * @param delta_t time difference from last frame
     **/
    void forward(double delta_t = 1.0f);
    /**
     * @brief moves camera position leftward
     * @author João Vitor Espig (jotaespig@gmail.com)
     * @param delta_t time difference from last frame
     **/
    void leftward(double delta_t = 1.0f);
    /**
     * @brief moves camera position rightward
     * @author João Vitor Espig (jotaespig@gmail.com)
     * @param delta_t time difference from last frame
     **/
    void rightward(double delta_t = 1.0f);
    /**
     * @brief moves camera position backward
     * @author João Vitor Espig (jotaespig@gmail.com)
     * @param delta_t time difference from last frame
     **/
    void backward(double delta_t = 1.0f);
    /**
     * @brief moves camera position upward
     * @author João Vitor Espig (jotaespig@gmail.com)
     * @param delta_t time difference from last frame
     **/
    void upward(double delta_t = 1.0f);
    /**
     * @brief moves camera position downward
     * @author João Vitor Espig (jotaespig@gmail.com)
     * @param delta_t time difference from last frame
     **/
    void downward(double delta_t = 1.0f);
    /**
     * @brief do view movement
     * @author João Vitor Espig (jotaespig@gmail.com)
     * @param dx change of mouse pos x value
     * @param dy change of mouse pos y value
     * @param delta_t time difference from last frame
     **/
    void move_vision(float dx, float dy, double delta_t = 1.0f);
    /**
     * @brief get ray from camera to a point in the screen
     * @param x point x value
     * @param y point y value
     * @param width Window width
     * @param height Window height
     * @return ray vector
     * @see https://antongerdelan.net/opengl/raycasting.html
     **/
    glm::vec3 get_ray(float x, float y, float width, float height);
    /**
     * @brief update camera view matrix, projection matrix and final matrix
     * @author João Vitor Espig (jotaespig@gmail.com)
     * @param aspect_ratio Window aspect ratio
     **/
    void update_matrix(float aspect_ratio);
    /**
     * @brief get camera view matrix
     * @author João Vitor Espig (jotaespig@gmail.com)
     * @return camera view matrix
     **/
    glm::mat4 view_matrix() const;
    /**
     * @brief get camera projection matrix
     * @author João Vitor Espig (jotaespig@gmail.com)
     * @return camera projection matrix
     **/
    glm::mat4 projection_matrix() const;
    /**
     * @brief get camera matrix
     * @author João Vitor Espig (jotaespig@gmail.com)
     * @return camera matrix
     **/
    glm::mat4 matrix() const;
    /**
     * @brief check if the camera position has moved
     * @author João Vitor Espig (jotaespig@gmail.com)
     * @return true if the camera position has moved
     **/
    bool has_moved() const;
    void set_pos(const glm::vec3 &pos);
    glm::vec3 get_pos() const;
    void set_orientation(const glm::vec3 &orientation);
    glm::vec3 get_orientation() const;
    void set_up(const glm::vec3 &up);
    glm::vec3 get_up() const;

    friend class Scene;

private:
    /** camera position vector **/
    glm::vec3 _pos;
    /** camera orientation vector **/
    glm::vec3 _orientation = glm::vec3(0.0f, 0.0f, -1.0f);
    /** camera up vector **/
    glm::vec3 _up = glm::vec3(0.0f, 1.0f, 0.0f);
    /** camera view matrix **/
    glm::mat4 _view_matrix{1.0f};
    /** camera projection matrix **/
    glm::mat4 _projection_matrix{1.0f};
    /** camera matrix **/
    glm::mat4 _matrix{1.0f};
    /** check if camera position has moved, so the matrix should be recalculated
     * **/
    bool _has_moved = true;
};

} // namespace axolote
