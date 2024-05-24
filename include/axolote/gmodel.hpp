/**
 * \file model.hpp
 * \brief Model class
 * \author João Vitor Espig (JotaEspig)
 * \date October 04, 2023
 * \version May 23, 2024
 **/
#pragma once

#include <string>
#include <vector>

#include <glm/glm.hpp>

#include <axolote/drawable.hpp>
#include <axolote/gl/shader.hpp>
#include <axolote/gl/texture.hpp>
#include <axolote/gmesh.hpp>

namespace axolote {

/**
 * \brief defines a 3D model
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
     * \date October 27, 2023
     * \version October 27, 2023
     * \param vertices - polygon mesh vertices
     * \param indices - polygon mesh indices
     * \param textures - textures to be rendered with polygon mesh
     **/
    GModel(
        const std::vector<Vertex> &vertices, const std::vector<GLuint> &indices,
        const std::vector<gl::Texture> &textures
    );
    /**
     * \brief Constructor
     * \author João Vitor Espig (JotaEspig)
     * \date October 04, 2023
     * \version October 08, 2023
     * \param path - path to model file (.obj)
     * \param _color - default Model color
     **/
    GModel(
        std::string path, const glm::vec3 &_color = glm::vec3(0.0f, 0.0f, 0.0f)
    );

    /**
     * \brief binds a shader into the meshes
     * \author João Vitor Espig (JotaEspig)
     * \date October 27, 2023
     * \version October 27, 2023
     **/
    void bind_shader(const gl::Shader &shader);
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

    friend class Object3D;
    friend class Scene;
    friend class Entity;

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
    /** loaded textures **/
    std::vector<gl::Texture> loaded_textures;
    /** loaded textures names **/
    std::vector<std::string> loaded_textures_names;
    /** model file directory **/
    std::string directory;
};

} // namespace axolote
