/**
 * \file drawable.hpp
 * \brief provides Java-like interface
 * \author João Vitor Espig (JotaEspig)
 * \date October 25, 2023
 * \version October 27, 2023
 **/
#pragma once

#include <glm/glm.hpp>

namespace axolote {

/**
 * \brief describes things that can draw
 * \author João Vitor Espig (JotaEspig)
 * \date October 25, 2023
 * \version October 27, 2023
 **/
class Drawable {
public:
    /**
     * \brief virtual function draw
     * \author João Vitor Espig (JotaEspig)
     **/
    virtual void draw() = 0;
    /**
     * \brief virtual function draw using a matrix 4x4 as the model matrix
     * \author João Vitor Espig (JotaEspig)
     **/
    virtual void draw(const glm::mat4 &mat) = 0;
};

} // namespace axolote
