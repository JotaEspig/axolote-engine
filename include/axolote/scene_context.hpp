/**
 * @file scene_context.hpp
 * @brief provides struct Scene Context
 * @author João Vitor Espig (jotaespig@gmail.com)
 **/
#pragma once

#include <memory>
#include <vector>

#include "axolote/camera.hpp"
#include "axolote/drawable.hpp"
#include "axolote/light.hpp"
#include "axolote/object3d.hpp"
#include "axolote/utils/grid.hpp"

namespace axolote {

/**
 * @brief Describes a scene context
 * @author João Vitor Espig (jotaespig@gmail.com)
 **/
struct SceneContext {
    /** Camera **/
    Camera camera;
    /** vector of drawables objects **/
    std::vector<std::shared_ptr<Drawable>> drawable_objects;
    /** sorted drawables objects **/
    std::vector<std::shared_ptr<Object3D>> sorted_drawables_objects;
    /** grid **/
    std::shared_ptr<utils::Grid> grid;
    /** lights of the scene **/
    std::vector<std::shared_ptr<Light>> lights;

    void render();
    void update_camera(float aspect_ratio);
};

} // namespace axolote
