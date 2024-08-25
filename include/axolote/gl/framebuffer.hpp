/**
 * @file framebuffer.hpp
 * @brief Framebuffer class
 * @author João Vitor Espig (jotaespig@gmail.com)
 **/
#pragma once

#include <memory>

#include "axolote/gl/opengl_object.hpp"
#include "axolote/gl/texture.hpp"
#include "axolote/glad/glad.h"

namespace axolote {

namespace gl {

/**
 * @brief Framebuffer class
 * @author João Vitor Espig (jotaespig@gmail.com)
 **/
class Framebuffer : public OpenGLObject {
public:
    template <typename... Args>
    static std::shared_ptr<Framebuffer> create(Args &&...args);

private:
    struct Deleter {
        void operator()(Framebuffer *framebuffer);
    };

    GLuint _id;
    std::shared_ptr<Texture> _texture;
    GLuint _rbo;

    Framebuffer();
};

template <typename... Args>
std::shared_ptr<Framebuffer> Framebuffer::create(Args &&...args) {
    return std::shared_ptr<Framebuffer>{
        new Framebuffer{std::forward<Args>(args)...}, Deleter{}
    };
}

} // namespace gl

} // namespace axolote
