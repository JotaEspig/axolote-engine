/**
 * \file texture.hpp
 * \brief Texture class
 * \author João Vitor Espig (JotaEspig)
 **/
#pragma once

#include <memory>
#include <string>

#include "axolote/glad/glad.h"

#include "axolote/gl/opengl_object.hpp"

namespace axolote {

namespace gl {

/**
 * \brief texture operations
 * \author João Vitor Espig (JotaEspig)
 **/
class Texture : public OpenGLObject {
public:
    /**
     * \brief Creates a texture
     * \author João Vitor Espig (JotaEspig)
     * \return shared pointer to texture
     **/
    template <typename... Args>
    static std::shared_ptr<Texture> create(Args &&...args);

    /**
     * \brief id getter
     * \author João Vitor Espig (JotaEspig)
     **/
    GLuint id() const override;
    /**
     * \brief type getter
     * \author João Vitor Espig (JotaEspig)
     **/
    std::string type() const;
    /**
     * \brief unit getter
     * \author João Vitor Espig (JotaEspig)
     **/
    GLuint unit() const;
    /**
     * \brief loaded getter
     * \author João Vitor Espig (JotaEspig)
     **/
    bool is_loaded() const;
    /**
     * \brief activates texture
     * \author João Vitor Espig (JotaEspig)
     **/
    void activate();
    /**
     * \brief binds texture
     * \author João Vitor Espig (JotaEspig)
     **/
    void bind();
    /**
     * \brief unbinds texture
     * \author João Vitor Espig (JotaEspig)
     **/
    void unbind();
    /**
     * \brief destroys texture
     * \author João Vitor Espig (JotaEspig)
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
    GLuint _unit;
    /** texture is loaded **/
    bool _loaded = false;

    /**
     * \brief Constructor
     * \author João Vitor Espig (JotaEspig)
     **/
    Texture();
    /**
     * \brief Constructor
     * \author João Vitor Espig (JotaEspig)
     * \param texture_filename - name of texture file
     * \param tex_type - type of text ("diffuse" or "specular")
     * \param _unit - texture unit (used inside OpenGL shaders)
     **/
    Texture(const char *texture_filename, std::string tex_type, GLuint unit);
};

template <typename... Args>
std::shared_ptr<Texture> Texture::create(Args &&...args) {
    return std::shared_ptr<Texture>{
        new Texture{std::forward<Args>(args)...}, Deleter{}
    };
}

} // namespace gl

} // namespace axolote
