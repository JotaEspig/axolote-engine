/**
* \file mesh.hpp
* \brief Mesh class
* \author João Vitor Espig (JotaEspig)
* \date October 04, 2023
* \version October 04, 2023
**/
#pragma once

#include <vector>

#include <GL/gl.h>
#include <glm/glm.hpp>

#include <axolote/shader.hpp>
#include <axolote/vao.hpp>
#include <axolote/vbo.hpp>
#include <axolote/ebo.hpp>
#include <axolote/texture.hpp>

namespace axolote
{

/**
* \brief defines a polygon mesh
* \author João Vitor Espig (JotaEspig)
* \date October 04, 2023
* \version October 04, 2023
**/
class Mesh
{
public:
    /**
    * \brief Constructor
    * \author João Vitor Espig (JotaEspig)
    * \date October 04, 2023
    * \version October 04, 2023
    **/
    Mesh() = default;
    /**
    * \brief Constructor
    * \author João Vitor Espig (JotaEspig)
    * \date October 04, 2023
    * \version October 04, 2023
    * \param _vertices - polygon mesh vertices
    * \param _indices - polygon mesh indices
    * \param _textures - textures to be rendered with polygon mesh
    **/
    Mesh(std::vector<Vertex> _vertices, std::vector<GLuint> _indices,
         std::vector<Texture> _textures);

    /**
    * \brief Constructor
    * \author João Vitor Espig (JotaEspig)
    * \date October 04, 2023
    * \version October 04, 2023
    * \param shader - Shader object
    * \param matrix - model transformation matrix
    **/
    void draw(Shader &shader, glm::mat4 matrix = glm::mat4(1.0f));
    /**
    * \brief Destroys OpenGL objects created
    * \author João Vitor Espig (JotaEspig)
    * \date October 04, 2023
    * \version October 04, 2023
    **/
    void destroy();

private:
    /** polygon mesh vertices **/
    std::vector<Vertex> vertices;
    /** polygon mesh indices **/
    std::vector<GLuint> indices;
    /** textures to be rendered **/
    std::vector<Texture> textures;
    /** VAO **/
    VAO vao;
    /** VBO **/
    VBO vbo;
    /** EBO **/
    EBO ebo;
};

} // namespace axolote
