/**
 * @file camera_renderer.hpp
 * @brief Describes how a camera that can render to a framebuffer should be
 * implemented
 * @author João Vitor Espig (jotaespig@gmail.com)
 **/
#pragma once

#include <memory>

#include "axolote/camera.hpp"
#include "axolote/gl/framebuffer.hpp"

namespace axolote {

/**
 * @brief Interface for a camera renderer
 * @author João Vitor Espig (jotaespig@gmail.com)
 *
 * This class should be inherited by a class that will render to a framebuffer
 * using a camera
 **/
class CameraRenderer {
public:
    /** Camera **/
    Camera camera;
    /** Framebuffer **/
    std::shared_ptr<gl::Framebuffer> fbo;
    /** Current scene pointer **/
    const void *scene_ptr;

    /**
     * @brief update method. Should be overriden by the child class
     * @author João Vitor Espig (jotaespig@gmail.com)
     * @param dt time difference from last frame
     * @param scene_ptr pointer to the scene. SHOULD BE CASTED TO THE
     *CORRECT CLASS (i.e. Scene*). Example:
     * @code
     * Scene *scene = (Scene*)scene_ptr;
     **/
    virtual void update(double dt) = 0;
    /**
     * @brief render method. Should be overriden by the child class
     * @author João Vitor Espig (jotaespig@gmail.com)
     **/
    virtual void render() = 0;
    /**
     * @brief Setups the camera renderer to the current scene
     * @author João Vitor Espig (jotaespig@gmail.com)
     * @param scene_ptr pointer to the scene
     **/
    void setup(const void *scene_ptr);
};

} // namespace axolote
