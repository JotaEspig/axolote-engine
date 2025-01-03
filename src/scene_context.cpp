#include "axolote/scene_context.hpp"

namespace axolote {

void SceneContext::render() {
    if (grid)
        grid->draw();
    for (std::shared_ptr<Drawable> d : drawable_objects)
        d->draw();
    for (std::shared_ptr<Object3D> d : sorted_drawables_objects)
        d->draw();
}

void SceneContext::update_camera(float aspect_ratio) {
    camera.update_matrix(aspect_ratio);
    for (auto &shader : cached_shaders) {
        shader->use();
        shader->set_uniform_float3(
            "axolote_camera_pos", camera.pos.x, camera.pos.y, camera.pos.z
        );
        shader->set_uniform_matrix4("axolote_camera", camera.matrix());
    }
}

} // namespace axolote
