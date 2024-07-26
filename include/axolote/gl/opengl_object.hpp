/**
 * \file opengl_object.hpp
 * \brief OpenGL object interface
 * \author João Vitor Espig (JotaEspig)
 *
 * This file contains the interface for OpenGL objects.
 **/
#pragma once

#include "axolote/glad/glad.h"

namespace axolote {

namespace gl {

/**
 * \brief OpenGL object interface
 * \author João Vitor Espig (JotaEspig)
 **/
class OpenGLObject {
public:
    /**
     * \brief default destructor
     * \author João Vitor Espig (JotaEspig)
     **/
    virtual ~OpenGLObject() = default;
    /**
     * \brief id getter
     * \author João Vitor Espig (JotaEspig)
     **/
    virtual GLuint id() const = 0;
    /**
     * \brief destroys the object
     * \author João Vitor Espig (JotaEspig)
     **/
    virtual void destroy() = 0;
};

} // namespace gl

} // namespace axolote
