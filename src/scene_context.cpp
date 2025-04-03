#include "axolote/scene_context.hpp"

namespace axolote {

void SceneContext::render() {
    for (std::shared_ptr<Drawable> d : drawable_objects)
        d->draw();
    for (std::shared_ptr<Object3D> d : sorted_drawables_objects)
        d->draw();
    if (grid)
        grid->draw();
}

void SceneContext::update_camera(float aspect_ratio) {
    camera.update_matrix(aspect_ratio);
    for (auto &shader : cached_shaders) {
        shader->use();
        glm::vec3 pos = camera.get_pos();
        shader->set_uniform_float3(
            "axolote_camera_pos", pos.x, pos.y, pos.z
        );
        shader->set_uniform_matrix4("axolote_camera", camera.matrix());
    }
}

} // namespace axolote
