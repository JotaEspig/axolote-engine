#pragma once

#include <vector>

#include <GL/gl.h>
#include <glm/glm.hpp>
#include <glm/gtx/quaternion.hpp>

#include <axolote/shader.hpp>
#include <axolote/camera.hpp>
#include <axolote/vao.hpp>
#include <axolote/vbo.hpp>
#include <axolote/ebo.hpp>
#include <axolote/texture.hpp>

namespace axolote
{
    class Mesh
    {
    public:
        bool is_simple_mesh = false;
        std::vector<Vertex> vertices;
        std::vector<GLuint> indices;
        std::vector<Texture> textures;
        VAO vao;
        VBO vbo;
        EBO ebo;

        Mesh(std::vector<Vertex> _vertices, std::vector<GLuint> _indices,
             std::vector<Texture> _textures);
        ~Mesh();

        void draw(Shader &shader,
                  glm::mat4 matrix = glm::mat4(1.0f),
                  glm::vec3 translation = glm::vec3(0.0f, 0.0f, 0.0f),
                  glm::quat rotation = glm::quat(1.0f, 0.0f, 0.0f, 0.0f),
                  glm::vec3 scale = glm::vec3(1.0f, 1.0f, 1.0f));
        void destroy();
    };
}
