/**
* \file gmesh.hpp
* \brief Graphic Mesh class
* \author João Vitor Espig (JotaEspig)
* \date October 06, 2023
* \version October 06, 2023
**/
#pragma once

#include <vector>

#include <GL/gl.h>
#include <glm/glm.hpp>

#include <axolote/drawable.hpp>
#include <axolote/mesh.hpp>
#include <axolote/shader.hpp>
#include <axolote/vao.hpp>
#include <axolote/vbo.hpp>
#include <axolote/ebo.hpp>
#include <axolote/texture.hpp>

namespace axolote
{

/**
* \brief defines a graphic polygon mesh
* \author João Vitor Espig (JotaEspig)
* \date October 06, 2023
* \version October 06, 2023
*
* The difference between GMesh and Mesh is that GMesh you can draw
**/
class GMesh : public Mesh, public Drawable
{
public:
    /**
    * \brief Constructor
    * \author João Vitor Espig (JotaEspig)
    * \date October 06, 2023
    * \version October 06, 2023
    **/
    GMesh();
    /**
    * \brief Constructor
    * \author João Vitor Espig (JotaEspig)
    * \date October 06, 2023
    * \version October 06, 2023
    * \param vertices - polygon mesh vertices
    * \param indices - polygon mesh indices
    * \param textures - textures to be rendered with polygon mesh
    **/
    GMesh(const std::vector<Vertex> &vertices, const std::vector<GLuint> &indices,
          const std::vector<Texture> &textures);

    /**
    * \brief draws
    * \author João Vitor Espig (JotaEspig)
    * \date October 25, 2023
    * \version October 25, 2023
    * \param shader - Shader object
    *
    * It calls draw(Shader, glm::mat4(1.0f))
    **/
    void draw(Shader &shader) override;
    /**
    * \brief draws
    * \author João Vitor Espig (JotaEspig)
    * \date October 06, 2023
    * \version October 06, 2023
    * \param shader - Shader object
    * \param matrix - model transformation matrix
    **/
    void draw(Shader &shader, const glm::mat4 &mat) override;
    /**
    * \brief Destroys OpenGL objects created
    * \author João Vitor Espig (JotaEspig)
    * \date October 06, 2023
    * \version October 06, 2023
    **/
    void destroy();

private:
    /** VAO **/
    VAO vao;
    /** VBO **/
    VBO vbo;
    /** EBO **/
    EBO ebo;
};

} // namespace axolote
