/**
 * \file gmodel.hpp
 * \brief GModel class
 * \author João Vitor Espig (JotaEspig)
 **/
#pragma once

#include <memory>
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
 *
 * You should use GModel if you want a default implementation for drawing
 **/
class GModel : public Drawable {
public:
    /** Model meshes **/
    std::vector<GMesh> meshes;

    /**
     * \brief Constructor
     * \author João Vitor Espig (JotaEspig)
     **/
    GModel();
    /**
     * \brief Constructor
     * \author João Vitor Espig (JotaEspig)
     * \param path - path to model file (.obj)
     * \param color - default Model color
     **/
    GModel(
        std::string path,
        const glm::vec4 &color = glm::vec4(0.0f, 0.0f, 0.0f, 1.0f)
    );

    /**
     * \brief loads a model from file
     * \author João Vitor Espig (JotaEspig)
     * \param path - path to file
     * \param color - default color for model
     **/
    void load_model(std::string path, const glm::vec4 &color);
    /**
     * \brief binds a shader into the meshes
     * \author João Vitor Espig (JotaEspig)
     **/
    void bind_shader(std::shared_ptr<gl::Shader> shader) override;
    /**
     * \brief binds a shader into the meshes
     * \author João Vitor Espig (JotaEspig)
     **/
    std::shared_ptr<gl::Shader> get_shader() const override;
    /**
     * \param dt - delta time
     **/
    void update(double dt) override;
    /**
     * \brief draws
     * \author João Vitor Espig (JotaEspig)
     *
     * It calls draw(glm::mat4(1.0f))
     **/
    void draw() override;
    /**
     * \brief draws
     * \author João Vitor Espig (JotaEspig)
     * \param mat - model transformation matrix
     **/
    void draw(const glm::mat4 &mat) override;
};
} // namespace axolote
