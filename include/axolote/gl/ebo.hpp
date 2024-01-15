/**
 * \file ebo.hpp
 * \brief OpenGL EBO operations handler
 * \author João Vitor Espig (JotaEspig)
 * \date October 04, 2023
 * \version November 06, 2023
 *
 * this file contains a class called EBO that handles OpenGL EBO operations:
 * Bind, Unbind and destroy
 **/
#pragma once

#include <vector>

#include <GL/gl.h>

namespace axolote
{

/**
 * \brief OpenGL EBO handler
 * \author João Vitor Espig (JotaEspig)
 * \date October 04, 2023
 * \version November 06, 2023
 **/
class EBO
{
public:
    /** OpenGL EBO id **/
    GLuint id;

    /**
     * \brief Constructor
     * \author João Vitor Espig (JotaEspig)
     * \date October 04, 2023
     * \version October 04, 2023
     **/
    EBO();
    /**
     * \brief Copy constructor
     * \author João Vitor Espig (JotaEspig)
     * \date November 06, 2023
     * \version November 06, 2023
     * \param ebo - EBO object
     **/
    EBO(const EBO &ebo);
    /**
     * \brief Move constructor
     * \author João Vitor Espig (JotaEspig)
     * \date November 06, 2023
     * \version November 06, 2023
     * \param ebo - EBO object
     **/
    EBO(EBO &&ebo);
    /**
     * \brief Constructor
     * \author João Vitor Espig (JotaEspig)
     * \date October 04, 2023
     * \version October 04, 2023
     * \param indices - array of indices
     **/
    EBO(const std::vector<GLuint> &indices);

    /**
     * \brief binds
     * \author João Vitor Espig (JotaEspig)
     * \date October 04, 2023
     * \version October 04, 2023
     **/
    void bind();
    /**
     * \brief unbinds
     * \author João Vitor Espig (JotaEspig)
     * \date October 04, 2023
     * \version October 04, 2023
     **/
    void unbind();
    /**
     * \brief destroys
     * \author João Vitor Espig (JotaEspig)
     * \date October 04, 2023
     * \version October 04, 2023
     **/
    void destroy();
    /**
     * \brief operator = overload (copy)
     * \author João Vitor Espig (JotaEspig)
     * \date November 06, 2023
     * \version November 06, 2023
     * \param ebo - EBO object
     **/
    void operator=(const EBO &ebo);
    /**
     * \brief operator = overload (move)
     * \author João Vitor Espig (JotaEspig)
     * \date November 06, 2023
     * \version November 06, 2023
     * \param ebo - EBO object
     **/
    void operator=(EBO &&ebo);
};

} // namespace axolote
