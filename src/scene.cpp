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

Scene::Scene(const Scene &scene) :
  entity_objects{scene.entity_objects},
  object3d_objects{scene.object3d_objects},
  camera{scene.camera},
  shaders{scene.shaders} {
}

Scene::Scene(Scene &&scene) :
  entity_objects{std::move(scene.entity_objects)},
  object3d_objects{std::move(scene.object3d_objects)},
  camera{std::move(scene.camera)},
  shaders{std::move(scene.shaders)} {
}

Scene::~Scene() {
}

void Scene::add_drawable(std::shared_ptr<Entity> e) {
    entity_objects.push_back(e);
    for (const Object3D &o : e->objects) {
        for (const GMesh &g : o.model->meshes) {
            bool already_included = false;
            for (const gl::Shader &s : shaders) {
                if (s.id == g.shader.id) {
                    already_included = true;
                    break;
                }
            }
            if (!already_included)
                shaders.push_back(g.shader);
        }
    }
}

void Scene::add_drawable(std::shared_ptr<Object3D> o) {
    object3d_objects.push_back(o);
    for (const GMesh &g : o->model->meshes) {
        bool already_included = false;
        for (const gl::Shader &s : shaders) {
            if (s.id == g.shader.id) {
                already_included = true;
                break;
            }
        }
        if (!already_included)
            shaders.push_back(g.shader);
    }
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
    for (std::shared_ptr<Entity> e : entity_objects)
        e->update(time);
}

void Scene::render() {
    for (std::shared_ptr<Entity> e : entity_objects)
        e->draw();
    for (std::shared_ptr<Object3D> o : object3d_objects)
        o->draw();
}

void Scene::operator=(const Scene &scene) {
    entity_objects = scene.entity_objects;
    object3d_objects = scene.object3d_objects;
    camera = scene.camera;
    shaders = scene.shaders;
}

void Scene::operator=(Scene &&scene) {
    entity_objects = std::move(scene.entity_objects);
    object3d_objects = std::move(scene.object3d_objects);
    camera = std::move(scene.camera);
    shaders = std::move(scene.shaders);
}

} // namespace axolote
