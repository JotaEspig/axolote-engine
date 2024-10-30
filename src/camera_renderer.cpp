#include "axolote/camera_renderer.hpp"

namespace axolote {

void CameraRenderer::setup(const void *scene_ptr) {
    CameraRenderer::scene_ptr = scene_ptr;
}

} // namespace axolote
