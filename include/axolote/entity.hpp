/**
 * \file entity.hpp
 * \brief entity class
 * \author João Vitor Espig (JotaEspig)
 * \date October 04, 2023
 * \version November 08, 2023
 **/
#pragma once

#include <vector>

#include <glm/glm.hpp>

#include <axolote/drawable.hpp>
#include <axolote/gmesh.hpp>
#include <axolote/model.hpp>
#include <axolote/object3d.hpp>
#include <axolote/shader.hpp>

namespace axolote
{

/**
 * \brief defines a Object (or multiple objects) that can move
 * \author João Vitor Espig (JotaEspig)
 * \date October 04, 2023
 * \version November 08, 2023
 *
 * You should inherit from this class to be able to create an Entity.
 * That's because each Entity has its own update pattern. See update() method.
 **/
class Entity : public Drawable
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
     * \brief Copy constructor
     * \author João Vitor Espig (JotaEspig)
     * \date November 07, 2023
     * \version November 07, 2023
     * \param ent - Entity object
     **/
    Entity(const Entity &ent);
    /**
     * \brief Move constructor
     * \author João Vitor Espig (JotaEspig)
     * \date November 07, 2023
     * \version November 07, 2023
     * \param ent - Entity object
     **/
    Entity(Entity &&ent);

    /**
     * \brief adds an object to entity
     * \author João Vitor Espig (JotaEspig)
     * \date November 05, 2023
     * \version November 05, 2023
     * \param o - Object3D object
     **/
    void add_object(const Object3D &o);
    /**
     * \brief adds an object to entity
     * \author João Vitor Espig (JotaEspig)
     * \date October 08, 2023
     * \version October 27, 2023
     * \param o - Object3D object
     * \param mat - model transformation matrix
     **/
    void add_object(const Object3D &o, const glm::mat4 &mat);
    /**
     * \brief set a model matrix at index
     * \author João Vitor Espig (JotaEspig)
     * \date October 04, 2023
     * \version November 08, 2023
     * \param idx - the index of the matrix you want to update
     * \param mat - the updated transformation matrix
     **/
    void set_matrix(size_t idx, const glm::mat4 &mat);
    /**
     * \brief binds a shader into object3D at idx
     * \author João Vitor Espig (JotaEspig)
     * \date October 27, 2023
     * \version October 27, 2023
     **/
    void bind_shader_at(size_t idx, const Shader &shader);
    /**
     * \brief virtual function that describes how entity updates its objects
     * \author João Vitor Espig (JotaEspig)
     * \date October 27, 2023
     * \version October 27, 2023
     **/
    virtual void update(double time);
    /**
     * \brief draws using a shader
     * \author João Vitor Espig (JotaEspig)
     * \date October 04, 2023
     * \version October 27, 2023
     **/
    void draw() override;
    /**
     * \brief function to override virtual function
     * \author João Vitor Espig (JotaEspig)
     * \date October 25, 2023
     * \version October 27, 2023
     * \param mat - matrix transformation model
     *
     * It just calls draw()
     **/
    void draw(const glm::mat4 &mat) override;
    /**
     * \brief operator = overload (copy)
     * \author João Vitor Espig (JotaEspig)
     * \date November 07, 2023
     * \version November 07, 2023
     * \param ent - Entity object
     **/
    void operator=(const Entity &ent);
    /**
     * \brief operator = overload (move)
     * \author João Vitor Espig (JotaEspig)
     * \date November 07, 2023
     * \version November 07, 2023
     * \param ent - Entity object
     **/
    void operator=(Entity &&ent);

    friend class Scene;

protected:
    /** vector of objects (Object3D) **/
    std::vector<Object3D> objects;
};

} // namespace axolote
