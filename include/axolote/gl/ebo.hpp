/**
 * @file ebo.hpp
 * @brief OpenGL EBO operations handler
 * @author João Vitor Espig (jotaespig@gmail.com)
 *
 * this file contains a class called EBO that handles OpenGL EBO operations:
 * Bind, Unbind and destroy
 **/
#pragma once

#include <memory>
#include <utility>
#include <vector>

#include "axolote/glad/glad.h"

#include "axolote/gl/opengl_object.hpp"

namespace axolote {

namespace gl {

/**
 * @brief OpenGL EBO handler
 * @author João Vitor Espig (jotaespig@gmail.com)
 **/
class EBO : public OpenGLObject {
public:
    /**
     * @brief Creates a EBO object
     * @author João Vitor Espig (jotaespig@gmail.com)
     * @return shared pointer to EBO object
     **/
    template <typename... Args>
    static std::shared_ptr<EBO> create(Args &&...args);

    /**
     * @brief id getter
     * @author João Vitor Espig (jotaespig@gmail.com)
     * @return id
     **/
    GLuint id() const override;
    /**
     * @brief size getter
     * @author João Vitor Espig (jotaespig@gmail.com)
     * @return size
     **/
    std::size_t size() const;
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
        void operator()(EBO *ebo);
    };

    /** OpenGL EBO id **/
    GLuint _id;
    /** amount of indices **/
    std::size_t _size;

    /**
     * @brief Constructor
     * @author João Vitor Espig (jotaespig@gmail.com)
     **/
    EBO();
    /**
     * @brief Constructor
     * @author João Vitor Espig (jotaespig@gmail.com)
     * @param indices array of indices
     **/
    EBO(const std::vector<GLuint> &indices);
};

template <typename... Args>
std::shared_ptr<EBO> EBO::create(Args &&...args) {
    return std::shared_ptr<EBO>{
        new EBO{std::forward<Args>(args)...}, Deleter{}
    };
}

} // namespace gl

} // namespace axolote
