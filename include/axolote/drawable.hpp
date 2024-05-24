/**
 * \file drawable.hpp
 * \brief provides Java-like interface
 * \author João Vitor Espig (JotaEspig)
 * \date October 25, 2023
 * \version May 24, 2024
 **/
#pragma once

#include <glm/glm.hpp>

#include "axolote/gl/shader.hpp"

namespace axolote {

/**
 * \brief describes things that can draw
 * \author João Vitor Espig (JotaEspig)
 * \date October 25, 2023
 * \version May 24, 2024
 **/
class Drawable {
public:
    /**
     * \brief virtual function bind_shader
     * \author João Vitor Espig (JotaEspig)
     **/
    virtual void bind_shader(const gl::Shader &shader_program) = 0;
    /**
     * \brief virtual function get_shader
     * \author João Vitor Espig (JotaEspig)
     **/
    virtual gl::Shader get_shader() const = 0;
    /**
     * \brief virtual function update
     * \author João Vitor Espig (JotaEspig)
     **/
    virtual void update(double dt) = 0;
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
