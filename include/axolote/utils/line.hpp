/**
 * \file line.hpp
 * \brief Line object
 * \author João Vitor Espig (JotaEspig)
 **/
#pragma once

#include <glm/glm.hpp>

#include "axolote/object3d.hpp"

namespace axolote {

/**
 * \brief Defines a drawable line
 * \author João Vitor Espig (JotaEspig)
 *
 * Abstraction from the equation: r = a + λb
 * See: https://www.cuemath.com/algebra/vector-equation/
 **/
class Line : public axolote::Object3D {
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
    /** quality of line **/
    float line_quality;

    /**
     * \brief Constructor
     * \author João Vitor Espig (JotaEspig)
     * \param point - starting point
     * \param direction_vector - direction vector
     * \param length - line length
     * \param thickness - line thickness
     * \param color - line color
     * \param line_quality - line quality
     **/
    Line(
        const glm::vec3 &point, const glm::vec3 &direction_vector, float length,
        float thickness, const glm::vec3 &color, float line_quality = 20.0f
    );

    /**
     * \brief build the mesh for the line
     * \author João Vitor Espig (JotaEspig)
     **/
    void build_mesh();

    /**
     * \brief set line end point
     * \author Mickael Reichert (mickaelrei)
     * \param end - end point
     **/
    void set_end(const glm::vec3 &end);

    /**
     *
     * it uses the point A and the direction vector
     **/
    void update(double dt) override;
    /**
     * \brief draws the line using set_matrix before
     * \author João Vitor Espig (JotaEspig)
     **/
    void draw() override;

private:
    // TODO these 2 functions is not working correctly, fix it
    // Maybe I should consider to try a different method instead of this
    // Ask for help from a professor
    float get_rotation_around_x() const;
    float get_rotation_around_y() const;
};

} // namespace axolote
