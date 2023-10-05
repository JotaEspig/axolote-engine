/**
* \file ebo.hpp
* \brief OpenGL EBO operations handler
* \author João Vitor Espig (JotaEspig)
* \date October 04, 2023
* \version October 04, 2023
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
* \version October 04, 2023
**/
class EBO
{
public:
    GLuint id;

    EBO() = default;
    EBO(std::vector<GLuint> indices);

    void bind();
    void unbind();
    void destroy();
};

} // namespace axolote
