/**
* \file entity.hpp
* \brief entity class
* \author João Vitor Espig (JotaEspig)
* \date October 04, 2023
* \version October 08, 2023
**/
#pragma once

#include <vector>

#include <glm/glm.hpp>

#include <axolote/idrawable.hpp>
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
* An Entity can be multiples Object3D or Object2D, it uses polymorphism to
* handle both at the same time
**/
class Entity : public IDrawable
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
    void add_object(Object *o, const glm::mat4 &mat = glm::mat4(1.0f));
    /**
    * \brief set a model matrix at index
    * \author João Vitor Espig (JotaEspig)
    * \date October 04, 2023
    * \version October 08, 2023
    * \param idx - the index of the matrix you want to update
    * \param mat - the updated transformation matrix
    **/
    void set_matrix(size_t idx, const glm::mat4 &mat);
    /**
    * \brief draws using a shader
    * \author João Vitor Espig (JotaEspig)
    * \date October 04, 2023
    * \version October 08, 2023
    * \param shader - Shader object
    **/
    void draw(Shader &shader) override;
    /**
    * \brief function to override virtual function
    * \author João Vitor Espig (JotaEspig)
    * \date October 25, 2023
    * \version October 25, 2023
    * \param shader - Shader object
    * \param mat - matrix transformation model
    *
    * It just calls draw(Shader)
    **/
    void draw(Shader &shader, const glm::mat4 &mat) override;

private:
    /** vector of objects (Object3D or Object2D) **/
    std::vector<Object*> objects;
};

} // namespace axolote
