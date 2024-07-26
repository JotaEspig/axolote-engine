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
#include "axolote/object3d.hpp"

namespace axolote {

/**
 * \brief Describes a scene
 * \author João Vitor Espig (JotaEspig)
 **/
class Scene {
public:
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
     * \brief get the unsorted drawables objects
     * \author João Vitor Espig (JotaEspig)
     **/
    const std::vector<std::shared_ptr<Drawable>> &drawables_objects() const;
    /**
     * \brief add a Drawable object to the scene in a sorted way
     * \author João Vitor Espig (JotaEspig)
     *
     * Useful when you want to use transparency in the objects
     **/
    void add_sorted_drawable(std::shared_ptr<Object3D> d);
    /**
     * \brief get the sorted drawables objects
     * \author João Vitor Espig (JotaEspig)
     *
     * It's not garanteed that the objects are sorted, because it depends on the
     * camera position
     **/
    const std::vector<std::shared_ptr<Object3D>> &
    sorted_drawables_objects() const;
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
    void update(double delta_t);
    /**
     * \brief draw the drawables
     * \author João Vitor Espig (JotaEspig)
     *
     * It draws the unsorted drawables first
     * (it assumes they're opaque objects), then the sorted drawables
     **/
    void render();

private:
    /** vector of drawables objects **/
    std::vector<std::shared_ptr<Drawable>> _drawable_objects;
    /** sorted drawables objects **/
    std::vector<std::shared_ptr<Object3D>> _sorted_drawables_objects;
    /** vector of shaders from drawable objects **/
    std::vector<std::shared_ptr<gl::Shader>> _shaders;
    /** lights of the scene **/
    std::vector<std::shared_ptr<Light>> _lights;
};

} // namespace axolote
