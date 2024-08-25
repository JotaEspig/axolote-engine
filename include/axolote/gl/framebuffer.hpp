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
    /**
     * @brief id getter
     * @author João Vitor Espig (jotaespig@gmail.com)
     **/
    GLuint id() const override;
    /**
     * @brief Initializes the framebuffer with a given width and height
     * @author João Vitor Espig (jotaespig@gmail.com)
     **/
    void init(std::uint16_t width, std::uint16_t height);
    /**
     * @brief Bind the framebuffer to the OpenGL context
     * @author João Vitor Espig (jotaespig@gmail.com)
     **/
    void bind();
    /**
     * @brief Unbind the framebuffer from the OpenGL context
     * @author João Vitor Espig (jotaespig@gmail.com)
     **/
    void unbind();
    /**
     * @brief destroys
     * @author João Vitor Espig (jotaespig@gmail.com)
     **/
    void destroy() override;

private:
    struct Deleter {
        void operator()(Framebuffer *fbo);
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
