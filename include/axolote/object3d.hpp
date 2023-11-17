/**
 * \file object3d.hpp
 * \brief Object3D class
 * \author João Vitor Espig (JotaEspig)
 * \date October 08, 2023
 * \version November 07, 2023
 **/
#pragma once

#include <GL/gl.h>
#include <glm/glm.hpp>

#include <axolote/model.hpp>
#include <axolote/shader.hpp>

namespace axolote
{

/**
 * \brief defines a 3D Object
 * \author João Vitor Espig (JotaEspig)
 * \date October 08, 2023
 * \version November 07, 2023
 **/
class Object3D : public Model
{
public:
    /**
     * \brief Constructor
     * \author João Vitor Espig (JotaEspig)
     * \date October 08, 2023
     * \version October 08, 2023
     **/
    Object3D();
    /**
     * \brief Copy constructor
     * \author João Vitor Espig (JotaEspig)
     * \date November 07, 2023
     * \version November 07, 2023
     * \param obj - Object3D object
     **/
    Object3D(const Object3D &obj);
    /**
     * \brief Move constructor
     * \author João Vitor Espig (JotaEspig)
     * \date November 07, 2023
     * \version November 07, 2023
     * \param obj - Object3D object
     **/
    Object3D(Object3D &&obj);
    /**
     * \brief Constructor
     * \author João Vitor Espig (JotaEspig)
     * \date October 08, 2023
     * \version October 08, 2023
     * \param mat - model transformation matrix
     **/
    Object3D(const glm::mat4 &mat);
    /**
     * \brief Constructor
     * \author João Vitor Espig (JotaEspig)
     * \date October 27, 2023
     * \version October 27, 2023
     * \param vertices - polygon mesh vertices
     * \param indices - polygon mesh indices
     * \param textures - textures to be rendered with polygon mesh
     * \param mat - model transformation matrix
     **/
    Object3D(
        const std::vector<Vertex> &vertices, const std::vector<GLuint> &indices,
        const std::vector<Texture> &textures, const glm::mat4 &mat
    );
    /**
     * \brief initializes an Object3D from model file
     * \author João Vitor Espig (JotaEspig)
     * \date October 27, 2023
     * \version October 27 2023
     * \param path - path to file
     * \param color - default color for the model if there's no texture
     * \param mat - model transformation matrix
     *
     * It calls load_model method
     **/
    Object3D(std::string path, const glm::vec3 &color, const glm::mat4 &mat);

    /**
     * \brief loads a model from file
     * \author João Vitor Espig (JotaEspig)
     * \date October 08, 2023
     * \version October 08, 2023
     * \param path - path to file
     * \param color - default color for the model if there's no texture
     *
     * It uses constructor from Model
     **/
    void load_model(
        std::string path, const glm::vec3 &color = glm::vec3(0.0f, 0.0f, 0.0f)
    );
    /**
     * \brief gets model matrix
     * \author João Vitor Espig
     * \date November 08, 2023
     * \version November 08, 2023
     **/
    glm::mat4 get_matrix() const;
    /**
     * \brief draws
     * \author João Vitor Espig (JotaEspig)
     * \date October 08, 2023
     * \version October 27, 2023
     **/
    void draw() override;
    /**
     * \brief draws
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
     * \param obj - Object3D object
     **/
    void operator=(const Object3D &obj);
    /**
     * \brief operator = overload (move)
     * \author João Vitor Espig (JotaEspig)
     * \date November 07, 2023
     * \version November 07, 2023
     * \param obj - Object3D object
     **/
    void operator=(Object3D &&obj);

    friend class Entity;
    friend class Scene;

protected:
    /** model_matition **/
    glm::mat4 model_mat;
};

} // namespace axolote
