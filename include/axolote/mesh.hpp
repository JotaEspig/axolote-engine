/**
 * \file mesh.hpp
 * \brief Mesh class
 * \author João Vitor Espig (JotaEspig)
 * \date October 04, 2023
 * \version November 06, 2023
 **/
#pragma once

#include <vector>

#include <GL/gl.h>
#include <glm/glm.hpp>

#include <axolote/shader.hpp>
#include <axolote/structs.hpp>
#include <axolote/texture.hpp>

namespace axolote
{

/**
 * \brief defines a polygon mesh
 * \author João Vitor Espig (JotaEspig)
 * \date October 04, 2023
 * \version November 06, 2023
 **/
class Mesh
{
public:
    /** polygon mesh vertices **/
    std::vector<Vertex> vertices;
    /** polygon mesh indices **/
    std::vector<GLuint> indices;
    /** textures to be rendered **/
    std::vector<Texture> textures;

    /**
     * \brief Constructor
     * \author João Vitor Espig (JotaEspig)
     * \date October 04, 2023
     * \version October 04, 2023
     **/
    Mesh();
    /**
     * \brief Copy constructor
     * \author João Vitor Espig (JotaEspig)
     * \date November 06, 2023
     * \version November 06, 2023
     * \param mesh - Mesh object
     **/
    Mesh(const Mesh &mesh);
    /**
     * \brief Move constructor
     * \author João Vitor Espig (JotaEspig)
     * \date November 06, 2023
     * \version November 06, 2023
     * \param mesh - Mesh object
     **/
    Mesh(Mesh &&mesh);
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
        const std::vector<Texture> &_textures
    );

    /**
     * \brief operator = overload (copy)
     * \author João Vitor Espig (JotaEspig)
     * \date November 06, 2023
     * \version November 06, 2023
     * \param mesh - Mesh object
     **/
    void operator=(const Mesh &mesh);
    /**
     * \brief operator = overload (move)
     * \author João Vitor Espig (JotaEspig)
     * \date November 06, 2023
     * \version November 06, 2023
     * \param mesh - Mesh object
     **/
    void operator=(Mesh &&mesh);
};

} // namespace axolote
