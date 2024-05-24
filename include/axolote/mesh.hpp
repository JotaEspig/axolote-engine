/**
 * \file mesh.hpp
 * \brief Mesh struct
 * \author João Vitor Espig (JotaEspig)
 * \date October 04, 2023
 * \version May 23, 2024
 **/
#pragma once

#include <vector>

#include <GL/gl.h>
#include <glm/glm.hpp>

#include "axolote/gl/texture.hpp"
#include "axolote/structs.hpp"

namespace axolote {

/**
 * \brief defines a polygon mesh
 * \author João Vitor Espig (JotaEspig)
 * \date October 04, 2023
 * \version May 23, 2024
 **/
struct Mesh {
    /** polygon mesh vertices **/
    std::vector<Vertex> vertices;
    /** polygon mesh indices **/
    std::vector<GLuint> indices;
    /** textures to be rendered **/
    std::vector<gl::Texture> textures;

    /**
     * \brief Constructor
     * \author João Vitor Espig (JotaEspig)
     * \date October 04, 2023
     * \version October 04, 2023
     **/
    Mesh();
    /**
     * \brief Constructor
     * \author João Vitor Espig (JotaEspig)
     * \date October 04, 2023
     * \version October 08, 2023
     * \param _vertices - polygon mesh vertices
     * \param _indices - polygon mesh indices
     * \param _textures - textures to be rendered with polygon mesh
     **/
    Mesh(
        const std::vector<Vertex> &_vertices,
        const std::vector<GLuint> &_indices,
        const std::vector<gl::Texture> &_textures
    );
};

} // namespace axolote
