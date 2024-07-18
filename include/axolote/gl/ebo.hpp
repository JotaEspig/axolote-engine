/**
 * \file ebo.hpp
 * \brief OpenGL EBO operations handler
 * \author João Vitor Espig (JotaEspig)
 *
 * this file contains a class called EBO that handles OpenGL EBO operations:
 * Bind, Unbind and destroy
 **/
#pragma once

#include <vector>

#include "axolote/glad/glad.h"

namespace axolote {

namespace gl {

/**
 * \brief OpenGL EBO handler
 * \author João Vitor Espig (JotaEspig)
 **/
class EBO {
public:
    /** OpenGL EBO id **/
    GLuint id;

    /**
     * \brief Constructor
     * \author João Vitor Espig (JotaEspig)
     **/
    EBO();
    /**
     * \brief Constructor
     * \author João Vitor Espig (JotaEspig)
     * \param indices - array of indices
     **/
    EBO(const std::vector<GLuint> &indices);

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
     * \brief buffer data
     * \author João Vitor Espig (JotaEspig)
     * \data June 07, 2024
     * \version June 07, 2024
     * \param size - size of the data
     * \param data - pointer to the data
     * \param usage - usage of the data
     **/
    void buffer_data(
        std::size_t size, const void *data, GLenum usage = GL_STATIC_DRAW
    );
    /**
     * \brief destroys
     * \author João Vitor Espig (JotaEspig)
     **/
    void destroy();
};

} // namespace gl

} // namespace axolote
