/**
 * @file model.hpp
 * @brief Model class
 * @author João Vitor Espig (jotaespig@gmail.com)
 **/
#pragma once

#include <string>
#include <vector>

#include <glm/glm.hpp>

#include "axolote/mesh.hpp"

namespace axolote {

/**
 * @brief defines a drawable 3D model
 * @author João Vitor Espig (jotaespig@gmail.com)
 **/
class Model {
public:
    /** Model meshes **/
    std::vector<Mesh> meshes;

    /**
     * @brief Constructor
     * @author João Vitor Espig (jotaespig@gmail.com)
     **/
    Model();
    /**
     * @brief Constructor
     * @author João Vitor Espig (jotaespig@gmail.com)
     * @param path path to model file (.obj)
     * @param color default Model color
     **/
    Model(
        std::string path,
        const glm::vec4 &color = glm::vec4(0.0f, 0.0f, 0.0f, 1.0f)
    );

    /**
     * @brief loads a model from file
     * @author João Vitor Espig (jotaespig@gmail.com)
     * @param path path to file
     * @param color default color for model
     **/
    void load_model(std::string path, const glm::vec4 &color);
};

} // namespace axolote
