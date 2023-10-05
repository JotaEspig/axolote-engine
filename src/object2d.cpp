#include <GL/gl.h>

#include <glm/glm.hpp>

#include <axolote/object2d.hpp>
#include <axolote/mesh.hpp>
#include <axolote/texture.hpp>
#include <axolote/structs.hpp>

namespace axolote
{

Object2D::Object2D()
{
}

Object2D::Object2D(std::vector<Vertex> vertices, std::vector<GLuint> indices,
                   std::vector<Texture> textures, glm::mat4 mat) :
    Mesh::Mesh(vertices, indices, textures)
{
    pos = mat;
}

void Object2D::draw(Shader &shader)
{
    Mesh::draw(shader, pos);
}

} // namespace axolote
