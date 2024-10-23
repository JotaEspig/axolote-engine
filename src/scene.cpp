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
    _drawable_objects.push_back(d);
}

bool Scene::remove_drawable(std::shared_ptr<Drawable> d) {
    auto it = std::find(_drawable_objects.begin(), _drawable_objects.end(), d);
    if (it == _drawable_objects.end())
        return false;

    _drawable_objects.erase(it);
    return true;
}

const std::vector<std::shared_ptr<Drawable>> &Scene::drawables_objects() const {
    return _drawable_objects;
}

void Scene::add_sorted_drawable(std::shared_ptr<Object3D> d) {
    auto it = std::lower_bound(
        _sorted_drawables_objects.begin(), _sorted_drawables_objects.end(), d,
        [this](
            const std::shared_ptr<Object3D> &a,
            const std::shared_ptr<Object3D> &b
        ) {
            if (a->is_transparent < b->is_transparent)
                return true;

            return glm::length2(camera.pos - glm::vec3(a->get_matrix()[3]))
                   > glm::length2(camera.pos - glm::vec3(b->get_matrix()[3]));
        }
    );
    _sorted_drawables_objects.insert(it, d);
}

bool Scene::remove_sorted_drawable(std::shared_ptr<Object3D> d) {
    auto it = std::find(
        _sorted_drawables_objects.begin(), _sorted_drawables_objects.end(), d
    );
    if (it == _sorted_drawables_objects.end())
        return false;

    _sorted_drawables_objects.erase(it);
    return true;
}

const std::vector<std::shared_ptr<Object3D>> &
Scene::sorted_drawables_objects() const {
    return _sorted_drawables_objects;
}

void Scene::add_light(std::shared_ptr<Light> light) {
    _lights.push_back(light);
}

bool Scene::remove_light(std::shared_ptr<Light> light) {
    auto it = std::find(_lights.begin(), _lights.end(), light);
    if (it == _lights.end())
        return false;

    _lights.erase(it);
    return true;
}

const std::vector<std::shared_ptr<Light>> &Scene::lights() const {
    return _lights;
}

void Scene::set_grid(std::shared_ptr<utils::Grid> grid) {
    _grid = grid;
}

void Scene::unset_grid() {
    _grid = nullptr;
}

std::shared_ptr<utils::Grid> Scene::grid() const {
    return _grid;
}

void Scene::update_camera(float aspect_ratio) {
    glm::mat4 view
        = glm::lookAt(camera.pos, camera.pos + camera.orientation, camera.up);
    glm::mat4 projection = glm::perspective(
        glm::radians(camera.fov), aspect_ratio, camera.min_dist, camera.max_dist
    );

    auto all_objects = _drawable_objects;
    all_objects.insert(
        all_objects.end(), _sorted_drawables_objects.begin(),
        _sorted_drawables_objects.end()
    );
    for (auto &o : all_objects) {
        for (std::shared_ptr<gl::Shader> s : o->get_shaders()) {
            s->activate();
            s->set_uniform_float3(
                "axolote_camera_pos", camera.pos.x, camera.pos.y, camera.pos.z
            );
            s->set_uniform_matrix4("axolote_projection", projection);
            s->set_uniform_matrix4("axolote_view", view);
        }
    }
    if (_grid) {
        _grid->camera_pos = camera.pos;
        auto shaders = _grid->get_shaders();
        for (auto &s : shaders) {
            s->activate();
            s->set_uniform_float3(
                "axolote_camera_pos", camera.pos.x, camera.pos.y, camera.pos.z
            );
            s->set_uniform_matrix4("axolote_projection", projection);
            s->set_uniform_matrix4("axolote_view", view);
        }
    }
}

void Scene::update(double delta_t) {
    if (camera.has_moved) {
        std::sort(
            _sorted_drawables_objects.begin(), _sorted_drawables_objects.end(),
            [this](
                const std::shared_ptr<Object3D> &a,
                const std::shared_ptr<Object3D> &b
            ) {
                if (a->is_transparent < b->is_transparent)
                    return true;

                return glm::length2(camera.pos - glm::vec3(a->get_matrix()[3]))
                       > glm::length2(
                           camera.pos - glm::vec3(b->get_matrix()[3])
                       );
            }
        );
        camera.has_moved = false;
    }

    for (std::shared_ptr<Object3D> d : _sorted_drawables_objects) {
        d->update(delta_t);
    }
    for (std::shared_ptr<Drawable> d : _drawable_objects)
        d->update(delta_t);
    if (_grid)
        _grid->update(delta_t);

    // Bind lighs to every shader and calculate how much of each type
    int num_point_lights = 0;
    int num_directional_lights = 0;
    int num_spot_lights = 0;
    for (auto &light : _lights) {
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

        auto all_objects = _drawable_objects;
        all_objects.insert(
            all_objects.end(), _sorted_drawables_objects.begin(),
            _sorted_drawables_objects.end()
        );
        for (auto &o : all_objects) {
            for (std::shared_ptr<gl::Shader> s : o->get_shaders()) {
                light->bind(s, prefix);
            }
        }
    }

    // Set number of each light type for every shader
    auto all_objects = _drawable_objects;
    all_objects.insert(
        all_objects.end(), _sorted_drawables_objects.begin(),
        _sorted_drawables_objects.end()
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
}

void Scene::render() {
    if (_grid)
        _grid->draw();
    for (std::shared_ptr<Drawable> d : _drawable_objects)
        d->draw();
    for (std::shared_ptr<Object3D> d : _sorted_drawables_objects)
        d->draw();
}

} // namespace axolote
