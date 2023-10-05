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
    Entity();

    void set_matrix(size_t idx, glm::mat4 mat = glm::mat4(1.0f));
    void draw(Shader &shader);
    void add_model(Model m, glm::mat4 mat = glm::mat4(1.0f));
    void add_mesh(Mesh m, glm::mat4 mat = glm::mat4(1.0f));

private:
    EntityType type;
    std::vector<Model> models;
    std::vector<Mesh> meshes;
    std::vector<glm::mat4> matrices;
};

} // namespace axolote
