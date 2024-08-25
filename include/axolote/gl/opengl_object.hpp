/**
 * @file opengl_object.hpp
 * @brief OpenGL object interface
 * @author João Vitor Espig (jotaespig@gmail.com)
 *
 * This file contains the interface for OpenGL objects.
 **/
#pragma once

#include "axolote/glad/glad.h"

namespace axolote {

namespace gl {

/**
 * @brief OpenGL object interface
 * @author João Vitor Espig (jotaespig@gmail.com)
 **/
class OpenGLObject {
public:
    /**
     * @brief default destructor
     * @author João Vitor Espig (jotaespig@gmail.com)
     **/
    virtual ~OpenGLObject() = default;
    /**
     * @brief id getter
     * @author João Vitor Espig (jotaespig@gmail.com)
     **/
    virtual GLuint id() const = 0;
    /**
     * @brief destroys the object
     * @author João Vitor Espig (jotaespig@gmail.com)
     **/
    virtual void destroy() = 0;
};

} // namespace gl

} // namespace axolote
