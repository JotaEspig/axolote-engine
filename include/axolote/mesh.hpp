#pragma once

#include <vector>

#include <GL/gl.h>
#include <glm/glm.hpp>

#include <axolote/shader.hpp>
#include <axolote/vao.hpp>
#include <axolote/vbo.hpp>
#include <axolote/ebo.hpp>
#include <axolote/texture.hpp>

namespace axolote
{

class Mesh
{
public:
    Mesh() = default;
    Mesh(std::vector<Vertex> _vertices, std::vector<GLuint> _indices,
         std::vector<Texture> _textures);

    void draw(Shader &shader, glm::mat4 matrix = glm::mat4(1.0f));
    void destroy();

private:
    std::vector<Vertex> vertices;
    std::vector<GLuint> indices;
    std::vector<Texture> textures;
    VAO vao;
    VBO vbo;
    EBO ebo;
};

} // namespace axolote
