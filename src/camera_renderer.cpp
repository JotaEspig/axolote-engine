#include "axolote/camera_renderer.hpp"

namespace axolote {

void CameraRenderer::setup(std::shared_ptr<SceneContext> context) {
    scene_context = context;
}

} // namespace axolote
