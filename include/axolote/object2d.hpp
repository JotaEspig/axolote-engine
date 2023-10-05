/**
* \file object2d.hpp
* \brief Object2D class
* \author João Vitor Espig (JotaEspig)
* \date October 04, 2023
* \version October 05, 2023
**/
#pragma once

#include <GL/gl.h>

#include <axolote/shader.hpp>
#include <glm/glm.hpp>

#include <axolote/mesh.hpp>
#include <axolote/texture.hpp>
#include <axolote/structs.hpp>

namespace axolote
{

/**
* \brief defines a 2D Object
* \author João Vitor Espig (JotaEspig)
* \date October 04, 2023
* \version October 05, 2023
**/
class Object2D : public Mesh
{
public:
    /**
    * \brief Constructor
    * \author João Vitor Espig (JotaEspig)
    * \date October 04, 2023
    * \version October 04, 2023
    **/
    Object2D();
    /**
    * \brief Constructor
    * \author João Vitor Espig (JotaEspig)
    * \date October 04, 2023
    * \version October 05, 2023
    * \param vertices - Mesh vertices
    * \param indices - Mesh indices
    * \param textures - Mesh textures
    * \param mat - model transformation matrix
    **/
    Object2D(std::vector<Vertex> vertices, std::vector<GLuint>,
             std::vector<Texture> textures, glm::mat4 mat = glm::mat4(1.0f));

    /**
    * \brief draws
    * \author João Vitor Espig (JotaEspig)
    * \date October 04, 2023
    * \version October 05, 2023
    * \param shader - Shader object
    **/
    void draw(Shader &shader);

private:
    /** model transformation matrix **/
    glm::mat4 pos = glm::mat4(1.0f);
};

} // namespace axolote
