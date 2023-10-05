/**
* \file vbo.hpp
* \brief OpenGL VBO operations handler
* \author João Vitor Espig (JotaEspig)
* \date October 04, 2023
* \version October 04, 2023
*
* this file contains a class called VBO that handles OpenGL VBO operations:
* Bind, Unbind and destroy
**/
#pragma once

#include <vector>

#include <GL/gl.h>
#include <glm/glm.hpp>

#include <axolote/structs.hpp>

namespace axolote
{

/**
* \brief OpenGL VBO handler
* \author João Vitor Espig (JotaEspig)
* \date October 04, 2023
* \version October 04, 2023
**/
class VBO
{
public:
    GLuint id;

    VBO() = default;
    VBO(std::vector<Vertex> vertices);

    void bind();
    void unbind();
    void destroy();
};

} // namespace axolote
