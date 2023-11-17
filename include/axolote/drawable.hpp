/**
 * \file idrawable.hpp
 * \brief provides Java-like interface
 * \author João Vitor Espig (JotaEspig)
 * \date October 25, 2023
 * \version October 27, 2023
 **/
#pragma once

#include <axolote/shader.hpp>

namespace axolote
{

/**
 * \brief describes things that can draw
 * \author João Vitor Espig (JotaEspig)
 * \date October 25, 2023
 * \version October 27, 2023
 **/
class Drawable
{
public:
    virtual void draw() = 0;
    virtual void draw(const glm::mat4 &mat) = 0;
};

} // namespace axolote
