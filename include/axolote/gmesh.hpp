/**
 * \file gmesh.hpp
 * \brief Graphic Mesh class
 * \author João Vitor Espig (JotaEspig)
 **/
#pragma once

#include <memory>
#include <vector>

#include <glm/glm.hpp>

#include "axolote/drawable.hpp"
#include "axolote/gl/ebo.hpp"
#include "axolote/gl/shader.hpp"
#include "axolote/gl/texture.hpp"
#include "axolote/gl/vao.hpp"
#include "axolote/gl/vbo.hpp"
#include "axolote/mesh.hpp"

namespace axolote {

/**
 * \brief defines a graphic polygon mesh
 * \author João Vitor Espig (JotaEspig)
 *
 * The difference between GMesh and Mesh is that GMesh you can draw.
 * You should use GMesh if you want a default implementation for drawing
 *
 * \remark You should use this class only when you want a low-level control
 **/
class GMesh : public Mesh, public Drawable {
public:
    /**
     * \brief Constructor
     * \author João Vitor Espig (JotaEspig)
     **/
    GMesh();
    /**
     * \brief Constructor
     * \author João Vitor Espig (JotaEspig)
     * \param mesh - mesh object
     **/
    GMesh(const Mesh &mesh);
    /**
     * \brief Constructor
     * \author João Vitor Espig (JotaEspig)
     * \param vertices - polygon mesh vertices
     * \param indices - polygon mesh indices
     * \param textures - textures to be rendered with polygon mesh
     **/
    GMesh(
        const std::vector<Vertex> &vertices, const std::vector<GLuint> &indices,
        const std::vector<std::shared_ptr<gl::Texture>> &textures
    );

    /**
     * \brief VAO getter
     * \author João Vitor Espig (JotaEspig)
     **/
    std::shared_ptr<gl::VAO> vao() const;
    /**
     * \brief VBO getter
     * \author João Vitor Espig (JotaEspig)
     **/
    std::shared_ptr<gl::VBO> vbo() const;
    /**
     * \brief EBO getter
     * \author João Vitor Espig (JotaEspig)
     **/
    std::shared_ptr<gl::EBO> ebo() const;
    /**
     * \brief binds a shader into gmesh
     * \author João Vitor Espig (JotaEspig)
     * \param shader_program - Shader
     **/
    void bind_shader(std::shared_ptr<gl::Shader> shader_program) override;
    /**
     * \brief binds a shader into gmesh
     * \author João Vitor Espig (JotaEspig)
     **/
    std::shared_ptr<gl::Shader> get_shader() const override;
    /**
     * \param dt - delta time
     **/
    void update(double dt) override;
    /**
     * \brief sets shaders uniforms and do the binds
     * \author João Vitor Espig (JotaEspig)
     **/
    void default_draw_binds(const glm::mat4 &mat);
    /**
     * \brief unbinds things used in drawing
     * \author João Vitor Espig (JotaEspig)
     **/
    void default_draw_unbinds();
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

private:
    /** VAO **/
    std::shared_ptr<gl::VAO> _vao;
    /** VBO **/
    std::shared_ptr<gl::VBO> _vbo;
    /** EBO **/
    std::shared_ptr<gl::EBO> _ebo;
    /** Shader **/
    std::shared_ptr<gl::Shader> _shader;
};

} // namespace axolote
