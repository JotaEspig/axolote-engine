#include <memory>

#include "axolote/gl/shader.hpp"
#include "axolote/gmesh.hpp"
#include "axolote/scene_renderer.hpp"

#define UNUSED(x) (void)(x)

namespace axolote {

SceneRenderer::SceneRenderer() {
}

void SceneRenderer::init(std::uint16_t width, std::uint16_t height) {
    fbo = gl::Framebuffer::create();
    fbo->init(width, height);
    quad.textures.clear();
    quad.textures.push_back(fbo->texture());
}

void SceneRenderer::setup_shader(std::shared_ptr<gl::Shader> shader) {
    quad.bind_shader(shader);
}

void SceneRenderer::update() {
    update(0,0);
}

void SceneRenderer::update(double absolute_time, double delta_time) {
    UNUSED(absolute_time);
    UNUSED(delta_time);

    fbo->bind();
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    scene_context->render();
    fbo->unbind();
}

void SceneRenderer::render() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    quad.draw();
}

} // namespace axolote
