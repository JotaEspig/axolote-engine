#pragma once

#include <memory>

#include "axolote/camera_renderer.hpp"
#include "axolote/gl/shader.hpp"
#include "axolote/gmesh.hpp"

namespace axolote {

class SceneRenderer : public CameraRenderer {
public:
    float aspect_ratio = -1.0f;

    SceneRenderer();

    void init(std::uint16_t width, std::uint16_t height);
    void setup_shader(std::shared_ptr<gl::Shader> shader);
    void update();
    void update(double absolute_time, double delta_time) override;
    void render();

protected:
    /** Quad to render **/
    GMesh quad{
        {{{-1.0f, 1.0f, 0.0f}, {}, {0.0f, 1.0f}, {}},
         {{-1.0f, -1.0f, 0.0f}, {}, {0.0f, 0.0f}, {}},
         {{1.0f, -1.0f, 0.0f}, {}, {1.0f, 0.0f}, {}},
         {{1.0f, 1.0f, 0.0f}, {}, {1.0f, 1.0f}, {}}},
        {0, 1, 2, 0, 2, 3},
        {}
    };
};

} // namespace axolote
