/**
 * @file scene.hpp
 * @brief provides class Scene
 * @author João Vitor Espig (jotaespig@gmail.com)
 **/
#pragma once

#include <memory>
#include <vector>

#include "axolote/camera_renderer.hpp"
#include "axolote/drawable.hpp"
#include "axolote/light.hpp"
#include "axolote/object3d.hpp"
#include "axolote/scene_context.hpp"
#include "axolote/scene_renderer.hpp"
#include "axolote/utils/grid.hpp"

namespace axolote {

/**
 * @brief Describes a scene
 * @author João Vitor Espig (jotaespig@gmail.com)
 **/
class Scene {
public:
    /** Scene Context pointer **/
    std::shared_ptr<SceneContext> context = std::make_shared<SceneContext>();
    /** Scene Renderer **/
    SceneRenderer renderer;
    /** Ambient light **/
    glm::vec3 ambient_light{1.0f};
    /** Ambient light intensity **/
    float ambient_light_intensity = 0.05f;
    /** Gamma correction for the scene **/
    float gamma = 1.0f;

    /**
     * @brief Constructor
     * @author João Vitor Espig (jotaespig@gmail.com)
     **/
    Scene();
    /**
     * @brief Destructor
     * @author João Vitor Espig (jotaespig@gmail.com)
     **/
    ~Scene();

    /**
     * @brief add a Drawable object to the scene
     * @author João Vitor Espig (jotaespig@gmail.com)
     **/
    void add_drawable(std::shared_ptr<Drawable> d);
    /**
     * @brief remove a Drawable object from the scene
     * @author João Vitor Espig (jotaespig@gmail.com)
     * @param d the object to be removed
     * @return true if the object was removed, false otherwise
     **/
    bool remove_drawable(std::shared_ptr<Drawable> d);
    /**
     * @brief get the unsorted drawables objects
     * @author João Vitor Espig (jotaespig@gmail.com)
     **/
    const std::vector<std::shared_ptr<Drawable>> &drawables_objects() const;
    /**
     * @brief add a Drawable object to the scene in a sorted way
     * @author João Vitor Espig (jotaespig@gmail.com)
     *
     * Useful when you want to use transparency in the objects
     **/
    void add_sorted_drawable(std::shared_ptr<Object3D> d);
    /**
     * @brief remove a Drawable object from the sorted drawables objects
     * @author João Vitor Espig (jotaespig@gmail.com)
     * @param d the object to be removed
     * @return true if the object was removed, false otherwise
     **/
    bool remove_sorted_drawable(std::shared_ptr<Object3D> d);
    /**
     * @brief get the sorted drawables objects
     * @author João Vitor Espig (jotaespig@gmail.com)
     *
     * Sorted by transparency and distance to the camera.
     * Please note that the objects are sorted based on the last call to method
     * update()
     **/
    const std::vector<std::shared_ptr<Object3D>> &
    sorted_drawables_objects() const;
    /**
     * @brief add a light to the scene
     * @author Mickael Reichert (mickael.reichert@gmail.com)
     * @author João Vitor Espig (jotaespig@gmail.com)
     **/
    void add_light(std::shared_ptr<Light> light);
    /**
     * @brief remove a light from the scene
     * @author João Vitor Espig (jotaespig@gmail.com)
     * @param light the light to be removed
     * @return true if the light was removed, false otherwise
     **/
    bool remove_light(std::shared_ptr<Light> light);
    /**
     * @brief get the lights of the scene
     * @author João Vitor Espig (jotaespig@gmail.com)
     **/
    const std::vector<std::shared_ptr<Light>> &lights() const;
    /**
     * @brief add a camera renderer to the scene
     * @author João Vitor Espig (jotaespig@gmail.com)
     * @param camera_renderer the camera renderer to be added
     **/
    void add_camera_renderer(std::shared_ptr<CameraRenderer> camera_renderer);
    /**
     * @brief remove a camera renderer from the scene
     * @author João Vitor Espig (jotaespig@gmail.com)
     * @param camera_renderer the camera renderer to be removed
     * @return true if the camera renderer was removed, false otherwise
     **/
    bool remove_camera_renderer(std::shared_ptr<CameraRenderer> camera_renderer
    );
    /**
     * @brief get the camera renderers of the scene
     * @author João Vitor Espig (jotaespig@gmail.com)
     **/
    const std::vector<std::shared_ptr<CameraRenderer>> &
    camera_renderers() const;
    /**
     * @brief set the grid of the scene
     * @author João Vitor Espig (jotaespig@gmail.com)
     **/
    void set_grid(std::shared_ptr<utils::Grid> grid);
    /**
     * @brief unset the grid of the scene
     * @author João Vitor Espig (jotaespig@gmail.com)
     **/
    void unset_grid();
    /**
     * @brief get the grid of the scene
     * @author João Vitor Espig (jotaespig@gmail.com)
     **/
    std::shared_ptr<utils::Grid> grid() const;
    /**
     * @brief updates the camera in the shaders
     * @author João Vitor Espig (jotaespig@gmail.com)
     **/
    void update_camera(float aspect_ratio);
    /**
     * @brief updates the drawables
     * @author João Vitor Espig (jotaespig@gmail.com)
     **/
    void update(double delta_t);
    /**
     * @brief draw the drawables
     * @author João Vitor Espig (jotaespig@gmail.com)
     *
     * It draws the unsorted drawables first
     * (it assumes they're opaque objects), then the sorted drawables
     **/
    void render();

private:
    double last_aspect_ratio = 1.0;
    /** Camera renderers **/
    std::vector<std::shared_ptr<CameraRenderer>> _camera_renderers;
    /** Framebuffer shader **/
};

} // namespace axolote
