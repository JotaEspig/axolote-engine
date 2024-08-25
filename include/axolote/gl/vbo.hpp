/**
 * @file vbo.hpp
 * @brief OpenGL VBO operations handler
 * @author João Vitor Espig (jotaespig@gmail.com)
 *
 * this file contains a class called VBO that handles OpenGL VBO operations:
 * Bind, Unbind and destroy
 **/
#pragma once

#include <memory>
#include <utility>
#include <vector>

#include <glm/glm.hpp>

#include "axolote/glad/glad.h"

#include "axolote/gl/opengl_object.hpp"

namespace axolote {

namespace gl {

/**
 * @brief OpenGL VBO handler
 * @author João Vitor Espig (jotaespig@gmail.com)
 **/
class VBO : public OpenGLObject {
public:
    /**
     * @brief Creates a VBO object
     * @author João Vitor Espig (jotaespig@gmail.com)
     * @return shared pointer to VBO object
     **/
    template <typename... Args>
    static std::shared_ptr<VBO> create(Args &&...args);
    /**
     * @brief id getter
     * @author João Vitor Espig (jotaespig@gmail.com)
     **/
    GLuint id() const override;
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
     * @brief buffer data
     * @author João Vitor Espig (jotaespig@gmail.com)
     * \data June 07, 2024
     * \version June 07, 2024
     * @param size size of the data
     * @param data pointer to the data
     * @param usage usage of the data
     **/
    void buffer_data(
        std::size_t size, const void *data, GLenum usage = GL_STATIC_DRAW
    );
    /**
     * @brief destroys
     * @author João Vitor Espig (jotaespig@gmail.com)
     **/
    void destroy() override;

private:
    struct Deleter {
        void operator()(VBO *vbo);
    };

    /** OpenGL VBO id **/
    GLuint _id;

    /**
     * @brief Constructor
     * @author João Vitor Espig (jotaespig@gmail.com)
     **/
    VBO();
    /**
     * @brief Constructor
     * @author João Vitor Espig (jotaespig@gmail.com)
     * @param vertices array of vertex
     **/
    template <class T>
    VBO(const std::vector<T> &vertices);
};

template <typename... Args>
std::shared_ptr<VBO> VBO::create(Args &&...args) {
    return std::shared_ptr<VBO>{
        new VBO{std::forward<Args>(args)...}, VBO::Deleter{}
    };
}

template <class T>
VBO::VBO(const std::vector<T> &vertices) :
  VBO{} {
    bind();
    buffer_data(vertices.size() * sizeof(T), vertices.data(), GL_STATIC_DRAW);
}

} // namespace gl

} // namespace axolote
