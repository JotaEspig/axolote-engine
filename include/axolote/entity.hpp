/**
* \file entity.hpp
* \brief entity class and entity type enum
* \author João Vitor Espig (JotaEspig)
* \date October 04, 2023
* \version October 04, 2023
**/
#pragma once

#include <vector>

#include <glm/glm.hpp>

#include <axolote/model.hpp>
#include <axolote/mesh.hpp>
#include <axolote/shader.hpp>

namespace axolote
{ 

/**
* \brief defines possibles types for an Entity object
* \author João Vitor Espig (JotaEspig)
* \date October 04, 2023
* \version October 04, 2023
**/
enum class EntityType
{
    MODEL,
    MESH
};

/**
* \brief defines a Object that can move
* \author João Vitor Espig (JotaEspig)
* \date October 04, 2023
* \version October 04, 2023
*
* The entity can be based on meshes or models.
* TODO: implement this class using an abstract class that can represent a
* Object2D or Object3D possibly called Object
**/
class Entity
{
public:
    /**
    * \brief Constructor
    * \author João Vitor Espig (JotaEspig)
    * \date October 04, 2023
    * \version October 04, 2023
    **/
    Entity();

    /**
    * \brief set a model matrix at index
    * \author João Vitor Espig (JotaEspig)
    * \date October 04, 2023
    * \version October 04, 2023
    * \param idx - the index of the matrix you want to update
    * \param mat - the updated transformation matrix
    **/
    void set_matrix(size_t idx, glm::mat4 mat = glm::mat4(1.0f));
    /**
    * \brief draws using a shader
    * \author João Vitor Espig (JotaEspig)
    * \date October 04, 2023
    * \version October 04, 2023
    * \param shader - Shader object
    **/
    void draw(Shader &shader);
    /**
    * \brief adds a model to entity
    * \author João Vitor Espig (JotaEspig)
    * \date October 04, 2023
    * \version October 04, 2023
    * \param m - Model object
    * \param mat - model transformation matrix
    **/
    void add_model(Model m, glm::mat4 mat = glm::mat4(1.0f));
    /**
    * \brief adds a mesh to entity
    * \author João Vitor Espig (JotaEspig)
    * \date October 04, 2023
    * \version October 04, 2023
    * \param m - Mesh object
    * \param mat - model transformation matrix
    **/
    void add_mesh(Mesh m, glm::mat4 mat = glm::mat4(1.0f));

private:
    /** type of the Entity **/
    EntityType type;
    /** vector of models **/
    std::vector<Model> models;
    /** vector of meshes **/
    std::vector<Mesh> meshes;
    /** vector of matrices **/
    std::vector<glm::mat4> matrices;
};

} // namespace axolote
