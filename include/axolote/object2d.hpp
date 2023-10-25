/**
* \file object2d.hpp
* \brief Object2D class
* \author João Vitor Espig (JotaEspig)
* \date October 04, 2023
* \version October 05, 2023
**/
#pragma once

#include <GL/gl.h>
#include <glm/glm.hpp>

#include <axolote/shader.hpp>
#include <axolote/gmesh.hpp>
#include <axolote/object.hpp>
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
class Object2D : public Object, public GMesh
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
    * \param mat - model transformation matrix
    * \param vertices - Mesh vertices
    * \param indices - Mesh indices
    * \param textures - Mesh textures
    **/
    Object2D(const glm::mat4 &mat, const std::vector<Vertex> &vertices,
             const std::vector<GLuint> &indices, const std::vector<Texture> &textures);

    /**
    * \brief draws
    * \author João Vitor Espig (JotaEspig)
    * \date October 04, 2023
    * \version October 05, 2023
    * \param shader - Shader object
    **/
    void draw(Shader &shader) override;
    /**
    * \brief draws
    * \author João Vitor Espig (JotaEspig)
    * \date October 25, 2023
    * \version October 25, 2023
    * \param shader - Shader object
    * \param mat - matrix transformation model
    *
    * It just calls draw(shader)
    **/
    void draw(Shader &shader, const glm::mat4 &mat) override;
};

} // namespace axolote
