/**
* \file entity.hpp
* \brief entity class and entity type enum
* \author João Vitor Espig (JotaEspig)
* \date October 04, 2023
* \version October 08, 2023
**/
#pragma once

#include <vector>

#include <glm/glm.hpp>

#include <axolote/object.hpp>
#include <axolote/model.hpp>
#include <axolote/gmesh.hpp>
#include <axolote/shader.hpp>

namespace axolote
{ 

/**
* \brief defines a Object (or multiple objects) that can move
* \author João Vitor Espig (JotaEspig)
* \date October 04, 2023
* \version October 08, 2023
*
* The entity can be based on meshes or models.
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
    * \brief adds an object to entity
    * \author João Vitor Espig (JotaEspig)
    * \date October 08, 2023
    * \version October 08, 2023
    * \param o - Object object pointer
    * \param mat - model transformation matrix
    **/
    void add_object(Object *o, glm::mat4 mat = glm::mat4(1.0f));
    /**
    * \brief set a model matrix at index
    * \author João Vitor Espig (JotaEspig)
    * \date October 04, 2023
    * \version October 08, 2023
    * \param idx - the index of the matrix you want to update
    * \param mat - the updated transformation matrix
    **/
    void set_matrix(size_t idx, glm::mat4 mat);
    /**
    * \brief draws using a shader
    * \author João Vitor Espig (JotaEspig)
    * \date October 04, 2023
    * \version October 08, 2023
    * \param shader - Shader object
    **/
    void draw(Shader &shader);

private:
    /** vector of objects **/
    std::vector<Object*> objects;
};

} // namespace axolote
