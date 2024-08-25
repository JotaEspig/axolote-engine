/**
 * @file vao.hpp
 * @brief OpenGL VAO operations handler
 * @author João Vitor Espig (jotaespig@gmail.com)
 *
 * this file contains a class called VAO that handles OpenGL VAO operations:
 * Bind, Unbind and destroy
 **/
#pragma once

#include <memory>
#include <utility>

#include "axolote/gl/opengl_object.hpp"
#include "axolote/gl/vbo.hpp"

namespace axolote {

namespace gl {

/**
 * @brief OpenGL VAO handler
 * @author João Vitor Espig (jotaespig@gmail.com)
 **/
class VAO : public OpenGLObject {
public:
    /**
     * @brief Creates a VAO object
     * @author João Vitor Espig (jotaespig@gmail.com)
     * @return shared pointer to VAO object
     **/
    template <typename... Args>
    static std::shared_ptr<VAO> create(Args &&...args);

    /**
     * @brief id getter
     * @author João Vitor Espig (jotaespig@gmail.com)
     **/
    GLuint id() const override;
    /**
     * @brief links an attribute
     * @author João Vitor Espig (jotaespig@gmail.com)
     * @param vbo VBO object
     * @param layout layout index (used in inside OpenGL shaders)
     * @param num_components number of components in attribute
     * @param type data type of the components
     * @param size size of attribute
     * @param offset offset to attribute according to VBO object
     **/
    void link_attrib(
        std::shared_ptr<VBO> vbo, GLuint layout, GLuint num_components,
        GLenum type, GLsizeiptr size, void *offset
    );
    /**
     * @brief Divides correctly attrib
     * @author João Vitor Espig (jotaespig@gmail.com)
     * @param vbo VBO object
     * @param layout index
     * @param divisor divisor
     **/
    void attrib_divisor(std::shared_ptr<VBO> vbo, GLuint index, GLuint divisor);
    /**
     * @brief binds
     * @author João Vitor Espig (jotaespig@gmail.com)
     **/
    void bind();
    /**
     * @brief unbinds
     * @author João Vitor Espig (jotaespig@gmail.com)
     **/
    void unbind();
    /**
     * @brief destroys
     * @author João Vitor Espig (jotaespig@gmail.com)
     **/
    void destroy() override;

private:
    struct Deleter {
        void operator()(VAO *vao);
    };

    /** OpenGL VAO id **/
    GLuint _id;

    /**
     * @brief Constructor
     * @author João Vitor Espig (jotaespig@gmail.com)
     **/
    VAO();
};

template <typename... Args>
std::shared_ptr<VAO> VAO::create(Args &&...args) {
    return std::shared_ptr<VAO>{
        new VAO{std::forward<Args>(args)...}, VAO::Deleter{}
    };
}

} // namespace gl

} // namespace axolote
