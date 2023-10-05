/**
* \file object2d.hpp
* \brief Object2D class
* \author João Vitor Espig (JotaEspig)
* \date October 04, 2023
* \version October 04, 2023
**/
#pragma once

#include <axolote/shader.hpp>
#include <glm/glm.hpp>

#include <axolote/mesh.hpp>

namespace axolote
{

/**
* \brief defines a 2D Object
* \author João Vitor Espig (JotaEspig)
* \date October 04, 2023
* \version October 04, 2023
**/
class Object2D
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
    * \version October 04, 2023
    * \param _mesh - Mesh object
    * \param mat - model transformation matrix
    **/
    Object2D(Mesh _mesh, glm::mat4 mat = glm::mat4(1.0f));

    /**
    * \brief draws
    * \author João Vitor Espig (JotaEspig)
    * \date October 04, 2023
    * \version October 04, 2023
    * \param shader - Shader object
    **/
    void draw(Shader &shader);

private:
    /** Mesh Object **/
    Mesh mesh;
    /** model transformation matrix **/
    glm::mat4 pos = glm::mat4(1.0f);
};

} // namespace axolote
