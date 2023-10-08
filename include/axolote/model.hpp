/**
* \file model.hpp
* \brief Mesh class
* \author João Vitor Espig (JotaEspig)
* \date October 04, 2023
* \version October 08, 2023
**/
#pragma once

#include <string>
#include <vector>

#include <glm/glm.hpp>

#include <axolote/shader.hpp>
#include <axolote/gmesh.hpp>
#include <axolote/texture.hpp>

namespace axolote
{

/**
* \brief defines a 3D model
* \author João Vitor Espig (JotaEspig)
* \date October 04, 2023
* \version October 08, 2023
**/
class Model
{
public:
    /**
    * \brief Constructor
    * \author João Vitor Espig (JotaEspig)
    * \date October 04, 2023
    * \version October 04, 2023
    **/
    Model() = default;
    /**
    * \brief Constructor
    * \author João Vitor Espig (JotaEspig)
    * \date October 04, 2023
    * \version October 08, 2023
    * \param path - path to model file (.obj)
    * \param _color - default Model color
    **/
    Model(std::string path, glm::vec3 _color = glm::vec3(0.0f, 0.0f, 0.0f));

    /**
    * \brief draws
    * \author João Vitor Espig (JotaEspig)
    * \date October 04, 2023
    * \version October 04, 2023
    * \param shader - Shader object
    * \param matrix - model transformation matrix
    **/
    void draw(Shader &shader, glm::mat4 matrix = glm::mat4(1.0f));

protected:
    /** default color **/
    glm::vec3 color;

    /**
    * \brief loads a model from file
    * \author João Vitor Espig (JotaEspig)
    * \date October 04, 2023
    * \version October 04, 2023
    * \param path - path to file
    **/
    void load_model(std::string path);

private:
    /** Model meshes **/
    std::vector<GMesh> meshes;
    /** loaded textures **/
    std::vector<Texture> loaded_textures;
    /** loaded textures names **/
    std::vector<std::string> loaded_textures_names;
    /** model file directory **/
    std::string directory;
};

} // namespace axolote
