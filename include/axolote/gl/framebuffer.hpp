/**
 * @file framebuffer.hpp
 * @brief Framebuffer class
 * @author João Vitor Espig (jotaespig@gmail.com)
 **/
#pragma once

#include <memory>
#include <cstdint>

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
    /**
     * @brief Creates a framebuffer
     *
     * @tparam Args
     * @param args
     * @return std::shared_ptr<Framebuffer>
     */
    template <typename... Args>
    static std::shared_ptr<Framebuffer> create(Args &&...args);
    /**
     * @brief id getter
     * @author João Vitor Espig (jotaespig@gmail.com)
     * @return GLuint - framebuffer id
     **/
    GLuint id() const override;
    /**
     * @brief Initializes the framebuffer with a given width and height
     * @author João Vitor Espig (jotaespig@gmail.com)
     * @param width framebuffer width
     * @param height framebuffer height
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
     * @brief texture getter
     * @author João Vitor Espig (jotaespig@gmail.com)
     * @return std::shared_ptr<Texture> - texture pointer
     **/
    std::shared_ptr<Texture> texture() const;
    /**
     * @brief Renderbuffer id getter
     * @author João Vitor Espig (jotaespig@gmail.com)
     * @return GLuint - renderbuffer id
     **/
    GLuint rbo() const;
    /**
     * @brief Resize the framebuffer to a given width and height
     * @author João Vitor Espig (jotaespig@gmail.com)
     * @param width new width
     * @param height new height
     **/
    void resize(std::uint16_t width, std::uint16_t height);
    /**
     * @brief clear color of the framebuffer
     * @author João Vitor Espig (jotaespig@gmail.com)
     * @param r red
     * @param g green
     * @param b blue
     * @param a alpha
     **/
    void clear_color(float r, float g, float b, float a);
    /**
     * @brief clear the framebuffer with a given mask
     * @author João Vitor Espig (jotaespig@gmail.com)
     * @param mask mask to clear
     **/
    void clear(GLbitfield mask);
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

    /**
     * @brief Construct a new Framebuffer object
     **/
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
