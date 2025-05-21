/**
 * @file scene_context.hpp
 * @brief provides struct Scene Context
 * @author João Vitor Espig (jotaespig@gmail.com)
 **/
#pragma once

#include <memory>
#include <unordered_set>
#include <vector>

#include "axolote/camera.hpp"
#include "axolote/drawable.hpp"
#include "axolote/light.hpp"
#include "axolote/object3d.hpp"
#include "axolote/utils/grid.hpp"
#include "axolote/skybox.hpp"

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
    /** Skybox **/
    std::shared_ptr<Skybox> skybox;
    /** lights of the scene **/
    std::vector<std::shared_ptr<Light>> lights;
    /** Uniform Buffer Object for Lights **/
    GLuint ubo_lights = 0;
    /** Cached shaders in a set **/
    std::unordered_set<
        std::shared_ptr<gl::Shader>, gl::Shader::Hash, gl::Shader::Equal>
        cached_shaders;

    void render();
    void update_camera(float aspect_ratio);
};

} // namespace axolote
