#include "axolote/gl/framebuffer.hpp"
#include "axolote/utils.hpp"

namespace axolote {

namespace gl {

GLuint Framebuffer::id() const {
    return _id;
}

void Framebuffer::init(std::uint16_t width, std::uint16_t height) {
    bind();
    _texture = Texture::create();
    _texture->bind();
    GLuint tex_id = _texture->id();
    glTexImage2D(
        GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE,
        NULL
    );
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    glFramebufferTexture2D(
        GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, tex_id, 0
    );

    glGenRenderbuffers(1, &_rbo);
    debug(DebugType::INFO, "Renderbuffer created: %u", _rbo);
    glBindRenderbuffer(GL_RENDERBUFFER, _rbo);
    glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, width, height);
    glBindRenderbuffer(GL_RENDERBUFFER, 0);
    glFramebufferRenderbuffer(
        GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, _rbo
    );

    bool is_ready
        = glCheckFramebufferStatus(GL_FRAMEBUFFER) == GL_FRAMEBUFFER_COMPLETE;
    if (!is_ready) {
        debug(DebugType::ERROR, "Framebuffer %u is not complete!", _id);
    }

    unbind();
    _texture->unbind();
}

void Framebuffer::bind() {
    glBindFramebuffer(GL_FRAMEBUFFER, _id);
}

void Framebuffer::unbind() {
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void Framebuffer::resize(std::uint16_t width, std::uint16_t height) {
    bind();
    _texture->bind();
    GLuint tex_id = _texture->id();
    glTexImage2D(
        GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE,
        NULL
    );
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    glFramebufferTexture2D(
        GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, tex_id, 0
    );

    glBindRenderbuffer(GL_RENDERBUFFER, _rbo);
    glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, width, height);
    glBindRenderbuffer(GL_RENDERBUFFER, 0);

    bool is_ready
        = glCheckFramebufferStatus(GL_FRAMEBUFFER) == GL_FRAMEBUFFER_COMPLETE;
    if (!is_ready) {
        debug(DebugType::ERROR, "Framebuffer %u is not complete!", _id);
    }

    debug(DebugType::INFO, "Framebuffer resized: %u", _id);
    unbind();
    _texture->unbind();
}

std::shared_ptr<Texture> Framebuffer::texture() const {
    return _texture;
}

GLuint Framebuffer::rbo() const {
    return _rbo;
}

void Framebuffer::clear_color(float r, float g, float b, float a) {
    glClearColor(r, g, b, a);
}

void Framebuffer::clear(GLbitfield mask) {
    glClear(mask);
}

void Framebuffer::destroy() {
    GLuint id = _id;
    GLuint rbo_id = _rbo;
    glDeleteFramebuffers(1, &_id);
    debug(DebugType::INFO, "Framebuffer destroyed: %u", id);
    glDeleteRenderbuffers(1, &_rbo);
    debug(DebugType::INFO, "Renderbuffer destroyed: %u", rbo_id);
}

Framebuffer::Framebuffer() {
    glGenFramebuffers(1, &_id);
    debug(DebugType::INFO, "Framebuffer created: %u", _id);
}

void Framebuffer::Deleter::operator()(Framebuffer *fbo) {
    fbo->destroy();
    delete fbo;
}

} // namespace gl

} // namespace axolote
