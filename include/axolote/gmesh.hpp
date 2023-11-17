/**
 * \file gmesh.hpp
 * \brief Graphic Mesh class
 * \author João Vitor Espig (JotaEspig)
 * \date October 06, 2023
 * \version November 08, 2023
 **/
#pragma once

#include <vector>

#include <GL/gl.h>
#include <glm/glm.hpp>

#include <axolote/drawable.hpp>
#include <axolote/ebo.hpp>
#include <axolote/mesh.hpp>
#include <axolote/shader.hpp>
#include <axolote/texture.hpp>
#include <axolote/vao.hpp>
#include <axolote/vbo.hpp>

namespace axolote
{

/**
 * \brief defines a graphic polygon mesh
 * \author João Vitor Espig (JotaEspig)
 * \date October 06, 2023
 * \version November 08, 2023
 *
 * The difference between GMesh and Mesh is that GMesh you can draw
 **/
class GMesh : public Mesh, public Drawable
{
public:
    /** VAO **/
    VAO vao;
    /** VBO **/
    VBO vbo;
    /** EBO **/
    EBO ebo;
    /** Shader **/
    Shader shader;

    /**
     * \brief Constructor
     * \author João Vitor Espig (JotaEspig)
     * \date October 06, 2023
     * \version October 06, 2023
     **/
    GMesh();
    /**
     * \brief Copy constructor
     * \author João Vitor Espig (JotaEspig)
     * \date November 07, 2023
     * \version November 07, 2023
     * \param gmesh - GMesh object
     **/
    GMesh(const GMesh &gmesh);
    /**
     * \brief Move constructor
     * \author João Vitor Espig (JotaEspig)
     * \date November 07, 2023
     * \version November 07, 2023
     * \param gmesh - GMesh object
     **/
    GMesh(GMesh &&gmesh);
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
        const std::vector<Texture> &textures
    );

    /**
     * \brief binds a shader into gmesh
     * \author João Vitor Espig (JotaEspig)
     * \date October 27, 2023
     * \version October 27, 2023
     **/
    void bind_shader(const Shader &shader);
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
    /**
     * \brief operator = overload (copy)
     * \author João Vitor Espig (JotaEspig)
     * \date November 07, 2023
     * \version November 07, 2023
     * \param gmesh - GMesh object
     **/
    void operator=(const GMesh &gmesh);
    /**
     * \brief operator = overload (move)
     * \author João Vitor Espig (JotaEspig)
     * \date November 07, 2023
     * \version November 07, 2023
     * \param gmesh - GMesh object
     **/
    void operator=(GMesh &&gmesh);

    friend class Scene;
    friend class Entity;
};

} // namespace axolote
