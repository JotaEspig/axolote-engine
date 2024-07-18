/**
 * \file vbo.hpp
 * \brief OpenGL VBO operations handler
 * \author João Vitor Espig (JotaEspig)
 *
 * this file contains a class called VBO that handles OpenGL VBO operations:
 * Bind, Unbind and destroy
 **/
#pragma once

#include <vector>

#include <glm/glm.hpp>

#include "axolote/glad/glad.h"

namespace axolote {

namespace gl {

/**
 * \brief OpenGL VBO handler
 * \author João Vitor Espig (JotaEspig)
 **/
class VBO {
public:
    /** OpenGL VBO id **/
    GLuint id;

    /**
     * \brief Constructor
     * \author João Vitor Espig (JotaEspig)
     **/
    VBO();
    /**
     * \brief Constructor
     * \author João Vitor Espig (JotaEspig)
     * \param vertices - array of vertex
     **/
    template <class T>
    VBO(const std::vector<T> &vertices);
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

template <class T>
VBO::VBO(const std::vector<T> &vertices) :
  VBO{} {
    bind();
    buffer_data(vertices.size() * sizeof(T), vertices.data(), GL_STATIC_DRAW);
  }

} // namespace gl

} // namespace axolote
