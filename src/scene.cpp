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
#include "axolote/scene_renderer.hpp"
#include "axolote/shaders/light_struct_ubo.hpp"
#include "axolote/utils/grid.hpp"

namespace axolote {

Scene::Scene() {
    glGenBuffers(1, &context->ubo_lights);
    glBindBuffer(GL_UNIFORM_BUFFER, context->ubo_lights);
    glBufferData(GL_UNIFORM_BUFFER, UBO_TOTAL_SIZE, nullptr, GL_DYNAMIC_DRAW);
    glBindBuffer(GL_UNIFORM_BUFFER, 0);

    glBindBufferBase(GL_UNIFORM_BUFFER, 0, context->ubo_lights); // HARDCODED

    debug(
        "Created ubo for lights: %u, size: %zu bytes", context->ubo_lights,
        UBO_TOTAL_SIZE
    );
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

void Scene::add_camera_renderer(std::shared_ptr<CameraRenderer> camera_renderer
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

void Scene::set_skybox(std::shared_ptr<Skybox> skybox) {
    assert(skybox->get_shaders().size() > 0);

    if (context->skybox) {
        auto shaders = context->skybox->get_shaders();
        for (auto &shader : shaders) {
            bool found = context->cached_shaders.find(shader)
                         != context->cached_shaders.end();
            if (found) {
                context->cached_shaders.erase(shader);
            }
        }
    }

    context->skybox = skybox;
    auto shaders = skybox->get_shaders();
    for (auto &shader : shaders) {
        context->cached_shaders.insert(shader);
    }
}

void Scene::unset_skybox() {
    auto shaders = context->skybox->get_shaders();
    for (auto &shader : shaders) {
        bool found = context->cached_shaders.find(shader)
                     != context->cached_shaders.end();
        if (found) {
            context->cached_shaders.erase(shader);
        }
    }
    context->skybox = nullptr;
}

std::shared_ptr<Skybox> Scene::skybox() const {
    return context->skybox;
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

                if (a->is_transparent) { // Both transparent: sort far to near
                    return glm::length2(
                               context->camera._pos
                               - glm::vec3(a->get_matrix()[3])
                           )
                           > glm::length2(
                               context->camera._pos
                               - glm::vec3(b->get_matrix()[3])
                           );
                }
                else { // Both opaque: sort near to far (optional optimization)
                    return glm::length2(
                               context->camera._pos
                               - glm::vec3(a->get_matrix()[3])
                           )
                           < glm::length2(
                               context->camera._pos
                               - glm::vec3(b->get_matrix()[3])
                           );
                }
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

    static shaders::LightsUBOData
        lights_data_buffer; // static to reuse memory, or member of
                            // Scene/Context

    int current_point_light_idx = 0;
    int current_dir_light_idx = 0;
    int current_spot_light_idx = 0;

    for (auto &light_base_ptr : context->lights) {
        if (!light_base_ptr->is_set) {
            continue;
        }
        if (light_base_ptr->should_overlap_scene_pause || !pause) {
            light_base_ptr->update(absolute_time, delta_time);
        }

        // Common light properties often in base Light class:
        // light_base_ptr->color, light_base_ptr->is_set

        // You'll need to dynamic_cast to get specific light properties
        // and fill the corresponding struct in lights_data_buffer.

        if (auto p_light
            = std::dynamic_pointer_cast<PointLight>(light_base_ptr)) {
            if (current_point_light_idx < SHADER_MAX_LIGHTS) {
                auto &ubo_pl
                    = lights_data_buffer.point_lights[current_point_light_idx];
                ubo_pl.color = p_light->color;
                ubo_pl.is_set = p_light->is_set ? 1 : 0;
                ubo_pl.pos = p_light->pos; // Assuming PointLight has 'pos'
                ubo_pl.constant = p_light->constant;
                ubo_pl.linear = p_light->linear;
                ubo_pl.quadratic = p_light->quadratic;
                // Ensure all padding fields are implicitly zero or correctly
                // handled by struct init
                current_point_light_idx++;
            }
        }
        else if (auto d_light
                 = std::dynamic_pointer_cast<DirectionalLight>(light_base_ptr
                 )) {
            if (current_dir_light_idx < SHADER_MAX_LIGHTS) {
                auto &ubo_dl
                    = lights_data_buffer.dir_lights[current_dir_light_idx];
                ubo_dl.color = d_light->color;
                ubo_dl.is_set = d_light->is_set ? 1 : 0;
                ubo_dl.dir
                    = d_light->dir; // Assuming DirectionalLight has 'dir'
                ubo_dl.intensity = d_light->intensity;
                current_dir_light_idx++;
            }
        }
        else if (auto s_light
                 = std::dynamic_pointer_cast<SpotLight>(light_base_ptr)) {
            if (current_spot_light_idx < SHADER_MAX_LIGHTS) {
                auto &ubo_sl
                    = lights_data_buffer.spot_lights[current_spot_light_idx];
                ubo_sl.color = s_light->color;
                ubo_sl.is_set = s_light->is_set ? 1 : 0;
                ubo_sl.pos = s_light->pos; // Assuming SpotLight has 'pos'
                ubo_sl.dir = s_light->dir; // Assuming SpotLight has 'dir'
                ubo_sl.cut_off = s_light->cut_off;
                ubo_sl.outer_cut_off = s_light->outer_cut_off;
                ubo_sl.constant = s_light->constant;
                ubo_sl.linear = s_light->linear;
                ubo_sl.quadratic = s_light->quadratic;
                current_spot_light_idx++;
            }
        }
    }

    // Fill remaining light slots in UBO with is_set = 0 (false)
    for (int i = current_point_light_idx; i < SHADER_MAX_LIGHTS; ++i) {
        lights_data_buffer.point_lights[i].is_set = 0;
    }
    for (int i = current_dir_light_idx; i < SHADER_MAX_LIGHTS; ++i) {
        lights_data_buffer.dir_lights[i].is_set = 0;
    }
    for (int i = current_spot_light_idx; i < SHADER_MAX_LIGHTS; ++i) {
        lights_data_buffer.spot_lights[i].is_set = 0;
    }

    lights_data_buffer.num_point_lights = current_point_light_idx;
    lights_data_buffer.num_dir_lights = current_dir_light_idx;
    lights_data_buffer.num_spot_lights = current_spot_light_idx;

    // Update the UBO on the GPU
    glBindBuffer(GL_UNIFORM_BUFFER, context->ubo_lights);
    glBufferSubData(GL_UNIFORM_BUFFER, 0, UBO_TOTAL_SIZE, &lights_data_buffer);
    glBindBuffer(GL_UNIFORM_BUFFER, 0);
    // --- End of UBO Light Update Logic ---

    // Set number of each light type for every shader
    for (auto &shader : context->cached_shaders) {
        shader->set_uniform_float3(
            "axolote_scene_ambient_light", ambient_light.x, ambient_light.y,
            ambient_light.z
        );
        shader->set_uniform_float(
            "axolote_scene_ambient_light_intensity", ambient_light_intensity
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
    // Ensure PolygonMode is GL_FILL to do not affect the rendering of the
    // framebuffer texture
    GLint polygon_mode[2];
    glGetIntegerv(GL_POLYGON_MODE, polygon_mode);
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    renderer.render();
    glPolygonMode(GL_FRONT_AND_BACK, polygon_mode[0]);

    // Play enqueued sounds
    _audio_engine->play_queue();
}

} // namespace axolote
