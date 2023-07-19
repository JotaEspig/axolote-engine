#include <vector>

#include <GL/gl.h>

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
        std::vector<Vertex> vertices;
        std::vector<GLuint> indices;
        Texture texture;
        Texture specular_map;
        VAO vao;
        VBO vbo;
        EBO ebo;

        Mesh(std::vector<Vertex> _vertices, std::vector<GLuint> _indices,
             Texture _texture = Texture(), Texture _specular_map = Texture());
        ~Mesh();

        void draw(Shader &shader);
        void destroy();
    };
}
