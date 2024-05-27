/**
 * \file gmesh.hpp
 * \brief Graphic Mesh class
 * \author João Vitor Espig (JotaEspig)
 * \date October 06, 2023
 * \version May 23, 2024
 **/
#pragma once

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
 * \date October 06, 2023
 * \version May 23, 2024
 *
 * The difference between GMesh and Mesh is that GMesh you can draw.
 * You should use GMesh if you want a default implementation for drawing
 **/
struct GMesh : public Mesh, public Drawable {
    /** VAO **/
    gl::VAO vao;
    /** VBO **/
    gl::VBO vbo;
    /** EBO **/
    gl::EBO ebo;
    /** Shader **/
    gl::Shader shader;

    /**
     * \brief Constructor
     * \author João Vitor Espig (JotaEspig)
     * \date October 06, 2023
     * \version October 06, 2023
     **/
    GMesh();
    /**
     * \brief Constructor
     * \author João Vitor Espig (JotaEspig)
     * \date May 23, 2024
     * \version May 23, 2024
     * \param mesh - mesh object
     **/
    GMesh(const Mesh &mesh);
    /**
     * \brief Constructor
     * \author João Vitor Espig (JotaEspig)
     * \date October 06, 2023
     * \version October 06, 2023
     * \param vertices - polygon mesh vertices
     * \param indices - polygon mesh indices
     * \param textures - textures to be rendered with polygon mesh
     **/
    GMesh(
        const std::vector<Vertex> &vertices, const std::vector<GLuint> &indices,
        const std::vector<gl::Texture> &textures
    );

    /**
     * \brief binds a shader into gmesh
     * \author João Vitor Espig (JotaEspig)
     * \date October 27, 2023
     * \version October 27, 2023
     * \param shader_program - Shader
     **/
    void bind_shader(const gl::Shader &shader_program) override;
    /**
     * \brief binds a shader into gmesh
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
     * \brief sets shaders uniforms and do the binds
     * \author João Vitor Espig (JotaEspig)
     * \date May 24, 2024
     * \version May 24, 2024
     **/
    void default_draw_binds(const glm::mat4 &mat);
    /**
     * \brief unbinds things used in drawing
     * \author João Vitor Espig (JotaEspig)
     * \date May 24, 2024
     * \version May 24, 2024
     **/
    void default_draw_unbinds();
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
     * \date October 06, 2023
     * \version October 27, 2023
     * \param mat - model transformation matrix
     **/
    void draw(const glm::mat4 &mat) override;
    /**
     * \brief Destroys OpenGL objects created
     * \author João Vitor Espig (JotaEspig)
     * \date October 06, 2023
     * \version October 06, 2023
     **/
    void destroy();
};

} // namespace axolote
