/**
 * \file texture.hpp
 * \brief Texture class
 * \author João Vitor Espig (JotaEspig)
 * \date October 04, 2023
 * \version November 06, 2023
 **/
#pragma once

#include <string>

#include <GL/gl.h>

namespace axolote
{

/**
 * \brief texture operations
 * \author João Vitor Espig (JotaEspig)
 * \date October 04, 2023
 * \version November 06, 2023
 **/
class Texture
{
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
     * \date October 04, 2023
     * \version October 08, 2023
     **/
    Texture();
    /**
     * \brief Copy constructor
     * \author João Vitor Espig (JotaEspig)
     * \date November 06, 2023
     * \version November 06, 2023
     * \param texture - Texture object
     **/
    Texture(const Texture &texture);
    /**
     * \brief Move constructor
     * \author João Vitor Espig (JotaEspig)
     * \date November 06, 2023
     * \version November 06, 2023
     * \param texture - Texture object
     **/
    Texture(Texture &&texture);
    /**
     * \brief Constructor
     * \author João Vitor Espig (JotaEspig)
     * \date October 04, 2023
     * \version October 08, 2023
     * \param texture_filename - name of texture file
     * \param tex_type - type of text ("diffuse" or "specular")
     * \param _unit - texture unit (used inside OpenGL shaders)
     **/
    Texture(const char *texture_filename, std::string tex_type, GLuint _unit);

    /**
     * \brief activates texture
     * \author João Vitor Espig (JotaEspig)
     * \date October 04, 2023
     * \version October 04, 2023
     **/
    void activate();
    /**
     * \brief binds texture
     * \author João Vitor Espig (JotaEspig)
     * \date October 04, 2023
     * \version October 04, 2023
     **/
    void bind();
    /**
     * \brief unbinds texture
     * \author João Vitor Espig (JotaEspig)
     * \date October 04, 2023
     * \version October 04, 2023
     **/
    void unbind();
    /**
     * \brief destroys texture
     * \author João Vitor Espig (JotaEspig)
     * \date October 04, 2023
     * \version October 04, 2023
     **/
    void destroy();
    /**
     * \brief operator = overload (copy)
     * \author João Vitor Espig (JotaEspig)
     * \date November 06, 2023
     * \version November 06, 2023
     * \param texture - Texture object
     **/
    void operator=(const Texture &texture);
    /**
     * \brief operator = overload (copy)
     * \author João Vitor Espig (JotaEspig)
     * \date November 06, 2023
     * \version November 06, 2023
     * \param texture - Texture object
     **/
    void operator=(Texture &&texture);
};

} // namespace axolote
