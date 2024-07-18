/**
 * \file shader.hpp
 * \brief Shader class
 * \author João Vitor Espig (JotaEspig)
 **/
#pragma once

#include <glm/glm.hpp>

#include "axolote/glad/glad.h"

namespace axolote {

namespace gl {

/**
 * \brief OpenGL shader handler
 * \author João Vitor Espig (JotaEspig)
 **/
class Shader {
public:
    /** OpenGL shader id **/
    GLuint id;

    /**
     * \brief Constructor
     * \author João Vitor Espig (JotaEspig)
     **/
    Shader();
    /**
     * \brief Constructor
     * \author João Vitor Espig (JotaEspig)
     * \param vertex_file - vertex glsl file
     * \param fragment_file - fragment glsl file
     **/
    Shader(const char *vertex_file, const char *fragment_file);

    /**
     * \brief sets a value in an integer uniform
     * \author João Vitor Espig (JotaEspig)
     * \param uniform_name - name of uniform variable
     * \param value - integer value
     **/
    void set_uniform_int(const char *uniform_name, int value);
    /**
     * \brief sets a value in a matrix 4x4 uniform
     * \author João Vitor Espig (JotaEspig)
     * \param uniform_name - name of uniform variable
     * \param matrix - matrix 4x4 value
     **/
    void set_uniform_matrix4(const char *uniform_name, const glm::mat4 &matrix);
    /**
     * \brief sets a value in a matrix 4x4 uniform
     * \author João Vitor Espig (JotaEspig)
     * \param uniform_name - name of uniform variable
     * \param x - float value
     **/
    void set_uniform_float(const char *uniform_name, float x);
    /**
     * \brief sets a value in a vector of 3 floats uniform
     * \author João Vitor Espig (JotaEspig)
     * \param uniform_name - name of uniform variable
     * \param x - first float value
     * \param y - second float value
     * \param z - third float value
     **/
    void
    set_uniform_float3(const char *uniform_name, float x, float y, float z);
    /**
     * \brief sets a value in a vector of 4 floats uniform
     * \author João Vitor Espig (JotaEspig)
     * \param uniform_name - name of uniform variable
     * \param x - first float value
     * \param y - second float value
     * \param z - third float value
     * \param w - fourth float value
     **/
    void set_uniform_float4(
        const char *uniform_name, float x, float y, float z, float w
    );
    /**
     * \brief activates shader
     * \author João Vitor Espig (JotaEspig)
     **/
    void activate();
    /**
     * \brief destroys shader
     * \author João Vitor Espig (JotaEspig)
     **/
    void destroy();
};

} // namespace gl

} // namespace axolote
