/**
 * \file model.hpp
 * \brief Model class
 * \author João Vitor Espig (JotaEspig)
 * \date May 23, 2024
 * \version May 23, 2024
 **/
#pragma once

#include <string>
#include <vector>

#include <glm/glm.hpp>

#include <axolote/gl/texture.hpp>
#include <axolote/mesh.hpp>

namespace axolote {

/**
 * \brief defines a drawable 3D model
 * \author João Vitor Espig (JotaEspig)
 * \date May 23, 2024
 * \version May 23, 2024
 **/
class Model {
public:
    /** Model meshes **/
    std::vector<Mesh> meshes;

    /**
     * \brief Constructor
     * \author João Vitor Espig (JotaEspig)
     * \date May 23, 2024
     * \version May 23, 2024
     **/
    Model();
    /**
     * \brief Constructor
     * \author João Vitor Espig (JotaEspig)
     * \date May 23, 2024
     * \version May 23, 2024
     * \param path - path to model file (.obj)
     * \param color - default Model color
     **/
    Model(
        std::string path, const glm::vec3 &color = glm::vec3(0.0f, 0.0f, 0.0f)
    );

    /**
     * \brief loads a model from file
     * \author João Vitor Espig (JotaEspig)
     * \date October 04, 2023
     * \version October 04, 2023
     * \param path - path to file
     * \param color - default color for model
     **/
    void load_model(std::string path, const glm::vec3 &color);
};

} // namespace axolote
