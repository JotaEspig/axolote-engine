/**
 * @file mesh.hpp
 * @brief Mesh struct
 * @author João Vitor Espig (jotaespig@gmail.com)
 **/
#pragma once

#include <vector>

#include <glm/glm.hpp>

#include "axolote/glad/glad.h"

#include "axolote/gl/texture.hpp"
#include "axolote/structs.hpp"

namespace axolote {

/**
 * @brief defines a polygon mesh
 * @author João Vitor Espig (jotaespig@gmail.com)
 **/
struct Mesh {
    /** polygon mesh vertices **/
    std::vector<Vertex> vertices;
    /** polygon mesh indices **/
    std::vector<GLuint> indices;
    /** textures to be rendered **/
    std::vector<std::shared_ptr<gl::Texture>> textures;

    /**
     * @brief Constructor
     * @author João Vitor Espig (jotaespig@gmail.com)
     **/
    Mesh();
    /**
     * @brief Constructor
     * @author João Vitor Espig (jotaespig@gmail.com)
     * @param _vertices polygon mesh vertices
     * @param _indices polygon mesh indices
     * @param _textures textures to be rendered with polygon mesh
     **/
    Mesh(
        const std::vector<Vertex> &_vertices,
        const std::vector<GLuint> &_indices,
        const std::vector<std::shared_ptr<gl::Texture>> &_textures
    );
};

} // namespace axolote
