/**
 * @file ubo.hpp
 * @brief OpenGL UBO operations handler
 * @author João Vitor Espig (jotaespig@gmail.com)
 **/
#pragma once

#include <memory>
#include <utility>

#include "axolote/glad/glad.h"

#include "axolote/gl/opengl_object.hpp"

namespace axolote {

namespace gl {

/**
 * @brief OpenGL UBO handler
 * @author João Vitor Espig (jotaespig@gmail.com)
 **/
class UBO : public OpenGLObject {
public:
    /**
     * @brief Creates a UBO object
     * @author João Vitor Espig (jotaespig@gmail.com)
     * @return shared pointer to UBO object
     **/
    template <typename... Args>
    static std::shared_ptr<UBO> create(Args &&...args);

    /**
     * @brief id getter
     * @author João Vitor Espig (jotaespig@gmail.com)
     * @return id
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
     * @param size size of the data
     * @param data pointer to the data
     * @param usage usage of the data
     **/
    void buffer_data(
        std::size_t size, const void *data, GLenum usage = GL_DYNAMIC_DRAW
    );
    /**
     * @brief buffer sub data
     * @author João Vitor Espig (jotaespig@gmail.com)
     * @param offset start index of updating
     * @param size size of the data
     * @param data pointer to the data
     **/
    void
    buffer_sub_data(std::size_t start_pos, std::size_t size, const void *data);
    /**
     * @brief destroys
     * @author João Vitor Espig (jotaespig@gmail.com)
     **/
    void destroy() override;
    /**
     * @brief binding_point getter
     * @author João Vitor Espig (jotaespig@gmail.com)
     **/
    GLuint binding_point() const;
    /**
     * @brief binding_point setter
     * @author João Vitor Espig (jotaespig@gmail.com)
     **/
    void set_binding_point(GLuint bp);

private:
    struct Deleter {
        void operator()(UBO *ubo);
    };

    /** OpenGL UBO id **/
    GLuint _id;
    GLuint _binding_point;

    /**
     * @brief Constructor
     * @author João Vitor Espig (jotaespig@gmail.com)
     **/
    UBO();
};

template <typename... Args>
std::shared_ptr<UBO> UBO::create(Args &&...args) {
    return std::shared_ptr<UBO>{
        new UBO{std::forward<Args>(args)...}, Deleter{}
    };
}

} // namespace gl

} // namespace axolote
