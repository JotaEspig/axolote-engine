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
#include "axolote/scene_context.hpp"

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
    /** Scene context pointer **/
    std::shared_ptr<SceneContext> scene_context;

    /**
     * @brief update method. Should be overriden by the child class
     * @author João Vitor Espig (jotaespig@gmail.com)
     * @param dt time difference from last frame
     **/
    virtual void update(double dt) = 0;
    /**
     * @brief Setups the camera renderer to the current scene
     * @author João Vitor Espig (jotaespig@gmail.com)
     * @param context the scene context
     **/
    void setup(std::shared_ptr<SceneContext> context);
};

} // namespace axolote
