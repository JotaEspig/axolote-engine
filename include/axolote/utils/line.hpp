/**
 * \file line.hpp
 * \brief Line object
 * \author João Vitor Espig (JotaEspig)
 * \date December 12, 2023
 * \version December 12, 2023
 **/
#pragma once

#include <glm/glm.hpp>

#include <axolote/object3d.hpp>

namespace axolote
{

/**
 * \brief Defines a drawable line
 * \author João Vitor Espig (JotaEspig)
 * \date December 12, 2023
 * \version December 12, 2023
 *
 * Abstraction from the equation: r = a + λb
 * See: https://www.cuemath.com/algebra/vector-equation/
 **/
class Line : public axolote::Object3D
{
public:
    /** starting point **/
    glm::vec3 a;
    /** direction vector **/
    glm::vec3 dir_vec;
    /** limit for the λ **/
    float length;
    /** line thickness **/
    float thickness;
    /** line color **/
    glm::vec3 color;

    /**
     * \brief Constructor
     * \author João Vitor Espig (JotaEspig)
     * \date December 12, 2023
     * \version December 12, 2023
     * \param point - starting point
     * \param direction_vector - direction vector
     * \param length - line length
     * \param thickness - line thickness
     **/
    Line(
        const glm::vec3 &point, const glm::vec3 &direction_vector, float length,
        float thickness, const glm::vec3 &color
    );

    /**
     * \brief build the mesh for the line
     * \author João Vitor Espig (JotaEspig)
     * \date December 12, 2023
     * \version December 12, 2023
     **/
    void build_mesh();
};

} // namespace axolote
