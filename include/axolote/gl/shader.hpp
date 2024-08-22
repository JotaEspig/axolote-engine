/**
 * \file shader.hpp
 * \brief Shader class
 * \author João Vitor Espig (JotaEspig)
 **/
#pragma once

#include <memory>
#include <string>
#include <utility>

#include <glm/glm.hpp>

#include "axolote/glad/glad.h"

#include "axolote/gl/opengl_object.hpp"

namespace axolote {

namespace gl {

/**
 * \brief OpenGL shader handler
 * \author João Vitor Espig (JotaEspig)
 **/
class Shader : public OpenGLObject {
public:
    /**
     * \brief Creates a Shader object
     * \author João Vitor Espig (JotaEspig)
     * \return shared pointer to Shader object
     **/
    template <typename... Args>
    static std::shared_ptr<Shader> create(Args &&...args);

    /**
     * \brief id getter
     * \author João Vitor Espig (JotaEspig)
     **/
    GLuint id() const override;
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
    void destroy() override;

private:
    struct Deleter {
        void operator()(Shader *shader);
    };

    /** OpenGL shader id **/
    GLuint _id;

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
    Shader(std::string vertex_file, std::string fragment_file);
};

template <typename... Args>
std::shared_ptr<Shader> Shader::create(Args &&...args) {
    return std::shared_ptr<Shader>{
        new Shader{std::forward<Args>(args)...}, Shader::Deleter{}
    };
}

} // namespace gl

} // namespace axolote
