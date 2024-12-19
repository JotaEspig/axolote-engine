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
    auto all_objects = drawable_objects;
    all_objects.insert(
        all_objects.end(), sorted_drawables_objects.begin(),
        sorted_drawables_objects.end()
    );
    for (auto &o : all_objects) {
        for (std::shared_ptr<gl::Shader> s : o->get_shaders()) {
            s->activate();
            s->set_uniform_float3(
                "axolote_camera_pos", camera.pos.x, camera.pos.y, camera.pos.z
            );
            s->set_uniform_matrix4("axolote_camera", camera.matrix());
        }
    }
    if (grid) {
        grid->camera_pos = camera.pos;
        auto shaders = grid->get_shaders();
        for (auto &s : shaders) {
            s->activate();
            s->set_uniform_float3(
                "axolote_camera_pos", camera.pos.x, camera.pos.y, camera.pos.z
            );
            s->set_uniform_matrix4("axolote_camera", camera.matrix());
        }
    }
}

} // namespace axolote
