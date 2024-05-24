/**
 * \file gmodel.hpp
 * \brief GModel class
 * \author João Vitor Espig (JotaEspig)
 * \date October 04, 2023
 * \version May 23, 2024
 **/
#pragma once

#include <string>
#include <vector>

#include <glm/glm.hpp>

#include "axolote/drawable.hpp"
#include "axolote/gl/shader.hpp"
#include "axolote/gmesh.hpp"

namespace axolote {

/**
 * \brief defines a drawable 3D model
 * \author João Vitor Espig (JotaEspig)
 * \date October 04, 2023
 * \version May 23, 2024
 **/
class GModel : public Drawable {
public:
    /** Model meshes **/
    std::vector<GMesh> meshes;

    /**
     * \brief Constructor
     * \author João Vitor Espig (JotaEspig)
     * \date October 04, 2023
     * \version October 04, 2023
     **/
    GModel();
    /**
     * \brief Constructor
     * \author João Vitor Espig (JotaEspig)
     * \date October 04, 2023
     * \version October 08, 2023
     * \param path - path to model file (.obj)
     * \param color - default Model color
     **/
    GModel(
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
    /**
     * \brief binds a shader into the meshes
     * \author João Vitor Espig (JotaEspig)
     * \date October 27, 2023
     * \version October 27, 2023
     **/
    void bind_shader(const gl::Shader &shader_program) override;
    /**
     * \brief binds a shader into the meshes
     * \author João Vitor Espig (JotaEspig)
     * \date May 24, 2024
     * \version May 24, 2024
     **/
    gl::Shader get_shader() const override;
    /**
     * \brief Override update from Drawable, does nothing in reality
     * \author João Vitor Espig (JotaEspig)
     * \date May 24, 2024
     * \version May 24, 2024
     * \param dt - delta time
     **/
    void update(double dt) override;
    /**
     * \brief draws
     * \author João Vitor Espig (JotaEspig)
     * \date October 25, 2023
     * \version October 27, 2023
     *
     * It calls draw(glm::mat4(1.0f))
     **/
    void draw() override;
    /**
     * \brief draws
     * \author João Vitor Espig (JotaEspig)
     * \date October 04, 2023
     * \version October 07, 2023
     * \param mat - model transformation matrix
     **/
    void draw(const glm::mat4 &mat) override;
};

} // namespace axolote
