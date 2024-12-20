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
    context->drawable_objects.push_back(d);
}

bool Scene::remove_drawable(std::shared_ptr<Drawable> d) {
    auto it = std::find(
        context->drawable_objects.begin(), context->drawable_objects.end(), d
    );
    if (it == context->drawable_objects.end())
        return false;

    context->drawable_objects.erase(it);
    return true;
}

const std::vector<std::shared_ptr<Drawable>> &Scene::drawables_objects() const {
    return context->drawable_objects;
}

void Scene::add_sorted_drawable(std::shared_ptr<Object3D> d) {
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
                       context->camera.pos - glm::vec3(a->get_matrix()[3])
                   )
                   > glm::length2(
                       context->camera.pos - glm::vec3(b->get_matrix()[3])
                   );
        }
    );
    context->sorted_drawables_objects.insert(it, d);
}

bool Scene::remove_sorted_drawable(std::shared_ptr<Object3D> d) {
    auto it = std::find(
        context->sorted_drawables_objects.begin(),
        context->sorted_drawables_objects.end(), d
    );
    if (it == context->sorted_drawables_objects.end())
        return false;

    context->sorted_drawables_objects.erase(it);
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
    context->grid = grid;
}

void Scene::unset_grid() {
    context->grid = nullptr;
}

std::shared_ptr<utils::Grid> Scene::grid() const {
    return context->grid;
}

void Scene::update_camera(float aspect_ratio) {
    last_aspect_ratio = aspect_ratio;
    context->camera.update_matrix(aspect_ratio);
    auto all_objects = context->drawable_objects;
    all_objects.insert(
        all_objects.end(), context->sorted_drawables_objects.begin(),
        context->sorted_drawables_objects.end()
    );
    for (auto &o : all_objects) {
        for (std::shared_ptr<gl::Shader> s : o->get_shaders()) {
            s->use();
            s->set_uniform_float3(
                "axolote_camera_pos", context->camera.pos.x,
                context->camera.pos.y, context->camera.pos.z
            );
            s->set_uniform_matrix4("axolote_camera", context->camera.matrix());
        }
    }
    if (context->grid) {
        context->grid->camera_pos = context->camera.pos;
        auto shaders = context->grid->get_shaders();
        for (auto &s : shaders) {
            s->use();
            s->set_uniform_float3(
                "axolote_camera_pos", context->camera.pos.x,
                context->camera.pos.y, context->camera.pos.z
            );
            s->set_uniform_matrix4("axolote_camera", context->camera.matrix());
        }
    }
}

void Scene::update(double delta_t) {
    if (context->camera.has_moved) {
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
                           context->camera.pos - glm::vec3(a->get_matrix()[3])
                       )
                       > glm::length2(
                           context->camera.pos - glm::vec3(b->get_matrix()[3])
                       );
            }
        );
        context->camera.has_moved = false;
    }

    for (std::shared_ptr<Object3D> d : context->sorted_drawables_objects) {
        d->update(delta_t);
    }
    for (std::shared_ptr<Drawable> d : context->drawable_objects)
        d->update(delta_t);
    if (context->grid)
        context->grid->update(delta_t);

    // Bind lighs to every shader and calculate how much of each type
    int num_point_lights = 0;
    int num_directional_lights = 0;
    int num_spot_lights = 0;
    for (auto &light : context->lights) {
        light->update(delta_t);
        std::string prefix;

        switch (light->type) {
        case Light::Type::Point:
            prefix = "axolote_point_lights["
                     + std::to_string(num_point_lights++) + "]";
            break;
        case Light::Type::Directional:
            num_directional_lights++;
            prefix = "axolote_directional_lights["
                     + std::to_string(num_directional_lights++) + "]";
            break;
        case Light::Type::Spot:
            num_spot_lights++;
            prefix = "axolote_spot_lights[" + std::to_string(num_spot_lights++)
                     + "]";
            break;
        }

        auto all_objects = context->drawable_objects;
        all_objects.insert(
            all_objects.end(), context->sorted_drawables_objects.begin(),
            context->sorted_drawables_objects.end()
        );
        for (auto &o : all_objects) {
            for (std::shared_ptr<gl::Shader> s : o->get_shaders()) {
                light->bind(s, prefix);
            }
        }
    }

    // Set number of each light type for every shader
    auto all_objects = context->drawable_objects;
    all_objects.insert(
        all_objects.end(), context->sorted_drawables_objects.begin(),
        context->sorted_drawables_objects.end()
    );
    for (auto &o : all_objects) {
        for (auto &shader : o->get_shaders()) {
            shader->set_uniform_float3(
                "axolote_ambient_light", ambient_light.x, ambient_light.y,
                ambient_light.z
            );
            shader->set_uniform_float(
                "axolote_ambient_light_intensity", ambient_light_intensity
            );
            shader->set_uniform_int(
                "axolote_num_point_lights", num_point_lights
            );
            shader->set_uniform_int(
                "axolote_num_directional_lights", num_directional_lights
            );
            shader->set_uniform_int("axolote_num_spot_lights", num_spot_lights);
            shader->set_uniform_float("axolote_gamma", gamma);
        }
    }

    for (auto &camera_renderer : _camera_renderers) {
        camera_renderer->setup(context);
        camera_renderer->update(delta_t);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
    }
    if (_camera_renderers.size() > 0) {
        update_camera(last_aspect_ratio);
    }
}

void Scene::render() {
    if (context->grid)
        context->grid->draw();
    for (std::shared_ptr<Drawable> d : context->drawable_objects)
        d->draw();
    for (std::shared_ptr<Object3D> d : context->sorted_drawables_objects)
        d->draw();
}

} // namespace axolote
