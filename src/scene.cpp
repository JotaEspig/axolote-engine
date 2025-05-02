#include <algorithm>
#include <memory>

#include <glm/glm.hpp>
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/norm.hpp>
#include <glm/gtx/string_cast.hpp>

#include "axolote/drawable.hpp"
#include "axolote/object3d.hpp"
#include "axolote/scene.hpp"

namespace axolote {

Scene::Scene() {
}

Scene::~Scene() {
}

void Scene::add_drawable(std::shared_ptr<Drawable> d) {
    assert(d->get_shaders().size() > 0);

    context->drawable_objects.push_back(d);
    auto shaders = d->get_shaders();
    context->cached_shaders.insert(shaders.begin(), shaders.end());
}

bool Scene::remove_drawable(std::shared_ptr<Drawable> d) {
    auto it = std::find(
        context->drawable_objects.begin(), context->drawable_objects.end(), d
    );
    if (it == context->drawable_objects.end())
        return false;

    context->drawable_objects.erase(it);
    auto shaders = d->get_shaders();
    for (auto &shader : shaders) {
        bool found = context->cached_shaders.find(shader)
                     != context->cached_shaders.end();
        if (found) {
            context->cached_shaders.erase(shader);
        }
    }
    return true;
}

const std::vector<std::shared_ptr<Drawable>> &Scene::drawables_objects() const {
    return context->drawable_objects;
}

void Scene::add_sorted_drawable(std::shared_ptr<Object3D> d) {
    assert(d->get_shaders().size() > 0);

    auto it = std::lower_bound(
        context->sorted_drawables_objects.begin(),
        context->sorted_drawables_objects.end(), d,
        [this](
            const std::shared_ptr<Object3D> &a,
            const std::shared_ptr<Object3D> &b
        ) {
            if (a->is_transparent < b->is_transparent)
                return true;

            return glm::length2(
                       context->camera._pos - glm::vec3(a->get_matrix()[3])
                   )
                   > glm::length2(
                       context->camera._pos - glm::vec3(b->get_matrix()[3])
                   );
        }
    );
    context->sorted_drawables_objects.insert(it, d);
    auto shaders = d->get_shaders();
    context->cached_shaders.insert(shaders.begin(), shaders.end());
}

bool Scene::remove_sorted_drawable(std::shared_ptr<Object3D> d) {
    auto it = std::find(
        context->sorted_drawables_objects.begin(),
        context->sorted_drawables_objects.end(), d
    );
    if (it == context->sorted_drawables_objects.end())
        return false;

    context->sorted_drawables_objects.erase(it);
    auto shaders = d->get_shaders();
    for (auto &shader : shaders) {
        bool found = context->cached_shaders.find(shader)
                     != context->cached_shaders.end();
        if (found) {
            context->cached_shaders.erase(shader);
        }
    }
    return true;
}

const std::vector<std::shared_ptr<Object3D>> &
Scene::sorted_drawables_objects() const {
    return context->sorted_drawables_objects;
}

void Scene::add_light(std::shared_ptr<Light> light) {
    context->lights.push_back(light);
}

bool Scene::remove_light(std::shared_ptr<Light> light) {
    auto it = std::find(context->lights.begin(), context->lights.end(), light);
    if (it == context->lights.end())
        return false;

    context->lights.erase(it);
    return true;
}

const std::vector<std::shared_ptr<Light>> &Scene::lights() const {
    return context->lights;
}

void Scene::add_camera_renderer(
    std::shared_ptr<CameraRenderer> camera_renderer
) {
    _camera_renderers.push_back(camera_renderer);
}

bool Scene::remove_camera_renderer(
    std::shared_ptr<CameraRenderer> camera_renderer
) {
    auto it = std::find(
        _camera_renderers.begin(), _camera_renderers.end(), camera_renderer
    );
    if (it == _camera_renderers.end())
        return false;

    _camera_renderers.erase(it);
    return true;
}

const std::vector<std::shared_ptr<CameraRenderer>> &
Scene::camera_renderers() const {
    return _camera_renderers;
}

void Scene::set_grid(std::shared_ptr<utils::Grid> grid) {
    assert(grid->get_shaders().size() > 0);

    if (context->grid) {
        auto shaders = context->grid->get_shaders();
        for (auto &shader : shaders) {
            bool found = context->cached_shaders.find(shader)
                         != context->cached_shaders.end();
            if (found) {
                context->cached_shaders.erase(shader);
            }
        }
    }

    context->grid = grid;
    auto shaders = grid->get_shaders();
    for (auto &shader : shaders) {
        context->cached_shaders.insert(shader);
    }
}

void Scene::unset_grid() {
    auto shaders = context->grid->get_shaders();
    for (auto &shader : shaders) {
        bool found = context->cached_shaders.find(shader)
                     != context->cached_shaders.end();
        if (found) {
            context->cached_shaders.erase(shader);
        }
    }
    context->grid = nullptr;
}

std::shared_ptr<utils::Grid> Scene::grid() const {
    return context->grid;
}

void Scene::update_camera(float aspect_ratio) {
    last_aspect_ratio = aspect_ratio;
    context->update_camera(aspect_ratio);
    if (context->grid) {
        context->grid->camera_pos = context->camera._pos;
    }
}

void Scene::update(double absolute_time, double delta_time) {
    if (context->camera._has_moved) {
        std::sort(
            context->sorted_drawables_objects.begin(),
            context->sorted_drawables_objects.end(),
            [this](
                const std::shared_ptr<Object3D> &a,
                const std::shared_ptr<Object3D> &b
            ) {
                if (a->is_transparent < b->is_transparent)
                    return true;

                return glm::length2(
                           context->camera._pos - glm::vec3(a->get_matrix()[3])
                       )
                       > glm::length2(
                           context->camera._pos - glm::vec3(b->get_matrix()[3])
                       );
            }
        );
        context->camera._has_moved = false;
    }

    if (context->grid && !context->grid->paused) {
        context->grid->update(absolute_time, delta_time);
    }

    if (!pause) {
        for (std::shared_ptr<Object3D> d : context->sorted_drawables_objects) {
            if (d->paused) {
                continue;
            }
            d->update(absolute_time, delta_time);
        }
        for (std::shared_ptr<Drawable> d : context->drawable_objects) {
            if (d->paused) {
                continue;
            }
            d->update(absolute_time, delta_time);
        }
    }

    // Bind lighs to every shader and calculate how much of each type
    int num_point_lights = 0;
    int num_directional_lights = 0;
    int num_spot_lights = 0;
    for (auto &light : context->lights) {
        if (!light->is_set) {
            continue;
        }
        if (light->should_overlap_scene_pause || !pause) {
            light->update(absolute_time, delta_time);
        }

        std::string prefix;

        switch (light->type) {
        case Light::Type::Point:
            prefix = "axolote_scene_point_lights["
                     + std::to_string(num_point_lights++) + "]";
            break;
        case Light::Type::Directional:
            num_directional_lights++;
            prefix = "axolote_scene_dir_lights["
                     + std::to_string(num_directional_lights++) + "]";
            break;
        case Light::Type::Spot:
            num_spot_lights++;
            prefix = "axolote_scene_spot_lights["
                     + std::to_string(num_spot_lights++) + "]";
            break;
        }

        for (auto &shader : context->cached_shaders) {
            light->bind(shader, prefix);
        }
    }

    // Set number of each light type for every shader
    for (auto &shader : context->cached_shaders) {
        shader->set_uniform_float3(
            "axolote_scene_ambient_light", ambient_light.x, ambient_light.y,
            ambient_light.z
        );
        shader->set_uniform_float(
            "axolote_scene_ambient_light_intensity", ambient_light_intensity
        );
        shader->set_uniform_int(
            "axolote_scene_num_point_lights", num_point_lights
        );
        shader->set_uniform_int(
            "axolote_scene_num_dir_lights", num_directional_lights
        );
        shader->set_uniform_int(
            "axolote_scene_num_spot_lights", num_spot_lights
        );
        shader->set_uniform_float("axolote_scene_gamma", gamma);
    }

    for (auto &camera_renderer : _camera_renderers) {
        camera_renderer->setup(context);
        camera_renderer->update(absolute_time, delta_time);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
    }
    // Resets the camera if has any camera renderers because the camera
    // renderers may change the camera
    if (_camera_renderers.size() > 0) {
        update_camera(last_aspect_ratio);
    }

    renderer.setup(context);
    renderer.update();
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
}

void Scene::render() {
    GLint polygon_mode[2];
    glGetIntegerv(GL_POLYGON_MODE, polygon_mode);
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    renderer.render();
    glPolygonMode(GL_FRONT_AND_BACK, polygon_mode[0]);
}

} // namespace axolote
