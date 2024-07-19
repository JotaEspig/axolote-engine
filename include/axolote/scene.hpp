/**
 * \file scene.hpp
 * \brief provides class Scene
 * \author João Vitor Espig (JotaEspig)
 **/
#pragma once

#include <memory>
#include <vector>

#include "axolote/camera.hpp"
#include "axolote/drawable.hpp"
#include "axolote/light.hpp"

namespace axolote {

/**
 * \brief Describes a scene
 * \author João Vitor Espig (JotaEspig)
 **/
class Scene {
public:
    /** vector of drawables objects **/
    std::vector<std::shared_ptr<Drawable>> drawable_objects;
    /** Camera in the scene **/
    Camera camera;
    /** Ambient light **/
    glm::vec3 ambient_light{1.0f};
    /** Ambient light intensity **/
    float ambient_light_intensity = 0.05f;

    /**
     * \brief Constructor
     * \author João Vitor Espig (JotaEspig)
     **/
    Scene();
    /**
     * \brief Destructor
     * \author João Vitor Espig (JotaEspig)
     **/
    ~Scene();

    /**
     * \brief add a Drawable object to the scene
     * \author João Vitor Espig (JotaEspig)
     **/
    void add_drawable(std::shared_ptr<Drawable> d);
    /**
     * \brief add a light to the scene
     * \author Mickael Reichert (mickaelrei)
     * \author João Vitor Espig (JotaEspig)
     **/
    void add_light(const std::shared_ptr<Light> &light);
    /**
     * \brief updates the camera in the shaders
     * \author João Vitor Espig (JotaEspig)
     **/
    void update_camera(float aspect_ratio);
    /**
     * \brief updates the drawables
     * \author João Vitor Espig (JotaEspig)
     **/
    void update(double time);
    /**
     * \brief draw the drawables
     * \author João Vitor Espig (JotaEspig)
     **/
    void render();

private:
    /** vector of shaders from drawable objects **/
    std::vector<gl::Shader> shaders;
    /** lights of the scene **/
    std::vector<std::shared_ptr<Light>> lights;
};

} // namespace axolote
