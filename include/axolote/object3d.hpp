/**
 * \file object3d.hpp
 * \brief Object3D class
 * \author João Vitor Espig (JotaEspig)
 **/
#pragma once

#include <memory>

#include <glm/glm.hpp>

#include "axolote/glad/glad.h"

#include "axolote/drawable.hpp"
#include "axolote/gl/shader.hpp"
#include "axolote/gmodel.hpp"

namespace axolote {

/**
 * \brief defines a 3D Object
 * \author João Vitor Espig (JotaEspig)
 **/
class Object3D : public Drawable {
public:
    /** pointer to gmodel **/
    std::shared_ptr<GModel> gmodel{new GModel{}};
    /** is the object transparent **/
    bool is_transparent = false;

    /**
     * \brief Constructor
     * \author João Vitor Espig (JotaEspig)
     **/
    Object3D();
    /**
     * \brief Constructor
     * \author João Vitor Espig (JotaEspig)
     * \param mat - model transformation matrix
     **/
    Object3D(const glm::mat4 &mat);
    /**
     * \brief Constructor
     * \author João Vitor Espig (JotaEspig)
     * \param vertices - polygon mesh vertices
     * \param indices - polygon mesh indices
     * \param textures - textures to be rendered with polygon mesh
     * \param mat - model transformation matrix
     **/
    Object3D(
        const std::vector<Vertex> &vertices, const std::vector<GLuint> &indices,
        const std::vector<gl::Texture> &textures, const glm::mat4 &mat
    );
    /**
     * \brief initializes an Object3D from model file
     * \author João Vitor Espig (JotaEspig)
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
     * \param path - path to file
     * \param color - default color for the model if there's no texture
     *
     * It uses constructor from Model
     **/
    void load_model(
        std::string path, const glm::vec3 &color = glm::vec3(0.0f, 0.0f, 0.0f)
    );
    /**
     * \brief sets model matrix
     * \author João Vitor Espig (JotaEspig)
     **/
    void set_matrix(const glm::mat4 &mat);
    /**
     * \brief gets model matrix
     * \author João Vitor Espig (JotaEspig)
     **/
    glm::mat4 get_matrix() const;
    /**
     * \brief binds a shader into the meshes
     * \author João Vitor Espig (JotaEspig)
     **/
    void bind_shader(const gl::Shader &shader_program) override;
    /**
     * \brief binds a shader into the meshes
     * \author João Vitor Espig (JotaEspig)
     **/
    gl::Shader get_shader() const override;
    /**
     * \param dt - delta time
     **/
    void update(double dt) override;
    /**
     * \brief draws
     * \author João Vitor Espig (JotaEspig)
     **/
    void draw() override;
    /**
     * \brief draws
     * \author João Vitor Espig (JotaEspig)
     * \param mat - matrix transformation model
     *
     * It just calls draw()
     **/
    void draw(const glm::mat4 &mat) override;

protected:
    /** model_matition **/
    glm::mat4 model_mat;
    /** normal_matrix **/
    glm::mat4 normal_mat;
};

} // namespace axolote
