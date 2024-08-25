/**
 * @file structs.hpp
 * @brief Useful structs used by Axolote Engine
 * @author João Vitor Espig (jotaespig@gmail.com)
 **/
#pragma once

#include <glm/glm.hpp>

namespace axolote {

/**
 * @brief defines a vertex
 * @author João Vitor Espig (jotaespig@gmail.com)
 **/
struct Vertex {
    /** position vector **/
    glm::vec3 pos;
    /** color vector **/
    glm::vec4 color;
    /** textures coordinates **/
    glm::vec2 tex_UV;
    /** normal vector **/
    glm::vec3 normal;
};

/**
 * @brief defines a color using RGBA
 * @author João Vitor Espig (jotaespig@gmail.com)
 **/
struct Color {
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
