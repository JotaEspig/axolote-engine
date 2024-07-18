/**
 * \file vao.hpp
 * \brief OpenGL VAO operations handler
 * \author João Vitor Espig (JotaEspig)
 *
 * this file contains a class called VAO that handles OpenGL VAO operations:
 * Bind, Unbind and destroy
 **/
#pragma once

#include "axolote/gl/vbo.hpp"

namespace axolote {

namespace gl {

/**
 * \brief OpenGL VAO handler
 * \author João Vitor Espig (JotaEspig)
 **/
class VAO {
public:
    /** OpenGL VAO id **/
    GLuint id;

    /**
     * \brief Constructor
     * \author João Vitor Espig (JotaEspig)
     **/
    VAO();

    /**
     * \brief links an attribute
     * \author João Vitor Espig (JotaEspig)
     * \param vbo - VBO object
     * \param layout - layout index (used in inside OpenGL shaders)
     * \param num_components - number of components in attribute
     * \param type - data type of the components
     * \param size - size of attribute
     * \param offset - offset to attribute according to VBO object
     **/
    void link_attrib(
        VBO &vbo, GLuint layout, GLuint num_components, GLenum type,
        GLsizeiptr size, void *offset
    );
    /**
     * \brief Divides correctly attrib
     * \author João Vitor Espig (JotaEspig)
     * \param vbo - VBO object
     * \param layout - index
     * \param divisor - divisor
     **/
    void attrib_divisor(VBO &vbo, GLuint index, GLuint divisor);
    /**
     * \brief binds
     * \author João Vitor Espig (JotaEspig)
     **/
    void bind();
    /**
     * \brief unbinds
     * \author João Vitor Espig (JotaEspig)
     **/
    void unbind();
    /**
     * \brief destroys
     * \author João Vitor Espig (JotaEspig)
     **/
    void destroy();
};

} // namespace gl

} // namespace axolote
