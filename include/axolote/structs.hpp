/**
 * \file structs.hpp
 * \brief Useful structs used by Axolote Engine
 * \author João Vitor Espig (JotaEspig)
 * \date October 04, 2023
 * \version October 04, 2023
 **/
#pragma once

#include <glm/glm.hpp>

namespace axolote
{

/**
 * \brief defines a vertex
 * \author João Vitor Espig (JotaEspig)
 * \date October 04, 2023
 * \version October 04, 2023
 **/
struct Vertex
{
    /** position vector **/
    glm::vec3 position;
    /** color vector **/
    glm::vec3 color;
    /** textures coordinates **/
    glm::vec2 tex_UV;
    /** normal vector **/
    glm::vec3 normal;
};

/**
 * \brief defines a color using RGBA
 * \author João Vitor Espig (JotaEspig)
 * \date October 04, 2023
 * \version October 04, 2023
 **/
struct Color
{
    /** red **/
    float r;
    /** green **/
    float g;
    /** blue **/
    float b;
    /** alpha **/
    float opacity;
};

} // namespace axolote
