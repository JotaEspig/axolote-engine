#include <memory>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "axolote/drawable.hpp"
#include "axolote/scene.hpp"

namespace axolote {

Scene::Scene() {
}

Scene::~Scene() {
}

void Scene::add_drawable(std::shared_ptr<Drawable> d) {
    drawable_objects.push_back(d);
    shaders.push_back(d->get_shader());
}

void Scene::add_light(const std::shared_ptr<Light> &light) {
    lights.push_back(light);
}

void Scene::update_camera(float aspect_ratio) {
    glm::mat4 view
        = glm::lookAt(camera.pos, camera.pos + camera.orientation, camera.up);
    glm::mat4 projection = glm::perspective(
        glm::radians(camera.fov), aspect_ratio, camera.min_dist, camera.max_dist
    );
    for (gl::Shader &s : shaders) {
        s.activate();
        s.set_uniform_float3(
            "camera_pos", camera.pos.x, camera.pos.y, camera.pos.z
        );
        s.set_uniform_matrix4("projection", projection);
        s.set_uniform_matrix4("view", view);
    }
}

void Scene::update(double time) {
    for (std::shared_ptr<Drawable> d : drawable_objects) {
        d->update(time);
    }

    // Bind lighs to every shader and calculate how much of each type
    int num_point_lights = 0;
    int num_directional_lights = 0;
    int num_spot_lights = 0;
    for (size_t i = 0; i < lights.size(); ++i) {
        auto &light = lights[i];
        std::string prefix;

        switch (light->type) {
        case Light::Type::point:
            prefix = "point_lights[" + std::to_string(num_point_lights++) + "]";
            break;
        case Light::Type::directional:
            num_directional_lights++;
            prefix = "directional_lights["
                     + std::to_string(num_directional_lights++) + "]";
            break;
        case Light::Type::spot:
            num_spot_lights++;
            prefix = "spot_lights[" + std::to_string(num_spot_lights++) + "]";
            break;
        }

        for (auto &shader : shaders) {
            light->bind(shader, prefix);
        }
    }

    // Set number of each light type for every shader
    for (auto &shader : shaders) {
        shader.set_uniform_int("num_point_lights", num_point_lights);
        shader.set_uniform_int(
            "num_directional_lights", num_directional_lights
        );
        shader.set_uniform_int("num_spot_lights", num_spot_lights);
    }
}

void Scene::render() {
    for (std::shared_ptr<Drawable> d : drawable_objects)
        d->draw();
}

} // namespace axolote
