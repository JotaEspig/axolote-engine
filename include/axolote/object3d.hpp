/**
* \file object3d.hpp
* \brief Object3D class
* \author João Vitor Espig (JotaEspig)
* \date October 08, 2023
* \version October 08, 2023
**/
#pragma once

#include <GL/gl.h>
#include <glm/glm.hpp>

#include <axolote/shader.hpp>
#include <axolote/model.hpp>
#include <axolote/object.hpp>

namespace axolote
{

/**
* \brief defines a 3D Object
* \author João Vitor Espig (JotaEspig)
* \date October 08, 2023
* \version October 08, 2023
**/
class Object3D : public Object, public Model
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
    * \brief Constructor
    * \author João Vitor Espig (JotaEspig)
    * \date October 08, 2023
    * \version October 08, 2023
    * \param mat - model transformation matrix
    **/
    Object3D(const glm::mat4 &mat);

    /**
    * \brief initializes an Object3D from model file
    * \author João Vitor Espig (JotaEspig)
    * \date October 09, 2023
    * \version October 09, 2023
    * \param mat - model transformation matrix
    * \param path - path to file
    * \param color - default color for the model if there's no texture
    *
    * It calls load_model method
    **/
    static Object3D from_model_file(const glm::mat4 &mat, std::string path,
                                    const glm::vec3 &color = glm::vec3(0.0f, 0.0f, 0.0f));

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
    void load_model(std::string path,
                    const glm::vec3 &color = glm::vec3(0.0f, 0.0f, 0.0f));
    /**
    * \brief draws
    * \author João Vitor Espig (JotaEspig)
    * \date October 08, 2023
    * \version October 08, 2023
    * \param shader - Shader object
    **/
    void draw(Shader &shader) override;
};

} // namespace axolote
