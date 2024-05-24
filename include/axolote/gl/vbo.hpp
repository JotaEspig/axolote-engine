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

#include <GL/gl.h>
#include <glm/glm.hpp>

#include "axolote/structs.hpp"

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
    VBO(const std::vector<Vertex> &vertices);

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
