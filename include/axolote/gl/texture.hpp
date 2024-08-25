/**
 * @file texture.hpp
 * @brief Texture class
 * @author João Vitor Espig (jotaespig@gmail.com)
 **/
#pragma once

#include <memory>
#include <string>

#include "axolote/glad/glad.h"

#include "axolote/gl/opengl_object.hpp"

namespace axolote {

namespace gl {

/**
 * @brief texture operations
 * @author João Vitor Espig (jotaespig@gmail.com)
 **/
class Texture : public OpenGLObject {
public:
    /**
     * @brief Creates a texture
     * @author João Vitor Espig (jotaespig@gmail.com)
     * @return shared pointer to texture
     **/
    template <typename... Args>
    static std::shared_ptr<Texture> create(Args &&...args);

    /**
     * @brief id getter
     * @author João Vitor Espig (jotaespig@gmail.com)
     **/
    GLuint id() const override;
    /**
     * @brief type getter
     * @author João Vitor Espig (jotaespig@gmail.com)
     **/
    std::string type() const;
    /**
     * @brief unit getter
     * @author João Vitor Espig (jotaespig@gmail.com)
     **/
    GLuint unit() const;
    /**
     * @brief loaded getter
     * @author João Vitor Espig (jotaespig@gmail.com)
     **/
    bool is_loaded() const;
    /**
     * @brief activates texture
     * @author João Vitor Espig (jotaespig@gmail.com)
     **/
    void activate();
    /**
     * @brief binds texture
     * @author João Vitor Espig (jotaespig@gmail.com)
     **/
    void bind();
    /**
     * @brief unbinds texture
     * @author João Vitor Espig (jotaespig@gmail.com)
     **/
    void unbind();
    /**
     * @brief destroys texture
     * @author João Vitor Espig (jotaespig@gmail.com)
     **/
    void destroy() override;

private:
    struct Deleter {
        void operator()(Texture *texture);
    };

    /** OpenGL texture id **/
    GLuint _id;
    /** texture type **/
    std::string _type;
    /** OpenGL texture unit **/
    GLuint _unit = 0;
    /** texture is loaded **/
    bool _loaded = false;

    /**
     * @brief Constructor
     * @author João Vitor Espig (jotaespig@gmail.com)
     **/
    Texture();
    /**
     * @brief Constructor
     * @author João Vitor Espig (jotaespig@gmail.com)
     * @param texture_filename name of texture file
     * @param tex_type type of text ("diffuse" or "specular")
     * @param _unit texture unit (used inside OpenGL shaders)
     **/
    Texture(std::string texture_filename, std::string tex_type, GLuint unit);
};

template <typename... Args>
std::shared_ptr<Texture> Texture::create(Args &&...args) {
    return std::shared_ptr<Texture>{
        new Texture{std::forward<Args>(args)...}, Deleter{}
    };
}

} // namespace gl

} // namespace axolote
