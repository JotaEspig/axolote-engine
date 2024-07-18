/**
 * \file texture.hpp
 * \brief Texture class
 * \author João Vitor Espig (JotaEspig)
 **/
#pragma once

#include <string>

#include "axolote/glad/glad.h"

namespace axolote {

namespace gl {

/**
 * \brief texture operations
 * \author João Vitor Espig (JotaEspig)
 **/
class Texture {
public:
    /** OpenGL texture id **/
    GLuint id;
    /** texture type **/
    std::string type;
    /** OpenGL texture unit **/
    GLuint unit;
    /** texture is loaded **/
    bool loaded;

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
    Texture(const char *texture_filename, std::string tex_type, GLuint _unit);

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
    void destroy();
};

} // namespace gl

} // namespace axolote
