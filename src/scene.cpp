#include <memory>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <axolote/entity.hpp>
#include <axolote/gmesh.hpp>
#include <axolote/object3d.hpp>
#include <axolote/scene.hpp>

namespace axolote {

Scene::Scene() {
}

Scene::~Scene() {
}

void Scene::add_drawable(std::shared_ptr<Drawable> d) {
    drawable_objects.push_back(d);
    shaders.push_back(d->get_shader());
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
}

void Scene::render() {
    for (std::shared_ptr<Drawable> d : drawable_objects)
        d->draw();
}

} // namespace axolote
