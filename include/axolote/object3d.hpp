/**
 * @file object3d.hpp
 * @brief Object3D class
 * @author João Vitor Espig (jotaespig@gmail.com)
 **/
#pragma once

#include <memory>
#include <string>
#include <vector>

#include <glm/glm.hpp>

#include "axolote/glad/glad.h"

#include "axolote/drawable.hpp"
#include "axolote/gl/shader.hpp"
#include "axolote/gmodel.hpp"

namespace axolote {

/**
 * @brief defines a 3D Object
 * @author João Vitor Espig (jotaespig@gmail.com)
 *
 * @remarks This class is probably the class you want to use to create any 3D
 * object
 **/
class Object3D : public Drawable {
public:
    /** pointer to gmodel **/
    std::shared_ptr<GModel> gmodel = std::make_shared<GModel>();
    /** is the object transparent **/
    bool is_transparent = false;
    /** is the object affected by lights **/
    bool is_affected_by_lights = true;
    std::string name;

    /**
     * @brief Constructor
     * @author João Vitor Espig (jotaespig@gmail.com)
     **/
    Object3D();
    /**
     * @brief Constructor
     * @author João Vitor Espig (jotaespig@gmail.com)
     * @param mat model transformation matrix
     **/
    Object3D(const glm::mat4 &mat);
    /**
     * @brief Constructor
     * @author João Vitor Espig (jotaespig@gmail.com)
     * @param vertices polygon mesh vertices
     * @param indices polygon mesh indices
     * @param textures textures to be rendered with polygon mesh
     * @param mat model transformation matrix
     **/
    Object3D(
        const std::vector<Vertex> &vertices, const std::vector<GLuint> &indices,
        const std::vector<std::shared_ptr<gl::Texture>> &textures,
        const glm::mat4 &mat
    );
    /**
     * @brief initializes an Object3D from model file
     * @author João Vitor Espig (jotaespig@gmail.com)
     * @param path path to file
     * @param color default color for the model if there's no texture
     * @param mat model transformation matrix
     *
     * It calls load_model method
     **/
    Object3D(std::string path, const glm::vec4 &color, const glm::mat4 &mat);

    /**
     * @brief loads a model from file
     * @author João Vitor Espig (jotaespig@gmail.com)
     * @param path path to file
     * @param color default color for the model if there's no texture
     *
     * It uses constructor from Model
     **/
    void load_model(
        std::string path,
        const glm::vec4 &color = glm::vec4(0.0f, 0.0f, 0.0f, 1.0f)
    );
    /**
     * @brief sets model matrix
     * @author João Vitor Espig (jotaespig@gmail.com)
     **/
    void set_matrix(const glm::mat4 &mat);
    /**
     * @brief gets model matrix
     * @author João Vitor Espig (jotaespig@gmail.com)
     **/
    glm::mat4 get_matrix() const;
    /**
     * @brief Get the normal matrix object
     *
     * @return glm::mat4
     **/
    glm::mat4 get_normal_matrix() const;
    /**
     * @brief binds a shader into the meshes
     * @author João Vitor Espig (jotaespig@gmail.com)
     **/
    void bind_shader(std::shared_ptr<gl::Shader> shader_program) override;
    /**
     * @brief binds a shader into the meshes
     * @author João Vitor Espig (jotaespig@gmail.com)
     **/
    std::vector<std::shared_ptr<gl::Shader>> get_shaders() const override;
    /**
     * @param dt delta time
     **/
    void update(double dt) override;
    /**
     * @brief draws
     * @author João Vitor Espig (jotaespig@gmail.com)
     **/
    void draw() override;
    /**
     * @brief draws
     * @author João Vitor Espig (jotaespig@gmail.com)
     * @param mat matrix transformation model
     *
     * It just calls draw()
     **/
    void draw(const glm::mat4 &mat) override;

protected:
    /** model_matrix **/
    glm::mat4 _model_matrix;
    /** normal_matrix.
     * Used in shaders to calcule correctly normals **/
    glm::mat4 _normal_matrix;
};

} // namespace axolote
