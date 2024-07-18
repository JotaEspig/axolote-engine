/**
 * \file mesh.hpp
 * \brief Mesh struct
 * \author João Vitor Espig (JotaEspig)
 **/
#pragma once

#include <vector>

#include <glm/glm.hpp>

#include "axolote/glad/glad.h"

#include "axolote/gl/texture.hpp"
#include "axolote/structs.hpp"

namespace axolote {

/**
 * \brief defines a polygon mesh
 * \author João Vitor Espig (JotaEspig)
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
     **/
    Mesh();
    /**
     * \brief Constructor
     * \author João Vitor Espig (JotaEspig)
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
