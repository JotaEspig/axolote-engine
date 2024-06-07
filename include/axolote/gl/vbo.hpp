/**
 * \file vbo.hpp
 * \brief OpenGL VBO operations handler
 * \author João Vitor Espig (JotaEspig)
 * \date October 04, 2023
 * \version May 23, 2024
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
 * \date October 04, 2023
 * \version May 23, 2024
 **/
class VBO {
public:
    /** OpenGL VBO id **/
    GLuint id;

    /**
     * \brief Constructor
     * \author João Vitor Espig (JotaEspig)
     * \date October 04, 2023
     * \version October 04, 2023
     **/
    VBO();
    /**
     * \brief Constructor
     * \author João Vitor Espig (JotaEspig)
     * \date October 04, 2023
     * \version October 04, 2023
     * \param vertices - array of vertex
     **/
    template <class T>
    VBO(const std::vector<T> &vertices) {
        glGenBuffers(1, &id);
        glBindBuffer(GL_ARRAY_BUFFER, id);
        glBufferData(
            GL_ARRAY_BUFFER, vertices.size() * sizeof(T), vertices.data(),
            GL_STATIC_DRAW
        );
    }

    /**
     * \brief binds
     * \author João Vitor Espig (JotaEspig)
     * \date October 04, 2023
     * \version October 04, 2023
     **/
    void bind();
    /**
     * \brief unbinds
     * \author João Vitor Espig (JotaEspig)
     * \date October 04, 2023
     * \version October 04, 2023
     **/
    void unbind();
    /**
     * \brief destroys
     * \author João Vitor Espig (JotaEspig)
     * \date October 04, 2023
     * \version October 04, 2023
     **/
    void destroy();
};

} // namespace gl

} // namespace axolote
